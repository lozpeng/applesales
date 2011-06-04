// DistillStep1.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Control.h"
#include "DistillStep1.h"


// CDistillStep1 �Ի���

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


// CDistillStep1 ��Ϣ�������

void CDistillStep1::OnBnClickedButtonPolygon()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	Framework::ITool* pTool = NULL;
	m_pMapControl->SetCurTool("DiTillTool");
	pTool=Framework::ITool::FindTool("DiTillTool");
	//����Ŀ��ͼ�����ֵ
	if(pTool)
	{
		pTool->Initialize(dynamic_cast<Framework::IUIObject*>(m_pMapControl));
	}
}
