#ifndef _DISTANCE_CLASSIFY_H_
#define _DISTANCE_CLASSIFY_H_

#include "IRasterDataset.h"
#include "ImageProcessDef.h"
namespace ImageProcess
{


	/**
	* 最小距离进行分类
	* @param InputFileName 输入影像文件名
	* @param lInputChannelCount 输入通道数
	* @param plChannelIndex     输入通道序号
	* @param OutputFileName     输出文件名
	* @param lOutputChannelNum  输出文件通道数
	* @param stFileExtent       输入影像地理范围
	* @param lSurveyDistMethod  量取距离的方法:(0—最小距离，1—马氏距离, 2—贝叶斯距离)
	* @param ClsInfo            类别信息
	* @param plValue            类的值
	* @param plColor            类的颜色
 	* @return 若是成功返回true，否则返回true 
	*/
IMP_DLL bool DistanceClassify(const char *InputFileName, long lInputChannelCount, long* plChannelIndex,
	const char *OutputFileName, long lOutputChannelNum, 
	long lSurveyDistMethod, ClassifyInfo *ClsInfo,
	long* plValue = NULL, long* plColor = NULL);


}
#endif