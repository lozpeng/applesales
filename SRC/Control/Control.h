// Control.h : Control DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CControlApp
// �йش���ʵ�ֵ���Ϣ������� Control.cpp
//

class CControlApp : public CWinApp
{
public:
	CControlApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
