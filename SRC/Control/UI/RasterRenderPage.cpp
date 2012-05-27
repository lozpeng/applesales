#include "stdafx.h"

#include "RasterRenderPage.h"
#include "SimpleRenderPage.h"
#include "RasterLayer.h"
#include "UniqueRenderPage.h"
#include "ClassifyColorRenderPage.h"


BOOL CCustomPane_R::OnSendCommand(const CBCGPToolbarButton *pButton)
{
	
	CWaitCursor wait;
	m_pParent->SetActivePage (ButtonToIndex (pButton));
    
	return TRUE;
}

void CCustomPane_R::EnsureVisible (int iButton)
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
// CCommonPropPage 对话框

IMPLEMENT_DYNCREATE(CRasterRenderPage, CPropertyPage)

CRasterRenderPage::CRasterRenderPage()
: CPropertyPage(CRasterRenderPage::IDD)

{
	m_psp.dwFlags &= ~PSP_HASHELP;

	m_pLayer = NULL;

	m_nActivePage=-1;
}

CRasterRenderPage::~CRasterRenderPage()
{
	for(size_t i=0;i<m_pages.size();i++)
	{
		delete m_pages[i];
	}
	m_pages.clear();
}


void CRasterRenderPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	

}


BEGIN_MESSAGE_MAP(CRasterRenderPage, CPropertyPage)
	
END_MESSAGE_MAP()


BOOL CRasterRenderPage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	if(!m_pLayer)
	{
		return FALSE;
	}

	m_icons.Create( IDB_FEATURE_RENDER, 32, 1, RGB(0,0,0) );
    
	//创建选项面板
	CreateImageCtrl();
    //添加专题按钮
	AddImageButtons();


	//调整控件的位置
	CRect BarRect,rect;
	GetClientRect(rect);
	BarRect =rect;
	BarRect.right =BarRect.left+100;
	m_wndOutlookBar.SetWindowPos(NULL,BarRect.left,BarRect.top,BarRect.Width(),BarRect.Height(),SWP_NOACTIVATE);
	
    GetDlgItem(IDC_RENDER_PAGE_CONTAINER)->SetWindowPos(NULL,BarRect.right+1,BarRect.top,rect.Width()-BarRect.Width()-2,rect.Height(),SWP_NOACTIVATE);

	long Rendertype =((Carto::CRasterLayer*)m_pLayer)->GetRender()->GetRenderType();

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

void CRasterRenderPage::CreateImageCtrl()
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

	//m_wndPane.SetBackImage(IDB_RENDER_BG);

    
}

void CRasterRenderPage::AddImageButtons()
{
	////简单图例按钮
 //   CSimpleRenderPage *simplePage = new CSimpleRenderPage();
	//simplePage->SetLayer(m_pLayer);
	//m_pages.push_back(simplePage);
	//HICON hIcon = m_icons.ExtractIcon (0);
	//m_wndPane.AddButton (hIcon, "简单专题", 0, -1, 0);
	//::DestroyIcon (hIcon);

	////唯一值图例
	//CUniqueRenderPage *uniPage =new CUniqueRenderPage();
	//uniPage->SetLayer(m_pLayer);
	//m_pages.push_back(uniPage);
	//hIcon = m_icons.ExtractIcon (1);
	//m_wndPane.AddButton (hIcon, "唯一值专题", 0, -1, 0);
	//::DestroyIcon (hIcon);

	//范围图例
	CClassifyColorPage *rangePage = new CClassifyColorPage();
	rangePage->SetLayer(m_pLayer);
	m_pages.push_back(rangePage);
	HICON hIcon = m_icons.ExtractIcon (1);
	m_wndPane.AddButton (hIcon, "范围专题", 0, -1, 0);
	::DestroyIcon (hIcon);

	
}

void CRasterRenderPage::SetActivePage(int index)
{
	//如果不是点中当前页,则创建新页
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

void CRasterRenderPage::SetLayer(Carto::ILayer* layer)
{
	m_pLayer = layer;
}

BOOL CRasterRenderPage::OnApply()
{
	if(m_nActivePage>=0 && m_pLayer)
	{
		dynamic_cast<Carto::CRasterLayer*>(m_pLayer)->SetRender(m_pages[m_nActivePage]->GetRasterRender());
	}
	return TRUE;
}