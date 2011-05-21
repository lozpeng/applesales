// DlgSymbolSelect.cpp : 实现文件
//

#include "stdafx.h"
#include "SymbolSelectdlg.h"
#include "DlgSymbolEdit.h"
//#include "DlgTextSymbolEdit.h"
#include "SymbolFactory.h"
#include "IComplexSymbol.h"
#include "IExtSymbol.h"
// CDlgSymbolSelect 对话框

IMPLEMENT_DYNAMIC(CDlgSymbolSelect, CDialog)

CDlgSymbolSelect::CDlgSymbolSelect(CWnd* pParent /*=NULL*/)
: CDialog(CDlgSymbolSelect::IDD, pParent)
, m_SymKeyString(_T(""))
, m_SymbolName(_T(""))
{

	m_bRun=TRUE;
	m_nSelect = 0;
	m_bFind = true;
	m_SymbolLibMenu =m_SymAddMenu =NULL;
	
}

CDlgSymbolSelect::~CDlgSymbolSelect()
{
	if( m_SymbolLibMenu != NULL)
	{
		delete m_SymbolLibMenu;
	}
	if( m_SymAddMenu != NULL)
	{
		delete m_SymAddMenu;
	}
	for (int i=0; i<SymLibs.size(); ++i)
	{
		delete SymLibs[i];
		SymLibs[i] = NULL;
	}
	SymLibs.clear();
}

void CDlgSymbolSelect::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_SYMBOL, m_SymList);
	DDX_Control(pDX, IDC_BTN_OVERVIEW, m_SymButton);
	DDX_Text(pDX, IDC_SYMKEY, m_SymKeyString);
	DDX_Text(pDX, IDC_SYMNAME, m_SymbolName);
	DDX_Control(pDX, IDC_SYMBOLFIND, m_btFind);
	DDX_Control(pDX, IDOK, m_btOk);

}


BEGIN_MESSAGE_MAP(CDlgSymbolSelect, CDialog)
	ON_BN_CLICKED(IDC_BTN_SYMBOL_EDIT, &CDlgSymbolSelect::OnBnClickedBtnSymbolEdit)
	ON_BN_CLICKED(IDC_ADD_SYMBOLLIB, &CDlgSymbolSelect::OnBnClickedAddSymbollib)
	ON_BN_CLICKED(IDC_BTN_OVERVIEW, &CDlgSymbolSelect::OnBnClickedBtnOverview)
	ON_BN_CLICKED(IDOK, &CDlgSymbolSelect::OnBnClickedOk)
	ON_BN_KILLFOCUS(IDC_BTN_OVERVIEW, OnBnKillfocusBtnOverview)
	/*ON_COMMAND_RANGE(ID_SYMBOLRANGSTART, ID_ADDSYMBOLRANGEND, &CDlgSymbolSelect::OnSymbolMenuItems)
	ON_UPDATE_COMMAND_UI_RANGE(ID_SYMBOLRANGSTART, ID_ADDSYMBOLRANGEND, &CDlgSymbolSelect::OnSymbolMenuItemsUI)*/
	ON_BN_CLICKED(IDC_SAVESYMBOL, OnBnClickedSavesymbol)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_SYMBOL, OnLvnItemchangedListSymbol)
	ON_EN_CHANGE(IDC_SYMNAME, OnEnChangeSymname)
	ON_BN_CLICKED(IDC_SYMBOLFIND, &CDlgSymbolSelect::OnBnClickedSymbolfind)
	ON_EN_CHANGE(IDC_SYMKEY, &CDlgSymbolSelect::OnEnChangeSymkey)
	ON_BN_CLICKED(IDC_SYMBOLRESETTING, &CDlgSymbolSelect::OnBnClickedSymbolresetting)
END_MESSAGE_MAP()


// CDlgSymbolSelect 消息处理程序

