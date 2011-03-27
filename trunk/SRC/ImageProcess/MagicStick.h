#ifndef  _MAGIC_STICK_H_
#define  _MAGIC_STICK_H_

#include "IRasterDataset.h"
#include <vector>

namespace ImageProcess
{
	/**
	* ħ������ȡ�߽�
	* pDataset Ŀ������
	* x        ���X����
	* y        ���Y����
	* rate     ��������ֵ�ķ�Χ
	* @return ������ȡ�ı߽�����
	*/
	IMP_DLL GEOMETRY::geom::Polygon*  MagicStick(Geodatabase::IRasterDataset* pDataset,int x,int y,unsigned char rate); 

	//����������
	IMP_DLL bool  AreaIncrease(unsigned char *pRed,unsigned char *pGreen,unsigned char *pBlue,long lwidth,long lheight,int x,int y,unsigned char value,unsigned char rate,std::vector<IntPoint> &points);
}

#endif