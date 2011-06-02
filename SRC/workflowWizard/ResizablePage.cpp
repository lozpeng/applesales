// ResizablePage.cpp : implementation file
//
/////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2000-2002 by Paolo Messina
// (http://www.geocities.com/ppescher - ppescher@yahoo.com)
//
// The contents of this file are subject to the Artistic License (the "License").
// You may not use this file except in compliance with the License. 
// You may obtain a copy of the License at:
// http://www.opensource.org/licenses/artistic-license.html
//
// If you find this code useful, credits would be nice!
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ResizablePage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CResizablePage

IMPLEMENT_DYNCREATE(CResizablePage, CMyPropertyPage)

CResizablePage::CResizablePage()
{
}

CResizablePage::CResizablePage(UINT nIDTemplate, UINT nIDCaption)
	: CMyPropertyPage(nIDTemplate, nIDCaption)
{
}

CResizablePage::CResizablePage(LPCTSTR lpszTemplateName, UINT nIDCaption)
	: CMyPropertyPage(lpszTemplateName, nIDCaption)
{
}

CResizablePage::~CResizablePage()
{
}


BEGIN_MESSAGE_MAP(CResizablePage, CMyPropertyPage)
	//{{AFX_MSG_MAP(CResizablePage)
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CResizablePage message handlers

void CResizablePage::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	
	ArrangeLayout();
}

BOOL CResizablePage::OnEraseBkgnd(CDC* pDC) 
{
	// Windows XP doesn't like clipping regions ...try this!
	EraseBackground(pDC);
	return TRUE;

/*	ClipChildren(pDC);	// old-method (for safety)
	
	return CMyPropertyPage::OnEraseBkgnd(pDC);
*/
}
int CResizablePage::DoWork()
{
	return 0;
}
//й╣ож
void DeletePages(std::vector<CPropertySheet*>& containerSheet)
{
	for( std::vector<CPropertySheet*>::iterator itSheet = containerSheet.begin(); 
		containerSheet.end() != itSheet; ++itSheet )
	{
		// Delete the pages.
		int nCount = (*itSheet)->GetPageCount();
		for( int nCurrent = 0; nCurrent < nCount; ++nCurrent )
		{
			CPropertyPage* pPage = (*itSheet)->GetPage( 0 );
			(*itSheet)->RemovePage( 0 );
			delete pPage;
		}

		// Destroy the associated window.
		if( ::IsWindow( (*itSheet)->GetSafeHwnd() ) )
			::DestroyWindow( (*itSheet)->GetSafeHwnd() );
		// Delete the sheet object.
		delete *itSheet;
	}
}