void CDlgSymbolSelect::OnBnClickedBtnSymbolEdit()
{

	if(m_pSymbol->GetType() & TEXT_SYMBOL)
	{
	/*	CDlgTextSymbolEdit DlgEdit;

		DlgEdit.SetSymbol(m_pSymbol);

		INT_PTR result = DlgEdit.DoModal();

		if ( result == IDOK ) 
		{
			m_pSymbol = DlgEdit.m_pTextSymbol;
		} */
	}
	else
	{
		CDlgSymbolEdit DlgEdit;

		m_pSymbol = DlgEdit.EditSymbol(m_pSymbol);
		if (m_pSymbol->GetType() & COMPLEX_SYMBOL)
		{
			Display::IComplexSymbolPtr complexSymbol = m_pSymbol;
			if (complexSymbol != NULL)
			{
				int index = complexSymbol->GetSize() - 1;
				for ( ; index >= 0 ; --index )
				{
					Display::IExtSymbolPtr pSymbol =  complexSymbol->GetAt(index);
					if ( pSymbol == NULL)
						break;
				}
				if (index >= 0)
				{
					Display::ISymbolPtr aimSymbol  = complexSymbol->GetAt(index);
					bool state = complexSymbol->IsVisible(index);
					complexSymbol->RemoveSymbol(index);
					complexSymbol->Insert(index , aimSymbol , state);
				}
			}
		}
	}
	


	m_SymButton.SetSymbol(m_pSymbol.get());
	m_SymButton.Invalidate();
	m_SymbolName = m_pSymbol->GetLabel().c_str();
	UpdateData(FALSE);
}

void CDlgSymbolSelect::OnBnClickedAddSymbollib()
{
	// 弹出菜单
	CRect rc;
	GetDlgItem(IDC_ADD_SYMBOLLIB)->GetWindowRect(&rc);

	this->m_SymbolLibMenu->TrackPopupMenu( TPM_LEFTALIGN |TPM_RIGHTBUTTON, rc.left, 
		rc.bottom, this);

}

void CDlgSymbolSelect::OnBnClickedBtnOverview()
{
	OnBnClickedBtnSymbolEdit();
}

void CDlgSymbolSelect::OnBnClickedOk()
{
	
	OnOK();
}

