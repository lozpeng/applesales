// ScalebarMarkPage.cpp : 实现文件
//

#include "stdafx.h"
#include "ScalebarMarkPage.h"
#include "ISymbolListCtrl.h"

// CScalebarMarkPage 对话框

IMPLEMENT_DYNAMIC(CScalebarMarkPage, CPropertyPage)

CScalebarMarkPage::CScalebarMarkPage()
	: CPropertyPage(CScalebarMarkPage::IDD)
{
	m_pElement = NULL;
}

CScalebarMarkPage::~CScalebarMarkPage()
{
}

void CScalebarMarkPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CMB_NUM_FREQUENCY, m_cmbNumFreq);
	DDX_Control(pDX, IDC_CMB_NUM_POS, m_cmbNumPos);
	DDX_Text(pDX, IDC_EDIT_NUM_GAP, m_fNumGap);
	DDX_Control(pDX, IDC_BTN_NUM_TEXT_SYMBOL_PREVIEW, m_PreviewNumBtn);
	DDX_Control(pDX, IDC_CMB_MARK_FREQUENCY, m_cmbMarkFreq);
	DDX_Control(pDX, IDC_CMB_MARK_POS, m_cmbMarkPos);
	DDX_Text(pDX, IDC_EDIT_MAIN_DIVISION_HEIGHT, m_fMainDivH);
	DDX_Text(pDX, IDC_EDIT_SUB_DIVISION_HEIGHT, m_fSubDivH);
	DDX_Control(pDX, IDC_BTN_MARK_LINE_SYMBOL_PREVIEW, m_PreviewMarkBtn);
}


BEGIN_MESSAGE_MAP(CScalebarMarkPage, CPropertyPage)
	ON_BN_CLICKED(IDC_BTN_NUM_SYM_SET, &CScalebarMarkPage::OnBnClickedBtnNumTextSymbol)
	ON_BN_CLICKED(IDC_BTN_MARK_SYM_SET, &CScalebarMarkPage::OnBnClickedBtnMarkLineSymbol)
	ON_CBN_SELCHANGE(IDC_CMB_NUM_FREQUENCY, &CScalebarMarkPage::OnCbnSelchangeCmbNumFrequency)
	ON_CBN_SELCHANGE(IDC_CMB_NUM_POS, &CScalebarMarkPage::OnCbnSelchangeCmbNumPos)
	ON_EN_CHANGE(IDC_EDIT_NUM_GAP, &CScalebarMarkPage::OnEnChangeEditNumGap)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_NUM_GAP, &CScalebarMarkPage::OnDeltaposSpinNumGap)
	ON_CBN_SELCHANGE(IDC_CMB_MARK_FREQUENCY, &CScalebarMarkPage::OnCbnSelchangeCmbMarkFrequency)
	ON_CBN_SELCHANGE(IDC_CMB_MARK_POS, &CScalebarMarkPage::OnCbnSelchangeCmbMarkPos)
	ON_EN_CHANGE(IDC_EDIT_MAIN_DIVISION_HEIGHT, &CScalebarMarkPage::OnEnChangeEditMainDivisionHeight)
	ON_EN_CHANGE(IDC_EDIT_SUB_DIVISION_HEIGHT, &CScalebarMarkPage::OnEnChangeEditSubDivisionHeight)
END_MESSAGE_MAP()

void CScalebarMarkPage::SetElement(Element::IScaleBarPtr pScaleBar)
{
	m_pElement= pScaleBar;

	m_NumTextSymbol = m_pElement->GetNumTextSymbol();
	m_pMarkLineSymbol = m_pElement->GetMarkLineSymbol();

	if(this->m_hWnd)
		SetCtrls();
}

// CScalebarMarkPage 消息处理程序
BOOL CScalebarMarkPage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	
	return SetCtrls();
}

