#ifndef  _FUZZYKMEAN_CLASS_H_
#define  _FUZZYKMEAN_CLASS_H_

#include "IRasterDataset.h"


//�������ܣ�
//	
//		ģ�� K ��ֵ�������
//
//������
//  
//---------------------------  ��ѡ������   ---------------------------	
//	
//		�����ļ�����						pszInputFileName
//		����ļ�����					    pszOutputFileName
//
//---------------------------  �㷨������   ---------------------------
//		�����ȣ�							dblResampleRatio
//		����������							lCenterCount
//		������������						lMaxIterCount
//		�ж���ֵ��							fMovementThreshold (ԽС������Խ��ȷ)
//

namespace ImageProcess
{
	IMP_DLL bool FuzzyKmeanClass(const char *pszInputFileName, const char *pszOutputFileName, double dblResampleRatio, long lCenterCount, long lMaxIterCount, float fMovementThreshold);
}

#endif