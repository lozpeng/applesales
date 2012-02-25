#ifndef _IMAGE2VEC_H_
#define _IMAGE2VEC_H_

#include "ImageProcessDef.h"
namespace ImageProcess
{
	/**
	* 将影像中某个像素值的对象进行矢量化
	* @param infile  输入影像
	* @param outfile  输出矢量名
	* @param classval  要进行矢量化的类别的像素值
	* @param minisize  最小面积阈值，小于这个像素数目的区域将舍弃 
	* @return 成功true, 失败false 
	*/
    IMP_DLL bool ImgClass2Shp(const char *infile,const char *outfile,unsigned char classval,int minisize);

}

#endif