BOOL CDlgSymbolSelect::OnInitDialog()
{	
	CDialog::OnInitDialog();

	
	
	InitData();
	
	m_pSymbol =m_pcopySymbol;
	m_SymButton.SetSymbol( m_pcopySymbol.get() );

	m_SymbolName = m_pcopySymbol->GetLabel().c_str();

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDlgSymbolSelect::SetSymbol(Display::ISymbolPtr pSymbol)
{
    m_pSymbol =m_pcopySymbol=pSymbol;
}

void CDlgSymbolSelect::UpdateAddSymbolMenu()
{
	/*for( int i = m_SymAddMenu->GetMenuItemCount()-1 ; i >= 0 ; i-- )
		m_SymAddMenu->RemoveMenu( i, 0 );

	for( unsigned int i = 0; i < m_SymbolLibMenu->GetMenuItemCount(); i++)
	{
		if( m_SymbolLibMenu->GetMenuState( ID_SYMBOLRANGSTART+i , MF_CHECKED ) == MF_CHECKED )
		{
			CString label;
			m_SymbolLibMenu->GetMenuString( ID_SYMBOLRANGSTART+i , label , 0 );
			m_SymAddMenu->AppendMenu( MF_STRING , ID_ADDSYMBOLRANGSTART+i ,  label );
		}
	}*/
}

void CDlgSymbolSelect::OnBnKillfocusBtnOverview()
{
	// TODO: 在此添加控件通知处理程序代码
}
void CDlgSymbolSelect:: OnOpenSymbolLibMenuItems(UINT nID)
{
	/*CFileDialog fileDlg(TRUE,"*.mdb","*.mdb");

	if( fileDlg.DoModal() != IDOK)
		return;

	CString strName;
	CString strPath = fileDlg.GetPathName();
	int pos1 = strPath.ReverseFind('\\');
	int pos2 = strPath.ReverseFind('.');
	strName = strPath.Mid(pos1+1, pos2-pos1-1);
	BOOL bFlag = SetCurrentDirectory(m_cPath);
	if ( strName.GetLength() == 0 )
		return;
	if ( strPath.GetLength() == 0 )
		return;
	CSymbolLibLoader SymbolAccess;
	if(!SymbolAccess.OpenDatabase( strPath.GetBuffer() ))
	{
		::MessageBox(this->m_hWnd , "不是Access文件" , "警告", MB_OK );
		return;
	}

	SYSTEM::XMLConfigurationPtr ptrParser = Display::GetSymbolRenderConfig();
	if(ptrParser == NULL)
	{
		return;
	}

	SYSTEM::IConfigItemPtr pDisplayItem = ptrParser->GetChildByName("Display");
	if( pDisplayItem == NULL ) 
	{
		return ;
	}
	SYSTEM::IConfigItemPtr pSymbolLibConfig = pDisplayItem->GetChildByName("SymbolLibConfig");
	if( pSymbolLibConfig == NULL ) 
	{
		return ;
	}

	SYSTEM::IConfigItemPtr SymbolLib = pSymbolLibConfig->AddChildNode( "SymbolLibItem");
	SymbolLib->AddAttribute( "Name" ,strName.GetBuffer() );
	SymbolLib->AddAttribute( "SymbolPathName" ,strPath.GetBuffer());	

	InitData();*/

}
void CDlgSymbolSelect::OnAddSymbolMenuItems(UINT nID)
{
	// 添加符号到库
	//long index = nID - ID_ADDSYMBOLRANGSTART;
	// CSymbolLibLoader &slib = SymLibs[index];
	//if( slib.AddSymbol( m_pSymbol ) )
	//	::MessageBox(this->m_hWnd , "符号保存成功！" , "提示", MB_OK );
	//else
	//	::MessageBox(this->m_hWnd , "符号保存失败：是否与现有符号重名？" , "警告", MB_OK );
}

void CDlgSymbolSelect::OnSymbolMenuItems(UINT nID )
{
	//if( nID > 0 )
	//{
	//	m_nMenuID = nID;
	//}

	//if( nID > ID_SYMBOLRANGEND )
	//{
	//	OnAddSymbolMenuItems( nID );
	//	InstallSymbol();
	//	return;
	//}
	//if( nID == ID_SYMBOLRANGEND )
	//{
	//	OnOpenSymbolLibMenuItems( nID );
	//	return;
	//}
	//UINT index = nID - ID_SYMBOLRANGSTART;
	//m_nSelect = index;
	//InitData();

}

void CDlgSymbolSelect::OnSymbolMenuItemsUI(CCmdUI *pCmdUI)
{
	/*if( pCmdUI->m_nID > ID_SYMBOLRANGEND )
		return;
	if( pCmdUI->m_nID == ID_SYMBOLRANGEND )
		return;

	pCmdUI->SetCheck( SymLibs[pCmdUI->m_nIndex].bVisible );*/
}
bool CDlgSymbolSelect::InstallSymbol(char * pStrName)
{

	m_SymList.DelListCtrl();
	for (long i = 0 ; i < SymLibs.size() ; i++)
	{
		if( SymLibs[i]->bVisible )
		{
			if( pStrName == NULL )
				m_SymList.AddSymbolArray( SymLibs[i]->GetName() , SymLibs[i]->QuerySymbols("",m_pSymbol->GetType()));
			else 
				m_SymList.AddSymbolArray( SymLibs[i]->GetName() , SymLibs[i]->QuerySymbols( pStrName ,m_pSymbol->GetType()));
		}
	}
	return false;
}


void CDlgSymbolSelect::OnBnClickedSavesymbol()
{
	// 保存代码到库中去
	//CRect rc;
	//GetDlgItem(IDC_SAVESYMBOL)->GetWindowRect(&rc);
	//m_SymAddMenu->TrackPopupMenu( TPM_LEFTALIGN |TPM_RIGHTBUTTON, rc.left, 
	//	rc.bottom, this);
	CSymbolLibLoader* pSymLib = new CSymbolLibLoader();
	pSymLib->OpenDatabase(m_strSymFile.GetBuffer());
	if( pSymLib->AddSymbol( m_pSymbol ) )
		::MessageBox(this->m_hWnd , "符号保存成功！" , "提示", MB_OK );
	else
		::MessageBox(this->m_hWnd , "符号保存失败：是否与现有符号重名？" , "警告", MB_OK );

	for (int i=0; i<SymLibs.size(); ++i)
	{
		delete SymLibs[i];
		SymLibs[i] = NULL;
	}
	SymLibs.clear();

	SymLibs.push_back(pSymLib);

	m_SymList.AddSymbol(pSymLib->GetName(), m_pSymbol);


	UpdateData(FALSE);
}

void CDlgSymbolSelect::OnLvnItemchangedListSymbol(NMHDR *pNOTDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNOTDR);

	// 更新选择符号对话框的符号预览框和名称
	m_pSymbol = ((Display::ISymbol*)m_SymList.GetItemData( pNMLV->iItem ))->Clone();

	m_SymButton.SetSymbol( m_pSymbol.get());

	m_SymbolName = m_pSymbol->GetLabel().c_str();
	UpdateData(FALSE);
	*pResult = 0;
}

