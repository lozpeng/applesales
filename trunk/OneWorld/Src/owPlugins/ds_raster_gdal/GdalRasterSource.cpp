#include <owPlugins/ds_raster_gdal/GdalRasterSource.h>
#include <osgDB/ReadFile>
#include <osgDB/FileNameUtils>

#include <gdal_priv.h>
#include <owUtil/Log.h>

using namespace owPlugins;

float Hue_2_RGB( float v1, float v2, float vH )
{
	if ( vH < 0 ) vH += 1;
	if ( vH > 1 ) vH -= 1;
	if ( ( 6 * vH ) < 1 ) return ( v1 + ( v2 - v1 ) * 6 * vH );
	if ( ( 2 * vH ) < 1 ) return ( v2 );
	if ( ( 3 * vH ) < 2 ) return ( v1 + ( v2 - v1 ) * ( ( 2 / 3 ) - vH ) * 6 );
	return ( v1 );
}

template<class T>
static void rasterio_resample(GDALRasterBand* pBand, int lCol, int lRow, int lWidth, int lHeight, void* pBuffer, int lBufferWidth, int lBufferHeight, GDALDataType targetGDALType)
{
	if(lWidth<lBufferWidth && lHeight<lBufferHeight)
	{
		double ratiox = 1.0 * lWidth / lBufferWidth;
		double ratioy = 1.0 * lHeight / lBufferHeight;
		double x,y,dx,dy;
		int i2,j2;
		//int m1,n1,m2,n2,m3,n3,m4,n4;

		T* pBuffer1 = (T*) pBuffer;
		T* pBuffer2 = new T[lCol*lRow];

		pBand->RasterIO(GF_Read,lCol,lRow,lWidth,lHeight,pBuffer2,lWidth,lHeight,targetGDALType,0,0);

		for(int i=0; i<lBufferHeight; i++)
		{
			for(int j=0; j<lBufferWidth; j++)
			{
				x = j*ratiox-0.5; y = i*ratioy-0.5;
				i2 = floor(y); j2 = floor(x);
				dx = x - j2; dy = y - i2;


				//if(j2 == -1)
				//{
				//	m1 = m2 = 1; m3 = m4 = 0;
				//}
				//else if(j2 == (lWidth-1))
				//{
				//	m1 = m2 = (lWidth-1); m3 = m4 = (lWidth-2);

				//}
				//else
				//{
				//	m1 = m2 = j2; m3 = m4 = j2+1;
				//}

				//if(i2 == -1)
				//{
				//	n1 = n3 = 1; n2 = n4 = 0;
				//}
				//else if( i2 == (lHeight-1))
				//{
				//	n1 = n3 = (lHeight-1); n2 = n4 = (lHeight-2);
				//}
				//else
				//{	
				//	n1 = n3 = i2; n2 = n4 = i2+1;
				//}

				//{
				//	pBuffer1[i*lBufferWidth+j] = (1-dx)*(1-dy)*pBuffer2[n1*lWidth+m1]+(1-dx)*dy*pBuffer2[n2*lWidth+m2]+dx*(1-dy)*pBuffer2[n3*lWidth+m3]+dx*dy*pBuffer2[n4*lWidth+m4];
				//}

				if(j2==-1 || i2==-1 || j2==(lWidth-1) || i2 ==(lHeight-1))
				{
					pBuffer1[i*lBufferWidth+j] = pBuffer2[((int)y)*lWidth+((int)x)];
				}
				else
				{
					pBuffer1[i*lBufferWidth+j] = (1-dx)*(1-dy)*pBuffer2[i2*lWidth+j2]+(1-dx)*dy*pBuffer2[(i2+1)*lWidth+j2]+dx*(1-dy)*pBuffer2[i2*lWidth+j2+1]+dx*dy*pBuffer2[(i2+1)*lWidth+j2+1];
				}

			}
		}

		delete []pBuffer2;
	}
	else
	{
		pBand->RasterIO(GF_Read,lCol,lRow,lWidth,lHeight,pBuffer,lBufferWidth,lBufferHeight,targetGDALType,0,0);
	}
}

GdalRasterSource::GdalRasterSource() : _gdalDataSet(NULL),_heightChannel(1),_imageRChannel(1),_imageGChannel(2),_imageBChannel(3),_alphaChannel(-1),_imagePChannel(1),_bResample(true)
{

}

GdalRasterSource::~GdalRasterSource()
{
	GDALDestroyDriverManager();
}

osg::Image* GdalRasterSource::readImage(const GeoExtent* extent, int size)
{
	//是否有apha通道
	_alphaChannel = -1;
	for(int b=1;b<=_bands;++b)
	{
		GDALRasterBand* band = ((GDALDataset *)_gdalDataSet)->GetRasterBand(b);

		if(band->GetColorInterpretation()==GCI_AlphaBand)
		{
			_alphaChannel = b;
			break;
		}
	}

	//是否有颜色查找表通道
	_paletteChannel = -1;
	for(int b=1;b<=_bands;++b)
	{
		GDALRasterBand* band = ((GDALDataset *)_gdalDataSet)->GetRasterBand(b);

		if(band->GetColorInterpretation()==GCI_AlphaBand)
		{
			_paletteChannel = b;
			break;
		}
	}

	if(_paletteChannel != -1)
	{
		return readPalImage(extent,size);
	}
	else if(_bands>=3)
	{
		return readRGBImage(extent,size);
	}
	else if(_bands == 1 && _alphaChannel != -1)
	{
		return readAlphaImage(extent,size);
	}
	else
	{
		return readPanImage(extent,size);
	}
}


