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
