// TDAppView.h : interface of the CTDAppView class
//
#include "MapControl.h"

#pragma once



class CTDAppCntrItem;

class CTDAppView : public CView
{
protected: // create from serialization only
	CTDAppView();
	DECLARE_DYNCREATE(CTDAppView)

// Attributes
public:
	CTDAppDoc* GetDocument() const;
	// m_pSelection holds the selection to the current CTDAppCntrItem.
	// For many applications, such a member variable isn't adequate to
	//  represent a selection, such as a multiple selection or a selection
	//  of objects that are not CTDAppCntrItem objects.  This selection
	//  mechanism is provided just to help you get started

	// TODO: replace this selection mechanism with one appropriate to your app
	CTDAppCntrItem* m_pSelection;

// Operations
public:

// Overrides
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual BOOL IsSelected(const CObject* pDocItem) const;// Container support

// Implementation
public:
	virtual ~CTDAppView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	CBCGPTabWnd	m_WndTab;
	Control::CMapControl m_MapCtrl;

// Generated message map functions
protected:
	afx_msg void OnDestroy();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnInsertObject();
	afx_msg void OnCancelEditCntr();
	afx_msg void OnFilePrint();
	afx_msg void OnFilePrintPreview();

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnOpenVector();
};

#ifndef _DEBUG  // debug version in TDAppView.cpp
inline CTDAppDoc* CTDAppView::GetDocument() const
   { return reinterpret_cast<CTDAppDoc*>(m_pDocument); }
#endif