osg::Image* GdalRasterSource::readRGBImage(const GeoExtent* extent, int size)
{
	//
	if(_imageRChannel>_bands || _imageGChannel>_bands || _imageBChannel>_bands)
	{
		return NULL;
	}

	//
	GDALRasterBand* bandRed = 0;
	GDALRasterBand* bandGreen = 0;
	GDALRasterBand* bandBlue = 0;
	GDALRasterBand* bandAlpha = 0;

	bandRed = ((GDALDataset*)_gdalDataSet)->GetRasterBand(_imageRChannel);
	bandGreen = ((GDALDataset*)_gdalDataSet)->GetRasterBand(_imageGChannel);
	bandBlue = ((GDALDataset*)_gdalDataSet)->GetRasterBand(_imageBChannel);

	if(_alphaChannel != -1)
	{
		bandAlpha = ((GDALDataset*)_gdalDataSet)->GetRasterBand(_alphaChannel);
	}

	unsigned int pixelFormat = GL_LUMINANCE;
	unsigned int dataType = GL_UNSIGNED_BYTE;
	unsigned int numBytesPerPixel = 1;
	GDALDataType targetGDALType = GDT_Byte;

	targetGDALType = bandRed->GetRasterDataType();

	switch(targetGDALType)
	{
	case(GDT_Byte):
		dataType = GL_UNSIGNED_BYTE; numBytesPerPixel = 1;break;
	case(GDT_UInt16):
		dataType = GL_UNSIGNED_SHORT;numBytesPerPixel = 2;break;
	case(GDT_Int16): 
		dataType = GL_SHORT;numBytesPerPixel = 2;break;
	case(GDT_UInt32): 
		dataType = GL_UNSIGNED_INT; numBytesPerPixel = 4;break;
	case(GDT_Int32): 
		dataType = GL_INT;numBytesPerPixel = 4;break;
	case(GDT_Float32):
		dataType = GL_FLOAT;numBytesPerPixel = 4;break;
	case(GDT_Float64):
		dataType = GL_DOUBLE;numBytesPerPixel = 8;break;  // not handled
	default:
		break; // not handled
	}

	const SpatialProperty* sp = getSP();
	const GeoExtent* ex = sp->getGeoExtent();
	osg::ref_ptr<GeoExtent> intersect_ex = ex->intersect(extent);

	int windowX = osg::maximum((int)floorf((float)_width*(intersect_ex->xMin()-ex->xMin())/(ex->xMax()-ex->xMin())),0);
	int windowY = osg::maximum((int)floorf((float)_height*(ex->yMax() - intersect_ex->yMax())/(ex->yMax()-ex->yMin())),0);
	int windowWidth = osg::minimum((int)ceilf((float)_width*(intersect_ex->xMax()-ex->xMin())/(ex->xMax()-ex->xMin())),(int)_width)-windowX;
	int windowHeight = osg::minimum((int)ceilf((float)_height*(ex->yMax() - intersect_ex->yMin())/(ex->yMax()-ex->yMin())),(int)_height)-windowY;

	int destX = osg::maximum((int)floorf((float)size*(intersect_ex->xMin()-extent->xMin())/(extent->xMax()-extent->xMin())),0);
	int destY = osg::maximum((int)floorf((float)size*(extent->yMax() - intersect_ex->yMax())/(extent->yMax()-extent->yMin())),0);
	int destWidth = osg::minimum((int)ceilf((float)size*(intersect_ex->xMax()-extent->xMin())/(extent->xMax()-extent->xMin())),(int)size)-destX;;
	int destHeight = osg::minimum((int)ceilf((float)size*(extent->yMax() - intersect_ex->yMin())/(extent->yMax()-extent->yMin())),(int)size)-destY;

	int s = size;
	int t = size;
	int r = 1;

	if (bandAlpha)
	{
		// RGBA
		unsigned char* red = new unsigned char[destWidth * destHeight*numBytesPerPixel];
		unsigned char* green = new unsigned char[destWidth * destHeight*numBytesPerPixel];
		unsigned char* blue = new unsigned char[destWidth * destHeight*numBytesPerPixel];
		unsigned char* alpha = new unsigned char[destWidth * destHeight*numBytesPerPixel];

		pixelFormat = GL_RGBA;

		OSG_INFO << "reading RGBA"<<std::endl;

		bandRed->RasterIO(GF_Read,windowX,windowY,windowWidth,windowHeight,(void*)(red),destWidth,destHeight,targetGDALType,0,0);
		bandGreen->RasterIO(GF_Read,windowX,windowY,windowWidth,windowHeight,(void*)(green),destWidth,destHeight,targetGDALType,0,0);
		bandBlue->RasterIO(GF_Read,windowX,windowY,windowWidth,windowHeight,(void*)(blue),destWidth,destHeight,targetGDALType,0,0);
		bandAlpha->RasterIO(GF_Read,windowX,windowY,windowWidth,windowHeight,(void*)(alpha),destWidth,destHeight,targetGDALType,0,0);

		osg::Image* image = new osg::Image;
		image->allocateImage(s,t,r,pixelFormat,dataType);

		//初始化
		for(int i=0;i<image->t();++i)
		{
			for(int j=0;j<image->s();++j)
			{
				for(unsigned int b=0;b<numBytesPerPixel;++b)
				{
					*(image->data(j, i) + 0+b) = 0;
					*(image->data(j, i) + 1+b) = 0;
					*(image->data(j, i) + 2+b) = 0;
					*(image->data(j, i) + 3+b) = 0;
				}
			}
		}

		//赋值
		for(int src_row=0,des_row=destY ;src_row<destHeight;++src_row,++des_row)
		{
			for(int src_col=0, des_col=destX;src_col<destWidth;++src_col,++des_col)
			{
				for(unsigned int b=0;b<numBytesPerPixel;++b)
				{
					*(image->data(des_col, des_row) + 0+b) = red[(src_col + src_row * destWidth)*numBytesPerPixel+b];
					*(image->data(des_col, des_row) + 1+b) = green[(src_col + src_row * destWidth)*numBytesPerPixel+b];
					*(image->data(des_col, des_row) + 2+b) = blue[(src_col + src_row * destWidth)*numBytesPerPixel+b];
					*(image->data(des_col, des_row) + 3+b) = alpha[(src_col + src_row * destWidth)*numBytesPerPixel+b];
				}
			}
		}

		//
		image->flipVertical();

		delete []red;
		delete []green;
		delete []blue;
		delete []alpha;
		return image;
	}
	else
	{
		// RGB
		unsigned char *red = new unsigned char[destWidth * destHeight*numBytesPerPixel];
		unsigned char *green = new unsigned char[destWidth * destHeight*numBytesPerPixel];
		unsigned char *blue = new unsigned char[destWidth * destHeight*numBytesPerPixel];

		pixelFormat = GL_RGBA;

		OSG_INFO << "reading RGBA"<<std::endl;

		switch(targetGDALType)
		{
		case(GDT_Byte): 
			rasterio_resample<unsigned char>(bandRed,windowX,windowY,windowWidth,windowHeight,(void*)(red),destWidth,destHeight,targetGDALType);
			rasterio_resample<unsigned char>(bandGreen,windowX,windowY,windowWidth,windowHeight,(void*)(green),destWidth,destHeight,targetGDALType);
			rasterio_resample<unsigned char>(bandBlue,windowX,windowY,windowWidth,windowHeight,(void*)(blue),destWidth,destHeight,targetGDALType);
			break;
		case(GDT_UInt16):
			rasterio_resample<unsigned short>(bandRed,windowX,windowY,windowWidth,windowHeight,(void*)(red),destWidth,destHeight,targetGDALType);
			rasterio_resample<unsigned short>(bandGreen,windowX,windowY,windowWidth,windowHeight,(void*)(green),destWidth,destHeight,targetGDALType);
			rasterio_resample<unsigned short>(bandBlue,windowX,windowY,windowWidth,windowHeight,(void*)(blue),destWidth,destHeight,targetGDALType);
			break;
		case(GDT_Int16):
			rasterio_resample<short>(bandRed,windowX,windowY,windowWidth,windowHeight,(void*)(red),destWidth,destHeight,targetGDALType);
			rasterio_resample<short>(bandGreen,windowX,windowY,windowWidth,windowHeight,(void*)(green),destWidth,destHeight,targetGDALType);
			rasterio_resample<short>(bandBlue,windowX,windowY,windowWidth,windowHeight,(void*)(blue),destWidth,destHeight,targetGDALType);
			break;
		default:
			bandRed->RasterIO(GF_Read,windowX,windowY,windowWidth,windowHeight,(void*)(red),destWidth,destHeight,targetGDALType,0,0);
			bandGreen->RasterIO(GF_Read,windowX,windowY,windowWidth,windowHeight,(void*)(green),destWidth,destHeight,targetGDALType,0,0);
			bandBlue->RasterIO(GF_Read,windowX,windowY,windowWidth,windowHeight,(void*)(blue),destWidth,destHeight,targetGDALType,0,0);
			break; // not handled
		}

		osg::Image* image = new osg::Image;
		image->allocateImage(s,t,r,pixelFormat,dataType);

		//初始化
		for(int i=0;i<image->t();++i)
		{
			for(int j=0;j<image->s();++j)
			{
				for(unsigned int b=0;b<numBytesPerPixel;++b)
				{
					*(image->data(j, i) + 0+b) = 0;
					*(image->data(j, i) + 1+b) = 0;
					*(image->data(j, i) + 2+b) = 0;
					*(image->data(j, i) + 3+b) = 0;
				}
			}
		}

		//赋值

		for(int src_row=0,des_row=destY ;src_row<destHeight;++src_row,++des_row)
		{
			for(int src_col=0, des_col=destX;src_col<destWidth;++src_col,++des_col)
			{
				for(unsigned int b=0;b<numBytesPerPixel;++b)
				{
					*(image->data(des_col, des_row) + 0+b) = red[(src_col + src_row * destWidth)*numBytesPerPixel+b];
					*(image->data(des_col, des_row) + 1+b) = green[(src_col + src_row * destWidth)*numBytesPerPixel+b];
					*(image->data(des_col, des_row) + 2+b) = blue[(src_col + src_row * destWidth)*numBytesPerPixel+b];
					*(image->data(des_col, des_row) + 3+b) = 255;
				}
			}
		}

		image->flipVertical();

		delete []red;
		delete []green;
		delete []blue;

		return image;

	}
}

