// TDAppDoc.cpp : implementation of the CTDAppDoc class
//

#include "stdafx.h"
#include "TDApp.h"

#include "TDAppDoc.h"
//#include "CntrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTDAppDoc

IMPLEMENT_DYNCREATE(CTDAppDoc, CDocument)

BEGIN_MESSAGE_MAP(CTDAppDoc, CDocument)
	// Enable default OLE container implementation
	/*ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, COleDocument::OnUpdatePasteMenu)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE_LINK, COleDocument::OnUpdatePasteLinkMenu)
	ON_UPDATE_COMMAND_UI(ID_OLE_EDIT_CONVERT, COleDocument::OnUpdateObjectVerbMenu)
	ON_COMMAND(ID_OLE_EDIT_CONVERT, COleDocument::OnEditConvert)
	ON_UPDATE_COMMAND_UI(ID_OLE_EDIT_LINKS, COleDocument::OnUpdateEditLinksMenu)
	ON_COMMAND(ID_OLE_EDIT_LINKS, COleDocument::OnEditLinks)
	ON_UPDATE_COMMAND_UI_RANGE(ID_OLE_VERB_FIRST, ID_OLE_VERB_LAST, COleDocument::OnUpdateObjectVerbMenu)*/
END_MESSAGE_MAP()


// CTDAppDoc construction/destruction

CTDAppDoc::CTDAppDoc()
{

	// TODO: add one-time construction code here

}

CTDAppDoc::~CTDAppDoc()
{
}

BOOL CTDAppDoc::OnNewDocument()
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




// CTDAppDoc serialization

void CTDAppDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}

	// Calling the base class COleDocument enables serialization
	//  of the container document's COleClientItem objects.
	CDocument::Serialize(ar);
}


// CTDAppDoc diagnostics

#ifdef _DEBUG
void CTDAppDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTDAppDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CTDAppDoc commands
