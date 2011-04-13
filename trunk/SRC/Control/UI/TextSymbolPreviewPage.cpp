#include "StdAfx.h"
#include "TextSymbolPreviewPage.h"
#include "ISymbolListCtrl.h"

IMPLEMENT_DYNCREATE(CTextSymbolPreviewPage, CPropertyPage)

BEGIN_MESSAGE_MAP(CTextSymbolPreviewPage, CPropertyPage)
	ON_BN_CLICKED(IDC_TEXT_SYMBOLSET, &CTextSymbolPreviewPage::OnBnClickedTextSymbolset)
	ON_BN_CLICKED(IDC_FILL_SYMBOLSET, &CTextSymbolPreviewPage::OnBnClickedFillSymbolset)
	ON_BN_CLICKED(IDC_CHECK_DRAW_BG, &CTextSymbolPreviewPage::OnBnClickedCheckDrawBg)
END_MESSAGE_MAP()

CTextSymbolPreviewPage::CTextSymbolPreviewPage(void): CPropertyPage(CTextSymbolPreviewPage::IDD)
{
	m_psp.dwFlags &= ~PSP_HASHELP;
	m_pElement = NULL;

}

CTextSymbolPreviewPage::~CTextSymbolPreviewPage(void)
{
}

void CTextSymbolPreviewPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_TEXT_SYMBOL_PREVIEW, m_TextPreviewBtn);
	DDX_Control(pDX, IDC_FILL_SYMBOL_PREVIEW, m_FillPreviewBtn);
	DDX_Check(pDX, IDC_CHECK_DRAW_BG, m_bDrawBg);
}

void CTextSymbolPreviewPage::SetElement(Element::ITextElementPtr pElement)
{
	m_pElement = pElement;
	m_pTextSymbol = m_pElement->GetSymbol();
	m_pFillSymbol = m_pElement->GetFillSymbol();
	m_bDrawBg = m_pElement->GetDrawBg();
}

BOOL CTextSymbolPreviewPage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	if (m_pElement == NULL)
		return FALSE;

	m_TextPreviewBtn.SetSymbol(m_pTextSymbol.get());

	m_FillPreviewBtn.SetSymbol(m_pFillSymbol.get());

	GetDlgItem(IDC_FILL_SYMBOLSET)->EnableWindow(m_bDrawBg);

	UpdateData(FALSE);

	return TRUE;
}


void CTextSymbolPreviewPage::OnBnClickedTextSymbolset()
{
	/*otFramework::ISymbolListCtrl *pCtrl =dynamic_cast<otFramework::ISymbolListCtrl*>(otFramework::IUIObject::GetUIObjectByName(OT_SYMBOLLISTCTRL));
	if(pCtrl)
	{
		m_pTextSymbol =pCtrl->SelectSymbol(m_pTextSymbol);
	}
	m_TextPreviewBtn.SetSymbol(m_pTextSymbol.get());

	SetModified();*/
}

void CTextSymbolPreviewPage::OnBnClickedFillSymbolset()
{
	/*Framework::ISymbolListCtrl *pCtrl =dynamic_cast<Framework::ISymbolListCtrl*>(Framework::IUIObject::GetUIObjectByName(OT_SYMBOLLISTCTRL));
	if(pCtrl)
	{
		m_pFillSymbol =pCtrl->SelectSymbol(m_pFillSymbol);
	}
	m_FillPreviewBtn.SetSymbol(m_pFillSymbol.get());

	SetModified();*/
}




BOOL CTextSymbolPreviewPage::OnApply()
{
	if(!IsWindow(m_hWnd))
		return FALSE;

	if (m_pElement == NULL)
		return FALSE;

	UpdateData(TRUE);

	m_pElement->SetSymbol(m_pTextSymbol);

	m_pElement->SetDrawBg(m_bDrawBg);

	m_pElement->SetFillSymbol(m_pFillSymbol);
	return TRUE;
}

void CTextSymbolPreviewPage::OnBnClickedCheckDrawBg()
{
	// TODO: 在此添加控件通知处理程序代码

	UpdateData(TRUE);

	GetDlgItem(IDC_FILL_SYMBOLSET)->EnableWindow(m_bDrawBg);
	
}
