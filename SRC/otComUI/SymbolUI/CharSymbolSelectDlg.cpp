#include "StdAfx.h"
#include "CharSymbolSelectDlg.h"


IMPLEMENT_DYNAMIC(CCharSymbolSelectDlg, CBCGPDialog)

BEGIN_MESSAGE_MAP(CCharSymbolSelectDlg, CBCGPDialog)

	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

CCharSymbolSelectDlg::CCharSymbolSelectDlg(CWnd* pParent) : CBCGPDialog(CCharSymbolSelectDlg::IDD ,pParent)
{
	m_pSymbolSelectProp = NULL;
}

CCharSymbolSelectDlg::~CCharSymbolSelectDlg(void)
{
}

void CCharSymbolSelectDlg::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
//	DDX_Control(pDX, IDC_CHARLIST, m_ctrlCharSymbolListBox);
}
void CCharSymbolSelectDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CBCGPDialog::OnMouseMove(nFlags, point);
}

void CCharSymbolSelectDlg::SetSymbolSelectProp(CCharSymbolSelectProp* pSymbolSelectProp)
{
	m_pSymbolSelectProp = pSymbolSelectProp;
}

BOOL CCharSymbolSelectDlg::OnInitDialog()
{
	CBCGPDialog::OnInitDialog();

	if (m_pCharMarkSymbol == NULL)
	{
		return FALSE;
	}

	CRect clientRect;
	this->GetClientRect(&clientRect);

	clientRect.left = clientRect.left + 8;
	clientRect.right = clientRect.right - 8;
	clientRect.top = clientRect.top + 8;
	clientRect.bottom =clientRect.bottom - 8;

	m_ctrlCharSymbolListBox.Create(
		      WS_CHILD|WS_VISIBLE|WS_BORDER/*|WS_HSCROLL*/|WS_VSCROLL|
		      /*LBS_SORT|*//*LBS_MULTIPLESEL|*/LBS_OWNERDRAWVARIABLE | LBS_DISABLENOSCROLL,
		      clientRect, this, 1);

	m_ctrlCharSymbolListBox.GetClientRect(&clientRect);
	m_ctrlCharSymbolListBox.m_rect = clientRect;
	

	m_ctrlCharSymbolListBox.SetSymbolSelectProp(m_pSymbolSelectProp);
	long lRow = FONTSYMBOLNUMS / NUMSYMBOLPERROW;
	if(FONTSYMBOLNUMS % NUMSYMBOLPERROW )
		lRow++; 

	for(int i = 0; i< lRow ; ++i)
		m_ctrlCharSymbolListBox.AddString("NULL");	

	

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CCharSymbolSelectDlg::SetCharMarkSymbol(Display::CCharMarkerSymbolPtr pCharMarkSymbol)
{
	m_pCharMarkSymbol = pCharMarkSymbol;
	m_ctrlCharSymbolListBox.SetCharMarkSymbol(m_pCharMarkSymbol);
}