#pragma once
#include "IRasterDataset.h"
#include "IProgress.h"
#include <vector>

namespace ImageProcess
{


class IMP_DLL ImgChangeDetect
{

	

//ͼ��仯������ݽṹ
struct ChangeBlock_Index	//ͼ��ָ��У����ڼ�¼ͼ��һ�μ��Ͷ��μ�����ı�ţ�����shp�ļ���
	{
		int index_block;
		int index_subblock;
	};
struct CPoint		//��Ե��ⷽʽͼ��ָ���
	{
		int x; //ͼ��x����
		int y; //ͼ��y����
	};
struct AreaEdges	//��Ե��ⷽʽͼ��ָ���
	{
		int            Number;		//ͼ���бպ�����ı��
		std::vector<CPoint> edge_set;	//�պ������Ե�ϵĵ㼯
	};

public:
	ImgChangeDetect(void);
	~ImgChangeDetect(void);

public:

	//���ϵ����
	bool RelativeDetect(const char *strSrc,const char *strDest,const char *strResult,int nsize,double threshold,SYSTEM::IProgress *pProgress);
	//ֱ��ͼ��ʽ
	bool Detect_Hist         (long lIndexBand, int Num, int nIndexBlock, float* Vector);						//���μ��
	bool Detect_Hist2        (long lIndexBand, int Num, int nIndexBlock, int nIndexSubBlock, float* Vector);
	void ImgDetect_Hist      (const char* ImageFileName_Src, const char* ImageFileName_Dest, const char* ImageFileName_Res, float Threshold);//���ƶ���ֵ);

	//��ɫ�ط�ʽ
	bool Detect_ColorMatix   (long lIndexBand, int Num, int nIndexBlock, float* Vector);
	bool Detect_ColorMatix2  (long lIndexBand, int Num, int nIndexBlock, int nIndexSubBlock, float* Vector);
	void ImgDetect_ColorMatix(const char* ImageFileName_Src, const char* ImageFileName_Dest, const char* ImageFileName_Res, float Threshold);

	//�����׷�ʽ
	bool Detect_TextureChart (long lIndexBand, int Num, int nIndexBlock, float* Vector);
	bool Detect_TextureChart2(long lIndexBand, int Num, int nIndexBlock, int nIndexSubBlock, float* Vector);
	void ImgDetect_Texture   (const char* ImageFileName_Src, const char* ImageFileName_Dest, const char* ImageFileName_Res, float Threshold);			

	//��������ʽ
	bool Detect_Adjoint      (long lIndexBand, int Num, int nIndexBlock, float* Vector);
	void ImgDetect_Adjoint   (const char* ImageFileName_Src, const char* ImageFileName_Dest, float Threshold);

	//��������
	void DetectResult	     (int nIndex, int Num);
	void DetectResult2       (int nIndex_Block, int nIndex_Subblock, int Num);
	bool SaveDetectResult_SHP(const char *shpfilename, int Num, int nBlockIndex, int nSubblockIndex);
	
	//���ƶȼ���
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
	int     m_nAverGrayDiff;//����ͼ���ƽ���ҶȲ��ֵ����������ͬԴͼ������绷����ͬ��������Ӱ��
	int     m_nDealImage;	//��ʶϵͳ���ڴ����ͼ��0û�д���ͼ��1ΪԴͼ��2ΪĿ��ͼ��
	std::vector<ChangeBlock_Index> m_DetectChangeList;	//���ڴ洢ͼ�������б仯��������
	std::vector<AreaEdges> area_edges;					//��Ե��ⷽʽͼ��ָɨ��ͼ�񣬼�¼ͼ���еĸ����պ������Ե�㼯
	
public:
	int  CalAverGrayDiff(const char* ImageFileName_Src, const char* ImageFileName_Dest);
	bool GetDetectArea_Hist(const char* detectfile_sc, const char* detectfile_ds, const char* detectfile_rs, STExtent scope);
	bool GetDetectArea_Object(const char* detectfile_sc, const char* detectfile_ds, STExtent scope);
	bool SegImgBackground(const char* ImageFileName);
	void ImgDetectCorrelation_Index(const char* ImageFileName_Src, const char* ImageFileName_Dest, const char* ImageFileName_Res, float Threshold);
	void ImgDetectCorrelation_Index2(const char* ImageFileName_Src, const char* ImageFileName_Dest, const char* ImageFileName_Res, float Threshold);

	void EdgeDetect_Sobel(const char* ImageFileName,  const char* ImageFileName_Out);	//ͼ���Ե��⣬ͼ��ָ���
	void EdgeDetect_PreWitt(const char* ImageFileName, const char* ImageFileName_Out);	//ͼ���Ե��⣬ͼ��ָ���
	void Templat(BYTE* m_pdata, long wide, long height, int tempH, int tempW, int tempMX, int tempMY, float *fpArray, float fCoef);

private:
	int  GetDiffValue(int* Vector, int length);		//�����õ���������ֵ
	int  GetExtremum1(float* vector, int length);	//����ָ�ͼ�񱳾�
	int  GetExtremum2(float* vector, int length);	//�����ָ�ͼ�񱳾�
	int  CalAverGrayDiff2(const char* ImageFileName_Src, const char* ImageFileName_Dest);
	bool CheckTrend(float* vector, int length);
	//��Ե��ⷽʽͼ��ָ��
	void Segment_Edge(BYTE* m_pdata, int wide, int height);
	int JudgePoint2Area(CPoint Edge_Point);

	double CalCorrelation(float* pBase, float* pSamp, int nBlockLen);
};


}