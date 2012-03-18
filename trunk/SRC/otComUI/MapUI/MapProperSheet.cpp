#include "StdAfx.h"
#include "MapProperSheet.h"
#include "MapBasicProperPage.h"

IMPLEMENT_DYNAMIC(CMapProperSheet, CPropertySheet)

BEGIN_MESSAGE_MAP(CMapProperSheet, CPropertySheet)
END_MESSAGE_MAP()

CMapProperSheet::CMapProperSheet(CString name , CWnd *pWnd): CPropertySheet(name , pWnd)
{
	m_psh.dwFlags &= ~PSH_HASHELP;
	m_pMap = NULL;
}

CMapProperSheet::~CMapProperSheet(void)
{
}

void CMapProperSheet::SetMap(Carto::CMapPtr pMap)
{
	m_pMap = pMap;
}

INT_PTR CMapProperSheet::DoModal()
{
	if (m_pMap == NULL)
	{
		return -1;
	}

	CMapBasicProperPage BasicProperPage;
	BasicProperPage.SetMap(m_pMap);
	AddPage(&BasicProperPage);

	return CPropertySheet::DoModal();
}

