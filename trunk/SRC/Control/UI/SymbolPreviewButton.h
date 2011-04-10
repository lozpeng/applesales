#pragma once

#include "ISymbol.h"
#include "IDisplay.h"

//可以显示符号预览的按钮
class CONTROL_DLL CSymbolPreviewButton : public CButton
{
	DECLARE_DYNAMIC(CSymbolPreviewButton)
public:
	CSymbolPreviewButton();
	virtual ~CSymbolPreviewButton();
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	void SetSymbol(Display::ISymbol *pSymbol);
private:

	Display::ISymbol *m_pSymbol;
	
protected:
	DECLARE_MESSAGE_MAP()
};
