#include "stdafx.h"
#include "DSRasterDataset.h"
#include "RasterWorkspace.h"
#include <geometry/geom/Envelope.h>

using namespace Geodatabase;

CDSRasterDataset::CDSRasterDataset(CRasterWorkspace *pWorkspace,GDALDataset *pDataset,bool bRead,const char *name)
	:IRasterDataset(pWorkspace,NULL)
{
   m_pDataset =pDataset;

   m_bReadOnly =bRead;

   m_name =name;

   Init();
}

CDSRasterDataset::~CDSRasterDataset()
{
	if(m_pDataset)
	{
		delete m_pDataset;
		m_pDataset =NULL;
	}
}

void CDSRasterDataset::Init()
{
	m_lBand =GetBandCount();
}

bool CDSRasterDataset::IsWritable()
{
	return m_bReadOnly;
}


long CDSRasterDataset::GetBandCount()
{
	if(m_pDataset==NULL)
	{
		return 0;
	}

	return m_pDataset->GetRasterCount();
}

bool CDSRasterDataset::GetSize(long *plWidth, long *plHeight)
{
	if(!m_pDataset)
	{
		return false;
	}

	*plWidth=m_pDataset->GetRasterXSize();
	*plHeight=m_pDataset->GetRasterYSize();

	return true;
}


bool CDSRasterDataset::GetExtent(GEOMETRY::geom::Envelope *pEnvelop) const
{
	if(!m_pDataset)
	{
		return false;
	}

	double MinX,MinY,MaxX,MaxY;
	long width,height;

	width=m_pDataset->GetRasterXSize();
	height=m_pDataset->GetRasterYSize();



	double GeoTrans[6];
	if(CE_None==m_pDataset->GetGeoTransform(GeoTrans))
	{
		MinX = GeoTrans[0] + 0*GeoTrans[1] + height*GeoTrans[2];
		MinY = GeoTrans[3] + 0*GeoTrans[4] + height*GeoTrans[5];

		MaxX = GeoTrans[0] + width*GeoTrans[1] + 0*GeoTrans[2];
		MaxY = GeoTrans[3] + width*GeoTrans[4] + 0*GeoTrans[5];
	}
	else
	{
		MinX = 0;
		MinY = 0;

		MaxX = width;
		MaxY = height;
	}

	pEnvelop->init(MinX,MaxX,MinY,MaxY);

	return true;
}

bool CDSRasterDataset::GetCellSize (double *pdblSizeX, double *pdblSizeY)
{
	if(!m_pDataset)
	{
		return false;
	}

	GEOMETRY::geom::Envelope extent;
	long lWidth, lHeight;

	GetSize(&lWidth, &lHeight);
	GetExtent(&extent);

	*pdblSizeX = (extent.getMaxX() - extent.getMinX()) / lWidth;
	*pdblSizeY = (extent.getMaxY() - extent.getMinY()) / lHeight;

	return true;
}

BANDDATATYPE CDSRasterDataset::GetBandDataType(long lChannelIndex)
{
	if(!m_pDataset)
	{
		return BDT_UNKNOWN;
	}

	GDALRasterBand *pBand=m_pDataset->GetRasterBand(lChannelIndex);
	GDALDataType datatype = pBand->GetRasterDataType();

	BANDDATATYPE bandtype;

	switch(datatype)
	{
	case GDT_Byte:
		bandtype =BDT_BYTE;
		break;
	case GDT_UInt16:
		bandtype =BDT_USHORT;
		break;
	case GDT_Int16:
	case GDT_CInt16:
		bandtype =BDT_SHORT;
		break;
	case GDT_UInt32:
		bandtype =BDT_ULONG;
	case GDT_Int32:
		bandtype =BDT_LONG;
	case GDT_CInt32:
	case GDT_Float32:
	case GDT_CFloat32:
		bandtype =BDT_FLOAT;
		break;

	default:
		bandtype =BDT_UNKNOWN;
		break;

	}


	return bandtype;
}


