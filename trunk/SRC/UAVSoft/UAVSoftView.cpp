// UAVSoftView.cpp : implementation of the CUAVSoftView class
//

#include "stdafx.h"
#include "UAVSoft.h"

#include "UAVSoftDoc.h"
#include "UAVSoftView.h"

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
END_MESSAGE_MAP()

// CUAVSoftView construction/destruction

CUAVSoftView::CUAVSoftView()
{
	// TODO: add construction code here

}

CUAVSoftView::~CUAVSoftView()
{
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

	//m_LayoutCtrl.CreateControl(Framework::CommonUIName::AppLayoutControl, &m_WndTab,ID_LAYOUTCTRL);
	//m_wndButton.Create(_T("Test"),WS_CHILD|WS_VISIBLE,CRect(0,0,10,20),&m_WndTab,IDC_TEST);
	//m_WndTab.AddTab(&m_LayoutCtrl,_T("Layout"));


	CUAVSoftDoc* pDoc = GetDocument();
	pDoc->SetLinkMapCtrl(&m_MapCtrl);

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
