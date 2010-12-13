// TDAppView.h : interface of the CTDAppView class
//
#include "MapControl.h"

#pragma once

class CTDAppView : public CView
{
protected: // create from serialization only
	CTDAppView();
	DECLARE_DYNCREATE(CTDAppView)

// Attributes
public:
	CTDAppDoc* GetDocument() const;

// Operations
public:

// Overrides
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	

// Implementation
public:
	virtual ~CTDAppView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	CBCGPTabWnd	m_WndTab;
	CBCGPButton m_wndButton;
	Control::CMapControl m_MapCtrl;
	//Carto::CMapPtr ipMap;
// Generated message map functions
protected:
	afx_msg void OnDestroy();
	
	afx_msg void OnSize(UINT nType, int cx, int cy);
	
	afx_msg void OnFilePrint();
	afx_msg void OnFilePrintPreview();

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnOpenVector();
	afx_msg void OnOpenImg();

	afx_msg void OnMapPan();
	afx_msg void OnUpdateMapPan(CCmdUI* pCmdUI);

	afx_msg void OnMapZoomin();
	afx_msg void OnUpdateMapZoomin(CCmdUI* pCmdUI);

	afx_msg void OnMapZoomout();
	afx_msg void OnUpdateMapZoomout(CCmdUI* pCmdUI);



	afx_msg void OnDrawSelect();
	afx_msg void OnUpdateDrawSelect(CCmdUI* pCmdUI);

	afx_msg void OnDrawRect();
	afx_msg void OnUpdateDrawRect(CCmdUI* pCmdUI);
};

#ifndef _DEBUG  // debug version in TDAppView.cpp
inline CTDAppDoc* CTDAppView::GetDocument() const
   { return reinterpret_cast<CTDAppDoc*>(m_pDocument); }
#endif

