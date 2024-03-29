#include "stdafx.h"
#include "ImgChangeDetect.h"
#include "IWorkspace.h"
#include "RasterWSFactory.h"
#include "ImageClip.h"
#include "SysPath.h"
#include "ShapefileWorkspaceFactory.h"
//#include <xcomplex>


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

bool ImgChangeDetect::TargetDetect(const char *strSrc,const char *strDest,const char *strTarget, const char* strResult, int nsize,double grade1,double grade2, double thres, SYSTEM::IProgress *pProgress)
{
	using namespace GEOMETRY;
	typedef std::vector<GEOMETRY::geom::Coordinate> CoordVect;
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
	double lCellSizeX,lCellSizeY;
	pSrcRS->GetSize(&lSrcWidth, &lSrcHeight);
	pSrcRS->GetCellSize(&lCellSizeX, &lCellSizeY);

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

	long lIndex = pFeatureClass->FindField("DamGrade");
	if(lIndex == -1)
	{
		return false;
	}

	//
	std::string path =strResult;
	path =path.substr(0,path.rfind('\\'));

	Geodatabase::IWorkspace *pshpResultWS =CShapefileWorkspaceFactory::GetInstance()->OpenFromFile(strResult);
	if(!pshpResultWS)
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


	Geodatabase::CField *pField2 =new Geodatabase::CField();
	pField2->SetType(Geodatabase::FTYPE_STRING);
	pField2->SetName("DameGrade");
	pField2->SetLength(1);
	fdef.FieldsDef.push_back(Geodatabase::CFieldPtr(pField2));

	//创建结果矢量
	Geodatabase::IFeatureClassPtr pFeatureResultClass =pshpResultWS->CreateFeatureClass(strResult,fdef);

	if(!pFeatureResultClass)
	{
		return false;
	}

	//
	long lBuffsize = (2*nsize+1);
	long lSrcCol,lSrcRow,lDestCol,lDestRow;
	char csGrade[24];

	unsigned char *pbuffer =new unsigned char[lBuffsize*lBuffsize];
	float *pfbuffer1 =new float[lBuffsize*lBuffsize];
	float *pfbuffer2 =new float[lBuffsize*lBuffsize];

	//
	pshpWS->StartEdit();
	pshpWS->StartEditOperation();

	pshpResultWS->StartEdit();
	pshpResultWS->StartEditOperation();
	//建立进度条
	if(pProgress)
	{
		pProgress->Create("处理中",SYSTEM::IProgress::Percent,100);
		pProgress->UpdateProgress("",0.01);

	}

	long lFeatrueCount = pFeatureClass->FeatureCount();
	long lCount = 0;
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
		lCount++;

		//
		GEOMETRY::geom::Geometry* pGeometry =NULL;
		pGeometry =(Geometry*)GeometryFactory::getDefaultInstance()->createPolygon();
		CoordVect *pcoords =new CoordVect(5);
		//左上角点
		(*pcoords)[0].x =coor->x - nsize*lCellSizeX;
		(*pcoords)[0].y =coor->y + nsize*lCellSizeY;
		//右上角点
		(*pcoords)[1].x =coor->x + nsize*lCellSizeX;
		(*pcoords)[1].y =coor->y + nsize*lCellSizeY;
		//右下角点
		(*pcoords)[2].x =coor->x + nsize*lCellSizeX;
		(*pcoords)[2].y =coor->y - nsize*lCellSizeY;
		//左下角点
		(*pcoords)[3].x =coor->x - nsize*lCellSizeX;
		(*pcoords)[3].y =coor->y - nsize*lCellSizeY;

		(*pcoords)[4] =(*pcoords)[0];

		CoordinateSequence *coords = GeometryFactory::getDefaultInstance()->getCoordinateSequenceFactory()->create(pcoords);
		LinearRing *pring = GeometryFactory::getDefaultInstance()->createLinearRing(coords);
		((GEOMETRY::geom::Polygon*)pGeometry)->AddGeometry((Geometry*)pring);

		//产生一个新的要素
		Geodatabase::CFeaturePtr pFeature2 =pFeatureResultClass->CreateFeature();
		Geodatabase::FieldValue& fv2 = pFeature2->GetValue(2);
		Geodatabase::FieldValue& fv3 = pFeature2->GetValue(1);

		pFeature2->SetShape( pGeometry);
		fv2.SetString(csGrade);
		fv3.SetInt(lCount);
		pFeatureResultClass->AddFeature(pFeature2.get());


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
	pshpWS->StopEdit(true);

	pshpResultWS->StopEditOperation();
	pshpResultWS->StopEdit(true);

	return true;
}


