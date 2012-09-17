#pragma once
#include "afxwin.h"


// CDlgFtrDectect �Ի���

class CDlgFtrDectect : public CDialog
{
	DECLARE_DYNAMIC(CDlgFtrDectect)

public:
	CDlgFtrDectect(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgFtrDectect();

// �Ի�������
	enum { IDD = IDD_DIALOG_FTRDETECT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_strInImg;
	afx_msg void OnBnClickedButtonInimg();
	CString m_strInImg2;
	CString m_strTargetFile;
	CString m_strResultFile;
	CComboBox m_comboTexOri;
	long m_targetSize;
	long m_blockSize;
	double m_P3;
	double m_H3;
	double m_H4;
	afx_msg void OnBnClickedButtonInimg2();
	afx_msg void OnBnClickedButtonTargetfile();
	afx_msg void OnBnClickedButtonTargetfile2();
	virtual BOOL OnInitDialog();
	BOOL m_c1;
	CComboBox m_CmbSrc;
	CComboBox m_CmbDest;
	CComboBox m_comboTarget;
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
};
