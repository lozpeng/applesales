#pragma once
#include "resource.h"
#include "SymbolPreviewButton.h"
#include "IScaleBar.h"
// CScalebarMarkPage 对话框

class CScalebarMarkPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CScalebarMarkPage)

public:
	CScalebarMarkPage();
	virtual ~CScalebarMarkPage();
	void SetElement(Element::IScaleBarPtr pScaleBar);
	BOOL OnApply();
	BOOL OnInitDialog();
	BOOL SetCtrls();

// 对话框数据
	enum { IDD = IDD_PAGE_SCALEBAR_MARK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedBtnNumTextSymbol();
	afx_msg void OnBnClickedBtnMarkLineSymbol();


private:
	Element::IScaleBarPtr		m_pElement;
	Display::CTextSymbolPtr	m_NumTextSymbol;
	Display::ILineSymbolPtr	m_pMarkLineSymbol;	

private:
	CComboBox	m_cmbNumFreq;
	CComboBox	m_cmbNumPos;
	float		m_fNumGap;
	CSymbolPreviewButton m_PreviewNumBtn;

	CComboBox	m_cmbMarkFreq;
	CComboBox	m_cmbMarkPos;
	float		m_fMainDivH;
	float		m_fSubDivH;
	CSymbolPreviewButton m_PreviewMarkBtn;
	

public:
	afx_msg void OnCbnSelchangeCmbNumFrequency();
	afx_msg void OnCbnSelchangeCmbNumPos();
	afx_msg void OnEnChangeEditNumGap();
	afx_msg void OnDeltaposSpinNumGap(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCbnSelchangeCmbMarkFrequency();
	afx_msg void OnCbnSelchangeCmbMarkPos();
	afx_msg void OnEnChangeEditMainDivisionHeight();
	afx_msg void OnEnChangeEditSubDivisionHeight();
};
