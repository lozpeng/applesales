#pragma once
#include "afxwin.h"
#include "resource.h"

// CDlgChangeDetect 对话框

class CDlgChangeDetect : public CDialog
{
	DECLARE_DYNAMIC(CDlgChangeDetect)

public:
	CDlgChangeDetect(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgChangeDetect();

// 对话框数据
	enum { IDD = IDD_IMG_CHANGEDETECT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
