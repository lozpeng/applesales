#pragma once
#include "afxwin.h"


// CDlgDrawingExport 对话框

class CDlgDrawingExport : public CDialog
{
	DECLARE_DYNAMIC(CDlgDrawingExport)

public:
	CDlgDrawingExport(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgDrawingExport();

// 对话框数据
	enum { IDD = IDD_DIG_DRAWINGEXPORT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_ComboxType;
	int		  m_DrawingType; 
	CString m_ExportPath;
	afx_msg void OnBnClickedBtnSlectpath();
	BOOL m_CheckAddMap;
	bool m_bExpoertAll;
	afx_msg void OnBnClickedRadioExportAll();
	afx_msg void OnBnClickedRadioExpoertSelected();
	afx_msg void OnBnClickedOk();
};
