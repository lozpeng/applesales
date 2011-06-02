#include "StdAfx.h"
#include "MyPropertyPage.h"

CMyPropertyPage::CMyPropertyPage(void)
{
}

CMyPropertyPage::CMyPropertyPage(UINT nIDTemplate, UINT nIDCaption)
	: CPropertyPage(nIDTemplate, nIDCaption)
{
}

CMyPropertyPage::CMyPropertyPage(LPCTSTR lpszTemplateName, UINT nIDCaption)
	: CPropertyPage(lpszTemplateName, nIDCaption)
{
}

CMyPropertyPage::~CMyPropertyPage(void)
{
}
IMPLEMENT_DYNCREATE(CMyPropertyPage, CPropertyPage)


BEGIN_MESSAGE_MAP(CMyPropertyPage, CPropertyPage)
	//{{AFX_MSG_MAP(CMyPropertyPage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

int CMyPropertyPage::DoWork()
{
	return 0;
}
