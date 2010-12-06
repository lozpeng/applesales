//////////////////////////////////////////////////////////////////////
// 版权(c) 2010-2020, 天地智绘
// 作者：  hhzhao
// 时间：  2010/10/18
// 描述：  选择要素的符号 负责对选择要素渲染
//////////////////////////////////////////////////////////////////////

#ifndef _SELECTION_SYMBOL_H
#define _SELECTION_SYMBOL_H

#include "ISymbol.h"

namespace Display
{

class DISPLAY_DLL CSelectionSymbol
{
public:
	CSelectionSymbol(void);
	~CSelectionSymbol(void);
public:
    static CSelectionSymbol* GetInstance();

	//得到高亮显示的点符号
	ISymbolPtr GetHighLightPtSymbol();
    //得到线符号
    ISymbolPtr GetHighLightLineSymbol();
    //得到面符号
	ISymbolPtr GetHighLightAreaSymbol();

	void SetHighLightPtSymbol(ISymbolPtr pSymbol);

	void SetHighLightLineSymbol(ISymbolPtr pSymbol);

	void SetHighLightAreaSymbol(ISymbolPtr pSymbol);

private:

	void Init();
private:
	//选择集点符号
    ISymbolPtr m_pSelPtSymbol;

	//选择集线符号
	ISymbolPtr m_pSelLineSymbol;

	//选择集面符号
	ISymbolPtr m_pSelAreaSymbol;

};

}
#endif 



