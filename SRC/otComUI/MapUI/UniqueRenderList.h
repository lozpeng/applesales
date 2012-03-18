#pragma once

#include "Isymbol.h"
#include "SymbolArray.h"

/****************************************************************************
* 扩展的ListCtrl,用于在唯一值专题里显示类别的符号和标注等
*
*****************************************************************************/

class CUniquerRenderSymbolList : public CListCtrl
{
	DECLARE_DYNAMIC(CUniquerRenderSymbolList)

public:
	CUniquerRenderSymbolList();
	virtual ~CUniquerRenderSymbolList();


	DECLARE_MESSAGE_MAP()

	
public:
	void InitCol();

	void AddSymbolItem(Display::ISymbolPtr pSymbol,CString str ,CString strLabel, CString strCount);

	//交换两行的顺序
	void ReposItem(int oldpos,int newpos);

	void InsertItemEX(int nItem,CString str ,CString strLabel, CString strCount);
	void SetImgList(CImageList * pImgList);
	void AddImgList(CBitmap * hBitmap);
	void DeleteAll(void);
	void SetbString(bool bStr);
	bool GetbString(void);
	afx_msg void OnNMClick(NMHDR *pNMHDR, LRESULT *pResult);
	void CreateSymbolArrayBitmap(Display::ISymbolArrayPtr m_pSymbolArray);
	void SetImageSize( int nWidth , int nHeight );

	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	void SetUniquePage(void* pUniqueRenderPage);
public:
	afx_msg void OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult);
public:
	void DelItem(int nItem);


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
	void * m_UniqueRenderPage;
	CBitmap m_Bitmap;
};


