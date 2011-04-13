#pragma once
#include "Resource.h"
#include "SymbolPreviewButton.h"
#include "ITextElement.h"

class CTextSymbolPreviewPage :
	public CPropertyPage
{
	DECLARE_DYNCREATE(CTextSymbolPreviewPage)

public:

	CTextSymbolPreviewPage(void);
	~CTextSymbolPreviewPage(void);

	enum { IDD = IDD_TEXT_SYMBOL_PREVIEW_PAGE };

	BOOL OnInitDialog();
	void SetElement(Element::ITextElementPtr pElement);
	virtual BOOL OnApply();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ÷ß≥÷

	DECLARE_MESSAGE_MAP()

	
public:
	afx_msg void OnBnClickedTextSymbolset();
	afx_msg void OnBnClickedFillSymbolset();

private:
	Element::ITextElementPtr m_pElement;
	Display::ISymbolPtr m_pTextSymbol;
	Display::ISymbolPtr m_pFillSymbol;

	//‘§¿¿∞¥≈•
	CSymbolPreviewButton m_TextPreviewBtn;
	CSymbolPreviewButton m_FillPreviewBtn;

	BOOL m_bDrawBg;

public:
	afx_msg void OnBnClickedCheckDrawBg();
};
