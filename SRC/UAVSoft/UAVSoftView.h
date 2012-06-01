// UAVSoftView.h : interface of the CUAVSoftView class
//


#pragma once

#include "MapControl.h"
#include "LayoutControl.h"
#include <boost/signal.hpp>
#include <boost/signals/connection.hpp>

class CDialogCreateRoi;
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
	Control::CLayoutControl m_LayoutCtrl;
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);

public:

	//获得当前图层下拉列表按钮
	CBCGPRibbonComboBox* GetCurLyrCombox();
	CBCGPRibbonComboBox* GetCurLyrCombox_Vector();
	CBCGPRibbonComboBox* GetMagicLayer();

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

	//layout 浏览工具
	afx_msg void OnLayoutPan();
	afx_msg void OnUpdateLayoutPan(CCmdUI* pCmdUI);

	afx_msg void OnLayoutZoomin();
	afx_msg void OnUpdateLayoutZoomin(CCmdUI* pCmdUI);

	afx_msg void OnLayoutZoomout();
	afx_msg void OnUpdateLayoutZoomout(CCmdUI* pCmdUI);

	afx_msg void OnLayoutFullView();
	afx_msg void OnUpdateLayoutZoomFullExtent(CCmdUI* pCmdUI);
	afx_msg void OnLayoutZoomActualSize();
	afx_msg void OnUpdateLayoutZoomActualSize(CCmdUI* pCmdUI);
	//地图整饰
	afx_msg void OnSelectFrameElement();
	afx_msg void OnUpdateSelectFrameElement(CCmdUI* pCmdUI);
	afx_msg void OnDrawMapFrameElement();
	afx_msg void OnUpdateDrawMapFrameElement(CCmdUI* pCmdUI);
	afx_msg void OnDrawNorthArrow();
	afx_msg void OnUpdateDrawNorthArrow(CCmdUI* pCmdUI);
	afx_msg void OnDrawScaleBar();
	afx_msg void OnUpdateDrawScaleBar(CCmdUI* pCmdUI);
	afx_msg void OnDrawLegend();
	afx_msg void OnUpdateDrawLegend(CCmdUI* pCmdUI);
	afx_msg void OnDrawMapTitle();
	afx_msg void OnUpdateDrawMapTitle(CCmdUI* pCmdUI);
	afx_msg void OnLoadTemp();
	afx_msg void OnSaveTemp();
	//
	afx_msg void OnCurrLayerCombo();
	afx_msg void OnCurrLayerCombo_Vector();
	afx_msg void OnUpdateCurrlayerCombo_Vector(CCmdUI* pCmdUI);
	Carto::ILayerPtr GetComboLayer();
	Carto::ILayerPtr GetComboLayer_Vector();
	void		RefreshLayerCombo();
	bool		IsLayerComboNull();
	bool        IsLayerComboCurFirstVisual();
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

	afx_msg void OnDrawExport();
	afx_msg void OnUpdateDrawExport(CCmdUI* pCmdUI);

	//量测工具
	afx_msg void OnLineMeasure();
	afx_msg void OnUpdateLineMeasure(CCmdUI* pCmdUI);

	afx_msg void OnAreaMeasure();
	afx_msg void OnUpdateAreaMeasure(CCmdUI* pCmdUI);


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
	afx_msg void OnIncrementalImport();
	afx_msg void OnUpdateIncrementalImport(CCmdUI*);



	//魔术棒提取
	afx_msg void OnMagicStick();
	afx_msg void OnUpdateMagicStick(CCmdUI* pCmdUI);
	afx_msg void OnMagicStickLayer();
	afx_msg void OnMagicTol();

	afx_msg void OnDeleteLastMagic();
	//边缘提取
	afx_msg void OnEdgeTrack();

	//变化检测
	afx_msg void OnImgChangeDetect();
	afx_msg void OnImgChangeRender();
	afx_msg void OnWaterExtract();
	afx_msg void OnChangeSetSymbol();

	afx_msg void OnSendBlueToothFile();

	afx_msg void OnEdgeEnhance();
	afx_msg void OnEdgeExtract();
	afx_msg void OnBuildDamage();
	afx_msg void OnHighWaterpol();
	afx_msg void OnClassifyFuzzyKMean();
	afx_msg void OnGasDatainsert();
	afx_msg void OnRoiDlg();
	afx_msg void OnSuperClsDlg();
	afx_msg void OnGasCreateImage();
	afx_msg void OnOilEdge();
	afx_msg void OnClassVector();

	//分类结果编号
	afx_msg void OnModifyClassinfo();

	//打开帮助
	afx_msg void OnOpenHelp();

	afx_msg void OnDelAll();

	LRESULT OnChangeActiveTab(WPARAM wp,LPARAM lp);

	void ContainerChangeEvent(Element::IElementPtr pElement);
	void ElementDelEvent(Element::IElementPtr pElement);
	void LayerDelEvent(Carto::ILayerPtr pLayer);

	Carto::ILayerPtr FindLayerbyPointer(Carto::ILayer* pLayer);

protected:

	BOOL m_bLayout; //标示是否layout视图

	boost::signals::connection m_ConnectionMapLayerDeleted;
	boost::signals::connection m_ConnectionContainerChanged;
	boost::signals::connection m_ConnectionElementDeleted;
	boost::shared_ptr<CDialogCreateRoi> m_Dlg_Roi;

public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // debug version in UAVSoftView.cpp
inline CUAVSoftDoc* CUAVSoftView::GetDocument() const
   { return reinterpret_cast<CUAVSoftDoc*>(m_pDocument); }
#endif

