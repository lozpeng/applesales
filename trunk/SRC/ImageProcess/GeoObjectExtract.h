#ifndef _GEOOBJ_EXTRACT_H_
#define _GEOOBJ_EXTRACT_H_

#include "IRasterDataset.h"
#include "ImageProcessDef.h"
#include "IProgress.h"
namespace ImageProcess
{
	/**
	* ˮ��Ҫ����ȡ
	* @param InputFileName      ����Ӱ���ļ���
	* @param OutputFileName     ���ʸ���ļ���
	* @param samples            ����ͼ��
	* @return ���ǳɹ�����true�����򷵻�true 
	*/
IMP_DLL bool WaterExtract(const char *InputFileName, 
		const char *OutputFileName,std::vector<GEOMETRY::geom::Polygon*> &samples,int nminsize,SYSTEM::IProgress *pProgress);

}

#endif