#include "StdAfx.h"
#include "ISymbolPropListInterface.h"

ISymbolPropListInterface::ISymbolPropListInterface(void)
{
	m_pSymbolPropList = NULL;
}

ISymbolPropListInterface::~ISymbolPropListInterface(void)
{
}

void ISymbolPropListInterface::SetPropList(CSymbolPropList *symbolPropList)
{
	m_pSymbolPropList = symbolPropList;
}

CSymbolPropList* ISymbolPropListInterface::GetPropList()
{
	return m_pSymbolPropList;
}