// TDAppView.cpp : implementation of the CTDAppView class
//

#include "stdafx.h"
#include "TDApp.h"

#include "TDAppDoc.h"
#include "TDAppView.h"

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
#include "DlgDrawingExport.h"
#include <boost/function.hpp>
#include <boost/bind.hpp>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTDAppView

IMPLEMENT_DYNCREATE(CTDAppView, CView)

BEGIN_MESSAGE_MAP(CTDAppView, CView)
	ON_WM_DESTROY()
	//ON_WM_SETFOCUS()
	ON_WM_SIZE()
	ON_WM_CREATE()


	ON_COMMAND(ID_FILE_PRINT, OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_OPEN_Vector, &CTDAppView::OnOpenVector)
	ON_COMMAND(ID_OPEN_IMG, &CTDAppView::OnOpenImg)

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



	ON_COMMAND(ID_POINT_SELECTFEATURE, OnSelectFeatureByPoint)
	ON_UPDATE_COMMAND_UI(ID_POINT_SELECTFEATURE, OnUpdateSelectFeatureByPoint)

	ON_COMMAND(ID_CURRLAYER_COMBO, OnCurrLayerCombo)
	ON_COMMAND(ID_CURRLAYER_COMBO_VECTOR, OnCurrLayerCombo_Vector)
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
	
	ON_COMMAND(ID_MAGIC_STICK, OnMagicStick)

	ON_REGISTERED_MESSAGE(BCGM_CHANGE_ACTIVE_TAB,OnChangeActiveTab)


END_MESSAGE_MAP()

//得到程序启动的路径
CString  GetAppPathName()
{
	TCHAR	szProgPath[MAX_PATH*2];
	::GetModuleFileName(NULL, szProgPath, sizeof(szProgPath)/sizeof(TCHAR));    
	CString PathName =szProgPath;
	CString  FileName= PathName;
	int     SplashPos=PathName.ReverseFind('\\');
	if(SplashPos>=2 && SplashPos<=PathName.GetLength()-4)
		FileName=PathName.Left(SplashPos);
	return FileName;
}


// CTDAppView construction/destruction

CTDAppView::CTDAppView()
{
	boost::function<void (Carto::ILayerPtr)> fundl = boost::bind(&CTDAppView::LayerDelEvent,this, _1);

	m_ConnectionMapLayerDeleted = Carto::CMap::RegisterDeleteLayer(fundl);
}

CTDAppView::~CTDAppView()
{
    m_ConnectionMapLayerDeleted.disconnect();
}

BOOL CTDAppView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CTDAppView drawing

void CTDAppView::OnDraw(CDC* pDC)
{
	CTDAppDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);


	m_MapCtrl.OnPaint();
}



// CTDAppView printing

void CTDAppView::OnFilePrintPreview()
{
	BCGPPrintPreview (this);
}

BOOL CTDAppView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CTDAppView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CTDAppView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CTDAppView::OnDestroy()
{
	CView::OnDestroy();
}



void CTDAppView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	m_WndTab.SetWindowPos (NULL, -1, -1, cx + 1, cy + 3,
		SWP_SHOWWINDOW | SWP_NOZORDER);

}

void CTDAppView::OnFilePrint()
{
	CPrintInfo printInfo;
	ASSERT(printInfo.m_pPD != NULL); 
	if (S_OK == COleDocObjectItem::DoDefaultPrinting(this, &printInfo))
		return;

	CView::OnFilePrint();

}

int CTDAppView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	m_WndTab.Create (CBCGPTabWnd::STYLE_3D_VS2005, CRect(0,0,0,0), this, ID_TABCONTROL);


	m_MapCtrl.CreateControl(Framework::CommonUIName::AppMapControl, &m_WndTab, ID_MAPCTRL);
	m_WndTab.AddTab( &m_MapCtrl , "Map" );

	//m_LayoutCtrl.CreateControl(Framework::CommonUIName::AppLayoutControl, &m_WndTab,ID_LAYOUTCTRL);
	//m_wndButton.Create(_T("Test"),WS_CHILD|WS_VISIBLE,CRect(0,0,10,20),&m_WndTab,IDC_TEST);
	//m_WndTab.AddTab(&m_LayoutCtrl,_T("Layout"));


	CTDAppDoc* pDoc = GetDocument();
	pDoc->SetLinkMapCtrl(&m_MapCtrl);
	pDoc->SetLinkLayoutCtrl(&m_LayoutCtrl);

	m_WndTab.SetActiveTab(0);
	m_WndTab.SetFlatFrame ();
	m_WndTab.SetTabBorderSize (0);
	m_WndTab.AutoDestroyWindow (FALSE);
	return true;
}

