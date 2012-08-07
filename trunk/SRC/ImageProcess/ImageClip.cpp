#include "stdafx.h"
#include "ImageClip.h"
#include "IWorkspace.h"
#include "RasterWSFactory.h"
#include "ShapefileWorkspaceFactory.h"

namespace ImageProcess
{

#define XtoCol(dblX, lWidth, stExtent) ((dblX - stExtent.xmin) / (stExtent.xmax - stExtent.xmin) * (lWidth))
#define	YtoRow(dblY, lHeight, stExtent) (lHeight - (dblY - stExtent.ymin) / (stExtent.ymax - stExtent.ymin) * (lHeight))


bool ImgClip(const char* pszInFile, 
	const char* pszOutFile, 
	GEOMETRY::geom::Envelope& aoiExtent,
	double dblCellX,
	double dblCellY)
{
	using namespace Geodatabase;
	long     lWidth1, lHeight1, lWidth2, lHeight2;
	long     lChannelCount, lDataType;
	STExtent stExtent1;

	Geodatabase::IWorkspace *pSrcWp =CRasterWSFactory::GetInstance()->OpenFromFile(pszInFile);
	if(!pSrcWp)
	{
		return false;
	}
	//打开原文件
	Geodatabase::IRasterDatasetPtr pSrcRS =pSrcWp->OpenRasterDataset(pszInFile);
	if(!pSrcRS)
	{
		return false;
	}
	//输入影像
	
	GEOMETRY::geom::Envelope env;
	pSrcRS->CreateBuffer();
	pSrcRS->GetExtent(&env);
	stExtent1.xmax =env.getMaxX();
	stExtent1.xmin =env.getMinX();
	stExtent1.ymax =env.getMaxY();
	stExtent1.ymin =env.getMinY();

	pSrcRS->GetSize(&lWidth1, &lHeight1);
	lChannelCount =pSrcRS->GetBandCount();
	
	lDataType =(long)pSrcRS->GetBandDataType(1);


	//重采样后图像的范围计算
	lWidth2 = (long)(aoiExtent.getWidth()/dblCellX + 0.5);
	lHeight2 = (long)(aoiExtent.getHeight()/dblCellY + 0.5);
	
	//获取目标文件文件夹路径
	std::string path =pszOutFile;

	path =path.substr(0,path.rfind('\\'));
	Geodatabase::IWorkspace *pdestWS =CRasterWSFactory::GetInstance()->OpenFolder(path.c_str());
	if(!pdestWS)
	{
		return false;
	}

	//重采样影像建立
	RasFileInfo rasfileInfoDes;
	rasfileInfoDes.lWidth = lWidth2;			//图像的宽度
	rasfileInfoDes.lHeight = lHeight2;			//图像的高度
	rasfileInfoDes.lChannelNum = lChannelCount;	//图像的通道数
	rasfileInfoDes.lDataType = lDataType;

	if(!pdestWS->CreateRasterDataset(pszOutFile,&rasfileInfoDes))
	{
		return false;
	}
    IRasterDatasetPtr rasDestDS =pdestWS->OpenRasterDataset(pszOutFile,false);


	if(!rasDestDS)
	{
		return false;
	}
	rasDestDS->CreateBuffer();

	rasDestDS->SetCoordinateExtent(aoiExtent);

	//图像重采样开始
	BYTE byValue = 0;
	unsigned short usValue = 0;
	short sValue = 0;
	float fValue = 0.0;
	double lon,lat;
	double dblx2, dbly2;
	double dblPixelPosX,dblPixelPosY;
	int k =0;
	//进度条
	int i,j;
	for (long m =0; m < lChannelCount; m++)
	{
		k = m+1;

		dbly2 = aoiExtent.getMaxY() - dblCellY/2;
		for ( i = 0; i < lHeight2; i++)
		{
			
			dblx2 = aoiExtent.getMinX() + dblCellX/2;
			for ( j = 0; j < lWidth2; j++)
			{
				lon=dblx2;
				lat=dbly2;

				dblPixelPosX = XtoCol(lon,lWidth1,stExtent1);
				dblPixelPosY = YtoRow(lat,lHeight1,stExtent1);

				switch((BANDDATATYPE)lDataType)
				{
				case BDT_BYTE:
					{
						pSrcRS->PixelIO(k,dblPixelPosX+0.5,dblPixelPosY+0.5,&byValue,true);

						rasDestDS->PixelIO(m+1, j+1 , i+1, &byValue, false);
					}
					break;
				case BDT_SHORT:
					{
						

						pSrcRS->PixelIO(k,dblPixelPosX+0.5,dblPixelPosY+0.5,&sValue,true);

						rasDestDS->PixelIO(m+1, j+1 , i+1, &sValue, false);
					}
					break;
				case BDT_USHORT:
					{

						pSrcRS->PixelIO(k,dblPixelPosX+0.5,dblPixelPosY+0.5,&usValue,true);

						rasDestDS->PixelIO(m+1, j+1 , i+1, &usValue, false);
					}
					break;
				case BDT_FLOAT:
					{
						pSrcRS->PixelIO(k,dblPixelPosX+0.5,dblPixelPosY+0.5,&fValue,true);

						rasDestDS->PixelIO(m+1, j+1 , i+1, &fValue, false);
					}
					break;
				default:
					break;
				}
				dblx2 += dblCellX;
			}

			dbly2 -= dblCellY;
		}
	}


	pSrcRS->DeleteBuffer();
;
	rasDestDS->DeleteBuffer();


	return true;
}

bool TargetClip(const char* pszInImage,
				const char* pszTargetFile,
				long lWidth,
				long lHeight,
				const char* pszOutPath)
{

	Geodatabase::IWorkspace *pSrcWp =CRasterWSFactory::GetInstance()->OpenFromFile(pszInImage);
	if(!pSrcWp)
	{
		return false;
	}
	//打开原文件
	Geodatabase::IRasterDatasetPtr pSrcRS =pSrcWp->OpenRasterDataset(pszInImage);
	if(!pSrcRS)
	{
		return false;
	}

	double dblSizeX, dblSizeY;
	pSrcRS->GetCellSize(&dblSizeX,&dblSizeY);

	//打开原文件
	Geodatabase::IWorkspace *pshpWS =CShapefileWorkspaceFactory::GetInstance()->OpenFromFile(pszTargetFile);
	if(!pshpWS)
	{
		return false;
	}

	Geodatabase::IFeatureClassPtr pFeatureClass =pshpWS->OpenFeatureClass(pszTargetFile);

	if(!pFeatureClass)
	{
		return false;
	}

	long lIndex = pFeatureClass->FindField("Name");
	std::string filename = pszInImage;
	filename = filename.substr(filename.rfind('\\')+1,filename.rfind('.')-filename.rfind('\\')-1);

	for(int i=0; i<pFeatureClass->FeatureCount(); i++)
	{
		//
		Geodatabase::CFeaturePtr pFeature = pFeatureClass->GetFeature(i+1);

		//
		GEOMETRY::geom::Geometry* pshape = pFeature->GetShape();
		const GEOMETRY::geom::Coordinate* coor = pshape->getCoordinate();
		GEOMETRY::geom::Envelope env(coor->x-lWidth/2.0*dblSizeX, coor->x+lWidth/2.0*dblSizeX, coor->y-lHeight/2.0*dblSizeY, coor->y+lHeight/2.0*dblSizeY);

		//
		Geodatabase::FieldValue fv = pFeature->GetValue(lIndex);
		std::string name = fv.GetasString();
		
		//
		std::string bname = pszOutPath + filename + "_"+name + ".tif";
		ImgClip(pszInImage, bname.c_str(), env, dblSizeX, dblSizeY);

	}

}


bool RelativeMap(const char* strSrc, const char* strDest, const char *strResult, int nsize, SYSTEM::IProgress *pProgress)
{
	Geodatabase::IWorkspace *pSrcWp =CRasterWSFactory::GetInstance()->OpenFromFile(strSrc);
	if(!pSrcWp)
	{
		return false;
	}
	//打开原文件
	Geodatabase::IRasterDatasetPtr pSrcRS =pSrcWp->OpenRasterDataset(strSrc);
	if(!pSrcRS)
	{
		return false;
	}

	Geodatabase::IWorkspace *pDestWp =CRasterWSFactory::GetInstance()->OpenFromFile(strDest);
	if(!pDestWp)
	{
		return false;
	}
	//打开目标文件
	Geodatabase::IRasterDatasetPtr pdestRS =pDestWp->OpenRasterDataset(strDest);
	if(!pdestRS)
	{
		return false;
	}
	GEOMETRY::geom::Envelope extent1,extent2;
	pSrcRS->GetExtent(&extent1);
	pdestRS->GetExtent(&extent2);

	//判断两幅图有没有交集
	if(!extent1.intersects(extent2))
	{
		return false;
	}
	bool bClip =true;
	long lwidth1,lheight1;
	long lwidth2,lheight2;
	pSrcRS->GetSize(&lwidth1,&lheight1);
	pdestRS->GetSize(&lwidth2,&lheight2);
	if(extent1==extent2)
	{

		if(lwidth1==lwidth2 && lheight1==lheight2)
		{
			bClip =false;
		}
	}
	//建立进度条
	if(pProgress)
	{
		pProgress->Create("处理中",SYSTEM::IProgress::Percent,100);
		pProgress->UpdateProgress("",0.01);

	}

	if(bClip)
	{
		//切割图像
		GEOMETRY::geom::Envelope interExt;
		extent1.intersection(extent2,interExt);
		std::string syspath =SYSTEM::CSystemPath::GetSystemPath();
		syspath+="temp";

		//切割后的影像路径
		std::string clip1 =syspath+"\\clip1.tif";
		std::string clip2 =syspath+"\\clip2.tif";

		//删除存在的临时文件
		_unlink(clip1.c_str());
		_unlink(clip2.c_str());

		double dcellx1,dcelly1,dcellx2,dcelly2;
		double dcellx,dcelly;

		pSrcRS->GetCellSize(&dcellx1,&dcelly1);
		pdestRS->GetCellSize(&dcellx2,&dcelly2);
		//选择分辨率最小作为基准
		dcellx =dcellx1>dcellx2?dcellx1:dcellx2;
		dcelly =dcelly1>dcelly2?dcelly1:dcelly2;

		if(!ImgClip(strSrc,clip1.c_str(),interExt,dcellx,dcelly))
		{
			return false;
		}
		if(!ImgClip(strDest,clip2.c_str(),interExt,dcellx,dcelly))
		{
			return false;
		}

		pSrcWp =CRasterWSFactory::GetInstance()->OpenFromFile(clip1.c_str());
		if(!pSrcWp)
		{
			return false;
		}
		//打开原文件
		pSrcRS =pSrcWp->OpenRasterDataset(clip1.c_str());
		if(!pSrcRS)
		{
			return false;
		}

		pDestWp =CRasterWSFactory::GetInstance()->OpenFromFile(clip2.c_str());
		if(!pDestWp)
		{
			return false;
		}
		//打开目标文件
		pdestRS =pDestWp->OpenRasterDataset(clip2.c_str());
		if(!pdestRS)
		{
			return false;
		}

	}

	//影像建立
	long lWidth,lHeight;
	GEOMETRY::geom::Envelope env;
	Geodatabase::RasFileInfo rasfileInfoDes;


	pSrcRS->GetSize(&lWidth,&lHeight);
	pSrcRS->GetExtent(&env);

	rasfileInfoDes.lWidth = lWidth;			//图像的宽度
	rasfileInfoDes.lHeight = lHeight;		//图像的高度
	rasfileInfoDes.lChannelNum = 1;	//图像的通道数
	rasfileInfoDes.lDataType = (long)Geodatabase::BDT_FLOAT;

	std::string path =strResult;

	path =path.substr(0,path.rfind('\\'));
	Geodatabase::IWorkspace *pdestWS =CRasterWSFactory::GetInstance()->OpenFolder(path.c_str());
	if(!pdestWS)
	{
		return false;
	}

	if(!pdestWS->CreateRasterDataset(strResult,&rasfileInfoDes))
	{
		return false;
	}
	Geodatabase::IRasterDatasetPtr rasDestDS =pdestWS->OpenRasterDataset(strResult,false);

	if(!rasDestDS)
	{
		return false;
	}

	rasDestDS->SetCoordinateExtent(env);
	rasDestDS->CreateBuffer();

	//计算每块的相关系数
	long startx,starty,endx,endy;
	long lBuffsize = 2*nsize+1;

	float cal;
	unsigned char *pbuffer =new unsigned char[lBuffsize*lBuffsize];

	float *pfbuffer1 =new float[lBuffsize*lBuffsize];
	float *pfbuffer2 =new float[lBuffsize*lBuffsize];
	double dmin1,dmin2,dmax1,dmax2;

	pSrcRS->GetBandMinMaxValue(1,&dmax1,&dmin1);
	pdestRS->GetBandMinMaxValue(1,&dmax2,&dmin2);


	for(int i=0; i<lHeight; i++)
	{
		starty = (i-nsize<0) ? 0 : i-nsize;
		endy = (i+nsize>lHeight-1) ? lHeight-1 : i+nsize;

		for(int j=0; j<lWidth; j++)
		{
			startx= (j-nsize<0) ? 0 : j-nsize;
			endx = (j+nsize>lWidth-1) ? lWidth-1 : j+nsize;

			//读取数据
			pSrcRS->DataReadBandNormalize(1,startx+1,starty+1,endx-startx+1,endy-starty+1,endx-startx+1,endy-starty+1,pbuffer,dmin1,dmax1);
			for(int k=0;k<((endx-startx+1)*(endy-starty+1));k++)
			{
				pfbuffer1[k] =pbuffer[k];
			}

			pdestRS->DataReadBandNormalize(1,startx+1,starty+1,endx-startx+1,endy-starty+1,endx-startx+1,endy-starty+1,pbuffer,dmin2,dmax2);
			for(int k=0;k<((endx-startx+1)*(endy-starty+1));k++)
			{
				pfbuffer2[k] =pbuffer[k];
			}

			//计算相关系数
			cal =CalCorrelation(pfbuffer1,pfbuffer2,(endx-startx+1)*(endy-starty+1));

			rasDestDS->PixelIO(1, j+1, i+1, &cal, false);
		}

		if(pProgress)
		{
			pProgress->UpdateProgress("",((double)i)/((double)lHeight));

		}
	}

	rasDestDS->DeleteBuffer();

	if(pProgress)
	{
		pProgress->UpdateProgress("",1.0);
		pProgress->Close();
	}

}

double CalCorrelation(float* pBase, float* pSamp, int nBlockLen)
{

	double dbSelfBase=0,dbSelfSamp=0;

	double dbCor=0;
	//均值
	double dbMeanBase=0,dbMeanSamp=0;

	int i,j;

	int size=nBlockLen;

	for(i=0;i<size;i++)
	{
		dbMeanBase += pBase[i];
		dbMeanSamp += pSamp[i];
	}
	dbMeanBase = dbMeanBase/size;
	dbMeanSamp = dbMeanSamp/size;

	for(i=0;i<size;i++)
	{
		dbSelfBase += (pBase[i] - dbMeanBase)*(pBase[i]  - dbMeanBase);
		dbSelfSamp += (pSamp[i] - dbMeanSamp)*(pSamp[i]  - dbMeanSamp);
		dbCor += (pBase[i] - dbMeanBase)*(pSamp[i]  - dbMeanSamp);
	}

	if((dbSelfBase * dbSelfSamp)<=0)
		return -1;
	if(dbCor==0)
		return dbCor;
	else 
		return(dbCor/sqrt(dbSelfBase * dbSelfSamp));
}
}