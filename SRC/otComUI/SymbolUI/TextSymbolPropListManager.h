#pragma once

#include "ISymbolPropListInterface.h"
class CSymbolPropList;
class CTextSymbolPropListManager : public ISymbolPropListInterface
{
public:
	CTextSymbolPropListManager(void);
	virtual ~CTextSymbolPropListManager(void);

	void OnSymbolPropChanged( Display::ISymbolPtr newSymbol , CWnd *wnd );	//�������б��е�ĳ��ֵ���ĺ�˷������ã�ʵ�ִ˷������Դ����磺���ı�ֵ�󣬱�Ŀؼ�ͬ��ˢ�·���

};
