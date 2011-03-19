// EnhanceSld.cpp : 实现文件
//

#include "stdafx.h"
//#include "otUI.h"
#include "DlgSwipeSld.h"
#include "Resource.h"


// CEnhanceSld 对话框

IMPLEMENT_DYNAMIC(CEnhanceSld, CDialog)

CEnhanceSld::CEnhanceSld(CWnd* pParent /*=NULL*/)
	: CDialog(CEnhanceSld::IDD, pParent)
{
	m_sldPos = 0;
	m_enhanceName = "";
	m_pDC1 = NULL;
	m_pDC2 = NULL;
}

CEnhanceSld::~CEnhanceSld()
{
}

void CEnhanceSld::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER1, m_sldCtrl);
	DDX_Control(pDX, IDC_STATIC1, m_staticPos);
	DDX_Control(pDX, IDC_RADIO_LR, m_rdLR);
}


BEGIN_MESSAGE_MAP(CEnhanceSld, CDialog)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &CEnhanceSld::OnNMCustomdrawSlider)
	ON_BN_CLICKED(IDC_RADIO_LR, &CEnhanceSld::OnBnClickedRadioLr)
	ON_BN_CLICKED(IDC_RADIO_UD, &CEnhanceSld::OnBnClickedRadioUd)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER1, &CEnhanceSld::OnNMReleasedcaptureSlider1)
	ON_WM_TIMER()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CEnhanceSld 消息处理程序
BOOL CEnhanceSld:: OnInitDialog()
{
	CDialog::OnInitDialog();

	m_enhanceName="卷帘";
	CString cs;
	cs.Format("%d%s", m_sldPos, "%");
	m_staticPos.SetWindowText(cs);
	SetWindowText(m_enhanceName);
	m_sldCtrl.SetRange(0,100);
	m_sldCtrl.SetPos(m_sldPos);
	m_sldPos=0;

	CenterWindow();	

	GetDlgItem(IDC_RADIO_LR)->ShowWindow(TRUE);
	GetDlgItem(IDC_RADIO_UD)->ShowWindow(TRUE);
	m_rdLR.SetCheck(BST_CHECKED);

	//SetTimer(1,500,NULL);

	return TRUE;
}
void CEnhanceSld::OnNMCustomdrawSlider(NMHDR *pNMHDR, LRESULT *pResult)
{
	CString cs;	
	cs.Format("%d%s", m_sldCtrl.GetPos(), "%");
	m_staticPos.SetWindowText(cs);

	int startx=0, starty=0;
	int rectWidth1=0, rectHeight1=0;
	int rectWidth2=0, rectHeight2=0;
	int curPos = m_sldCtrl.GetPos();

	if(m_rdLR.GetCheck()==BST_CHECKED)
	{
		startx=m_drawRect.left+curPos*m_drawRect.Width()/100;
		starty=m_drawRect.top;
		rectWidth1=m_drawRect.Width()-curPos*m_drawRect.Width()/100;
		rectHeight1=m_drawRect.Height();
		rectWidth2=startx;
		rectHeight2=m_drawRect.Height();
	}
	else
	{
		startx = m_drawRect.left;
		starty = m_drawRect.top + curPos * m_drawRect.Height()/100;
		rectWidth1 = m_drawRect.Width();
		rectHeight1 = m_drawRect.Height() - curPos * m_drawRect.Height()/100 ;
		rectWidth2 = m_drawRect.Width();
		rectHeight2 = starty;
	}
	
	m_hdc1=m_pDC1->GetSafeHdc();
    m_hdc2=m_pDC2->GetSafeHdc();
	m_hClientDC=m_pMap->GetClientDC();
	
	::BitBlt(m_hClientDC,startx, starty, rectWidth2, rectHeight2, m_hdc1, startx, starty,SRCCOPY);

	::BitBlt(m_hClientDC,0, 0, rectWidth2, rectHeight2, m_hdc2, 0, 0,SRCCOPY);

	UpdateData(FALSE);
	pResult = 0;

	
}
void CEnhanceSld::OnBnClickedRadioLr()
{
	CString cs;
	m_sldCtrl.SetPos(0);	
	cs.Format("%d%s", m_sldCtrl.GetPos(), "%");
	m_staticPos.SetWindowText(cs);
	m_rdLR.SetCheck(BST_CHECKED);
	::BitBlt(m_hClientDC,0, 0, m_drawRect.Width(), m_drawRect.Height(), m_hdc1, 0, 0,SRCCOPY);
}
void CEnhanceSld::OnBnClickedRadioUd()
{
	CString cs;
	m_sldCtrl.SetPos(0);	
	cs.Format("%d%s", m_sldCtrl.GetPos(), "%");
	m_staticPos.SetWindowText(cs);
	m_rdLR.SetCheck(BST_UNCHECKED);
	::BitBlt(m_hClientDC,0, 0, m_drawRect.Width(), m_drawRect.Height(), m_hdc1, 0, 0,SRCCOPY);
}
void CEnhanceSld::OnNMReleasedcaptureSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	*pResult = 0;
	CString cs;	
	cs.Format("%d%s", m_sldCtrl.GetPos(), "%");
	m_staticPos.SetWindowText(cs);
	//DoProcess();
	m_sldPos = m_sldCtrl.GetPos();
}
void CEnhanceSld::OnTimer(UINT_PTR nIDEvent)
{
	CDialog::OnTimer(nIDEvent);
}
void CEnhanceSld::OnDestroy()
{
	CDialog::OnDestroy();
	KillTimer(1);
}