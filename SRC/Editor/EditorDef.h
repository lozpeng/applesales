//////////////////////////////////////////////////////////////////////
// 版权(c) 2010-2020, 天地智绘
// 作者：  leo
// 时间：  2010.12
// 描述：  Editor库的基础定义
//////////////////////////////////////////////////////////////////////


#ifndef _Editor_Define_H
#define _Editor_Define_H

#if defined  CONTROL_EXPORTS
#define EDITOR_DLL __declspec(dllexport)
#else
#define EDITOR_DLL __declspec(dllimport)
#pragma comment(lib,"Editor.lib")
#pragma message("Automatically linking with Editor.dll")

#endif


#endif