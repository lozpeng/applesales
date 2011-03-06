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
#include "ProgressBar.h"
#include "MainFrm.h"

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

	//调整
	ON_COMMAND(ID_BRIGHT_RESTORE, OnBrightRestore)
	ON_COMMAND(ID_BRIGHT_SLIDER, OnBrightSlider)
	ON_COMMAND(ID_CONTRAST_RESTORE, OnContrastRestore)
	ON_COMMAND(ID_CONTRAST_SLIDER, OnContrastSlider)
	ON_COMMAND(ID_TRANSPARENT_RESTORE, OnTransparentRestore)
	ON_COMMAND(ID_TRANSPARENT_SLIDER, OnTransparentSlider)

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

	ON_COMMAND(ID_EDITOR, OnEditElement)
	ON_UPDATE_COMMAND_UI(ID_EDITOR, OnUpdateEditElement)
	ON_COMMAND(ID_Ellipse, OnDrawEllipse)
	ON_UPDATE_COMMAND_UI(ID_Ellipse, OnUpdateDrawEllipse)
	ON_COMMAND(ID_CalloutText, OnDrawCalloutText)
	ON_UPDATE_COMMAND_UI(ID_CalloutText, OnUpdateDrawCalloutText)
	ON_COMMAND(ID_DRAW_HANDLINE, OnDrawFreeHandline)
	ON_UPDATE_COMMAND_UI(ID_DRAW_HANDLINE, OnUpdateDrawFreeHandline)
	
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
	

}

CTDAppView::~CTDAppView()
{
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

	m_LayoutCtrl.CreateControl(Framework::CommonUIName::AppLayoutControl, &m_WndTab,ID_LAYOUTCTRL);
	//m_wndButton.Create(_T("Test"),WS_CHILD|WS_VISIBLE,CRect(0,0,10,20),&m_WndTab,IDC_TEST);
	m_WndTab.AddTab(&m_LayoutCtrl,_T("Layout"));

	
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
	CFileDialog dlg(true, "*.*", "",OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,"ImageFile(*.jpg)|*.jpg|All file(*.*)|*.*|",this);
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

void CTDAppView::OnCurrLayerCombo()
{
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
}
void CTDAppView::OnContrastSlider()
{
}
void CTDAppView::OnTransparentSlider()
{
}
void CTDAppView::RefreshLayerCombo()
{
	int nSize = m_MapCtrl.GetMap()->GetLayers().GetSize();
	GetCurLyrCombox()->RemoveAllItems();
	for (int i=0; i<nSize; ++i)
	{
		Carto::ILayerPtr pLayer = m_MapCtrl.GetMap()->GetLayers().GetAt(i);
		std::string strName = pLayer->GetName();
		GetCurLyrCombox()->AddItem(strName.c_str());
	}
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