#ifndef _DISTANCE_CLASSIFY_H_
#define _DISTANCE_CLASSIFY_H_

#include "IRasterDataset.h"
#include "ImageProcessDef.h"
namespace ImageProcess
{


	/**
	* ��С������з���
	* @param InputFileName ����Ӱ���ļ���
	* @param lInputChannelCount ����ͨ����
	* @param plChannelIndex     ����ͨ�����
	* @param OutputFileName     ����ļ���
	* @param lOutputChannelNum  ����ļ�ͨ����
	* @param stFileExtent       ����Ӱ�����Χ
	* @param lSurveyDistMethod  ��ȡ����ķ���:(0����С���룬1�����Ͼ���, 2����Ҷ˹����)
	* @param ClsInfo            �����Ϣ
	* @param plValue            ���ֵ
	* @param plColor            �����ɫ
 	* @return ���ǳɹ�����true�����򷵻�true 
	*/
IMP_DLL bool DistanceClassify(const char *InputFileName, long lInputChannelCount, long* plChannelIndex,
	const char *OutputFileName, long lOutputChannelNum, 
	long lSurveyDistMethod, ClassifyInfo *ClsInfo,
	long* plValue = NULL, long* plColor = NULL);


}
#endif