// otSymbolConvert.cpp : CotSymbolConvert µÄÊµÏÖ

#include "stdafx.h"
#include "otSymbolConvert.h"
#include "InterfaceConvert.h"

// CotSymbolConvert


STDMETHODIMP CotSymbolConvert::ConvertSymbol(LONG ldata, VARIANT_BOOL bown, IotSymbol** retSymbol)
{
	Display::ISymbolPtr* ppSymbol =(Display::ISymbolPtr*)ldata;

	CInterfaceConvert::ConvertSymbol(ppSymbol,retSymbol,(bown==VARIANT_FALSE)?false:true);

	return S_OK;
}
