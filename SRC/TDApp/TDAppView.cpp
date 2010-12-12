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

	//浏览工具
	ON_COMMAND(ID_MAP_PAN, OnMapPan)
	ON_UPDATE_COMMAND_UI(ID_MAP_PAN, OnUpdateMapPan)

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



//打开矢量数据
void CTDAppView::OnOpenVector()
{
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

	//_crtBreakAlloc = 9878;



	// TODO: 在此添加命令处理程序代码
	CString fileName ="D:\\数据\\平台测试数据\\t119.shp";

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
	// TODO: 在此添加命令处理程序代码
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