//////////////////////////////////////////////////////////////////////
// ��Ȩ(c) 2010-2020, ����ǻ�
// ���ߣ�  leo
// ʱ�䣺  2010.12
// ������  Control��Ļ�������
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