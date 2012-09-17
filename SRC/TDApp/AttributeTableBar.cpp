#include "StdAfx.h"
#include "AttributeTableBar.h"
#include "Resource.h"

const int nBorderSize = 1;

CAttributeTableBar::CAttributeTableBar(void)
{
}

CAttributeTableBar::~CAttributeTableBar(void)
{
}

BEGIN_MESSAGE_MAP(CAttributeTableBar, CBCGPDockingControlBar)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_WM_PAINT()
	
	ON_UPDATE_COMMAND_UI(ID_TABLE_EDITMODE, &CAttributeTableBar::OnUpdateTableEdit)
	
	ON_COMMAND(ID_TABLE_SQLQUERY, &CAttributeTableBar::OnTableQuery)
	ON_UPDATE_COMMAND_UI(ID_TABLE_SQLQUERY, &CAttributeTableBar::OnUpdateTableQuery)
	
	ON_COMMAND(ID_FIND_REPLACE, &CAttributeTableBar::OnFindReplace)
	ON_UPDATE_COMMAND_UI(ID_FIND_REPLACE, &CAttributeTableBar::OnUpdateFindReplace)
	
	ON_COMMAND(ID_ATTRTABLE_SELALL, &CAttributeTableBar::OnSelectAll)
	ON_UPDATE_COMMAND_UI(ID_ATTRTABLE_SELALL, &CAttributeTableBar::OnUpdateSelectAll)
	
	ON_COMMAND(ID_ATTRTABLE_SELNONE, &CAttributeTableBar::OnSelectNone)
	ON_UPDATE_COMMAND_UI(ID_ATTRTABLE_SELNONE, &CAttributeTableBar::OnUpdateSelectNone)
	
	ON_COMMAND(ID_ADD_FIELD, &CAttributeTableBar::OnAddField)
	ON_UPDATE_COMMAND_UI(ID_ADD_FIELD, &CAttributeTableBar::OnUpdateAddField)

	ON_COMMAND(ID_START_EDIT, &CAttributeTableBar::OnStartEdit)
	ON_UPDATE_COMMAND_UI(ID_START_EDIT, &CAttributeTableBar::OnUpdateStartEdit)

	ON_COMMAND(ID_STOPSAVE_EDIT, &CAttributeTableBar::OnStopSaveEdit)
	ON_UPDATE_COMMAND_UI(ID_STOPSAVE_EDIT, &CAttributeTableBar::OnUpdateStopSaveEdit)

	ON_COMMAND(ID_SHOW_ALLFIELDS, &CAttributeTableBar::OnShowFields)

	ON_COMMAND(ID_ATTRBAR_OUTPUTTABLE, &CAttributeTableBar::OnOutputTable)

	ON_COMMAND(ID_ATTRBAR_PRINT, &CAttributeTableBar::OnPrintTable)

	ON_COMMAND(ID_SET_APREARENCE, &CAttributeTableBar::OnSetAprearence)

	ON_MESSAGE(WM_UPDATESELECTNUM,OnUpdateSelNum)
END_MESSAGE_MAP()

int CAttributeTableBar::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CBCGPDockingControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	
	m_table.CreateControl("ATTRIBUTE TABLE",(void*)this,1);

	m_table.SetAutoDetroy(true);

	//创建工具条
	m_OperToolbar.Create (this, WS_CHILD|WS_VISIBLE|CBRS_TOP|CBRS_TOOLTIPS|CBRS_FLYBY|CBRS_HIDE_INPLACE|CBRS_SIZE_DYNAMIC|
		CBRS_GRIPPER | CBRS_BORDER_3D, IDR_TOOLBAR_ATTRTABLE);
	m_OperToolbar.LoadToolBar (IDR_TOOLBAR_ATTRTABLE, 0, 0, TRUE /* Is locked */);
	m_OperToolbar.SetBarStyle (
		m_OperToolbar.GetBarStyle () & 
		~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));
	m_OperToolbar.SetOwner (this);
	m_OperToolbar.SetRouteCommandsViaFrame (FALSE);
	
	//将第一个按钮替换成Edit控件
	CBCGPToolbarEditBoxButton EditBoxBtn(0, 0, ES_CENTER | ES_READONLY ,150); 
	m_OperToolbar.ReplaceButton(ID_SELRECORD_TEXT, EditBoxBtn);
	
	return 0;
}

