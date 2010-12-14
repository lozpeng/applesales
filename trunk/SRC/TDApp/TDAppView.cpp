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

	//�������
	ON_COMMAND(ID_MAP_PAN, OnMapPan)
	ON_UPDATE_COMMAND_UI(ID_MAP_PAN, OnUpdateMapPan)
	ON_COMMAND(ID_MAP_ZOOM_IN, OnMapZoomin)
	ON_UPDATE_COMMAND_UI(ID_MAP_ZOOM_IN, OnUpdateMapZoomin)
	ON_COMMAND(ID_ZOOM_OUT, OnMapZoomout)
	ON_UPDATE_COMMAND_UI(ID_ZOOM_OUT, OnUpdateMapZoomout)

	//��湤��

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

END_MESSAGE_MAP()

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
	m_WndTab.Create (CBCGPTabWnd::STYLE_3D_VS2005, CRect(0,0,0,0), this, 1);


	m_MapCtrl.CreateControl(Framework::CommonUIName::AppMapControl, &m_WndTab, ID_MAPCTRL);
	//ipMap = Carto::CMapPtr(new Carto::CMap());
	//m_MapCtrl.SetMap(ipMap);
	m_WndTab.AddTab( &m_MapCtrl , "Map" );

	m_wndButton.Create(_T("Test"),WS_CHILD|WS_VISIBLE,CRect(0,0,10,20),&m_WndTab,IDC_TEST);
	m_WndTab.AddTab(&m_wndButton,_T("Layout"));

	
	CTDAppDoc* pDoc = GetDocument();
	pDoc->SetLinkMapCtrl(&m_MapCtrl);

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


// CTDAppView message handlers



//��ʸ������
void CTDAppView::OnOpenVector()
{
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

	//_crtBreakAlloc = 9878;



	// TODO: �ڴ�����������������
	CString fileName ="";

	CFileDialog dlg(true, "*.*", "",OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,"shapefile(*.shp)|*.shp|All file(*.*)|*.*|",this);
	if(dlg.DoModal()==IDOK) 
		fileName = dlg.GetPathName(); 
	else
		return;

	Geodatabase::IWorkspace* ipWorkspace = CShapefileWorkspaceFactory::GetInstance()->OpenFromFile(fileName);
	Geodatabase::IFeatureClassPtr ipFeatureCls = ipWorkspace->OpenFeatureClass(fileName);

	//Carto::CMapPtr ipMap = Carto::CMapPtr(new Carto::CMap());
	//m_MapCtrl.SetMap(ipMap);

	Carto::ILayerPtr ipLayer = Carto::ILayerPtr(new Carto::CFeatureLayer());
	ipLayer = Carto::ILayer::CreateLayer(ipFeatureCls);
	this->GetDocument()->GetActiveMap()->AddLayer(ipLayer);
	m_MapCtrl.UpdateControl(drawAll);
}

void CTDAppView::OnOpenImg()
{
	// TODO: �ڴ�����������������
	CString fileName("");
	CFileDialog dlg(true, "*.*", "",OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,"ImageFile(*.jpg)|*.jpg|All file(*.*)|*.*|",this);
	if(dlg.DoModal()==IDOK) 
		fileName = dlg.GetPathName(); 
	else
		return;
	Geodatabase::IWorkspace* pWorkspace = CRasterWSFactory::GetInstance()->OpenFromFile(fileName);
	Geodatabase::IRasterDatasetPtr pRasterDataset = pWorkspace->OpenRasterDataset(fileName);

	Carto::ILayerPtr pLayer = Carto::ILayerPtr(new Carto::CRasterLayer());
	pLayer = Carto::ILayer::CreateLayer(pRasterDataset);
	this->GetDocument()->GetActiveMap()->AddLayer(pLayer);
	m_MapCtrl.UpdateControl(drawAll);
}


void CTDAppView::OnMapPan()
{
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
	pCmdUI->SetCheck(m_MapCtrl.GetCurToolname() == "MapPan");

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
    pCmdUI->SetCheck(m_MapCtrl.GetCurToolname() == "MapZoomin");
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
    pCmdUI->SetCheck(m_MapCtrl.GetCurToolname() == "MapZoomout");
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
	pCmdUI->SetCheck(m_MapCtrl.GetCurToolname() == "DrawRectElementTool");

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
	pCmdUI->SetCheck(m_MapCtrl.GetCurToolname() == "SelectElementTool");

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
	pCmdUI->SetCheck(m_MapCtrl.GetCurToolname() == "DrawSimpleMarkerElementTool");
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
}
afx_msg void CTDAppView::OnUpdateDrawCircle(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_MapCtrl.GetCurToolname() == "DrawCircleElementTool");
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
	pCmdUI->SetCheck(m_MapCtrl.GetCurToolname() == "DrawPolygonElementTool");
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
	pCmdUI->SetCheck(m_MapCtrl.GetCurToolname() == "DrawPolylineElementTool");
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
	pCmdUI->SetCheck(m_MapCtrl.GetCurToolname() == "DrawBezierCurveElementTool");
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
	pCmdUI->SetCheck(m_MapCtrl.GetCurToolname() == "DrawTextElementTool");
}