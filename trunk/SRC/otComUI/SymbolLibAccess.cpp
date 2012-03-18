#include "StdAfx.h"
#include "SymbolLibAccess.h"
#include "SymbollibLoader.h"

namespace otComUI
{

CSymbolLibAccess::CSymbolLibAccess()
{
    m_pLoader =new CSymbolLibLoader();

}

CSymbolLibAccess::~CSymbolLibAccess()
{
    if(m_pLoader)
	{
		delete m_pLoader;
	}
}

bool CSymbolLibAccess::OpenLib(const char *name)
{
    if(!m_pLoader)
	{
		return false;
	}
	m_pLoader->CloseDatabase();

	//´ò¿ª·ûºÅ¿â
	return m_pLoader->OpenDatabase(name);


}


void CSymbolLibAccess::CloseLib()
{
	if(m_pLoader)
	{
		m_pLoader->CloseDatabase();
	}
}


Display::ISymbolPtr CSymbolLibAccess::GetSymbol(const char *name)
{
	if(!m_pLoader)
	{
		return NULL;
	}
    
	return m_pLoader->QuerySymbol(name);
}

}//namespace otComUI