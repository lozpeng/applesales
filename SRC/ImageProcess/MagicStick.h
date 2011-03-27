#ifndef  _MAGIC_STICK_H_
#define  _MAGIC_STICK_H_

#include "IRasterDataset.h"
#include <vector>

namespace ImageProcess
{
	/**
	* 魔术棒提取边界
	* pDataset 目标数据
	* x        点的X坐标
	* y        点的Y坐标
	* rate     相似像素值的范围
	* @return 返回提取的边界多边形
	*/
	IMP_DLL GEOMETRY::geom::Polygon*  MagicStick(Geodatabase::IRasterDataset* pDataset,int x,int y,unsigned char rate); 

	//区域增长法
	IMP_DLL bool  AreaIncrease(unsigned char *pRed,unsigned char *pGreen,unsigned char *pBlue,long lwidth,long lheight,int x,int y,unsigned char value,unsigned char rate,std::vector<IntPoint> &points);
}

#endif