#pragma once

#include "Isymbol.h"
#include "SymbolArray.h"

/****************************************************************************
* 用于在范围专题里显示分段类别的符号和标注等
*
*****************************************************************************/

class CRangeRenderList : public CListCtrl
{
	DECLARE_DYNAMIC(CRangeRenderList)

public:
	CRangeRenderList();
	virtual ~CRangeRenderList();


	DECLARE_MESSAGE_MAP()


public:
	void InitCol();

	void AddSymbolItem(Display::ISymbolPtr pSymbol,CString str ,CString strLabel);

	void SetImgList(CImageList * pImgList);
	void AddImgList(CBitmap * hBitmap);
	void DeleteAll(void);
	void SetbString(bool bStr);
	bool GetbString(void);
	
	void CreateSymbolArrayBitmap(Display::ISymbolArrayPtr m_pSymbolArray);
	void SetImageSize( int nWidth , int nHeight );

	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	void SetRangePage(void* pRangeRenderPage);
public:
	afx_msg void OnNMClick(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult);
public:


	void ReplaceSymbol(Display::ISymbolPtr pSymbol, int nItem);


protected:
	static LPCTSTR MakeShortString(CDC* pDC, LPCTSTR lpszLong, int nColumnLen, int nOffset);
	void RepaintSelectedItems();
	HBITMAP CoverBitmap( Display::ISymbolPtr pSymbol );

	void AddItem(int nItem, int nSubItem, CString strName);

public:
	int m_nSelect;
	COLORREF m_clrText;
	COLORREF m_clrTextBk;
	COLORREF m_clrBkgnd;
	BOOL m_bFullRowSel;
	BOOL m_bClientWidthSel;
	int m_cxClient;
	int m_cxStateImageOffset;
	int m_iSubItem;
protected:
	long m_LegendnWidth ,m_LegendnHeight;
	CImageList * m_SymbolImage;
	bool  m_bString;
	void * m_RangeRenderPage;
	CBitmap m_Bitmap;
};


