#pragma once
#include "workflowWizardInclude.h"

// CDistillStep1 �Ի���

class CDistillStep1 : public CResizablePage,
   public TreePropSheet::CWhiteBackgroundProvider
{
	DECLARE_DYNAMIC(CDistillStep1)

public:
	CDistillStep1(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDistillStep1();

// �Ի�������
	enum { IDD = IDD_DISTILL_STEP1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
