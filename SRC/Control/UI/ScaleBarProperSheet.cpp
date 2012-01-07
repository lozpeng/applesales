#include "StdAfx.h"
#include "ScaleBarProperSheet.h"
#include "ILayoutCtrl.h"
#include "PageLayout.h"





IMPLEMENT_DYNAMIC(CScaleBarProperSheet, CElementProperSheet)


BEGIN_MESSAGE_MAP(CScaleBarProperSheet, CElementProperSheet)
	ON_BN_CLICKED(ID_APPLY_NOW , &CScaleBarProperSheet::OnApply)
END_MESSAGE_MAP()

CScaleBarProperSheet::CScaleBarProperSheet(CString name , CWnd *pWnd): CElementProperSheet(name , pWnd)
{
	m_psh.dwFlags &= ~PSH_HASHELP;
	m_pElement = NULL;
}

CScaleBarProperSheet::~CScaleBarProperSheet(void)
{
}

void CScaleBarProperSheet::SetElement(Element::IScaleBarPtr  pElement)
{
	m_pElement = pElement;

	sizePosPage.SetElement(pElement);
	//FramePage.SetElement(pElement);
	MarkNumPage.SetElement(pElement);
	UnitPage.SetElement(pElement);
	StylePage.SetElement(pElement);
}

Element::IScaleBarPtr CScaleBarProperSheet::GetElement()
{
	return m_pElement;
}

INT_PTR CScaleBarProperSheet::DoModal()
{
	if (m_pElement == NULL)
	{
		return -1;
	}

	AddPage(&MarkNumPage);
	AddPage(&UnitPage);

	StylePage.SetSheet(this);
	AddPage(&StylePage);

	//AddPage(&FramePage);

	Framework::ILayoutCtrl *pLayoutCtrl =Framework::ILayoutCtrl::GetActiveLayoutCtrl();
	if(!pLayoutCtrl)
		return FALSE;

	Carto::CPageLayoutPtr pPageLayout = pLayoutCtrl->GetPageLayout();
	if(!pPageLayout)
		return FALSE;

	sizePosPage.SetLayoutUnit(pPageLayout->GetDisplay()->GetDisplayTransformation().GetUnit());
	AddPage(&sizePosPage);

	return CPropertySheet::DoModal();
}

