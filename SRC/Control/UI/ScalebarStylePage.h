#pragma once
#include "resource.h"
#include "SymbolPreviewButton.h"
#include "IScaleBar.h"
// CScalebarStylePage 对话框

class CScaleBarProperSheet;

class CScalebarStylePage : public CPropertyPage
{
	DECLARE_DYNAMIC(CScalebarStylePage)

public:
	CScalebarStylePage();
	virtual ~CScalebarStylePage();

	void SetSheet(CScaleBarProperSheet* pSheet ){m_pSheet = pSheet;};
	void SetElement(Element::IScaleBarPtr pScaleBar);
	BOOL OnApply();
	BOOL OnInitDialog();
	BOOL SetCtrls();

// 对话框数据
	enum { IDD = IDD_PAGE_SCALEBAR_FORMAT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedBtnSetTextSymbol();
	afx_msg void OnBnClickedBtnSetForeFillSymbol();
	afx_msg void OnBnClickedBtnSetFillBackSymbol();

private:
	CScaleBarProperSheet*		m_pSheet;

	Element::IScaleBarPtr		m_pElement;
	Display::CTextSymbolPtr	m_pTextSymbol;
	Display::ISymbolPtr		m_pForeSymbol;
	Display::ISymbolPtr		m_pBackSymbol;
	
	Element::ELEMENT_TYPE		m_ScaleBarType;


private:
	CSymbolPreviewButton m_PreviewTextBtn;
	CSymbolPreviewButton m_PreviewForeBtn;
	CSymbolPreviewButton m_PreviewBackBtn;

	CComboBox	m_cmbScalebarStyle;

public:
	afx_msg void OnCbnSelchangeCmbScalebarStyle();
};
