#include "StdAfx.h"
#include "PictureElementProperSheet.h"
#include "ElementSizePositionPage.h"
#include "SymbolPreviewPage.h"
#include "ElementFramePage.h"
#include "PicturePathPage.h"
#include "Map.h"

IMPLEMENT_DYNAMIC(CPictureElementProperSheet, CElementProperSheet)


BEGIN_MESSAGE_MAP(CPictureElementProperSheet, CElementProperSheet)
	ON_BN_CLICKED(ID_APPLY_NOW , &CPictureElementProperSheet::OnApply)
END_MESSAGE_MAP()

CPictureElementProperSheet::CPictureElementProperSheet(CString name , CWnd *pWnd): CElementProperSheet(name , pWnd)
{
	m_psh.dwFlags &= ~PSH_HASHELP;
	m_pElement = NULL;
}

CPictureElementProperSheet::~CPictureElementProperSheet(void)
{
}

INT_PTR CPictureElementProperSheet::DoModal()
{
	if (m_pElement == NULL)
	{
		return -1;
	}
	if(!m_pMap)
	{
		return -1;
	}

	//获取活动制图控件
	
	CPicturePathPage pathPage;
	pathPage.SetElement(m_pElement);
	AddPage(&pathPage);

	CElementSizePositionPage sizePosPage;
	sizePosPage.SetLayoutUnit(m_pMap->GetDisplay()->GetDisplayTransformation().GetUnit());
	sizePosPage.SetElement(m_pElement);
	AddPage(&sizePosPage);

	CElementFramePage framePage;
	framePage.SetElement(m_pElement);
	AddPage(&framePage);

	return CPropertySheet::DoModal();
}

