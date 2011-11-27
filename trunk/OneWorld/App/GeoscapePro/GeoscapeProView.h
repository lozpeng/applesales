// GeoscapeProView.h : interface of the CGeoscapeProView class
//


#pragma once
#include "MFC_OSG.h"

class CGeoscapeProView : public CView
{
protected: // create from serialization only
	CGeoscapeProView();
	DECLARE_DYNCREATE(CGeoscapeProView)

// Attributes
public:
	CGeoscapeProDoc* GetDocument() const;

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
	virtual ~CGeoscapeProView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	cOSG* mOSG;
	HANDLE mThreadHandle;

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()

public:
	virtual void OnInitialUpdate();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

#ifndef _DEBUG  // debug version in GeoscapeProView.cpp
inline CGeoscapeProDoc* CGeoscapeProView::GetDocument() const
   { return reinterpret_cast<CGeoscapeProDoc*>(m_pDocument); }
#endif

