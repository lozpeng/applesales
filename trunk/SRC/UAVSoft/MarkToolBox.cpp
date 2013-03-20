// ToolBox.cpp: implementation of the CResourceViewBar class.
//

#include "stdafx.h"
#include "UAVSoft.h"
#include "MainFrm.h"
#include "MarkToolBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CToolBoxBar

CToolBoxBar::CToolBoxBar()
{
	CBCGPOutlookWnd::EnableAnimation ();
}

CToolBoxBar::~CToolBoxBar()
{
}

BEGIN_MESSAGE_MAP(CToolBoxBar, CBCGPToolBox)
	//{{AFX_MSG_MAP(CToolBoxBar)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

int CToolBoxBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CBCGPToolBox::OnCreate(lpCreateStruct) == -1)
		return -1;

	//AddToolsPage (_T("目标选择"), IDB_TOOLBAR_WORKSPACE, 40, 
	//	_T("指针\n标签\nButton\nTextBox\nMainMenu\nCheckBox\nRadioButton\nGroupBox\nPictureBox\nPanel\nDataGrid\nListBox\nCheckedListBox\nComboBox\nListView\nTreeView\nTabControl\nDateTimePicker\nMonthCalendar\nHScrollBar\nVScrollBar\nTimer\nSplitter\nDomainUpDown\nNumericUpDown\nTrackBar\nProgressBar\nRichTextBox"));

	//GetPage (0)->SetMode (CBCGPToolBoxPage::ToolBoxPageMode_Images);

	//AddToolsPage (_T("Components"),	IDB_TOOLS_PAGE2, 16, _T("Pointer\nDataSet\nOleDbDataAdapter\nOleDbConnection"));
	//AddToolsPage (_T("Data"),	IDB_TOOLS_PAGE3, 16, _T("Pointer\nFileSystemWatch\nEventLog\nDirectoryEntry"));
	//AddToolsPage (_T("基本标绘"), IDB_BITMAP_MARK, 20,
	//	_T("取消\n选择\n军标工具\n直线\n折线\n矩形\n椭圆\n多边形\n标记\n节点\n删除\n旋转"));
	//GetPage (0)->SetMode (CBCGPToolBoxPage::ToolBoxPageMode_Images);
	/*AddToolsPage (_T("减灾符号"), IDB_BITMAP_MARK, 20, 
		_T("取消\n选择\n军标工具\n直线\n折线\n矩形\n椭圆\n多边形\n标记\n节点\n删除\n旋转"));
	GetPage (1)->SetMode (CBCGPToolBoxPage::ToolBoxPageMode_Images);*/
	return 0;
	
}

/////////////////////////////////////////////////////////////////////////////
// CToolBoxBarEx

CMarkToolBoxBarEx::CMarkToolBoxBarEx()
{
}

CMarkToolBoxBarEx::~CMarkToolBoxBarEx()
{
}

BEGIN_MESSAGE_MAP(CMarkToolBoxBarEx, CBCGPToolBoxEx)
	//{{AFX_MSG_MAP(CToolBoxBarEx)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

int CMarkToolBoxBarEx::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CBCGPToolBoxEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	/*AddToolsPage (_T("基本标绘"), IDB_BITMAP_MARK, 20, 
		_T("取消\n选择\n军标工具\n直线\n折线\n矩形\n椭圆\n多边形\n标记\n节点\n删除\n旋转"));
	GetPage (0)->SetMode (CBCGPToolBoxPage::ToolBoxPageMode_Images);
	AddToolsPage (_T("减灾符号"), IDB_BITMAP_MARK, 20, 
		_T("取消\n选择\n军标工具\n直线\n折线\n矩形\n椭圆\n多边形\n标记\n节点\n删除\n旋转"));
	GetPage (1)->SetMode (CBCGPToolBoxPage::ToolBoxPageMode_Images);*/
	return 0;
}
