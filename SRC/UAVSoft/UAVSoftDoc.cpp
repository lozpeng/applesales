// UAVSoftDoc.cpp : implementation of the CUAVSoftDoc class
//

#include "stdafx.h"
#include "UAVSoft.h"

#include "UAVSoftDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CUAVSoftDoc

IMPLEMENT_DYNCREATE(CUAVSoftDoc, CDocument)

BEGIN_MESSAGE_MAP(CUAVSoftDoc, CDocument)
END_MESSAGE_MAP()


// CUAVSoftDoc construction/destruction

CUAVSoftDoc::CUAVSoftDoc()
{
	// TODO: add one-time construction code here

}

CUAVSoftDoc::~CUAVSoftDoc()
{
}

BOOL CUAVSoftDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	//注册文档
	CreateAss(Framework::CommonUIName::AppDocument);
	SetAutoDetroy(true);

	//新建一个地图
	AddNewMap();

	//设置为活动地图
	SetActiveMap(GetMap(0));

	return TRUE;
}




// CUAVSoftDoc serialization

void CUAVSoftDoc::Serialize(CArchive& ar)
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


// CUAVSoftDoc diagnostics

#ifdef _DEBUG
void CUAVSoftDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CUAVSoftDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CUAVSoftDoc commands
