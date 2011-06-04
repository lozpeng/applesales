// DistillStep1.cpp : 实现文件
//

#include "stdafx.h"
#include "Control.h"
#include "DistillStep1.h"


// CDistillStep1 对话框

IMPLEMENT_DYNAMIC(CDistillStep1, CResizablePage)

CDistillStep1::CDistillStep1(CWnd* pParent /*=NULL*/)
	: CResizablePage(CDistillStep1::IDD)
{
	//m_psp.dwFlags &= (~PSP_HASHELP);
	m_psp.dwFlags |= PSP_USEHICON;
	HICON hIconTab = AfxGetApp()->LoadIcon(IDI_STEP1);
	m_psp.hIcon = hIconTab;
	m_pMapControl = NULL;
}

CDistillStep1::~CDistillStep1()
{
}

void CDistillStep1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDistillStep1, CResizablePage)
	ON_BN_CLICKED(IDC_BUTTON_POLYGON, &CDistillStep1::OnBnClickedButtonPolygon)
END_MESSAGE_MAP()


// CDistillStep1 消息处理程序

void CDistillStep1::OnBnClickedButtonPolygon()
{
	// TODO: 在此添加控件通知处理程序代码
	Framework::ITool* pTool = NULL;
	m_pMapControl->SetCurTool("DiTillTool");
	pTool=Framework::ITool::FindTool("DiTillTool");
	//设置目标图层和阈值
	if(pTool)
	{
		pTool->Initialize(dynamic_cast<Framework::IUIObject*>(m_pMapControl));
	}
}
