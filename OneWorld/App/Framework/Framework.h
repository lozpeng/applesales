// Framework.h : Framework DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CFrameworkApp
// �йش���ʵ�ֵ���Ϣ������� Framework.cpp
//

class CFrameworkApp : public CWinApp
{
public:
	CFrameworkApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
