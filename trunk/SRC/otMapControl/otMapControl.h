#pragma once

// otMapControl.h : otMapControl.DLL ����ͷ�ļ�

#if !defined( __AFXCTL_H__ )
#error "�ڰ������ļ�֮ǰ������afxctl.h��"
#endif

#include "resource.h"       // ������
#include "otMapControlidl.h"

// CotMapControlApp : �й�ʵ�ֵ���Ϣ������� otMapControl.cpp��

class CotMapControlApp : public COleControlModule
{
public:
	BOOL InitInstance();
	int ExitInstance();
};

extern const GUID CDECL _tlid;
extern const WORD _wVerMajor;
extern const WORD _wVerMinor;

