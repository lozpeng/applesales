#pragma once

#include "ISymbol.h"

namespace otComUI
{


class otComUI_DLL CotSymbolList
{
public:
	CotSymbolList(void);
	~CotSymbolList(void);
public:
	Display::ISymbolPtr SelectSymbol( Display::ISymbolPtr pSymbol);
};


}

