//////////////////////////////////////////////////////////////////////
  // ��Ȩ(c) 2010-2020, ����ǻ�
  // ���ߣ�  hhzhao
  // ʱ�䣺  2010/11/18
  // ������  carto��Ļ������壬���������ꡢ�������ӵĻ���ͷ�ļ���
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