
//////////////////////////////////////////////////////////////////////
  // ��Ȩ(c) 2010-2020, ����ǻ�
  // ���ߣ�  hhzhao
  // ʱ�䣺  2009/11/18
  // ������  DataSourcesFile��Ļ������壬���������ꡢ�������ӵĻ���ͷ�ļ���
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
