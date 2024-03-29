/* Generated by Together */

#ifndef CSYMBOLARRAY_H
#define CSYMBOLARRAY_H

#include "alm.h"
#include "ISymbol.h"

namespace Display {
class DISPLAY_DLL CSymbolArray : public SYSTEM::CArray<ISymbolPtr>//, public SYSTEM::CRef 
{
public:

    ~CSymbolArray();

    CSymbolArray();

	int GetSize();

	ISymbolPtr GetAt(int nIndex);

	void SetAt(int nIndex, ISymbolPtr newElement);

	int Add(ISymbolPtr newElement);

};

typedef SYSTEM::CSmartPtr<CSymbolArray> ISymbolArrayPtr;
}
#endif //CSYMBOLARRAY_H
