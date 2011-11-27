// GeoscapeProDoc.cpp : implementation of the CGeoscapeProDoc class
//

#include "stdafx.h"
#include "GeoscapePro.h"

#include "GeoscapeProDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGeoscapeProDoc

IMPLEMENT_DYNCREATE(CGeoscapeProDoc, CDocument)

BEGIN_MESSAGE_MAP(CGeoscapeProDoc, CDocument)
END_MESSAGE_MAP()


// CGeoscapeProDoc construction/destruction

CGeoscapeProDoc::CGeoscapeProDoc()
{
	// TODO: add one-time construction code here

}

CGeoscapeProDoc::~CGeoscapeProDoc()
{
}

BOOL CGeoscapeProDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CGeoscapeProDoc serialization

void CGeoscapeProDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}


// CGeoscapeProDoc diagnostics

#ifdef _DEBUG
void CGeoscapeProDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGeoscapeProDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CGeoscapeProDoc commands