bool CDSRasterDataset::GetBandMinMaxValue(long lChannelIndex, void *pvMaxValue, void *pvMinValue)
{
	if(!m_pDataset)
	{
		return false;
	}
	int nBand;
	nBand = lChannelIndex;
	int dblMinTemp, dblMaxTemp;
	double dblMin,dblMax;
	GDALRasterBand *poBand = NULL;
	poBand = m_pDataset->GetRasterBand( nBand );
	if ( NULL == poBand )
	{

		return false;
	}
	dblMin = poBand->GetMinimum( &dblMinTemp );
	dblMax = poBand->GetMaximum( &dblMaxTemp );   
	if( (dblMin && dblMax) )
	{
		*((double *)pvMinValue) = dblMin;
		*((double *)pvMaxValue) = dblMax;
	}

	return true;
}



/*@*****************************坐标转换，投影相关接口*****************************************@*/


bool CDSRasterDataset::SetCoordinateExtent(const GEOMETRY::geom::Envelope &extent)
{
	if(!m_pDataset)
	{
		return false;
	}
	double dblTrans[6];
	double CellSizeX,CellSizeY;

	long lwidth,lheight;
	GetSize(&lwidth, &lheight);
	CellSizeX = (extent.getMaxX() - extent.getMinX())/lwidth;
	CellSizeY = (extent.getMaxY() - extent.getMinY())/lheight;

	dblTrans[0] = extent.getMinX();
	dblTrans[1] = CellSizeX;
	dblTrans[2] = 0;
	dblTrans[3] = extent.getMaxY(); 
	dblTrans[4] = 0;
	dblTrans[5] = -CellSizeY;
	if(CE_Failure==m_pDataset->SetGeoTransform(dblTrans))
	{
		return false;
	}

	return true;
}


bool CDSRasterDataset::WorldToPixel (double dblX, double dblY, long *plCol,long *plRow)
{
	if(!m_pDataset)
	{
		return false;
	}
	long width,height;
	GetSize(&width, &height);

	double GeoTrans[6];
	if(CE_None==m_pDataset->GetGeoTransform(GeoTrans))
	{
		*plCol=(long)((GeoTrans[5]*(dblX-GeoTrans[0])-GeoTrans[2]*(dblY-GeoTrans[3]))/(GeoTrans[1]*GeoTrans[5]-GeoTrans[4]*GeoTrans[2]) + 1);
		*plRow=(long)((GeoTrans[4]*(dblX-GeoTrans[0])-GeoTrans[1]*(dblY-GeoTrans[3]))/(GeoTrans[4]*GeoTrans[2]-GeoTrans[1]*GeoTrans[5]) + 1);

	}
	else
	{

		*plCol=(long)(dblX + 1);
		*plRow=(long)(height -dblY + 1);
	}

	if (*plRow < 1)
		*plRow = 1;
	if (*plCol < 1)
		*plCol = 1;

	if (*plRow > height)
		*plRow = height;
	if (*plCol > width)
		*plCol = width;

	return true;
}


bool CDSRasterDataset::PixelToWorld ( long lCol,long lRow, double *pdblX, double *pdblY)
{
	if(!m_pDataset)
	{
		return false;
	}

	double GeoTrans[6];
	if(CE_None==m_pDataset->GetGeoTransform(GeoTrans))
	{
		*pdblX=GeoTrans[0]+(lCol-0.5)*GeoTrans[1]+(lRow-0.5)*GeoTrans[2];
		*pdblY=GeoTrans[3]+(lCol-0.5)*GeoTrans[4]+(lRow-0.5)*GeoTrans[5];
	}
	else
	{
		long width,height;
		GetSize(&width,&height);

		*pdblX=(double)(lCol-0.5);
		*pdblY=(double)(height-lRow+0.5);
	}
	return true;

}


std::string CDSRasterDataset::GetProjection()
{
	if(!m_pDataset)
	{
		return "";
	}
	return m_pDataset->GetProjectionRef();
}


bool CDSRasterDataset::SetProjection(const char *pszWKT)
{
	if(!m_pDataset)
	{
		return false;
	}
	CPLErr error=m_pDataset->SetProjection(pszWKT);
	if(error==CE_Failure)
	{
		return false;
	}
	return true;
}


