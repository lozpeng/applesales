#ifndef _BLUETOOTHCOMM_DEF_H_
#define _BLUETOOTHCOMM_DEF_H_

#if defined  BLUETOOTHCOMM_EXPORTS
#define BLUETOOTH_DLL __declspec(dllexport)
#else
#define BLUETOOTH_DLL __declspec(dllimport)
#pragma comment(lib,"BlueToothComm.lib")
#pragma message("Automatically linking with BlueToothComm.dll")
#endif

#endif