// otComUI.h : otComUI DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CotComUIApp
// �йش���ʵ�ֵ���Ϣ������� otComUI.cpp
//

class CotComUIApp : public CWinApp
{
public:
	CotComUIApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