// CTDAppView diagnostics

#ifdef _DEBUG
void CTDAppView::AssertValid() const
{
	CView::AssertValid();
}

void CTDAppView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTDAppDoc* CTDAppView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTDAppDoc)));
	return (CTDAppDoc*)m_pDocument;
}


#endif //_DEBUG

CBCGPRibbonComboBox* CTDAppView::GetCurLyrCombox()
{
	CMainFrame* pMainFrm = (CMainFrame*)::AfxGetApp()->GetMainWnd();
	CBCGPRibbonComboBox* pCombox = (CBCGPRibbonComboBox*)pMainFrm->m_wndRibbonBar.FindByID(ID_CURRLAYER_COMBO);
	return pCombox;
}
CBCGPRibbonComboBox* CTDAppView::GetCurLyrCombox_Vector()
{
	CMainFrame* pMainFrm = (CMainFrame*)::AfxGetApp()->GetMainWnd();
	CBCGPRibbonComboBox* pCombox = (CBCGPRibbonComboBox*)pMainFrm->m_wndRibbonBar.FindByID(ID_CURRLAYER_COMBO_VECTOR);
	return pCombox;
}
// CTDAppView message handlers



//打开矢量数据
void CTDAppView::OnOpenVector()
{
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

	//_crtBreakAlloc = 9878;




	// TODO: 在此添加命令处理程序代码
	CString fileName ="";

	CFileDialog dlg(true, "*.*", "",OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,"shapefile(*.shp)|*.shp|All file(*.*)|*.*|",this);
	if(dlg.DoModal()==IDOK) 
		fileName = dlg.GetPathName(); 
	else
		return;


	this->GetDocument()->LoadShpFile(fileName);
	m_MapCtrl.UpdateControl(drawAll);
	RefreshLayerCombo();
}

void CTDAppView::OnOpenImg()
{
	// TODO: 在此添加命令处理程序代码
	CString fileName("");
	CFileDialog dlg(true, "*.*", "",OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,"影像数据(*.tif;*.img;*.tiff;*.bmp)|*.tif;*.img;*.tiff;*.bmp|All Files(*.*)|*.*||",this);
	if(dlg.DoModal()==IDOK) 
		fileName = dlg.GetPathName(); 
	else
		return;
	//Control::CProgressBar *pbar =new Control::CProgressBar();
	this->GetDocument()->LoadImageFile(fileName);
	m_MapCtrl.UpdateControl(drawAll);
	RefreshLayerCombo();
}


void CTDAppView::OnMapPan()
{
	//Framework::ITool* pTool = NULL;
	//m_LayoutCtrl.SetCurTool("LayoutPanTool");

	//pTool=Framework::ITool::FindTool("LayoutPanTool");
	//if(pTool)
	//{
	//	pTool->Initialize(dynamic_cast<Framework::IUIObject*>(&m_LayoutCtrl));
	//}
	Framework::ITool* pTool = NULL;
	m_MapCtrl.SetCurTool("MapPan");

	pTool=Framework::ITool::FindTool("MapPan");
	if(pTool)
	{
		pTool->Initialize(dynamic_cast<Framework::IUIObject*>(&m_MapCtrl));
	}
}

void CTDAppView::OnUpdateMapPan(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_MapCtrl.GetCurToolName() == "MapPan");

}

void CTDAppView::OnMapZoomin()
{
	Framework::ITool* pTool = NULL;
	m_MapCtrl.SetCurTool("MapZoomin");

	pTool=Framework::ITool::FindTool("MapZoomin");
	if(pTool)
	{
		pTool->Initialize(dynamic_cast<Framework::IUIObject*>(&m_MapCtrl));
	}
}

void CTDAppView::OnUpdateMapZoomin(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_MapCtrl.GetCurToolName() == "MapZoomin");
}

void CTDAppView::OnMapZoomout()
{
	Framework::ITool* pTool = NULL;
	m_MapCtrl.SetCurTool("MapZoomout");

	pTool=Framework::ITool::FindTool("MapZoomout");
	if(pTool)
	{
		pTool->Initialize(dynamic_cast<Framework::IUIObject*>(&m_MapCtrl));
	}
}

void CTDAppView::OnUpdateMapZoomout(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_MapCtrl.GetCurToolName() == "MapZoomout");
}