/*@*****************************数据读取相关接口********************************************@*/

bool    CDSRasterDataset::GetPixel(long lBandIndex,long lCol, long lRow,  void *pvValue)
{
	if(m_pDataset==NULL || lBandIndex<1 || lBandIndex>m_lBand)
	{
		return false;
	}

	GDALRasterBand *pBand=m_pDataset->GetRasterBand(lBandIndex);
	GDALDataType datatype=pBand->GetRasterDataType();
	CPLErr error=pBand->RasterIO(GF_Read,lCol-1,lRow-1,1,1,pvValue,1,1,datatype,0,0);

	if(error==CE_Failure)
	{
		return false;
	}
	return true;
}

bool	CDSRasterDataset::SetPixel(long lBandIndex,long lCol,  long lRow, void *pvValue)
{
	if(m_pDataset==NULL || lBandIndex<1 || lBandIndex>m_lBand)
	{
		return false;
	}

	GDALRasterBand *pBand=m_pDataset->GetRasterBand(lBandIndex);
	GDALDataType datatype = pBand->GetRasterDataType();
	CPLErr error=pBand->RasterIO(GF_Write,lCol-1,lRow-1,1,1,pvValue,1,1,datatype,0,0);

	if(error==CE_Failure)
	{
		return false;
	}
	return true;
}

bool CDSRasterDataset::DataReadBandNormalize(long lBandIndex, long lCol, long lRow, long lWidth, long lHeight, long lBuffSizeX, long lBuffSizeY, unsigned char *pbBuffer,double minValue,double maxValue)
{
	 if(m_pDataset==NULL || lBandIndex<1 || lBandIndex>m_lBand)
	{
		return false;
	}

    GDALRasterBand *pBand=m_pDataset->GetRasterBand(lBandIndex);
	GDALDataType datatype = pBand->GetRasterDataType();
    switch(datatype)
	{
	case GDT_Byte:
		BYTE bdummyTemp;
		if(false==ReadNormal<BYTE>(bdummyTemp,lBandIndex,lCol,lRow,lWidth,lHeight,lBuffSizeX,lBuffSizeY,pbBuffer,minValue,maxValue))
		{
			return false;
		}
		break;
	case GDT_UInt16:
        unsigned short usTemp;
		if(false==ReadNormal<unsigned short>(usTemp,lBandIndex,lCol,lRow,lWidth,lHeight,lBuffSizeX,lBuffSizeY,pbBuffer,minValue,maxValue))
		{
			return false;
		}
		break;
	case GDT_Int16:
	case GDT_CInt16:
		short sTemp;
		  
		if(false==ReadNormal<short>(sTemp,lBandIndex,lCol,lRow,lWidth,lHeight,lBuffSizeX,lBuffSizeY,pbBuffer,minValue,maxValue))
		{
			return false;
		}
		break;
	case GDT_UInt32:
		unsigned int uiTemp;
		if(false==ReadNormal<unsigned int>(uiTemp,lBandIndex,lCol,lRow,lWidth,lHeight,lBuffSizeX,lBuffSizeY,pbBuffer,minValue,maxValue))
		{
			return false;
		}
		break;
	case GDT_Int32:
	case GDT_CInt32:
		int iTemp;
		if(false==ReadNormal<int>(iTemp,lBandIndex,lCol,lRow,lWidth,lHeight,lBuffSizeX,lBuffSizeY,pbBuffer,minValue,maxValue))
		{
		  return false;
		}
		break;
	case GDT_Float32:
	case GDT_CFloat32:
		float fTemp;
		if(false==ReadNormal<float>(fTemp,lBandIndex,lCol,lRow,lWidth,lHeight,lBuffSizeX,lBuffSizeY,pbBuffer,minValue,maxValue))
		{
		  return false;
		}
		break;
	case GDT_Float64:
	case GDT_CFloat64:
		double dTemp;
		if(false==ReadNormal<double>(dTemp,lBandIndex,lCol,lRow,lWidth,lHeight,lBuffSizeX,lBuffSizeY,pbBuffer,minValue,maxValue))
		{
		  return false;
		}
		break;
	default:
	  return false;
	  break;
	}
	return true;
}

