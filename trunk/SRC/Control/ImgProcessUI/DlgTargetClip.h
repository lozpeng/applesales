#pragma once


// CDlgTargetClip �Ի���

class CDlgTargetClip : public CDialog
{
	DECLARE_DYNAMIC(CDlgTargetClip)

public:
	CDlgTargetClip(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgTargetClip();

// �Ի�������
	enum { IDD = IDD_DIALOG_TARGETCLIP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