osg::Image* GdalRasterSource::readPanImage(const GeoExtent* extent, int size)
{
	//
	if(_imagePChannel>_bands)
	{
		return NULL;
	}

	//
	GDALRasterBand* bandGray= 0;
	GDALRasterBand* bandAlpha = 0;

	bandGray = ((GDALDataset*)_gdalDataSet)->GetRasterBand(_imagePChannel);

	if(_alphaChannel != -1)
	{
		bandAlpha = ((GDALDataset*)_gdalDataSet)->GetRasterBand(_alphaChannel);
	}

	unsigned int pixelFormat = GL_LUMINANCE;
	unsigned int dataType = GL_UNSIGNED_BYTE;
	unsigned int numBytesPerPixel = 1;
	GDALDataType targetGDALType = GDT_Byte;

	targetGDALType = bandGray->GetRasterDataType();

	switch(targetGDALType)
	{
	case(GDT_Byte):
		dataType = GL_UNSIGNED_BYTE; numBytesPerPixel = 1;break;
	case(GDT_UInt16):
		dataType = GL_UNSIGNED_SHORT;numBytesPerPixel = 2;break;
	case(GDT_Int16): 
		dataType = GL_SHORT;numBytesPerPixel = 2;break;
	case(GDT_UInt32): 
		dataType = GL_UNSIGNED_INT; numBytesPerPixel = 4;break;
	case(GDT_Int32): 
		dataType = GL_INT;numBytesPerPixel = 4;break;
	case(GDT_Float32):
		dataType = GL_FLOAT;numBytesPerPixel = 4;break;
	case(GDT_Float64):
		dataType = GL_DOUBLE;numBytesPerPixel = 8;break;  // not handled
	default:
		break; // not handled
	}

	const SpatialProperty* sp = getSP();
	const GeoExtent* ex = sp->getGeoExtent();
	osg::ref_ptr<GeoExtent> intersect_ex = ex->intersect(extent);

	int windowX = osg::maximum((int)floorf((float)_width*(intersect_ex->xMin()-ex->xMin())/(ex->xMax()-ex->xMin())),0);
	int windowY = osg::maximum((int)floorf((float)_height*(ex->yMax() - intersect_ex->yMax())/(ex->yMax()-ex->yMin())),0);
	int windowWidth = osg::minimum((int)ceilf((float)_width*(intersect_ex->xMax()-ex->xMin())/(ex->xMax()-ex->xMin())),(int)_width)-windowX;
	int windowHeight = osg::minimum((int)ceilf((float)_height*(ex->yMax() - intersect_ex->yMin())/(ex->yMax()-ex->yMin())),(int)_height)-windowY;

	int destX = osg::maximum((int)floorf((float)size*(intersect_ex->xMin()-extent->xMin())/(extent->xMax()-extent->xMin())),0);
	int destY = osg::maximum((int)floorf((float)size*(extent->yMax() - intersect_ex->yMax())/(extent->yMax()-extent->yMin())),0);
	int destWidth = osg::minimum((int)ceilf((float)size*(intersect_ex->xMax()-extent->xMin())/(extent->xMax()-extent->xMin())),(int)size)-destX;;
	int destHeight = osg::minimum((int)ceilf((float)size*(extent->yMax() - intersect_ex->yMin())/(extent->yMax()-extent->yMin())),(int)size)-destY;

	int s = size;
	int t = size;
	int r = 1;

	if (bandAlpha)
	{
		// Luminance alpha
		unsigned char* gray = new unsigned char[destWidth * destHeight*numBytesPerPixel];
		unsigned char* alpha = new unsigned char[destWidth * destHeight*numBytesPerPixel];

		pixelFormat = GL_LUMINANCE_ALPHA;

		OSG_INFO << "reading grey + alpha"<<std::endl;

		bandGray->RasterIO(GF_Read,windowX,windowY,windowWidth,windowHeight,(void*)(gray),destWidth,destHeight,targetGDALType,0,0);
		bandAlpha->RasterIO(GF_Read,windowX,windowY,windowWidth,windowHeight,(void*)(alpha),destWidth,destHeight,targetGDALType,0,0);

		osg::Image* image = new osg::Image;
		image->allocateImage(s,t,r,pixelFormat,dataType);

		//初始化
		for(int i=0;i<image->t();++i)
		{
			for(int j=0;j<image->s();++j)
			{
				for(unsigned int b=0;b<numBytesPerPixel;++b)
				{
					*(image->data(j, i) + 0+b) = 0;
					*(image->data(j, i) + 1+b) = 0;
				}
			}
		}

		//赋值
		for(int src_row=0,des_row=destY ;src_row<destHeight;++src_row,++des_row)
		{
			for(int src_col=0, des_col=destX;src_col<destWidth;++src_col,++des_col)
			{
				for(unsigned int b=0;b<numBytesPerPixel;++b)
				{
					*(image->data(des_col, des_row) + 0+b) = gray[(src_col + src_row * destWidth)*numBytesPerPixel+b];
					*(image->data(des_col, des_row) + 1+b) = alpha[(src_col + src_row * destWidth)*numBytesPerPixel+b];
				}
			}
		}

		image->flipVertical();

		delete []gray;
		delete []alpha;

		return image;
	}
	else
	{
		// Luminance map
		unsigned char* gray = new unsigned char[destWidth * destHeight*numBytesPerPixel];

		pixelFormat = GL_LUMINANCE_ALPHA;

		OSG_INFO << "reading grey"<<std::endl;

		switch(targetGDALType)
		{
		case(GDT_Byte): 
			rasterio_resample<unsigned char>(bandGray,windowX,windowY,windowWidth,windowHeight,(void*)(gray),destWidth,destHeight,targetGDALType);
			break;
		case(GDT_UInt16):
			rasterio_resample<unsigned short>(bandGray,windowX,windowY,windowWidth,windowHeight,(void*)(gray),destWidth,destHeight,targetGDALType);
			break;
		case(GDT_Int16):
			rasterio_resample<short>(bandGray,windowX,windowY,windowWidth,windowHeight,(void*)(gray),destWidth,destHeight,targetGDALType);
			break;
		default:
			bandGray->RasterIO(GF_Read,windowX,windowY,windowWidth,windowHeight,(void*)(gray),destWidth,destHeight,targetGDALType,0,0);
			break; // not handled
		}


		//bandGray->RasterIO(GF_Read,windowX,windowY,windowWidth,windowHeight,(void*)(gray),destWidth,destHeight,targetGDALType,0,0);

		osg::Image* image = new osg::Image;

		image->allocateImage(s,t,r,pixelFormat,dataType);

		//初始化
		for(int i=0;i<image->t();++i)
		{
			for(int j=0;j<image->s();++j)
			{
				for(unsigned int b=0;b<numBytesPerPixel;++b)
				{
					*(image->data(j, i) + 0+b) = 0;
					*(image->data(j, i) + 1+b) = 0;
				}
			}
		}

		//赋值

		for(int src_row=0,des_row=destY ;src_row<destHeight;++src_row,++des_row)
		{
			for(int src_col=0, des_col=destX;src_col<destWidth;++src_col,++des_col)
			{
				for(unsigned int b=0;b<numBytesPerPixel;++b)
				{
					*(image->data(des_col, des_row) + 0+b) = gray[(src_col + src_row * destWidth)*numBytesPerPixel+b];
					*(image->data(des_col, des_row) + 1+b) = 255;
				}
			}
		}

		image->flipVertical();

		delete []gray;

		return image;
	}
}

