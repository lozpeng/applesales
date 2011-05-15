#pragma once

#include "IDisplay.h"

class CSymbolPropList;
class ISymbolPropListInterface
{
public:
	ISymbolPropListInterface(void);
	virtual ~ISymbolPropListInterface(void);

	virtual void OnSymbolPropChanged( Display::ISymbolPtr newSymbol , CWnd *wnd ) = 0;	//�������б��е�ĳ��ֵ���ĺ�˷������ã�ʵ�ִ˷������Դ����磺���ı�ֵ�󣬱�Ŀؼ�ͬ��ˢ�·���
							//����װ��һ���·��Ÿ������б�ؼ�������
	void SetPropList(CSymbolPropList *symbolPropList);
	CSymbolPropList* GetPropList();
protected:
	CSymbolPropList *m_pSymbolPropList;
};
