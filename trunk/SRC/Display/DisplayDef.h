//////////////////////////////////////////////////////////////////////
// 版权(c) 2010-2020, 天地智绘
// 作者：  9527
// 时间：  2008/11/27
// 描述
//////////////////////////////////////////////////////////////////////

#ifndef _DISPLAY_DEFINE_H_
#define _DISPLAY_DEFINE_H_

#if defined DISPLAY_EXPORTS
#define DISPLAY_DLL __declspec(dllexport)
#else
#define DISPLAY_DLL __declspec(dllimport)
#pragma comment(lib,"Display.lib")
#pragma message("Automatically linking with Display.dll")
#endif

#endif //_DISPLAY_DEFINE_H_