osg::Image* GdalRasterSource::readPalImage(const GeoExtent* extent, int size)
{
	//
	if(_paletteChannel == -1)
	{
		return NULL;
	}

	//
	GDALRasterBand* bandPalette = 0;
	bandPalette =((GDALDataset*)_gdalDataSet)->GetRasterBand(_paletteChannel);

	unsigned int pixelFormat = GL_LUMINANCE;
	unsigned int dataType = GL_UNSIGNED_BYTE;
	unsigned int numBytesPerPixel = 1;
	GDALDataType targetGDALType = GDT_Byte;

	targetGDALType = bandPalette->GetRasterDataType();

	switch(targetGDALType)
	{
	case(GDT_Byte):
		dataType = GL_UNSIGNED_BYTE; numBytesPerPixel = 1;break;
	case(GDT_UInt16):
		dataType = GL_UNSIGNED_SHORT;numBytesPerPixel = 2;break;
	case(GDT_Int16): 
		dataType = GL_SHORT;numBytesPerPixel = 2;break;
	case(GDT_UInt32): 
		dataType = GL_UNSIGNED_INT; numBytesPerPixel = 4;break;
	case(GDT_Int32): 
		dataType = GL_INT;numBytesPerPixel = 4;break;
	case(GDT_Float32):
		dataType = GL_FLOAT;numBytesPerPixel = 4;break;
	case(GDT_Float64):
		dataType = GL_DOUBLE;numBytesPerPixel = 8;break;  // not handled
	default:
		break; // not handled
	}

	const SpatialProperty* sp = getSP();
	const GeoExtent* ex = sp->getGeoExtent();
	osg::ref_ptr<GeoExtent> intersect_ex = ex->intersect(extent);

	int windowX = osg::maximum((int)floorf((float)_width*(intersect_ex->xMin()-ex->xMin())/(ex->xMax()-ex->xMin())),0);
	int windowY = osg::maximum((int)floorf((float)_height*(ex->yMax() - intersect_ex->yMax())/(ex->yMax()-ex->yMin())),0);
	int windowWidth = osg::minimum((int)ceilf((float)_width*(intersect_ex->xMax()-ex->xMin())/(ex->xMax()-ex->xMin())),(int)_width)-windowX;
	int windowHeight = osg::minimum((int)ceilf((float)_height*(ex->yMax() - intersect_ex->yMin())/(ex->yMax()-ex->yMin())),(int)_height)-windowY;

	int destX = osg::maximum((int)floorf((float)size*(intersect_ex->xMin()-extent->xMin())/(extent->xMax()-extent->xMin())),0);
	int destY = osg::maximum((int)floorf((float)size*(extent->yMax() - intersect_ex->yMax())/(extent->yMax()-extent->yMin())),0);
	int destWidth = osg::minimum((int)ceilf((float)size*(intersect_ex->xMax()-extent->xMin())/(extent->xMax()-extent->xMin())),(int)size)-destX;;
	int destHeight = osg::minimum((int)ceilf((float)size*(extent->yMax() - intersect_ex->yMin())/(extent->yMax()-extent->yMin())),(int)size)-destY;

	int s = size;
	int t = size;
	int r = 1;

	{
		// Paletted map
		int pixelSpace=1*numBytesPerPixel;
		int lineSpace=destWidth * pixelSpace;

		unsigned char* rawImageData = new unsigned char[destWidth * destHeight *pixelSpace];
		unsigned char* red = new unsigned char[destWidth * destHeight*numBytesPerPixel];
		unsigned char* green = new unsigned char[destWidth * destHeight*numBytesPerPixel];
		unsigned char* blue = new unsigned char[destWidth * destHeight*numBytesPerPixel];
		unsigned char* alpha = new unsigned char[destWidth * destHeight*numBytesPerPixel];
		pixelFormat = GL_RGBA;

		OSG_INFO << "reading palette"<<std::endl;
		OSG_INFO << "numBytesPerPixel: " << numBytesPerPixel << std::endl;

		bandPalette->RasterIO(GF_Read,windowX,windowY,windowWidth,windowHeight,(void*)(rawImageData),destWidth,destHeight,targetGDALType,pixelSpace,lineSpace);

		// Map the indexes to an actual RGBA Value.
		for (int i = 0; i < destWidth * destHeight; i++)
		{
			const GDALColorEntry *colorEntry = bandPalette->GetColorTable()->GetColorEntry(rawImageData[i]);
			GDALPaletteInterp interp = bandPalette->GetColorTable()->GetPaletteInterpretation();
			if (!colorEntry)
			{
				//FIXME: What to do here?

				//OSG_INFO << "NO COLOR ENTRY FOR COLOR " << rawImageData[i] << std::endl;
				red[4*i] = 255;
				green[4*i] = 0;
				blue[4*i] = 0;
				alpha[4*i] = 1;

			}
			else
			{
				if (interp == GPI_RGB)
				{
					red[4*i] = colorEntry->c1;
					green[4*i] = colorEntry->c2;
					blue[4*i] = colorEntry->c3;
					alpha[4*i] = colorEntry->c4;
				}
				else if (interp == GPI_CMYK)
				{
					// from wikipedia.org
					short C = colorEntry->c1;
					short M = colorEntry->c2;
					short Y = colorEntry->c3;
					short K = colorEntry->c4;
					red[4*i] = 255 - C*(255 - K) - K;
					green[4*i] = 255 - M*(255 - K) - K;
					blue[4*i] = 255 - Y*(255 - K) - K;
					alpha[4*i] = 255;
				}
				else if (interp == GPI_HLS)
				{
					// from easyrgb.com
					float H = colorEntry->c1;
					float S = colorEntry->c3;
					float L = colorEntry->c2;
					float R, G, B;
					if ( S == 0 )                       //HSL values = 0 - 1
					{
						R = L;                      //RGB results = 0 - 1 
						G = L;
						B = L;
					}
					else
					{
						float var_2, var_1;
						if ( L < 0.5 )
							var_2 = L * ( 1 + S );
						else
							var_2 = ( L + S ) - ( S * L );

						var_1 = 2 * L - var_2;

						R = Hue_2_RGB( var_1, var_2, H + ( 1 / 3 ) );
						G = Hue_2_RGB( var_1, var_2, H );
						B = Hue_2_RGB( var_1, var_2, H - ( 1 / 3 ) );                                
					} 
					red[4*i] = static_cast<unsigned char>(R*255.0f);
					green[4*i] = static_cast<unsigned char>(G*255.0f);
					blue[4*i] = static_cast<unsigned char>(B*255.0f);
					alpha[4*i] = static_cast<unsigned char>(255.0f);
				}
				else if (interp == GPI_Gray)
				{
					red[4*i] = static_cast<unsigned char>(colorEntry->c1*255.0f);
					green[4*i] = static_cast<unsigned char>(colorEntry->c1*255.0f);
					blue[4*i] = static_cast<unsigned char>(colorEntry->c1*255.0f);
					alpha[4*i] = static_cast<unsigned char>(255.0f);
				}
			}
		}

		osg::Image* image = new osg::Image;
		image->allocateImage(s,t,r,pixelFormat,dataType);

		//初始化
		for(int i=0;i<image->t();++i)
		{
			for(int j=0;j<image->s();++j)
			{
				for(unsigned int b=0;b<numBytesPerPixel;++b)
				{
					*(image->data(j, i) + 0+b) = 0;
					*(image->data(j, i) + 1+b) = 0;
					*(image->data(j, i) + 2+b) = 0;
					*(image->data(j, i) + 3+b) = 0;
				}
			}
		}

		//赋值

		for(int src_row=0,des_row=destY ;src_row<destHeight;++src_row,++des_row)
		{
			for(int src_col=0, des_col=destX;src_col<destWidth;++src_col,++des_col)
			{
				for(unsigned int b=0;b<numBytesPerPixel;++b)
				{
					*(image->data(des_col, des_row) + 0+b) = red[(src_col + src_row * destWidth)*numBytesPerPixel+b];
					*(image->data(des_col, des_row) + 1+b) = green[(src_col + src_row * destWidth)*numBytesPerPixel+b];
					*(image->data(des_col, des_row) + 2+b) = blue[(src_col + src_row * destWidth)*numBytesPerPixel+b];
					*(image->data(des_col, des_row) + 3+b) = alpha[(src_col + src_row * destWidth)*numBytesPerPixel+b];
				}
			}
		}

		image->flipVertical();

		delete [] rawImageData;
		delete [] red;
		delete [] green;
		delete [] blue;
		delete [] alpha;

		return image;
	}
}

