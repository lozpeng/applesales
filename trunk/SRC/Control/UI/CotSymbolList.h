#pragma once

#include "ISymbol.h"

namespace Control
{

class  CotSymbolList
{
public:
	CotSymbolList(void);
	~CotSymbolList(void);
public:
	Display::ISymbolPtr SelectSymbol( Display::ISymbolPtr pSymbol);
};

}

