#pragma once
#include "resource.h"
#include "SymbolPreviewButton.h"
#include "IScaleBar.h"

// CScalebarUnitPage 对话框

class CScalebarUnitPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CScalebarUnitPage)

public:
	CScalebarUnitPage();
	virtual ~CScalebarUnitPage();

// 对话框数据
	enum { IDD = IDD_PAGE_SCALEBAR_UNIT };

public:
	void SetElement(Element::IScaleBarPtr pScaleBar);
	BOOL OnApply();
	BOOL OnInitDialog();
	BOOL SetCtrls();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

private:
	Element::IScaleBarPtr		m_pElement;
	Display::CTextSymbolPtr	m_pUnitTextSymbol;

private:
	int m_nNumDiv;
	int m_nNumSubDiv;
	BOOL m_bDivBfZero;
	CComboBox	m_cmbUnit;
	CComboBox	m_cmbUnitPos;
	float m_fUnitGap;
	CSymbolPreviewButton m_PreviewUnitBtn;
public:
	afx_msg void OnBnClickedBtnSetUnitSymbol();
	afx_msg void OnEnChangeEditMainDivisionNum();
	afx_msg void OnDeltaposSpinMainDivisionNum(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnChangeEditSubDivisionNum();
	afx_msg void OnDeltaposSpinSubDivisionNum(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedChkDivisionBfZero();
	afx_msg void OnCbnSelchangeComboUnit();
	afx_msg void OnCbnSelchangeComboUnitPos();
	afx_msg void OnEnChangeEditunitGap();
	afx_msg void OnDeltaposSpinUnitGap(NMHDR *pNMHDR, LRESULT *pResult);
};
