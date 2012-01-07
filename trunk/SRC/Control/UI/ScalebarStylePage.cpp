// ScalebarStylePage.cpp : 实现文件
//

#include "stdafx.h"
#include "ScalebarStylePage.h"
#include "ISymbolListCtrl.h"
#include "ScaleBarProperSheet.h"
#include "MapFrame.h"
#include "AlternatingScaleBar.h"
#include "ScaleLine.h"
#include "ILayoutCtrl.h"
// CScalebarStylePage 对话框

IMPLEMENT_DYNAMIC(CScalebarStylePage, CPropertyPage)

CScalebarStylePage::CScalebarStylePage()
	: CPropertyPage(CScalebarStylePage::IDD)
{
	m_pForeSymbol = NULL;
	m_pBackSymbol = NULL;
	m_pElement = NULL;
}

CScalebarStylePage::~CScalebarStylePage()
{
}

void CScalebarStylePage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CMB_SCALEBAR_STYLE, m_cmbScalebarStyle);
	DDX_Control(pDX, IDC_BTN_TEXT_SYMBOL, m_PreviewTextBtn);
	DDX_Control(pDX, IDC_BTN_FORE_FILL_SYMBOL, m_PreviewForeBtn);
	DDX_Control(pDX, IDC_BTN_BACK_FILL_SYMBOL, m_PreviewBackBtn);
}


BEGIN_MESSAGE_MAP(CScalebarStylePage, CPropertyPage)
	ON_BN_CLICKED(IDC_BTN_SET_TEXT_SYMBOL, &CScalebarStylePage::OnBnClickedBtnSetTextSymbol)
	ON_BN_CLICKED(IDC_BTN_SET_FORE_FILL_SYMBOL, &CScalebarStylePage::OnBnClickedBtnSetForeFillSymbol)
	ON_BN_CLICKED(IDC_BTN_SET_FILL_BACK_SYMBOL, &CScalebarStylePage::OnBnClickedBtnSetFillBackSymbol)
	ON_CBN_SELCHANGE(IDC_CMB_SCALEBAR_STYLE, &CScalebarStylePage::OnCbnSelchangeCmbScalebarStyle)
END_MESSAGE_MAP()

void CScalebarStylePage::SetElement(Element::IScaleBarPtr pScaleBar)
{
	m_pElement= pScaleBar;

	m_ScaleBarType = m_pElement->GetType();

	m_pTextSymbol = m_pElement->GetTextSymbol();

	m_pForeSymbol = m_pElement->GetForeSymbol();

	m_pBackSymbol = m_pElement->GetBackSymbol();

	if(this->m_hWnd)
		SetCtrls();
}

// CScalebarStylePage 消息处理程序
BOOL CScalebarStylePage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	return SetCtrls();
}

BOOL CScalebarStylePage::SetCtrls()
{
	if(m_pElement == NULL)
		return FALSE;

	m_PreviewTextBtn.SetSymbol(m_pTextSymbol.get());

	if(!m_pForeSymbol)
	{
		m_PreviewForeBtn.EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_SET_TEXT_SYMBOL)->EnableWindow(FALSE);
	}
	else
	{
		m_PreviewForeBtn.SetSymbol(m_pForeSymbol.get());
	}

	if(!m_pBackSymbol)
	{
		m_PreviewBackBtn.EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_SET_TEXT_SYMBOL)->EnableWindow(FALSE);
	}
	else
	{
		m_PreviewBackBtn.SetSymbol(m_pBackSymbol.get());
	}

	m_cmbScalebarStyle.AddString("单段交替比例尺");
	m_cmbScalebarStyle.AddString("单线比例尺");
	switch(m_ScaleBarType)
	{
	case Element::ET_ALTERNATING_SCALEBAR:
		m_cmbScalebarStyle.SetCurSel(0);
		break;
	case Element::ET_SCALELINE:
		m_cmbScalebarStyle.SetCurSel(1);
		break;
	default:
		break;
	}

	UpdateData(FALSE);
	return TRUE;
}

