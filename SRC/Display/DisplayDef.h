//////////////////////////////////////////////////////////////////////
// ��Ȩ(c) 2010-2020, ����ǻ�
// ���ߣ�  9527
// ʱ�䣺  2008/11/27
// ����
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