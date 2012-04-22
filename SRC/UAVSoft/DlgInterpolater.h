#pragma once


// CDlgInterpolater 对话框

class CDlgInterpolater : public CDialog
{
	DECLARE_DYNAMIC(CDlgInterpolater)

public:
	CDlgInterpolater(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgInterpolater();

// 对话框数据
	enum { IDD = IDD_DIG_Interpolater };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonOutputfile();
	CString m_strInputFile;
	CString m_strOutputFile;
	afx_msg void OnBnClickedButtonInputfile();
	double m_dbCellSize;
	double m_dbSearchRadius;
	afx_msg void OnBnClickedOk();
};
