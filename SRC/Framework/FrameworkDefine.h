//////////////////////////////////////////////////////////////////////
// ��Ȩ(c) 2010-2020, ����ǻ�
// ���ߣ�  leo
// ʱ�䣺  2010.12
// ������  Framework��Ļ�������
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