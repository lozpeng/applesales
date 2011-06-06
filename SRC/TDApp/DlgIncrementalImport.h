#pragma once


// CDlgIncrementalImport 对话框

class CDlgIncrementalImport : public CDialog
{
	DECLARE_DYNAMIC(CDlgIncrementalImport)

public:
	CDlgIncrementalImport(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgIncrementalImport();

// 对话框数据
	enum { IDD = IDD_DIG_IncrementalImport };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedBtnSlectpath();
	CString m_IncrementalPath;
};
