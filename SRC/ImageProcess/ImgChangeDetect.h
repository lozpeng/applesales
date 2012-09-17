#pragma once
#include "IRasterDataset.h"
#include "IProgress.h"
#include <vector>

namespace ImageProcess
{
class IMP_DLL ImgChangeDetect
{
public:
	ImgChangeDetect(void);
	~ImgChangeDetect(void);

public:

	//相关系数法
	bool RelativeDetect(const char *strSrc,const char *strDest,const char *strResult,int nsize,double threshold1,double threshold2, SYSTEM::IProgress *pProgress);

	//
	bool TargetDetect(const char *strSrc,const char *strDest,const char *strTarget, const char* strResult, int nsize,double grade1,double grade2, double thres, SYSTEM::IProgress *pProgress);
	//
	bool TargetDetect2(const char *strSrc,const char *strDest,const char *strTarget, const char* strResult, int nsize,double grade1,double grade2, double thres, SYSTEM::IProgress *pProgress);

protected:

	double CalCorrelation(float* pBase, float* pSamp, int nBlockLen);

	float DamGradeCal(float* src, float* dest, long lWidth, long lHeight, float thres);
	float DamGradeCal2(BYTE* src, BYTE* dest, long lWidth, long lHeight, float thres, int ot);

	bool CalculateGLCM(BYTE* ptr, int width, int height, float *entropy, float *moment, float *contrast, float *correlation, float *homogeneity);
};


}