osg::Image* GdalRasterSource::readAlphaImage(const GeoExtent* extent, int size)
{

	//
	if(_alphaChannel == -1)
	{
		return NULL;
	}

	//
	GDALRasterBand* bandAlpha = 0;
	bandAlpha = ((GDALDataset*)_gdalDataSet)->GetRasterBand(_alphaChannel);
	

	unsigned int pixelFormat = GL_LUMINANCE;
	unsigned int dataType = GL_UNSIGNED_BYTE;
	unsigned int numBytesPerPixel = 1;
	GDALDataType targetGDALType = GDT_Byte;

	targetGDALType = bandAlpha->GetRasterDataType();

	switch(targetGDALType)
	{
	case(GDT_Byte):
		dataType = GL_UNSIGNED_BYTE; numBytesPerPixel = 1;break;
	case(GDT_UInt16):
		dataType = GL_UNSIGNED_SHORT;numBytesPerPixel = 2;break;
	case(GDT_Int16): 
		dataType = GL_SHORT;numBytesPerPixel = 2;break;
	case(GDT_UInt32): 
		dataType = GL_UNSIGNED_INT; numBytesPerPixel = 4;break;
	case(GDT_Int32): 
		dataType = GL_INT;numBytesPerPixel = 4;break;
	case(GDT_Float32):
		dataType = GL_FLOAT;numBytesPerPixel = 4;break;
	case(GDT_Float64):
		dataType = GL_DOUBLE;numBytesPerPixel = 8;break;  // not handled
	default:
		break; // not handled
	}

	const SpatialProperty* sp = getSP();
	const GeoExtent* ex = sp->getGeoExtent();
	osg::ref_ptr<GeoExtent> intersect_ex = ex->intersect(extent);

	int windowX = osg::maximum((int)floorf((float)_width*(intersect_ex->xMin()-ex->xMin())/(ex->xMax()-ex->xMin())),0);
	int windowY = osg::maximum((int)floorf((float)_height*(ex->yMax() - intersect_ex->yMax())/(ex->yMax()-ex->yMin())),0);
	int windowWidth = osg::minimum((int)ceilf((float)_width*(intersect_ex->xMax()-ex->xMin())/(ex->xMax()-ex->xMin())),(int)_width)-windowX;
	int windowHeight = osg::minimum((int)ceilf((float)_height*(ex->yMax() - intersect_ex->yMin())/(ex->yMax()-ex->yMin())),(int)_height)-windowY;

	int destX = osg::maximum((int)floorf((float)size*(intersect_ex->xMin()-extent->xMin())/(extent->xMax()-extent->xMin())),0);
	int destY = osg::maximum((int)floorf((float)size*(extent->yMax() - intersect_ex->yMax())/(extent->yMax()-extent->yMin())),0);
	int destWidth = osg::minimum((int)ceilf((float)size*(intersect_ex->xMax()-extent->xMin())/(extent->xMax()-extent->xMin())),(int)size)-destX;;
	int destHeight = osg::minimum((int)ceilf((float)size*(extent->yMax() - intersect_ex->yMin())/(extent->yMax()-extent->yMin())),(int)size)-destY;

	int s = size;
	int t = size;
	int r = 1;

	{
		// alpha map
		unsigned char* alpha = new unsigned char[destWidth * destHeight*numBytesPerPixel];
		pixelFormat = GL_ALPHA;

		OSG_INFO << "reading alpha"<<std::endl;

		bandAlpha->RasterIO(GF_Read,windowX,windowY,windowWidth,windowHeight,(void*)(alpha),destWidth,destHeight,targetGDALType,0,0);

		osg::Image* image = new osg::Image;
		image->allocateImage(s,t,r,pixelFormat,dataType);

		//初始化
		for(int i=0;i<image->t();++i)
		{
			for(int j=0;j<image->s();++j)
			{
				for(unsigned int b=0;b<numBytesPerPixel;++b)
				{
					*(image->data(j, i) + 0+b) = 0;
				}
			}
		}

		//赋值
		for(int src_row=0,des_row=destY ;src_row<destHeight;++src_row,++des_row)
		{
			for(int src_col=0, des_col=destX;src_col<destWidth;++src_col,++des_col)
			{
				for(unsigned int b=0;b<numBytesPerPixel;++b)
				{
					*(image->data(des_col, des_row) + 0+b) = alpha[(src_col + src_row * destWidth)*numBytesPerPixel+b];
				}
			}
		}

		//
		image->flipVertical();

		delete []alpha;

		return image;
	}
}


