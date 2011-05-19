#pragma once
#include "afxwin.h"
//
#include "ILayer.h"
#include "FeatureLayer.h"
// CDlgObjExport 对话框



class CDlgObjExport : public CDialog
{
	DECLARE_DYNAMIC(CDlgObjExport)

public:
	CDlgObjExport(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgObjExport();

// 对话框数据
	enum { IDD = IDD_OBJ_EXPORT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_Combox_Export;
	bool m_bExpoertAll ;

	Carto::IFeatureLayerPtr m_SrcFeatureLayer;
	afx_msg void OnBnClickedRadioExpoertSelected();
	afx_msg void OnBnClickedRadioExportAll();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();


public:
	void FeatureLayer2Featurelayer(Carto::IFeatureLayerPtr pSrcFeature,Carto::IFeatureLayerPtr pDestFeatureLayer);
};
