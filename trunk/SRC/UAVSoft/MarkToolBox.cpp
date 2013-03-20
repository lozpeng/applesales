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

	//AddToolsPage (_T("Ŀ��ѡ��"), IDB_TOOLBAR_WORKSPACE, 40, 
	//	_T("ָ��\n��ǩ\nButton\nTextBox\nMainMenu\nCheckBox\nRadioButton\nGroupBox\nPictureBox\nPanel\nDataGrid\nListBox\nCheckedListBox\nComboBox\nListView\nTreeView\nTabControl\nDateTimePicker\nMonthCalendar\nHScrollBar\nVScrollBar\nTimer\nSplitter\nDomainUpDown\nNumericUpDown\nTrackBar\nProgressBar\nRichTextBox"));

	//GetPage (0)->SetMode (CBCGPToolBoxPage::ToolBoxPageMode_Images);

	//AddToolsPage (_T("Components"),	IDB_TOOLS_PAGE2, 16, _T("Pointer\nDataSet\nOleDbDataAdapter\nOleDbConnection"));
	//AddToolsPage (_T("Data"),	IDB_TOOLS_PAGE3, 16, _T("Pointer\nFileSystemWatch\nEventLog\nDirectoryEntry"));
	//AddToolsPage (_T("�������"), IDB_BITMAP_MARK, 20,
	//	_T("ȡ��\nѡ��\n���깤��\nֱ��\n����\n����\n��Բ\n�����\n���\n�ڵ�\nɾ��\n��ת"));
	//GetPage (0)->SetMode (CBCGPToolBoxPage::ToolBoxPageMode_Images);
	/*AddToolsPage (_T("���ַ���"), IDB_BITMAP_MARK, 20, 
		_T("ȡ��\nѡ��\n���깤��\nֱ��\n����\n����\n��Բ\n�����\n���\n�ڵ�\nɾ��\n��ת"));
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

	/*AddToolsPage (_T("�������"), IDB_BITMAP_MARK, 20, 
		_T("ȡ��\nѡ��\n���깤��\nֱ��\n����\n����\n��Բ\n�����\n���\n�ڵ�\nɾ��\n��ת"));
	GetPage (0)->SetMode (CBCGPToolBoxPage::ToolBoxPageMode_Images);
	AddToolsPage (_T("���ַ���"), IDB_BITMAP_MARK, 20, 
		_T("ȡ��\nѡ��\n���깤��\nֱ��\n����\n����\n��Բ\n�����\n���\n�ڵ�\nɾ��\n��ת"));
	GetPage (1)->SetMode (CBCGPToolBoxPage::ToolBoxPageMode_Images);*/
	return 0;
}