void CTDAppView::OnMapPreExtent()
{
	Carto::CMapPtr pMap =m_MapCtrl.GetMap();
	if(!pMap)
	{
		return;
	}
	pMap->GetDisplay()->GetDisplayTransformation().SetPreExtent();
	m_MapCtrl.UpdateControl(drawAll);
}

void CTDAppView::OnUpdateMapPreExtent(CCmdUI* pCmdUI)
{
	Carto::CMapPtr pMap =m_MapCtrl.GetMap();
	if(!pMap)
	{
		pCmdUI->Enable(FALSE);
	}
	pCmdUI->Enable(pMap->GetDisplay()->GetDisplayTransformation().HasPreExtent());
}

void CTDAppView::OnMapNextExtent()
{
	Carto::CMapPtr pMap =m_MapCtrl.GetMap();
	if(!pMap)
	{
		return;
	}
	pMap->GetDisplay()->GetDisplayTransformation().SetNextExtent();
	m_MapCtrl.UpdateControl(drawAll);
}

void CTDAppView::OnUpdateMapNextExtent(CCmdUI* pCmdUI)
{
	Carto::CMapPtr pMap =m_MapCtrl.GetMap();
	if(!pMap)
	{
		pCmdUI->Enable(FALSE);
	}
	pCmdUI->Enable(pMap->GetDisplay()->GetDisplayTransformation().HasNextExtent());
}

//全图显示
void CTDAppView::OnMapFullView()
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




void CTDAppView::OnDrawRect()
{
	Framework::ITool* pTool = NULL;
	m_MapCtrl.SetCurTool("DrawRectElementTool");

	pTool=Framework::ITool::FindTool("DrawRectElementTool");
	if(pTool)
	{
		pTool->Initialize(dynamic_cast<Framework::IUIObject*>(&m_MapCtrl));
	}
}

void CTDAppView::OnUpdateDrawRect(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_MapCtrl.GetCurToolName() == "DrawRectElementTool");

}

void CTDAppView::OnDrawSelect()
{
	Framework::ITool* pTool = NULL;
	m_MapCtrl.SetCurTool("SelectElementTool");

	pTool=Framework::ITool::FindTool("SelectElementTool");
	if(pTool)
	{
		pTool->Initialize(dynamic_cast<Framework::IUIObject*>(&m_MapCtrl));
	}
}

void CTDAppView::OnUpdateDrawSelect(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_MapCtrl.GetCurToolName() == "SelectElementTool");

}

afx_msg void CTDAppView::OnDrawMarker()
{
	Framework::ITool* pTool = NULL;
	m_MapCtrl.SetCurTool("DrawSimpleMarkerElementTool");

	pTool=Framework::ITool::FindTool("DrawSimpleMarkerElementTool");
	if(pTool)
	{
		pTool->Initialize(dynamic_cast<Framework::IUIObject*>(&m_MapCtrl));
	}
}
afx_msg void CTDAppView::OnUpdateDrawMarker(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_MapCtrl.GetCurToolName() == "DrawSimpleMarkerElementTool");
}
afx_msg void CTDAppView::OnDrawCircle()
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
afx_msg void CTDAppView::OnUpdateDrawCircle(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_MapCtrl.GetCurToolName() == "DrawCircleElementTool");
}
afx_msg void CTDAppView::OnDrawPolygon()
{
	Framework::ITool* pTool = NULL;
	m_MapCtrl.SetCurTool("DrawPolygonElementTool");

	pTool=Framework::ITool::FindTool("DrawPolygonElementTool");
	if(pTool)
	{
		pTool->Initialize(dynamic_cast<Framework::IUIObject*>(&m_MapCtrl));
	}
}
afx_msg void CTDAppView::OnUpdateDrawPolygon(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_MapCtrl.GetCurToolName() == "DrawPolygonElementTool");
}
afx_msg void CTDAppView::OnDrawPolyline()
{
	Framework::ITool* pTool = NULL;
	m_MapCtrl.SetCurTool("DrawPolylineElementTool");

	pTool=Framework::ITool::FindTool("DrawPolylineElementTool");
	if(pTool)
	{
		pTool->Initialize(dynamic_cast<Framework::IUIObject*>(&m_MapCtrl));
	}
}
afx_msg void CTDAppView::OnUpdateDrawPolyline(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_MapCtrl.GetCurToolName() == "DrawPolylineElementTool");
}
afx_msg void CTDAppView::OnDrawCurve()
{
	Framework::ITool* pTool = NULL;
	m_MapCtrl.SetCurTool("DrawBezierCurveElementTool");

	pTool=Framework::ITool::FindTool("DrawBezierCurveElementTool");
	if(pTool)
	{
		pTool->Initialize(dynamic_cast<Framework::IUIObject*>(&m_MapCtrl));
	}
}
afx_msg void CTDAppView::OnUpdateDrawCurve(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_MapCtrl.GetCurToolName() == "DrawBezierCurveElementTool");
}
afx_msg void CTDAppView::OnDrawText()
{
	Framework::ITool* pTool = NULL;
	m_MapCtrl.SetCurTool("DrawTextElementTool");

	pTool=Framework::ITool::FindTool("DrawTextElementTool");
	if(pTool)
	{
		pTool->Initialize(dynamic_cast<Framework::IUIObject*>(&m_MapCtrl));
	}
}
afx_msg void CTDAppView::OnUpdateDrawtext(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_MapCtrl.GetCurToolName() == "DrawTextElementTool");
}


