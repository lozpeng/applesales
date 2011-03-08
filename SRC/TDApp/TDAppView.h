// TDAppView.h : interface of the CTDAppView class
//
#include "MapControl.h"
#include "LayoutControl.h"

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
	//获得当前图层下拉列表按钮
	CBCGPRibbonComboBox* GetCurLyrCombox();
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
	Control::CLayoutControl m_LayoutCtrl;
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

	afx_msg void OnMapFullView();

	//前视图，后视图
	afx_msg void OnMapPreExtent();
	afx_msg void OnUpdateMapPreExtent(CCmdUI* pCmdUI);

	afx_msg void OnMapNextExtent();
	afx_msg void OnUpdateMapNextExtent(CCmdUI* pCmdUI);

	afx_msg void OnSelectFeatureByPoint();
	afx_msg void OnUpdateSelectFeatureByPoint(CCmdUI* pCmdUI);

	//
	afx_msg void OnCurrLayerCombo();
	void		RefreshLayerCombo();
	bool		IsLayerComboNull();
	afx_msg void OnBrightRestore();
	afx_msg void OnContrastRestore();
	afx_msg void OnTransparentRestore();
	afx_msg void OnBrightSlider();
	afx_msg void OnContrastSlider();
	afx_msg void OnTransparentSlider();
	afx_msg void OnUpdateBrightRestore(CCmdUI* pCmdUI);
	afx_msg void OnUpdateContrastRestore(CCmdUI* pCmdUI);
	afx_msg void OnUpdateTransparentRestore(CCmdUI* pCmdUI);
	afx_msg void OnUpdateBrightSlider(CCmdUI* pCmdUI);
	afx_msg void OnUpdateContrastSlider(CCmdUI* pCmdUI);
	afx_msg void OnUpdateTransparentSlider(CCmdUI* pCmdUI);
	//标绘
	afx_msg void OnDrawSelect();
	afx_msg void OnUpdateDrawSelect(CCmdUI* pCmdUI);

	afx_msg void OnDrawRect();
	afx_msg void OnUpdateDrawRect(CCmdUI* pCmdUI);

	afx_msg void OnDrawMarker();
	afx_msg void OnUpdateDrawMarker(CCmdUI* pCmdUI);
	afx_msg void OnDrawCircle();
	afx_msg void OnUpdateDrawCircle(CCmdUI* pCmdUI);
	afx_msg void OnDrawPolygon();
	afx_msg void OnUpdateDrawPolygon(CCmdUI* pCmdUI);
	afx_msg void OnDrawPolyline();
	afx_msg void OnUpdateDrawPolyline(CCmdUI* pCmdUI);
	afx_msg void OnDrawCurve();
	afx_msg void OnUpdateDrawCurve(CCmdUI* pCmdUI);
	afx_msg void OnDrawText();
	afx_msg void OnUpdateDrawtext(CCmdUI* pCmdUI);


	afx_msg void OnEditElement();
	afx_msg void OnUpdateEditElement(CCmdUI* pCmdUI);

	afx_msg void OnDrawEllipse();
	afx_msg void OnUpdateDrawEllipse(CCmdUI* pCmdUI);
	afx_msg void OnDrawCalloutText();
	afx_msg void OnUpdateDrawCalloutText(CCmdUI* pCmdUI);

	afx_msg void OnDrawFreeHandline();
	afx_msg void OnUpdateDrawFreeHandline(CCmdUI* pCmdUI);


	//地图整饰
	afx_msg void OnSelectFrameElement();
	afx_msg void OnUpdateSelectFrameElement(CCmdUI* pCmdUI);
	afx_msg void OnDrawMapFrameElement();
	afx_msg void OnUpdateDrawMapFrameElement(CCmdUI* pCmdUI);

	LRESULT OnChangeActiveTab(WPARAM wp,LPARAM lp);
};

#ifndef _DEBUG  // debug version in TDAppView.cpp
inline CTDAppDoc* CTDAppView::GetDocument() const
   { return reinterpret_cast<CTDAppDoc*>(m_pDocument); }
#endif