BOOL CScalebarMarkPage::SetCtrls()
{
	if(NULL == m_pElement)
		return FALSE;

	//num
	m_cmbNumFreq.AddString("无标注");
	m_cmbNumFreq.AddString("单个标注");
	m_cmbNumFreq.AddString("主分段");
	m_cmbNumFreq.AddString("所有分段");
	m_cmbNumFreq.AddString("主分段及第一个分段中点");
	m_cmbNumFreq.AddString("主分段及第一个次分段");
	m_cmbNumFreq.SetCurSel((int)m_pElement->GetNumFreq());

	m_cmbNumPos.AddString("比例尺之上");
	m_cmbNumPos.AddString("比例尺之下");
	m_cmbNumPos.SetCurSel((int)m_pElement->GetNumPos());

	m_fNumGap = m_pElement->GetNumGap();
	CSpinButtonCtrl	* pSpinNumGap = NULL;
	pSpinNumGap = (CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_NUM_GAP);
	if (pSpinNumGap)
		pSpinNumGap->SetRange(0, 1000);


	m_PreviewNumBtn.SetSymbol(m_NumTextSymbol.get());
	//mark
	m_cmbMarkFreq.AddString("无刻度");
	m_cmbMarkFreq.AddString("单个刻度");
	m_cmbMarkFreq.AddString("主分段");
	m_cmbMarkFreq.AddString("所有分段");
	m_cmbMarkFreq.AddString("主分段及第一个分段中点");
	m_cmbMarkFreq.AddString("主分段及第一个次分段");
	m_cmbMarkFreq.SetCurSel((int)m_pElement->GetMarkFreq());

	m_cmbMarkPos.AddString("比例尺之上");
	m_cmbMarkPos.AddString("比例尺之下");
	m_cmbMarkPos.AddString("比例尺之中");
	m_cmbMarkPos.SetCurSel((int)m_pElement->GetMarkPos());

	m_fMainDivH = m_pElement->GetDivMarkHeight();
	m_fSubDivH = m_pElement->GetSubDivMarkHeight();

	CSpinButtonCtrl	* pSpinMainDivH = NULL;
	pSpinMainDivH = (CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_MAIN_DIVISION_HEIGHT);
	if (pSpinMainDivH)
		pSpinMainDivH->SetRange(0, 1000);

	CSpinButtonCtrl	* pSpinSubDivH = NULL;
	pSpinSubDivH = (CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_SUB_DIVISION_HEIGHT);
	if (pSpinSubDivH)
		pSpinSubDivH->SetRange(0, 1000);

	m_PreviewMarkBtn.SetSymbol(m_pMarkLineSymbol.get());

	UpdateData(FALSE);

	return TRUE;
}
	
	
void CScalebarMarkPage::OnBnClickedBtnNumTextSymbol()
{
	// TODO: 在此添加控件通知处理程序代码
	Framework::ISymbolListCtrl *pCtrl =dynamic_cast<Framework::ISymbolListCtrl*>(Framework::IUIObject::GetUIObjectByName(Framework::CommonUIName::AppSymbolLstCtrl));
	if(pCtrl)
	{
		m_NumTextSymbol =pCtrl->SelectSymbol(m_NumTextSymbol);
		m_PreviewNumBtn.SetSymbol(m_NumTextSymbol.get());
	}
	SetModified();
}

void CScalebarMarkPage::OnBnClickedBtnMarkLineSymbol()
{
	// TODO: 在此添加控件通知处理程序代码
	Framework::ISymbolListCtrl *pCtrl =dynamic_cast<Framework::ISymbolListCtrl*>(Framework::IUIObject::GetUIObjectByName(Framework::CommonUIName::AppSymbolLstCtrl));
	if(pCtrl)
	{
		m_pMarkLineSymbol =pCtrl->SelectSymbol(m_pMarkLineSymbol);
		m_PreviewMarkBtn.SetSymbol(m_pMarkLineSymbol.get());
	}
	SetModified();
}

BOOL CScalebarMarkPage::OnApply()
{
	if(!IsWindow(m_hWnd))
		return FALSE;

	if (m_pElement == NULL)
		return FALSE;

	UpdateData();

	m_pElement->SetNumFreq((Element::LabelFrequency)m_cmbNumFreq.GetCurSel());
	m_pElement->SetNumPos((Element::NumPosition)m_cmbNumPos.GetCurSel());
	m_pElement->SetNumGap(m_fNumGap);
	m_pElement->SetNumTextSymbol(m_NumTextSymbol);

	m_pElement->SetMarkFreq((Element::LabelFrequency)m_cmbMarkFreq.GetCurSel());
	m_pElement->SetMarkPos((Element::MarkPosition)m_cmbMarkPos.GetCurSel());
	m_pElement->SetDivMarkHeight(m_fMainDivH);
	m_pElement->SetSubDivMarkHeight(m_fSubDivH);
	m_pElement->SetMarkLineSymbol(m_pMarkLineSymbol);

	SetModified(FALSE);

	return TRUE;
}

void CScalebarMarkPage::OnCbnSelchangeCmbNumFrequency()
{
	// TODO: 在此添加控件通知处理程序代码
	SetModified();	
}

void CScalebarMarkPage::OnCbnSelchangeCmbNumPos()
{
	// TODO: 在此添加控件通知处理程序代码
	SetModified();
}

void CScalebarMarkPage::OnEnChangeEditNumGap()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CPropertyPage::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	SetModified();
}

void CScalebarMarkPage::OnDeltaposSpinNumGap(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	SetModified();
}

void CScalebarMarkPage::OnCbnSelchangeCmbMarkFrequency()
{
	// TODO: 在此添加控件通知处理程序代码
	SetModified();
}

void CScalebarMarkPage::OnCbnSelchangeCmbMarkPos()
{
	// TODO: 在此添加控件通知处理程序代码
	SetModified();
}

void CScalebarMarkPage::OnEnChangeEditMainDivisionHeight()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CPropertyPage::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	SetModified();
}

void CScalebarMarkPage::OnEnChangeEditSubDivisionHeight()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CPropertyPage::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	SetModified();
}
