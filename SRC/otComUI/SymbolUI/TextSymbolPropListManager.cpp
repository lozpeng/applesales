#include "StdAfx.h"
#include "TextSymbolPropListManager.h"

CTextSymbolPropListManager::CTextSymbolPropListManager(void)
{
	m_pSymbolPropList = NULL;
}

CTextSymbolPropListManager::~CTextSymbolPropListManager(void)
{
}

void CTextSymbolPropListManager::OnSymbolPropChanged( Display::ISymbolPtr newSymbol , CWnd *wnd )
{
	PostMessage( wnd->m_hWnd , WM_REPAINTLEGEND , 0 , 0 );
}