#ifndef _OT_COMUI_DEF_H_
#define _OT_COMUI_DEF_H_

#if defined OTCOMUI_EXPORTS
#define otComUI_DLL __declspec(dllexport)
#else
#define otComUI_DLL __declspec(dllimport)

#pragma comment(lib,"ComUI.lib")
#pragma message("Automatically linking with ComUI.dll")

#endif
#endif