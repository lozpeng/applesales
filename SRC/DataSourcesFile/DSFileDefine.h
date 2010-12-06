
//////////////////////////////////////////////////////////////////////
  // 版权(c) 2010-2020, 天地智绘
  // 作者：  hhzhao
  // 时间：  2009/11/18
  // 描述：  DataSourcesFile库的基础定义，包括导出宏、工程连接的基础头文件等
//////////////////////////////////////////////////////////////////////

#ifndef _DataSourcesFile_DEF_H_
#define _DataSourcesFile_DEF_H_

#if defined  DataSourcesFile_EXPORTS
#define DSFile_DLL __declspec(dllexport)
#else
#define DSFile_DLL __declspec(dllimport)
#pragma comment(lib,"DataSourcesFile.lib")
#pragma message("Automatically linking with DataSourcesFile.dll")

#endif

#endif