bool ImgChangeDetect::CalculateGLCM(BYTE* ptr, int width, int height, float *entropy, float *moment, float *contrast, float *correlation, float *homogeneity)
{


	const int d=1; //像素的距离
	//灰度降级为0~8级
	BYTE* ptr2 = new BYTE[width*height];

	for(int i=0; i<width*height; i++)
	{
		ptr2[i] = ptr[i] / 32;

		if(ptr2[i] == 8)
			ptr2[i] = 7;
	}
	//创建四个方向的数组并初始化为0
	double GLCM_0[8][8]={0};
	double GLCM_45[8][8]={0};
	double GLCM_90[8][8]={0};
	double GLCM_135[8][8]={0};
	//开始遍历并生成共生矩阵  忽略边界
	for (int j=d;j<height;j++)
	{
		for (int i=d;i<width-d;i++)
		{
			int x=(int)(ptr2[j*width+i]);
			int y0=(int)(ptr2[j*width+i+d]);
			int y45=(int)(ptr2[(j-d)*width+i+d]);
			int y90=(int)(ptr2[(j-d)*width+i]);
			int y135=(int)(ptr2[(j-d)*width+i-d]);

			GLCM_0[x][y0]++;
			GLCM_45[x][y45]++;
			GLCM_90[x][y90]++;
			GLCM_135[x][y135]++;
		}
	}
	//开始归一化
	double sum=0;
	for (int i=0;i<8;i++)
	{
		for (int j=0;j<8;j++)
		{
			sum=sum+GLCM_0[i][j];
		}
	}
	for (int i=0; i<8;i++)
	{
		for (int j=0;j<8;j++)
		{
			GLCM_0[i][j]=GLCM_0[i][j]/sum;
			GLCM_45[i][j]=GLCM_45[i][j]/sum;
			GLCM_90[i][j]=GLCM_90[i][j]/sum;
			GLCM_135[i][j]=GLCM_135[i][j]/sum;
		}
	}  
	//计算四个方向的灰度共生矩阵的熵
	double entropy1=0,entropy2=0,entropy3=0,entropy4=0;
	double minV=1.0/sum;
	for(int i=0;i<8;i++)
	{
		for (int j=0;j<8;j++)
		{
			//entropy1=entropy1+GLCM_0[i][j]*std::log(GLCM_0[i][j]);
			//entropy2=entropy2+GLCM_45[i][j]*std::log(GLCM_45[i][j]);
			//entropy3=entropy3+GLCM_90[i][j]*std::log(GLCM_90[i][j]);
			//entropy4=entropy4+GLCM_135[i][j]*std::log(GLCM_135[i][j]);
			entropy1=entropy1+GLCM_0[i][j]*(GLCM_0[i][j]<minV? 0 : log(GLCM_0[i][j]));
			entropy2=entropy2+GLCM_45[i][j]*(GLCM_45[i][j]<minV? 0 : log(GLCM_45[i][j]));
			entropy3=entropy3+GLCM_90[i][j]*(GLCM_90[i][j]<minV? 0 : log(GLCM_90[i][j]));
			entropy4=entropy4+GLCM_135[i][j]*(GLCM_135[i][j]<minV? 0 : log(GLCM_135[i][j]));
		}
	}
	entropy[0]=-(float)entropy1;
	entropy[1]=-(float)entropy2;
	entropy[2]=-(float)entropy3;
	entropy[3]=-(float)entropy4;
	//计算四个方向的角二阶矩moment
	double moment1=0,moment2=0,moment3=0,moment4=0;
	for(int i=0;i<8;i++)
	{
		for (int j=0;j<8;j++)
		{
			moment1=moment1+GLCM_0[i][j]*GLCM_0[i][j];
			moment2=moment2+GLCM_45[i][j]*GLCM_45[i][j];
			moment3=moment3+GLCM_90[i][j]*GLCM_90[i][j];
			moment4=moment4+GLCM_135[i][j]*GLCM_135[i][j];
		}
	}
	moment[0]=(float)moment1;
	moment[1]=(float)moment2;
	moment[2]=(float)moment3;
	moment[3]=(float)moment4;
	//计算四个方向的灰度共生矩阵的惯性矩
	double contrast1=0,contrast2=0,contrast3=0,contrast4=0;
	for(int i=0;i<8;i++)
	{
		for (int j=0;j<8;j++)
		{
			contrast1=contrast1+GLCM_0[i][j]*(i-j)*(i-j);
			contrast2=contrast2+GLCM_45[i][j]*(i-j)*(i-j);
			contrast3=contrast3+GLCM_90[i][j]*(i-j)*(i-j);
			contrast4=contrast4+GLCM_135[i][j]*(i-j)*(i-j);
		}
	}
	contrast[0]=(float)contrast1;
	contrast[1]=(float)contrast2;
	contrast[2]=(float)contrast3;
	contrast[3]=(float)contrast4;
	//计算四个方向的灰度共生矩阵的相关性
	double ux0=0,uy0=0,theta2X0=0,theta2Y0=0;	
	double ux45=0,uy45=0,theta2X45=0,theta2Y45=0;	
	double ux90=0,uy90=0,theta2X90=0,theta2Y90=0;	
	double ux135=0,uy135=0,theta2X135=0,theta2Y135=0;	
	double rowSum0=0,rowSum45=0,rowSum90=0,rowSum135=0;
	for(int i=0;i<8;i++)
	{
		rowSum0=0;rowSum45=0;rowSum90=0;rowSum135=0;
		for (int j=0;j<8;j++)  
		{
			rowSum0=rowSum0+GLCM_0[i][j];
			rowSum45=rowSum45+GLCM_45[i][j];
			rowSum90=rowSum90+GLCM_90[i][j];
			rowSum135=rowSum135+GLCM_135[i][j];
		}
		ux0=ux0+i*rowSum0;ux45=ux45+i*rowSum45;ux90=ux90+i*rowSum90;ux135=ux135+i*rowSum135;
	}
	for(int j=0;j<8;j++)
	{
		rowSum0=0;rowSum45=0;rowSum90=0;rowSum135=0;
		for (int i=0;i<8;i++)
		{
			rowSum0=rowSum0+GLCM_0[i][j];
			rowSum45=rowSum45+GLCM_45[i][j];
			rowSum90=rowSum90+GLCM_90[i][j];
			rowSum135=rowSum135+GLCM_135[i][j];
		}
		uy0=uy0+j*rowSum0;uy45=uy45+j*rowSum45;uy90=uy90+j*rowSum90;uy135=uy135+j*rowSum135;
	}
	for(int i=0;i<8;i++)
	{
		rowSum0=0;rowSum45=0;rowSum90=0;rowSum135=0;
		for (int j=0;j<8;j++)
		{
			rowSum0=rowSum0+GLCM_0[i][j];
			rowSum45=rowSum45+GLCM_45[i][j];
			rowSum90=rowSum90+GLCM_90[i][j];
			rowSum135=rowSum135+GLCM_135[i][j];
		}
		theta2X0=theta2X0+(i-ux0)*(i-ux0)*rowSum0;
		theta2X45=theta2X45+(i-ux45)*(i-ux45)*rowSum45;
		theta2X90=theta2X90+(i-ux90)*(i-ux90)*rowSum90;
		theta2X135=theta2X135+(i-ux135)*(i-ux135)*rowSum135;
	}
	for(int j=0;j<8;j++)
	{
		rowSum0=0;rowSum45=0;rowSum90=0;rowSum135=0;
		for (int i=0;i<8;i++)
		{  
			rowSum0=rowSum0+GLCM_0[i][j];
			rowSum45=rowSum45+GLCM_45[i][j];
			rowSum90=rowSum90+GLCM_90[i][j];
			rowSum135=rowSum135+GLCM_135[i][j];
		}
		theta2Y0=theta2Y0+(j-uy0)*(j-uy0)*rowSum0;
		theta2Y45=theta2Y45+(j-uy45)*(j-uy45)*rowSum45;
		theta2Y90=theta2Y90+(j-uy90)*(j-uy90)*rowSum90;
		theta2Y135=theta2Y135+(j-uy135)*(j-uy135)*rowSum135;
	}
	double correlation1=0,correlation2=0,correlation3=0,correlation4=0;
	for(int i=0;i<8;i++)
	{
		for (int j=0;j<8;j++)
		{
			correlation1=correlation1+GLCM_0[i][j]*i*j;
			correlation2=correlation2+GLCM_45[i][j]*i*j;
			correlation3=correlation3+GLCM_90[i][j]*i*j;
			correlation4=correlation4+GLCM_135[i][j]*i*j;
		}
	}
	correlation[0]=(float)((correlation1-ux0*uy0)/(theta2X0*theta2Y0));
	correlation[1]=(float)((correlation2-ux45*uy45)/(theta2X45*theta2Y45));
	correlation[2]=(float)((correlation3-ux90*uy90)/(theta2X90*theta2Y90));
	correlation[3]=(float)((correlation4-ux135*uy135)/(theta2X135*theta2Y135));
	//计算四个方向的灰度共生矩阵的局部均匀性
	double homogeneity1=0,homogeneity2=0,homogeneity3=0,homogeneity4=0;
	for(int i=0;i<8;i++)
	{
		for (int j=0;j<8;j++)
		{
			homogeneity1=homogeneity1+GLCM_0[i][j]/(1+(i-j)*(i-j));
			homogeneity2=homogeneity2+GLCM_45[i][j]/(1+(i-j)*(i-j));
			homogeneity3=homogeneity3+GLCM_90[i][j]/(1+(i-j)*(i-j));
			homogeneity4=homogeneity4+GLCM_135[i][j]/(1+(i-j)*(i-j));
		}
	}
	homogeneity[0]=-(float)homogeneity1;
	homogeneity[1]=-(float)homogeneity2;
	homogeneity[2]=-(float)homogeneity3;
	homogeneity[3]=-(float)homogeneity4;

	delete []ptr2;
	return true;
}

