#pragma once


// CDlgIncrementalImport �Ի���

class CDlgIncrementalImport : public CDialog
{
	DECLARE_DYNAMIC(CDlgIncrementalImport)

public:
	CDlgIncrementalImport(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgIncrementalImport();

// �Ի�������
	enum { IDD = IDD_DIG_IncrementalImport };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedBtnSlectpath();
	CString m_IncrementalPath;
};
