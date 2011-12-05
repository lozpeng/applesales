// UAVSoftView.h : interface of the CUAVSoftView class
//


#pragma once

#include "MapControl.h"
#include "LayoutControl.h"
#include <boost/signal.hpp>
#include <boost/signals/connection.hpp>

class CUAVSoftView : public CView
{
protected: // create from serialization only
	CUAVSoftView();
	DECLARE_DYNCREATE(CUAVSoftView)

// Attributes
public:
	CUAVSoftDoc* GetDocument() const;

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
	virtual ~CUAVSoftView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	DECLARE_MESSAGE_MAP()

private:
	CBCGPTabWnd	m_WndTab;
	CBCGPButton m_wndButton;
	Control::CMapControl m_MapCtrl;
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

#ifndef _DEBUG  // debug version in UAVSoftView.cpp
inline CUAVSoftDoc* CUAVSoftView::GetDocument() const
   { return reinterpret_cast<CUAVSoftDoc*>(m_pDocument); }
#endif

