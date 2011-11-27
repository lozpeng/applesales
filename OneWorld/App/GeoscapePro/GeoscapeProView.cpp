// GeoscapeProView.cpp : implementation of the CGeoscapeProView class
//

#include "stdafx.h"
#include "GeoscapePro.h"

#include "GeoscapeProDoc.h"
#include "GeoscapeProView.h"
#include <owNavi/FlyToManipulator.h>
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGeoscapeProView

IMPLEMENT_DYNCREATE(CGeoscapeProView, CView)

BEGIN_MESSAGE_MAP(CGeoscapeProView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_WM_CREATE()
END_MESSAGE_MAP()

// CGeoscapeProView construction/destruction

CGeoscapeProView::CGeoscapeProView()
{
	// TODO: add construction code here
	mOSG = NULL;
}

CGeoscapeProView::~CGeoscapeProView()
{
	if (mOSG)
	{
		delete mOSG;
		mOSG = NULL;
	}
}

BOOL CGeoscapeProView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CGeoscapeProView drawing

void CGeoscapeProView::OnDraw(CDC* /*pDC*/)
{
	CGeoscapeProDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// TODO: add draw code for native data here
}


// CGeoscapeProView printing

void CGeoscapeProView::OnFilePrintPreview()
{
	BCGPPrintPreview (this);
}

BOOL CGeoscapeProView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CGeoscapeProView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CGeoscapeProView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CGeoscapeProView::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CGeoscapeProView::OnContextMenu(CWnd* pWnd, CPoint point)
{
//	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}

// CGeoscapeProView diagnostics

#ifdef _DEBUG
void CGeoscapeProView::AssertValid() const
{
	CView::AssertValid();
}

void CGeoscapeProView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}


CGeoscapeProDoc* CGeoscapeProView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGeoscapeProDoc)));
	return (CGeoscapeProDoc*)m_pDocument;
}

#endif //_DEBUG

void CGeoscapeProView::OnInitialUpdate()
{
	CView::OnInitialUpdate();


	//
	std::string modelName = "startup.earth";

	// Init the osg class
	mOSG->InitOSG(modelName);
	CMainFrame* pMainFrm = (CMainFrame*)::AfxGetApp()->GetMainWnd();
	Framework::ITocCtrl* pTocCtrl = pMainFrm->GetTOC();
	pTocCtrl->RefreshFromOSG(mOSG);
	// Start the thread to do OSG Rendering
	mThreadHandle = (HANDLE)_beginthread(&cOSG::Render, 0, mOSG); 
}

int CGeoscapeProView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// Now that the window is created setup OSG
	mOSG = new cOSG(m_hWnd);

	return 0;
}