afx_msg void CTDAppView::OnEditElement()
{
	Framework::ITool* pTool = NULL;
	m_MapCtrl.SetCurTool("EditElementVertixTool");

	pTool=Framework::ITool::FindTool("EditElementVertixTool");
	if(pTool)
	{
		pTool->Initialize(dynamic_cast<Framework::IUIObject*>(&m_MapCtrl));
	}
}
afx_msg void CTDAppView::OnUpdateEditElement(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_MapCtrl.GetCurToolName() == "EditElementVertixTool");
}

afx_msg void CTDAppView::OnDrawEllipse()
{
	Framework::ITool* pTool = NULL;
	m_MapCtrl.SetCurTool("DrawEllipseElementTool");

	pTool=Framework::ITool::FindTool("DrawEllipseElementTool");
	if(pTool)
	{
		pTool->Initialize(dynamic_cast<Framework::IUIObject*>(&m_MapCtrl));
	}
}
afx_msg void CTDAppView::OnUpdateDrawEllipse(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_MapCtrl.GetCurToolName() == "DrawEllipseElementTool");
}
afx_msg void CTDAppView::OnDrawCalloutText()
{
	Framework::ITool* pTool = NULL;
	m_MapCtrl.SetCurTool("DrawCalloutTextElementTool");

	pTool=Framework::ITool::FindTool("DrawCalloutTextElementTool");
	if(pTool)
	{
		pTool->Initialize(dynamic_cast<Framework::IUIObject*>(&m_MapCtrl));
	}
}
afx_msg void CTDAppView::OnUpdateDrawCalloutText(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_MapCtrl.GetCurToolName() == "DrawCalloutTextElementTool");
}


afx_msg void CTDAppView::OnDrawFreeHandline()
{
	Framework::ITool* pTool = NULL;
	m_MapCtrl.SetCurTool("DrawFreehandLineElement");

	pTool=Framework::ITool::FindTool("DrawFreehandLineElement");
	if(pTool)
	{
		pTool->Initialize(dynamic_cast<Framework::IUIObject*>(&m_MapCtrl));
	}
}
afx_msg void CTDAppView::OnUpdateDrawFreeHandline(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_MapCtrl.GetCurToolName() == "DrawFreehandLineElement");
}
afx_msg void CTDAppView::OnDrawSaveAs()
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
		ipGraphicLayer->SaveElementAsShp(fileName,!Dlg.m_bExpoertAll,Dlg.m_DrawingType);
		if (Dlg.m_CheckAddMap)
		{
			this->GetDocument()->LoadShpFile(fileName);
			m_MapCtrl.UpdateControl(drawAll);
			RefreshLayerCombo();
		}
	}


}
afx_msg void CTDAppView::OnUpdateDrawSaveAs(CCmdUI* pCmdUI)
{

}


