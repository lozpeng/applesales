#include "stdafx.h"
#include "ImgChangeDetect.h"
#include "IWorkspace.h"
#include "RasterWSFactory.h"
#include "ImageClip.h"
#include "SysPath.h"
using namespace std;

namespace ImageProcess
{

	#define NUM 10

ImgChangeDetect::ImgChangeDetect(void)
: m_nAverGrayDiff(0)
{
}

ImgChangeDetect::~ImgChangeDetect(void)
{
}


//相关系数法，图像检测，LQ
void ImgChangeDetect::ImgDetectCorrelation_Index2(const char* ImageFileName_Src, const char* ImageFileName_Dest, const char* ImageFileName_Res, float Threshold)
{
	//long     lWidth, lHeight;
	//long     lDataType1,lDataType2;
	//double	 dblCellX,dblCellY;
	//double	 dblCellX1,dblCellY1;
	//double	 dblCellX2,dblCellY2;
	//STExtent stExtent1,stExtent2,stExtent;

	////
	//BYTE byValue = 0;
	//unsigned short usValue = 0;
	//short sValue = 0;
 //	float fValue = 0.0;

	////多光谱影像
 //   CRasterDS rasMulDS;
	//rasMulDS.Open(ImageFileName_Src);
	//rasMulDS.GetCellSize(&dblCellX1,&dblCellY1);
	//rasMulDS.GetBandDataType(1, &lDataType1);
	//rasMulDS.GetCoordinateExtent(&stExtent1);

	////全色影像
 //   CRasterDS rasPanDS;
	//rasPanDS.Open(ImageFileName_Dest);
	//rasPanDS.GetCellSize(&dblCellX2,&dblCellY2);
	//rasPanDS.GetBandDataType(1, &lDataType2);
	//rasPanDS.GetCoordinateExtent(&stExtent2);

	//rasMulDS.Close();
	//rasPanDS.Close();

	//if(dblCellX1>dblCellX2)
	//{
	//	dblCellX = dblCellX2;
	//	dblCellY = dblCellY2;
	//}
	//else
	//{
	//	dblCellX = dblCellX1;
	//	dblCellY = dblCellY1;
	//}

	//if(!GeoExtentSect(stExtent1, stExtent2, &stExtent))
	//	return;

	//
	////创建中间结果文件
	//char* strImagePanWave;
	//char* strImageSrc;
	//char* strImageDest;
	//long lBandIndex=1;
	//long lBandNum=1;

	//::CreateDirectory("c:\\tempDirec_ImgDectect",NULL);
	//strImageSrc = "c:\\tempDirec_ImgDectect\\ImageSrc.tif";
	//strImageDest = "c:\\tempDirec_ImgDectect\\ImageDest.tif";

	//ImgClip(ImageFileName_Src,strImageSrc,stExtent,dblCellX,dblCellY,1,&lBandIndex,lBandNum);
	//ImgClip(ImageFileName_Dest,strImageDest,stExtent,dblCellX,dblCellY,1,&lBandIndex,lBandNum);

	//ImgDetectCorrelation_Index(strImageSrc,strImageDest,ImageFileName_Res,Threshold);

	////清除中间结果文件
	//::DeleteFile("c:\\tempDirec_ImgDectect\\ImageSrc.tif");
	//::DeleteFile("c:\\tempDirec_ImgDectect\\ImageDest.tif");
	//::RemoveDirectory("c:\\tempDirec_ImgDectect");
}

//相关系数法，图像检测，LQ
void ImgChangeDetect::ImgDetectCorrelation_Index(const char* ImageFileName_Src, const char* ImageFileName_Dest, const char* ImageFileName_Res, float Threshold)
{
	//if((strcmp(ImageFileName_Src,"")==0)||(strcmp(ImageFileName_Dest,"")==0))
	//	return;

	//bool        Flag=false;
	//int		    i, j, m, n;
	//int		    ResultFlag[100];
	//long		lWidth_temp, lHeight_temp;
	//long		lChannelCount_temp;
	//double		Block_Similar[100];
	//CRasterDS	rasSrcDS_temp;
	//
	////初始化各个数组
	//for(i=0; i<NUM*NUM; i++)
	//{
	//	Block_Similar[i] = 0.0f;
	//	ResultFlag[i] = 0;
	//}

	//
	////读取检测原文件
	//rasSrcDS.Open(ImageFileName_Src);
	//rasSrcDS.CreateBuffer();
	//rasSrcDS.GetSize(&lWidth, &lHeight);
	//rasSrcDS.GetBandCount(&lChannelCount);

	////读取检测目标文件
	//rasSrcDS_temp.Open(ImageFileName_Dest);
	//rasSrcDS_temp.CreateBuffer();
	//rasSrcDS_temp.GetSize(&lWidth_temp, &lHeight_temp);
	//rasSrcDS_temp.GetBandCount(&lChannelCount_temp);

	////判断两幅图象规格（长，宽，波段）是否一致，若不一致则退出程序
	//if((lWidth!=lWidth_temp) || (lHeight!=lHeight_temp) || (lChannelCount_temp!=lChannelCount))
	//{
	//	return;
	//}

	//int 	 Index_Col, Index_Row;
	//int      lWidth_N,lHeight_N;

	//lWidth_N  = lWidth/NUM;
	//lHeight_N = lHeight/NUM;
	////计算图像分块的特征向量

	//HPROGRESS hProgress;
	//ProgressCreate( &hProgress,csProCaption,TRUE,FALSE );
	//ProgressBegin( hProgress,PROGRESS_MODE_PERCENT, NUM*NUM);
	//ProgressSetStepTitle( hProgress, "一级检测");
	//ProgressUpdate( hProgress,FALSE );

	//for(i=0; i<NUM*NUM; i++)
	//{
	//	ProgressUpdate( hProgress,FALSE );

	//	unsigned char byValue=0;
	//	
	//	unsigned char *temp1 = new unsigned char[lWidth_N*lHeight_N];
	//	if(temp1 == NULL)
	//	{
	//		return ;
	//	}
	//	unsigned char *temp2 = new unsigned char[lWidth_N*lHeight_N];
	//	if(temp2 == NULL)
	//	{
	//		return ;
	//	}

	//	Index_Col = i/NUM;
	//	Index_Row = i%NUM;
	//	//得到第一幅图像对应区域的数据
	//	m = 0;
	//	for(j=Index_Col*lHeight_N; j<(Index_Col+1)*lHeight_N; j++)
	//	{
	//		n=0;
	//		for(int f=Index_Row*lWidth_N; f<(Index_Row+1)*lWidth_N; f++)
	//		{
	//			if(!rasSrcDS.PixelIO(1, f+1, j+1, &byValue, true))
	//				byValue = 0;
	//			
	//			temp1[m*lWidth_N+n] = byValue;	

	//			if(!rasSrcDS_temp.PixelIO(1, f+1, j+1, &byValue, true))
	//				byValue = 0;
	//			
	//			temp2[m*lWidth_N+n] = byValue;	
	//			n++;
	//		}//for i
	//		m++;
	//	}//for j

	//	//计算两图像对应区域的相关系数
	//	Block_Similar[i] =ColateCoeff(temp1, temp2, lWidth_N, lHeight_N);//相关系数函数，由关小平提供
	//	delete temp1;
	//	delete temp2;
	//}//for i

	//ProgressEnd( hProgress );
 //   ProgressClose( &hProgress );

	////
	//HPROGRESS hProgress2;
	//ProgressCreate( &hProgress2,csProCaption,TRUE,FALSE );
	//ProgressBegin( hProgress2,PROGRESS_MODE_PERCENT, NUM*NUM);
	//ProgressSetStepTitle( hProgress2, "二级检测");
	//ProgressUpdate( hProgress2,FALSE );

	//CopyFile((LPCTSTR)ImageFileName_Dest, (LPCTSTR)ImageFileName_Res, TRUE);

	//resResDS.Open(ImageFileName_Res);
	//resResDS.CreateBuffer();
	//
	//for(i=0; i<NUM*NUM; i++)
	//{
	//	ProgressUpdate( hProgress2,FALSE );
	//	if(Block_Similar[i]<Threshold)
	//	{
	//		/////第一级检测结果处理
	//		ResultFlag[i] = 1;	//为0表示没有变化，为1表示有变化
	//		DetectResult(i, NUM);

	//		//开始第二级检测
	//		int    k;
	//		long   lWidth_nn, lHeight_nn;
	//		double Block_Similar_2[NUM*NUM];
	//		
	//		lWidth_N  = lWidth/NUM;
	//		lHeight_N = lHeight/NUM;
	//		Index_Col = i/NUM;
	//		Index_Row = i%NUM;
	//		//读取检测原文件
	//		rasSrcDS.Open(ImageFileName_Src);
	//		rasSrcDS.CreateBuffer();
	//		rasSrcDS.GetSize(&lWidth, &lHeight);
	//		rasSrcDS.GetBandCount(&lChannelCount);

	//		rasSrcDS_temp.Open(ImageFileName_Dest);
	//		rasSrcDS_temp.CreateBuffer();
	//		rasSrcDS_temp.GetSize(&lWidth_temp, &lHeight_temp);
	//		rasSrcDS_temp.GetBandCount(&lChannelCount_temp);

	//		lWidth_nn  = lWidth/(NUM*NUM);
	//		lHeight_nn = lHeight/(NUM*NUM);

	//		memset(Block_Similar_2, 0, sizeof(Block_Similar_2));
	//		for(k=0; k<NUM*NUM; k++)
	//		{
	//			unsigned char byValue = 0;
	//			unsigned char *temp21 = new unsigned char[lWidth_nn*lHeight_nn];
	//			if(temp21==NULL)
	//			{
	//				return ;
	//			}
	//			unsigned char *temp22 = new unsigned char[lWidth_nn*lHeight_nn];
	//			if(temp22==NULL)
	//			{
	//				return ;
	//			}

	//			int		Index_Col2, Index_Row2;
	//			
	//			Index_Col2 = k/NUM;	//检测图象的第二次定位列
	//			Index_Row2 = k%NUM;	//检测图象的第二次定位行
	//			//得到第一幅图像对应区域的数据
	//			m=0;
	//			for(int p=Index_Col*lHeight_N+Index_Col2*lHeight_nn; p<Index_Col*lHeight_N+(Index_Col2+1)*lHeight_nn; p++)
	//			{
	//				n=0;
	//				for(int q=Index_Row*lWidth_N+Index_Row2*lWidth_nn; q<Index_Row*lWidth_N+(Index_Row2+1)*lWidth_nn; q++)
	//				{
	//					
	//					if(!rasSrcDS.PixelIO(1, q+1, p+1, &byValue, true))
	//						byValue = 0;
	//			
	//					temp21[m*lWidth_nn+n] = byValue;
	//					if(!rasSrcDS_temp.PixelIO(1, q+1, p+1, &byValue, true))
	//						byValue = 0;
	//			
	//					temp22[m*lWidth_nn+n] = byValue;
	//					n++;
	//				}//for i
	//				m++;
	//			}//for j

	//			//计算两图像对应区域的相关系数
	//			Block_Similar_2[k] =ColateCoeff(temp21, temp22, lWidth_nn, lHeight_nn);//相关系数函数，由关小平提供

	//			delete temp22;
	//			delete temp21;
	//		}//for k
	//		rasSrcDS.DeleteBuffer();
	//		rasSrcDS_temp.DeleteBuffer();
	//		 
	//		for(k=0; k<NUM*NUM; k++)
	//		{
	//			/////第二级检测结果处理
	//			if(Block_Similar_2[k]<0.80)
	//			{
	//				DetectResult2(i, k, NUM);

	//				//将检测结果保存到文件中，（为生成ＳＨＰ文件做数据准备）
	//				ChangeBlock_Index data_temp;
	//				data_temp.index_block = i;
	//				data_temp.index_subblock = k;

	//				m_DetectChangeList.push_back(data_temp);
	//			}
	//		}//for k

	//	}//if

	//}//for i

	//ProgressEnd( hProgress2 );
 //   ProgressClose( &hProgress2 );

	////将检测结果生成ＳＨＰ文件
	//string strtemp;
	//string m_szShapeName;
	//string m_szShapeName_temp;
	//string strtemp1;
	//char   csName[256];
	//ChangeBlock_Index data;
	//
	////矢量文件名
	//resResDS.GetName(csName);
	//strtemp = csName;
	//strtemp = strtemp.substr(0, strtemp.find_last_of("."));
	//m_szShapeName_temp = strtemp;	//为删除之前的检测结果文件做准备
	//strtemp += ".shp";
	//m_szShapeName = strtemp;


	//strtemp = m_szShapeName_temp;
	//strtemp1 = strtemp + ".bmp";
	//DeleteFile(strtemp1.c_str());
	//strtemp = m_szShapeName_temp;
	//strtemp1 = strtemp + ".dbf";
	//DeleteFile(strtemp1.c_str());
	//strtemp = m_szShapeName_temp;
	//strtemp1 = strtemp+".shp";
	//DeleteFile(strtemp1.c_str());
	//strtemp = m_szShapeName_temp;
	//strtemp1 = strtemp+".shx";
	//DeleteFile(strtemp1.c_str());
	//strtemp = m_szShapeName_temp;
	//strtemp1 = strtemp+".ovr";
	//DeleteFile(strtemp1.c_str());
 //   
	//OGRFieldDefn oField("userid",OFTInteger);
	//oField.SetWidth(32);

	//m_poFeatureDS = new CFeatureDS();
	//m_poFeatureDS->Create(m_szShapeName.c_str());
	//if(!m_poFeatureDS->get_NumLayers())
	//	m_poFeatureDS->CreatLayer(m_szShapeName.c_str(), "", wkbPolygon, NULL, &oField, 1);
	//
	//for(i=0; i<m_DetectChangeList.size(); i++)
	//{
	//	data = m_DetectChangeList[i];
	//	if(!SaveDetectResult_SHP(m_poFeatureDS, NUM, data.index_block, data.index_subblock))
	//		continue;
	//}

	//delete m_poFeatureDS;

	//resResDS.DeleteBuffer();
	//resResDS.Close();
}



//对待检测的两幅图像分块后的区域，提取直方图特征并进行相似度计算
//注意：图像分割为N×N块，则整幅图像要产生N×N个特征向量，每个特征向量长度为256
//ImageFileName_Src  变化检测原图象路径
//ImageFileName_Dest 变化检测目标图象路径
//Threshold		     相似度域值
void ImgChangeDetect::ImgDetect_Hist(const char* ImageFileName_Src, const char* ImageFileName_Dest, const char* ImageFileName_Res, float Threshold)//相似度阈值
{
	
	//if((strcmp(ImageFileName_Src,"")==0)||(strcmp(ImageFileName_Dest,"")==0))
	//	return;

	//bool        Flag=false;
	//int			i, j;
	//int			ResultFlag[100];
	//float		Vector_Src[100][256];		//原图像分块区域的特征向量集
	//float		Vector_Dest[100][265];	//检测图像分块区域的特征向量集
	//float		Block_Similar[100];
	//long		lWidth_temp, lHeight_temp;
	//long		lChannelCount_temp;
	//CRasterDS	rasSrcDS_temp;
	//
	////初始化各个数组
	//for(i=0; i<NUM*NUM; i++)
	//{
	//	for(j=0; j<256; j++)
	//	{
	//		Vector_Src[i][j]  = 0.0f;
	//		Vector_Dest[i][j] = 0.0f;
	//	}//for j
	//	Block_Similar[i] = 0.0f;
	//	ResultFlag[i] = 0;
	//}

	//
	////读取检测原文件
	//rasSrcDS.Open(ImageFileName_Src);
	//rasSrcDS.CreateBuffer();
	//rasSrcDS.GetSize(&lWidth, &lHeight);
	//rasSrcDS.GetBandCount(&lChannelCount);

	////读取检测目标文件
	//rasSrcDS_temp.Open(ImageFileName_Dest);
	//rasSrcDS_temp.GetSize(&lWidth_temp, &lHeight_temp);
	//rasSrcDS_temp.GetBandCount(&lChannelCount_temp);

	////判断两幅图象规格（长，宽，波段）是否一致，若不一致则退出程序
	//if((lWidth!=lWidth_temp) || (lHeight!=lHeight_temp) || (lChannelCount_temp!=lChannelCount))
	//{
	//	return;
	//}
	//Flag = rasSrcDS_temp.Close();

	////计算两幅图像的平均灰度差分，用来消除同源图像因外界环境不同而产生的影响
	////m_nAverGrayDiff = CalAverGrayDiff(ImageFileName_Src, ImageFileName_Dest);
	//m_nAverGrayDiff = CalAverGrayDiff2(ImageFileName_Src, ImageFileName_Dest);
	////m_nAverGrayDiff = 0;
	//if(m_nAverGrayDiff == -1)
	//{
	//	m_nAverGrayDiff = 0;
	//}

	//
	//pfnProgress(0.1, 0, 0);
	//m_nDealImage = 1;
	////计算图像分块的特征向量
	//for(i=0; i<NUM*NUM; i++)
	//{
	//	Detect_Hist(1, NUM, i, Vector_Src[i]);
	//}//for i

	//pfnProgress(0.2, 0, 0);
	//m_nDealImage = 2;
	////读取检测目标文件
	//rasSrcDS.Open(ImageFileName_Dest);
	//rasSrcDS.CreateBuffer();
	//rasSrcDS.GetSize(&lWidth, &lHeight);
	//rasSrcDS.GetBandCount(&lChannelCount);
	////计算图像分块的特征向量
	//for(i=0; i<NUM*NUM; i++)
	//{
	//	Detect_Hist(1, NUM, i, Vector_Dest[i]);
	//}//for i

	//float Similar_Max=0.0f;
	//float Similar_Sum=0.0f;
	////根据图像分块的特征向量，进行相似度计算
	//for(i=0; i<NUM*NUM; i++)
	//{
	//	for(j=0; j<256; j++)
	//	{
	//		//马氏距离计算两图像块的相似度
	//		Block_Similar[i] += abs(Vector_Src[i][j]-Vector_Dest[i][j]);
	//		
	//	}//for j
	//	Similar_Sum += Block_Similar[i];

	//	if(Similar_Max<Block_Similar[i])
	//	{
	//		Similar_Max = Block_Similar[i];
	//	}
	//}//for i

	//Similar_Sum = Similar_Sum/(NUM*NUM);
	//Threshold   = (Similar_Sum+Similar_Max)/2.0;

	//CopyFile((LPCTSTR)ImageFileName_Dest, (LPCTSTR)ImageFileName_Res, TRUE);

	//resResDS.Open(ImageFileName_Res);
	//resResDS.CreateBuffer();

	//pfnProgress(0.3, 0, 0);
	//m_DetectChangeList.clear();
	//for(i=0; i<NUM*NUM; i++)
	//{
	//	pfnProgress(0.3+i/(NUM*NUM)*0.4, 0, 0);
	//	if(Block_Similar[i]>Threshold)
	//	{
	//		/////第一级检测结果处理
	//		ResultFlag[i] = 1;	//为0表示没有变化，为1表示有变化
	//		DetectResult(i, NUM);

	//		//开始第二级检测
	//		int   k;
	//		float Block_Similar_2[NUM*NUM];
	//		
	//		//初始化各个数组
	//		for(int m=0; m<NUM*NUM; m++)
	//		{
	//			memset(Vector_Src[m], 0, sizeof(float)*256);
	//			memset(Vector_Dest[m], 0, sizeof(float)*256);
	//		
	//		}
	//		memset(Block_Similar_2, 0, sizeof(Block_Similar_2));

	//		//读取检测原文件
	//		rasSrcDS.Open(ImageFileName_Src);
	//		rasSrcDS.CreateBuffer();
	//		rasSrcDS.GetSize(&lWidth, &lHeight);
	//		rasSrcDS.GetBandCount(&lChannelCount);
	//		for(k=0; k<NUM*NUM; k++)
	//		{
	//			Detect_Hist2(lChannelCount, NUM, i, k, Vector_Src[k]);
	//		}//for k
	//		rasSrcDS.DeleteBuffer();

	//		//读取检测目标文件
	//		rasSrcDS.Open(ImageFileName_Dest);
	//		rasSrcDS.CreateBuffer();
	//		rasSrcDS.GetSize(&lWidth, &lHeight);
	//		rasSrcDS.GetBandCount(&lChannelCount);
	//		//计算图像分块的特征向量
	//		for(k=0; k<NUM*NUM; k++)
	//		{
	//			Detect_Hist2(lChannelCount, NUM, i, k, Vector_Dest[k]);
	//		}//for k

	//		//关闭图像缓冲区
	//		rasSrcDS.DeleteBuffer();
	//		rasSrcDS.Close();

	//		Similar_Max=0.0f;
	//		Similar_Sum=0.0f;
	//		//根据图像分块的特征向量，进行相似度计算
	//		for(k=0; k<NUM*NUM; k++)
	//		{
	//			for(int m=0; m<256; m++)
	//			{
	//				//马氏距离计算两图像块的相似度
	//				Block_Similar_2[k] += abs(Vector_Src[k][m]-Vector_Dest[k][m]);
	//				
	//			}//for j
	//			Similar_Sum += Block_Similar_2[i];
	//			if(Similar_Max<Block_Similar_2[i])
	//			{
	//				Similar_Max = Block_Similar_2[i];
	//			}//if
	//		}//for i

	//		Similar_Sum = Similar_Sum/(NUM*NUM);
	//		Threshold   = (Similar_Sum+Similar_Max)/2.0;
	//		 
	//		for(k=0; k<NUM*NUM; k++)
	//		{
	//			/////第二级检测结果处理
	//			if(Block_Similar_2[k]>Threshold)
	//			//if(Block_Similar_2[k]>1.8)
	//			{
	//				DetectResult2(i, k, NUM);

	//				//将检测结果保存到文件中，（为生成ＳＨＰ文件做数据准备）
	//				ChangeBlock_Index data_temp;
	//				data_temp.index_block = i;
	//				data_temp.index_subblock = k;

	//				m_DetectChangeList.push_back(data_temp);
	//			}
	//		}//for k

	//	}//if

	//}//for i

	////将检测结果生成ＳＨＰ文件
	//string strtemp;
	//string m_szShapeName;
	//string m_szShapeName_temp;
	//string strtemp1;
	//char   csName[256];
	//ChangeBlock_Index data;
	//
	////矢量文件名
	//resResDS.GetName(csName);
	//strtemp = csName;
	//strtemp = strtemp.substr(0, strtemp.find_last_of("."));
	//m_szShapeName_temp = strtemp;	//为删除之前的检测结果文件做准备
	//strtemp += ".shp";
	//m_szShapeName = strtemp;


	//strtemp = m_szShapeName_temp;
	//strtemp1 = strtemp + ".bmp";
	//DeleteFile(strtemp1.c_str());
	//strtemp = m_szShapeName_temp;
	//strtemp1 = strtemp + ".dbf";
	//DeleteFile(strtemp1.c_str());
	//strtemp = m_szShapeName_temp;
	//strtemp1 = strtemp+".shp";
	//DeleteFile(strtemp1.c_str());
	//strtemp = m_szShapeName_temp;
	//strtemp1 = strtemp+".shx";
	//DeleteFile(strtemp1.c_str());
	//strtemp = m_szShapeName_temp;
	//strtemp1 = strtemp+".ovr";
	//DeleteFile(strtemp1.c_str());
 //   
	//OGRFieldDefn oField("userid",OFTInteger);
	//oField.SetWidth(32);

	//m_poFeatureDS = new CFeatureDS();
	//m_poFeatureDS->Create(m_szShapeName.c_str());
	//if(!m_poFeatureDS->get_NumLayers())
	//	m_poFeatureDS->CreatLayer(m_szShapeName.c_str(), "", wkbPolygon, NULL, &oField, 1);
	//
	//pfnProgress(0.8, 0, 0);
	//for(i=0; i<m_DetectChangeList.size(); i++)
	//{
	//	data = m_DetectChangeList[i];
	//	if(!SaveDetectResult_SHP(m_poFeatureDS, NUM, data.index_block, data.index_subblock))
	//		continue;
	//}

	//pfnProgress(1.0, 0, 0);

	//delete m_poFeatureDS;

	//resResDS.DeleteBuffer();
	//resResDS.Close();

}

//对待检测的两幅图像分块后的区域，提取颜色矩特征并进行相似度计算
//注意：图像分割为N×N块，则整幅图像要产生N×N个特征向量，每个特征向量长度为3，类型为int
//ImageFileName_Src  变化检测原图象路径
//ImageFileName_Dest 变化检测目标图象路径
//ResultFlag         检测结果返回值，返回值为整型数组 ，值为1表示该区域有变化，为0表示该区域没有变化
//Threshold		     相似度域值
void ImgChangeDetect::ImgDetect_ColorMatix(const char* ImageFileName_Src, const char* ImageFileName_Dest, const char* ImageFileName_Res, float Threshold)
{
	//if((strcmp(ImageFileName_Src,"")==0)||(strcmp(ImageFileName_Dest,"")==0))
	//	return;

	//int			i, j;
	//int			ResultFlag[100];
	//float		Vector_Src[100][3];		//原图像分块区域的特征向量集
	//float		Vector_Dest[100][3];	//检测图像分块区域的特征向量集
	//float		Block_Similar[100];
	//long		lWidth_temp, lHeight_temp;
	//long		lChannelCount_temp;
	//CRasterDS	rasSrcDS_temp;
	//
	////初始化各个数组
	//for(i=0; i<NUM*NUM; i++)
	//{
	//	for(j=0; j<3; j++)
	//	{
	//		Vector_Src[i][j]  = 0.0f;
	//		Vector_Dest[i][j] = 0.0f;
	//	}//for j
	//	Block_Similar[i] = 0.0f;
	//}

	////读取检测原文件
	//rasSrcDS.Open(ImageFileName_Src);
	//rasSrcDS.CreateBuffer();
	//rasSrcDS.GetSize(&lWidth, &lHeight);
	//rasSrcDS.GetBandCount(&lChannelCount);

	////读取检测目标文件
	//rasSrcDS_temp.Open(ImageFileName_Src);
	//rasSrcDS_temp.GetSize(&lWidth_temp, &lHeight_temp);
	//rasSrcDS_temp.GetBandCount(&lChannelCount_temp);

	////判断两幅图象规格（长，宽，波段）是否一致，若不一致则退出程序
	//if((lWidth!=lWidth_temp) || (lHeight!=lHeight_temp) || (lChannelCount_temp!=lChannelCount))
	//{
	//	return;
	//}

	////计算两幅图像的平均灰度差分，用来消除同源图像因外界环境不同而产生的影响
	////m_nAverGrayDiff = CalAverGrayDiff(ImageFileName_Src, ImageFileName_Dest);
	//if(m_nAverGrayDiff == -1)
	//{
	//	m_nAverGrayDiff = 0;
	//}

	//rasSrcDS_temp.Close();

	////计算图像分块的特征向量
	//m_nDealImage = 1;
	//for(i=0; i<NUM*NUM; i++)
	//{
	//	Detect_ColorMatix(1, NUM, i, Vector_Src[i]);
	//}//for i

	////读取检测目标文件
	//m_nDealImage = 2;
	//rasSrcDS.Open(ImageFileName_Dest);
	//rasSrcDS.CreateBuffer();
	//rasSrcDS.GetSize(&lWidth, &lHeight);
	//rasSrcDS.GetBandCount(&lChannelCount);
	////计算图像分块的特征向量
	//for(i=0; i<NUM*NUM; i++)
	//{
	//	Detect_ColorMatix(1, NUM, i, Vector_Dest[i]);
	//}//for i

	//float Similar_Max=0.0f;
	//float Similar_Sum=0.0f;
	////根据图像分块的特征向量，进行相似度计算
	//for(i=0; i<NUM*NUM; i++)
	//{
	//	for(j=0; j<3; j++)
	//	{
	//		//马氏距离计算两图像块的相似度
	//		Block_Similar[i] += abs(Vector_Src[i][j]-Vector_Dest[i][j]);
	//
	//	}//for j
	//	Similar_Sum += Block_Similar[i];

	//	if(Similar_Max<Block_Similar[i])
	//	{
	//		Similar_Max = Block_Similar[i];
	//	}
	//}//for i

	//Similar_Sum = Similar_Sum/(NUM*NUM);
	//Threshold   = (Similar_Sum+Similar_Max)/2.0;

	////问题：建立金字塔
	//CopyFile((LPCTSTR)ImageFileName_Dest, (LPCTSTR)ImageFileName_Res, TRUE);

	//resResDS.Open((char*)(LPCTSTR)ImageFileName_Res);
	//resResDS.CreateBuffer();

	//m_DetectChangeList.clear();
	//for(i=0; i<NUM*NUM; i++)
	//{
	//	if(Block_Similar[i]>Threshold)
	//	//if(Block_Similar[i]>1.0)
	//	{
	//		/////第一级检测结果处理
	//		ResultFlag[i] = 1;	//为0表示没有变化，为1表示有变化
	//		DetectResult(i, NUM);

	//		//开始第二级检测
	//		int k;
	//		float Block_Similar_2[100];
	//		
	//		//初始化各个数组
	//		for(int m=0; m<NUM*NUM; m++)
	//		{
	//			memset(Vector_Src[m], 0, sizeof(float)*3);
	//			memset(Vector_Dest[m], 0, sizeof(float)*3);
	//		
	//		}
	//		memset(Block_Similar_2, 0, sizeof(Block_Similar_2));

	//		//读取检测原文件
	//		rasSrcDS.Open(ImageFileName_Src);
	//		rasSrcDS.CreateBuffer();
	//		rasSrcDS.GetSize(&lWidth, &lHeight);
	//		rasSrcDS.GetBandCount(&lChannelCount);
	//		for(k=0; k<NUM*NUM; k++)
	//		{
	//			Detect_ColorMatix2(lChannelCount, NUM, i, k, Vector_Src[k]);
	//		}//for k

	//		//读取检测目标文件
	//		rasSrcDS.Open(ImageFileName_Dest);
	//		rasSrcDS.CreateBuffer();
	//		rasSrcDS.GetSize(&lWidth, &lHeight);
	//		rasSrcDS.GetBandCount(&lChannelCount);
	//		//计算图像分块的特征向量
	//		for(k=0; k<NUM*NUM; k++)
	//		{
	//			Detect_ColorMatix2(lChannelCount, NUM, i, k, Vector_Dest[k]);
	//		}//for k

	//		//关闭图像缓冲区
	//		rasSrcDS.DeleteBuffer();
	//		rasSrcDS.Close();

	//		Similar_Max=0.0f;
	//		Similar_Sum=0.0f;
	//		//根据图像分块的特征向量，进行相似度计算
	//		for(k=0; k<NUM*NUM; k++)
	//		{
	//			for(int m=0; m<3; m++)
	//			{
	//				//马氏距离计算两图像块的相似度
	//				Block_Similar_2[k] += abs(Vector_Src[k][m]-Vector_Dest[k][m]);
	//				
	//			}//for j
	//			Similar_Sum += Block_Similar[i];

	//			if(Similar_Max<Block_Similar[i])
	//			{
	//				Similar_Max = Block_Similar[i];
	//			}
	//		}//for i
	//		Similar_Sum = Similar_Sum/(NUM*NUM);
	//		Threshold   = (Similar_Sum+Similar_Max)/2.0;

	//		for(k=0; k<NUM*NUM; k++)
	//		{
	//			/////第二级检测结果处理
	//			if(Block_Similar_2[k]>Threshold)
	//			//if(Block_Similar_2[k]>1.97)
	//			{
	//				DetectResult2(i, k, NUM);

	//				//将检测结果保存到文件中，（为生成ＳＨＰ文件做数据准备）
	//				ChangeBlock_Index data_temp;
	//				data_temp.index_block = i;
	//				data_temp.index_subblock = k;

	//				m_DetectChangeList.push_back(data_temp);
	//			}
	//		}//for k

	//	}//if

	//}//for i
	//
	////将检测结果生成ＳＨＰ文件
	//string strtemp;
	//string m_szShapeName;
	//string m_szShapeName_temp;
	//string strtemp1;
	//char csName[256];
	//ChangeBlock_Index data;
	//
	////矢量文件名
	//resResDS.GetName(csName);
	//strtemp = csName;
	//strtemp = strtemp.substr(0, strtemp.find_last_of("."));
	//m_szShapeName_temp = strtemp;	//为删除之前的检测结果文件做准备
	//strtemp += ".shp";
	//m_szShapeName = strtemp;


	//strtemp = m_szShapeName_temp;
	//strtemp1 = strtemp + ".bmp";
	//DeleteFile(strtemp1.c_str());
	//strtemp = m_szShapeName_temp;
	//strtemp1 = strtemp + ".dbf";
	//DeleteFile(strtemp1.c_str());
	//strtemp = m_szShapeName_temp;
	//strtemp1 = strtemp+".shp";
	//DeleteFile(strtemp1.c_str());
	//strtemp = m_szShapeName_temp;
	//strtemp1 = strtemp+".shx";
	//DeleteFile(strtemp1.c_str());
	//strtemp = m_szShapeName_temp;
	//strtemp1 = strtemp+".ovr";
	//DeleteFile(strtemp1.c_str());
 //   
	//OGRFieldDefn oField("userid",OFTInteger);
	//oField.SetWidth(32);

	//m_poFeatureDS = new CFeatureDS;
	//m_poFeatureDS->Create(m_szShapeName.c_str());
	//if(!m_poFeatureDS->get_NumLayers())
	//	m_poFeatureDS->CreatLayer(m_szShapeName.c_str(), "", wkbPolygon, NULL, &oField, 1);

	//for(i=0; i<m_DetectChangeList.size(); i++)
	//{
	//	data = m_DetectChangeList[i];
	//	if(!SaveDetectResult_SHP(m_poFeatureDS, NUM, data.index_block, data.index_subblock))
	//		continue;
	//}

	//delete m_poFeatureDS;

	//resResDS.DeleteBuffer();
	//resResDS.Close();
}

//对待检测的两幅图像分块后的区域，提取纹理谱特征并进行相似度计算
//注意：图像分割为N×N块，则整幅图像要产生N×N个特征向量，每个特征向量长度为3，类型为int
//ImageFileName_Src  变化检测原图象路径
//ImageFileName_Dest 变化检测目标图象路径
//ResultFlag         检测结果返回值，返回值为整型数组 ，值为1表示该区域有变化，为0表示该区域没有变化
//Threshold		     相似度域值
void ImgChangeDetect::ImgDetect_Texture(const char* ImageFileName_Src, const char* ImageFileName_Dest, const char* ImageFileName_Res, float Threshold)
{
	//if((strcmp(ImageFileName_Src,"")==0)||(strcmp(ImageFileName_Dest,"")==0))
	//	return;

	//int			i, j;

	//int			ResultFlag[100];
	//float		Vector_Src[100][256];		//原图像分块区域的特征向量集
	//float		Vector_Dest[100][265];	//检测图像分块区域的特征向量集
	//float		Block_Similar[100];
	//long		lWidth_temp, lHeight_temp;
	//long		lChannelCount_temp;
	//CRasterDS	rasSrcDS_temp;
	//
	////初始化各个数组
	//for(i=0; i<NUM*NUM; i++)
	//{
	//	for(j=0; j<256; j++)
	//	{
	//		Vector_Src[i][j]  = 0.0f;
	//		Vector_Dest[i][j] = 0.0f;
	//	}//for j
	//	Block_Similar[i] = 0.0f;
	//	ResultFlag[i] = 0;
	//}

	////读取检测原文件
	//rasSrcDS.Open(ImageFileName_Src);
	//rasSrcDS.CreateBuffer();
	//rasSrcDS.GetSize(&lWidth, &lHeight);
	//rasSrcDS.GetBandCount(&lChannelCount);

	////读取检测目标文件
	//rasSrcDS_temp.Open(ImageFileName_Src);
	//rasSrcDS_temp.GetSize(&lWidth_temp, &lHeight_temp);
	//rasSrcDS_temp.GetBandCount(&lChannelCount_temp);

	////判断两幅图象规格（长，宽，波段）是否一致，若不一致则退出程序
	//if((lWidth!=lWidth_temp) || (lHeight!=lHeight_temp) || (lChannelCount_temp!=lChannelCount))
	//{
	//	return;
	//}
	//rasSrcDS_temp.Close();
	//
	////计算两幅图像的平均灰度差分，用来消除同源图像因外界环境不同而产生的影响
	////m_nAverGrayDiff = CalAverGrayDiff(ImageFileName_Src, ImageFileName_Dest);
	//if(m_nAverGrayDiff == -1)
	//{
	//	m_nAverGrayDiff = 0;
	//}

	////计算图像分块的特征向量
	//m_nDealImage = 1;
	//for(i=0; i<NUM*NUM; i++)
	//{
	//	Detect_TextureChart(1, NUM, i, Vector_Src[i]);
	//}//for i

	////读取检测目标文件
	//rasSrcDS.Open(ImageFileName_Dest);
	//rasSrcDS.CreateBuffer();
	//rasSrcDS.GetSize(&lWidth, &lHeight);
	//rasSrcDS.GetBandCount(&lChannelCount);
	////计算图像分块的特征向量
	//m_nDealImage = 2;
	//for(i=0; i<NUM*NUM; i++)
	//{
	//	Detect_TextureChart(1, NUM, i, Vector_Dest[i]);
	//}//for i

	//float Similar_Max=0.0f;
	//float Similar_Sum=0.0f;
	////根据图像分块的特征向量，进行相似度计算
	//for(i=0; i<NUM*NUM; i++)
	//{
	//	for(j=0; j<256; j++)
	//	{
	//		//马氏距离计算两图像块的相似度
	//		Block_Similar[i] += abs(Vector_Src[i][j]-Vector_Dest[i][j]);
	//		
	//	}//for j
	//	Similar_Sum += Block_Similar[i];

	//	if(Similar_Max<Block_Similar[i])
	//	{
	//		Similar_Max = Block_Similar[i];
	//	}
	//}//for i
	//Similar_Sum = Similar_Sum/(NUM*NUM);
	//Threshold   = (Similar_Sum+Similar_Max)/2.0;

	//CopyFile((LPCTSTR)ImageFileName_Dest, (LPCTSTR)ImageFileName_Res, TRUE);

	//resResDS.Open((char*)(LPCTSTR)ImageFileName_Res);
	//resResDS.CreateBuffer();

	//m_DetectChangeList.clear();
	//for(i=0; i<NUM*NUM; i++)
	//{
	//	if(Block_Similar[i]>Threshold)
	//	//if(Block_Similar[i]>0.03)
	//	{
	//		/////第一级检测结果处理
	//		ResultFlag[i] = 1;	//为0表示没有变化，为1表示有变化
	//		DetectResult(i, NUM);

	//		//开始第二级检测
	//		int   k;
	//		float Block_Similar_2[NUM*NUM];
	//		
	//		//初始化各个数组
	//		for(int m=0; m<NUM*NUM; m++)
	//		{
	//			memset(Vector_Src[m], 0, sizeof(float)*256);
	//			memset(Vector_Dest[m], 0, sizeof(float)*256);
	//		
	//		}
	//		memset(Block_Similar_2, 0, sizeof(Block_Similar_2));

	//		//读取检测原文件
	//		rasSrcDS.Open(ImageFileName_Src);
	//		rasSrcDS.CreateBuffer();
	//		rasSrcDS.GetSize(&lWidth, &lHeight);
	//		rasSrcDS.GetBandCount(&lChannelCount);
	//		for(k=0; k<NUM*NUM; k++)
	//		{
	//			Detect_TextureChart2(lChannelCount, NUM, i, k, Vector_Src[k]);
	//		}//for k

	//		//读取检测目标文件
	//		rasSrcDS.Open(ImageFileName_Dest);
	//		rasSrcDS.CreateBuffer();
	//		rasSrcDS.GetSize(&lWidth, &lHeight);
	//		rasSrcDS.GetBandCount(&lChannelCount);
	//		//计算图像分块的特征向量
	//		for(k=0; k<NUM*NUM; k++)
	//		{
	//			Detect_TextureChart2(lChannelCount, NUM, i, k, Vector_Dest[k]);
	//		}//for k

	//		//关闭图像缓冲区
	//		rasSrcDS.DeleteBuffer();
	//		rasSrcDS.Close();

	//		Similar_Max=0.0f;
	//		Similar_Sum=0.0f;
	//		//根据图像分块的特征向量，进行相似度计算
	//		for(k=0; k<NUM*NUM; k++)
	//		{
	//			for(int m=0; m<256; m++)
	//			{
	//				//马氏距离计算两图像块的相似度
	//				Block_Similar_2[k] += abs(Vector_Src[k][m]-Vector_Dest[k][m]);
	//				
	//			}//for j
	//			Similar_Sum += Block_Similar[i];

	//			if(Similar_Max<Block_Similar[i])
	//			{
	//				Similar_Max = Block_Similar[i];
	//			}
	//		}//for i
	//		Similar_Sum = Similar_Sum/(NUM*NUM);
	//		Threshold   = (Similar_Sum+Similar_Max)/2.0;
	//		 
	//		for(k=0; k<NUM*NUM; k++)
	//		{
	//			/////第二级检测结果处理
	//			if(Block_Similar_2[k]>Threshold)
	//			//if(Block_Similar_2[k]>0.02)
	//			{
	//				DetectResult2(i, k, NUM);

	//				//将检测结果保存到文件中，（为生成ＳＨＰ文件做数据准备）
	//				ChangeBlock_Index data_temp;
	//				data_temp.index_block = i;
	//				data_temp.index_subblock = k;

	//				m_DetectChangeList.push_back(data_temp);
	//			}
	//		}//for k

	//	}//if

	//}//for i
	//

	////将检测结果生成ＳＨＰ文件
	//string strtemp;
	//string m_szShapeName;
	//string m_szShapeName_temp;
	//string strtemp1;
	//char csName[256];
	//ChangeBlock_Index data;
	//
	////矢量文件名
	//resResDS.GetName(csName);
	//strtemp = csName;
	//strtemp = strtemp.substr(0, strtemp.find_last_of("."));
	//m_szShapeName_temp = strtemp;	//为删除之前的检测结果文件做准备
	//strtemp += ".shp";
	//m_szShapeName = strtemp;


	//strtemp = m_szShapeName_temp;
	//strtemp1 = strtemp + ".bmp";
	//DeleteFile(strtemp1.c_str());
	//strtemp = m_szShapeName_temp;
	//strtemp1 = strtemp + ".dbf";
	//DeleteFile(strtemp1.c_str());
	//strtemp = m_szShapeName_temp;
	//strtemp1 = strtemp+".shp";
	//DeleteFile(strtemp1.c_str());
	//strtemp = m_szShapeName_temp;
	//strtemp1 = strtemp+".shx";
	//DeleteFile(strtemp1.c_str());
	//strtemp = m_szShapeName_temp;
	//strtemp1 = strtemp+".ovr";
	//DeleteFile(strtemp1.c_str());
 //   
	//OGRFieldDefn oField("userid",OFTInteger);
	//oField.SetWidth(32);

	//m_poFeatureDS = new CFeatureDS();
	//m_poFeatureDS->Create(m_szShapeName.c_str());
	//if(!m_poFeatureDS->get_NumLayers())
	//	m_poFeatureDS->CreatLayer(m_szShapeName.c_str(), "", wkbPolygon, NULL, &oField, 1);
	//
	//for(i=0; i<m_DetectChangeList.size(); i++)
	//{
	//	data = m_DetectChangeList[i];
	//	if(!SaveDetectResult_SHP(m_poFeatureDS, NUM, data.index_block, data.index_subblock))
	//		continue;
	//}

	//delete m_poFeatureDS;
	//resResDS.DeleteBuffer();
	//resResDS.Close();

}

//对待检测的两幅图像分块后的区域，提取共生矩阵特征并进行相似度计算
//注意：图像分割为N×N块，则整幅图像要产生N×N个特征向量，每个特征向量长度为5，类型为int
//ImageFileName_Src  变化检测原图象路径
//ImageFileName_Dest 变化检测目标图象路径
//ResultFlag         检测结果返回值，返回值为整型数组 ，值为1表示该区域有变化，为0表示该区域没有变化
//Threshold		     相似度域值
void ImgChangeDetect::ImgDetect_Adjoint(const char* ImageFileName_Src, const char* ImageFileName_Dest, float Threshold)
{
//	if((strcmp(ImageFileName_Src,"")==0)||(strcmp(ImageFileName_Dest,"")==0))
//		return;
//
//	int		i, j;
//	int		ResultFlag[NUM*NUM];
//	float		Vector_Src[NUM*NUM][256];		//原图像分块区域的特征向量集
//	float		Vector_Dest[NUM*NUM][265];	//检测图像分块区域的特征向量集
//	float		Block_Similar[NUM*NUM];
//	long		lWidth_temp, lHeight_temp;
//	long		lChannelCount_temp;
//	CRasterDS	rasSrcDS_temp;
//	
//	//初始化各个数组
//	for(i=0; i<NUM*NUM; i++)
//	{
//		for(j=0; j<256; j++)
//		{
//			Vector_Src[i][j]  = 0.0f;
//			Vector_Dest[i][j] = 0.0f;
//		}//for j
//		Block_Similar[i] = 0.0f;
//		ResultFlag[i] = 0;
//	}
//
//	//读取检测原文件
//	rasSrcDS.Open(ImageFileName_Src);
//	rasSrcDS.CreateBuffer();
//	rasSrcDS.GetSize(&lWidth, &lHeight);
//	rasSrcDS.GetBandCount(&lChannelCount);
//
//	//读取检测目标文件
//	rasSrcDS_temp.Open(ImageFileName_Src);
//	rasSrcDS_temp.CreateBuffer();
//	rasSrcDS_temp.GetSize(&lWidth_temp, &lHeight_temp);
//	rasSrcDS_temp.GetBandCount(&lChannelCount_temp);
//
//	//判断两幅图象规格（长，宽，波段）是否一致，若不一致则退出程序
//	if((lWidth!=lWidth_temp) || (lHeight!=lHeight_temp) || (lChannelCount_temp!=lChannelCount))
//	{
//		return;
//	}
//	rasSrcDS_temp.DeleteBuffer();
//	rasSrcDS_temp.Close();
//	
//	
//	//计算图像分块的特征向量
//	for(i=0; i<NUM*NUM; i++)
//	{
//		Detect_Adjoint(1, NUM, i, Vector_Src[i]);
//	}//for i
//
//	//读取检测目标文件
//	rasSrcDS.Open(ImageFileName_Dest);
//	rasSrcDS.CreateBuffer();
//	rasSrcDS.GetSize(&lWidth, &lHeight);
//	rasSrcDS.GetBandCount(&lChannelCount);
//	//计算图像分块的特征向量
//	for(i=0; i<NUM*NUM; i++)
//	{
//		Detect_Adjoint(1, NUM, i, Vector_Dest[i]);
//	}//for i
//
//	//根据图像分块的特征向量，进行相似度计算
//	for(i=0; i<NUM*NUM; i++)
//	{
//		for(j=0; j<256; j++)
//		{
//			//马氏距离计算两图像块的相似度
//			Block_Similar[i] += abs(Vector_Src[i][j]-Vector_Dest[i][j]);
//		}//for j
//	}//for i
//
//	//建立检测结果文件
//	STRasFileInfo Info;
//	Info.lHeaderLen = 0;				//图像的头长度
//	Info.lWidth = lWidth;				//图像的宽度
//	Info.lHeight = lHeight;				//图像的高度
//	Info.lChannelNum = lChannelCount;	//图像的通道数
//	Info.lFormatType = 3;				//数据组织方式
//	Info.lDataType = lDataType;
//
//	BYTE byValue = 0;
//	FILE *pFile;
//	char* strTemp = "e:\\DetectChangeHist_temp.bmp";
//
//	if(!resResDS.Create(strTemp, &Info))
//		return ;
//
//	resResDS.Open(strTemp, GA_Update);
//	resResDS.CreateBuffer();
//
///*
//	//保存图象变化检测结果到文本文件
//	if((pFile=fopen("E:\\cognition\\imagedetect_hist.txt", "wb"))==NULL)
//	{
//		return;
//	}
//*/
//	for(i=0; i<lHeight; i++)
//
//		for(j=0; j<lWidth; j++)
//		{
//			if(!rasSrcDS.PixelIO(lChannelCount, j+1, i+1, &byValue, true))
//				byValue = 0;
//				
//			resResDS.PixelIO(lChannelCount, j+1, i+1, &byValue, false); 
//		}//for j
//
//	m_DetectChangeList.clear();
//	for(i=0; i<NUM*NUM; i++)
//	{
//		if(Block_Similar[i]>Threshold)
//		{
//			/////第一级检测结果处理
//			ResultFlag[i] = 1;	//为0表示没有变化，为1表示有变化
//			DetectResult(i, NUM);
///*
//			//开始第二级检测
//			int k;
//			float Block_Similar_2[NUM*NUM];
//			
//			//初始化各个数组
//			for(int m=0; m<NUM*NUM; m++)
//			{
//				memset(Vector_Src[m], 0, sizeof(float)*256);
//				memset(Vector_Dest[m], 0, sizeof(float)*256);
//			
//			}
//			memset(Block_Similar_2, 0, sizeof(Block_Similar_2));
//
//			//读取检测原文件
//			rasSrcDS.Open(ImageFileName_Src);
//			rasSrcDS.CreateBuffer();
//			rasSrcDS.GetSize(&lWidth, &lHeight);
//			rasSrcDS.GetBandCount(&lChannelCount);
//			for(k=0; k<NUM*NUM; k++)
//			{
//				Detect_TextureChart2(lChannelCount, NUM, i, k, Vector_Src[k]);
//			}//for k
//
//			//读取检测目标文件
//			rasSrcDS.Open(ImageFileName_Dest);
//			rasSrcDS.CreateBuffer();
//			rasSrcDS.GetSize(&lWidth, &lHeight);
//			rasSrcDS.GetBandCount(&lChannelCount);
//			//计算图像分块的特征向量
//			for(k=0; k<NUM*NUM; k++)
//			{
//				Detect_TextureChart2(lChannelCount, NUM, i, k, Vector_Dest[k]);
//			}//for k
//
//			//关闭图像缓冲区
//			rasSrcDS.DeleteBuffer();
//			rasSrcDS.Close();
//
//			//根据图像分块的特征向量，进行相似度计算
//			for(k=0; k<NUM*NUM; k++)
//			{
//				for(int m=0; m<256; m++)
//				{
//					//马氏距离计算两图像块的相似度
//					Block_Similar_2[k] += abs(Vector_Src[k][m]-Vector_Dest[k][m]);
//				}//for j
//			}//for i
//			 
//			for(k=0; k<NUM*NUM; k++)
//			{
//				/////第二级检测结果处理
//				//if(Block_Similar_2[k]>Threshold)
//				if(Block_Similar_2[k]>0.8)
//				{
//					DetectResult2(i, k, NUM);
//
//					//将检测结果保存到文件中，（为生成ＳＨＰ文件做数据准备）
//					ChangeBlock_Index data_temp;
//					data_temp.index_block = i;
//					data_temp.index_subblock = k;
//
//					m_DetectChangeList.push_back(data_temp);
//
//					//fseek(pFile, 0, SEEK_END);
//					//fwrite(&data_temp, sizeof(data_temp), 1, pFile); 
//				}
//			}//for k
//*/
//		}//if
//
//	}//for i
//	
///*
//	//将检测结果生成ＳＨＰ文件
//	string strtemp;
//	string m_szShapeName;
//	string m_szShapeName_temp;
//	string strtemp1;
//	char csName[256];
//	ChangeBlock_Index data;
//	
//	//矢量文件名
//	resResDS.GetName(csName);
//	strtemp = csName;
//	strtemp = strtemp.substr(0, strtemp.find_last_of("."));
//	m_szShapeName_temp = strtemp;	//为删除之前的检测结果文件做准备
//	strtemp += ".shp";
//	m_szShapeName = strtemp;
//
//
//	strtemp = m_szShapeName_temp;
//	strtemp1 = strtemp + ".bmp";
//	DeleteFile(strtemp1.c_str());
//	strtemp = m_szShapeName_temp;
//	strtemp1 = strtemp + ".dbf";
//	DeleteFile(strtemp1.c_str());
//	strtemp = m_szShapeName_temp;
//	strtemp1 = strtemp+".shp";
//	DeleteFile(strtemp1.c_str());
//	strtemp = m_szShapeName_temp;
//	strtemp1 = strtemp+".shx";
//	DeleteFile(strtemp1.c_str());
//	strtemp = m_szShapeName_temp;
//	strtemp1 = strtemp+".ovr";
//	DeleteFile(strtemp1.c_str());
//    
//	OGRFieldDefn oField("userid",OFTInteger);
//	oField.SetWidth(32);
//
//	m_poFeatureDS = new CFeatureDS();
//	m_poFeatureDS->Create(m_szShapeName.c_str());
//	if(!m_poFeatureDS->get_NumLayers())
//		m_poFeatureDS->CreatLayer(m_szShapeName.c_str(), "", wkbPolygon, NULL, &oField, 1);
//
//*/
//
///*
//	fseek(pFile, 0, SEEK_SET);
//	while(!feof(pFile))
//	{
//		fread(&data, sizeof(ChangeBlock_Index), 1, pFile);
//		if(!SaveDetectResult_SHP(m_poFeatureDS, NUM, data.index_block, data.index_subblock))
//			continue;
//	}
//	fclose(pFile);
//
//	for(i=0; i<m_DetectChangeList.size(); i++)
//	{
//		data = m_DetectChangeList[i];
//		if(!SaveDetectResult_SHP(m_poFeatureDS, NUM, data.index_block, data.index_subblock))
//			continue;
//	}
//
//	delete m_poFeatureDS;
//*/
//	resResDS.DeleteBuffer();
//	resResDS.Close();
}

#undef //#define NUM 10

//计算图像指定区域的颜色矩特征向量
//ImageFileName	图像名称
//lIndexBand	图像的波段
//Num			图像分割为Num*Num块	
//nIndexBlock	图像分割后，要计算直方图特征向量的区域标号
//*Vector		图像直方图特征向量， 向量默认长度为3，类型为float
bool ImgChangeDetect::Detect_ColorMatix(long lIndexBand, int Num, int nIndexBlock, float* Vector)
{
	bool flag=false;

	//if(Vector == NULL)
	//{
	//	return flag;
	//}
	//
	//int      i, j;
	//int 	 Index_Col, Index_Row;
	//int      lWidth_N,lHeight_N;
	//float	 Block_Density[3];
	//unsigned char byValue=0;

	//lWidth_N  = lWidth/Num;
	//lHeight_N = lHeight/Num;
	//Index_Col = nIndexBlock/Num;
	//Index_Row = nIndexBlock%Num;
	//
	//unsigned char *temp1 = new unsigned char[lWidth*lHeight];
	//if(temp1 == NULL)
	//{
	//	flag = false;
	//	return flag;
	//}

	////多光谱影像
	//rasSrcDS.GetBandDataType(lIndexBand, &lDataType);
	//memset(Block_Density, 0, sizeof(Block_Density));

	////取得图像指定块的像素信息
	//int m, n;
	//
	//m = 0;
	//for(j=Index_Col*lHeight_N; j<(Index_Col+1)*lHeight_N; j++)
	//{
	//	n=0;
	//	for(i=Index_Row*lWidth_N; i<(Index_Row+1)*lWidth_N; i++)
	//	{
	//		if(!rasSrcDS.PixelIO(lIndexBand, i+1, j+1, &byValue, true))
	//			byValue = 0;
	//		if(m_nDealImage==2)//表示正在处理的是目标图像，需要进行灰度差分弥合（即消除同源图像在不同环境下的差别）
	//		{
	//			byValue += m_nAverGrayDiff;
	//			if(byValue>255)
	//				byValue = 255;
	//			if(byValue<0)
	//				byValue = 0;
	//		}//if
	//		
	//		temp1[m*lWidth_N+n] = byValue;	
	//		n++;
	//	}//for i
	//	m++;
	//}//for j
	//
	////计算图像块的一阶矩
	////分量的一阶矩为各个分量的平均值
	//float sum_temp=0.0f;
	//float index_pow;
	//float temp;

	//for(i=0; i<lHeight_N; i++)
	//	for(j=0; j<lWidth_N; j++)
	//	{
	//		sum_temp += (float)temp1[i*lWidth_N+j];
	//	}//for j 
	//Block_Density[0] = sum_temp/(float)(lHeight_N*lWidth_N);

	////计算图像块的二阶矩
	//sum_temp = 0.0f;
	//for(i=0; i<lHeight_N; i++)
	//	for(j=0; j<lWidth_N; j++)
	//	{
	//		
	//		//取得图像块的像素信息
	//		byValue = temp1[i*lWidth_N+j];
	//		temp = byValue;
	//		temp = Block_Density[0]-temp;
	//		sum_temp += temp*temp;
	//
	//	}//for j
	//sum_temp = sum_temp/(lHeight_N*lWidth_N);
	//Block_Density[1] = (float)sqrt(sum_temp);
	//
	////计算图像块的三阶矩
	//sum_temp = 0.0f;
	//index_pow = 0.3334f;
 //   for(i=0; i<lHeight_N; i++)
	//	for(j=0; j<lWidth_N; j++)
	//	{
	//		//取得图像块的像素信息
	//		byValue = temp1[i*lWidth_N+j];
	//		temp = byValue;
	//		temp = Block_Density[1]-temp;
	//		sum_temp += fabs(powf(temp, 3.0f));
	//	}//for j
	//sum_temp = sum_temp/(lHeight_N*lWidth_N);
	//Block_Density[2] = powf(sum_temp, index_pow);

	//delete []temp1;
	//temp1 = NULL;

	//for(i=0; i<3; i++)
	//{
	//	Vector[i] = Block_Density[i];
	//}

	flag = true;
	return flag;
}

//计算图像指定区域的纹理谱特征向量
//ImageFileName	图像名称
//lIndexBand	图像的波段
//Num			图像分割为Num*Num块	
//nIndexBlock	图像分割后，要计算直方图特征向量的区域标号
//*Vector		图像直方图特征向量， 向量默认长度为256，类型为float
bool ImgChangeDetect::Detect_TextureChart(long lIndexBand, int Num, int nIndexBlock, float* Vector)
{
	//const int THRESHOLD=8; //象素点与其邻接点之间进行比较的阈值

	//bool flag=false;
	//int  border[8];
	//long stat[256];//图像纹理谱特征向量
	//
	//BYTE	byValue = 0;
	//LPBYTE	temp1;
	//int     i, j;
	//int 	Index_Col, Index_Row;
	//int     lWidth_N,lHeight_N;

	////多光谱影像
	//rasSrcDS.GetBandDataType(lIndexBand, &lDataType);
	//
	//lWidth_N  = lWidth/Num;
	//lHeight_N = lHeight/Num;
	//Index_Col = nIndexBlock/Num;
	//Index_Row = nIndexBlock%Num;

	////取得图像指定块的像素信息
	////temp1 = new BYTE[lHeight_N*lWidth_N];
	//temp1 = (BYTE*)malloc(sizeof(BYTE)*lHeight_N*lWidth_N);
	//if(temp1 == NULL)
	//{
	//	flag = false;
	//	return flag;
	//}
	//int m,n;

	//m=0;
	//for(j=Index_Col*lHeight_N; j<(Index_Col+1)*lHeight_N; j++)
	//{
	//	n=0;
	//	for(i=Index_Row*lWidth_N; i<(Index_Row+1)*lWidth_N; i++)
	//	{
	//		if(!rasSrcDS.PixelIO(lIndexBand, j+1, i+1, &byValue, true))
	//			byValue = 0;
	//		if(m_nDealImage==2)//表示正在处理的是目标图像，需要进行灰度差分弥合（即消除同源图像在不同环境下的差别）
	//		{
	//			byValue += m_nAverGrayDiff;
	//			if(byValue>255)
	//				byValue = 255;
	//			if(byValue<0)
	//				byValue = 0;
	//		}//if
	//		
	//		temp1[m*lWidth_N+n] = byValue;	
	//		n++;
	//	}//for i

	//	m++;
	//}
	//memset(stat, 0, sizeof(stat));
	//for(j=1; j<lHeight_N-1; j++)
	//{
	//	for(i=1; i<lWidth_N-1; i++)
	//	{
	//		///计算某象素点的八个邻接点的相对灰阶关系
	//		int sum=0;
	//		int difference; 
	//		int border_point;
	//		int center_point = temp1[j*lWidth_N+i];
	//		 
	//		//first
	//		border_point = temp1[(j-1)*lWidth_N+(i-1)];
	//		difference = abs(border_point-center_point);
	//		if(difference<THRESHOLD)
	//			border[0] = 1;
	//		else
	//			border[0] = 0; 
	//		
	//		//second
	//		border_point = temp1[(j-1)*lWidth_N+i];
	//		difference = abs(border_point-center_point);
	//		if(difference<THRESHOLD)
	//			border[1] = 1;
	//		else
	//			border[1] = 0; 
	//		
	//		//third
	//		border_point = temp1[(j-1)*lWidth_N+(i+1)];
	//		difference = abs(border_point-center_point);
	//		if(difference<THRESHOLD)
	//			border[2] = 1;
	//		else
	//			border[2] = 0; 
	//		
	//		//forth
	//		border_point = temp1[j*lWidth_N+(i-1)];
	//		difference = abs(border_point-center_point);
	//		if(difference<THRESHOLD)
	//			border[3] = 1;
	//		else
	//			border[3] = 0;
	//		
	//		//fifth
	//		border_point = temp1[(j)*lWidth_N+(i+1)];
	//		difference = abs(border_point-center_point);
	//		if(difference<THRESHOLD)
	//			border[4] = 1;
	//		else
	//			border[4] = 0;
	//		
	//		//sixth
	//		border_point = temp1[(j+1)*lWidth_N+(i-1)];
	//		difference = abs(border_point-center_point);
	//		if(difference<THRESHOLD)
	//			border[5] = 1;
	//		else
	//			border[5] = 0;
	//		
	//		//seventh
	//		border_point = temp1[(j+1)*lWidth_N+(i)];
	//		difference = abs(border_point-center_point);
	//		if(difference<THRESHOLD)
	//			border[6] = 1;
	//		else
	//			border[6] = 0;
	//		
	//		//eighth
	//		border_point = temp1[(j+1)*lWidth_N+(i+1)];
	//		difference = abs(border_point-center_point);
	//		if(difference<THRESHOLD)
	//			border[7] = 1;
	//		else
	//			border[7] = 0;
	//	
	//		///根据八个邻接点的相对灰度关系，统计纹理单元的发生频数
	//		for(int k=0; k<8; k++)
	//		{
	//			sum += (int)pow(2.0f, k)*border[k];
	//		}//for k
	//		///统计频率
	//		stat[sum]++;
	//	}//for j
	//}//for i 

	//delete temp1;

	////对特征向量进行归一化
	//long sum=0;
	//for(i=0; i<256; i++)
	//{
	//	sum += stat[i];
	//}// for i
	//for(i=0; i<256; i++)
	//{
	//	Vector[i] = (float)stat[i]/(float)sum;
	//}//for i

	//flag = true;
	//return flag;
    
    return true;
}

//计算图像指定区域的直方图特征向量
//lIndexBand	图像的波段
//Num			图像分割为Num*Num块	
//nIndexBlock	图像分割后，要计算直方图特征向量的区域标号
//*Vector		图像直方图特征向量， 向量默认长度为256，类型为float
bool ImgChangeDetect::Detect_Hist(long lIndexBand, int Num, int nIndexBlock, float* Vector)
{
	bool    flag=false;
	//BYTE	byValue = 0;
	//int     i, j;
	//int 	Index_Col, Index_Row;
	//long    lWidth_n,lHeight_n;
	//int	    Block_Density[256];
	//
	//memset(Block_Density, 0, sizeof(Block_Density));

	////多光谱影像
	//rasSrcDS.GetBandDataType(lIndexBand, &lDataType);
	//
	//lWidth_n  = lWidth/Num;
	//lHeight_n = lHeight/Num;
	//Index_Col = nIndexBlock/Num;
	//Index_Row = nIndexBlock%Num;

	//for(j=Index_Col*lHeight_n; j<(Index_Col+1)*lHeight_n; j++)
	//	for(i=Index_Row*lWidth_n; i<(Index_Row+1)*lWidth_n; i++)
	//	{
	//		
	//		if(!rasSrcDS.PixelIO(lIndexBand, i+1, j+1, &byValue, true))
	//			byValue = 0;
	//
	//		if(m_nDealImage==2)//表示正在处理的是目标图像，需要进行灰度差分弥合（即消除同源图像在不同环境下的差别）
	//		{
	//			byValue += m_nAverGrayDiff;
	//			if(byValue>255)
	//				byValue = 255;
	//			if(byValue<0)
	//				byValue = 0;
	//		}
	//		Block_Density[byValue]++;
	//	}//for i
	//for(i=0; i<256; i++)
	//	{
	//		Vector[i] = (float)Block_Density[i]/(float)(lWidth_n*lHeight_n);
	//	}//for i
	
	flag = true;
	return flag;
}

//显示变化检测结果，以矩形框的方式显示在目标图象中
//nIndex 表示图象中变化的区块号
//Num    表示图象被分割为Num*Num块
void ImgChangeDetect::DetectResult(int nIndex, int Num)
{
	//int nWidth_N, nHeight_N;
	//int temp_h,temp_w;
	//BYTE byValue = 0;

	//nWidth_N  = lWidth/Num;
	//nHeight_N = lHeight/Num;

	//temp_h = nIndex/Num;
	//temp_w = nIndex%Num;
	//
	//for(int m=temp_h*nHeight_N; m<=(temp_h+1)*nHeight_N; m++)
	//{
	//	for(int n=temp_w*nWidth_N; n<=(temp_w+1)*nWidth_N; n++)
	//	{
	//		if(m==temp_h*nHeight_N || m==(temp_h+1)*nHeight_N)
	//		{
	//			resResDS.PixelIO(1, n, m, &byValue, false);
	//		}
	//		if(n==temp_w*nWidth_N || n==(temp_w+1)*nWidth_N)
	//		{
	//			resResDS.PixelIO(1, n, m, &byValue, false);
	//		}
	//	}//n
	//}//
			
}

//显示图象变化检测，直方图方式的二次检测结果，LQ
void ImgChangeDetect::DetectResult2(int nIndex_Block, int nIndex_Subblock, int Num)
{
	//BYTE	byValue = 254;
	//int     i, j;
	//int 	Index_Col, Index_Row;
	//int		Index_Col2, Index_Row2;
	//long    lWidth_N,lHeight_N;
	//long 	lWidth_NN,lHeight_NN;
	//

	//lWidth_N   = lWidth/Num;
	//lHeight_N  = lHeight/Num;
	//lWidth_NN  = lWidth/(Num*Num);
	//lHeight_NN = lHeight/(Num*Num);

	//Index_Col  = nIndex_Block/Num;
	//Index_Row  = nIndex_Block%Num;
	//Index_Col2 = nIndex_Subblock/Num;	//检测图象的第二次定位列
	//Index_Row2 = nIndex_Subblock%Num;	//检测图象的第二次定位行

	/////将变化检测结果在图象上标示出来，
	//for(j=Index_Col*lHeight_N+Index_Col2*lHeight_NN; j<=Index_Col*lHeight_N+(Index_Col2+1)*lHeight_NN; j++)
	//	for(i=Index_Row*lWidth_N+Index_Row2*lWidth_NN; i<=Index_Row*lWidth_N+(Index_Row2+1)*lWidth_NN; i++)
	//	{
	//		if(j==Index_Col*lHeight_N+Index_Col2*lHeight_NN || j==Index_Col*lHeight_N+(Index_Col2+1)*lHeight_NN)
	//		{
	//			resResDS.PixelIO(1, i+1, j+1, &byValue, false);
	//		}
	//		if(i==Index_Row*lWidth_N+Index_Row2*lWidth_NN || i==Index_Row*lWidth_N+(Index_Row2+1)*lWidth_NN)
	//		{
	//			resResDS.PixelIO(1, i+1, j+1, &byValue, false);
	//		}
	//	}//for i
}

//图像分块相似度计算函数（适用像素级(直方图，颜色矩，纹理谱方式)的图像变化检测），LQ
//vector1为图像分块1的特征向量
//length1表示特征向量1的长度
//vector2为图像分块2的特征向量
//length2表示特征向量2的长度
//返回值为两图像分块的相似度，为float型
//float ImgChangeDetect::VectorMatch_M(float* vector1, int length1, float* vector2, int length2)
//{
//	if(length1 != length2)
//		return -1.0f;
//
//	float result;
//
//	result = 0.0f;
//	//马氏距离
//	for(int i=0; i<length1; i++)
//	{
//		result += abs(vector1[i]-vector2[i]);
//	}//for i
//
//	return result;
//}

//图像分块相似度计算函数（适用像素级(直方图，颜色矩，纹理谱方式)的图像变化检测），LQ
//vector1为图像分块1的特征向量
//length1表示特征向量1的长度
//vector2为图像分块2的特征向量
//length2表示特征向量2的长度
//返回值为两图像分块的相似度，为float型
//float ImgChangeDetect::VectorMatch_O(float* vector1, int length1, float* vector2, int length2)
//{
//	float sim=-1.0f;
//
//	if(length1 != length2)
//		return sim;
//	
//	sim = 0.0f;
//	for(int i=0; i<length1; i++)
//	{
//		sim += (float)sqrt((vector1[i]-vector2[i])*(vector1[i]-vector2[i]));
//	}
//
//	return sim;
//}

//图像分割对象相似度计算函数（适用对象级的变化检测）,LQ
//Object1表示图像分割对象1
//Object2表示图像分割对象2
//返回值为两图像对象的相似度，为bool型；为1表示
//bool ImgChangeDetect::ObjMatch(Obj_Shape Object1, Obj_Shape Object2)
//{
//	bool flag=true;
//	float result_temp;
//
//	////比较两对象形状属性
//	//比较两分割对象形状属性中的面积属性
//	result_temp = Object1.data_shape_generic.Area - Object2.data_shape_generic.Area;
//	result_temp = result_temp/Object1.data_shape_generic.Area;
//	if(fabs(result_temp)>0.1)	//面积域值 0.1
//		return false;
//
//	//比较两分割对象形状属性中的平均灰度属性
//	result_temp = Object1.data_shape_generic.AverGray - Object2.data_shape_generic.AverGray;
//	if(fabs(result_temp)>5)	   //平均灰度域值 5
//		return false;
//
//	//比较两分割对象形状属性中的紧致度属性
//	result_temp = Object1.data_shape_generic.Compactness - Object2.data_shape_generic.Compactness;
//	result_temp = result_temp/Object1.data_shape_generic.Compactness;
//	if(fabs(result_temp)>0.1)	//紧致度域值 0.1
//		return false;
//
//	//比较两分割对象形状属性中的边长属性
//	result_temp = Object1.data_shape_generic.Border_Length - Object2.data_shape_generic.Border_Length;
//	result_temp = result_temp/Object1.data_shape_generic.Border_Length;
//	if(fabs(result_temp)>0.1)	//边长域值 0.1
//		return false;
//
//	//比较两分割对象形状属性中的x坐标重心属性
//	result_temp = Object1.data_shape_position.X_Center_Cood - Object2.data_shape_position.X_Center_Cood;
//	if(fabs(result_temp)>8)		//对象X重心坐标域值 8 
//		return false;			
//
//	result_temp = Object1.data_shape_position.Y_Center_Cood - Object2.data_shape_position.Y_Center_Cood;
//	if(fabs(result_temp)>8)		//对象Y重心坐标域值 8 
//		return false;
///*
//	////比较两对象纹理属性
//	//比较两对象纹理属性中对象纹理的同质性属性
//	result_temp = Object1.data_texture.data_GLCM_homogeneity.Layer1_GLCM_Homogeneity - Object2.data_texture.data_GLCM_homogeneity.Layer1_GLCM_Homogeneity;
//	if(fabs(result_temp)>0.1)	//对象纹理的同质性域值 0.1
//		return false;
//
//	//比较两对象纹理属性中对象纹理的同质性属性
//	result_temp = Object1.data_texture.data_GLCM_contrast.Layer1_GLCM_Contrast - Object2.data_texture.data_GLCM_contrast.Layer1_GLCM_Contrast;
//	if(fabs(result_temp)>0.1)	//对象纹理的对比性域值 0.1
//		return false;
//
//	//比较两对象纹理属性中对象纹理的均值属性
//	result_temp = Object1.data_texture.data_GLCM_mean.Layer1_GLCM_Mean - Object2.data_texture.data_GLCM_mean.Layer1_GLCM_Mean;
//	if(fabs(result_temp)>0.1)	//对象纹理的均值域值 0.1
//		return false;
//
//	//比较两对象纹理属性中对象纹理的均值属性
//	result_temp = Object1.data_texture.data_GLCM_entropy.Layer1_GLCM_Entropy - Object2.data_texture.data_GLCM_entropy.Layer1_GLCM_Entropy;
//	if(fabs(result_temp)>0.1)	//对象纹理的均值域值 0.1
//		return false;
//*/
//	return true;
//}

//将图象变化检测结果保存到ＳＨＰ文件中，ＬＱ
bool ImgChangeDetect::SaveDetectResult_SHP(const char *shpfilename, int Num, int nBlockIndex, int nSubblockIndex)
{
	bool flag=true;

	//if(m_poFeatureDS == NULL)
	//	return false;

	//OGRPolygon    *ppoly=new OGRPolygon();
	//OGRLinearRing *pRing=new OGRLinearRing();
	//OGRPoint pt;
	//SPoint CurPoint;

	//int     i, j;
	//int 	Index_Col, Index_Row;
	//int		Index_Col2, Index_Row2;
	//long    lWidth_N, lHeight_N;
	//long 	lWidth_NN, lHeight_NN;
	//double  dblX, dblY;
	//
	//lWidth_N   = lWidth/Num;
	//lHeight_N  = lHeight/Num;
	//lWidth_NN  = lWidth/(Num*Num);
	//lHeight_NN = lHeight/(Num*Num);

	//Index_Col  = nBlockIndex/Num;
	//Index_Row  = nBlockIndex%Num;
	//Index_Col2 = nSubblockIndex/Num;	//检测图象的第二次定位列
	//Index_Row2 = nSubblockIndex%Num;	//检测图象的第二次定位行

	////(x,y)
	//CurPoint.y = Index_Col*lHeight_N+Index_Col2*lHeight_NN;
	//CurPoint.x = Index_Row*lWidth_N+Index_Row2*lWidth_NN;
	//resResDS.Pixel2World(CurPoint.x, CurPoint.y, &dblX, &dblY);
	//pt.setX(dblX);
	//pt.setY(dblY);
	//pRing->addPoint(&pt);

	////(x, y+1)
	//CurPoint.y = Index_Col*lHeight_N+(Index_Col2+1)*lHeight_NN;
	//CurPoint.x = Index_Row*lWidth_N+Index_Row2*lWidth_NN;
	//resResDS.Pixel2World(CurPoint.x, CurPoint.y, &dblX, &dblY);
	//pt.setX(dblX);
	//pt.setY(dblY);
	//pRing->addPoint(&pt);

	////(x+1, y+1)
	//CurPoint.y = Index_Col*lHeight_N+(Index_Col2+1)*lHeight_NN;
	//CurPoint.x = Index_Row*lWidth_N+(Index_Row2+1)*lWidth_NN;
	//resResDS.Pixel2World(CurPoint.x, CurPoint.y, &dblX, &dblY);
	//pt.setX(dblX);
	//pt.setY(dblY);
	//pRing->addPoint(&pt);
	//
	////(x+1, y)
	//CurPoint.y = Index_Col*lHeight_N+Index_Col2*lHeight_NN;
	//CurPoint.x = Index_Row*lWidth_N+(Index_Row2+1)*lWidth_NN;
	//resResDS.Pixel2World(CurPoint.x, CurPoint.y, &dblX, &dblY);
	//pt.setX(dblX);
	//pt.setY(dblY);
	//pRing->addPoint(&pt);

	////(x,y)
	//CurPoint.y = Index_Col*lHeight_N+Index_Col2*lHeight_NN;
	//CurPoint.x = Index_Row*lWidth_N+Index_Row2*lWidth_NN;
	//resResDS.Pixel2World(CurPoint.x, CurPoint.y, &dblX, &dblY);
	//pt.setX(dblX);
	//pt.setY(dblY);
	//pRing->addPoint(&pt);

	//OGRFeature* pNewF=new OGRFeature(m_poFeatureDS->m_DataSource->GetLayer(0)->GetLayerDefn());
	//ppoly->addRingDirectly(pRing);
	//pNewF->SetGeometryDirectly(ppoly);
	//m_poFeatureDS->CreatNewFeature(0, pNewF);

	//delete ppoly;
	//delete pRing;

	return flag;
}


//计算图像指定区域的直方图特征向量，在第一次检测结果上进行第二次检测
//lIndexBand	图像的波段
//Num			图像分割为Num*Num块	
//nIndexBlock	图像分割后，要计算直方图特征向量的区域标号
//nIndex		二次图像检测中图像块的编号
//*Vector		图像直方图特征向量， 向量默认长度为256，类型为float
bool ImgChangeDetect::Detect_Hist2(long lIndexBand, int Num, int nIndexBlock, int nIndexSubBlock, float* Vector)
{
	bool	flag=false;
	//BYTE	byValue = 0;
	//int     i, j;
	//int 	Index_Col, Index_Row;
	//int		Index_Col2, Index_Row2;
	//int		Block_Density[256];
	//long    lWidth_n,lHeight_n;
	//long 	lWidth_nn,lHeight_nn;
	//
	//memset(Block_Density, 0, sizeof(Block_Density));

	////多光谱影像
	//rasSrcDS.GetBandDataType(lIndexBand, &lDataType);
	//
	//lWidth_n   = lWidth/Num;
	//lHeight_n  = lHeight/Num;
	//lWidth_nn  = lWidth/(Num*Num);
	//lHeight_nn = lHeight/(Num*Num);

	//Index_Col  = nIndexBlock/Num;
	//Index_Row  = nIndexBlock%Num;
	//Index_Col2 = nIndexSubBlock/Num;	//检测图象的第二次定位列
	//Index_Row2 = nIndexSubBlock%Num;	//检测图象的第二次定位行

	//for(j=Index_Col*lHeight_n+Index_Col2*lHeight_nn; j<Index_Col*lHeight_n+(Index_Col2+1)*lHeight_nn; j++)
	//	for(i=Index_Row*lWidth_n+Index_Row2*lWidth_nn; i<Index_Row*lWidth_n+(Index_Row2+1)*lWidth_nn; i++)
	//	{
	//		
	//		if(!rasSrcDS.PixelIO(lIndexBand, i+1, j+1, &byValue, true))
	//			byValue = 0;
	//		if(m_nDealImage==2)//表示正在处理的是目标图像，需要进行灰度差分弥合（即消除同源图像在不同环境下的差别）
	//		{
	//			byValue += m_nAverGrayDiff;
	//			if(byValue>255)
	//				byValue = 255;
	//			if(byValue<0)
	//				byValue = 0;
	//		}
	//		Block_Density[byValue]++;
	//	}//for i
	//for(i=0; i<256; i++)
	//	{
	//		Vector[i] = (float)Block_Density[i]/(float)(lWidth_nn*lHeight_nn);
	//	}//for i
	
	flag = true;
	return flag;
}

//计算图像指定区域的颜色矩特征向量，在第一次检测结果上进行第二次检测
//lIndexBand	图像的波段
//Num			图像分割为Num*Num块	
//nIndexBlock	图像分割后，要计算颜色矩特征向量的区域标号
//nIndexSubBlock	二次图像检测中图像块的编号
//*Vector		图像直方图特征向量， 向量默认长度为3，类型为float
bool ImgChangeDetect::Detect_ColorMatix2(long lIndexBand, int Num, int nIndexBlock, int nIndexSubBlock, float* Vector)
{
	bool	flag=false;
	
	//int     i, j;
	//int 	Index_Col, Index_Row;
	//int		Index_Col2, Index_Row2;
	//long    lWidth_n,lHeight_n;
	//long 	lWidth_nn,lHeight_nn;
	//float	Block_Density[3];

	////多光谱影像
	//rasSrcDS.GetBandDataType(lIndexBand, &lDataType);
	//
	//lWidth_n   = lWidth/Num;
	//lHeight_n  = lHeight/Num;
	//lWidth_nn  = lWidth/(Num*Num);
	//lHeight_nn = lHeight/(Num*Num);

	//Index_Col  = nIndexBlock/Num;
	//Index_Row  = nIndexBlock%Num;
	//Index_Col2 = nIndexSubBlock/Num;	//检测图象的第二次定位列
	//Index_Row2 = nIndexSubBlock%Num;	//检测图象的第二次定位行
	//
	//unsigned char byValue = 0;
	//unsigned char *temp1 = new unsigned char[lWidth_nn*lHeight_nn];
	//if(temp1==NULL)
	//{
	//	return false;
	//}
	//memset(Block_Density, 0, sizeof(Block_Density));

	//int m, n;

	//m=n=0;
	//for(j=Index_Col*lHeight_n+Index_Col2*lHeight_nn; j<Index_Col*lHeight_n+(Index_Col2+1)*lHeight_nn; j++)
	//{
	//	n=0;
	//	for(i=Index_Row*lWidth_n+Index_Row2*lWidth_nn; i<Index_Row*lWidth_n+(Index_Row2+1)*lWidth_nn; i++)
	//	{
	//		
	//		if(!rasSrcDS.PixelIO(lIndexBand, i+1, j+1, &byValue, true))
	//			byValue = 0;
	//		if(m_nDealImage==2)//表示正在处理的是目标图像，需要进行灰度差分弥合（即消除同源图像在不同环境下的差别）
	//		{
	//			byValue += m_nAverGrayDiff;
	//			if(byValue>255)
	//				byValue = 255;
	//			if(byValue<0)
	//				byValue = 0;
	//		}
	//
	//		temp1[m*lWidth_nn+n] = byValue;
	//		n++;
	//	}//for i
	//	m++;
	//}//for j
	////计算图像块的一阶矩
	////分量的一阶矩为各个分量的平均值
	//float sum_temp=0.0f;
	//float index_pow;

	//for(i=0; i<lHeight_nn; i++)
	//	for(j=0; j<lWidth_nn; j++)
	//	{
	//		sum_temp += (float)temp1[i*lWidth_nn+j];
	//	}//for j 
	//Block_Density[0] = sum_temp/(float)(lHeight_nn*lWidth_nn);	

	////计算图像块的二阶矩
	//sum_temp = 0.0f;
	//for(i=0; i<lHeight_nn; i++)
	//	for(j=0; j<lWidth_nn; j++)
	//	{
	//		float temp;
	//		
	//		//取得图像块的像素信息
	//		temp = (float)temp1[i*lWidth_nn+j];
	//		temp = Block_Density[0]-temp;
	//		sum_temp += (float)pow(temp, 2);
	//
	//	}//for j
	//sum_temp = sum_temp/(float)(lHeight_nn*lWidth_nn);
	//Block_Density[1] = (float)sqrt(sum_temp);

	////计算图像块的三阶矩
	//sum_temp = 0.0f;
	//index_pow = 0.33333f;
 //   for(i=0; i<lHeight_nn; i++)
	//	for(j=0; j<lWidth_nn; j++)
	//	{
	//		float temp;
	//		
	//		//取得图像块的像素信息
	//		temp = (float)temp1[i*lWidth_nn+j];
	//		temp = Block_Density[1]-temp;
	//		sum_temp += fabs((float)pow(temp, 3));
	//	}//for j
	//sum_temp = sum_temp/(float)(lHeight_nn*lWidth_nn);
	//Block_Density[2] = (float)pow(sum_temp, index_pow);

	//for(i=0; i<3; i++)
	//{
	//	Vector[i] = Block_Density[i];
	//}//for i

	//delete []temp1;	

	flag = true;
	return flag;
}

//计算图像指定区域的纹理谱特征向量，在第一次检测结果上进行第二次检测
//lIndexBand	图像的波段
//Num			图像分割为Num*Num块	
//nIndexBlock	图像分割后，要计算纹理谱特征向量的区域标号
//nIndexSubBlock	二次图像检测中图像块的编号
//*Vector		图像直方图特征向量， 向量默认长度为256，类型为float
bool ImgChangeDetect::Detect_TextureChart2(long lIndexBand, int Num, int nIndexBlock, int nIndexSubBlock, float* Vector)
{
	//const int THRESHOLD=8; //象素点与其邻接点之间进行比较的阈值

	//bool    flag=false;
	//BYTE	byValue = 0;
	//LPBYTE	temp1;
	//int     i, j;
	//int 	Index_Col, Index_Row;
	//int		Index_Col2, Index_Row2;
	//int     border[8];
	//long    stat[256];  //图像纹理谱特征向量
	//long    lWidth_n,lHeight_n;
	//long 	lWidth_nn,lHeight_nn;
	//float	Block_Density[3];

	//memset(Block_Density, 0, sizeof(Block_Density));

	////多光谱影像
	//rasSrcDS.GetBandDataType(lIndexBand, &lDataType);
	//
	//lWidth_n   = lWidth/Num;
	//lHeight_n  = lHeight/Num;
	//lWidth_nn  = lWidth/(Num*Num);
	//lHeight_nn = lHeight/(Num*Num);

	//Index_Col  = nIndexBlock/Num;
	//Index_Row  = nIndexBlock%Num;
	//Index_Col2 = nIndexSubBlock/Num;	//检测图象的第二次定位列
	//Index_Row2 = nIndexSubBlock%Num;	//检测图象的第二次定位行

	////取得图像指定块的像素信息
	//temp1 = new BYTE[lWidth_nn*lHeight_nn];
	//int m,n;
	//m=n=0;
	//for(j=Index_Col*lHeight_n+Index_Col2*lHeight_nn; j<Index_Col*lHeight_n+(Index_Col2+1)*lHeight_nn; j++)
	//{
	//	n=0;
	//	for(i=Index_Row*lWidth_n+Index_Row2*lWidth_nn; i<Index_Row*lWidth_n+(Index_Row2+1)*lWidth_nn; i++)
	//	{
	//		
	//		if(!rasSrcDS.PixelIO(lIndexBand, i+1, j+1, &byValue, true))
	//			byValue = 0;
	//		if(m_nDealImage==2)//表示正在处理的是目标图像，需要进行灰度差分弥合（即消除同源图像在不同环境下的差别）
	//		{
	//			byValue += m_nAverGrayDiff;
	//			if(byValue>255)
	//				byValue = 255;
	//			if(byValue<0)
	//				byValue = 0;
	//		}
	//
	//		temp1[m*lWidth_nn+n] = byValue;
	//		n++;
	//	}//for i
	//	m++;
	//}//for j
	//memset(stat, 0, sizeof(stat));
	//for(j=1; j<lHeight_nn-1; j++)
	//{
	//	for(i=1; i<lWidth_nn-1; i++)
	//	{
	//		///计算某象素点的八个邻接点的相对灰阶关系
	//		int sum=0;
	//		int difference; 
	//		int border_point;
	//		int center_point = temp1[j*lWidth_nn+i];
	//		 
	//		//first
	//		border_point = temp1[(j-1)*lWidth_nn+(i-1)];
	//		difference = abs(border_point-center_point);
	//		if(difference<THRESHOLD)
	//			border[0] = 1;
	//		else
	//			border[0] = 0; 
	//		
	//		//second
	//		border_point = temp1[(j-1)*lWidth_nn+i];
	//		difference = abs(border_point-center_point);
	//		if(difference<THRESHOLD)
	//			border[1] = 1;
	//		else
	//			border[1] = 0; 
	//		
	//		//third
	//		border_point = temp1[(j-1)*lWidth_nn+(i+1)];
	//		difference = abs(border_point-center_point);
	//		if(difference<THRESHOLD)
	//			border[2] = 1;
	//		else
	//			border[2] = 0; 
	//		
	//		//forth
	//		border_point = temp1[j*lWidth_nn+(i-1)];
	//		difference = abs(border_point-center_point);
	//		if(difference<THRESHOLD)
	//			border[3] = 1;
	//		else
	//			border[3] = 0;
	//		
	//		//fifth
	//		border_point = temp1[(j)*lWidth_nn+(i+1)];
	//		difference = abs(border_point-center_point);
	//		if(difference<THRESHOLD)
	//			border[4] = 1;
	//		else
	//			border[4] = 0;
	//		
	//		//sixth
	//		border_point = temp1[(j+1)*lWidth_nn+(i-1)];
	//		difference = abs(border_point-center_point);
	//		if(difference<THRESHOLD)
	//			border[5] = 1;
	//		else
	//			border[5] = 0;
	//		
	//		//seventh
	//		border_point = temp1[(j+1)*lWidth_nn+(i)];
	//		difference = abs(border_point-center_point);
	//		if(difference<THRESHOLD)
	//			border[6] = 1;
	//		else
	//			border[6] = 0;
	//		
	//		//eighth
	//		border_point = temp1[(j+1)*lWidth_nn+(i+1)];
	//		difference = abs(border_point-center_point);
	//		if(difference<THRESHOLD)
	//			border[7] = 1;
	//		else
	//			border[7] = 0;
	//	
	//		///根据八个邻接点的相对灰度关系，统计纹理单元的发生频数
	//		for(int k=0; k<8; k++)
	//		{
	//			sum += (int)pow(2.0f, k)*border[k];
	//		}//for k
	//		///统计频率
	//		stat[sum]++;
	//	}//for j
	//}//for i 

	////对特征向量进行归一化
	//long sum=0;
	//for(i=0; i<256; i++)
	//{
	//	sum += stat[i];
	//}// for i
	//for(i=0; i<256; i++)
	//{
	//	Vector[i] = (float)stat[i]/(float)sum;
	//}//for i

	//flag = true;
	//return flag;

    return false;
}


//计算图像指定区域的共生矩阵特征向量，进行第一次检测
//lIndexBand	图像的波段
//Num			图像分割为Num*Num块	
//nIndexBlock	图像分割后，要计算纹理谱特征向量的区域标号
//*Vector		图像共生矩阵特征向量， 向量默认长度为5，类型为float
bool ImgChangeDetect::Detect_Adjoint(long lIndexBand, int Num, int nIndexBlock, float* Vector)
{
	//const int N=255, COLUMN=32, ROW=32;//共生矩阵的行，列

	//bool    flag=false;
	//BYTE	byValue = 0;
	//LPBYTE	temp1;
	//int     i,j;
	//int 	Index_Col, Index_Row;
	//long    lWidth_N,lHeight_N;
	//long    Density_0[COLUMN][ROW];//  0度方向的共生矩阵
	//long    Density_1[COLUMN][ROW];// 45度方向的共生矩阵
	//long    Density_2[COLUMN][ROW];// 90度方向的共生矩阵
	//long    Density_3[COLUMN][ROW];//135度方向的共生矩阵
	//float   Adjoint_Result[5];    //用于存储图像共生矩阵二次统计的特征值
	//float   Density[COLUMN][ROW];
	//
	//lWidth_N  = lWidth/Num;
	//lHeight_N = lHeight/Num;
	//Index_Col = nIndexBlock/Num;
	//Index_Row = nIndexBlock%Num;

	////得到需要处理的图像分块，多光谱影像
	//rasSrcDS.GetBandDataType(lIndexBand, &lDataType);
	//temp1 = new BYTE[lHeight_N*lWidth_N];

	////取得图像指定块的像素信息
	//for(j=Index_Col*lHeight_N; j<(Index_Col+1)*lHeight_N; j++)
	//	for(i=Index_Row*lWidth_N; i<(Index_Row+1)*lWidth_N; i++)
	//	{
	//		if(!rasSrcDS.PixelIO(lIndexBand, i+1, j+1, &byValue, true))
	//			byValue = 0;
	//		
	//			temp1[j*lWidth_N+i] = byValue;	
	//	}//for i
	//

	////初始化共生矩阵的密度统计数组
	//for(i=0; i<COLUMN; i++)
	//	for(j=0; j<ROW; j++)
	//	{
	//		Density[i][j] = 0.0f;
	//		Density_0[i][j] = 0;
	//		Density_1[i][j] = 0;
	//		Density_2[i][j] = 0;
	//		Density_3[i][j] = 0;
	//	}//for j
 //  
	////计算0度方向的共生矩阵
	//for(j=0; j<lHeight_N; j++)
	//	for(i=0; i<lHeight_N-1; i++)
	//		{
	//			int a1 = temp1[j*lWidth_N+i];
	//			int a2 = temp1[j*lWidth_N+(i+1)];
	//			a1 = a1/8;
	//			a2 = a2/8;
	//			Density_0[a1][a2]++;
	//		}//for j

	////计算45度方向的共生矩阵
	//for(j=0; j<lHeight_N-1; j++)
	//	for(i=0; i<lWidth_N-1; i++)
	//		{
	//			int a1 = temp1[j*lWidth_N+i];
	//			if((i+1)>lWidth_N || (j+1)>lHeight_N)
	//			{
	//				continue;
	//			}
	//			int a2 = temp1[(j+1)*lWidth_N+(i+1)];
	//			a1 = a1/8;
	//			a2 = a2/8;
	//			Density_1[a1][a2]++;
	//		}//for j

	////计算90度方向的共生矩阵
	//for(j=0; j<lHeight_N-1; j++)
	//	for(i=0; i<lWidth_N; i++)
	//		{
	//			int a1 = temp1[j*lWidth_N+i];
	//			int a2 = temp1[(j+1)*lWidth_N+i];
	//			a1 = a1/8;
	//			a2 = a2/8;
	//			Density_2[a1][a2]++;
	//		}//for j

	////计算135度方向的共生矩阵
	//for(j=0; j<lHeight_N-1; j++)
	//	for(i=1; i<lWidth_N; i++)
	//		{
	//			int a1 = temp1[j*lWidth_N+i];
	//			int a2 = temp1[(j+1)*lWidth_N+(i-1)];
	//			a1 = a1/8;
	//			a2 = a2/8;
	//			Density_3[a1][a2]++;
	//		}//for j

	////融合四个方向的共生矩阵为一个
	//float max_density;

	//max_density = Density[0][0];
	//for(i=0; i<COLUMN; i++)
	//	for(j=0; j<ROW; j++)
	//	{ 
	//		float temp=0;
	//		temp = Density_0[i][j] + Density_1[i][j] + Density_2[i][j] + Density_3[i][j];// 四个方向的融合
	//		Density[i][j] = temp/4;
	//		if(max_density<Density[i][j])
	//		{
	//			max_density = Density[i][j];//找到共生矩阵中密度的最大值，供共生矩阵归一化使用
	//		}
	//	}//for 

	////对共生矩阵进行归一化
	//float Density_Unity[COLUMN][ROW];
	//memset(Density_Unity, 0, sizeof(float)*COLUMN*ROW);
	//int count1=0,count2=0;
	//for(i=0; i<COLUMN; i++)
	//	for(j=0; j<ROW; j++)
	//	{
	//		if(Density[i][j]>0)
	//		{
	//			count2++;
	//		}
	//		Density_Unity[i][j] = (float)Density[i][j]/(float)max_density;
	//		if(Density_Unity[i][j]>0.0)
	//		{
	//			count1++;
	//		}
	//	}

	//////开始计算共生矩阵的特征值
	////初始化共生矩阵特征值
	//for(i=0; i<5; i++)
	//	{
	//		Adjoint_Result[i] = 0.0f;
	//	}
	//
	////计算图像共生矩阵的对比度（主对角线惯性矩）
	////它的大小反映了整个图像的灰度变化情况。如果其值越大，则该图像像素间的灰度差异越大，
	////视觉效果就越好，即对应细纹理。
	////数组Adjoint_Result[0]用来存储共生矩阵的融合方向的对比度特征值
	//for(int n=0; n<N; n++)
	//{
	//	float n_2=0.0f, sum=0.0f;
	//	for(int i=0; i<COLUMN; i++)
	//	{
	//		if((i-n)<0 || (i+n)>32)
	//			continue;
	//		if((i-n)>=0)
	//			j = i-n;
	//		sum += Density_Unity[i][j];
	//		if((i+n)<=32)
	//			j = i+n;
	//		sum += Density_Unity[i][j];
	//	
	//	}//for i
	//	
	//	n_2 = pow((float)n, 2);
	//	Adjoint_Result[0] += n_2*sum;/////计算结果特征值：共生矩阵对比度
	//}//for n


	////计算图像共生矩阵的差熵
	////代表了整个图像区域内灰度变化的复杂度。图像的灰度变化越是没有规则，该值就越大。
	////数组Adjoint_Result[1]用来存储共生矩阵的融合方向的差熵特征值
	//for(i=0; i<COLUMN; i++)
	//	for(j=0; j<ROW; j++)
	//	{
	//		if(Density_Unity[i][j]<=0.0f)
	//			continue;
	//		Adjoint_Result[1] += Density_Unity[i][j]*(log10((Density_Unity[i][j])/log10(2.0)));
	//	}//for j
	//Adjoint_Result[1] = -Adjoint_Result[1];/////计算结果特征值：共生矩阵差熵

	////计算图像共生矩阵的能量(或称为角二阶矩)
	////它是一种对图像灰度分布均匀性的度量，当图像灰度分布比较均匀时，其值越大。
	////数组Adjoint_Result[2]用来存储共生矩阵的融合方向的能量特征值
	//for(i=0; i<COLUMN; i++)
	//	for(j=0; j<ROW; j++)
	//	{
	//		Adjoint_Result[2] += pow(Density_Unity[i][j], 2);/////计算结果特征值：共生矩阵能量
	//	}//for j

	////计算图像共生矩阵的相关
	////相关量是用来描述矩阵中行或列元素之间相似程度的，它是灰度线性关系的度量。
	////数组Adjoint_Result[3]用来存储共生矩阵的融合方向的相关特征值
	//float columnave, rowave, columndif, rowdif;
	//float column_ave[COLUMN], row_ave[ROW];
	//float column_dif[COLUMN], row_dif[ROW];

	////初始化
	//for(i=0; i<COLUMN; i++)
	//{
	//	column_ave[i] = 0;
	//	column_dif[i] = 0;
	//	row_ave[i] = 0;
	//	row_dif[i] = 0;
	//}//for i

	//for(i=0; i<COLUMN; i++)
	//{
	//	for(j=0; j<ROW; j++)
	//	{
	//		column_ave[i] += Density_Unity[i][j];
	//		row_ave[j] += Density_Unity[i][j];
	//	}//for j
	//}//for i
	//float sum_temp1=0, sum_temp2=0; 
	//for(i=0; i<COLUMN; i++)
	//{
	//	sum_temp1 += column_ave[i];
	//	sum_temp2 += row_ave[i];
	//}
	//columnave = sum_temp1/32;	//各个列的均值
	//rowave = sum_temp2/32;		//各个行的均值

	//float sum_temp3=0, sum_temp4=0;
	//for(i=0; i<COLUMN; i++)
	//{
	//	sum_temp3 += fabs(columnave-column_ave[i]);
	//	sum_temp4 += fabs(rowave-row_ave[i]);
	//}//for i
	//columndif = sum_temp3/32;	//各个列的标准差
	//rowdif = sum_temp4/32;		//各个列的行准差

	//float sum_temp5=0.0f;
	//for(i=0; i<COLUMN; i++)
	//	for(j=0; j<ROW; j++)
	//	{
	//		sum_temp5 += i*j*Density_Unity[i][j];
	//	}//for j
	//Adjoint_Result[3] = (sum_temp5 - columnave*rowave)/(columndif*rowdif);/////计算结果特征值：共生矩阵能量

	////计算图像共生矩阵的逆方差
	////相关量是用来描述矩阵中行或列元素之间相似程度的，它是灰度线性关系的度量。
	////数组Adjoint_Result[4]用来存储共生矩阵的融合方向的逆方差特征值
	//for(i=0; i<COLUMN; i++)
	//	for(j=0; j<ROW; j++)
	//	{
	//		Adjoint_Result[4] += Density_Unity[i][j]/(1+pow((float)(i-j), 2));/////计算结果特征值：共生矩阵能量
	//	}//for j

	////CString Output;
	////Output.Format("%10.3f, %10.3f, %10.3f, %10.3f", Adjoint_Result[0], Adjoint_Result[1],Adjoint_Result[2],Adjoint_Result[3], Adjoint_Result[4]);
	////AfxMessageBox(Output);
	//for(i=0; i<5; i++)
	//{
	//	Vector[i] = Adjoint_Result[i];
	//}

	//flag = true;
	//return flag;

    return false;

}

//用户裁切指定图像区域，对裁切区域进行直方图方式变换检测，LQ
bool ImgChangeDetect::GetDetectArea_Hist(const char* detectfile_sc, const char* detectfile_ds, const char* detectfile_rs, STExtent scope)
{
	bool flag=false;

	/*if(strcmp(detectfile_sc, "")==0 || strcmp(detectfile_ds, "")==0)
		return flag;
	
	CRasterDS  rsTemp;
	float      threshold;
	double     dblCellX, dblCellY;
	long       lSampleType, lBandIndex, lBandNum;
	char*      detectfile_sc_temp;
	char*      detectfile_ds_temp; 
	
	threshold = 0.9f;
	rsTemp.Open(detectfile_sc);
	rsTemp.GetCellSize(&dblCellX, &dblCellY);
	rsTemp.GetBandCount(&lChannelCount);
	rsTemp.Close();
	detectfile_sc_temp = "C:\\imagedetect_temp_sc.tif";
	ImgClip(detectfile_sc, detectfile_sc_temp, scope, dblCellX, dblCellY, 1, &lChannelCount, 1);

	rsTemp.Open(detectfile_ds);
	rsTemp.GetCellSize(&dblCellX, &dblCellY);
	rsTemp.GetBandCount(&lChannelCount);
	rsTemp.Close();
	detectfile_ds_temp = "C:\\imagedetect_temp_ds.tif";
	ImgClip(detectfile_ds, detectfile_ds_temp, scope, dblCellX, dblCellY, 1, &lChannelCount, 1);
	
	ImgDetect_Hist(detectfile_sc_temp, detectfile_ds_temp, detectfile_rs, threshold, pfnProgress);

	DeleteFile((LPCTSTR)detectfile_sc_temp);
	DeleteFile((LPCTSTR)detectfile_ds_temp);*/

	return true;
}

//用户裁切指定图像区域，对裁切区域进行对象级图像变换检测，LQ
bool ImgChangeDetect::GetDetectArea_Object(const char* detectfile_sc, const char* detectfile_ds, STExtent scope)
{
	bool flag=false;

	/*if(strcmp(detectfile_sc, "")==0 || strcmp(detectfile_ds, "")==0)
		return flag;
	
	CRasterDS  rsTemp;
	float      threshold;
	double     dblCellX, dblCellY;
	long       lSampleType, lBandIndex, lBandNum;
	char*      detectfile_sc_temp;
	char*      detectfile_ds_temp; 
	
	threshold = 0.1f;
	rsTemp.Open(detectfile_sc);
	rsTemp.GetCellSize(&dblCellX, &dblCellY);
	rsTemp.GetBandCount(&lChannelCount);
	rsTemp.Close();
	detectfile_sc_temp = "C:\\imagedetect_temp_sc.tif";
	flag = ImgClip(detectfile_sc, detectfile_sc_temp, scope, dblCellX, dblCellY, 1, &lChannelCount, 1);
	if (flag ==false)
	{
		return flag;
	}

	rsTemp.Open(detectfile_ds);
	rsTemp.GetCellSize(&dblCellX, &dblCellY);
	rsTemp.GetBandCount(&lChannelCount);
	rsTemp.Close();
	detectfile_ds_temp = "C:\\imagedetect_temp_ds.tif";
	flag = ImgClip(detectfile_ds, detectfile_ds_temp, scope, dblCellX, dblCellY, 1, &lChannelCount, 1);*/
	
	return true;
}

//功能：用于计算两幅图像之间灰度变化分布。计算两幅图像灰度变化的平均差值，用平均差值来消除同源图像
//在不同环境（光照等）下的成像差别
//ImageFileName_Src  用于传入原图像信息
//ImageFileName_Dest 用于传入目标图像信息
//返回值为两副图像灰度的平均差值，可用来平衡图像间的差异
int ImgChangeDetect::CalAverGrayDiff(const char* ImageFileName_Src, const char* ImageFileName_Dest)
{
	int result=-1;
	//if(strcmp(ImageFileName_Src,"")==0 || strcmp(ImageFileName_Dest,"")==0)
	//	return result;

	//int  i,j;
	//int  nSam_w1, nSam_w2; 
	//int  nSam_h1, nSam_h2;
	//long nWide1, nHeight1;
	//long nWide2, nHeight2;
	//CRasterDS raster_sc;
	//CRasterDS raster_ds;
	//vector<int> samlpe_pixel_list1;
	//vector<int> samlpe_pixel_list2;
	//
	//if(!raster_sc.Open(ImageFileName_Src))
	//	return result;
	//if(!raster_ds.Open(ImageFileName_Dest))
	//	return result;

	//raster_sc.GetSize(&nWide1,&nHeight1);
	//raster_sc.CreateBuffer();
	//raster_ds.GetSize(&nWide2,&nHeight2);
	//raster_ds.CreateBuffer();

	//samlpe_pixel_list1.clear();
	//samlpe_pixel_list2.clear();
	//if(nWide1*nHeight1<10000 || nWide2*nHeight2<10000)//图像规格小于100*100，不进行采样
	//{
	//	raster_sc.DeleteBuffer();
	//	raster_sc.Close();
	//	raster_ds.DeleteBuffer();
	//	raster_ds.Close();

	//	return 0;
	//}
	//else if(nWide1*nHeight1<1000000 || nWide2*nHeight2<1000000)//图像规格小于1000*1000，大于100*100；采样50*50个像素
	//{
	//	BYTE  value=0;
	//	int* vector;

	//	///对图像进行像素采样
	//	nSam_w1 = nWide1/50;
	//	nSam_w2 = nWide2/50;
	//	nSam_h1 = nHeight1/50;
	//	nSam_h2 = nHeight2/50;

	//	for(i=0; i<50; i++)
	//		for(j=0; j<50; j++)
	//		{
	//			raster_sc.PixelIO(1, (j*nSam_h1)+1, (i*nSam_w1)+1, &value, true);
	//			samlpe_pixel_list1.push_back((int)value);

	//		}//for j
	//	
	//	for(i=0; i<50; i++)
	//		for(j=0; j<50; j++)
	//		{
	//			raster_ds.PixelIO(1, (j*nSam_h2)+1, (i*nSam_w2)+1, &value, true);
	//			samlpe_pixel_list2.push_back((int)value);
	//		}//for j
	//	
	//	///分析采样像素差分分布
	//	vector = (int*)malloc(sizeof(int)*2500);
	//	if(vector==NULL)
	//	{
	//		raster_sc.DeleteBuffer();
	//		raster_sc.Close();
	//		raster_ds.DeleteBuffer();
	//		raster_ds.Close();

	//		return -1;
	//	}
	//	int sum=0;
	//	memset(vector, 0, sizeof(int)*2500);
	//	for(i=0; i<2500; i++)
	//	{
	//		vector[i] = samlpe_pixel_list1[i] - samlpe_pixel_list2[i]; 
	//		sum +=vector[i];
	//	}//for i
	//	result = sum/2500;
	///*
	//	///计算向量
	//	result = GetDiffValue(vector, 2500);
	//*/
	//	free(vector);
	//}
	//else	//图像规格大于1000*1000，采样200*200个像素点
	//{
	//	BYTE  value=0;
	//	int* vector;

	//	///对图像进行像素采样
	//	nSam_w1 = nWide1/200;
	//	nSam_w2 = nWide2/200;
	//	nSam_h1 = nHeight1/200;
	//	nSam_h2 = nHeight2/200;

	//	for(i=0; i<200; i++)
	//		for(j=0; j<200; j++)
	//		{
	//			raster_sc.PixelIO(1, (j*nSam_h1)+1, (i*nSam_w1)+1, &value, true);
	//			
	//			samlpe_pixel_list1.push_back((int)value);

	//		}//for j
	//
	//	for(i=0; i<200; i++)
	//		for(j=0; j<200; j++)
	//		{
	//			raster_ds.PixelIO(1, (j*nSam_h2)+1, (i*nSam_w2)+1, &value, true);
	//			samlpe_pixel_list2.push_back((int)value);
	//		}//for j

	//	///分析采样像素差分分布
	//	vector = (int*)malloc(sizeof(int)*40000);
	//	if(vector==NULL)
	//	{
	//		raster_sc.DeleteBuffer();
	//		raster_sc.Close();
	//		raster_ds.DeleteBuffer();
	//		raster_ds.Close();

	//		return -1;
	//	}
	//	memset(vector, 0, sizeof(int)*40000);
	//	int sum=0;
	//	for(i=0; i<40000; i++)
	//	{
	//		vector[i] = samlpe_pixel_list1[i] - samlpe_pixel_list2[i]; 
	//		sum += vector[i];
	//	}//for i

	//	result = sum/40000;
	///*
	//	///计算向量
	//	result = GetDiffValue(vector, 40000);
	//*/
	//	free(vector);
	//	vector = NULL;
	//}
	//samlpe_pixel_list1.erase(samlpe_pixel_list1.begin(), samlpe_pixel_list1.end());
	//samlpe_pixel_list2.erase(samlpe_pixel_list2.begin(), samlpe_pixel_list2.end());

	//raster_sc.DeleteBuffer();
	//raster_sc.Close();
	//raster_ds.DeleteBuffer();
	//raster_ds.Close();

	return result;

}

int ImgChangeDetect::CalAverGrayDiff2(const char* ImageFileName_Src, const char* ImageFileName_Dest)
{
	int result=-1;
	//if(strcmp(ImageFileName_Src,"")==0 || strcmp(ImageFileName_Dest,"")==0)
	//	return result;

	//BYTE  value=0;
	//int* vector;
	//int  i,j;
	//long nWide1, nHeight1;
	//long nWide2, nHeight2;
	//CRasterDS raster_sc;
	//CRasterDS raster_ds;

	//std::vector<int> samlpe_pixel_list1;
	//std::vector<int> samlpe_pixel_list2;
	//
	//if(!raster_sc.Open(ImageFileName_Src))
	//	return result;
	//if(!raster_ds.Open(ImageFileName_Dest))
	//	return result;

	//raster_sc.GetSize(&nWide1,&nHeight1);
	//raster_sc.CreateBuffer();
	//raster_ds.GetSize(&nWide2,&nHeight2);
	//raster_ds.CreateBuffer();

	//if(nWide1!=nWide2 || nHeight1!= nHeight2)
	//{
	//	return -1;
	//}
	//samlpe_pixel_list1.clear();
	//samlpe_pixel_list2.clear();

	//

	//for(i=0; i<nHeight1; i++)
	//	for(j=0; j<nWide1; j++)
	//	{
	//		raster_sc.PixelIO(1, j+1, i+1, &value, true);
	//		samlpe_pixel_list1.push_back((int)value);

	//	}//for j
	//
	//for(i=0; i<nHeight2; i++)
	//	for(j=0; j<nWide2; j++)
	//	{
	//		raster_ds.PixelIO(1, j+1, i+1, &value, true);
	//		samlpe_pixel_list2.push_back((int)value);
	//	}//for j
	//	
	/////分析采样像素差分分布
	//vector = (int*)malloc(sizeof(int)*nWide1*nHeight1);
	//if(vector==NULL)
	//{
	//	raster_sc.DeleteBuffer();
	//	raster_sc.Close();
	//	raster_ds.DeleteBuffer();
	//	raster_ds.Close();

	//	return -1;
	//}
	//int sum=0;
	//memset(vector, 0, sizeof(int)*nWide1*nHeight1);
	//for(i=0; i<nWide1*nHeight1; i++)
	//{
	//	vector[i] = samlpe_pixel_list1[i] - samlpe_pixel_list2[i]; 
	//	sum +=vector[i];
	//}//for i
	//result = sum/(nWide1*nHeight1);
	//
	//free(vector);
	//
	//samlpe_pixel_list1.erase(samlpe_pixel_list1.begin(), samlpe_pixel_list1.end());
	//samlpe_pixel_list2.erase(samlpe_pixel_list2.begin(), samlpe_pixel_list2.end());

	//raster_sc.DeleteBuffer();
	//raster_sc.Close();
	//raster_ds.DeleteBuffer();
	//raster_ds.Close();

	return result;
}


//计算向量的二次平均差值，LQ
int ImgChangeDetect::GetDiffValue(int* Vector, int length)
{
	int result=-1;

	//if(NULL==Vector || 0==length)
	//	return result;
	//
	//int i;
	//int aver, sum=0;
	//int* aver_vector;

	//for(i=0; i<length; i++)
	//{
	//	sum += Vector[i];
	//}//for i
	//aver = sum/length;

	//aver_vector = (int*)malloc(sizeof(int)*length);
	//if(aver_vector==NULL)
	//{
	//	return result;
	//}
	//sum = 0;
	//for(i=0; i<length; i++)
	//{
	//	aver_vector[i] = abs(Vector[i] - aver);
	//	sum += aver_vector[i];
	//}
	//result = sum/length;

	//free(aver_vector);
	//aver_vector = NULL;

	return result;
}

//得到矢量数组中的区域极值,用于基于灰度分布统计划分图像背景区域,LQ
//方法：先对向量进行均衡化（保证数据趋势一致），然后对向量中的数据进行邻接相减，
//      根据相减向量的数据分布取得数据鞍型底部，判断是否为区域极值。
//vector 输入矢量数组
//length 数组长度
//返回值为flag 表示数组极值的索引
int ImgChangeDetect::GetExtremum1(float* vector, int length)
{
	int flag=-1;
	if(NULL==vector || length<1)
		return flag;

	int i;
	int state;
	float* temp_vector;

	temp_vector = (float*)malloc(sizeof(float)*length);
	if(temp_vector==NULL)
	{
		return flag;
	}
	
	//进行数据均衡
	temp_vector[0] = vector[0];
	for(i=1; i<length; i++)
	{
		temp_vector[i] = (vector[i]+vector[i-1])/2;
	}//for i

	temp_vector[0]=0.0f;
	for(i=1; i<length; i++)
	{
		temp_vector[i] = temp_vector[i]-temp_vector[i-1];
	}//for i

	std::vector<int> extremum_list;

	//extremum_list.clear();
	for(i=1; i<length; i++)
	{
		if(temp_vector[i]<0.0f&&temp_vector[i-1]>0.0f)
			extremum_list.push_back(i);
	}//for i

	if(extremum_list.size()<1)
		flag = 0;
	else if(extremum_list.size()==1)
		flag = extremum_list[0];
	else 
	{
		for(i=1; i<extremum_list.size(); i++)
		{
			if(vector[extremum_list[i-1]]>vector[extremum_list[i]])
				flag = i;
		}//for i
	}//else 
		
	extremum_list.clear();
	free(temp_vector);
	temp_vector = NULL;

	return flag;
}

//检测向量的变化趋势，是否一致（递增或递减）,LQ
bool ImgChangeDetect::CheckTrend(float* vector, int length)
{
	bool  flag=true;
	int   i;
	float choose[3];

	if(NULL == vector)
		return false;

	memset(choose, 0, sizeof(choose));
	for(i=0; i<3; i++)
	{
		choose[i] = vector[i+1]-vector[i]; 
	}//for i

	for(i=0; i<3; i++)
	{
		if(choose[i]<0.0f)
			flag = false;
	}//for i

	return flag;
}


//得到矢量数组中的区域极值,用于基于灰度分布统计划分图像背景区域,LQ
//方法：先对向量进行均衡化（保证数据趋势一致），然后对向量中的数据进行邻接相减，
//      根据相减向量的数据分布确定各个波段，统计各个波段的灰度分布，找到最大灰度分布范围（用来确定图像背景）
//vector 输入矢量数组
//length 数组长度
//返回值为flag 表示数组极值的索引(用于划分图像前景和背景)
int ImgChangeDetect::GetExtremum2(float* vector, int length)
{
	int flag=-1;
	if(NULL==vector || length<1)
		return flag;

	int i;
	int state;
	float temp_vector[256];
	float temp_temp[256];

	memset(temp_vector, 0, sizeof(temp_vector));
	memset(temp_temp, 0, sizeof(temp_temp));
	
	//进行数据均衡
	temp_vector[0] = vector[0];
	for(i=1; i<length; i++)
	{
		temp_vector[i] = (vector[i]+vector[i-1])/2;
	}//for i

	////////wrong!!!!!
	temp_temp[0]=0.0f;
	for(i=1; i<length; i++)
	{
		temp_temp[i] = temp_vector[i]-temp_vector[i-1];
	}//for i

	float sum;
	std::vector<int>    extremum_list;	//用于记录各个波谷索引
	std::vector<float>  extremum_stat;	//用于统计各个波段灰度分布累积

	//extremum_list.clear();
	for(i=1; i<length; i++)
	{
		if(temp_temp[i]<0.0f&&temp_temp[i-1]>0.0f)
			extremum_list.push_back(i);
	}//for i

	//统计各个波段的灰度分布累积
	if(extremum_list.size()>1)
	{
		//判断取得的极值点处的向量变化趋势是否一致，若是则为极值点，若非则不是极值点，需删除
		for(i=0; i<extremum_list.size(); i++)
		{
			if((extremum_list[i]+3)<255)//检测数组的长度不超过总数组的长度
			{
				if(!CheckTrend((vector+extremum_list[i]), 3))
				{
					//该点不是极值点，删除之
					extremum_list.erase(extremum_list.begin()+i);
				}
			}
		}//for i

		for(i=1; i<extremum_list.size(); i++)
		{
			sum=0.0f;
			for(int m=extremum_list[i-1]; m<extremum_list[i]; m++)
			{
				sum += vector[m];
			}//for m
			extremum_stat.push_back(sum);
		}//for i

		float max=0.0f;
		for(i=1; i<extremum_stat.size(); i++)
		{
			if(max<extremum_stat[i])
			{
				flag = extremum_list[i];
				max  = extremum_stat[i]; 
			}//if
		}//for i
	}//if
	else 
	{
		flag = 0;
	}

	extremum_list.clear();
	extremum_stat.clear();

	return flag;
}


//函数要求输入图像为单波段图像数据
bool ImgChangeDetect::SegImgBackground(const char* ImageFileName)
{
	bool      flag=false;
	//BYTE	  byValue = 0;
	//int       i, j;
	//int	      Block_Density[256];
	//float     Block_Stat[256];
	//long      lWidth, lHeight;
	//long	  lIndexBand, lDataType;
	//CRasterDS rasterDS;

	//rasterDS.Open(ImageFileName);
	//rasterDS.CreateBuffer();
	//rasterDS.GetSize(&lWidth, &lHeight);
	////rasterDS.GetBandDataType((lIndexBand, &lDataType);
	//
	//memset(Block_Density, 0, sizeof(Block_Density));
	//memset(Block_Stat, 0, sizeof(Block_Stat));
	//for(j=0; j<lHeight; j++)
	//{
	//	for(i=0; i<lWidth; i++)
	//	{
	//		flag = rasterDS.PixelIO(1, i+1, j+1, &byValue, true);
	//		if(false == flag)
	//			byValue = 0;
	//
	//		Block_Density[byValue]++;
	//	}//for i
	//}//for j
	//rasterDS.DeleteBuffer();
	//rasterDS.Close();

	//for(i=0; i<256; i++)                  
	//{
	//	Block_Stat[i] = (float)Block_Density[i]/(float)(lWidth*lHeight);
	//}//for i
	//
	//int seg_index = GetExtremum2(Block_Stat, 256);

	//if(seg_index<1)
	//	flag = false;
	//else
	//	flag = true;

	return flag;
}


//void ImgChangeDetect::Templat(unsigned char *m_pdata, long wide, long height, int tempH, int tempW, int tempMX, int tempMY, float *fpArray, float fCoef)
void ImgChangeDetect::Templat(BYTE* m_pdata, long wide, long height, int tempH, int tempW, int tempMX, int tempMY, float *fpArray, float fCoef)
{   
	int i,j,k,l;  
    BYTE* temp = new BYTE[lWidth*lHeight];  
	
    memcpy(temp, m_pdata, sizeof(BYTE)*wide*height);
    float fResult;    
	for(j=tempMY; j<height-tempH+tempMY+1; j++)
		for(i=tempMX; i<wide-tempW+tempMX+1; i++)
		{
			fResult=0;
			for(k=0; k<tempH; k++)
				for(l=0; l<tempW; l++)
				{
					fResult = fResult+m_pdata[(j-tempMY+k)*wide+(i-tempMX+l)]*fpArray[k*tempW+l];
				}
			
			fResult*=fCoef;
			
			fResult=(float)fabs(fResult);
			
			if(fResult>255)
				
                temp[j*wide+i]=255;
			else
				temp[j*wide+i]=(int)(fResult+0.5);
		}
    memcpy(m_pdata, temp, sizeof(BYTE)*wide*height);  
	delete  []temp;
}


//图像分割，边缘检测方式，sobel方法，LQ
void ImgChangeDetect::EdgeDetect_Sobel(const char* ImageFileName, const char* ImageFileName_Out)
{
	//if(strcmp(ImageFileName, "")==0)
	//	return;

	//int i,j;
	//int tempH;		//模板高度 
	//int tempW;		//模板宽度  
	//
	//int tempMY;		//模板中心元素Y坐标
	//int tempMX;		//目标中心元素X坐标

	//long lWidth;	//图像宽度
	//long lHeight;   //图像高度
	//long lIndexBand; 

	//float tempC;		//模板系数
	//float Template[9];	//模板数组     
 //
	//CRasterDS rasterDS;
	//CRasterDS rasDestTemp;

	//rasterDS.Open(ImageFileName);
	//rasterDS.CreateBuffer();
	//rasterDS.GetSize(&lWidth, &lHeight);
	//rasterDS.GetBandCount(&lChannelCount);
	//rasterDS.GetBandDataType(1, &lDataType);

	////unsigned char byValue;
	////unsigned char *temp1 = new unsigned char[lWidth*lHeight];
	////unsigned char *temp2 = new unsigned char[lWidth*lHeight];
	//BYTE byValue;
	//BYTE*  temp1=new BYTE[lWidth*lHeight];
	//BYTE*  temp2=new BYTE[lWidth*lHeight];

	//if((temp1==NULL) ||(temp2==NULL))
	//{
	//	return ;
	//}

	//for(j=0; j<lHeight; j++)
	//{
	//	for(i=0; i<lWidth; i++)
	//	{
	//		if(!rasterDS.PixelIO(1, i+1, j+1, &byValue, true))
	//		{
	//			byValue = 0;
	//		}
	//		
	//		temp1[j*lWidth+i] = byValue;
	//		temp2[j*lWidth+i] = byValue;
	//	}//for i
	//	
	//}//for j
	//rasterDS.DeleteBuffer();
	//rasterDS.Close();

	//tempW=3;
	//tempH=3;
	//tempC=1.0;
	//tempMY=1;
	//tempMX=1;
	//Template[0] = -1.0;
 //   Template[1] = -2.0;
	//Template[2] = -1.0;
	//Template[3] = 0.0;
	//Template[4] = 0.0;
	//Template[5] = 0.0;
	//Template[6] = 1.0;
	//Template[7] = 2.0;
	//Template[8] = 1.0;
	//Templat(temp1, lWidth, lHeight ,tempH, tempW, tempMX, tempMY, Template, tempC); 
 //   
 //   Template[0] = -1.0;
 //   Template[1] = 0.0;
	//Template[2] = 1.0;
	//Template[3] = -2.0;
	//Template[4] = 0.0;
	//Template[5] = 2.0;
	//Template[6] = -1.0;
	//Template[7] = 0.0;
	//Template[8] = 1.0;
	//Templat(temp2, lWidth, lHeight, tempH, tempW, tempMX, tempMY, Template, tempC);
	//
	//for(j=0; j<lHeight; j++)
	//	for(i=0; i<lWidth; i++)
	//		if( temp2[j*lWidth+i]> temp1[j*lWidth+i])
	//		{
	//			temp1[j*lWidth+i] = temp2[j*lWidth+i];
	//		}//if
 //   
	////创建中间结果影像
	//STRasFileInfo rasfileInfoTemp;
	//rasfileInfoTemp.lHeaderLen = 0;				//图像的头长度
	//rasfileInfoTemp.lWidth = lWidth;			//图像的宽度
	//rasfileInfoTemp.lHeight = lHeight;			//图像的高度
	//rasfileInfoTemp.lChannelNum = lChannelCount;	//图像的通道数
	//rasfileInfoTemp.lFormatType = 3;				//数据组织方式
	//rasfileInfoTemp.lDataType = lDataType;

	//if(!rasDestTemp.Create(ImageFileName_Out, &rasfileInfoTemp))
	//	return ;

	//rasDestTemp.Open(ImageFileName_Out, GA_Update);
	//rasDestTemp.CreateBuffer();

	//for(j=0; j<lHeight; j++)
	//{
	//	for(i=0; i<lWidth; i++)
	//	{
	//		byValue = temp1[j*lWidth+i];
	//		if(byValue<0)
	//		{
	//			byValue = 0;
	//		}
	//		if(byValue>255)
	//		{
	//			byValue = 255;
	//		}
	//	/*
	//		if(byValue<127)
	//		{
	//			byValue = 0;
	//		}
	//		else
	//		{
	//			byValue = 255;
	//		}
	//	*/
	//		bool flag = rasDestTemp.PixelIO(1, i+1, j+1, &byValue, false);
	//			
	//	}//for i	
	//}//for j

	//rasDestTemp.DeleteBuffer();
	//rasDestTemp.Close();

	//delete  temp1;
	//delete  temp2;
	
}

//图像分割，边缘检测方式，PreWitt方法，LQ
void ImgChangeDetect::EdgeDetect_PreWitt(const char* ImageFileName, const char* ImageFileName_Out)
{
	//if(strcmp(ImageFileName, "")==0)
	//	return;

	//int i,j;
	//int tempH;		//模板高度 
	//int tempW;		//模板宽度  
	//
	//int tempMY;		//模板中心元素Y坐标
	//int tempMX;		//目标中心元素X坐标

	//long lWidth;	//图像宽度
	//long lHeight;   //图像高度
	//long lIndexBand;

	//float tempC;		//模板系数
	//float Template[9];	//模板数组     
 //
	//CRasterDS rasterDS;
	//CRasterDS rasDestTemp;

	//rasterDS.Open(ImageFileName);
	//rasterDS.CreateBuffer();
	//rasterDS.GetSize(&lWidth, &lHeight);
	////rasterDS.GetBandDataType(lIndexBand, &lDataType);
	//
	////unsigned char byValue;
	////unsigned char *temp1 = new unsigned char[lWidth*lHeight];
	////unsigned char *temp2 = new unsigned char[lWidth*lHeight];
	//BYTE   byValue;
	//BYTE*  temp1=new BYTE[lWidth*lHeight];
	//BYTE*  temp2=new BYTE[lWidth*lHeight];

	//if((temp1==NULL) ||(temp2==NULL))
	//{
	//	return ;
	//} 
 //  
	//for(j=0; j<lHeight; j++)
	//{
	//	for(i=0; i<lWidth; i++)
	//	{
	//		if(!rasterDS.PixelIO(1, i+1, j+1, &byValue, true))
	//		{
	//			byValue = 0;
	//		}//if
	//		temp1[j*lWidth+i] = byValue;
	//		temp2[j*lWidth+i] = byValue;

	//	}//for i
	//}//for j
	//rasterDS.DeleteBuffer();
	//rasterDS.Close();
 //	
	//tempW = 3;
	//tempH = 3;
	//tempC = 1.0;
	//tempMY = 1;
	//tempMX = 1;
	//Template[0] = -1.0;
 //   Template[1] = -1.0;
	//Template[2] = -1.0;
	//Template[3] = 0.0;
	//Template[4] = 0.0;
	//Template[5] = 0.0;
	//Template[6] = 1.0;
	//Template[7] = 1.0;
	//Template[8] = 1.0;	
	//Templat(temp1, lWidth, lHeight, tempH, tempW, tempMX, tempMY, Template, tempC);
 //   
 //   Template[0] = 1.0;
 //   Template[1] = 0.0;
	//Template[2] = -1.0;
	//Template[3] = 1.0;
	//Template[4] = 0.0;
	//Template[5] = -1.0;
	//Template[6] = 1.0;
	//Template[7] = 0.0;
	//Template[8] = -1.0;
	//Templat(temp2, lWidth, lHeight, tempH, tempW, tempMX, tempMY, Template, tempC);
	//
	//for(j=0; j<lHeight; j++)
	//	for(i=0; i<lWidth; i++)
	//		if( temp2[j*lWidth+i]> temp1[j*lWidth+i])
	//		{
	//			 temp1[j*lWidth+i]= temp2[j*lWidth+i];
	//		}//if

	////创建中间结果影像
	//STRasFileInfo rasfileInfoTemp;
	//rasfileInfoTemp.lHeaderLen = 0;				//图像的头长度
	//rasfileInfoTemp.lWidth = lWidth;			//图像的宽度
	//rasfileInfoTemp.lHeight = lHeight;			//图像的高度
	//rasfileInfoTemp.lChannelNum = lChannelCount;	//图像的通道数
	//rasfileInfoTemp.lFormatType = 3;				//数据组织方式
	//rasfileInfoTemp.lDataType = lDataType;

	//if(!rasDestTemp.Create(ImageFileName_Out, &rasfileInfoTemp))
	//	return ;

	//rasDestTemp.Open(ImageFileName_Out, GA_Update);
	//rasDestTemp.CreateBuffer();

 //   for(j=0; j<lHeight; j++)
	//{
	//	for(i=0; i<lWidth; i++)
	//	{
	//		 byValue = temp1[j*lWidth+i];
	//		 if(byValue<0)
	//			 byValue = 0;
	//		 if(byValue>255)
	//			 byValue = 255;

	//		rasDestTemp.PixelIO(1, i+1, j+1, &byValue, false);
	//			
	//	}//for i	
	//}//for j
	//rasDestTemp.DeleteBuffer();
	//rasDestTemp.Close();
	//
	//delete  temp1;
	//delete  temp2;

}

//图像分割，边缘检测方式,LQ
//算法适应：    本算法适应内容轮廓，纹理信息比较清晰的图像的分割
//主要算法描述：对图像进行边缘检测，对检测结果进行二值化，对二值化图像进行水淹算法提取图像闭合区域，
//             根据提取的闭合区域进行分割，非闭合区域则为背景
//m_pdata 图像数据；wide    图像宽度；height  图像高度

void ImgChangeDetect::Segment_Edge(BYTE* m_pdata, int wide, int height)
{
	//if((NULL == m_pdata) || (wide<0) || (height<0))
	//	return;

	//int    i,j;
	//int    Area_Number;
	//BYTE   value;
	//CPoint edgepoint;
	//vector<CPoint>    row_edge_points;	//行扫描时，记录行中边缘点

	///////扫描二值化图像，提取闭合区域（area_edges）
	//Area_Number = 0;
	//area_edges.clear();
	//for(i=0; i<height; i++)
	//{
	//	row_edge_points.clear();
	//	for(j=0; j<wide; j++)
	//	{
	//		value = m_pdata[i*wide+j];
	//		if(value==255)	//扫描点为边缘点，
	//		{
	//			edgepoint.x = j;
	//			edgepoint.y = i;
	//		
	//			//确定边缘点属于哪个闭合区域。如果属于现有区域，则将其加入该区域边缘集中，如果不属于任何区域，
	//			//则新创建一个闭合区域，加入之
	//			int belong_area_index = JudgePoint2Area(edgepoint);
	//			if(belong_area_index == -1)//边缘点不属于任何已知区域，新建区域
	//			{
	//				Area_Number++;
	//				AreaEdges data;

	//				data.Number  = Area_Number;
	//				data.edge_set.push_back(edgepoint);	//将边缘点加入到新的区域边缘点集中
	//				area_edges.push_back(data);			//将新建的区域加入到图像闭合区域列表中
	//			}//if
	//			else //将边缘点加入到所属闭合区域的边缘集中
	//			{
	//				area_edges[belong_area_index].edge_set.push_back(edgepoint);
	//			}//else
	//			
	//		}//if
	//	}// for j
	//}//for i

	//////

	//////对提取的闭合区域进行分割

	//////保存图像分割的结果（shp文件）

}

//判断边缘点属于哪个闭合区域
//返回值表示检测边缘点所属闭合区域的编号。若返回值为-1，则边缘点不属于已存在的闭合区域，属于新的闭合区域。
int ImgChangeDetect::JudgePoint2Area(CPoint Edge_Point)
{
	//int  i, j;
	//int  BelongArea_Index=-1;
	//bool flag=false;

	//for(i=0; i<area_edges.size(); i++)//对全部已存在的闭合区域进行遍历
	//{
	//	for(j=0; j<area_edges[i].edge_set.size(); j++)//对区域已加入的边缘点进行遍历，检查是否有边缘点与其邻接
	//	{
	//		float temp1, temp2;
	//		float distance;
	//		
	//		temp1    = pow((area_edges[i].edge_set[j].x- Edge_Point.x), 2.0);
	//		temp2    = pow((area_edges[i].edge_set[j].y- Edge_Point.y), 2.0);
	//		distance = sqrt(temp1 + temp2);

	//		if(distance<1.5 && distance>0.0)//两点邻接
	//		{
	//			BelongArea_Index = i;
	//			flag = true;
	//			break;
	//		}//if

	//	}
	//	if(flag == true)
	//	{
	//		break;
	//	}
	//		
	//}//for i
	//
	//
	//return BelongArea_Index;

	return 0;
}

bool ImgChangeDetect::RelativeDetect(const char *strSrc, const char *strDest, const char *strResult,int nsize, double threshold)
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
	for(starty=0;starty<lheight;)
	{

		endy =(starty+nsize-1<lheight)?nsize:(lheight-1);
		for(startx=0;startx<lheight;)
		{
			endx =(startx+nsize-1<lwidth)?nsize:(lwidth-1);
            
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

			if(cal<threshold)
			{
				//记录结果

			}
			startx =endx+1;

		}
		starty =endy+1;
	}

	delete []pbuffer;
	delete []pfbuffer1;
	delete []pfbuffer2;


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


}