#pragma once

#include "ISymbolPropListInterface.h"
class CSymbolPropList;
class CTextSymbolPropListManager : public ISymbolPropListInterface
{
public:
	CTextSymbolPropListManager(void);
	virtual ~CTextSymbolPropListManager(void);

	void OnSymbolPropChanged( Display::ISymbolPtr newSymbol , CWnd *wnd );	//当属性列表中的某个值更改后此方法启用，实现此方法可以处理如：当改变值后，别的控件同步刷新符号

};
