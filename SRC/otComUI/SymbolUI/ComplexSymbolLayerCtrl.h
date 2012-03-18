#pragma once
#define DEFAULTCOLOR 16645374
#include "IComplexSymbolLayerCtrlInterface.h"
#include "ISymbol.h"

class CComplexSymbolLayerCtrl : public CListCtrl
{
	DECLARE_DYNAMIC(CComplexSymbolLayerCtrl)

public:
	CComplexSymbolLayerCtrl();
	virtual ~CComplexSymbolLayerCtrl();
	void InitComplexSymbolLayerCtrl(RECT * rect, UINT nIDResource, unsigned int nWidth);//初始化ComplexSymbolLayerCtrl只能调用1次；
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDIS);
	void UpDataCSLC(Display::ISymbolPtr pSymbol, SYMBOL_TYPE enumSymbolType);
	int GetSelect();
	void SetSelect(int nSelect);
protected:
	DECLARE_MESSAGE_MAP()
	void AddCOL(void);
	int AnalyseState(bool bState, int nSelect=-1 );
	void ResetItem(int nSelect);
	void CheckItem(int nItem);
	void SetSymbol(Display::ISymbolPtr pSymbol, SYMBOL_TYPE enumSymbolType);
	HBITMAP CoverBitmap(Display::ISymbolPtr pSymbol);
	void AddSymbol(Display::ISymbolPtr pSymbol, int nIndex);
	BOOL ReplaceSymbol(Display::ISymbolPtr pSymbol, long nIndex ,unsigned long nColor=16645374 );
	void AddItem(int nIndex, int nState);
	BOOL ImageListRemoveAll(void);
	BOOL RemoveSymbol(int nIndex);
	void CheckItemEx(int nIndex);
	CImageList * m_LargeImageList;						//存放显示位图的图片列表控件
	IComplexSymbolLayerCtrlInterface *m_IComplexSymbolLayerCtrl;
	DIS_RECT m_rc,m_rc1;			
	unsigned int m_nX,m_nY;								//存放绘制的大小，起始值x=y=0;
	CArray <int>  m_arState;								//存放状态的数组
	CBitmap *m_Bitmap;									//位图对象
	CImageList  m_StateImageList;						//存放复选按钮效果的图片列表控件
	bool m_bDraw,m_bView;										//是否绘制
	CBitmap *m_MaskBitmap;
	int m_nWidth,m_nSelect;										//图片的宽度
	CBitmap *m_OldBitmap;								//从设备选下来的位图	
	SYMBOL_TYPE m_SymbolType;

public:
	afx_msg void OnNMClick(NMHDR *pNMHDR, LRESULT *pResult);
public:
	afx_msg void OnNMRclick(NMHDR *pNMHDR, LRESULT *pResult);
public:
	afx_msg void OnLvnBegindrag(NMHDR *pNMHDR, LRESULT *pResult);
public:
	afx_msg void OnLvnBeginrdrag(NMHDR *pNMHDR, LRESULT *pResult);
public:
	void SetManageControl(IComplexSymbolLayerCtrlInterface * IComplexSymbolLayerCtrl);

};


