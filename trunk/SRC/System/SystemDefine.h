#ifndef _SYSTEM_DEFINE_H_
#define _SYSTEM_DEFINE_H_


#if defined SYSTEM_EXPORTS
#define SYSTEM_DLL __declspec(dllexport)
#else
#define SYSTEM_DLL __declspec(dllimport)
#pragma comment(lib,"BaseSystem.lib")
#pragma message("Automatically linking with BaseSystem.dll")
#endif

#include "SmartPtr.h"
#include "Configer.h"
#include "IArchive.h"
#include "ISerialization.h"
//#include "SysLog.h"
#include "SysPath.h"
#include "alm.h"


#endif