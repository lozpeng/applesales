//////////////////////////////////////////////////////////////////////
// ��Ȩ(c) 2010-2020, ����ǻ�
// ���ߣ�  leo
// ʱ�䣺  2010.12
// ������  Editor��Ļ�������
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