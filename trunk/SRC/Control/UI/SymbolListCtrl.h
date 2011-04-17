#ifndef _SYMBOLLISTCTRL_H_
#define _SYMBOLLISTCTRL_H_

#include "ISymbolListCtrl.h"

class  CSymbolListCtrl : public Framework::ISymbolListCtrl 
{
public:
	CSymbolListCtrl();
	virtual ~CSymbolListCtrl();
public:
	 Display::ISymbolPtr SelectSymbol( Display::ISymbolPtr pSymbol = NULL);
	 Display::ISymbolPtr SelectSymbol2( Display::ISymbolPtr pSymbol = NULL);
};


#endif 