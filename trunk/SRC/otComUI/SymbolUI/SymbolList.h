#pragma once

#include "SymbolArray.h"

class CSymbolList : public CListCtrl
{ 
	DECLARE_DYNAMIC(CSymbolList)

public:
	CSymbolList();
	virtual ~CSymbolList();
public:

	void AddSymbolArray(CString Name, Display::ISymbolArrayPtr m_pSymbolArray);
	void SetImageSize(int Size);
protected:
	long m_LegendSize;
	typedef std::map<CString,Display::ISymbolArrayPtr >::const_iterator iterator;
	std::map<CString,Display::ISymbolArrayPtr> m_mapSymbolArray;

	CImageList * m_SymbolImage;
	CBitmap m_Bitmap;

	DECLARE_MESSAGE_MAP()
public:
	//	afx_msg void OnLvnItemchanged(NMHDR *pNMHDR, LRESULT *pResult);
	//virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
public:
	void DelListCtrl(void);
};


