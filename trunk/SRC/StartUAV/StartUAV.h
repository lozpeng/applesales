// StartUAV.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CStartUAVApp:
// �йش����ʵ�֣������ StartUAV.cpp
//

class CStartUAVApp : public CWinApp
{
public:
	CStartUAVApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CStartUAVApp theApp;