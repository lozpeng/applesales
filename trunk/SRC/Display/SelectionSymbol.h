//////////////////////////////////////////////////////////////////////
// ��Ȩ(c) 2010-2020, ����ǻ�
// ���ߣ�  hhzhao
// ʱ�䣺  2010/10/18
// ������  ѡ��Ҫ�صķ��� �����ѡ��Ҫ����Ⱦ
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

	//�õ�������ʾ�ĵ����
	ISymbolPtr GetHighLightPtSymbol();
    //�õ��߷���
    ISymbolPtr GetHighLightLineSymbol();
    //�õ������
	ISymbolPtr GetHighLightAreaSymbol();

	void SetHighLightPtSymbol(ISymbolPtr pSymbol);

	void SetHighLightLineSymbol(ISymbolPtr pSymbol);

	void SetHighLightAreaSymbol(ISymbolPtr pSymbol);

private:

	void Init();
private:
	//ѡ�񼯵����
    ISymbolPtr m_pSelPtSymbol;

	//ѡ���߷���
	ISymbolPtr m_pSelLineSymbol;

	//ѡ�������
	ISymbolPtr m_pSelAreaSymbol;

};

}
#endif 



