#include "StdAfx.h"
#include "CotSymbolList.h"
#include "SymbolSelectDlg.h"

namespace otComUI
{

CotSymbolList::CotSymbolList(void)
{
}

CotSymbolList::~CotSymbolList(void)
{
}

Display::ISymbolPtr CotSymbolList::SelectSymbol(Display::ISymbolPtr pSymbol)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

	Display::ISymbolPtr pCopysymbol =pSymbol->Clone();
	CDlgSymbolSelect dlg;
	dlg.SetSymbol(pCopysymbol);

	if(dlg.DoModal()==IDOK)
	{
		return dlg.GetSymbol();
	}
	else
	{
		return pSymbol;
	}
    
}
	
}

