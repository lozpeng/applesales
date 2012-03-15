#ifndef _SERVERBASE_DEF_H_
#define _SERVERBASE_DEF_H_

#if defined  SERVERBASE_EXPORTS
#define SERVERBASE_DLL __declspec(dllexport)
#else
#define SERVERBASE_DLL __declspec(dllimport)
#pragma comment(lib,"ServerBase.lib")
#pragma message("Automatically linking with ServerBase.dll")

#endif


#endif