void CTDAppView::OnSelectFeatureByPoint()
{
	Framework::ITool* pTool = NULL;
	m_MapCtrl.SetCurTool("SelectbyPoint");

	pTool=Framework::ITool::FindTool("SelectbyPoint");
	if(pTool)
	{
		pTool->Initialize(dynamic_cast<Framework::IUIObject*>(&m_MapCtrl));
	}
}
Carto::ILayerPtr CTDAppView::GetComboLayer()
{
	int nSize = m_MapCtrl.GetMap()->GetLayers().GetSize();
	int nSel = GetCurLyrCombox()->GetCurSel();
	if (nSel >=0 && nSel<nSize)
	{
		return FindLayerbyPointer((Carto::ILayer*)GetCurLyrCombox()->GetItemData(nSel));
	}
	return NULL;
}
Carto::ILayerPtr CTDAppView::GetComboLayer_Vector()
{
	int nSize = m_MapCtrl.GetMap()->GetLayers().GetSize();
	int nSel = GetCurLyrCombox_Vector()->GetCurSel();
	if (nSel >=0 && nSel<nSize)
	{
		return FindLayerbyPointer((Carto::ILayer*)GetCurLyrCombox()->GetItemData(nSel));
	}
	return NULL;
}
void CTDAppView::OnCurrLayerCombo()
{

}
void CTDAppView::OnCurrLayerCombo_Vector()
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
void CTDAppView::OnBrightRestore()
{
}
void CTDAppView::OnContrastRestore()
{
}
void CTDAppView::OnTransparentRestore()
{
}
void CTDAppView::OnBrightSlider()
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
void CTDAppView::OnTransparentSlider()
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
void CTDAppView::OnContrastSlider()
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
void CTDAppView::OnUpdateBrightRestore(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(IsLayerComboNull());
}
void CTDAppView::OnUpdateContrastRestore(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(IsLayerComboNull());
}
void CTDAppView::OnUpdateTransparentRestore(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(IsLayerComboNull());
}
void CTDAppView::OnUpdateBrightSlider(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(IsLayerComboNull());
}
void CTDAppView::OnUpdateContrastSlider(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(IsLayerComboNull());
}
void CTDAppView::OnUpdateTransparentSlider(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(IsLayerComboNull());
}
void CTDAppView::OnSwipe()
{
	Framework::ICommand* pCmd = NULL;
	m_MapCtrl.SetCurTool("SwipeEnhance");

	pCmd= Framework::ICommand::FindCommand("SwipeEnhance");
	if(pCmd)
	{
		pCmd->Click();
	}
}
void CTDAppView::OnUpdateSwipe(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(IsLayerComboNull());
}
void CTDAppView::OnFlick()
{
	Framework::ICommand* pCmd = NULL;
	m_MapCtrl.SetCurTool("Flick");

	pCmd= Framework::ICommand::FindCommand("Flick");
	if(pCmd)
	{
		pCmd->Click();
	}
}
void CTDAppView::OnUpdateFlick(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(IsLayerComboNull());
}
void CTDAppView::BrightContrast(int nBright,int nContrast)
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
bool CTDAppView::IsLayerComboNull()
{
	int nSize = m_MapCtrl.GetMap()->GetLayers().GetSize();
	int nSel = GetCurLyrCombox()->GetCurSel();
	if (nSel>=0 && nSel<nSize)
	{
	    return true;	
	}
	return false;
}

