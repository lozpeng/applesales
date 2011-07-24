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
	//����һ�������豸
	bool Connect(const char *remote);

	bool IsConnect() {return m_bConnected;}

	bool SendFile(const char *filename);

	//�ر�����
	void Close();

private:
	bool m_bConnected;

	UINT_PTR m_socket;


};


}

