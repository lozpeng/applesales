#ifndef _ISYMBOLLISTCTRL_H_
#define _ISYMBOLLISTCTRL_H_
#include "IUIObject.h"
#include "ISymbol.h"
namespace Framework
{

class CONTROL_DLL ISymbolListCtrl : public IUIObject 
{
public:
	ISymbolListCtrl();
	virtual ~ISymbolListCtrl();
public:
	virtual Display::ISymbolPtr SelectSymbol( Display::ISymbolPtr pSymbol = NULL) = 0;
	virtual Display::ISymbolPtr SelectSymbol2( Display::ISymbolPtr pSymbol = NULL) = 0;
};
typedef SYSTEM::CSmartPtr<ISymbolListCtrl> ISymbolListCtrlPtr;
}
#endif 
