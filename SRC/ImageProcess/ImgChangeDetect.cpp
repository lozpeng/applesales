#include "stdafx.h"
#include "ImgChangeDetect.h"
#include "IWorkspace.h"
#include "RasterWSFactory.h"
#include "ImageClip.h"
#include "SysPath.h"
#include "ShapefileWorkspaceFactory.h"

using namespace std;

namespace ImageProcess
{

#define NUM 10

ImgChangeDetect::ImgChangeDetect(void)
{
}

ImgChangeDetect::~ImgChangeDetect(void)
{
}


bool ImgChangeDetect::RelativeDetect(const char *strSrc, const char *strDest, const char *strResult,int nsize, double threshold1, double threshold2, SYSTEM::IProgress *pProgress)
{
	using namespace GEOMETRY;
	typedef std::vector<GEOMETRY::geom::Coordinate> CoordVect;
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


	std::string path =strResult;
	//得到文件路径
	path =path.substr(0,path.rfind('\\'));

	Geodatabase::IWorkspace *pshpWS =CShapefileWorkspaceFactory::GetInstance()->OpenFromFile(strResult);
	if(!pshpWS)
	{
		return false;
	}


	Geodatabase::FeatureClassDef fdef;
	fdef.hasz =false;

	fdef.lshptype = GEOMETRY::geom::GEOS_POLYGON;
	
	Geodatabase::CField *pField =new Geodatabase::CField();
	pField->SetType(Geodatabase::FTYPE_LONG);
	pField->SetName("ID");
	pField->SetLength(10);
	fdef.FieldsDef.push_back(Geodatabase::CFieldPtr(pField));

	//创建结果矢量
	Geodatabase::IFeatureClassPtr pFeatureClass =pshpWS->CreateFeatureClass(strResult,fdef);

	if(!pFeatureClass)
	{
		return false;
	}

	//建立一个空的多边形要素
	GEOMETRY::geom::Geometry* pGeometry =NULL;
    Coordinate coord;
	
	//开始编辑
	pshpWS->StartEdit();
	pshpWS->StartEditOperation();

	Geodatabase::CFeaturePtr pFeature;


	long lwidth,lheight;
	pSrcRS->GetSize(&lwidth,&lheight);
	//计算每块的相关系数
    long startx,starty,endx,endy;
	long i;
	unsigned char *pbuffer =new unsigned char[nsize*nsize];
	float *pfbuffer1 =new float[nsize*nsize];
	float *pfbuffer2 =new float[nsize*nsize];
	double dmin1,dmin2,dmax1,dmax2;
	pSrcRS->GetBandMinMaxValue(1,&dmax1,&dmin1);
	pdestRS->GetBandMinMaxValue(1,&dmax2,&dmin2);
	double cal;
	long lprocessnum =(lwidth/nsize+1)*(lheight/nsize+1);
	long lcurProcess=0;
	for(starty=0;starty<lheight;)
	{

		endy =(starty+nsize-1<lheight)?starty+nsize-1:(lheight-1);
		for(startx=0;startx<lwidth;)
		{
			endx =(startx+nsize-1<lwidth)?startx+nsize-1:(lwidth-1);
            
			//读取数据
			pSrcRS->DataReadBandNormalize(1,startx+1,starty+1,endx-startx+1,endy-starty+1,endx-startx+1,endy-starty+1,pbuffer,dmin1,dmax1);

			for(i=0;i<((endx-startx+1)*(endy-starty+1));i++)
			{
				pfbuffer1[i] =pbuffer[i];
			}
			pdestRS->DataReadBandNormalize(1,startx+1,starty+1,endx-startx+1,endy-starty+1,endx-startx+1,endy-starty+1,pbuffer,dmin2,dmax2);
            
			for(i=0;i<((endx-startx+1)*(endy-starty+1));i++)
			{
				pfbuffer2[i] =pbuffer[i];
			}

			//计算相关系数
            cal =CalCorrelation(pfbuffer1,pfbuffer2,(endx-startx+1)*(endy-starty+1));

			if(cal<threshold2 && cal>threshold1)
			{
				//记录结果
                pGeometry =(Geometry*)GeometryFactory::getDefaultInstance()->createPolygon();

				CoordVect *pcoords =new CoordVect(5);
				//左上角点
				pSrcRS->PixelToWorld(startx+1,starty+1,&coord.x,&coord.y);
				(*pcoords)[0] =coord;
				//右上角点
				pSrcRS->PixelToWorld(endx+1,starty+1,&coord.x,&coord.y);
				(*pcoords)[1] =coord;
				//右下角点
				pSrcRS->PixelToWorld(endx+1,endy+1,&coord.x,&coord.y);
				(*pcoords)[2] =coord;
				//左下角点
				pSrcRS->PixelToWorld(startx+1,endy+1,&coord.x,&coord.y);
				(*pcoords)[3] =coord;

				(*pcoords)[4] =(*pcoords)[0];

				CoordinateSequence *coords = GeometryFactory::getDefaultInstance()->getCoordinateSequenceFactory()->create(pcoords);
				LinearRing *pring = GeometryFactory::getDefaultInstance()->createLinearRing(coords);

				((GEOMETRY::geom::Polygon*)pGeometry)->AddGeometry((Geometry*)pring);
				//产生一个新的要素
				pFeature =pFeatureClass->CreateFeature();
				pFeature->SetShape( pGeometry);

				//提交要素
				pFeatureClass->AddFeature(pFeature.get());

			}
			startx =endx+1;

			lcurProcess++;
			if(pProgress)
			{
				pProgress->UpdateProgress("",((double)lcurProcess)/((double)lprocessnum));
				
			}

		}
		starty =endy+1;
	}

	pshpWS->StopEditOperation();
	pshpWS->StopEdit(true);

	delete []pbuffer;
	delete []pfbuffer1;
	delete []pfbuffer2;

	if(pProgress)
	{
		pProgress->UpdateProgress("",1.0);
		pProgress->Close();
	}


    return true;
}


/**********************************************************************************
* CalCorrelation() 计算两块Float数组的相关系数
* 参数：
* pBase: 相关数据
* pSamp: 相关数据
* nBlockLen： 相关系数模板大小
* 返回 :相关系数
**********************************************************************************/
double  ImgChangeDetect::CalCorrelation(float* pBase, float* pSamp, int nBlockLen)
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
	if(dbCor==0)
		return dbCor;
	else 
		return(dbCor/sqrt(dbSelfBase * dbSelfSamp));
}

