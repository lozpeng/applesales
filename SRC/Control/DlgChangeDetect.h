#pragma once
#include "afxwin.h"
#include "resource.h"

// CDlgChangeDetect �Ի���

class CDlgChangeDetect : public CDialog
{
	DECLARE_DYNAMIC(CDlgChangeDetect)

public:
	CDlgChangeDetect(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgChangeDetect();

// �Ի�������
	enum { IDD = IDD_IMG_CHANGEDETECT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_CmbSrc;
	CComboBox m_CmbDest;
	CString m_strResult;
	BOOL m_bLoadShp;
	afx_msg void OnBnClickedBtnSelchashp();
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
