#pragma once
#include "otcDisplay.h"
#include "ISymbol.h"
class CInterfaceConvert
{
public:
	CInterfaceConvert(void);
	~CInterfaceConvert(void);
public:
    
	//从IotSymbol里获取symbol指针
	static Display::ISymbolPtr ConvertISymbol(IotSymbol *pSymbol);

	static void ConvertSymbol(Display::ISymbolPtr pSymbol,IotSymbol **retSymbol,bool bown =true);

	static void ConvertSymbol(Display::ISymbolPtr* ppSymbol,IotSymbol **retSymbol,bool bown =true);


    static otSymbolUnit ConvertSymbolUnit(SYSTEM::SYS_UNIT_TYPE unit);

	static SYSTEM::SYS_UNIT_TYPE ConvertSymbolUnit(otSymbolUnit unit);

};
