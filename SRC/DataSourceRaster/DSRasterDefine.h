//////////////////////////////////////////////////////////////////////
// ��Ȩ(c) 2008-2020, ����ǻ�
// ���ߣ�  champion
// ʱ�䣺  2008.7
// ������  դ���������������
//////////////////////////////////////////////////////////////////////

#ifndef _DSRASTER_DEFINE_H_
#define _DSRASTER_DEFINE_H_


#if defined DATASOURCERASTER_EXPORTS
#define DSRASTER_DLL __declspec(dllexport)
#else
#define DSRASTER_DLL __declspec(dllimport)
#pragma comment(lib,"DataSourceRaster.lib")
#pragma message("Automatically linking with DataSourceRaster.dll")
#endif


#endif