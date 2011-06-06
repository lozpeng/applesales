#pragma once


// CDlgIncrementalExport 对话框

class CDlgIncrementalExport : public CDialog
{
	DECLARE_DYNAMIC(CDlgIncrementalExport)

public:
	CDlgIncrementalExport(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgIncrementalExport();

// 对话框数据
	enum { IDD = IDD_DLG_IncrementalExport};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CString m_IncrementalPath;
	afx_msg void OnBnClickedBtnSlectpath();
};