bool CDSRasterDataset::DataReadBand(long lBandIndex, long lCol, long lRow, long lWidth, long lHeight, long lBuffSizeX, long lBuffSizeY, void *pvBuffer)
{
	if(m_pDataset==NULL || lBandIndex<1 || lBandIndex>m_lBand)
	{
		return false;
	}
    GDALRasterBand *pBand=m_pDataset->GetRasterBand(lBandIndex);
	GDALDataType datatype= pBand->GetRasterDataType();

	CPLErr error=pBand->RasterIO(GF_Read,lCol-1,lRow-1,lWidth,lHeight,pvBuffer,lBuffSizeX,lBuffSizeY,datatype,0,0);

	if(error==CE_Failure)
	{
		return false;
	}
	return true;
}

bool CDSRasterDataset::DataWriteBand(long lBandIndex, long lCol, long lRow, long lWidth, long lHeight, void *pvBuffer)
{
	if(m_pDataset==NULL || lBandIndex<1 || lBandIndex>m_lBand)
	{
		return false;
	}

    GDALRasterBand *pBand=m_pDataset->GetRasterBand(lBandIndex);
	GDALDataType datatype= pBand->GetRasterDataType();
	CPLErr error=pBand->RasterIO(GF_Write,lCol-1,lRow-1,lWidth,lHeight,pvBuffer,lWidth,lHeight,datatype,0,0);

	if(error==CE_Failure)
	{
		return false;
	}

	return true;
}




/*@*****************************金字塔操作相关接口********************************************@*/

bool	CDSRasterDataset::HasPyramid()
{
	if(m_pDataset==NULL)
	{
		return false;
	}

	GDALRasterBand *pBand=m_pDataset->GetRasterBand(1);
	if(pBand->GetOverviewCount()==0)
	{
		return false;

	}
	return true;
}

//建立金字塔
bool CDSRasterDataset::BuildPyramid(double dResample)
{
	if(m_pDataset==NULL)
	{
		return false;
	}
	//如果文件以可写方式打开，则转化为以只读方式打开
	GDALAccess m_access =GA_ReadOnly;
	if(!m_bReadOnly)
	{
		delete m_pDataset;
		m_pDataset=(GDALDataset*)GDALOpen(m_name.c_str(),GA_ReadOnly);

		m_access =GA_Update;

	}
    int rate=(int)(1/dResample+0.5);
	long width,height;
	GetSize(&width,&height);
	long minBound=(width>height)?height:width;//最小边
    long ratio=minBound/16;  //缩放的最大比率
	int lLevel=log((double)ratio)/log((double)rate);//计算所需层数

    int *panBandList=new int[lLevel];
	for(int i=0;i<lLevel;i++)
	{
		panBandList[i]=pow(double(rate),double(i+1));
	}
	
	//

	CPLErr error=m_pDataset->BuildOverviews("AVERAGE",lLevel,panBandList,0,NULL,NULL,NULL);

	//重新打开建过金字塔的文件
	delete []panBandList;
	delete m_pDataset;
	m_pDataset=(GDALDataset*)GDALOpen(m_name.c_str(),m_access);
	if(CE_Failure==error)
	{
		return false;
	}


	return true;
}

bool CDSRasterDataset::DataReadPyramidBand(long lLevel, long lBandIndex, long lCol, long lRow, long lWidth, long lHeight,long lBuffSizeX, long lBuffSizeY, void *pvBuffer)
{
	CPLErr error;
    if(m_pDataset==NULL || lBandIndex<1 || lBandIndex>m_lBand)
	{
		return false;
	}

	GDALRasterBand *pBand=m_pDataset->GetRasterBand(lBandIndex);
	GDALDataType datatype=pBand->GetRasterDataType();
	int ocount=pBand->GetOverviewCount();

	if(lLevel<0 || lLevel>ocount)
	{
	  return false;
	}

	if(lLevel == 0)
	{
		error=pBand->RasterIO(GF_Read,lCol-1,lRow-1,lWidth,lHeight,pvBuffer,lBuffSizeX, lBuffSizeY,datatype,0,0);
	}
	else
	{
		GDALRasterBand *poverBand=pBand->GetOverview(lLevel-1);
		error=poverBand->RasterIO(GF_Read,lCol-1,lRow-1,lWidth,lHeight,pvBuffer,lBuffSizeX, lBuffSizeY,datatype,0,0);
	}

	if(CE_Failure==error)
	{
		return false;
	}

	return true;
}


