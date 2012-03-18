// ElementFramePage.cpp : 实现文件
//

#include "stdafx.h"
#include "ElementFramePage.h"
#include "../CotSymbolList.h"


// CElementFramePage 对话框

IMPLEMENT_DYNAMIC(CElementFramePage, CPropertyPage)

CElementFramePage::CElementFramePage()
	: CPropertyPage(CElementFramePage::IDD)
{
	m_pElement = NULL;

	m_fBorderGapX = 0;
	m_fBorderGapY = 0;
	m_fBgGapX = 0;
	m_fBgGapY = 0;
	m_fShadowGapX = 0;
	m_fShadowGapY = 0;

	m_pBorder = NULL;
	m_pBg = NULL;
	m_pShadow = NULL;

	m_BorderSymbol = NULL;
	m_BgSymbol = NULL;
	m_ShadowSymbol = NULL;
}

CElementFramePage::~CElementFramePage()
{
}

void CElementFramePage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BORDER_PRIVIEW, m_PreviewBorderBtn);
	DDX_Text(pDX, IDC_EDIT_BORDER_X, m_fBorderGapX);
	DDX_Text(pDX, IDC_EDIT_BORDER_Y, m_fBorderGapY);
	DDX_Control(pDX, IDC_BG_PREVIEW, m_PreviewBgBtn);
	DDX_Text(pDX, IDC_EDIT_BG_X, m_fBgGapX);
	DDX_Text(pDX, IDC_EDIT_BG_Y, m_fBgGapY);
	DDX_Control(pDX, IDC_SHADOW_PREVIEW, m_PreviewShadowBtn);
	DDX_Text(pDX, IDC_EDIT_SHADOW_X, m_fShadowGapX);
	DDX_Text(pDX, IDC_EDIT_SHADOW_Y, m_fShadowGapY);
	DDX_Check(pDX, IDC_CHK_DRAW_BORDER, m_bDrawBorder);
	DDX_Check(pDX, IDC_CHK_DRAW_BG, m_bDrawBg);
	DDX_Check(pDX, IDC_CHK_DRAW_SHADOW, m_bDrawShadow);
	DDX_Check(pDX, IDC_CHK_DRAW_DRAFT, m_bDrawDraftMode);
}


BEGIN_MESSAGE_MAP(CElementFramePage, CPropertyPage)
	ON_BN_CLICKED(IDC_BORDER_SYMBOLSET, &CElementFramePage::OnBnClickedBtnBordersymbol)
	ON_BN_CLICKED(IDC_BG_SYMBOLSET, &CElementFramePage::OnBnClickedBtnBgsymbol)
	ON_BN_CLICKED(IDC_SHADOW_SYMBOLSET, &CElementFramePage::OnBnClickedBtnShadowsymbol)
	ON_BN_CLICKED(IDC_CHK_DRAW_BORDER, &CElementFramePage::OnBnClickedChkDrawBorder)
	ON_BN_CLICKED(IDC_CHK_DRAW_BG, &CElementFramePage::OnBnClickedChkDrawBg)
	ON_BN_CLICKED(IDC_CHK_DRAW_SHADOW, &CElementFramePage::OnBnClickedChkDrawShadow)
	ON_EN_CHANGE(IDC_EDIT_BORDER_Y, &CElementFramePage::OnEnChangeEditBorderY)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_BORDER_X, &CElementFramePage::OnDeltaposSpinBorderX)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_BORDER_Y, &CElementFramePage::OnDeltaposSpinBorderY)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_BG_X, &CElementFramePage::OnDeltaposSpinBgX)
	ON_EN_CHANGE(IDC_EDIT_BG_X, &CElementFramePage::OnEnChangeEditBgX)
	ON_EN_CHANGE(IDC_EDIT_BG_Y, &CElementFramePage::OnEnChangeEditBgY)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_BG_Y, &CElementFramePage::OnDeltaposSpinBgY)
	ON_EN_CHANGE(IDC_EDIT_SHADOW_X, &CElementFramePage::OnEnChangeEditShadowX)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_SHADOW_X, &CElementFramePage::OnDeltaposSpinShadowX)
	ON_EN_CHANGE(IDC_EDIT_SHADOW_Y, &CElementFramePage::OnEnChangeEditShadowY)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_SHADOW_Y, &CElementFramePage::OnDeltaposSpinShadowY)
	ON_BN_CLICKED(IDC_CHK_DRAW_DRAFT, &CElementFramePage::OnBnClickedChkDrawDraft)
