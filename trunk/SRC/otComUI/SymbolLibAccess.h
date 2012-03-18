#pragma once

#include "ISymbol.h"

class CSymbolLibLoader;

namespace otComUI
{
class otComUI_DLL CSymbolLibAccess
{
public:
    CSymbolLibAccess();
	~CSymbolLibAccess();


public:
    //打开符号库
	bool OpenLib(const char *name);

	//关闭打开的符号库
	void CloseLib();

	Display::ISymbolPtr GetSymbol(const char *name);



private:

	CSymbolLibLoader *m_pLoader;

};

}