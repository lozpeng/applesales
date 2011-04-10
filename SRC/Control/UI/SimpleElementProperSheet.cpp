#include "StdAfx.h"
#include "SimpleElementProperSheet.h"
#include "ElementSizePositionPage.h"
#include "SymbolPreviewPage.h"
#include "IMapCtrl.h"
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

	//获取活动制图控件
	Framework::IMapCtrl* pMapCtrl = Framework::IMapCtrl::GetActiveMapCtrl();
	if(!pMapCtrl)
		return -1;

	Carto::CMapPtr pMap = pMapCtrl->GetMap();
	if(!pMap)
		return FALSE;

	CElementSizePositionPage sizePosPage;
	sizePosPage.SetLayoutUnit(pMap->GetDisplay()->GetDisplayTransformation().GetUnit());
	sizePosPage.SetElement(m_pElement);
	AddPage(&sizePosPage);

	CSymbolPreviewPage symbolPage;
	symbolPage.SetElement(m_pElement);
	AddPage(&symbolPage);

	return CPropertySheet::DoModal();
}

