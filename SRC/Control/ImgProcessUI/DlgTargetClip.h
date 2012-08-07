#pragma once


// CDlgTargetClip 对话框

class CDlgTargetClip : public CDialog
{
	DECLARE_DYNAMIC(CDlgTargetClip)

public:
	CDlgTargetClip(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgTargetClip();

// 对话框数据
	enum { IDD = IDD_DIALOG_TARGETCLIP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_strInImg;
	CString m_strTargetFile;
	CString m_strOutPath;
	long m_lWidth;
	long m_lHeight;
	afx_msg void OnBnClickedOk();
	CString m_strInImg2;
	afx_msg void OnBnClickedButtonInimg();
	afx_msg void OnBnClickedButtonInimg2();
	afx_msg void OnBnClickedButtonTargetfile();
};
