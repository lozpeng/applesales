#pragma once

#include "DialogCreateRoi.h"
#include "afxwin.h"
// CSuperClassDlg �Ի���

class CSuperClassDlg : public CDialog
{
	DECLARE_DYNAMIC(CSuperClassDlg)

public:
	CSuperClassDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSuperClassDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_SUPERCLASS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
public:
	std::vector<ROI_INFO*>		m_Rois;
	std::string					m_strName;
	CString m_strInputFile;
	afx_msg void OnBnClickedOk();
	CListBox m_lstCls;
};