void CDlgSymbolSelect::OnEnChangeSymname()
{
	UpdateData();
	m_pSymbol->SetLabel( (LPCTSTR)m_SymbolName );
}

void CDlgSymbolSelect::OnBnClickedSymbolfind()
{
	/*this->GetDlgItemText( IDC_SYMKEY , m_SymKeyString );
	if( m_SymKeyString.IsEmpty() )
		::MessageBox( this->m_hWnd , "字符串不能为空" , "警告" , MB_OK );
	int i=m_nMenuID - ID_SYMBOLRANGSTART;
	InstallSymbol(m_SymKeyString.GetBuffer());
	m_SymKeyString = "";
	SetDlgItemText(IDC_SYMKEY ,m_SymKeyString );
	m_bFind = true;*/
}

void CDlgSymbolSelect::InitData(void)
{
	char szTempPath[_MAX_PATH] = "";
	char szTemp[_MAX_PATH] = "";
	char szDriver[_MAX_DRIVE] = "";
	char szDir[_MAX_DIR] = "";
	GetModuleFileName (::AfxGetApp()->m_hInstance, szTemp, MAX_PATH);
	_splitpath(szTemp, szDriver, szDir, NULL, NULL);
	_makepath(szTempPath, szDriver, szDir, NULL, NULL);

	CString strPath(szTempPath);
	CString strSymbol = strPath + "\symbol\\symbol.mdb";
	CSymbolLibLoader* pSymLib = new CSymbolLibLoader();
	pSymLib->OpenDatabase(strSymbol.GetBuffer());
	m_strSymFile = strSymbol;
	SymLibs.push_back(pSymLib);
	m_SymList.SetImageSize( 50 );
	InstallSymbol();
	UpdateData(FALSE);

	//SYSTEM::CXMLConfiguration::Initialize();
	////得到程序所在路径
	//DWORD dwRet = ::GetModuleFileName( NULL , m_cPath , 512 );
	//int i;
	//for( i = strlen(m_cPath)-1 ; i >= 0 && m_cPath[i] !='\\' ; i-- );
	//m_cPath[i+1] = '\0';

	//if(dwRet==0)
	//{
	//	::MessageBox(this->m_hWnd , "得到当前路径错误" , "警告", MB_OK );
	//	return ;
	//}
	//if(dwRet > 512)
	//{
	//	::MessageBox(this->m_hWnd , "路径过长，建议路径字符不超过500个字！" , "警告", MB_OK );
	//	return ;
	//}

	//if( SymLibs.GetSize() != 0 )
	//{
	//	SymLibs.RemoveAll();
	//}
	//if( m_SymbolLibMenu != NULL )
	//{
	//	delete m_SymbolLibMenu;
	//	m_SymbolLibMenu = new CMenu;
	//}
	//else
	//{
	//	m_SymbolLibMenu = new CMenu;
	//}
	//if( m_SymAddMenu != NULL )
	//{
	//	delete m_SymAddMenu;
	//	m_SymAddMenu = new CMenu;
	//}
	//else
	//{
	//	m_SymAddMenu = new CMenu;
	//}
	//m_SymbolLibMenu->CreatePopupMenu();
	//m_SymAddMenu->CreatePopupMenu();


	//SYSTEM::XMLConfigurationPtr ptrParser = Display::GetSymbolRenderConfig();
	//if(ptrParser == NULL)
	//{
	//	ErrorLog("Get symbolrender node failed.");
	//	return;
	//}

	//SYSTEM::IConfigItemPtr pDisplayItem = ptrParser->GetChildByName("Display");
	//if( pDisplayItem == NULL ) 
	//{
	//	ErrorLog("Get Display child failed in symbol file, maybe the file is wrong.");
	//	return ;
	//}
	//SYSTEM::IConfigItemPtr pSymbolLibConfig = pDisplayItem->GetChildByName("SymbolLibConfig");
	//if( pSymbolLibConfig == NULL ) 
	//{
	//	ErrorLog("Get SymbolLibConfig child failed in otSymbolRender.xml \n maybe the file is wrong.");
	//	return ;
	//}

	//SymLibs.SetSize( pSymbolLibConfig->GetChildCount() );
	//long nCount = pSymbolLibConfig->GetChildCount();
	//CString str, str1;
	//long index = 0;
	//for( long i = 0; i < nCount; i++)
	//{
	//	SYSTEM::IConfigItemPtr pSymbolLibItem = pSymbolLibConfig->GetChilds(i);
	//	str.Format( "%s" , pSymbolLibItem->GetProperties("SymbolPathName"));
	//	int nFind = str.Find(":\\");
	//	str1.Format("%s",m_cPath);
	//	str1 += str;
	//	if( nFind == -1 )
	//	{
	//		
	//		if(!SymLibs[index].OpenDatabase( str1.GetBuffer() ))
	//		{
	//			SymLibs.RemoveAt(index);
	//			continue;
	//		}
	//	}
	//	else
	//	{
	//		
	//		if(!SymLibs[index].OpenDatabase(pSymbolLibItem->GetProperties("SymbolPathName")))
	//		{
	//			SymLibs.RemoveAt(index);
	//			continue;
	//		}
	//	}

	//	if( m_nSelect == i )
	//	{

	//		m_SymbolLibMenu->AppendMenu( MF_CHECKED | MF_STRING , ID_SYMBOLRANGSTART+index , pSymbolLibItem->GetProperties("Name") );
	//	}
	//	else
	//	{
	//		m_SymbolLibMenu->AppendMenu( MF_UNCHECKED | MF_STRING , ID_SYMBOLRANGSTART+index , pSymbolLibItem->GetProperties("Name") );
	//		SymLibs[ index ].bVisible = FALSE;
	//	}
	//	index++;
	//}
	//if(SymLibs.GetSize() == 0)
	//{
		//如果没有符号库，创建一个默认的符号库
	//	SYSTEM::IConfigItemPtr pSymbolLib = pDisplayItem->GetChildByName("SymbolLib");
	//	SymLibs.SetSize(1);
	//	str.Format( "%s" , pSymbolLib->GetProperties("SymbolPathName"));
	//	str1.Format("%s",m_cPath);
	//	str1 +=str;
	//	SymLibs[0].CreateDataBase(str1);
	//	SymLibs[0].OpenDatabase(str1);
	//	if( m_nSelect == 0 )
	//	{
	//		m_SymbolLibMenu->AppendMenu( MF_CHECKED | MF_STRING , ID_SYMBOLRANGSTART , pSymbolLib->GetProperties("Name"));
	//	}
	//	else
	//	{
	//		m_SymbolLibMenu->AppendMenu( MF_UNCHECKED | MF_STRING , ID_SYMBOLRANGSTART , pSymbolLib->GetProperties("Name") );
	//		SymLibs[ 0 ].bVisible = FALSE;
	//	}
	//}

	//m_SymbolLibMenu->AppendMenu( MF_SEPARATOR );
	//m_SymbolLibMenu->AppendMenu( MF_STRING , ID_SYMBOLRANGEND , "添加新符号库..." );
	//m_nMenuID =  ID_SYMBOLRANGSTART;
	//UpdateAddSymbolMenu();

	//InstallSymbol();
	//UpdateData(FALSE);
}


void CDlgSymbolSelect::OnEnChangeSymkey()
{
	m_bFind = false;
}

void CDlgSymbolSelect::OnBnClickedSymbolresetting()
{
	InstallSymbol();
}


