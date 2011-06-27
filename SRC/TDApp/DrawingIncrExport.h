#pragma once
#include "afxwin.h"


// CDrawingIncrExport �Ի���

class CDrawingIncrExport : public CDialog
{
	DECLARE_DYNAMIC(CDrawingIncrExport)

public:
	CDrawingIncrExport(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDrawingIncrExport();

// �Ի�������
	enum { IDD = IDD_DIG_Drawing_IncrExport };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
