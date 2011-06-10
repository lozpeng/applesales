#ifndef _GEOOBJ_EXTRACT_H_
#define _GEOOBJ_EXTRACT_H_

#include "IRasterDataset.h"
#include "ImageProcessDef.h"
#include "IProgress.h"
namespace ImageProcess
{
	/**
	* 水体要素提取
	* @param InputFileName      输入影像文件名
	* @param OutputFileName     输出矢量文件名
	* @param samples            样本图形
	* @return 若是成功返回true，否则返回true 
	*/
IMP_DLL bool WaterExtract(const char *InputFileName, 
		const char *OutputFileName,std::vector<GEOMETRY::geom::Polygon*> &samples,int nminsize,SYSTEM::IProgress *pProgress);

}

#endif