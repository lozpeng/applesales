// workflowWizard.h : workflowWizard DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CworkflowWizardApp
// �йش���ʵ�ֵ���Ϣ������� workflowWizard.cpp
//

class CworkflowWizardApp : public CWinApp
{
public:
	CworkflowWizardApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