//通过指针查找图层的智能指针
Carto::ILayerPtr CTDAppView::FindLayerbyPointer(Carto::ILayer* pLayer)
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
void CTDAppView::RefreshLayerCombo()
{
	int nSize = m_MapCtrl.GetMap()->GetLayers().GetSize();
	GetCurLyrCombox()->RemoveAllItems();
	GetCurLyrCombox_Vector()->RemoveAllItems();
	for (int i=0; i<nSize; ++i)
	{
		Carto::ILayerPtr pLayer = m_MapCtrl.GetMap()->GetLayers().GetAt(i);
		std::string strName = pLayer->GetName();
		//判断图层类型
		if(pLayer->GetLayerType()==Carto::RasterLayer)
		{
           GetCurLyrCombox()->AddItem(strName.c_str(),(DWORD_PTR)pLayer.get());
		   
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

}

void CTDAppView::OnUpdateSelectFeatureByPoint(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_MapCtrl.GetCurToolName() == "SelectbyPoint");
}


//map与layout之间切换
LRESULT CTDAppView::OnChangeActiveTab(WPARAM wp,LPARAM lp)
{
	int iTabIndex=(int)wp;//激活哪个tab的索引
	if(iTabIndex== 1)
	{
		//在此初始化layout
		if(!m_LayoutCtrl.Initialized())
		{
			m_LayoutCtrl.Initialize();
			OnDrawMapFrameElement();
			//load temp
			CString strTempFile =GetAppPathName()+"\\china.TMP";
			//m_LayoutCtrl.LoadTemplate(m_MapCtrl.GetMap(),strTempFile.AllocSysString());
		}
	}
	return 0;
}
void CTDAppView::OnSelectFrameElement()
{
	Framework::ITool* pTool = NULL;
	m_LayoutCtrl.SetCurTool("SelectFrameElementsTool");

	pTool=Framework::ITool::FindTool("SelectFrameElementsTool");
	if(pTool)
	{
		pTool->Initialize(dynamic_cast<Framework::IUIObject*>(&m_LayoutCtrl));
	}
}
void CTDAppView::OnUpdateSelectFrameElement(CCmdUI* pCmdUI)
{

	pCmdUI->SetCheck(m_LayoutCtrl.GetCurToolName() == "SelectFrameElementsTool");
	//pCmdUI->Enable(m_bLayout);
}


void CTDAppView::OnDrawMapFrameElement()
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
void CTDAppView::OnUpdateDrawMapFrameElement(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_LayoutCtrl.GetCurToolName() == "DrawMapFrameElementCmd");
	//pCmdUI->Enable(m_bLayout);
}
//编辑工具
afx_msg void CTDAppView::OnEditorStart()
{
	Carto::CMapPtr pMap =m_MapCtrl.GetMap();

	if(pMap)
	{
		if(!pMap->GetEditor())
		{
			pMap->SetEditor(new Editor::CEditor(pMap.get()));

		}
		pMap->GetEditor()->StartEdit();
	}
}
afx_msg void CTDAppView::OnUpdateEditorStart(CCmdUI *pCmdUI)
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
	pCmdUI->Enable(!pMap->GetEditor()->IsEditing());
}
afx_msg void CTDAppView::OnEditorSketch()
{
	Framework::ITool* pTool = NULL;
	m_MapCtrl.SetCurTool("SketchTool");
}
afx_msg void CTDAppView::OnUpdateEditorSketch(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_LayoutCtrl.GetCurToolName() == "SketchTool");
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
afx_msg void CTDAppView::OnEditerEdit()
{
	Framework::ITool* pTool = NULL;
	m_MapCtrl.SetCurTool("EditFeatureTool");
	pTool=Framework::ITool::FindTool("EditFeatureTool");
	if(pTool)
	{
		pTool->Initialize(dynamic_cast<Framework::IUIObject*>(&m_MapCtrl));
	}
}
afx_msg void CTDAppView::OnUpdateEditerEdit(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_LayoutCtrl.GetCurToolName() == "EditFeatureTool");
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
afx_msg void CTDAppView::OnEditerRedo()
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
afx_msg void CTDAppView::OnUpdateEditerRedo(CCmdUI *pCmdUI)
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
afx_msg void CTDAppView::OnEditerUndo()
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
afx_msg void CTDAppView::OnUpdateEditerUndo(CCmdUI *pCmdUI)
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
afx_msg void CTDAppView::OnEditerEnd()
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
afx_msg void CTDAppView::OnUpdateEditerEnd(CCmdUI *pCmdUI)
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

afx_msg void CTDAppView::OnEditerSave()
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
afx_msg void CTDAppView::OnUpdateEditerSave(CCmdUI *pCmdUI)
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

afx_msg void CTDAppView::OnEditerDel()
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
afx_msg void CTDAppView::OnUpdateEditerDel(CCmdUI *pCmdUI)
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

afx_msg void CTDAppView::OnEditerUnion()
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
afx_msg void CTDAppView::OnUpdateEditerUnion(CCmdUI *pCmdUI)
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
afx_msg void CTDAppView::OnEditerAttribute()
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
afx_msg void CTDAppView::OnUpdateEditerAttribute(CCmdUI *pCmdUI)
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

afx_msg void CTDAppView::OnFeatureInfo()
{
	Framework::ITool* pTool = NULL;
	m_MapCtrl.SetCurTool("FeatureInfoTool");
	pTool=Framework::ITool::FindTool("FeatureInfoTool");
	if(pTool)
	{
		pTool->Initialize(dynamic_cast<Framework::IUIObject*>(&m_MapCtrl));
	}
}
void CTDAppView::OnMagicStick()
{
	Framework::ITool* pTool = NULL;
	m_MapCtrl.SetCurTool("MagicStickTool");
	pTool=Framework::ITool::FindTool("MagicStickTool");
	if(pTool)
	{
		pTool->Initialize(dynamic_cast<Framework::IUIObject*>(&m_MapCtrl));
	}
}

void CTDAppView::LayerDelEvent(Carto::ILayerPtr pLayer)
{
	//更新图层下拉框
	RefreshLayerCombo();
}