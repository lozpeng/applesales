#pragma once
#include "Resource.h"
#include "SymbolPreviewButton.h"
#include "IElement.h"

class CSymbolPreviewPage :
	public CPropertyPage
{
	DECLARE_DYNCREATE(CSymbolPreviewPage)

public:

	CSymbolPreviewPage(void);
	~CSymbolPreviewPage(void);

	enum { IDD = IDD_SYMBOL_PREVIEW_PAGE };

	BOOL OnInitDialog();
	void SetElement(Element::IElementPtr pElement);
	virtual BOOL OnApply();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ÷ß≥÷

	DECLARE_MESSAGE_MAP()

	
public:
	afx_msg void OnBnClickedSrSymbolset();

private:
	Element::IElementPtr m_pElement;
	Display::ISymbolPtr m_pSymbol;

	//‘§¿¿∞¥≈•
	CSymbolPreviewButton m_PreviewBtn;

};
