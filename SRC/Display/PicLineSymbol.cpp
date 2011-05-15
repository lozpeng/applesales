#include "stdafx.h"
#include "PicLineSymbol.h"
#include "IArchive.h"
Display::CPicLineSymbol::CPicLineSymbol()
{
}
Display::CPicLineSymbol::~CPicLineSymbol()
{
		ClearDC();
}

void Display::CPicLineSymbol::Draw(void * pObject )
{
}
void Display::CPicLineSymbol::SetXScale(double dScaleX)
{
}
void Display::CPicLineSymbol::SetYScale(double dScaleY)
{
}
void Display::CPicLineSymbol::SetBitMapSymbol(CtoBitMapSymbol* pBitMapSymbol)
{
}
void Display::CPicLineSymbol::serialization(SYSTEM::IArchive & ar)
{ 
	ILineSymbol::serialization(ar); 
}
