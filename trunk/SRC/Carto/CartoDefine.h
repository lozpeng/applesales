//////////////////////////////////////////////////////////////////////
  // 版权(c) 2010-2020, 天地智绘
  // 作者：  hhzhao
  // 时间：  2010/11/18
  // 描述：  carto库的基础定义，包括导出宏、工程连接的基础头文件等
//////////////////////////////////////////////////////////////////////


#ifndef Carto_Define_H
#define Carto_Define_H

#if defined  CARTO_EXPORTS
#define CARTO_DLL __declspec(dllexport)
#else
#define CARTO_DLL __declspec(dllimport)
#pragma comment(lib,"Carto.lib")
#pragma message("Automatically linking with Carto.dll")

#endif


#endif