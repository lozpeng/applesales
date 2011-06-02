// Control.h : Control DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include "TreePropSheetEx.h"
#include <vector>

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
	virtual int ExitInstance();
public:
	std::vector<TreePropSheet::CTreePropSheetEx*> m_manageSheet;
	std::vector<CResizablePage*>  m_manageSheetPage;
};
extern CControlApp theApp;