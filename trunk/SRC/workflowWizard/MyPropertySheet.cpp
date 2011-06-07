#include "StdAfx.h"
#include "MyPropertySheet.h"
#include "MyPropertyPage.h"
#include "wizardResource.h"
#include "BCGStyleHeader.h"
#include "resource.h"
#include <BCGCBProInc.h>			// BCGControlBar Pro
//const char* NEXTCAPTION = "��һ��(&N)>";
//const char* PREVCAPTION = "<��һ��(&P)";
const char* NEXTCAPTION = "��һ��";
const char* PREVCAPTION = "��һ��";
const char* FINISHCAPTION = "���";
const char* HELPCAPTION = "����";
const char* CANCELCAPTION = "ȡ��";
IMPLEMENT_DYNCREATE(CMyPropertySheet, CPropertySheet)

CMyPropertySheet::CMyPropertySheet(void)
{
	prevButton = NULL;
	nextButton = NULL;
	helpButton = NULL;
	cancelButton = NULL;
}

CMyPropertySheet::~CMyPropertySheet(void)
{
	if (NULL != prevButton)
	{
		delete prevButton;
		prevButton = NULL;
	}
	if (NULL != nextButton)
	{
		delete nextButton;
		nextButton = NULL;
	}
	if (NULL != helpButton)
	{
		delete helpButton;
		helpButton = NULL;
	}
	if (NULL != cancelButton)
	{
		delete cancelButton;
		cancelButton = NULL;
	}
}
CMyPropertySheet::CMyPropertySheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
 : CPropertySheet( pszCaption, pParentWnd, iSelectPage )
{
	m_psh.dwFlags &= ~( PSH_HASHELP );//û������
//	this->AddPage(&m_page);
	
}
CMyPropertySheet::CMyPropertySheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
 : CPropertySheet( nIDCaption, pParentWnd, iSelectPage )
{
	m_psh.dwFlags &= ~( PSH_HASHELP );//û������
	
}

BEGIN_MESSAGE_MAP(CMyPropertySheet, CPropertySheet)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_NEXT, &CMyPropertySheet::OnBnClickedNext)
	ON_BN_CLICKED(IDC_BTN_PREV, &CMyPropertySheet::OnBnClickedPrev)
	ON_BN_CLICKED(IDC_BTN_CANCEL,&CMyPropertySheet::OnBnClickedCancel)
END_MESSAGE_MAP()
BOOL CMyPropertySheet::OnInitDialog()
{
	prevButton = new CBCGPButton();
	nextButton = new CBCGPButton();
	helpButton = new CBCGPButton();
	cancelButton = new CBCGPButton();

	m_bModeless = FALSE;	
	m_nFlags |= WF_CONTINUEMODAL;

	BOOL result = CPropertySheet::OnInitDialog();
	
	m_bModeless = TRUE;
	m_nFlags &= WF_CONTINUEMODAL;


	CRect rect,tabrect;
	int width;

	GetDlgItem(IDOK)->GetWindowRect(rect);
	ScreenToClient(rect);
	width = rect.Width();
	//rect.left = rect.left - 2*width -16;//tabrect.left;
	//rect.right = rect.left + width;
	prevButton->Create(_T(PREVCAPTION),BS_PUSHBUTTON|WS_CHILD|WS_VISIBLE|WS_TABSTOP,
						rect,this,IDC_BTN_PREV);
	prevButton->SetFont(GetFont());
	//
	//rect.left = rect.right + 8;
	//rect.right = rect.left + width;
	GetDlgItem(IDCANCEL)->GetWindowRect(rect);
	ScreenToClient(rect);
	nextButton->Create(_T(NEXTCAPTION),BS_PUSHBUTTON|WS_CHILD|WS_VISIBLE|WS_TABSTOP,
						rect,this,IDC_BTN_NEXT);
	nextButton->SetFont(GetFont());

	//prevButton->MoveWindow(rect);
	//GetDlgItem(IDOK)->GetWindowRect(rect);
	//ScreenToClient(rect);
	//nextButton->MoveWindow(rect);

	//����ȡ����ť
	GetDlgItem(IDCANCEL)->GetWindowRect(rect);
	ScreenToClient(rect);

	GetDlgItem(ID_APPLY_NOW)->GetWindowRect(rect);
	ScreenToClient(rect);
	cancelButton->Create(_T(CANCELCAPTION),BS_PUSHBUTTON|WS_CHILD|WS_VISIBLE|WS_TABSTOP,
						rect,this,IDC_BTN_CANCEL);
	cancelButton->SetFont(GetFont());
	cancelButton->MoveWindow(rect);


	//����������ť
	GetDlgItem(ID_APPLY_NOW)->GetWindowRect(rect);
	ScreenToClient(rect);
	helpButton->Create(_T(HELPCAPTION),BS_PUSHBUTTON|WS_CHILD|WS_VISIBLE|WS_TABSTOP,
						rect,this,IDC_BTN_HELP);
	helpButton->SetFont(GetFont());
	helpButton->MoveWindow(rect);

	//���ء�ȷ��������Ӧ�á���ť
	GetDlgItem(IDOK)->ShowWindow(SW_HIDE);
	GetDlgItem(ID_APPLY_NOW)->ShowWindow(SW_HIDE);
	GetDlgItem(IDCANCEL)->ShowWindow(SW_HIDE);

	SetBCGButtonStyle(*prevButton, EnumApplyBtn::LEFTBUTTON, "��һ��");
	SetBCGButtonStyle(*nextButton, EnumApplyBtn::RIGHTBUTTON, "��һ��");
	SetBCGButtonStyle(*cancelButton, EnumApplyBtn::CANCELBUTTON, "ȡ��");
	SetBCGButtonStyle(*helpButton, EnumApplyBtn::HELPBUTTON, "����");

	GetDlgItem(IDC_BTN_HELP)->ShowWindow(SW_HIDE);
	GetDlgItem(IDHELP)->ShowWindow(SW_HIDE);

	
	return result;
}
void CMyPropertySheet::OnBnClickedCancel()
{
	OnClose();
}
void CMyPropertySheet::OnBnClickedNext()
{
	//����ǡ���ɡ���ֱ���˳�����
	CString csCaption;
	nextButton->GetWindowText(csCaption);
	if(0 == strcmp(FINISHCAPTION,csCaption))
	{
		if(0 != DoNext())
		{
			return;
		}

		OnClose();//ֱ�ӹر�
		return;
	}

	DoNext();
}
void CMyPropertySheet::OnBnClickedPrev()
{
	DoPrev();
}
int CMyPropertySheet::DoNext()
{
	return 0;
}
int CMyPropertySheet::DoPrev()
{	
	return 0;
}
int CMyPropertySheet::DoSkip()
{
	return 0;
}
int CMyPropertySheet::UpdateCustomButtons(bool isFirst, bool isLast)
{
	//����һ������ť���
	prevButton->EnableWindow(!isFirst);
	if(isLast)
	{
		nextButton->SetWindowTextA(FINISHCAPTION);
	}
	else
	{
		nextButton->SetWindowTextA(NEXTCAPTION);
	}
	return 0;
}