#pragma once


// CDlgIncrementalExport �Ի���

class CDlgIncrementalExport : public CDialog
{
	DECLARE_DYNAMIC(CDlgIncrementalExport)

public:
	CDlgIncrementalExport(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgIncrementalExport();

// �Ի�������
	enum { IDD = IDD_DLG_IncrementalExport};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CString m_IncrementalPath;
	afx_msg void OnBnClickedBtnSlectpath();
};
