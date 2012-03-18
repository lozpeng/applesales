#include "StdAfx.h"
#include "SimpleTextProperSheet.h"
#include "TextContentPage.h"
//#include "GeoPageLayout.h"
#include "ElementSizePositionPage.h"
#include "TextSymbolPreviewPage.h"
#include "TextContentPage.h"

IMPLEMENT_DYNAMIC(CSimpleTextProperSheet, CElementProperSheet)


BEGIN_MESSAGE_MAP(CSimpleTextProperSheet, CElementProperSheet)
	ON_BN_CLICKED(ID_APPLY_NOW , &CSimpleTextProperSheet::OnApply)
END_MESSAGE_MAP()

CSimpleTextProperSheet::CSimpleTextProperSheet(CString name , CWnd *pWnd): CElementProperSheet(name , pWnd)
{
	m_psh.dwFlags &= ~PSH_HASHELP;
	m_pElement = NULL;
}

CSimpleTextProperSheet::~CSimpleTextProperSheet(void)
{
}

INT_PTR CSimpleTextProperSheet::DoModal()
{
	if (m_pElement == NULL)
	{
		return -1;
	}

	CTextContentPage TextPage;
	TextPage.SetElement(m_pElement);	
	AddPage(&TextPage);

	CTextSymbolPreviewPage symbolPage;
	symbolPage.SetElement(m_pElement);
	AddPage(&symbolPage);

	//获取活动制图控件
	
	CElementSizePositionPage sizePosPage;
	sizePosPage.SetLayoutUnit(m_pMap->GetDisplay()->GetDisplayTransformation().GetUnit());
	sizePosPage.SetElement(m_pElement);
	AddPage(&sizePosPage);


	return CPropertySheet::DoModal();
}

