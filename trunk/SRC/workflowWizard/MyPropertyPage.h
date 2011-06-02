#pragma once
#include "afxdlgs.h"

class CMyPropertyPage :
	public CPropertyPage
{
	DECLARE_DYNCREATE(CMyPropertyPage)
public:
	CMyPropertyPage();
	CMyPropertyPage(UINT nIDTemplate, UINT nIDCaption = 0);
	CMyPropertyPage(LPCTSTR lpszTemplateName, UINT nIDCaption = 0);
public:
	~CMyPropertyPage(void);
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual int DoWork();
};
