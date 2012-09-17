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
	//待检测影像路径
	CString m_strSrc;
	CString m_strDest;
	BOOL m_bLoadShp;
	afx_msg void OnBnClickedBtnSelchashp();
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedCheckLoadchange();
	double m_dCor;
	int m_nSize;
	double m_dblH1;
	double m_dblH2;
	double m_dblP1;
	double m_dblP2;
	double m_dblW1;
	double m_dblW2;
	CString n_strRel2;
	CString m_strResult3;
	afx_msg void OnBnClickedBtnSelchashp2();
	afx_msg void OnBnClickedBtnSelchashp3();
	CString m_strRelMap;
	afx_msg void OnBnClickedBtnRelmap();
	int m_nBlockSize;
	CString m_strResult2;
	afx_msg void OnBnClickedBtnSelchashp4();
	afx_msg void OnEnChangeEditRelshp();
	afx_msg void OnCbnSelchangeComboDestimg();
	CComboBox m_comboTarget;
};
