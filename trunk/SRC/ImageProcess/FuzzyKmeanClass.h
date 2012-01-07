#ifndef  _FUZZYKMEAN_CLASS_H_
#define  _FUZZYKMEAN_CLASS_H_

#include "IRasterDataset.h"


//函数功能：
//	
//		模糊 K 均值分类计算
//
//参数：
//  
//---------------------------  必选参数段   ---------------------------	
//	
//		输入文件名：						pszInputFileName
//		输出文件名：					    pszOutputFileName
//
//---------------------------  算法参数段   ---------------------------
//		采样比：							dblResampleRatio
//		类中心数：							lCenterCount
//		最大迭代次数：						lMaxIterCount
//		判定阈值：							fMovementThreshold (越小分类结果越精确)
//

namespace ImageProcess
{
	IMP_DLL bool FuzzyKmeanClass(const char *pszInputFileName, const char *pszOutputFileName, double dblResampleRatio, long lCenterCount, long lMaxIterCount, float fMovementThreshold);
}

#endif