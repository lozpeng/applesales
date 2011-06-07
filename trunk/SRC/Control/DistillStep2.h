#pragma once
#include "workflowWizardInclude.h"

// CDistillStep2 �Ի���

class CDistillStep2: public CResizablePage,
   public TreePropSheet::CWhiteBackgroundProvider
{
	DECLARE_DYNAMIC(CDistillStep2)

public:
	CDistillStep2(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDistillStep2();

// �Ի�������
	enum { IDD = IDD_DISTILL_STEP2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	double m_dTol;
	int m_nMinArea;
	virtual BOOL OnApply();
	virtual void OnOK();
};
