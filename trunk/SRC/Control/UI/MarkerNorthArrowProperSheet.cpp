#include "StdAfx.h"
#include "MarkerNorthArrowProperSheet.h"
#include "ILayoutCtrl.h"
#include "PageLayout.h"
#include "SymbolPreviewPage.h"
#include "ElementSizePositionPage.h"
//#include "ElementFramePage.h"



IMPLEMENT_DYNAMIC(CMarkerNorthArrowProperSheet, CElementProperSheet)


BEGIN_MESSAGE_MAP(CMarkerNorthArrowProperSheet, CElementProperSheet)
	ON_BN_CLICKED(ID_APPLY_NOW , &CMarkerNorthArrowProperSheet::OnApply)
END_MESSAGE_MAP()

CMarkerNorthArrowProperSheet::CMarkerNorthArrowProperSheet(CString name , CWnd *pWnd): CElementProperSheet(name , pWnd)
{
	m_psh.dwFlags &= ~PSH_HASHELP;
	m_pElement = NULL;
}

CMarkerNorthArrowProperSheet::~CMarkerNorthArrowProperSheet(void)
{
}

INT_PTR CMarkerNorthArrowProperSheet::DoModal()
{
	if (m_pElement == NULL)
	{
		return -1;
	}

	Framework::ILayoutCtrl *pLayoutCtrl =Framework::ILayoutCtrl::GetActiveLayoutCtrl();
	if(!pLayoutCtrl)
		return FALSE;

	Carto::CPageLayoutPtr pPageLayout = pLayoutCtrl->GetPageLayout();
	if(!pPageLayout)
		return FALSE;


	CSymbolPreviewPage symbolPage;
	symbolPage.SetElement(m_pElement);
	AddPage(&symbolPage);

	CElementSizePositionPage sizePosPage;
	sizePosPage.SetLayoutUnit(pPageLayout->GetDisplay()->GetDisplayTransformation().GetUnit());
	sizePosPage.SetElement(m_pElement);
	AddPage(&sizePosPage);

	//CElementFramePage FramePage;
	//FramePage.SetElement(m_pElement);
	//AddPage(&FramePage);

	return CPropertySheet::DoModal();
}