void CAttributeTableBar::OnSize(UINT nType, int cx, int cy)
{
	CBCGPDockingControlBar::OnSize(nType, cx, cy);

	CRect rect;
	GetClientRect(rect);

	//设置工具条的位置
	int toolbarHeight = m_OperToolbar.CalcFixedLayout (FALSE, TRUE).cy;
	int toolbarWidth = m_OperToolbar.CalcFixedLayout (FALSE, TRUE).cx;
	m_OperToolbar.SetWindowPos (NULL, rect.left, rect.top, 
		rect.Width (), toolbarHeight,
		SWP_NOACTIVATE |SWP_NOZORDER);

	m_table.SetWindowPos (NULL, rect.left + 1, rect.top + toolbarHeight + 1,
		rect.Width () - 2, rect.Height () - toolbarHeight - 2,
		SWP_NOACTIVATE | SWP_NOZORDER);
}

void CAttributeTableBar::OnDestroy()
{
	CBCGPDockingControlBar::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
}

void CAttributeTableBar::OnPaint()
{
	CPaintDC dc(this); // device context for painting
    

	CRect rectList;
	m_table.GetWindowRect (rectList);
	ScreenToClient (rectList);

	rectList.InflateRect (1, 1);
	dc.Draw3dRect (rectList, ::GetSysColor (COLOR_3DSHADOW), 
		::GetSysColor (COLOR_3DSHADOW));

}

void CAttributeTableBar::SetTableEdit( bool bEdit )
{
	m_table.SetEditMode( bEdit );
}

void CAttributeTableBar::OnUpdateTableEdit(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(m_table.IsEditMode());
	pCmdUI->SetRadio( m_table.IsEditMode() );
	pCmdUI->Enable( m_table.IsEditMode() );
}

LRESULT CAttributeTableBar::OnUpdateSelNum(WPARAM wParam, LPARAM lParam)
{
	CString  tmp;
	tmp.Format("选中%d%s%d条记录", m_table.GetSelectCount(),"/",m_table.GetRecordCount());


	CBCGPToolbarEditBoxButton *pEditBtn = (CBCGPToolbarEditBoxButton*)m_OperToolbar.GetButton(0);
	if (pEditBtn != NULL)
	{
		pEditBtn->SetContents( tmp );
	}
	return 0;
}

void CAttributeTableBar::OnTableQuery()
{
   m_table.TableQuery();
}

void CAttributeTableBar::OnUpdateTableQuery(CCmdUI *pCmdUI)
{

}



void CAttributeTableBar::OnFindReplace()
{
	m_table.FindReplace();
}

void CAttributeTableBar::OnUpdateFindReplace(CCmdUI* pCmndUI)
{

}

void CAttributeTableBar::OnSelectAll()
{
	m_table.SelectAll();
}

void CAttributeTableBar::OnUpdateSelectAll(CCmdUI* pCmndUI)
{
	
}

void CAttributeTableBar::OnSelectNone()
{
	m_table.SelectNone();
}

void CAttributeTableBar::OnUpdateSelectNone(CCmdUI* pCmndUI)
{

}

void CAttributeTableBar::OnAddField()
{
	m_table.AddField();
}

void CAttributeTableBar::OnUpdateAddField(CCmdUI* pCmndUI)
{
	pCmndUI->Enable( !m_table.IsEditMode() );
}

void CAttributeTableBar::OnShowFields()
{
	m_table.ShowAllFields();
}

void CAttributeTableBar::OnOutputTable()
{
	CString csSavePath;	
	CString csFilter = "TXT (*.txt)|*.txt| Database file(*.dbf)|*.dbf||";
	CFileDialog dlgSave(FALSE, "TXT", "未标题", OFN_HIDEREADONLY, csFilter);
	
	if( IDOK == dlgSave.DoModal())
	{
		CString strPathName = dlgSave.GetPathName();
		CString strExt = dlgSave.GetFileExt();

		if ( strExt == "txt")
			m_table.OutputToTxt( strPathName );
		else if( strExt == "dbf" )
			m_table.OutputToDbf( strPathName );
	}
}

void CAttributeTableBar::OnPrintTable()
{
	m_table.Print();
}

void CAttributeTableBar::OnSetAprearence()
{
	m_table.SetTableProperty();
}

void CAttributeTableBar::OnStartEdit()
{
	SetTableEdit(true);
}

void CAttributeTableBar::OnUpdateStartEdit(CCmdUI* pCmndUI)
{
	pCmndUI->Enable( !m_table.IsEditMode() );
}

void CAttributeTableBar::OnStopSaveEdit()
{
	SetTableEdit(false);
}

void CAttributeTableBar::OnUpdateStopSaveEdit(CCmdUI* pCmndUI)
{
	pCmndUI->Enable( m_table.IsEditMode() );
}