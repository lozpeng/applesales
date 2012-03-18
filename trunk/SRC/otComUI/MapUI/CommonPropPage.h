#pragma once

#include "ILayer.h"
#include "Resource.h"

class CCommonPropPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CCommonPropPage)

public:
	CCommonPropPage();
	virtual ~CCommonPropPage();
public:
	void SetLayer(Carto::ILayer* player);
	virtual BOOL OnSetActive();
	void SetModified(BOOL bChanged = TRUE);
	// 对话框数据
	enum { IDD = IDD_LAYER_COMMON_PROP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	void SetValuesToLayer();
	BOOL ValidateCheck();

	DECLARE_MESSAGE_MAP()
public:

	virtual BOOL OnInitDialog();

	afx_msg void OnEnChangeLayername();
	virtual BOOL OnApply();
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnEnChangeLayerdescrib();
	afx_msg void OnBnClickedLayervisible();
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnChangeScaleMax();
	afx_msg void OnChangeScaleMin();

	virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
	CEdit m_editLayerName;
	CEdit m_editLayerDescrib;

	CButton m_buttonLayerVisible;
	CButton m_buttonRadio1,m_buttonRadio2;

	CEdit m_editMax,m_editMin;
	//CEdit m_editDataSource;

	bool m_bAllowSetModified;
	bool m_bModified;
	Carto::ILayer* m_pLayer;

};
