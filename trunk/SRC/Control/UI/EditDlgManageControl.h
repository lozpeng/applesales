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
	Display::ISymbolPtr m_pComplexSymbol;							//层控件使用

	Display::ISymbolPtr m_pStandbyCopySymbol;						//备用的符号副本

	Display::ISymbolPtr m_pSymbolCopy;							//预览绘制用

	Display::ISymbolPtr m_pSymbol;								//当前使用的符号

	Display::ISymbolPtr m_pCopySymbol;							//复制时使用的符号

	CComplexSymbolLayerCtrl m_ComplexSymbolLayerCL;					//层列表控件对象	

	bool m_bVisible;												//复制时使用的显示不显示
	
	
public:
	void SetSymbol(Display::ISymbolPtr pSymbol);
	Display::ISymbolPtr GetSymbol();
	void ReSetSymboltoPropList(Display::ISymbolPtr newSymbol);				//重新装入一个新符号给属性列表控件并更新
	void ResetSymboltoLengend(Display::ISymbolPtr newSymbol);					//重新装入一个新符号给预览控件
	/*SYMBO_LTYPE GetSymbolType(Display::ISymbolPtr pSymbol)*/
	void SelectSymbol(int nIndex);
	//实现从父类继承的抽象方法
	virtual void OnSymbolPropChanged( Display::ISymbolPtr newSymbol , CWnd *wnd );
	virtual void UpdateComplexSymbolLayerCtrl();
	int GetSelect();												//层列表控件的选择第几个
    void SetPropList( int nSelect );                           //设置属性控件
	 void SetSelect(int nSelect);

public:
	 void InitComplexSymbolLayerCtrl();
     void UPdateSymbol( int nIndex, int nState );
     void SetCopySymbol(void) ;
	 void ReSetSelectIndexToBegin();										//将当前层列表控件的选取位设为第一列
};
