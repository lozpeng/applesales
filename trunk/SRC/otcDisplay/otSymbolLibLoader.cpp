// otSymbolLibLoader.cpp : CotSymbolLibLoader µÄÊµÏÖ

#include "stdafx.h"
#include "otSymbolLibLoader.h"
#include "InterfaceConvert.h"

// CotSymbolLibLoader

CotSymbolLibLoader::CotSymbolLibLoader()
{
	m_lib =new otComUI::CSymbolLibAccess();
}

CotSymbolLibLoader::~CotSymbolLibLoader()
{
    if(m_lib)
	{
		delete m_lib;
	}
}
STDMETHODIMP CotSymbolLibLoader::Open(BSTR libName, VARIANT_BOOL* ret)
{
	_bstr_t name =libName;

	m_lib->OpenLib(name);

	return S_OK;
}

STDMETHODIMP CotSymbolLibLoader::GetSymbol(BSTR name,IotSymbol** retSymbol)
{
	_bstr_t str =name;
    
	Display::ISymbolPtr pSymbol =m_lib->GetSymbol(str);

    if(!pSymbol)
	{
		*retSymbol =NULL;
		return S_OK;
	}

	CInterfaceConvert::ConvertSymbol(pSymbol,retSymbol);

	return S_OK;
}
