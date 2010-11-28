//////////////////////////////////////////////////////////////////////
// 版权(c) 2008-2020, 天地智绘
// 作者：  champion
// 时间：  2008.7
// 描述：  栅格驱动库基础定义
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