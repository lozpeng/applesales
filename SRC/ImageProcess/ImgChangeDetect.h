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

	//重点目标探测
	bool TargetDetect(const char *strSrc,const char *strDest,const char *strTarget,int nsize,double grade1,double grade2, double thres, SYSTEM::IProgress *pProgress);


protected:

	double CalCorrelation(float* pBase, float* pSamp, int nBlockLen);

	float DamGradeCal(float* src, float* dest, long lWidth, long lHeight, float thres);

};


}