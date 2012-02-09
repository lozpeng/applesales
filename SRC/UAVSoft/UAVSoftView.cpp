// UAVSoftView.cpp : implementation of the CUAVSoftView class
//

#include "stdafx.h"
#include "UAVSoft.h"

#include "UAVSoftDoc.h"
#include "UAVSoftView.h"
#include "ShapefileWorkspaceFactory.h"
#include "ShapefileWorkspace.h"
#include "ShapefileFeatureClass.h"
#include "FeatureLayer.h"
#include "RasterLayer.h"
#include "RasterWSFactory.h"
#include "RasterRGBRender.h"
#include "ProgressBar.h"
#include "MainFrm.h"
#include "CEditor.h"
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include "Tool/MagicStickTool.h"
#include "ImgProcessUI/ImageProcessTool.h"
#include "ILayer.h"
#include "DlgDrawingExport.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CUAVSoftView

IMPLEMENT_DYNCREATE(CUAVSoftView, CView)

BEGIN_MESSAGE_MAP(CUAVSoftView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_WM_CREATE()
	ON_WM_SIZE()

	ON_COMMAND(ID_OPEN_Vector, OnOpenVector)
	ON_COMMAND(ID_OPEN_IMG, OnOpenImg)

	//浏览工具
	ON_COMMAND(ID_MAP_PAN, OnMapPan)
	ON_UPDATE_COMMAND_UI(ID_MAP_PAN, OnUpdateMapPan)
	ON_COMMAND(ID_MAP_ZOOM_IN, OnMapZoomin)
	ON_UPDATE_COMMAND_UI(ID_MAP_ZOOM_IN, OnUpdateMapZoomin)
	ON_COMMAND(ID_ZOOM_OUT, OnMapZoomout)
	ON_UPDATE_COMMAND_UI(ID_ZOOM_OUT, OnUpdateMapZoomout)
	ON_COMMAND(ID_MAP_FULLVIEW, OnMapFullView)


	ON_COMMAND(ID_PRE_EXTENT, OnMapPreExtent)
	ON_UPDATE_COMMAND_UI(ID_PRE_EXTENT, OnUpdateMapPreExtent)
	ON_COMMAND(ID_NEXT_EXTENT, OnMapNextExtent)
	ON_UPDATE_COMMAND_UI(ID_NEXT_EXTENT, OnUpdateMapNextExtent)


	//layout 浏览工具
	ON_COMMAND(ID_LAYOUT_PAN, OnLayoutPan)
	ON_UPDATE_COMMAND_UI(ID_LAYOUT_PAN, OnUpdateLayoutPan)
	ON_COMMAND(ID_LAYOUT_ZOOM_IN, OnLayoutZoomin)
	ON_UPDATE_COMMAND_UI(ID_LAYOUT_ZOOM_IN, OnUpdateLayoutZoomin)
	ON_COMMAND(ID_LAYOUT_ZOOM_OUT, OnLayoutZoomout)
	ON_UPDATE_COMMAND_UI(ID_LAYOUT_ZOOM_OUT, OnUpdateLayoutZoomout)
	ON_COMMAND(ID_LAYOUT_FULLVIEW, OnLayoutFullView)
	ON_UPDATE_COMMAND_UI(ID_LAYOUT_FULLVIEW, OnUpdateLayoutZoomFullExtent)
	ON_COMMAND(ID_LAYOUT_ACTUALSIZE, OnLayoutZoomActualSize)
	ON_UPDATE_COMMAND_UI(ID_LAYOUT_ACTUALSIZE, OnUpdateLayoutZoomActualSize)

	//地图整饰
	ON_COMMAND(ID_SELECT_FRAME_ELEMENT, OnSelectFrameElement)
	ON_UPDATE_COMMAND_UI(ID_SELECT_FRAME_ELEMENT, OnUpdateSelectFrameElement)	
	ON_COMMAND(ID_DRAW_NORTH_ARROW, OnDrawNorthArrow)
	ON_UPDATE_COMMAND_UI(ID_DRAW_NORTH_ARROW, OnUpdateDrawNorthArrow)
	ON_COMMAND(ID_DRAW_SCALEBAR, OnDrawScaleBar)
	ON_UPDATE_COMMAND_UI(ID_DRAW_SCALEBAR, OnUpdateDrawScaleBar)
	ON_COMMAND(ID_DRAW_LEGEND, OnDrawLegend)
	ON_UPDATE_COMMAND_UI(ID_DRAW_LEGEND, OnUpdateDrawLegend)
	ON_COMMAND(ID_DRAW_MAP_TITLE, OnDrawMapTitle)
	ON_UPDATE_COMMAND_UI(ID_DRAW_MAP_TITLE, OnUpdateDrawMapTitle)

	ON_COMMAND(ID_POINT_SELECTFEATURE, OnSelectFeatureByPoint)
	ON_UPDATE_COMMAND_UI(ID_POINT_SELECTFEATURE, OnUpdateSelectFeatureByPoint)

	ON_COMMAND(ID_CURRLAYER_COMBO, OnCurrLayerCombo)
	ON_COMMAND(ID_CURRLAYER_COMBO_VECTOR, OnCurrLayerCombo_Vector)
	ON_UPDATE_COMMAND_UI(ID_CURRLAYER_COMBO_VECTOR,OnUpdateCurrlayerCombo_Vector)
	//调整
	ON_COMMAND(ID_BRIGHT_RESTORE, OnBrightRestore)
	ON_COMMAND(ID_BRIGHT_SLIDER, OnBrightSlider)
	ON_COMMAND(ID_CONTRAST_RESTORE, OnContrastRestore)
	ON_COMMAND(ID_CONTRAST_SLIDER, OnContrastSlider)
	ON_COMMAND(ID_TRANSPARENT_RESTORE, OnTransparentRestore)
	ON_COMMAND(ID_TRANSPARENT_SLIDER, OnTransparentSlider)

	ON_UPDATE_COMMAND_UI(ID_BRIGHT_RESTORE, OnUpdateBrightRestore)
	ON_UPDATE_COMMAND_UI(ID_BRIGHT_SLIDER, OnUpdateBrightSlider)
	ON_UPDATE_COMMAND_UI(ID_CONTRAST_RESTORE, OnUpdateContrastRestore)
	ON_UPDATE_COMMAND_UI(ID_CONTRAST_SLIDER, OnUpdateContrastSlider)
	ON_UPDATE_COMMAND_UI(ID_TRANSPARENT_RESTORE, OnUpdateTransparentRestore)
	ON_UPDATE_COMMAND_UI(ID_TRANSPARENT_SLIDER, OnUpdateTransparentSlider)

	ON_COMMAND(ID_SWIPE, OnSwipe)
	ON_UPDATE_COMMAND_UI(ID_SWIPE, OnUpdateSwipe)
	ON_COMMAND(ID_RASLUT_EDIT, OnFlick)
	ON_UPDATE_COMMAND_UI(ID_RASLUT_EDIT, OnUpdateFlick)
	//标绘工具

	ON_COMMAND(ID_DRAW_SELECT, OnDrawSelect)
	ON_UPDATE_COMMAND_UI(ID_DRAW_SELECT, OnUpdateDrawSelect)

	ON_COMMAND(ID_DEL_ALL, OnDelAll)

	ON_COMMAND(ID_DRAW_RECT, OnDrawRect)
	ON_UPDATE_COMMAND_UI(ID_DRAW_RECT, OnUpdateDrawRect)

	ON_COMMAND(ID_DRAW_MARKER, OnDrawMarker)
	ON_UPDATE_COMMAND_UI(ID_DRAW_MARKER, OnUpdateDrawMarker)

	ON_COMMAND(ID_DRAW_CIRCLE, OnDrawCircle)
	ON_UPDATE_COMMAND_UI(ID_DRAW_CIRCLE, OnUpdateDrawCircle)
	ON_COMMAND(ID_DRAW_POLYGON, OnDrawPolygon)
	ON_UPDATE_COMMAND_UI(ID_DRAW_POLYGON, OnUpdateDrawPolygon)
	ON_COMMAND(ID_DRAW_POLYLINE, OnDrawPolyline)
	ON_UPDATE_COMMAND_UI(ID_DRAW_POLYLINE, OnUpdateDrawPolyline)
	ON_COMMAND(ID_DRAW_CURVE, OnDrawCurve)
	ON_UPDATE_COMMAND_UI(ID_DRAW_CURVE, OnUpdateDrawCurve)
	ON_COMMAND(ID_DRAW_TEXT, OnDrawText)
	ON_UPDATE_COMMAND_UI(ID_DRAW_TEXT, OnUpdateDrawtext)

	ON_COMMAND(ID_DRAW_EDITOR, OnEditElement)
	ON_UPDATE_COMMAND_UI(ID_DRAW_EDITOR, OnUpdateEditElement)
	ON_COMMAND(ID_DRAW_Ellipse, OnDrawEllipse)
	ON_UPDATE_COMMAND_UI(ID_DRAW_Ellipse, OnUpdateDrawEllipse)
	ON_COMMAND(ID_DRAW_CalloutText, OnDrawCalloutText)
	ON_UPDATE_COMMAND_UI(ID_DRAW_CalloutText, OnUpdateDrawCalloutText)
	ON_COMMAND(ID_DRAW_HANDLINE, OnDrawFreeHandline)
	ON_UPDATE_COMMAND_UI(ID_DRAW_HANDLINE, OnUpdateDrawFreeHandline)
	ON_COMMAND(ID_DRAW_SAVEAS, OnDrawSaveAs)
	ON_UPDATE_COMMAND_UI(ID_DRAW_SAVEAS, OnUpdateDrawSaveAs)
	ON_COMMAND(ID_DRAW_Export, OnDrawExport)
	ON_UPDATE_COMMAND_UI(ID_DRAW_Export, OnUpdateDrawExport)

	//量测工具
	 
	ON_COMMAND(ID_LINE_MEASURE, OnLineMeasure)
	ON_UPDATE_COMMAND_UI(ID_LINE_MEASURE, OnUpdateLineMeasure)
	ON_COMMAND(ID_AREA_MEASURE, OnAreaMeasure)
	ON_UPDATE_COMMAND_UI(ID_AREA_MEASURE, OnUpdateAreaMeasure)

	//编辑工具

	ON_COMMAND(ID_EDITOR_START, OnEditorStart)
	ON_UPDATE_COMMAND_UI(ID_EDITOR_START, OnUpdateEditorStart)
	ON_COMMAND(ID_EDITOR_SKETCH, OnEditorSketch)
	ON_UPDATE_COMMAND_UI(ID_EDITOR_SKETCH, OnUpdateEditorSketch)
	ON_COMMAND(ID_EDITOR_EDIT, OnEditerEdit)
	ON_UPDATE_COMMAND_UI(ID_EDITOR_EDIT, OnUpdateEditerEdit)
	ON_COMMAND(ID_EDITOR_REDO, OnEditerRedo)
	ON_UPDATE_COMMAND_UI(ID_EDITOR_REDO, OnUpdateEditerRedo)
	ON_COMMAND(ID_EDITOR_UNDO, OnEditerUndo)
	ON_UPDATE_COMMAND_UI(ID_EDITOR_UNDO, OnUpdateEditerUndo)
	ON_COMMAND(ID_EDITOR_END, OnEditerEnd)
	ON_UPDATE_COMMAND_UI(ID_EDITOR_END, OnUpdateEditerEnd)
	ON_COMMAND(ID_EDITOR_SAVE, OnEditerSave)
	ON_UPDATE_COMMAND_UI(ID_EDITOR_SAVE, OnUpdateEditerSave)
	ON_COMMAND(ID_DELETE_FEATURES, OnEditerDel)
	ON_UPDATE_COMMAND_UI(ID_DELETE_FEATURES, OnUpdateEditerSave)
	ON_COMMAND(ID_UNION_FEATURES, OnEditerUnion)
	ON_UPDATE_COMMAND_UI(ID_UNION_FEATURES, OnUpdateEditerUnion)
	ON_COMMAND(ID_FEATURES_INFO, OnFeatureInfo)
	ON_COMMAND(ID_ATTRIBUTE_EDIT, OnEditerAttribute)
	ON_UPDATE_COMMAND_UI(ID_ATTRIBUTE_EDIT, OnUpdateEditerAttribute)
	ON_COMMAND(ID_SELECTFEATURE, OnSelectFeature)
	ON_UPDATE_COMMAND_UI(ID_SELECTFEATURE, OnUpdateSelectFeature)
	ON_COMMAND(ID_IncrementalImport, OnIncrementalImport)
	ON_UPDATE_COMMAND_UI(ID_IncrementalImport, OnUpdateIncrementalImport)


	ON_COMMAND(ID_CHANGE_DETECT, OnImgChangeDetect)
	ON_COMMAND(ID_CHANGE_RENDER, OnImgChangeRender)
	ON_COMMAND(ID_WATER_EXTRACT, OnWaterExtract)
	ON_COMMAND(ID_MAGIC_STICK, OnMagicStick)
	ON_UPDATE_COMMAND_UI(ID_MAGIC_STICK, OnUpdateMagicStick)
	ON_COMMAND(ID_CLASSIFY_FUZZYKMEAN, OnClassifyFuzzyKMean)


	ON_COMMAND(ID_MAGICSTICK_LAYER,OnMagicStickLayer)
	ON_COMMAND(ID_MAGICSTICK_TOL,OnMagicTol)

	ON_COMMAND(ID_MAGIC_STICK, OnMagicStick)

	ON_COMMAND(ID_REMOVELASTMAGIC,OnDeleteLastMagic)

	//ON_COMMAND(ID_EDGE_EXTRACT,OnEdgeTrack)

	ON_COMMAND(ID_CHANGE_SETSYMBOL,OnChangeSetSymbol)

	ON_COMMAND(ID_SEND_BLUEFILE,OnSendBlueToothFile)

	ON_COMMAND(ID_FOR_HELP,OnOpenHelp)

	ON_REGISTERED_MESSAGE(BCGM_CHANGE_ACTIVE_TAB,OnChangeActiveTab)

END_MESSAGE_MAP()

// CUAVSoftView construction/destruction

CUAVSoftView::CUAVSoftView()
{

	boost::function<void (Carto::ILayerPtr)> fundl = boost::bind(&CUAVSoftView::LayerDelEvent,this, _1);

	m_ConnectionMapLayerDeleted = Carto::CMap::RegisterDeleteLayer(fundl);

}

CUAVSoftView::~CUAVSoftView()
{
	m_ConnectionMapLayerDeleted.disconnect();
}

BOOL CUAVSoftView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CUAVSoftView drawing

void CUAVSoftView::OnDraw(CDC* /*pDC*/)
{
	CUAVSoftDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}


// CUAVSoftView printing

void CUAVSoftView::OnFilePrintPreview()
{
	BCGPPrintPreview (this);
}

BOOL CUAVSoftView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CUAVSoftView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CUAVSoftView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CUAVSoftView diagnostics

#ifdef _DEBUG
void CUAVSoftView::AssertValid() const
{
	CView::AssertValid();
}

void CUAVSoftView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CUAVSoftDoc* CUAVSoftView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CUAVSoftDoc)));
	return (CUAVSoftDoc*)m_pDocument;
}
#endif //_DEBUG


