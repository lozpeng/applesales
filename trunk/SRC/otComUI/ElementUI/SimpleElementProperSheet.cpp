#include "StdAfx.h"
#include "SimpleElementProperSheet.h"
#include "ElementSizePositionPage.h"
#include "SymbolPreviewPage.h"
#include "Map.h"

IMPLEMENT_DYNAMIC(CSimpleElementProperSheet, CElementProperSheet)


BEGIN_MESSAGE_MAP(CSimpleElementProperSheet, CElementProperSheet)
	ON_BN_CLICKED(ID_APPLY_NOW , &CSimpleElementProperSheet::OnApply)
END_MESSAGE_MAP()

CSimpleElementProperSheet::CSimpleElementProperSheet(CString name , CWnd *pWnd): CElementProperSheet(name , pWnd)
{
	m_psh.dwFlags &= ~PSH_HASHELP;
	m_pElement = NULL;
}

CSimpleElementProperSheet::~CSimpleElementProperSheet(void)
{
}

INT_PTR CSimpleElementProperSheet::DoModal()
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

	CElementSizePositionPage sizePosPage;
	sizePosPage.SetLayoutUnit(m_pMap->GetDisplay()->GetDisplayTransformation().GetUnit());
	sizePosPage.SetElement(m_pElement);
	AddPage(&sizePosPage);

	CSymbolPreviewPage symbolPage;
	symbolPage.SetElement(m_pElement);
	AddPage(&symbolPage);

	return CPropertySheet::DoModal();
}