bool CDSRasterDataset::GetPyramidSize( long lLevel, long *lWidth, long *lHeight)
{
	if(m_pDataset==NULL)
	{
		return false;
	}

	GDALRasterBand *pBand=m_pDataset->GetRasterBand(1);
	int ovrCount=pBand->GetOverviewCount();

	if(lLevel<0 || lLevel>ovrCount)
	{
	 return false;
	}


	GDALRasterBand *poverBand=NULL;
	if(lLevel==0)
	{
          poverBand=pBand;
	}
	else
	{
		poverBand=pBand->GetOverview(lLevel-1);
	}
	
		
		*lWidth = poverBand->GetXSize();
		*lHeight = poverBand->GetYSize();
	
	return true;
}

bool CDSRasterDataset::GetPyramidCellSize(long lLevel, double *pdCellX, double *pdCellY)
{
	 if(m_pDataset==NULL)
	{
		return false;
	}

	GDALRasterBand *pBand=m_pDataset->GetRasterBand(1);
	int ovrCount=pBand->GetOverviewCount();

	if(lLevel<0 || lLevel>ovrCount)
	{
	 return false;
	}
	GDALRasterBand *poverBand=pBand->GetOverview(lLevel-1);

	GEOMETRY::geom::Envelope extent;
	long lWidth, lHeight;

	GetPyramidSize(lLevel, &lWidth, &lHeight);
	GetExtent(&extent);

	*pdCellX = (extent.getMaxX() - extent.getMinX()) / lWidth;
	*pdCellY = (extent.getMaxY() - extent.getMinY()) / lHeight;

	return true;
}

bool CDSRasterDataset::GetPyramidLevelNum(long *lLevelNum)
{
	if(m_pDataset==NULL)
	{
		return false;
	}

	GDALRasterBand *pBand=m_pDataset->GetRasterBand(1);
	*lLevelNum=pBand->GetOverviewCount() + 1;
	return true;
}

bool CDSRasterDataset::ReadPyramidNormal(long lLevel,long lBandlIndex, long lCol, long lRow, long lWidth, long lHeight, long lBuffSizeX, long lBuffSizeY, unsigned char *pbBuffer)
{
	return false;
}


//数据压缩
template<class T>
bool CDSRasterDataset::ReadNormal(T dummyTemp, long lBandIndex, long lCol, long lRow, long lWidth, long lHeight, long lBuffSizeX, long lBuffSizeY, BYTE *pbBuffer,double dblMin,double dblMax)
{
	T* tempBuffer;
	//建立一块临时缓存，用来存放从图像中读取的未压缩数据
	tempBuffer=(T*)malloc(sizeof(T)*lBuffSizeX*lBuffSizeY);
	if(false==DataReadBand(lBandIndex,lCol,lRow,lWidth,lHeight,lBuffSizeX,lBuffSizeY,tempBuffer))
	{
		free(tempBuffer);
		return false;
	}

	double dblValue;


	T* temp=tempBuffer;
	for (long i=0;i<lBuffSizeX*lBuffSizeY;i++)
	{
		dblValue = double(*temp);

		if(dblValue<dblMin)
			dblValue = dblMin;
		if(dblValue>dblMax)
			dblValue=dblMax;

		*pbBuffer=(BYTE)((dblValue-dblMin)/(double)(dblMax-dblMin)*255);
		++temp;++pbBuffer;
	}
        
	free(tempBuffer);
	return true;
}