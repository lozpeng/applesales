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
	void InitComplexSymbolLayerCtrl(RECT * rect, UINT nIDResource, unsigned int nWidth);//��ʼ��ComplexSymbolLayerCtrlֻ�ܵ���1�Σ�
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
	CImageList * m_LargeImageList;						//�����ʾλͼ��ͼƬ�б�ؼ�
	IComplexSymbolLayerCtrlInterface *m_IComplexSymbolLayerCtrl;
	DIS_RECT m_rc,m_rc1;			
	unsigned int m_nX,m_nY;								//��Ż��ƵĴ�С����ʼֵx=y=0;
	CArray <int>  m_arState;								//���״̬������
	CBitmap *m_Bitmap;									//λͼ����
	CImageList  m_StateImageList;						//��Ÿ�ѡ��ťЧ����ͼƬ�б�ؼ�
	bool m_bDraw,m_bView;										//�Ƿ����
	CBitmap *m_MaskBitmap;
	int m_nWidth,m_nSelect;										//ͼƬ�Ŀ��
	CBitmap *m_OldBitmap;								//���豸ѡ������λͼ	
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


