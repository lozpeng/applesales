#pragma once
#include "resource.h"

// CCustomScaleDlg �Ի���

class CCustomScaleDlg : public CDialog
{
	DECLARE_DYNAMIC(CCustomScaleDlg)

public:
	CCustomScaleDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCustomScaleDlg();

	BOOL OnInitDialog();

// �Ի�������
	enum { IDD = IDD_DLG_CUSTOM_SCALE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	double m_dbScale;
	CString m_csScale;
	afx_msg void OnBnClickedOk();
};