float ImgChangeDetect::DamGradeCal2(BYTE* src, BYTE* dest, long lWidth, long lHeight, float thres, int ot)
{
	long size = 32;
	long lCountX = lWidth / size;
	long lCountY = lHeight / size;

	BYTE* buff1 = new BYTE[size*size];
	BYTE* buff2 = new BYTE[size*size];

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
			float ent[4], mom[4], con[4], cor[4], hom[4];
			float ent2[4], mom2[4], con2[4], cor2[4], hom2[4];

			CalculateGLCM(buff1, size, size, ent, mom, con, cor, hom);
			CalculateGLCM(buff2, size, size, ent2, mom2, con2, cor2, hom2);

			double t1,t2,t3,corr;

			t1 = ent[ot]*ent2[ot]+mom[ot]*mom2[ot]+con[ot]*con2[ot]+cor[ot]*cor2[ot]+hom[ot]*hom2[ot];
			t2 = ent[ot]*ent[ot]+mom[ot]*mom[ot]+con[ot]*con[ot]+cor[ot]*cor[ot]+hom[ot]*hom[ot];t2=sqrt(t2);
			t3 = ent2[ot]*ent2[ot]+mom2[ot]*mom2[ot]+con2[ot]*con2[ot]+cor2[ot]*cor2[ot]+hom2[ot]*hom2[ot];t3=sqrt(t3);

			if( t2<1.0e-5 || t1<1.0e-5)
				corr =0.0;
			else
				corr = t1/(t2*t3);

			if(corr>0.96)
				lCount++;

		}
	}

	delete []buff1;
	delete []buff2;

	return (1.0*lCount) /(lCountY*lCountX);
}