float ImgChangeDetect::DamGradeCal(float* src, float* dest, long lWidth, long lHeight, float thres)
{
	long size = 21;
	long lCountX = lWidth / size;
	long lCountY = lHeight / size;

	float* buff1 = new float[size*size];
	float* buff2 = new float[size*size];

	long lCount=0;
	for(int i=0; i<lCountY; i++)
	{
		for(int j=0; j<lCountX; j++)
		{
			//
			for(int k=0; k<size; k++)
			{
				for(int l=0; l<size; l++)
				{
					buff1[k*size+l] = src[(i*size+k)*lWidth+(j*size+l)];
					buff2[k*size+l] = dest[(i*size+k)*lWidth+(j*size+l)];
				}
			}

			//
			float corre = CalCorrelation(buff1, buff2, size*size);
			if(corre > thres)
			{
				lCount++;
			}
		}
	}

	delete []buff1;
	delete []buff2;

	return (1.0*lCount) /(lCountY*lCountX);
}

bool ImgChangeDetect::TargetDetect(const char *strSrc,const char *strDest,const char *strTarget,int nsize,double grade1,double grade2, double thres, SYSTEM::IProgress *pProgress)
{
	//打开原文件
	Geodatabase::IWorkspace *pSrcWp =CRasterWSFactory::GetInstance()->OpenFromFile(strSrc);
	if(!pSrcWp)
	{
		return false;
	}

	Geodatabase::IRasterDatasetPtr pSrcRS =pSrcWp->OpenRasterDataset(strSrc);
	if(!pSrcRS)
	{
		return false;
	}
	long lSrcWidth,lSrcHeight;
	pSrcRS->GetSize(&lSrcWidth, &lSrcHeight);


	//打开目标文件
	Geodatabase::IWorkspace *pDestWp =CRasterWSFactory::GetInstance()->OpenFromFile(strSrc);
	if(!pDestWp)
	{
		return false;
	}

	Geodatabase::IRasterDatasetPtr pDestRS =pDestWp->OpenRasterDataset(strDest);
	if(!pDestRS)
	{
		return false;
	}
	long lDestWidth,lDestHeight;
	pDestRS->GetSize(&lDestWidth, &lDestHeight);

	//打开矢量文件
	Geodatabase::IWorkspace *pshpWS =CShapefileWorkspaceFactory::GetInstance()->OpenFromFile(strTarget);
	if(!pshpWS)
	{
		return false;
	}

	Geodatabase::IFeatureClassPtr pFeatureClass =pshpWS->OpenFeatureClass(strTarget);

	if(!pFeatureClass)
	{
		return false;
	}

	pshpWS->StartEdit();
	pshpWS->StartEditOperation();

	long lIndex = pFeatureClass->FindField("DamGrade");
	long lBuffsize = (2*nsize+1);
	long lSrcCol,lSrcRow,lDestCol,lDestRow;
	char csGrade[24];

	unsigned char *pbuffer =new unsigned char[lBuffsize*lBuffsize];
	float *pfbuffer1 =new float[lBuffsize*lBuffsize];
	float *pfbuffer2 =new float[lBuffsize*lBuffsize];

	//建立进度条
	if(pProgress)
	{
		pProgress->Create("处理中",SYSTEM::IProgress::Percent,100);
		pProgress->UpdateProgress("",0.01);

	}

	long lFeatrueCount = pFeatureClass->FeatureCount();
	for(int i=0; i<lFeatrueCount; i++)
	{
		//
		Geodatabase::CFeaturePtr pFeature = pFeatureClass->GetFeature(i+1);

		//
		GEOMETRY::geom::Geometry* pshape = pFeature->GetShape();
		const GEOMETRY::geom::Coordinate* coor = pshape->getCoordinate();
		Geodatabase::FieldValue& fv = pFeature->GetValue(lIndex);

		//
		pSrcRS->WorldToPixel(coor->x, coor->y, &lSrcCol, &lSrcRow);

		if((lSrcCol-nsize)<0 || (lSrcCol+nsize)>=lSrcWidth)
			continue;

		if((lSrcRow-nsize)<0 || (lSrcRow+nsize)>=lSrcHeight)
			continue;

		pSrcRS->DataReadBand(1, lSrcCol-nsize+1, lSrcRow-nsize+1, lBuffsize, lBuffsize, lBuffsize, lBuffsize, pbuffer);
		for(int k=0;k<lBuffsize*lBuffsize;k++)
		{
			pfbuffer1[k] =pbuffer[k];
		}

		//
		pDestRS->WorldToPixel(coor->x, coor->y, &lDestCol, &lDestRow);

		if((lDestCol-nsize)<0 || (lDestCol+nsize)>=lDestWidth)
			continue;

		if((lDestRow-nsize)<0 || (lDestRow+nsize)>=lDestHeight)
			continue;

		pDestRS->DataReadBand(1, lDestCol-nsize+1, lDestRow-nsize+1, lBuffsize, lBuffsize, lBuffsize, lBuffsize, pbuffer);
		for(int k=0;k<lBuffsize*lBuffsize;k++)
		{
			pfbuffer2[k] =pbuffer[k];
		}

		float grade = DamGradeCal(pfbuffer1, pfbuffer2, lBuffsize, lBuffsize, thres);
		long lGrade = 0;

		if(grade < grade1)
		{
			lGrade = 1;
		}
		else if(grade > grade2)
		{
			lGrade = 3;
		}
		else
			lGrade = 2;

		sprintf(csGrade,"%d",lGrade);
		fv.SetString(csGrade);

		pFeature->Update();

		if(pProgress)
		{
			pProgress->UpdateProgress("",((double)i)/((double)lFeatrueCount));

		}
	}

	if(pProgress)
	{
		pProgress->UpdateProgress("",1.0);
		pProgress->Close();
	}

	delete []pbuffer;
	delete []pfbuffer1;
	delete []pfbuffer2;

	pshpWS->StopEditOperation();
	pshpWS->StopEdit();
}


}