// CUAVSoftView message handlers

int CUAVSoftView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_WndTab.Create (CBCGPTabWnd::STYLE_3D_VS2005, CRect(0,0,0,0), this, ID_TABCONTROL);


	m_MapCtrl.CreateControl(Framework::CommonUIName::AppMapControl, &m_WndTab, ID_MAPCTRL);
	m_WndTab.AddTab( &m_MapCtrl , "Map" );

	m_LayoutCtrl.CreateControl(Framework::CommonUIName::AppLayoutControl, &m_WndTab,ID_LAYOUTCTRL);
	m_WndTab.AddTab(&m_LayoutCtrl,_T("Layout"));


	CUAVSoftDoc* pDoc = GetDocument();
	pDoc->SetLinkMapCtrl(&m_MapCtrl);
	pDoc->SetLinkLayoutCtrl(&m_LayoutCtrl);

	m_WndTab.SetActiveTab(0);
	m_WndTab.SetFlatFrame ();
	m_WndTab.SetTabBorderSize (0);
	m_WndTab.AutoDestroyWindow (FALSE);

	return 0;
}

void CUAVSoftView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	m_WndTab.SetWindowPos (NULL, -1, -1, cx + 1, cy + 3,
		SWP_SHOWWINDOW | SWP_NOZORDER);
}


CBCGPRibbonComboBox* CUAVSoftView::GetCurLyrCombox()
{
	CMainFrame* pMainFrm = (CMainFrame*)::AfxGetApp()->GetMainWnd();
	CBCGPRibbonComboBox* pCombox = (CBCGPRibbonComboBox*)pMainFrm->m_wndRibbonBar.FindByID(ID_CURRLAYER_COMBO);
	return pCombox;
}
CBCGPRibbonComboBox* CUAVSoftView::GetCurLyrCombox_Vector()
{
	CMainFrame* pMainFrm = (CMainFrame*)::AfxGetApp()->GetMainWnd();
	CBCGPRibbonComboBox* pCombox = (CBCGPRibbonComboBox*)pMainFrm->m_wndRibbonBar.FindByID(ID_CURRLAYER_COMBO_VECTOR);
	return pCombox;
}
// CUAVSoftView message handlers



//打开矢量数据
void CUAVSoftView::OnOpenVector()
{
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

	//_crtBreakAlloc = 9878;


	//测试读取s57数据
	//char *szS57File = "E:\\应用工程\\海图\\S57\\US3AK1DM\\US3AK1DM.000";
	//this->GetDocument()->LoadS57File(szS57File);


	char	szBigBuf[4096] = "";
	CString fileName ="";

	CFileDialog dlg(true, "*.*", "",OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT|OFN_ALLOWMULTISELECT,"shapefile(*.shp)|*.shp|All file(*.*)|*.*|",this);
	dlg.m_ofn.lpstrFile = szBigBuf;
	dlg.m_ofn.nMaxFile = sizeof (szBigBuf);
	if(dlg.DoModal()==IDOK) 
	{
		POSITION pos = dlg.GetStartPosition();
		while (pos != NULL)
		{
			fileName = dlg.GetNextPathName (pos);
			this->GetDocument()->LoadShpFile(fileName);

		}
		m_MapCtrl.UpdateControl(drawAll);
		RefreshLayerCombo();
	}


}

