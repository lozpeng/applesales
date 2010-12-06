


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
