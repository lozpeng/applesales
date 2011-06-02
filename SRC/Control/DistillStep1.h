#pragma once
#include "workflowWizardInclude.h"

// CDistillStep1 对话框

class CDistillStep1 : public CResizablePage,
   public TreePropSheet::CWhiteBackgroundProvider
{
	DECLARE_DYNAMIC(CDistillStep1)

public:
	CDistillStep1(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDistillStep1();

// 对话框数据
	enum { IDD = IDD_DISTILL_STEP1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
