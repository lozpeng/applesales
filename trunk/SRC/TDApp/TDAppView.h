// TDAppView.h : interface of the CTDAppView class
//
#include "MapControl.h"
#include "LayoutControl.h"
#include <boost/signal.hpp>
#include <boost/signals/connection.hpp>

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
	CBCGPRibbonComboBox* GetCurLyrCombox_Vector();
	CBCGPRibbonComboBox* GetMagicLayer();
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
	afx_msg void OnCurrLayerCombo_Vector();
	Carto::ILayerPtr GetComboLayer();
	Carto::ILayerPtr GetComboLayer_Vector();
	void		RefreshLayerCombo();
	bool		IsLayerComboNull();
	void		BrightContrast(int nBright=-1,int nContrast=-1);
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
	//卷帘
	afx_msg void OnSwipe();
	afx_msg void OnUpdateSwipe(CCmdUI* pCmdUI); 

	afx_msg void OnFlick();
	afx_msg void OnUpdateFlick(CCmdUI* pCmdUI);
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

	afx_msg void OnDrawSaveAs();
	afx_msg void OnUpdateDrawSaveAs(CCmdUI* pCmdUI);
	//编辑工具
	afx_msg void OnEditorStart();
	afx_msg void OnUpdateEditorStart(CCmdUI *pCmdUI);
	afx_msg void OnEditorSketch();
	afx_msg void OnUpdateEditorSketch(CCmdUI *pCmdUI);
	afx_msg void OnEditerEdit();
	afx_msg void OnUpdateEditerEdit(CCmdUI *pCmdUI);
	afx_msg void OnEditerRedo();
	afx_msg void OnUpdateEditerRedo(CCmdUI *pCmdUI);
	afx_msg void OnEditerUndo();
	afx_msg void OnUpdateEditerUndo(CCmdUI *pCmdUI);
	afx_msg void OnEditerEnd();
	afx_msg void OnUpdateEditerEnd(CCmdUI *pCmdUI);
	afx_msg void OnEditerSave();
	afx_msg void OnUpdateEditerSave(CCmdUI *pCmdUI);
	afx_msg void OnEditerDel();
	afx_msg void OnUpdateEditerDel(CCmdUI *pCmdUI);
	afx_msg void OnEditerUnion();
	afx_msg void OnUpdateEditerUnion(CCmdUI *pCmdUI);
	
	afx_msg void OnEditerAttribute();
	afx_msg void OnUpdateEditerAttribute(CCmdUI *pCmdUI);
	afx_msg void OnFeatureInfo();
	afx_msg void OnSelectFeature();
	afx_msg void OnUpdateSelectFeature(CCmdUI *pCmdUI);

	//地图整饰
	afx_msg void OnSelectFrameElement();
	afx_msg void OnUpdateSelectFrameElement(CCmdUI* pCmdUI);
	afx_msg void OnDrawMapFrameElement();
	afx_msg void OnUpdateDrawMapFrameElement(CCmdUI* pCmdUI);

	//魔术棒提取
	afx_msg void OnMagicStick();
	afx_msg void OnUpdateMagicStick(CCmdUI* pCmdUI);
	afx_msg void OnMagicStickLayer();
	afx_msg void OnMagicTol();

	afx_msg void OnDeleteLastMagic();

	//变化检测
	afx_msg void OnImgChangeDetect();

	LRESULT OnChangeActiveTab(WPARAM wp,LPARAM lp);

	void LayerDelEvent(Carto::ILayerPtr pLayer);

	Carto::ILayerPtr FindLayerbyPointer(Carto::ILayer* pLayer);

protected:

    boost::signals::connection m_ConnectionMapLayerDeleted;
	
};

#ifndef _DEBUG  // debug version in TDAppView.cpp
inline CTDAppDoc* CTDAppView::GetDocument() const
   { return reinterpret_cast<CTDAppDoc*>(m_pDocument); }
#endif

