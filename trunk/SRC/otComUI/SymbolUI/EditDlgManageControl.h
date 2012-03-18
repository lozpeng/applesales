#pragma once
#include "ComplexSymbolLayerCtrl.h"
#include "ISymbolPropListInterface.h"
#include "IComplexSymbolLayerCtrlInterface.h"

class CEditDlgManageControl : public ISymbolPropListInterface , public IComplexSymbolLayerCtrlInterface
{
public:
	CEditDlgManageControl(void);
	~CEditDlgManageControl(void);
	int m_nType;
	Display::ISymbolPtr m_pComplexSymbol;							//��ؼ�ʹ��

	Display::ISymbolPtr m_pStandbyCopySymbol;						//���õķ��Ÿ���

	Display::ISymbolPtr m_pSymbolCopy;							//Ԥ��������

	Display::ISymbolPtr m_pSymbol;								//��ǰʹ�õķ���

	Display::ISymbolPtr m_pCopySymbol;							//����ʱʹ�õķ���

	CComplexSymbolLayerCtrl m_ComplexSymbolLayerCL;					//���б�ؼ�����	

	bool m_bVisible;												//����ʱʹ�õ���ʾ����ʾ
	
	
public:
	void SetSymbol(Display::ISymbolPtr pSymbol);
	Display::ISymbolPtr GetSymbol();
	void ReSetSymboltoPropList(Display::ISymbolPtr newSymbol);				//����װ��һ���·��Ÿ������б�ؼ�������
	void ResetSymboltoLengend(Display::ISymbolPtr newSymbol);					//����װ��һ���·��Ÿ�Ԥ���ؼ�
	/*SYMBO_LTYPE GetSymbolType(Display::ISymbolPtr pSymbol)*/
	void SelectSymbol(int nIndex);
	//ʵ�ִӸ���̳еĳ��󷽷�
	virtual void OnSymbolPropChanged( Display::ISymbolPtr newSymbol , CWnd *wnd );
	virtual void UpdateComplexSymbolLayerCtrl();
	int GetSelect();												//���б�ؼ���ѡ��ڼ���
    void SetPropList( int nSelect );                           //�������Կؼ�
	 void SetSelect(int nSelect);

public:
	 void InitComplexSymbolLayerCtrl();
     void UPdateSymbol( int nIndex, int nState );
     void SetCopySymbol(void) ;
	 void ReSetSelectIndexToBegin();										//����ǰ���б�ؼ���ѡȡλ��Ϊ��һ��
};