void CUAVSoftView::OnOpenImg()
{
	char	szBigBuf[4096] = "";


	CString fileName("");
	CFileDialog dlg(true, "*.*", "",OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT|OFN_ALLOWMULTISELECT,"影像数据(*.tif;*.img;*.tiff;*.bmp)|*.tif;*.img;*.tiff;*.bmp|All Files(*.*)|*.*||",this);
	dlg.m_ofn.lpstrFile = szBigBuf;
	dlg.m_ofn.nMaxFile = sizeof (szBigBuf);

	if(dlg.DoModal()==IDOK) 
	{
		POSITION pos = dlg.GetStartPosition();
		while (pos != NULL)
		{
			fileName = dlg.GetNextPathName (pos);
			this->GetDocument()->LoadImageFile(fileName);

		}

		m_MapCtrl.UpdateControl(drawAll);
		RefreshLayerCombo();

	}



}
	//layout 浏览工具
	afx_msg void CUAVSoftView::OnLayoutPan()
	{
		Framework::ITool* pTool = NULL;
		m_LayoutCtrl.SetCurTool("LayoutPanTool");

		pTool=Framework::ITool::FindTool("LayoutPanTool");
		if(pTool)
		{
			pTool->Initialize(dynamic_cast<Framework::IUIObject*>(&m_LayoutCtrl));
		}
	}
	afx_msg void CUAVSoftView::OnUpdateLayoutPan(CCmdUI* pCmdUI)
	{
		pCmdUI->SetCheck(m_MapCtrl.GetCurToolName() == "LayoutPanTool");
	}

	afx_msg void CUAVSoftView::OnLayoutZoomin()
	{
		
		Framework::ITool* pTool = NULL;
		m_LayoutCtrl.SetCurTool("LayoutZoomInTool");

		pTool=Framework::ITool::FindTool("LayoutZoomInTool");
		if(pTool)
		{
			pTool->Initialize(dynamic_cast<Framework::IUIObject*>(&m_LayoutCtrl));
		}
	}
	afx_msg void CUAVSoftView::OnUpdateLayoutZoomin(CCmdUI* pCmdUI)
	{
		pCmdUI->SetCheck(m_LayoutCtrl.GetCurToolName() == "LayoutZoomInTool");
	}

	afx_msg void CUAVSoftView::OnLayoutZoomout()
	{
		Framework::ITool* pTool = NULL;
		m_LayoutCtrl.SetCurTool("LayoutZoomOutTool");

		pTool=Framework::ITool::FindTool("LayoutZoomOutTool");
		if(pTool)
		{
			pTool->Initialize(dynamic_cast<Framework::IUIObject*>(&m_LayoutCtrl));
		}
	}
	afx_msg void CUAVSoftView::OnUpdateLayoutZoomout(CCmdUI* pCmdUI)
	{
		pCmdUI->SetCheck(m_LayoutCtrl.GetCurToolName() == "LayoutZoomOutTool");
	}

	afx_msg void CUAVSoftView::OnLayoutFullView()
	{
		Framework::ICommand* pCmd = NULL;
		m_LayoutCtrl.SetCurTool("LayoutZoomFullExtent");
		pCmd= Framework::ICommand::FindCommand("LayoutZoomFullExtent");
		if(pCmd)
		{
			pCmd->Initialize(dynamic_cast<Framework::IUIObject*>(&m_LayoutCtrl));
			pCmd->Click();
		}
	}

	void CUAVSoftView::OnUpdateLayoutZoomFullExtent(CCmdUI *pCmdUI)
	{
		pCmdUI->SetCheck(m_LayoutCtrl.GetCurToolName() == "LayoutZoomFullExtent");
	}

	void CUAVSoftView::OnLayoutZoomActualSize()
	{
		Framework::ICommand* pCmd = NULL;
		m_LayoutCtrl.SetCurTool("LayoutZoomActualSize");
		pCmd= Framework::ICommand::FindCommand("LayoutZoomActualSize");
		if(pCmd)
		{
			pCmd->Initialize(dynamic_cast<Framework::IUIObject*>(&m_LayoutCtrl));
			pCmd->Click();
		}
	}

	void CUAVSoftView::OnUpdateLayoutZoomActualSize(CCmdUI* pCmdUI)
	{
		pCmdUI->SetCheck(m_LayoutCtrl.GetCurToolName() == "LayoutZoomActualSize");
	}

	void CUAVSoftView::OnSelectFrameElement()
	{
		Framework::ITool* pTool = NULL;
		m_LayoutCtrl.SetCurTool("SelectFrameElementsTool");

		pTool=Framework::ITool::FindTool("SelectFrameElementsTool");
		if(pTool)
		{
			pTool->Initialize(dynamic_cast<Framework::IUIObject*>(&m_LayoutCtrl));
		}
	}
	void CUAVSoftView::OnUpdateSelectFrameElement(CCmdUI* pCmdUI)
	{
		pCmdUI->SetCheck(m_LayoutCtrl.GetCurToolName() == "SelectFrameElementsTool");
	}

	void CUAVSoftView::OnDrawNorthArrow()
	{
		Framework::ICommand* pCmd = NULL;
		m_LayoutCtrl.SetCurTool("DrawNorthArrowCmd");
		pCmd= Framework::ICommand::FindCommand("DrawNorthArrowCmd");
		if(pCmd)
		{
			pCmd->Initialize(dynamic_cast<Framework::IUIObject*>(&m_LayoutCtrl));
			pCmd->Click();
		}
	}

	void CUAVSoftView::OnUpdateDrawNorthArrow(CCmdUI *pCmdUI)
	{
		pCmdUI->SetCheck(m_LayoutCtrl.GetCurToolName() == "DrawNorthArrowCmd");
	}

	void CUAVSoftView::OnDrawScaleBar()
	{
		Framework::ICommand* pCmd = NULL;
		m_LayoutCtrl.SetCurTool("DrawScaleBarCmd");
		pCmd= Framework::ICommand::FindCommand("DrawScaleBarCmd");
		if(pCmd)
		{
			pCmd->Initialize(dynamic_cast<Framework::IUIObject*>(&m_LayoutCtrl));
			pCmd->Click();
		}
	}

	void CUAVSoftView::OnUpdateDrawScaleBar(CCmdUI *pCmdUI)
	{
		pCmdUI->SetCheck(m_LayoutCtrl.GetCurToolName() == "DrawScaleBarCmd");
	}

	void CUAVSoftView::OnDrawLegend()
	{
		Framework::ICommand* pCmd = NULL;
		m_LayoutCtrl.SetCurTool("DrawLegendCmd");
		pCmd= Framework::ICommand::FindCommand("DrawLegendCmd");
		if(pCmd)
		{
			pCmd->Initialize(dynamic_cast<Framework::IUIObject*>(&m_LayoutCtrl));
			pCmd->Click();
		}
	}

	void CUAVSoftView::OnUpdateDrawLegend(CCmdUI *pCmdUI)
	{
		pCmdUI->SetCheck(m_LayoutCtrl.GetCurToolName() == "DrawLegendCmd");
	}

	void CUAVSoftView::OnDrawMapTitle()
	{
		Framework::ICommand* pCmd = NULL;
		m_LayoutCtrl.SetCurTool("DrawMapTitleCmd");
		pCmd= Framework::ICommand::FindCommand("DrawMapTitleCmd");
		if(pCmd)
		{
			pCmd->Initialize(dynamic_cast<Framework::IUIObject*>(&m_LayoutCtrl));
			pCmd->Click();
		}
	}

	void CUAVSoftView::OnUpdateDrawMapTitle(CCmdUI *pCmdUI)
	{
		pCmdUI->SetCheck(m_LayoutCtrl.GetCurToolName() == "DrawMapTitle");
	}

void CUAVSoftView::OnMapPan()
{
	Framework::ITool* pTool = NULL;
	m_MapCtrl.SetCurTool("MapPan");

	pTool=Framework::ITool::FindTool("MapPan");
	if(pTool)
	{
		pTool->Initialize(dynamic_cast<Framework::IUIObject*>(&m_MapCtrl));
	}
}

void CUAVSoftView::OnUpdateMapPan(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_MapCtrl.GetCurToolName() == "MapPan");

}

void CUAVSoftView::OnMapZoomin()
{
	Framework::ITool* pTool = NULL;
	m_MapCtrl.SetCurTool("MapZoomin");

	pTool=Framework::ITool::FindTool("MapZoomin");
	if(pTool)
	{
		pTool->Initialize(dynamic_cast<Framework::IUIObject*>(&m_MapCtrl));
	}
}

void CUAVSoftView::OnUpdateMapZoomin(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_MapCtrl.GetCurToolName() == "MapZoomin");
}

void CUAVSoftView::OnMapZoomout()
{
	Framework::ITool* pTool = NULL;
	m_MapCtrl.SetCurTool("MapZoomout");

	pTool=Framework::ITool::FindTool("MapZoomout");
	if(pTool)
	{
		pTool->Initialize(dynamic_cast<Framework::IUIObject*>(&m_MapCtrl));
	}
}

void CUAVSoftView::OnUpdateMapZoomout(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_MapCtrl.GetCurToolName() == "MapZoomout");
}

void CUAVSoftView::OnMapPreExtent()
{
	Carto::CMapPtr pMap =m_MapCtrl.GetMap();
	if(!pMap)
	{
		return;
	}
	pMap->GetDisplay()->GetDisplayTransformation().SetPreExtent();
	m_MapCtrl.UpdateControl(drawAll);
}