BOOL CScalebarStylePage::OnApply()
{
	if(!IsWindow(m_hWnd))
		return FALSE;

	if (m_pElement == NULL)
		return FALSE;


	UpdateData();

	if(m_pTextSymbol)
		m_pElement->SetTextSymbol(m_pTextSymbol);

	if(m_pForeSymbol)
		m_pElement->SetForeSymbol(m_pForeSymbol);

	if(m_pBackSymbol)
		m_pElement->SetBackSymbol(m_pBackSymbol);

	switch(m_cmbScalebarStyle.GetCurSel())
	{
	case 0:
		m_ScaleBarType = Element::ET_ALTERNATING_SCALEBAR;
		break;
	case 1:
		m_ScaleBarType = Element::ET_SCALELINE;
		break;
	default:
		break;
	}


	Element::CMapFrame* pMapFrm = m_pElement->GetMapFrame();
	if(m_pElement->GetType() != m_ScaleBarType)
	{
		Element::IScaleBarPtr pNewScaleBar;
		switch(m_ScaleBarType)
		{
		case Element::ET_ALTERNATING_SCALEBAR:
			pNewScaleBar = Element::CAlternatingScaleBarPtr(new Element::CAlternatingScaleBar(*m_pElement->GetGeometry(), pMapFrm));
			break;
		case Element::ET_SCALELINE:
			pNewScaleBar = Element::CScaleLinePtr(new Element::CScaleLine(*m_pElement->GetGeometry(), pMapFrm));
			break;
		default:
			break;
		}

		Framework::ILayoutCtrl *pLayoutCtrl =Framework::ILayoutCtrl::GetActiveLayoutCtrl();
		if(!pLayoutCtrl)
			return FALSE;

		Carto::CPageLayoutPtr pPageLayout = pLayoutCtrl->GetPageLayout();
		if(!pPageLayout)
			return FALSE;

		Carto::CGraphicLayerPtr pLayer = pPageLayout->GetGraphicLayer();
		if(!pPageLayout)
			return FALSE;

		pLayer->RemoveElement(m_pElement);
		pLayer->AddElement(pNewScaleBar);
		m_pElement = pNewScaleBar;

		pLayer->UnselectAllElements();
		pLayer->SelectElement(m_pElement);
		m_pSheet->SetElement(m_pElement);
	}

	return TRUE;
}
void CScalebarStylePage::OnBnClickedBtnSetTextSymbol()
{
	// TODO: 在此添加控件通知处理程序代码
	Framework::ISymbolListCtrl *pCtrl =dynamic_cast<Framework::ISymbolListCtrl*>(Framework::IUIObject::GetUIObjectByName(Framework::CommonUIName::AppSymbolLstCtrl));
	if(pCtrl)
	{
		m_pTextSymbol =pCtrl->SelectSymbol(m_pTextSymbol);
		m_PreviewTextBtn.SetSymbol(m_pTextSymbol.get());
	}
	SetModified();
}

void CScalebarStylePage::OnBnClickedBtnSetForeFillSymbol()
{
	// TODO: 在此添加控件通知处理程序代码
	Framework::ISymbolListCtrl *pCtrl =dynamic_cast<Framework::ISymbolListCtrl*>(Framework::IUIObject::GetUIObjectByName(Framework::CommonUIName::AppSymbolLstCtrl));
	if(pCtrl)
	{
		m_pForeSymbol =pCtrl->SelectSymbol(m_pForeSymbol);
		m_PreviewForeBtn.SetSymbol(m_pForeSymbol.get());
	}

	SetModified();
}

void CScalebarStylePage::OnBnClickedBtnSetFillBackSymbol()
{
	// TODO: 在此添加控件通知处理程序代码
	Framework::ISymbolListCtrl *pCtrl =dynamic_cast<Framework::ISymbolListCtrl*>(Framework::IUIObject::GetUIObjectByName(Framework::CommonUIName::AppSymbolLstCtrl));
	if(pCtrl)
	{
		m_pBackSymbol =pCtrl->SelectSymbol(m_pBackSymbol);
		m_PreviewBackBtn.SetSymbol(m_pBackSymbol.get());
	}

	SetModified();
}

void CScalebarStylePage::OnCbnSelchangeCmbScalebarStyle()
{
	// TODO: 在此添加控件通知处理程序代码
	SetModified();
}
