#pragma once
#include <string>
#include "BlueToothCommDef.h"
namespace BlueToothComm
{

class BLUETOOTH_DLL CBlueTooth
{
public:
	CBlueTooth(void);
	~CBlueTooth(void);

public:
	//连接一个蓝牙设备
	bool Connect(const char *remote);

	bool IsConnect() {return m_bConnected;}

	bool SendFile(const char *filename);

	//关闭连接
	void Close();

private:
	bool m_bConnected;

	UINT_PTR m_socket;


};


}

