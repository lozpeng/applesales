#ifndef _SYSTEM_DEFINE_H_
#define _SYSTEM_DEFINE_H_


#if defined SYSTEM_EXPORTS
#define SYSTEM_DLL __declspec(dllexport)
#else
#define SYSTEM_DLL __declspec(dllimport)
#pragma comment(lib,"System.lib")
#pragma message("Automatically linking with System.dll")
#endif

#include "SmartPtr.h"

#endif