#pragma once
#include "IRasterDataset.h"
#include "IProgress.h"
#include <vector>

namespace ImageProcess
{


class IMP_DLL ImgChangeDetect
{

	

//图象变化检测数据结构
struct ChangeBlock_Index	//图像分割中，用于记录图像一次检测和二次检测结果的编号，生成shp文件用
	{
		int index_block;
		int index_subblock;
	};
struct CPoint		//边缘检测方式图像分割用
	{
		int x; //图像x坐标
		int y; //图像y坐标
	};
struct AreaEdges	//边缘检测方式图像分割用
	{
		int            Number;		//图像中闭合区域的编号
		std::vector<CPoint> edge_set;	//闭合区域边缘上的点集
	};

public:
	ImgChangeDetect(void);
	~ImgChangeDetect(void);

public:

	//相关系数法
	bool RelativeDetect(const char *strSrc,const char *strDest,const char *strResult,int nsize,double threshold,SYSTEM::IProgress *pProgress);
	//直方图方式
	bool Detect_Hist         (long lIndexBand, int Num, int nIndexBlock, float* Vector);						//初次检测
	bool Detect_Hist2        (long lIndexBand, int Num, int nIndexBlock, int nIndexSubBlock, float* Vector);
	void ImgDetect_Hist      (const char* ImageFileName_Src, const char* ImageFileName_Dest, const char* ImageFileName_Res, float Threshold);//相似度阈值);

	//颜色矩方式
	bool Detect_ColorMatix   (long lIndexBand, int Num, int nIndexBlock, float* Vector);
	bool Detect_ColorMatix2  (long lIndexBand, int Num, int nIndexBlock, int nIndexSubBlock, float* Vector);
	void ImgDetect_ColorMatix(const char* ImageFileName_Src, const char* ImageFileName_Dest, const char* ImageFileName_Res, float Threshold);

	//纹理谱方式
	bool Detect_TextureChart (long lIndexBand, int Num, int nIndexBlock, float* Vector);
	bool Detect_TextureChart2(long lIndexBand, int Num, int nIndexBlock, int nIndexSubBlock, float* Vector);
	void ImgDetect_Texture   (const char* ImageFileName_Src, const char* ImageFileName_Dest, const char* ImageFileName_Res, float Threshold);			

	//共生矩阵方式
	bool Detect_Adjoint      (long lIndexBand, int Num, int nIndexBlock, float* Vector);
	void ImgDetect_Adjoint   (const char* ImageFileName_Src, const char* ImageFileName_Dest, float Threshold);

	//处理检测结果
	void DetectResult	     (int nIndex, int Num);
	void DetectResult2       (int nIndex_Block, int nIndex_Subblock, int Num);
	bool SaveDetectResult_SHP(const char *shpfilename, int Num, int nBlockIndex, int nSubblockIndex);
	
	//相似度计算
	//bool  ObjMatch           (Obj_Shape Object1, Obj_Shape Object2);
	//float VectorMatch_M      (float* vector1, int length1, float* vector2, int length2);
	//float VectorMatch_O      (float* vector1, int length1, float* vector2, int length2);
	
protected:
	Geodatabase::IRasterDatasetPtr	rasSrcDS;
	Geodatabase::IRasterDatasetPtr	resResDS;
	//CFeatureDS  *m_poFeatureDS;
	
	long    lWidth; 
	long	lHeight;
	long    lChannelCount;
	long	lDataType;
	int     m_nAverGrayDiff;//两幅图像的平均灰度差分值，用来消除同源图像因外界环境不同而产生的影响
	int     m_nDealImage;	//标识系统正在处理的图像，0没有处理图像，1为源图像，2为目标图像
	std::vector<ChangeBlock_Index> m_DetectChangeList;	//用于存储图像区块中变化的区块编号
	std::vector<AreaEdges> area_edges;					//边缘检测方式图像分割，扫描图像，记录图像中的各个闭合区域边缘点集
	
public:
	int  CalAverGrayDiff(const char* ImageFileName_Src, const char* ImageFileName_Dest);
	bool GetDetectArea_Hist(const char* detectfile_sc, const char* detectfile_ds, const char* detectfile_rs, STExtent scope);
	bool GetDetectArea_Object(const char* detectfile_sc, const char* detectfile_ds, STExtent scope);
	bool SegImgBackground(const char* ImageFileName);
	void ImgDetectCorrelation_Index(const char* ImageFileName_Src, const char* ImageFileName_Dest, const char* ImageFileName_Res, float Threshold);
	void ImgDetectCorrelation_Index2(const char* ImageFileName_Src, const char* ImageFileName_Dest, const char* ImageFileName_Res, float Threshold);

	void EdgeDetect_Sobel(const char* ImageFileName,  const char* ImageFileName_Out);	//图像边缘检测，图像分割用
	void EdgeDetect_PreWitt(const char* ImageFileName, const char* ImageFileName_Out);	//图像边缘检测，图像分割用
	void Templat(BYTE* m_pdata, long wide, long height, int tempH, int tempW, int tempMX, int tempMY, float *fpArray, float fCoef);

private:
	int  GetDiffValue(int* Vector, int length);		//用来得到向量均差值
	int  GetExtremum1(float* vector, int length);	//用类分割图像背景
	int  GetExtremum2(float* vector, int length);	//用来分割图像背景
	int  CalAverGrayDiff2(const char* ImageFileName_Src, const char* ImageFileName_Dest);
	bool CheckTrend(float* vector, int length);
	//边缘检测方式图像分割函数
	void Segment_Edge(BYTE* m_pdata, int wide, int height);
	int JudgePoint2Area(CPoint Edge_Point);

	double CalCorrelation(float* pBase, float* pSamp, int nBlockLen);
};


}