#ifndef _IMAGE2VEC_H_
#define _IMAGE2VEC_H_

#include "ImageProcessDef.h"
namespace ImageProcess
{
	/**
	* ��Ӱ����ĳ������ֵ�Ķ������ʸ����
	* @param infile  ����Ӱ��
	* @param outfile  ���ʸ����
	* @param classval  Ҫ����ʸ��������������ֵ
	* @param minisize  ��С�����ֵ��С�����������Ŀ���������� 
	* @return �ɹ�true, ʧ��false 
	*/
    IMP_DLL bool ImgClass2Shp(const char *infile,const char *outfile,unsigned char classval,int minisize);

}

#endif