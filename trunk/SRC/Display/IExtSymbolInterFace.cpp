#include "StdAfx.h"
#include "IExtSymbolInterFace.h"
#include "IExtSymbol.h"
namespace Display{
IExtSymbolInterFace::IExtSymbolInterFace(void)
{
}

IExtSymbolInterFace::~IExtSymbolInterFace(void)
{
}

std::string IExtSymbolInterFace::GetSymbolName()
{
	Display::IExtSymbolPtr newSymbol = CreateSymbol();
	if (newSymbol == NULL)
	{
		return "";
	}

	std::string symbolName = newSymbol->GetSymbolName();
	return symbolName;
}

Display::ISymbolPtr IExtSymbolInterFace::CreateSymbol()
{
	return NULL;
}

std::string IExtSymbolInterFace::GetDescription()
{
	Display::IExtSymbolPtr newSymbol = CreateSymbol();
	if (newSymbol == NULL)
	{
		return "";
	}

	std::string symbolDescription = newSymbol->GetDescription();
	return symbolDescription;
}

}