END_MESSAGE_MAP()


// CElementFramePage 消息处理程序
void CElementFramePage::SetElement(Element::IFrameElementBasePtr pElement)
{
	m_pElement = pElement;

	m_pBorder = m_pElement->GetBorder();	
	m_BorderSymbol = m_pBorder->GetSymbol();
	m_pBg = m_pElement->GetBackground();
	m_BgSymbol = m_pBg->GetSymbol();
	m_pShadow = m_pElement->GetShadow();
	m_ShadowSymbol = m_pShadow->GetSymbol();

	if(this->m_hWnd)
		SetCtrls();
}

BOOL CElementFramePage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	SetCtrls();

	return TRUE;
}

void CElementFramePage::SetCtrls()
{
	if(!m_pElement)
		return;

	//border
	m_bDrawBorder = m_pElement->GetDrawBorder();
	m_PreviewBorderBtn.SetSymbol(m_BorderSymbol.get());
	m_pBorder->GetGap(m_fBorderGapX, m_fBorderGapY);
	CSpinButtonCtrl	* pSpinBorderX = NULL;
	pSpinBorderX = (CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_BORDER_X);
	if (pSpinBorderX)
		pSpinBorderX->SetRange(-1000, 1000);

	CSpinButtonCtrl	* pSpinBorderY = NULL;
	pSpinBorderY = (CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_BORDER_Y);
	if (pSpinBorderY)
		pSpinBorderY->SetRange(-1000, 1000);

	//background
	m_bDrawBg= m_pElement->GetDrawBackground();
	m_PreviewBgBtn.SetSymbol(m_BgSymbol.get());
	m_pBg->GetGap(m_fBgGapX, m_fBgGapY);

	CSpinButtonCtrl	* pSpinBgX = NULL;
	pSpinBgX = (CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_BG_X);
	if (pSpinBgX)
		pSpinBgX->SetRange(-1000, 1000);

	CSpinButtonCtrl	* pSpinBgY = NULL;
	pSpinBgY = (CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_BG_Y);
	if (pSpinBgY)
		pSpinBgY->SetRange(-1000, 1000);

	//shadow
	m_bDrawShadow = m_pElement->GetDrawShadow();
	m_PreviewShadowBtn.SetSymbol(m_ShadowSymbol.get());
	m_pShadow->GetGap(m_fShadowGapX, m_fShadowGapY);

	CSpinButtonCtrl	* pSpinShadowX = NULL;
	pSpinShadowX = (CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_SHADOW_X);
	if (pSpinShadowX)
		pSpinShadowX->SetRange(-1000, 1000);

	CSpinButtonCtrl	* pSpinShadowY = NULL;
	pSpinShadowY = (CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_SHADOW_Y);
	if (pSpinShadowY)
		pSpinShadowY->SetRange(-1000, 1000);

	//draft mode
	if(m_pElement->GetDrawMode() == Element::EDM_NORMAL)
		m_bDrawDraftMode = FALSE;
	else if(m_pElement->GetDrawMode() == Element::EDM_DRAFT)
		m_bDrawDraftMode = TRUE;

	UpdateData(FALSE);
	UpdateCtrl();
}

BOOL CElementFramePage::OnApply()
{
	if(!IsWindow(m_hWnd))
		return FALSE;

	UpdateData();

	if(m_bDrawBorder)
	{
		m_pBorder->SetSymbol(m_BorderSymbol);
		m_pBorder->SetGap(m_fBorderGapX, m_fBorderGapY);
		m_pElement->SetBorder(m_pBorder);
	}

	if(m_bDrawBg)
	{
		m_pBg->SetSymbol(m_BgSymbol);
		m_pBg->SetGap(m_fBgGapX, m_fBgGapY);
		m_pElement->SetBackground(m_pBg);
	}

	if(m_bDrawShadow)
	{
		m_pShadow->SetSymbol(m_ShadowSymbol);
		m_pShadow->SetGap(m_fShadowGapX, m_fShadowGapY);
		m_pElement->SetShadow(m_pShadow);
	}

	m_pElement->SetDrawBorder(m_bDrawBorder);
	m_pElement->SetDrawBackground(m_bDrawBg);
	m_pElement->SetDrawShadow(m_bDrawShadow);

	//draft mode
	if(m_bDrawDraftMode == FALSE)
		m_pElement->SetDrawMode(Element::EDM_NORMAL);
	else
		m_pElement->SetDrawMode(Element::EDM_DRAFT);

	//SetModified(FALSE);

	return TRUE;
}


