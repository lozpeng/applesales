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
    //�򿪷��ſ�
	bool OpenLib(const char *name);

	//�رմ򿪵ķ��ſ�
	void CloseLib();

	Display::ISymbolPtr GetSymbol(const char *name);



private:

	CSymbolLibLoader *m_pLoader;

};

}