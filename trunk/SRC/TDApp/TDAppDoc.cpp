// TDAppDoc.cpp : implementation of the CTDAppDoc class
//

#include "stdafx.h"
#include "TDApp.h"

#include "TDAppDoc.h"
#include "RelativePath.h"
#include "IMapCtrl.h"
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

	ON_COMMAND(ID_NEWMAPCLASS, OnNewProject)
	ON_COMMAND(ID_OPENMAPCLASS, OnOpenProject)
	ON_COMMAND(ID_SAVEMAPCLASS, OnSaveProject)

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

	//ע���ĵ�
	CreateAss(Framework::CommonUIName::AppDocument);
	SetAutoDetroy(true);

	//�½�һ����ͼ
	AddNewMap();

	//����Ϊ���ͼ
	SetActiveMap(GetMap(0));

	return TRUE;
}




// CTDAppDoc serialization

void CTDAppDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		SYSTEM::CBinArchive bin;
		bin.SetWriteState();

		if(m_pActiveMap)
		{
			m_pActiveMap->serialization(bin);
		}

		ar << bin.GetSize();

		ar.Write( bin.GetData() , bin.GetSize() );	
	}
	else
	{
		unsigned long Size;
		ar >> Size;

		BYTE * pStart = new BYTE[Size];

		ar.Read( pStart , Size );

		SYSTEM::CBinArchive bin( pStart , Size );

		bin.SetReadState();

		//�½�һ����ͼ
		AddNewMap();

		//����Ϊ���ͼ
		SetActiveMap(GetMap(0));

        m_pActiveMap->serialization(bin);

		if(m_linkMapCtrl)
		{
			//������ʾ
			DIS_BOUND rect;
			rect.left = rect.top = 0;
			rect.right = m_linkMapCtrl->GetSizeX();
			rect.bottom = m_linkMapCtrl->GetSizeY();	
			m_pActiveMap->SetViewBound(rect);
		}
		

		delete[] pStart;
	}

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


void CTDAppDoc::OnNewProject()
{
	int returnVal = MessageBox(NULL,"�Ƿ񱣴浱ǰ���̣�", "��ʾ", MB_YESNOCANCEL);
	if( returnVal == IDOK)
	{
		OnSaveProject();
	}
	else  if(returnVal == IDCANCEL)
	{
		return;
	}
	ClearProject();
	static CString csFilter = "�����ļ�(*.proj)|*.proj||";
	CFileDialog dlg(FALSE, "proj", "", OFN_HIDEREADONLY, csFilter);
	if( IDOK == dlg.DoModal() )
	{
		m_prjPath = dlg.GetPathName();
		
	}
	//�½�һ����ͼ
	AddNewMap();

	//����Ϊ���ͼ
	SetActiveMap(GetMap(0));
	OnSaveProject();
	//ˢ����ͼ
	m_pLinkMapTree->RefreshFromDoc();
	m_linkMapCtrl->UpdateControl(drawAll);
	
}

void CTDAppDoc::OnOpenProject()
{
	int returnVal = MessageBox(NULL,"�Ƿ񱣴浱ǰ���̣�", "��ʾ", MB_YESNOCANCEL);
	if( returnVal == IDOK)
	{
		OnSaveProject();
	}
	else  if(returnVal == IDCANCEL)
	{
		return;
	}
	ClearProject();


	CString csFileName(_T("*.proj"));
	static CString csFilter = "�����ļ�(*.proj)|*.proj||";
	CFileDialog dlg(TRUE, "proj", csFileName, OFN_HIDEREADONLY, csFilter);
	if( IDOK == dlg.DoModal() )
	{	
		CString csPath = dlg.GetPathName();

		if(csPath.Compare("") == 0)
			return;

		m_prjPath =csPath;
		CFile file(m_prjPath,CFile::modeRead);
		CArchive ar(&file,CArchive::load);

		CString basePath =m_prjPath.Left(m_prjPath.ReverseFind('\\')+1);
		//���òο�·��
		SYSTEM::CRelativePath::SetBasePath(basePath);


		Serialize( ar );

		ar.Close ();
		file.Close ();

		//ˢ����ͼ
		m_pLinkMapTree->RefreshFromDoc();
		m_linkMapCtrl->UpdateControl(drawAll);
	}
}


void CTDAppDoc::OnSaveProject()
{
    if(m_prjPath.IsEmpty())
	{
        //�����û�й����ļ�
		static CString csFilter = "�����ļ�(*.proj)|*.proj||";

		CFileDialog dlg(FALSE, "proj", "", OFN_HIDEREADONLY, csFilter);
		if( IDOK == dlg.DoModal() )
		{
		    m_prjPath =dlg.GetPathName();
			SaveProject();
		}		
	}
	else
	{
        //ֱ�ӱ���
		SaveProject();
	}
}

void CTDAppDoc::ClearProject()
{
	Framework::IMaptreeCtrl *pTree =GetLinkMapTree();
	if(pTree)
	{
		pTree->ClearControl();
	}
	m_pMaps.clear();
	SetActiveMap(NULL);
	m_prjPath ="";
}

void CTDAppDoc::SaveProject()
{
	CFile file(m_prjPath,CFile::modeCreate|CFile::modeWrite);
	CArchive ar(&file,CArchive::store);

	CString basePath =m_prjPath.Left(m_prjPath.ReverseFind('\\')+1);
	//���òο�·��
	SYSTEM::CRelativePath::SetBasePath(basePath);

	
	Serialize( ar );
	

	ar.Close ();
	file.Close ();
}

// CTDAppDoc commands