void CElementFramePage::UpdateCtrl()
{
	GetDlgItem(IDC_BORDER_SYMBOLSET)->EnableWindow(m_bDrawBorder);
	GetDlgItem(IDC_SPIN_BORDER_X)->EnableWindow(m_bDrawBorder);
	GetDlgItem(IDC_SPIN_BORDER_Y)->EnableWindow(m_bDrawBorder);

	GetDlgItem(IDC_BG_SYMBOLSET)->EnableWindow(m_bDrawBg);
	GetDlgItem(IDC_SPIN_BG_X)->EnableWindow(m_bDrawBg);
	GetDlgItem(IDC_SPIN_BG_Y)->EnableWindow(m_bDrawBg);

	GetDlgItem(IDC_SHADOW_SYMBOLSET)->EnableWindow(m_bDrawShadow);
	GetDlgItem(IDC_SPIN_SHADOW_X)->EnableWindow(m_bDrawShadow);
	GetDlgItem(IDC_SPIN_SHADOW_Y)->EnableWindow(m_bDrawShadow);
}



void CElementFramePage::OnBnClickedBtnBordersymbol()
{
	otComUI::CotSymbolList symbollist;


	m_BorderSymbol =symbollist.SelectSymbol(m_pBorder->GetSymbol());
	m_PreviewBorderBtn.SetSymbol(m_BorderSymbol.get());
	SetModified();
	

}

void CElementFramePage::OnBnClickedBtnBgsymbol()
{
	otComUI::CotSymbolList symbollist;


	m_BgSymbol =symbollist.SelectSymbol(m_pBg->GetSymbol());
	m_PreviewBgBtn.SetSymbol(m_BgSymbol.get());
	SetModified();
	
}

void CElementFramePage::OnBnClickedBtnShadowsymbol()
{
	otComUI::CotSymbolList symbollist;


	m_ShadowSymbol =symbollist.SelectSymbol(m_pShadow->GetSymbol());
	
	m_PreviewShadowBtn.SetSymbol(m_ShadowSymbol.get());
	SetModified();
	
}

void CElementFramePage::OnBnClickedChkDrawBorder()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	UpdateCtrl();
	SetModified();
}

void CElementFramePage::OnBnClickedChkDrawBg()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	UpdateCtrl();
	SetModified();
}

void CElementFramePage::OnBnClickedChkDrawShadow()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	UpdateCtrl();
	SetModified();
}


void CElementFramePage::OnEnChangeEditBorderY()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CPropertyPage::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	SetModified();
}

void CElementFramePage::OnDeltaposSpinBorderX(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	SetModified();
}

void CElementFramePage::OnDeltaposSpinBorderY(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	SetModified();
}

void CElementFramePage::OnDeltaposSpinBgX(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	SetModified();
}

void CElementFramePage::OnEnChangeEditBgX()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CPropertyPage::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	SetModified();
}

void CElementFramePage::OnEnChangeEditBgY()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CPropertyPage::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	SetModified();
}

void CElementFramePage::OnDeltaposSpinBgY(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	SetModified();
}

void CElementFramePage::OnEnChangeEditShadowX()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CPropertyPage::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	SetModified();
}

void CElementFramePage::OnDeltaposSpinShadowX(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	SetModified();
}

void CElementFramePage::OnEnChangeEditShadowY()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CPropertyPage::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	SetModified();
}

void CElementFramePage::OnDeltaposSpinShadowY(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	SetModified();
}

void CElementFramePage::OnBnClickedChkDrawDraft()
{
	// TODO: 在此添加控件通知处理程序代码
	SetModified();
}
