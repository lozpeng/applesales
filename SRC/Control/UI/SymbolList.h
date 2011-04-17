#pragma once

#include "ISymbol.h"

#include <vector>
#include <map>
using namespace std;

class CSymbolList : public CListCtrl
{ 
	DECLARE_DYNAMIC(CSymbolList)

public:
	CSymbolList();
	virtual ~CSymbolList();
public:

	void AddSymbolArray(CString Name, vector<Display::ISymbolPtr>& m_pSymbolArray);
	void SetImageSize(int Size);
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
protected:
	long m_LegendSize;
	typedef std::map<CString,vector<Display::ISymbolPtr>>::const_iterator iterator;
	vector<Display::ISymbolPtr> m_mapSymbolArray;
	CImageList * m_SymbolImage;
	CBitmap m_Bitmap;

	DECLARE_MESSAGE_MAP()
public:
	//	afx_msg void OnLvnItemchanged(NMHDR *pNMHDR, LRESULT *pResult);
	//virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
public:
	void DelListCtrl(void);
};


