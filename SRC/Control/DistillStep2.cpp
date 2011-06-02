// DistillStep2.cpp : 实现文件
//

#include "stdafx.h"
#include "Control.h"
#include "DistillStep2.h"


// CDistillStep2 对话框

IMPLEMENT_DYNAMIC(CDistillStep2, CResizablePage)

CDistillStep2::CDistillStep2(CWnd* pParent /*=NULL*/)
: CResizablePage(CDistillStep2::IDD)
{
	//m_psp.dwFlags &= (~PSP_HASHELP);
	m_psp.dwFlags |= PSP_USEHICON;
	HICON hIconTab = AfxGetApp()->LoadIcon(IDI_STEP2);
	m_psp.hIcon = hIconTab;
}

CDistillStep2::~CDistillStep2()
{
}

void CDistillStep2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDistillStep2, CResizablePage)
END_MESSAGE_MAP()


// CDistillStep2 消息处理程序
