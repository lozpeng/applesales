// TransparentDLG.cpp : 实现文件
//

#include "stdafx.h"
#include "TransparentDLG.h"
#include "ILayer.h"


// CTransparentDLG 对话框

IMPLEMENT_DYNAMIC(CTransparentDLG, CDialog)

CTransparentDLG::CTransparentDLG(Type nameType/* = EHC_TRANS*/,CWnd* pParent /*=NULL*/)
	: CDialog(CTransparentDLG::IDD, pParent)
{
	m_sldPos=0;
	m_pMapCtrl=NULL;
	m_enumType = nameType;
	bShow = false;

}

CTransparentDLG::~CTransparentDLG()
{
}

void CTransparentDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER1, m_sldCtrl);
	DDX_Control(pDX, IDC_STATIC1, m_staticPos);
}


BEGIN_MESSAGE_MAP(CTransparentDLG, CDialog)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &CTransparentDLG::OnNMCustomdrawSlider)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER1, &CTransparentDLG::OnNMReleasedcaptureSlider)
	ON_WM_DESTROY()
	ON_WM_HSCROLL()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CTransparentDLG 消息处理程序

BOOL CTransparentDLG::OnInitDialog()
{
	if(!m_pLayer)
		return FALSE;

	if(!m_pMapCtrl)
		return FALSE;

	CDialog::OnInitDialog();

	m_boldVisual =m_pLayer->GetVisible();

	switch(m_enumType)
	{
	case EHC_TRANS:
		{
	       SetWindowText("透明度");
		   	m_sldPos = m_pLayer->GetTransparentValue();
			break;
		}
	case EHC_ALTERNATE:
		{
	       SetWindowText("闪烁");
		   	m_sldPos = 0;
			SetTimer(1,500,NULL);
			break;
		}
	default:
		break;
	}

	CString cs;
	cs.Format("%d%s", m_sldPos, "%");
	m_staticPos.SetWindowText(cs);
	m_sldCtrl.SetRange(0,100);
	m_sldCtrl.SetPos(m_sldPos);

	CenterWindow();	

	return TRUE;
}
void CTransparentDLG::OnNMCustomdrawSlider(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	CString cs;	
	cs.Format("%d%s", m_sldCtrl.GetPos(), "%");
	m_staticPos.SetWindowText(cs);
	UpdateData(FALSE);
	pResult = 0;
}
void CTransparentDLG::OnNMReleasedcaptureSlider(NMHDR *pNMHDR, LRESULT *pResult)
{
	*pResult = 0;
	CString cs;	
	cs.Format("%d%s", m_sldCtrl.GetPos(), "%");
	m_staticPos.SetWindowText(cs);
	int curPos = m_sldCtrl.GetPos();

	switch(m_enumType)
	{
	case EHC_TRANS:
		{
	       m_pLayer->SetTransparent(curPos);
			break;
		}
	case EHC_ALTERNATE:
		{
			KillTimer(1);
			int newtime = 5*curPos+500;
			SetTimer(1,newtime,NULL);
			break;
		}
	default:
		break;
	}
    
	m_pMapCtrl->UpdateControl(drawGeography);

	m_sldPos = m_sldCtrl.GetPos();
}

void CTransparentDLG::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	if (m_enumType == EHC_ALTERNATE)
	{
		bShow = !bShow;
		m_pLayer->SetVisible(bShow);
		m_pMapCtrl->UpdateControl(drawGeography);
	}

	CDialog::OnTimer(nIDEvent);
}


void CTransparentDLG::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{

	if (pScrollBar->GetDlgCtrlID() == IDC_SLIDER1)
	{

		switch(m_enumType)
		{
		case EHC_TRANS:
			{
				m_pLayer->SetTransparent(m_sldCtrl.GetPos());
				break;
			}
		//case EHC_ALTERNATE:
		//	{
		//		KillTimer(1);
		//		int newtime = 5*m_sldCtrl.GetPos()+500;
		//		SetTimer(1,newtime,NULL);
		//		break;
		//	}
		default:
			break;
		}

		m_pMapCtrl->UpdateControl(drawGeography);

	}

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CTransparentDLG::OnDestroy()
{
	CDialog::OnDestroy();

	if(m_enumType == EHC_ALTERNATE)
	{
		long lNumLayer = m_pMapCtrl->GetMap()->GetLayers().GetSize();

		/*for(long i= 0; i< lNumLayer; i++)
		{
			Carto::ILayerPtr pLayer = m_pMapCtrl->GetMap()->GetLayers().GetAt(i);
			pLayer->SetVisible(true);
		}*/
		m_pLayer->SetVisible(m_boldVisual);
	}

   	m_pMapCtrl->UpdateControl(drawGeography);
	KillTimer(1);
}