void CUAVSoftView::OnUpdateMapPreExtent(CCmdUI* pCmdUI)
{
	Carto::CMapPtr pMap =m_MapCtrl.GetMap();
	if(!pMap)
	{
		pCmdUI->Enable(FALSE);
	}
	pCmdUI->Enable(pMap->GetDisplay()->GetDisplayTransformation().HasPreExtent());
}

void CUAVSoftView::OnMapNextExtent()
{
	Carto::CMapPtr pMap =m_MapCtrl.GetMap();
	if(!pMap)
	{
		return;
	}
	pMap->GetDisplay()->GetDisplayTransformation().SetNextExtent();
	m_MapCtrl.UpdateControl(drawAll);
}

void CUAVSoftView::OnUpdateMapNextExtent(CCmdUI* pCmdUI)
{
	Carto::CMapPtr pMap =m_MapCtrl.GetMap();
	if(!pMap)
	{
		pCmdUI->Enable(FALSE);
	}
	pCmdUI->Enable(pMap->GetDisplay()->GetDisplayTransformation().HasNextExtent());
}

//全图显示
void CUAVSoftView::OnMapFullView()
{
	Carto::CMapPtr pMap =m_MapCtrl.GetMap();
	if(!pMap)
	{
		return;
	}
	GEOMETRY::geom::Envelope env = pMap->GetExtent();

	pMap->GetDisplay()->GetDisplayTransformation().FitViewBound(env);

	m_MapCtrl.UpdateControl(drawAll);

}




void CUAVSoftView::OnDrawRect()
{
	Framework::ITool* pTool = NULL;
	m_MapCtrl.SetCurTool("DrawRectElementTool");

	pTool=Framework::ITool::FindTool("DrawRectElementTool");
	if(pTool)
	{
		pTool->Initialize(dynamic_cast<Framework::IUIObject*>(&m_MapCtrl));
	}
}

void CUAVSoftView::OnUpdateDrawRect(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_MapCtrl.GetCurToolName() == "DrawRectElementTool");

}

void CUAVSoftView::OnDrawSelect()
{
	Framework::ITool* pTool = NULL;
	m_MapCtrl.SetCurTool("SelectElementTool");

	pTool=Framework::ITool::FindTool("SelectElementTool");
	if(pTool)
	{
		pTool->Initialize(dynamic_cast<Framework::IUIObject*>(&m_MapCtrl));
	}
}

void CUAVSoftView::OnUpdateDrawSelect(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_MapCtrl.GetCurToolName() == "SelectElementTool");

}

afx_msg void CUAVSoftView::OnDrawMarker()
{
	Framework::ITool* pTool = NULL;
	m_MapCtrl.SetCurTool("DrawSimpleMarkerElementTool");

	pTool=Framework::ITool::FindTool("DrawSimpleMarkerElementTool");
	if(pTool)
	{
		pTool->Initialize(dynamic_cast<Framework::IUIObject*>(&m_MapCtrl));
	}
}
afx_msg void CUAVSoftView::OnUpdateDrawMarker(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_MapCtrl.GetCurToolName() == "DrawSimpleMarkerElementTool");
}
afx_msg void CUAVSoftView::OnDrawCircle()
{
	Framework::ITool* pTool = NULL;
	m_MapCtrl.SetCurTool("DrawCircleElementTool");

	pTool=Framework::ITool::FindTool("DrawCircleElementTool");
	if(pTool)
	{
		pTool->Initialize(dynamic_cast<Framework::IUIObject*>(&m_MapCtrl));
	}
	//Framework::ICommand* pCommand = NULL;
	//m_MapCtrl.SetCurTool("UndoOperationCmd");

	//pCommand=Framework::ICommand::FindCommand("UndoOperationCmd");
	//if(pCommand)
	//{
	//	pCommand->Initialize(dynamic_cast<Framework::IUIObject*>(&m_MapCtrl));
	//	pCommand->Click();
	//}

}
afx_msg void CUAVSoftView::OnUpdateDrawCircle(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_MapCtrl.GetCurToolName() == "DrawCircleElementTool");
}
afx_msg void CUAVSoftView::OnDrawPolygon()
{
	Framework::ITool* pTool = NULL;
	m_MapCtrl.SetCurTool("DrawPolygonElementTool");

	pTool=Framework::ITool::FindTool("DrawPolygonElementTool");
	if(pTool)
	{
		pTool->Initialize(dynamic_cast<Framework::IUIObject*>(&m_MapCtrl));
	}
}
afx_msg void CUAVSoftView::OnUpdateDrawPolygon(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_MapCtrl.GetCurToolName() == "DrawPolygonElementTool");
}

afx_msg void CUAVSoftView::OnLineMeasure()
{
	Framework::ITool* pTool = NULL;
	m_MapCtrl.SetCurTool("LineMeasureTool");

	pTool=Framework::ITool::FindTool("LineMeasureTool");
	if(pTool)
	{
		pTool->Initialize(dynamic_cast<Framework::IUIObject*>(&m_MapCtrl));
	}
}
afx_msg void CUAVSoftView::OnUpdateLineMeasure(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_MapCtrl.GetCurToolName() == "LineMeasureTool");
}
afx_msg void CUAVSoftView::OnAreaMeasure()
{
	Framework::ITool* pTool = NULL;
	m_MapCtrl.SetCurTool("AreaMeasureTool");

	pTool=Framework::ITool::FindTool("AreaMeasureTool");
	if(pTool)
	{
		pTool->Initialize(dynamic_cast<Framework::IUIObject*>(&m_MapCtrl));
	}
}
afx_msg void CUAVSoftView::OnUpdateAreaMeasure(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_MapCtrl.GetCurToolName() == "AreaMeasureTool");
}


afx_msg void CUAVSoftView::OnDrawPolyline()
{
	Framework::ITool* pTool = NULL;
	m_MapCtrl.SetCurTool("DrawPolylineElementTool");

	pTool=Framework::ITool::FindTool("DrawPolylineElementTool");
	if(pTool)
	{
		pTool->Initialize(dynamic_cast<Framework::IUIObject*>(&m_MapCtrl));
	}
}
afx_msg void CUAVSoftView::OnUpdateDrawPolyline(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_MapCtrl.GetCurToolName() == "DrawPolylineElementTool");
}
afx_msg void CUAVSoftView::OnDrawCurve()
{
	Framework::ITool* pTool = NULL;
	m_MapCtrl.SetCurTool("DrawBezierCurveElementTool");

	pTool=Framework::ITool::FindTool("DrawBezierCurveElementTool");
	if(pTool)
	{
		pTool->Initialize(dynamic_cast<Framework::IUIObject*>(&m_MapCtrl));
	}
}
afx_msg void CUAVSoftView::OnUpdateDrawCurve(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_MapCtrl.GetCurToolName() == "DrawBezierCurveElementTool");
}
afx_msg void CUAVSoftView::OnDrawText()
{
	Framework::ITool* pTool = NULL;
	m_MapCtrl.SetCurTool("DrawTextElementTool");

	pTool=Framework::ITool::FindTool("DrawTextElementTool");
	if(pTool)
	{
		pTool->Initialize(dynamic_cast<Framework::IUIObject*>(&m_MapCtrl));
	}
}
afx_msg void CUAVSoftView::OnUpdateDrawtext(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_MapCtrl.GetCurToolName() == "DrawTextElementTool");
}


afx_msg void CUAVSoftView::OnEditElement()
{
	Framework::ITool* pTool = NULL;
	m_MapCtrl.SetCurTool("EditElementVertixTool");

	pTool=Framework::ITool::FindTool("EditElementVertixTool");
	if(pTool)
	{
		pTool->Initialize(dynamic_cast<Framework::IUIObject*>(&m_MapCtrl));
	}
}
afx_msg void CUAVSoftView::OnUpdateEditElement(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_MapCtrl.GetCurToolName() == "EditElementVertixTool");
}

afx_msg void CUAVSoftView::OnDrawEllipse()
{
	Framework::ITool* pTool = NULL;
	m_MapCtrl.SetCurTool("DrawEllipseElementTool");

	pTool=Framework::ITool::FindTool("DrawEllipseElementTool");
	if(pTool)
	{
		pTool->Initialize(dynamic_cast<Framework::IUIObject*>(&m_MapCtrl));
	}
}
afx_msg void CUAVSoftView::OnUpdateDrawEllipse(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_MapCtrl.GetCurToolName() == "DrawEllipseElementTool");
}
afx_msg void CUAVSoftView::OnDrawCalloutText()
{
	Framework::ITool* pTool = NULL;
	m_MapCtrl.SetCurTool("DrawCalloutTextElementTool");

	pTool=Framework::ITool::FindTool("DrawCalloutTextElementTool");
	if(pTool)
	{
		pTool->Initialize(dynamic_cast<Framework::IUIObject*>(&m_MapCtrl));
	}
}
afx_msg void CUAVSoftView::OnUpdateDrawCalloutText(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_MapCtrl.GetCurToolName() == "DrawCalloutTextElementTool");
}


