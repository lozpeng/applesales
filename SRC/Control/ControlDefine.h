//////////////////////////////////////////////////////////////////////
// 版权(c) 2010-2020, 天地智绘
// 作者：  leo
// 时间：  2010.12
// 描述：  Control库的基础定义
//////////////////////////////////////////////////////////////////////


#ifndef _Control_Define_H
#define _Control_Define_H

#if defined  CONTROL_EXPORTS
#define CONTROL_DLL __declspec(dllexport)
#else
#define CONTROL_DLL __declspec(dllimport)
#pragma comment(lib,"Control.lib")
#pragma message("Automatically linking with Control.dll")

#endif


#endif