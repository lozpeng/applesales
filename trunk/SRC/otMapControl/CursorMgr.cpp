#include "StdAfx.h"
#include "CursorMgr.h"
#include "resource.h"
#include "IAction.h"

CCursorMgr *g_pCursorMgr=NULL;

CCursorMgr::CCursorMgr(HMODULE hResource)
{
	for(int i = 0 ; i < CURSOR_COUNT ; i++ )
		m_cursors.push_back( ::LoadCursor( hResource , MAKEINTRESOURCE( i + IDC_NORMAL) ) );
}

CCursorMgr::~CCursorMgr()
{
	for(int i = 0 ; i < CURSOR_COUNT ; i++ )
		DeleteObject( m_cursors[i] );
	m_cursors.clear();
}


HCURSOR CCursorMgr::GetCursor(long type)
{
	if( g_pCursorMgr->m_cursors.size() > (long)type )
		return g_pCursorMgr->m_cursors[(long)type];
	else
		return g_pCursorMgr->m_cursors[0];
}