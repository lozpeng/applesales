#ifndef _Control_Define_H
#define _Control_Define_H

#if defined  CONTROL_EXPORTS
#define CONTROL_DLL __declspec(dllexport)
#else
#define CONTROL_DLL __declspec(dllimport)
#pragma comment(lib,"Controls.lib")
#pragma message("Automatically linking with Controls.dll")

#endif


#endif //_Control_Define_H