bool ImgChangeDetect::TargetDetect2(const char *strSrc,const char *strDest,const char *strTarget, const char* strResult, int nsize,double grade1,double grade2, double thres, SYSTEM::IProgress *pProgress)
{
	using namespace GEOMETRY;
	typedef std::vector<GEOMETRY::geom::Coordinate> CoordVect;
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
	double lCellSizeX,lCellSizeY;
	pSrcRS->GetSize(&lSrcWidth, &lSrcHeight);
	pSrcRS->GetCellSize(&lCellSizeX, &lCellSizeY);

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

	long lIndex = pFeatureClass->FindField("DamGrade");
	if(lIndex == -1)
	{
		return false;
	}

	//
	std::string path =strResult;
	path =path.substr(0,path.rfind('\\'));

	Geodatabase::IWorkspace *pshpResultWS =CShapefileWorkspaceFactory::GetInstance()->OpenFromFile(strResult);
	if(!pshpResultWS)
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


	Geodatabase::CField *pField2 =new Geodatabase::CField();
	pField2->SetType(Geodatabase::FTYPE_STRING);
	pField2->SetName("DameGrade");
	pField2->SetLength(1);
	fdef.FieldsDef.push_back(Geodatabase::CFieldPtr(pField2));

	//创建结果矢量
	Geodatabase::IFeatureClassPtr pFeatureResultClass =pshpResultWS->CreateFeatureClass(strResult,fdef);

	if(!pFeatureResultClass)
	{
		return false;
	}

	//
	long lBuffsize = (2*nsize+1);
	long lSrcCol,lSrcRow,lDestCol,lDestRow;
	char csGrade[24];

	unsigned char *pbuffer1 =new unsigned char[lBuffsize*lBuffsize];
	unsigned char *pbuffer2 =new unsigned char[lBuffsize*lBuffsize];


	//
	pshpWS->StartEdit();
	pshpWS->StartEditOperation();

	pshpResultWS->StartEdit();
	pshpResultWS->StartEditOperation();
	//建立进度条
	if(pProgress)
	{
		pProgress->Create("处理中",SYSTEM::IProgress::Percent,100);
		pProgress->UpdateProgress("",0.01);

	}

	long lFeatrueCount = pFeatureClass->FeatureCount();
	long lCount = 0;
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

		pSrcRS->DataReadBand(1, lSrcCol-nsize+1, lSrcRow-nsize+1, lBuffsize, lBuffsize, lBuffsize, lBuffsize, pbuffer1);

		//
		pDestRS->WorldToPixel(coor->x, coor->y, &lDestCol, &lDestRow);

		if((lDestCol-nsize)<0 || (lDestCol+nsize)>=lDestWidth)
			continue;

		if((lDestRow-nsize)<0 || (lDestRow+nsize)>=lDestHeight)
			continue;

		pDestRS->DataReadBand(1, lDestCol-nsize+1, lDestRow-nsize+1, lBuffsize, lBuffsize, lBuffsize, lBuffsize, pbuffer2);

		float grade = DamGradeCal2(pbuffer1, pbuffer2, lBuffsize, lBuffsize, thres, 0);
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
		lCount++;

		//
		GEOMETRY::geom::Geometry* pGeometry =NULL;
		pGeometry =(Geometry*)GeometryFactory::getDefaultInstance()->createPolygon();
		CoordVect *pcoords =new CoordVect(5);
		//左上角点
		(*pcoords)[0].x =coor->x - nsize*lCellSizeX;
		(*pcoords)[0].y =coor->y + nsize*lCellSizeY;
		//右上角点
		(*pcoords)[1].x =coor->x + nsize*lCellSizeX;
		(*pcoords)[1].y =coor->y + nsize*lCellSizeY;
		//右下角点
		(*pcoords)[2].x =coor->x + nsize*lCellSizeX;
		(*pcoords)[2].y =coor->y - nsize*lCellSizeY;
		//左下角点
		(*pcoords)[3].x =coor->x - nsize*lCellSizeX;
		(*pcoords)[3].y =coor->y - nsize*lCellSizeY;

		(*pcoords)[4] =(*pcoords)[0];

		CoordinateSequence *coords = GeometryFactory::getDefaultInstance()->getCoordinateSequenceFactory()->create(pcoords);
		LinearRing *pring = GeometryFactory::getDefaultInstance()->createLinearRing(coords);
		((GEOMETRY::geom::Polygon*)pGeometry)->AddGeometry((Geometry*)pring);

		//产生一个新的要素
		Geodatabase::CFeaturePtr pFeature2 =pFeatureResultClass->CreateFeature();
		Geodatabase::FieldValue& fv2 = pFeature2->GetValue(2);
		Geodatabase::FieldValue& fv3 = pFeature2->GetValue(1);

		pFeature2->SetShape( pGeometry);
		fv2.SetString(csGrade);
		fv3.SetInt(lCount);
		pFeatureResultClass->AddFeature(pFeature2.get());


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

	delete []pbuffer1;
	delete []pbuffer2;

	pshpWS->StopEditOperation();
	pshpWS->StopEdit(true);

	pshpResultWS->StopEditOperation();
	pshpResultWS->StopEdit(true);

	return true;
}

}