osg::Image* GdalRasterSource::readHeight(const GeoExtent* extent, int size)
{
	//
	if(_heightChannel>_bands)
	{
		return NULL;
	}

	//
	GDALRasterBand* bandGray= 0;

	bandGray = ((GDALDataset*)_gdalDataSet)->GetRasterBand(_heightChannel);

	unsigned int pixelFormat = GL_LUMINANCE;
	unsigned int dataType = GL_UNSIGNED_BYTE;
	unsigned int numBytesPerPixel = 1;
	GDALDataType targetGDALType = GDT_Byte;

	targetGDALType = bandGray->GetRasterDataType();

	switch(targetGDALType)
	{
	case(GDT_Byte):
		dataType = GL_UNSIGNED_BYTE; numBytesPerPixel = 1;break;
	case(GDT_UInt16):
		dataType = GL_UNSIGNED_SHORT;numBytesPerPixel = 2;break;
	case(GDT_Int16): 
		dataType = GL_SHORT;numBytesPerPixel = 2;break;
	case(GDT_UInt32): 
		dataType = GL_UNSIGNED_INT; numBytesPerPixel = 4;break;
	case(GDT_Int32): 
		dataType = GL_INT;numBytesPerPixel = 4;break;
	case(GDT_Float32):
		dataType = GL_FLOAT;numBytesPerPixel = 4;break;
	case(GDT_Float64):
		dataType = GL_DOUBLE;numBytesPerPixel = 8;break;  // not handled
	default:
		break; // not handled
	}

	const SpatialProperty* sp = getSP();
	const GeoExtent* ex = sp->getGeoExtent();
	osg::ref_ptr<GeoExtent> intersect_ex = ex->intersect(extent);

	int windowX = osg::maximum((int)floorf((float)_width*(intersect_ex->xMin()-ex->xMin())/(ex->xMax()-ex->xMin())),0);
	int windowY = osg::maximum((int)floorf((float)_height*(ex->yMax() - intersect_ex->yMax())/(ex->yMax()-ex->yMin())),0);
	int windowWidth = osg::minimum((int)ceilf((float)_width*(intersect_ex->xMax()-ex->xMin())/(ex->xMax()-ex->xMin())),(int)_width)-windowX;
	int windowHeight = osg::minimum((int)ceilf((float)_height*(ex->yMax() - intersect_ex->yMin())/(ex->yMax()-ex->yMin())),(int)_height)-windowY;

	int destX = osg::maximum((int)floorf((float)size*(intersect_ex->xMin()-extent->xMin())/(extent->xMax()-extent->xMin())),0);
	int destY = osg::maximum((int)floorf((float)size*(extent->yMax() - intersect_ex->yMax())/(extent->yMax()-extent->yMin())),0);
	int destWidth = osg::minimum((int)ceilf((float)size*(intersect_ex->xMax()-extent->xMin())/(extent->xMax()-extent->xMin())),(int)size)-destX;;
	int destHeight = osg::minimum((int)ceilf((float)size*(extent->yMax() - intersect_ex->yMin())/(extent->yMax()-extent->yMin())),(int)size)-destY;

	int s = size;
	int t = size;
	int r = 1;

	{
		// Luminance map
		unsigned char* gray = new unsigned char[destWidth * destHeight*numBytesPerPixel];

		pixelFormat = GL_LUMINANCE;

		OSG_INFO << "reading grey"<<std::endl;

		switch(targetGDALType)
		{
		case(GDT_Byte): 
			rasterio_resample<unsigned char>(bandGray,windowX,windowY,windowWidth,windowHeight,(void*)(gray),destWidth,destHeight,targetGDALType);
			break;
		case(GDT_UInt16):
			rasterio_resample<unsigned short>(bandGray,windowX,windowY,windowWidth,windowHeight,(void*)(gray),destWidth,destHeight,targetGDALType);
			break;
		case(GDT_Int16):
			rasterio_resample<short>(bandGray,windowX,windowY,windowWidth,windowHeight,(void*)(gray),destWidth,destHeight,targetGDALType);
			break;
		default:
			bandGray->RasterIO(GF_Read,windowX,windowY,windowWidth,windowHeight,(void*)(gray),destWidth,destHeight,targetGDALType,0,0);
			break; // not handled
		}

		osg::Image* image = new osg::Image;

		image->allocateImage(s,t,r,pixelFormat,dataType);

		//初始化
		for(int i=0;i<image->t();++i)
		{
			for(int j=0;j<image->s();++j)
			{
				for(unsigned int b=0;b<numBytesPerPixel;++b)
				{
					*(image->data(j, i) + 0+b) = 0;
				}
			}
		}

		//赋值

		for(int src_row=0,des_row=destY ;src_row<destHeight;++src_row,++des_row)
		{
			for(int src_col=0, des_col=destX;src_col<destWidth;++src_col,++des_col)
			{
				for(unsigned int b=0;b<numBytesPerPixel;++b)
				{
					*(image->data(des_col, des_row) + 0+b) = gray[(src_col + src_row * destWidth)*numBytesPerPixel+b];
				}
			}
		}

		image->flipVertical();

		delete []gray;

		return image;
	}
}