afx_msg void CUAVSoftView::OnDrawFreeHandline()
{
	Framework::ITool* pTool = NULL;
	m_MapCtrl.SetCurTool("DrawFreehandLineElement");

	pTool=Framework::ITool::FindTool("DrawFreehandLineElement");
	if(pTool)
	{
		pTool->Initialize(dynamic_cast<Framework::IUIObject*>(&m_MapCtrl));
	}
}
afx_msg void CUAVSoftView::OnUpdateDrawFreeHandline(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_MapCtrl.GetCurToolName() == "DrawFreehandLineElement");
}
afx_msg void CUAVSoftView::OnDrawSaveAs()
{
	//element 转成shp

	Carto::CMapPtr ipMap = m_MapCtrl.GetMap();
	Carto::CGraphicLayerPtr ipGraphicLayer = ipMap->GetGraphicLayer();
	long lElementCnt = ipGraphicLayer->GetElementCount();
	if(lElementCnt <1)return;

	CDlgDrawingExport Dlg;
	if(Dlg.DoModal()==IDOK)
	{
		char* fileName = Dlg.m_ExportPath.GetBuffer(Dlg.m_ExportPath.GetLength());

		Carto::CLayerArray &layers = ipMap->GetLayers();

		Carto::ILayerPtr pLayer;
		int index;
		bool bfind =false;
		bool flag = false;
		for(int i=0;i<layers.GetSize();i++)
		{
			pLayer =layers.GetAt(i);
			if(!pLayer)
			{
				continue;
			}
			if(pLayer->GetLayerType()==Carto::FeatureLayer)
			{
				if (strcmp(pLayer->GetName().c_str(),fileName) == 0)
				{
					flag = true;
					break;
				}
			}
		}
		if(flag)
		{
			Geodatabase::IWorkspace *pWorkspace = pLayer->GetDataObject()->GetWorkspace();
			//开始编辑
			bool srcState = pWorkspace->IsEditing();
			if(srcState== false)
				pWorkspace->StartEdit();
			Geodatabase::IFeatureClassPtr pFeatureClass =  (Geodatabase::IFeatureClassPtr) pLayer->GetDataObject();
			ipGraphicLayer->SaveElementAsShp(pFeatureClass,!Dlg.m_bExpoertAll,Dlg.m_DrawingType);

			pWorkspace->StopEditOperation();
			if(srcState == false)
				pWorkspace->StopEdit(true);
		}
		else
		{
			ipGraphicLayer->SaveElementAsShp(fileName,!Dlg.m_bExpoertAll,Dlg.m_DrawingType);

			if (Dlg.m_CheckAddMap)
			{	
				this->GetDocument()->LoadShpFile(fileName);
				RefreshLayerCombo();
			}
		}
		m_MapCtrl.UpdateControl((DrawContent)(drawElement | drawAll));

	}

}
afx_msg void CUAVSoftView::OnUpdateDrawSaveAs(CCmdUI* pCmdUI)
{

}

afx_msg void CUAVSoftView::OnDrawExport()
{
	




}
afx_msg void CUAVSoftView::OnUpdateDrawExport(CCmdUI* pCmdUI)
{

}

void CUAVSoftView::OnSelectFeatureByPoint()
{
	Framework::ITool* pTool = NULL;
	m_MapCtrl.SetCurTool("SelectbyPoint");

	pTool=Framework::ITool::FindTool("SelectbyPoint");
	if(pTool)
	{
		pTool->Initialize(dynamic_cast<Framework::IUIObject*>(&m_MapCtrl));
	}
}
Carto::ILayerPtr CUAVSoftView::GetComboLayer()
{
	int nSize = m_MapCtrl.GetMap()->GetLayers().GetSize();
	int nSel = GetCurLyrCombox()->GetCurSel();
	if (nSel >=0 && nSel<nSize)
	{
		return FindLayerbyPointer((Carto::ILayer*)GetCurLyrCombox()->GetItemData(nSel));
	}
	return NULL;
}
Carto::ILayerPtr CUAVSoftView::GetComboLayer_Vector()
{
	int nSize = m_MapCtrl.GetMap()->GetLayers().GetSize();
	int nSel = GetCurLyrCombox_Vector()->GetCurSel();
	if (nSel >=0 && nSel<nSize)
	{
		return FindLayerbyPointer((Carto::ILayer*)GetCurLyrCombox()->GetItemData(nSel));
	}
	return NULL;
}
void CUAVSoftView::OnCurrLayerCombo()
{

}
void CUAVSoftView::OnCurrLayerCombo_Vector()
{
	std::string curLayerName = GetCurLyrCombox_Vector()->GetItem(GetCurLyrCombox_Vector()->GetCurSel());
	Carto::CMapPtr pMap =m_MapCtrl.GetMap();
	if(pMap)
	{
		if(!pMap->GetEditor())
		{
			pMap->SetEditor(new Editor::CEditor(pMap.get()));

		}
		Editor::CEditor* pEditor = (Editor::CEditor*)pMap->GetEditor().get();
		pEditor->ChangeCurLayer(curLayerName);
	}

}
void CUAVSoftView::OnUpdateCurrlayerCombo_Vector(CCmdUI* pCmdUI)
{

	Carto::CMapPtr pMap =m_MapCtrl.GetMap();
	if(!pMap)
	{
		pCmdUI->Enable(FALSE);
	}
	if(!pMap->GetEditor())
	{
		pMap->SetEditor(new Editor::CEditor(pMap.get()));

	}
	pCmdUI->Enable(pMap->GetEditor()->IsEditing());
}
void CUAVSoftView::OnBrightRestore()
{
}
void CUAVSoftView::OnContrastRestore()
{
}
void CUAVSoftView::OnTransparentRestore()
{
}
void CUAVSoftView::OnBrightSlider()
{
	BrightContrast();
	CMainFrame* pMainFrm = (CMainFrame*)::AfxGetApp()->GetMainWnd();
	CBCGPRibbonSlider* pSlider = DYNAMIC_DOWNCAST (CBCGPRibbonSlider,(CBCGPRibbonComboBox*)pMainFrm->m_wndRibbonBar.FindByID (ID_BRIGHT_SLIDER));
	ASSERT_VALID (pSlider);
	int nPos = pSlider->GetPos();
	CString str;
	str.Format("%d", nPos);
	CBCGPRibbonEdit* pZoom = DYNAMIC_DOWNCAST (CBCGPRibbonEdit,(CBCGPRibbonComboBox*)pMainFrm->m_wndRibbonBar.FindByID (ID_BRIGHT_TEXT));
	ASSERT_VALID (pZoom);
	pZoom->SetEditText(str);
}
void CUAVSoftView::OnTransparentSlider()
{
	CMainFrame* pMainFrm = (CMainFrame*)::AfxGetApp()->GetMainWnd();
	CBCGPRibbonSlider* pSlider = DYNAMIC_DOWNCAST (CBCGPRibbonSlider,(CBCGPRibbonComboBox*)pMainFrm->m_wndRibbonBar.FindByID (ID_TRANSPARENT_SLIDER));
	ASSERT_VALID (pSlider);
	int nPos = pSlider->GetPos();
	Carto::CRasterLayerPtr layer = Carto::CRasterLayerPtr(GetComboLayer());
	layer->SetTransparent(nPos);
	CString str;
	str.Format("%d", nPos);
	CBCGPRibbonEdit* pZoom = DYNAMIC_DOWNCAST (CBCGPRibbonEdit,(CBCGPRibbonComboBox*)pMainFrm->m_wndRibbonBar.FindByID (ID_TRANSPARENT_TEXT));
	ASSERT_VALID (pZoom);
	pZoom->SetEditText(str);
	m_MapCtrl.UpdateControl(drawAll);
	UpdateData(FALSE);
}
void CUAVSoftView::OnContrastSlider()
{
	BrightContrast();
	CMainFrame* pMainFrm = (CMainFrame*)::AfxGetApp()->GetMainWnd();
	CBCGPRibbonSlider* pSlider = DYNAMIC_DOWNCAST (CBCGPRibbonSlider,(CBCGPRibbonComboBox*)pMainFrm->m_wndRibbonBar.FindByID (ID_CONTRAST_SLIDER));
	ASSERT_VALID (pSlider);
	int nPos = pSlider->GetPos();
	CString str;
	str.Format("%d", nPos);
	CBCGPRibbonEdit* pZoom = DYNAMIC_DOWNCAST (CBCGPRibbonEdit,(CBCGPRibbonComboBox*)pMainFrm->m_wndRibbonBar.FindByID (ID_CONTRAST_TEXT));
	ASSERT_VALID (pZoom);
	pZoom->SetEditText(str);
}
void CUAVSoftView::OnUpdateBrightRestore(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(IsLayerComboNull());
}
void CUAVSoftView::OnUpdateContrastRestore(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(IsLayerComboNull());
}
void CUAVSoftView::OnUpdateTransparentRestore(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(IsLayerComboNull());
}
void CUAVSoftView::OnUpdateBrightSlider(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(IsLayerComboNull());
}
void CUAVSoftView::OnUpdateContrastSlider(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(IsLayerComboNull());
}
void CUAVSoftView::OnUpdateTransparentSlider(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(IsLayerComboNull());
}
void CUAVSoftView::OnSwipe()
{
	Framework::ICommand* pCmd = NULL;
	m_MapCtrl.SetCurTool("SwipeEnhance");
	m_MapCtrl.GetMap()->SetOperLayer(GetComboLayer());
	pCmd= Framework::ICommand::FindCommand("SwipeEnhance");
	if(pCmd)
	{
		pCmd->Click();
	}
}
void CUAVSoftView::OnUpdateSwipe(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(IsLayerComboNull());
}
void CUAVSoftView::OnFlick()
{
	Framework::ICommand* pCmd = NULL;
	m_MapCtrl.SetCurTool("Flick");
	m_MapCtrl.GetMap()->SetOperLayer(GetComboLayer());
	pCmd= Framework::ICommand::FindCommand("Flick");
	if(pCmd)
	{
		pCmd->Click();
	}
}
void CUAVSoftView::OnUpdateFlick(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(IsLayerComboNull());
}
void CUAVSoftView::BrightContrast(int nBright,int nContrast)
{
	if (nBright == -1)
	{
		CMainFrame* pMainFrm = (CMainFrame*)::AfxGetApp()->GetMainWnd();
		CBCGPRibbonSlider* pSlider = DYNAMIC_DOWNCAST (CBCGPRibbonSlider,(CBCGPRibbonComboBox*)pMainFrm->m_wndRibbonBar.FindByID (ID_BRIGHT_SLIDER));
		ASSERT_VALID (pSlider);
		nBright = pSlider->GetPos();
	}
	if (nContrast == -1)
	{
		CMainFrame* pMainFrm = (CMainFrame*)::AfxGetApp()->GetMainWnd();
		CBCGPRibbonSlider* pSlider = DYNAMIC_DOWNCAST (CBCGPRibbonSlider,(CBCGPRibbonComboBox*)pMainFrm->m_wndRibbonBar.FindByID (ID_CONTRAST_SLIDER));
		ASSERT_VALID (pSlider);
		nContrast = pSlider->GetPos();
	}

	Carto::CRasterLayerPtr layer = Carto::CRasterLayerPtr(GetComboLayer());
	Carto::IRasterRenderPtr pRender = layer->GetRender();
	if(!pRender)
		return;
	Carto::CRasterRGBRender* pRGBRender =  dynamic_cast<Carto::CRasterRGBRender*>(pRender.get());
	long RChannel=pRGBRender->GetRedBandIndex();
	long GChannel=pRGBRender->GetGreenBandIndex();
	long BChannel=pRGBRender->GetBlueBandIndex();
	BYTE *srcRLUT = new BYTE[256];
	BYTE *srcGLUT = new BYTE[256];
	BYTE *srcBLUT = new BYTE[256];
	//这里计算LUT是有问题的，应该获取当前的LUT，暂时先这样
	for (int i=0; i<256; ++i)
	{
		srcRLUT[i] = i;
		srcGLUT[i] = i;
		srcBLUT[i] = i;
	}
	if (pRGBRender->GetRGBMode())
	{
		pRGBRender->SetBrightAndContrast(srcRLUT,srcGLUT,srcBLUT,nBright,nContrast);
	}
	else
	{
		pRGBRender->SetBrightAndContrast(srcRLUT,nBright,nContrast);
	}
	if(srcRLUT != NULL)
	{
		delete []srcRLUT;
		srcRLUT = NULL;

	}
	if(srcGLUT != NULL)
	{
		delete []srcGLUT;
		srcGLUT = NULL;

	}
	if(srcBLUT != NULL)
	{
		delete []srcBLUT;
		srcBLUT = NULL;
	}
	m_MapCtrl.UpdateControl(drawAll);
	UpdateData(FALSE);
}
bool CUAVSoftView::IsLayerComboNull()
{
	int nSize = m_MapCtrl.GetMap()->GetLayers().GetSize();
	int nSel = GetCurLyrCombox()->GetCurSel();
	if (nSel>=0 && nSel<nSize)
	{
		return true;	
	}
	return false;
}

