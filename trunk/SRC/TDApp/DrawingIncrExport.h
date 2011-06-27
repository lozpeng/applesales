#pragma once
#include "afxwin.h"


// CDrawingIncrExport 对话框

class CDrawingIncrExport : public CDialog
{
	DECLARE_DYNAMIC(CDrawingIncrExport)

public:
	CDrawingIncrExport(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDrawingIncrExport();

// 对话框数据
	enum { IDD = IDD_DIG_Drawing_IncrExport };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()


	BOOL OnInitDialog();
public:
	CComboBox m_ComboxType;
	BOOL m_bExpoertAll;
	CComboBox m_Combo_TagertLayer;
	CString m_ExportPath;
	CString m_TargetLayerName_P,m_TargetLayerName_L,m_TargetLayerName_A;
	int m_DrawingType;
	afx_msg void OnBnClickedBtnSlectpath();
	afx_msg void OnBnClickedOk();
	afx_msg void OnCbnSelendcancelComboDrawingtype();
	afx_msg void OnBnClickedRadioExportAll();
	afx_msg void OnBnClickedRadioExpoertSelected();
	afx_msg void OnCbnSelchangeComboDrawingtype();
	CComboBox m_Combox_Export_P;
	CComboBox m_Combox_Export_L;
	CComboBox m_Combox_Export_A;
};