Height* GdalRasterSource::CreatHeight(const SpatialProperty* sp,unsigned int tilesize,ProgressBase* p)
{
	if(!bValid())
	{
		std::ostringstream os;
		os<<"GDAL raster source: "<<_url<<"is invalid , return NULL";
		LOG_DEBUG(os.str());	
		return NULL;
	}

	unsigned int numBands = ((GDALDataset *)_gdalDataSet)->GetRasterCount();

	if(_heightChannel==0 || _heightChannel>numBands)
	{
		std::ostringstream os;
		os<<"Height band is invalid , return NULL";
		LOG_WARNING(os.str());	
		return NULL;
	}

	SpatialProperty* dt_sp = getSP();
	osg::ref_ptr<GeoExtent> readExtent = new GeoExtent(sp->getGeoExtent());
	if(!(sp->getSrs()->isEquivalentTo(dt_sp->getSrs())))
	{
		sp->getSrs()->transformExtent(dt_sp->getSrs(),readExtent->xMin(),readExtent->yMin(),readExtent->xMax(),readExtent->yMax());
	}

	if(!readExtent->isValid())
	{
		std::ostringstream os;
		os<<"The Extent to read is invalid , return NULL";
		LOG_DEBUG(os.str());	
		return NULL;
	}

	if(!dt_sp->getGeoExtent()->intersects(readExtent.get()))
		return NULL;

;

	osg::ref_ptr<osg::Image> image = readHeight(readExtent,tilesize);

	if(!image.valid())
	{
		std::ostringstream os;
		os<<"Error to read Height , return NULL";
		LOG_DEBUG(os.str());	
		return NULL;
	}


	unsigned int dataType = image->getDataType();

	Height* h = new Height(tilesize,tilesize);
	for(unsigned int i=0;i<tilesize;++i)
	{
		for(unsigned int j=0;j<tilesize;++j)
		{
			float v = 0.0;
			switch (dataType)
			{
			case GL_UNSIGNED_BYTE:
				v = float(*((unsigned char *)image->data(i, j)));
				break;
			case GL_UNSIGNED_SHORT:
				v = float(*((unsigned short *)image->data(i, j)));
				break;
			case GL_SHORT:
				v = float(*((short *)image->data(i, j)));
				break;
			case GL_UNSIGNED_INT:
				v = float(*((unsigned int *)image->data(i, j)));
				break;
			case GL_INT:
				v = float(*((int *)image->data(i, j)));
				break;
			case GL_FLOAT:
				v = float(*((float *)image->data(i, j)));
				break;
			case GL_DOUBLE:
				v = float(*((double *)image->data(i, j)));
				break;
			default:
				break;
			}

			h->setValue(i,j,v);
		}
	}

	return h;
}

