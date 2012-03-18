#pragma once
#include "resource.h"
#include "SymbolPreviewButton.h"
#include "IFrameElementBase.h"

// CElementFramePage 对话框

class CElementFramePage : public CPropertyPage
{
	DECLARE_DYNAMIC(CElementFramePage)

public:
	CElementFramePage();   // 标准构造函数
	virtual ~CElementFramePage();

	virtual BOOL OnInitDialog();
	void SetCtrls();
	void SetElement(Element::IFrameElementBasePtr pElement);
	BOOL OnApply();

	void UpdateCtrl();

	afx_msg void OnBnClickedBtnBordersymbol();
	afx_msg void OnBnClickedBtnBgsymbol();
	afx_msg void OnBnClickedBtnShadowsymbol();
	afx_msg void OnBnClickedChkDrawBorder();
	afx_msg void OnBnClickedChkDrawBg();
	afx_msg void OnBnClickedChkDrawShadow();
// 对话框数据
	enum { IDD = IDD_PAGE_ELEMENT_FRAME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()


private:
	Element::IFrameElementBasePtr m_pElement;

	//预览边界按钮
	CSymbolPreviewButton m_PreviewBorderBtn;
	float	m_fBorderGapX;
	float	m_fBorderGapY;
	int		m_bDrawBorder;

	//预览背景按钮
	CSymbolPreviewButton m_PreviewBgBtn;
	float	m_fBgGapX;
	float	m_fBgGapY;
	int		m_bDrawBg;

	//预览阴影按钮
	CSymbolPreviewButton m_PreviewShadowBtn;
	float	m_fShadowGapX;
	float	m_fShadowGapY;
	int		m_bDrawShadow;

	BOOL	m_bDrawDraftMode;

private:
	Element::CSimpleBorderPtr m_pBorder;
	Element::CSimpleBackgroundPtr m_pBg;
	Element::CSimpleShadowPtr m_pShadow;

	Display::ISymbolPtr m_BorderSymbol;
	Display::ISymbolPtr m_BgSymbol;
	Display::ISymbolPtr m_ShadowSymbol;
public:
	afx_msg void OnEnChangeEditBorderY();
	afx_msg void OnDeltaposSpinBorderX(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinBorderY(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinBgX(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnChangeEditBgX();
	afx_msg void OnEnChangeEditBgY();
	afx_msg void OnDeltaposSpinBgY(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnChangeEditShadowX();
	afx_msg void OnDeltaposSpinShadowX(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnChangeEditShadowY();
	afx_msg void OnDeltaposSpinShadowY(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedChkDrawDraft();
};
