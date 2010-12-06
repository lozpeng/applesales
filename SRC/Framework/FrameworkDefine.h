//////////////////////////////////////////////////////////////////////
// 版权(c) 2010-2020, 天地智绘
// 作者：  leo
// 时间：  2010.12
// 描述：  Framework库的基础定义
//////////////////////////////////////////////////////////////////////


#ifndef _Frame_Define_H
#define _Frame_Define_H

#if defined  FRAMEWORK_EXPORTS
#define FRAMEWORK_DLL __declspec(dllexport)
#else
#define FRAMEWORK_DLL __declspec(dllimport)
#pragma comment(lib,"Framework.lib")
#pragma message("Automatically linking with Framework.dll")

#endif


#endif