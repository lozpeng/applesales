#pragma once

#include "IDisplay.h"

class CSymbolPropList;
class ISymbolPropListInterface
{
public:
	ISymbolPropListInterface(void);
	virtual ~ISymbolPropListInterface(void);

	virtual void OnSymbolPropChanged( Display::ISymbolPtr newSymbol , CWnd *wnd ) = 0;	//当属性列表中的某个值更改后此方法启用，实现此方法可以处理如：当改变值后，别的控件同步刷新符号
							//重新装入一个新符号给属性列表控件并更新
	void SetPropList(CSymbolPropList *symbolPropList);
	CSymbolPropList* GetPropList();
protected:
	CSymbolPropList *m_pSymbolPropList;
};