bool  CUAVSoftView::IsLayerComboCurFirstVisual()
{
	int nSize = m_MapCtrl.GetMap()->GetLayers().GetSize();
	Carto::ILayerPtr pCurLyr = GetComboLayer();
	if (NULL == pCurLyr)
	{
		return false;
	}
	BOOL bVisual = FALSE;
	bVisual = pCurLyr->GetVisible();
	if (!bVisual)
	{
		return false;
	}
	Carto::ILayerPtr pLyr = NULL;
	for (int i=nSize - 1; i> -1; i--)
	{
		pLyr = m_MapCtrl.GetMap()->GetLayers().GetAt(i);
		bVisual = pLyr->GetVisible();
		if (bVisual && pLyr != pCurLyr)
		{
			return false;
		}
		else if (pLyr == pCurLyr)
		{
			break;
		}
	}
	return true;
}

//通过指针查找图层的智能指针
Carto::ILayerPtr CUAVSoftView::FindLayerbyPointer(Carto::ILayer* pLayer)
{
	Carto::CLayerArray &layers =m_MapCtrl.GetMap()->GetLayers();
	Carto::ILayerPtr pl;
	for(int i=0;i<layers.GetSize();i++)
	{
		pl =layers.GetAt(i);
		if(pl.get()==pLayer)
		{
			return pl;
		}
	}
	return NULL;
}
void CUAVSoftView::RefreshLayerCombo()
{
	int nSize = m_MapCtrl.GetMap()->GetLayers().GetSize();
	GetCurLyrCombox()->RemoveAllItems();
	GetCurLyrCombox_Vector()->RemoveAllItems();
	GetMagicLayer()->RemoveAllItems();
	for (int i=0; i<nSize; ++i)
	{
		Carto::ILayerPtr pLayer = m_MapCtrl.GetMap()->GetLayers().GetAt(i);
		std::string strName = pLayer->GetName();
		//判断图层类型
		if(pLayer->GetLayerType()==Carto::RasterLayer)
		{
			GetCurLyrCombox()->AddItem(strName.c_str(),(DWORD_PTR)pLayer.get());
			GetMagicLayer()->AddItem(strName.c_str(),(DWORD_PTR)pLayer.get());

		}
		else if(pLayer->GetLayerType()==Carto::FeatureLayer)
		{
			GetCurLyrCombox_Vector()->AddItem(strName.c_str(),(DWORD_PTR)pLayer.get());

		}


	}
	if(GetCurLyrCombox()->GetCount() > 0)
		GetCurLyrCombox()->SelectItem(0);
	if(GetCurLyrCombox_Vector()->GetCount() > 0)
		GetCurLyrCombox_Vector()->SelectItem(0);
	if(GetMagicLayer()->GetCount() > 0)
	{
		GetMagicLayer()->SelectItem(0);
	}

}

void CUAVSoftView::OnUpdateSelectFeatureByPoint(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_MapCtrl.GetCurToolName() == "SelectbyPoint");
}

void CUAVSoftView::OnIncrementalImport()
{
	
}
void CUAVSoftView::OnUpdateIncrementalImport(CCmdUI* pCmdUI)
{
	Carto::CMapPtr pMap =m_MapCtrl.GetMap();
	if(!pMap)
	{
		pCmdUI->Enable(FALSE);
	}
	if(!pMap->GetEditor())
	{
		pMap->SetEditor(new Editor::CEditor(pMap.get()));

	}
	pCmdUI->Enable(pMap->GetEditor()->IsEditing());
}


//map与layout之间切换
LRESULT CUAVSoftView::OnChangeActiveTab(WPARAM wp,LPARAM lp)
{
	int iTabIndex=(int)wp;//激活哪个tab的索引
	if(iTabIndex== 0)
	{
		//m_MapCtrl.SetMapFramedStatus(FALSE);
	}
	else if(iTabIndex== 1)
	{
		//m_MapCtrl.SetMapFramedStatus(TRUE);
		//在此初始化layout
		if(!m_LayoutCtrl.Initialized())
		{
			m_LayoutCtrl.Initialize();
			OnDrawMapFrameElement();
			//load temp
			//CString strTempFile =GetAppPathName()+"\\china.TMP";
			//m_LayoutCtrl.LoadTemplate(m_MapCtrl.GetMap(),strTempFile.AllocSysString());
		}
	}
	return 0;
}



void CUAVSoftView::OnDrawMapFrameElement()
{

	Framework::ICommand* pCommand = NULL;
	m_LayoutCtrl.SetCurTool("DrawMapFrameElementCmd");

	pCommand=Framework::ICommand::FindCommand("DrawMapFrameElementCmd");
	if(pCommand)
	{
		pCommand->Initialize(dynamic_cast<Framework::IUIObject*>(&m_LayoutCtrl));
		pCommand->Click();
	}
	OnSelectFrameElement();
}
void CUAVSoftView::OnUpdateDrawMapFrameElement(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_LayoutCtrl.GetCurToolName() == "DrawMapFrameElementCmd");
	//pCmdUI->Enable(m_bLayout);
}
//编辑工具

