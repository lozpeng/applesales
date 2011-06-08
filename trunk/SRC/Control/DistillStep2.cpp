// DistillStep2.cpp : 实现文件
//

#include "stdafx.h"
#include "Control.h"
#include "DistillStep2.h"


// CDistillStep2 对话框

IMPLEMENT_DYNAMIC(CDistillStep2, CResizablePage)

CDistillStep2::CDistillStep2(CWnd* pParent /*=NULL*/)
: CResizablePage(CDistillStep2::IDD)
, m_dTol(0.2)
, m_nMinArea(10)
{
	//m_psp.dwFlags &= (~PSP_HASHELP);
	m_psp.dwFlags |= PSP_USEHICON;
	HICON hIconTab = AfxGetApp()->LoadIcon(IDI_STEP2);
	m_psp.hIcon = hIconTab;
	m_pTargetLyr = NULL;
}

CDistillStep2::~CDistillStep2()
{
}

void CDistillStep2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_TOLL, m_dTol);
	DDV_MinMaxDouble(pDX, m_dTol, 0, 1);
	DDX_Text(pDX, IDC_EDIT_MINAREA, m_nMinArea);
	DDV_MinMaxInt(pDX, m_nMinArea, 1, 100000000);
}


BEGIN_MESSAGE_MAP(CDistillStep2, CResizablePage)
END_MESSAGE_MAP()


// CDistillStep2 消息处理程序

BOOL CDistillStep2::OnApply()
{
	// TODO: 在此添加专用代码和/或调用基类

	return __super::OnApply();
}


void CDistillStep2::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	__super::OnOK();
}

int CDistillStep2::DoWork()
{
	UpdateData();
	if(m_nMinArea<1)
	{
        MessageBox("阈值不能小于1","提示",MB_OK);
		return 0;
	}
    return 1;

}
