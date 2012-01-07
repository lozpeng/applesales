#include "StdAfx.h"
#include "MapTitleProperSheet.h"
#include "TextContentPage.h"
#include "ILayoutCtrl.h"
#include "PageLayout.h"
#include "ElementSizePositionPage.h"
#include "SymbolPreviewPage.h"
//#include "ElementFramePage.h"
#include "TextContentPage.h"
#include "ITextElement.h"

IMPLEMENT_DYNAMIC(CMapTitleProperSheet, CElementProperSheet)


BEGIN_MESSAGE_MAP(CMapTitleProperSheet, CElementProperSheet)
	ON_BN_CLICKED(ID_APPLY_NOW , &CMapTitleProperSheet::OnApply)
END_MESSAGE_MAP()

CMapTitleProperSheet::CMapTitleProperSheet(CString name , CWnd *pWnd): CElementProperSheet(name , pWnd)
{
	m_psh.dwFlags &= ~PSH_HASHELP;
	m_pElement = NULL;
}

CMapTitleProperSheet::~CMapTitleProperSheet(void)
{
}

INT_PTR CMapTitleProperSheet::DoModal()
{
	if (m_pElement == NULL)
	{
		return -1;
	}

	CTextContentPage TextPage;
	TextPage.SetElement(m_pElement);	
	AddPage(&TextPage);

	CSymbolPreviewPage symbolPage;
	symbolPage.SetElement(m_pElement);
	AddPage(&symbolPage);

	//CElementFramePage FramePage;
	//FramePage.SetElement(m_pElement);
	//AddPage(&FramePage);

	Framework::ILayoutCtrl *pLayoutCtrl =Framework::ILayoutCtrl::GetActiveLayoutCtrl();
	if(!pLayoutCtrl)
		return FALSE;

	Carto::CPageLayoutPtr pPageLayout = pLayoutCtrl->GetPageLayout();
	if(!pPageLayout)
		return FALSE;

	CElementSizePositionPage sizePosPage;
	sizePosPage.SetLayoutUnit(pPageLayout->GetDisplay()->GetDisplayTransformation().GetUnit());
	sizePosPage.SetElement(m_pElement);
	AddPage(&sizePosPage);

	return CPropertySheet::DoModal();
}