afx_msg void CUAVSoftView::OnEditorStart()
{
	Carto::CMapPtr pMap =m_MapCtrl.GetMap();

	if(pMap)
	{
		if(!pMap->GetEditor())
		{
			pMap->SetEditor(new Editor::CEditor(pMap.get()));

		}
		pMap->GetEditor()->StartEdit();

		CShapefileWorkspace* pShapeWS = NULL;
		Carto::CLayerArray &layers =pMap->GetLayers();
		int num =layers.GetSize();
		Carto::ILayerPtr pLayer;
		Geodatabase::IFeatureClass *pFeatureClass =NULL;
		Geodatabase::IWorkspace *pWorkspace =NULL;

		
		//结束编辑
		for(int i=0;i<num;i++)
		{
			pLayer =layers.GetAt(i);
			if(pLayer->GetLayerType()!=Carto::FeatureLayer)
			{
				continue;
			}

			pFeatureClass =dynamic_cast<Geodatabase::IFeatureClass*>(pLayer->GetDataObject().get());
			if(!pFeatureClass)
			{
				continue;
			}

			pWorkspace =pFeatureClass->GetWorkspace();

			pShapeWS = dynamic_cast<CShapefileWorkspace* >(pWorkspace);

		}

		if(pShapeWS==NULL)
			return;

		//int flagSave = MessageBox("是否导出数据编辑增量信息？\n若导出，编辑将被保存到增量文件","提示",MB_YESNO);
		//if (flagSave == 6)
		//{
		//	

		//}
		//else
		//{
		//	pShapeWS->m_bEditIncremental = false;

		//}
		m_MapCtrl.UpdateControl(drawAll);
	}
}
afx_msg void CUAVSoftView::OnUpdateEditorStart(CCmdUI *pCmdUI)
{
	Carto::CMapPtr pMap =m_MapCtrl.GetMap();
	if(!pMap )
	{
		pCmdUI->Enable(FALSE);
	}

	if(!pMap->GetEditor())
	{
		pMap->SetEditor(new Editor::CEditor(pMap.get()));

	}
	if(GetCurLyrCombox_Vector()->GetCount()<1)
		pCmdUI->Enable(FALSE);
	else
		pCmdUI->Enable(!pMap->GetEditor()->IsEditing());
}
afx_msg void CUAVSoftView::OnEditorSketch()
{
	Framework::ITool* pTool = NULL;
	m_MapCtrl.SetCurTool("SketchTool");
	pTool=Framework::ITool::FindTool("SketchTool");
	if(pTool)
	{
		pTool->Initialize(dynamic_cast<Framework::IUIObject*>(&m_MapCtrl));
	}
}
afx_msg void CUAVSoftView::OnUpdateEditorSketch(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_MapCtrl.GetCurToolName() == "SketchTool");
	Carto::CMapPtr pMap =m_MapCtrl.GetMap();
	if(!pMap)
	{
		pCmdUI->Enable(FALSE);
	}
	if(!pMap->GetEditor())
	{
		pMap->SetEditor(new Editor::CEditor(pMap.get()));

	}
	pCmdUI->Enable(pMap->GetEditor()->IsEditing());
}
afx_msg void CUAVSoftView::OnEditerEdit()
{
	Framework::ITool* pTool = NULL;
	m_MapCtrl.SetCurTool("EditFeatureTool");
	pTool=Framework::ITool::FindTool("EditFeatureTool");
	if(pTool)
	{
		pTool->Initialize(dynamic_cast<Framework::IUIObject*>(&m_MapCtrl));
	}
}
afx_msg void CUAVSoftView::OnUpdateEditerEdit(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_MapCtrl.GetCurToolName() == "EditFeatureTool");
	Carto::CMapPtr pMap =m_MapCtrl.GetMap();
	if(!pMap)
	{
		pCmdUI->Enable(FALSE);
	}
	if(!pMap->GetEditor())
	{
		pMap->SetEditor(new Editor::CEditor(pMap.get()));

	}
	pCmdUI->Enable(pMap->GetEditor()->IsEditing());
}
afx_msg void CUAVSoftView::OnEditerRedo()
{
	Carto::CMapPtr pMap =m_MapCtrl.GetMap();

	if(pMap)
	{
		if(!pMap->GetEditor())
		{
			pMap->SetEditor(new Editor::CEditor(pMap.get()));

		}
		if(pMap->GetEditor()->CanRedo())
			pMap->GetEditor()->Redo();
	}
}
afx_msg void CUAVSoftView::OnUpdateEditerRedo(CCmdUI *pCmdUI)
{
	Carto::CMapPtr pMap =m_MapCtrl.GetMap();
	if(!pMap)
	{
		pCmdUI->Enable(FALSE);
	}
	if(!pMap->GetEditor())
	{
		pMap->SetEditor(new Editor::CEditor(pMap.get()));

	}
	pCmdUI->Enable(pMap->GetEditor()->CanRedo());
}
afx_msg void CUAVSoftView::OnEditerUndo()
{
	Carto::CMapPtr pMap =m_MapCtrl.GetMap();

	if(pMap)
	{
		if(!pMap->GetEditor())
		{
			pMap->SetEditor(new Editor::CEditor(pMap.get()));

		}
		if(pMap->GetEditor()->CanUndo())
			pMap->GetEditor()->Undo();
	}
}
afx_msg void CUAVSoftView::OnUpdateEditerUndo(CCmdUI *pCmdUI)
{
	Carto::CMapPtr pMap =m_MapCtrl.GetMap();
	if(!pMap)
	{
		pCmdUI->Enable(FALSE);
	}
	if(!pMap->GetEditor())
	{
		pMap->SetEditor(new Editor::CEditor(pMap.get()));

	}
	pCmdUI->Enable(pMap->GetEditor()->CanUndo());
}
afx_msg void CUAVSoftView::OnEditerEnd()
{
	Carto::CMapPtr pMap =m_MapCtrl.GetMap();

	if(pMap)
	{
		if(!pMap->GetEditor())
		{
			pMap->SetEditor(new Editor::CEditor(pMap.get()));

		}
		int flagSave = MessageBox("是否保存编辑！","提示",MB_YESNOCANCEL);
		if (flagSave == 6)
		{
			pMap->GetEditor()->StopEdit(true);
		}
		else if(flagSave == 7)
		{
			pMap->GetEditor()->StopEdit(false);
		}

	}
}
afx_msg void CUAVSoftView::OnUpdateEditerEnd(CCmdUI *pCmdUI)
{
	Carto::CMapPtr pMap =m_MapCtrl.GetMap();
	if(!pMap)
	{
		pCmdUI->Enable(FALSE);
	}
	if(!pMap->GetEditor())
	{
		pMap->SetEditor(new Editor::CEditor(pMap.get()));

	}
	pCmdUI->Enable(pMap->GetEditor()->IsEditing());
}

afx_msg void CUAVSoftView::OnEditerSave()
{
	Carto::CMapPtr pMap =m_MapCtrl.GetMap();

	if(pMap)
	{
		if(!pMap->GetEditor())
		{
			pMap->SetEditor(new Editor::CEditor(pMap.get()));

		}
		pMap->GetEditor()->StopEdit(true);
	}
}
afx_msg void CUAVSoftView::OnUpdateEditerSave(CCmdUI *pCmdUI)
{
	Carto::CMapPtr pMap =m_MapCtrl.GetMap();
	if(!pMap)
	{
		pCmdUI->Enable(FALSE);
	}
	if(!pMap->GetEditor())
	{
		pMap->SetEditor(new Editor::CEditor(pMap.get()));

	}
	pCmdUI->Enable(pMap->GetEditor()->IsEditing());
}

afx_msg void CUAVSoftView::OnEditerDel()
{
	Carto::CMapPtr pMap =m_MapCtrl.GetMap();

	if(pMap)
	{
		if(!pMap->GetEditor())
		{
			pMap->SetEditor(new Editor::CEditor(pMap.get()));

		}
		Editor::CEditorPtr pEditor = pMap->GetEditor();
		pEditor->DeleteFeature();
	}
}
afx_msg void CUAVSoftView::OnUpdateEditerDel(CCmdUI *pCmdUI)
{
	Carto::CMapPtr pMap =m_MapCtrl.GetMap();
	if(!pMap)
	{
		pCmdUI->Enable(FALSE);
	}
	if(!pMap->GetEditor())
	{
		pMap->SetEditor(new Editor::CEditor(pMap.get()));

	}
	pCmdUI->Enable(pMap->GetEditor()->IsEditing());
}

afx_msg void CUAVSoftView::OnEditerUnion()
{
	Carto::CMapPtr pMap =m_MapCtrl.GetMap();

	if(pMap)
	{
		if(!pMap->GetEditor())
		{
			pMap->SetEditor(new Editor::CEditor(pMap.get()));

		}
		Framework::ICommand* pCommand = NULL;
		//m_MapCtrl.SetCurTool("PolygonUnionCmd");
		pCommand=Framework::ICommand::FindCommand("PolygonUnionCmd");
		if(pCommand)
		{
			pCommand->Initialize(dynamic_cast<Framework::IUIObject*>(&m_MapCtrl));
			pCommand->Click();
		}
	}
}
afx_msg void CUAVSoftView::OnUpdateEditerUnion(CCmdUI *pCmdUI)
{
	Carto::CMapPtr pMap =m_MapCtrl.GetMap();
	if(!pMap)
	{
		pCmdUI->Enable(FALSE);
	}
	if(!pMap->GetEditor())
	{
		pMap->SetEditor(new Editor::CEditor(pMap.get()));

	}
	pCmdUI->Enable(pMap->GetEditor()->IsEditing());
}
afx_msg void CUAVSoftView::OnEditerAttribute()
{
	Carto::CMapPtr pMap =m_MapCtrl.GetMap();

	if(pMap)
	{
		if(!pMap->GetEditor())
		{
			pMap->SetEditor(new Editor::CEditor(pMap.get()));

		}
		Framework::ICommand* pCommand = NULL;
		pCommand=Framework::ICommand::FindCommand("FeatureAtrEditCmd");
		if(pCommand)
		{
			pCommand->Initialize(dynamic_cast<Framework::IUIObject*>(&m_MapCtrl));
			pCommand->Click();
		}
	}
}
afx_msg void CUAVSoftView::OnUpdateEditerAttribute(CCmdUI *pCmdUI)
{
	Carto::CMapPtr pMap =m_MapCtrl.GetMap();
	if(!pMap)
	{
		pCmdUI->Enable(FALSE);
	}
	if(!pMap->GetEditor())
	{
		pMap->SetEditor(new Editor::CEditor(pMap.get()));

	}
	pCmdUI->Enable(pMap->GetEditor()->IsEditing());
}
afx_msg void CUAVSoftView::OnSelectFeature()
{
	Framework::ITool* pTool = NULL;
	m_MapCtrl.SetCurTool("SelectbyPoint");
	pTool=Framework::ITool::FindTool("SelectbyPoint");
	if(pTool)
	{
		pTool->Initialize(dynamic_cast<Framework::IUIObject*>(&m_MapCtrl));
	}
}
afx_msg void CUAVSoftView::OnUpdateSelectFeature(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_MapCtrl.GetCurToolName() == "SelectbyPoint");
}

