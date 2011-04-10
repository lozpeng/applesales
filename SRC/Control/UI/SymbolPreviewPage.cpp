#include "StdAfx.h"
#include "SymbolPreviewPage.h"
#include "ISymbolListCtrl.h"

IMPLEMENT_DYNCREATE(CSymbolPreviewPage, CPropertyPage)

BEGIN_MESSAGE_MAP(CSymbolPreviewPage, CPropertyPage)

	ON_BN_CLICKED(IDC_SYMBOLSET, &CSymbolPreviewPage::OnBnClickedSrSymbolset)
END_MESSAGE_MAP()

CSymbolPreviewPage::CSymbolPreviewPage(void): CPropertyPage(CSymbolPreviewPage::IDD)
{
	m_psp.dwFlags &= ~PSP_HASHELP;
	m_pElement = NULL;

}

CSymbolPreviewPage::~CSymbolPreviewPage(void)
{
}

void CSymbolPreviewPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_SYMBOL_PREVIEW, m_PreviewBtn);
}

void CSymbolPreviewPage::SetElement(Element::IElementPtr pElement)
{
	m_pElement = pElement;
	m_pSymbol = m_pElement->GetSymbol();
}

BOOL CSymbolPreviewPage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	if (m_pElement == NULL)
		return FALSE;

	m_PreviewBtn.SetSymbol(m_pSymbol.get());

	return TRUE;
}


void CSymbolPreviewPage::OnBnClickedSrSymbolset()
{
	/*Framework::ISymbolListCtrl *pCtrl =dynamic_cast<Framework::ISymbolListCtrl*>(Framework::IUIObject::GetUIObjectByName(SYMBOLLISTCTRL));
	if(pCtrl)
	{
		m_pSymbol =pCtrl->SelectSymbol(m_pSymbol);
	}
	m_PreviewBtn.SetSymbol(m_pSymbol.get());

	SetModified();*/
}



BOOL CSymbolPreviewPage::OnApply()
{
	if(!IsWindow(m_hWnd))
		return FALSE;

	if (m_pElement == NULL)
		return FALSE;

	m_pElement->SetSymbol(m_pSymbol);
	return TRUE;
}
