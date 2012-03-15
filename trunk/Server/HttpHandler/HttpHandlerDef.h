#ifndef _HTTPHANDLER_DEF_H_
#define _HTTPHANDLER_DEF_H_

#if defined  HTTPHANDLER_EXPORTS
#define HTTPHANDLER_DLL __declspec(dllexport)
#else
#define HTTPHANDLER_DLL __declspec(dllimport)
#pragma comment(lib,"HttpHandler.lib")
#pragma message("Automatically linking with HttpHandler.dll")

#endif


#endif