osg::Image* GdalRasterSource::CreateImage(const SpatialProperty* sp,unsigned int tilesize,ProgressBase* p)
{
	if(!bValid())
	{
		std::ostringstream os;
		os<<"GDAL raster source: "<<_url<<"is invalid , return NULL";
		LOG_DEBUG(os.str());	
		return NULL;
	}

	unsigned int numBands = ((GDALDataset *)_gdalDataSet)->GetRasterCount();

	if(_imageRChannel==0 ||
		_imageGChannel == 0 ||
		_imageBChannel == 0 ||
		_imageRChannel>numBands ||
		_imageGChannel>numBands ||
		_imageBChannel>numBands)
	{
		std::ostringstream os;
		os<<"Image bands setting is invalid , return NULL";
		LOG_WARNING(os.str());	
		return NULL;
	}

	SpatialProperty* dt_sp = getSP();
	osg::ref_ptr<GeoExtent> readExtent = new GeoExtent(sp->getGeoExtent());
	if(!(sp->getSrs()->isEquivalentTo(dt_sp->getSrs())))
	{
		sp->getSrs()->transformExtent(dt_sp->getSrs(),readExtent->xMin(),readExtent->yMin(),readExtent->xMax(),readExtent->yMax());
	}

	if(!readExtent->isValid())
	{
		std::ostringstream os;
		os<<"The Extent to read is invalid , return NULL";
		LOG_DEBUG(os.str());	
		return NULL;
	}

	if(!dt_sp->getGeoExtent()->intersects(readExtent.get()))
		return NULL;

	osg::ref_ptr<osg::Image> image = readImage(readExtent,tilesize);

	if(!image.valid())
	{
		std::ostringstream os;
		os<<"Error to read Height , return NULL";
		LOG_DEBUG(os.str());	
		return NULL;
	}

	image->setDataVariance(osg::Object::DYNAMIC);

	return image.release();
}

bool GdalRasterSource::Connect(owUtil::ProgressBase* p)
{
	if(_gdalDataSet)
		return true;

	GDALAllRegister();

	//数据集
	_gdalDataSet = (void*)GDALOpen(_url.c_str(), GA_ReadOnly);

	if (!_gdalDataSet)
	{
		std::ostringstream os;
		os<<"Read file from: "<<_url<<"failed!";
		LOG_WARNING(os.str());
		return false;
	}

	//长宽和波段数
	_width = ((GDALDataset *)_gdalDataSet)->GetRasterXSize();
	_height = ((GDALDataset *)_gdalDataSet)->GetRasterYSize();
	_bands = ((GDALDataset *)_gdalDataSet)->GetRasterCount();

	if(_width==0 || _height==0 || _bands==0)
		return false;

	//投影信息
	const char* pszSourceSRS = ((GDALDataset *)_gdalDataSet)->GetProjectionRef();
	if (!pszSourceSRS || strlen(pszSourceSRS)==0) pszSourceSRS = ((GDALDataset *)_gdalDataSet)->GetGCPProjection();

	if (!pszSourceSRS || strlen(pszSourceSRS)==0)
	{
		std::ostringstream os;
		os<<"Read projection from file: "<<_url<<"failed!";
		LOG_WARNING(os.str());
		return false;
	}

	osg::ref_ptr<SpatialReference> srs = SpatialReference::create(pszSourceSRS);

	if(!srs.valid())
	{
		std::ostringstream os;
		os<<"Create spatial reference from file: "<<_url<<"failed!";
		LOG_WARNING(os.str());
		return false;
	}

	//地理范围
	double geoTransform[6];
	if (((GDALDataset *)_gdalDataSet)->GetGeoTransform(geoTransform)!=CE_None)
	{
		std::ostringstream os;
		os<<"Read Geo Extent from file: "<<_url<<"failed!";
		LOG_WARNING(os.str());
		return false;
	}

	osg::Matrixd m = osg::Matrixd::identity();
	m.set( geoTransform[1],    geoTransform[4],    0.0,    0.0,
		geoTransform[2],    geoTransform[5],    0.0,    0.0,
		0.0,                0.0,                1.0,    0.0,
		geoTransform[0],    geoTransform[3],    0.0,    1.0);

	osg::Vec3d lt =  osg::Vec3(0.0,0.0,0.0)*m;
	osg::Vec3d rb = osg::Vec3(_width,_height,0.0)*m;

	osg::ref_ptr<GeoExtent> e = new GeoExtent();
	e->expandToInclude(lt.x(),lt.y());
	e->expandToInclude(rb.x(),rb.y());

	osg::ref_ptr<SpatialProperty> sp = new SpatialProperty(e.get(),srs.get());

	if(!sp->isValid())
	{
		std::ostringstream os;
		os<<"Read Geo Extent from file: "<<_url<<" sucess, but it is invalid!";
		LOG_WARNING(os.str());
		return false;
	}

	setSP(sp);

	//设置数据源有效
	setValid(true);

	return true;
}

bool GdalRasterSource::disConnect(owUtil::ProgressBase* p)
{
	setValid(false);

	GDALClose(_gdalDataSet);

	_gdalDataSet = NULL;

	return true;
}


void GdalRasterSource::read(const Config& config)
{
	RasterSource::read(config);

	_url = config.value("url");

}

void GdalRasterSource::write(Config& config) const
{
	RasterSource::write(config);

}
std::string	GdalRasterSource::getUrl()
{
	return _url;
}