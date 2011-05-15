#include "stdafx.h"
#include "SymbolListCtrl.h"
#include "SymbolSelectDlg.h"
#include "DllResource.h"
#include "IUIObject.h"

#ifdef DEBUG
#define new DEBUG_NEW
#endif

static CSymbolListCtrl gSymbolList;

CSymbolListCtrl::CSymbolListCtrl()
{
	CreateAss(Framework::CommonUIName::AppSymbolLstCtrl);
	SetAutoDetroy(true);
}

CSymbolListCtrl::~CSymbolListCtrl()
{

}

Display::ISymbolPtr CSymbolListCtrl::SelectSymbol(Display::ISymbolPtr pSymbol)
{
	Display::ISymbolPtr pCopysymbol =pSymbol->Clone();
	Control::CDllResource hdll;
	CDlgSymbolSelect dlg;
	dlg.SetSymbol(pCopysymbol);

	if(dlg.DoModal()==IDOK)
	{
        return dlg.GetSymbol();
	}
	else
	{
		return pCopysymbol;
	}
	
}

Display::ISymbolPtr CSymbolListCtrl::SelectSymbol2(Display::ISymbolPtr pSymbol)
{
	Display::ISymbolPtr pCopysymbol =pSymbol->Clone();
	Control::CDllResource hdll;
	CDlgSymbolSelect dlg;
	dlg.SetSymbol(pCopysymbol);

	if(dlg.DoModal()==IDOK)
	{
		return dlg.GetSymbol();
	}
	else
	{
		return NULL;
	}

}