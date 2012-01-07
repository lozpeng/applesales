#pragma once
#include "workflowWizardInclude.h"
#include "ILayer.h"
// CDistillStep2 对话框

class CDistillStep2: public CResizablePage,
   public TreePropSheet::CWhiteBackgroundProvider
{
	DECLARE_DYNAMIC(CDistillStep2)

public:
	CDistillStep2(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDistillStep2();

// 对话框数据
	enum { IDD = IDD_DISTILL_STEP2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	double m_dTol;
	int m_nMinArea;
	Carto::ILayerPtr m_pTargetLyr;
	void SetTargetLyr(Carto::ILayerPtr pLyr){m_pTargetLyr = pLyr;};


	virtual int DoWork(); 
	virtual void OnOK();
	CString m_shpfile;
	afx_msg void OnBnClickedBtnSelexshp();
};
