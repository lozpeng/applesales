#include "stdafx.h"

#include "FeatureRenderPage.h"
#include "SimpleRenderPage.h"
#include "FeatureLayer.h"
#include "UniqueRenderPage.h"
#include "RangeRenderPage.h"

BOOL CCustomPane::OnSendCommand(const CBCGPToolbarButton *pButton)
{
	
	CWaitCursor wait;
	m_pParent->SetActivePage (ButtonToIndex (pButton));
    
	return TRUE;
}

void CCustomPane::EnsureVisible (int iButton)
{


	CBCGPToolbarButton* pButton = GetButton (iButton);


	CRect rectButton = pButton->Rect ();

	CRect rectWork;
	GetClientRect (rectWork);

	if (rectButton.Height () >= rectWork.Height ())
	{
		// Work area is too small, nothing to do
		return;
	}

	if (rectButton.top >= rectWork.top && rectButton.bottom <= rectWork.bottom)
	{
		// Already visible
		return;
	}

	if (rectButton.top < rectWork.top)
	{
		while (pButton->Rect ().top < rectWork.top)
		{
			int iScrollOffset = m_iScrollOffset;

			ScrollUp ();

			if (iScrollOffset == m_iScrollOffset)
			{
				break;
			}
		}
	}
	else
	{
		while (pButton->Rect ().bottom > rectWork.bottom)
		{
			int iScrollOffset = m_iScrollOffset;

			ScrollDown ();

			if (iScrollOffset == m_iScrollOffset)
			{
				break;
			}
		}
	}
}
// CCommonPropPage �Ի���

IMPLEMENT_DYNCREATE(CFeatureRenderPage, CPropertyPage)

CFeatureRenderPage::CFeatureRenderPage()
: CPropertyPage(CFeatureRenderPage::IDD)

{
	m_psp.dwFlags &= ~PSP_HASHELP;

	m_pLayer = NULL;

	m_nActivePage=-1;
}

CFeatureRenderPage::~CFeatureRenderPage()
{
	for(size_t i=0;i<m_pages.size();i++)
	{
		delete m_pages[i];
	}
	m_pages.clear();
}


void CFeatureRenderPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	

}


BEGIN_MESSAGE_MAP(CFeatureRenderPage, CPropertyPage)
	
END_MESSAGE_MAP()


BOOL CFeatureRenderPage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	if(!m_pLayer)
	{
		return FALSE;
	}

	m_icons.Create( IDB_FEATURE_RENDER, 24, 1, RGB(0,0,0) );
    
	//����ѡ�����
	CreateImageCtrl();
    //���ר�ⰴť
	AddImageButtons();


	//�����ؼ���λ��
	CRect BarRect,rect;
	GetClientRect(rect);
	BarRect =rect;
	BarRect.right =BarRect.left+100;
	m_wndOutlookBar.SetWindowPos(NULL,BarRect.left,BarRect.top,BarRect.Width(),BarRect.Height(),SWP_NOACTIVATE);
	
    GetDlgItem(IDC_RENDER_PAGE_CONTAINER)->SetWindowPos(NULL,BarRect.right+1,BarRect.top,rect.Width()-BarRect.Width()-2,rect.Height(),SWP_NOACTIVATE);

	long Rendertype =((Carto::CFeatureLayer*)m_pLayer)->GetFeatureRender()->GetRenderType();

	bool bfit =false;
	for(size_t i=0;i<m_pages.size();i++)
	{
		if(Rendertype==m_pages[i]->GetRenderType())
		{
             SetActivePage(i);
			 bfit =true;
			 break;

		}
	}
	if(!bfit)
	{
       SetActivePage(0);
	}

	return TRUE;
}

void CFeatureRenderPage::CreateImageCtrl()
{
	DWORD dwStyle = WS_CHILD | WS_VISIBLE | CBRS_ALIGN_LEFT;
	DWORD dwBCGStyle = 0;
	m_wndOutlookBar.Create (_T(""), this, CRect (0, 0, 100, 100), 
		AFX_IDW_TOOLBAR, dwStyle, dwBCGStyle);

	CBCGPBaseTabWnd* pWndTab = m_wndOutlookBar.GetUnderlinedWindow ();

	pWndTab->HideSingleTab ();

	m_wndPane.Create (&m_wndOutlookBar, dwDefaultToolbarStyle, 1);

	m_wndPane.m_pParent =this;
	
	m_wndOutlookBar.AddTab (&m_wndPane);

	m_wndPane.EnableTextLabels (TRUE);
	m_wndPane.SetOwner (this);

	m_wndPane.SetBackImage(IDB_RENDER_BG);

    
}

void CFeatureRenderPage::AddImageButtons()
{
    CSimpleRenderPage *simplePage = new CSimpleRenderPage();
	simplePage->SetLayer(m_pLayer);
	m_pages.push_back(simplePage);
	//��ͼ����ť
	HICON hIcon = m_icons.ExtractIcon (0);
	m_wndPane.AddButton (hIcon, "����Ⱦ", 0, -1, 0);
	::DestroyIcon (hIcon);

	CUniqueRenderPage *uniPage =new CUniqueRenderPage();
	uniPage->SetLayer(m_pLayer);
	m_pages.push_back(uniPage);
	//Ψһֵͼ��
	hIcon = m_icons.ExtractIcon (1);
	m_wndPane.AddButton (hIcon, "Ψһֵ��Ⱦ", 0, -1, 0);
	::DestroyIcon (hIcon);

	//��Χͼ��
	CRangeRenderPage *rangePage =new CRangeRenderPage();
	rangePage->SetLayer(m_pLayer);
	m_pages.push_back(rangePage);
	//Ψһֵͼ��
	hIcon = m_icons.ExtractIcon (2);
	m_wndPane.AddButton (hIcon, "�ּ���Ⱦ", 0, -1, 0);
	::DestroyIcon (hIcon);
}

void CFeatureRenderPage::SetActivePage(int index)
{
	//������ǵ��е�ǰҳ,�򴴽���ҳ
	if(index!=m_nActivePage)
	{
        if(m_nActivePage>=0)
		{
			dynamic_cast<CWnd*>(m_pages[m_nActivePage])->DestroyWindow();
		}
        CRect rect;

		GetDlgItem(IDC_RENDER_PAGE_CONTAINER)->GetWindowRect( &rect );
		ScreenToClient( &rect );

		if(m_pages[index]->CreateDlg(this))
		{
             CDialog *pdlg =dynamic_cast<CDialog*>(m_pages[index]);
			 pdlg->SetWindowPos(NULL, rect.left, rect.top, 0, 0,
				 SWP_NOZORDER | SWP_NOSIZE | SWP_NOACTIVATE );
			 pdlg->ShowWindow(SW_SHOW); 

		}
        m_nActivePage =index;
		
		
		
        
	}
	if (index >= 0)
	{
		if (m_wndPane.GetSafeHwnd () != NULL)
		{
			m_wndPane.SetButtonStyle (index, TBBS_CHECKED);
			
		}
	}
}

void CFeatureRenderPage::SetLayer(Carto::ILayer* layer)
{
	m_pLayer = layer;
}

BOOL CFeatureRenderPage::OnApply()
{
	if(m_nActivePage>=0 && m_pLayer)
	{
		dynamic_cast<Carto::CFeatureLayer*>(m_pLayer)->SetFeatureRender(m_pages[m_nActivePage]->GetRender());
	}
	return TRUE;
}