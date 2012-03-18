#pragma once
#include "resource.h"

// CCustomScaleDlg 对话框

class CCustomScaleDlg : public CDialog
{
	DECLARE_DYNAMIC(CCustomScaleDlg)

public:
	CCustomScaleDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCustomScaleDlg();

	BOOL OnInitDialog();

// 对话框数据
	enum { IDD = IDD_DLG_CUSTOM_SCALE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	double m_dbScale;
	CString m_csScale;
	afx_msg void OnBnClickedOk();
};