afx_msg void CUAVSoftView::OnFeatureInfo()
{
	Framework::ITool* pTool = NULL;
	m_MapCtrl.SetCurTool("FeatureInfoTool");
	pTool=Framework::ITool::FindTool("FeatureInfoTool");
	if(pTool)
	{
		pTool->Initialize(dynamic_cast<Framework::IUIObject*>(&m_MapCtrl));
	}
}
void CUAVSoftView::OnMagicStick()
{
	Framework::ITool* pTool = NULL;
	m_MapCtrl.SetCurTool("MagicStickTool");
	pTool=Framework::ITool::FindTool("MagicStickTool");

	Carto::ILayer* pLayer =(Carto::ILayer*)GetMagicLayer()->GetItemData(GetMagicLayer()->GetCurSel());
	CMainFrame* pMainFrm = (CMainFrame*)::AfxGetApp()->GetMainWnd();
	CBCGPRibbonEdit* pEdit = (CBCGPRibbonEdit*)pMainFrm->m_wndRibbonBar.FindByID(ID_MAGICSTICK_TOL);
	CString strValue =pEdit->GetEditText();
	int ntol =atoi(strValue);
	if(ntol<=0 || ntol>100)
	{
		ntol =20;
	}
	Control::CMagicStickTool::SetParam(ntol,pLayer);

	//设置目标图层和阈值
	if(pTool)
	{
		pTool->Initialize(dynamic_cast<Framework::IUIObject*>(&m_MapCtrl));
	}
}

void CUAVSoftView::OnUpdateMagicStick(CCmdUI* pCmdUI)
{
	std::string strtool =m_MapCtrl.GetCurToolName();
	if(strtool=="MagicStickTool")
	{
		pCmdUI->SetCheck(TRUE);
	}
	else
	{
		pCmdUI->SetCheck(FALSE);
	}
}
void CUAVSoftView::LayerDelEvent(Carto::ILayerPtr pLayer)
{
	//更新图层下拉框
	RefreshLayerCombo();
}

void CUAVSoftView::OnMagicStickLayer()
{
	Framework::ITool* pTool = NULL;

	pTool=Framework::ITool::FindTool("MagicStickTool");

	Carto::ILayer* pLayer =(Carto::ILayer*)GetMagicLayer()->GetItemData(GetMagicLayer()->GetCurSel());
	CMainFrame* pMainFrm = (CMainFrame*)::AfxGetApp()->GetMainWnd();
	CBCGPRibbonEdit* pEdit = (CBCGPRibbonEdit*)pMainFrm->m_wndRibbonBar.FindByID(ID_MAGICSTICK_TOL);
	CString strValue =pEdit->GetEditText();
	int ntol =atoi(strValue);
	if(ntol<=0 || ntol>100)
	{
		ntol =20;
	}
	//设置目标图层和阈值
	Control::CMagicStickTool::SetParam(ntol,pLayer);



}

void CUAVSoftView::OnMagicTol()
{
	Framework::ITool* pTool = NULL;

	pTool=Framework::ITool::FindTool("MagicStickTool");

	Carto::ILayer* pLayer =(Carto::ILayer*)GetMagicLayer()->GetItemData(GetMagicLayer()->GetCurSel());
	CMainFrame* pMainFrm = (CMainFrame*)::AfxGetApp()->GetMainWnd();
	CBCGPRibbonEdit* pEdit = (CBCGPRibbonEdit*)pMainFrm->m_wndRibbonBar.FindByID(ID_MAGICSTICK_TOL);
	CString strValue =pEdit->GetEditText();
	int ntol =atoi(strValue);
	if(ntol<=0 || ntol>100)
	{
		ntol =20;
	}
	//设置目标图层和阈值
	Control::CMagicStickTool::SetParam(ntol,pLayer);
}

CBCGPRibbonComboBox* CUAVSoftView::GetMagicLayer()
{
	CMainFrame* pMainFrm = (CMainFrame*)::AfxGetApp()->GetMainWnd();
	CBCGPRibbonComboBox* pCombox = (CBCGPRibbonComboBox*)pMainFrm->m_wndRibbonBar.FindByID(ID_MAGICSTICK_LAYER);
	return pCombox;
}

void CUAVSoftView::OnImgChangeDetect()
{
	Control::CImageProcessTool::ShowImgChangeDetectDlg();

	RefreshLayerCombo();

}
void CUAVSoftView::OnImgChangeRender()
{
	CMainFrame* pMainFrm = (CMainFrame*)::AfxGetApp()->GetMainWnd();
	Control::CImageProcessTool::ShowDistillWaterSheet(&m_MapCtrl, pMainFrm);
	//Framework::ITool* pTool = NULL;
	//m_MapCtrl.SetCurTool("DiTillTool");
	//pTool=Framework::ITool::FindTool("DiTillTool");
	////设置目标图层和阈值
	//if(pTool)
	//{
	//	pTool->Initialize(dynamic_cast<Framework::IUIObject*>(&m_MapCtrl));
	//}
}
void CUAVSoftView::OnWaterExtract()
{
	CMainFrame* pMainFrm = (CMainFrame*)::AfxGetApp()->GetMainWnd();
	Control::CImageProcessTool::ShowDistillWaterSheet(&m_MapCtrl, pMainFrm);
}

void CUAVSoftView::OnClassifyFuzzyKMean()
{
	Control::CImageProcessTool::ShowFuzzyKMeanDlg();
}

//删除上次魔术棒提取结果
void CUAVSoftView::OnDeleteLastMagic()
{
	Carto::CMapPtr pMap =m_MapCtrl.GetMap();

	if(!pMap)
	{
		return;
	}
	Carto::CGraphicLayerPtr pLayer =pMap->GetGraphicLayer();
	Element::IElementPtr pElement;
	int count =pLayer->GetElementCount();
	if(count<=0)
	{
		return;
	}
	long ldata;
	for(int i=count-1;i>=0;i--)
	{
		pElement =pLayer->GetElement(i);
		if(!pElement)
		{
			continue;
		}
		ldata =pElement->GetUserdata();
		if(ldata==1 ||ldata ==3 ||ldata==2)
		{
			pLayer->RemoveElement(pElement);
			//更新视图
			m_MapCtrl.UpdateControl(drawElement);
			break;
		}
	}


}

void CUAVSoftView::OnEdgeTrack()
{
	Framework::ITool* pTool = NULL;
	m_MapCtrl.SetCurTool("EdgeTrackTool");
	pTool=Framework::ITool::FindTool("EdgeTrackTool");
	if(pTool)
	{
		pTool->Initialize(dynamic_cast<Framework::IUIObject*>(&m_MapCtrl));
	}
}

void CUAVSoftView::OnChangeSetSymbol()
{
	Control::CImageProcessTool::ShowChangeSymbolDlg();
}

void CUAVSoftView::OnSendBlueToothFile()
{
	
}

CString GetExePath()
{
	char szFullPath[_MAX_PATH];
	char szDriver[_MAX_DRIVE];
	char szDir[_MAX_DIR];
	char szExePath[_MAX_DIR];

	GetModuleFileName(AfxGetApp()->m_hInstance, szFullPath, MAX_PATH);
	_splitpath(szFullPath, szDriver, szDir, NULL, NULL);
	_makepath(szExePath, szDriver, szDir, NULL, NULL);

	CString  exepath= szExePath;
	return exepath;
}

void CUAVSoftView::OnOpenHelp()
{
	//获得要启动的程序所在路径
	CString strCurrentPath = GetExePath();
	strCurrentPath +="help\\";
	TCHAR szOldPath[MAX_PATH] = {0};
	::GetCurrentDirectory(MAX_PATH, szOldPath);
	//kdk,设置当前文件夹路径，可以执行chm文件
	bool bsuc =::SetCurrentDirectory(strCurrentPath);

	CString strExeName ="help.doc";
	UINT flag =(UINT)ShellExecute(NULL,"open",strExeName,NULL,NULL,SW_NORMAL);
	if (flag <= 31)
	{
		switch (flag)
		{

		case ERROR_BAD_FORMAT:
			MessageBox("可执行文件已经损坏","提示");
			break;
		case ERROR_FILE_NOT_FOUND:
			MessageBox("没有找到可执行的文件","提示");
			break;
		case ERROR_PATH_NOT_FOUND:
			MessageBox("指定的执行文件路径没有找到","提示");
			break;
		default:
			break;
		}
	}
	::SetCurrentDirectory(szOldPath);
}

void CUAVSoftView::OnDelAll()
{
	Carto::CMapPtr pMap =m_MapCtrl.GetMap();

	if(!pMap)
	{
		return;
	}
	Carto::CGraphicLayerPtr pLayer =pMap->GetGraphicLayer();

	pLayer->UnselectAllElements();
	pLayer->RemoveAllElements();
	//更新视图
	m_MapCtrl.UpdateControl(drawAll);

}
