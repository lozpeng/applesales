#pragma once
#include "afxwin.h"
#include "SymbolPropList.h"
#include "CharMarkerSymbol.h"

class CCharSymbolSelectListBox : public CListBox
{
public:
	CCharSymbolSelectListBox(void);
	~CCharSymbolSelectListBox(void);
	void SetCharMarkSymbol(Display::CCharMarkerSymbolPtr pCharMarkSymbol);
	void SetSymbolSelectProp(CCharSymbolSelectProp* pSymbolSelectProp);
	void ReSetScorll(long lRow);
	void SetNewSelectId(long lNewSelectId);

	DECLARE_MESSAGE_MAP()
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
public:
	CRect m_rect;
private:
	int SnapGrid(long lRowOffset, CPoint point);

	Display::CCharMarkerSymbolPtr m_pCharMarkSymbol;
	long m_lItemHeight;
	Display::CCharMarkerSymbolPtr m_pCharDraw;

	CCharSymbolSelectProp *m_pSymbolSelectProp;

	long m_lNewSelectId;			//±£´æÐÂÑ¡·ûºÅIndex	
	long m_lOldSelectId;

	CToolTipCtrl m_ctrlToolTip;
	bool m_bToolTipCreate;
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT /*lpMeasureItemStruct*/);
	virtual int CompareItem(LPCOMPAREITEMSTRUCT /*lpCompareItemStruct*/);

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
protected:
	virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
