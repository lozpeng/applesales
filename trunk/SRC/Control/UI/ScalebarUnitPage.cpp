// ScalebarUnitPage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ScalebarUnitPage.h"
#include "ISymbolListCtrl.h"

// CScalebarUnitPage �Ի���

IMPLEMENT_DYNAMIC(CScalebarUnitPage, CPropertyPage)

CScalebarUnitPage::CScalebarUnitPage()
	: CPropertyPage(CScalebarUnitPage::IDD)
{
	m_pElement = NULL;
}

CScalebarUnitPage::~CScalebarUnitPage()
{
}

void CScalebarUnitPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_MAIN_DIVISION_NUM, m_nNumDiv);
	DDX_Text(pDX, IDC_EDIT_SUB_DIVISION_NUM, m_nNumSubDiv);
	DDX_Check(pDX, IDC_CHK_DIVISION_BF_ZERO, m_bDivBfZero);
	DDX_Control(pDX, IDC_COMBO_UNIT, m_cmbUnit);
	DDX_Control(pDX, IDC_COMBO_UNIT_POS, m_cmbUnitPos);
	DDX_Text(pDX, IDC_EDITUNIT_GAP, m_fUnitGap);
	DDX_Control(pDX, IDC_BTN_SET_SYMBOL, m_PreviewUnitBtn);
}


BEGIN_MESSAGE_MAP(CScalebarUnitPage, CPropertyPage)
	ON_BN_CLICKED(IDC_BTN_SET_UNIT_SYMBOL, &CScalebarUnitPage::OnBnClickedBtnSetUnitSymbol)
	ON_EN_CHANGE(IDC_EDIT_MAIN_DIVISION_NUM, &CScalebarUnitPage::OnEnChangeEditMainDivisionNum)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_MAIN_DIVISION_NUM, &CScalebarUnitPage::OnDeltaposSpinMainDivisionNum)
	ON_EN_CHANGE(IDC_EDIT_SUB_DIVISION_NUM, &CScalebarUnitPage::OnEnChangeEditSubDivisionNum)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_SUB_DIVISION_NUM, &CScalebarUnitPage::OnDeltaposSpinSubDivisionNum)
	ON_BN_CLICKED(IDC_CHK_DIVISION_BF_ZERO, &CScalebarUnitPage::OnBnClickedChkDivisionBfZero)
	ON_CBN_SELCHANGE(IDC_COMBO_UNIT, &CScalebarUnitPage::OnCbnSelchangeComboUnit)
	ON_CBN_SELCHANGE(IDC_COMBO_UNIT_POS, &CScalebarUnitPage::OnCbnSelchangeComboUnitPos)
	ON_EN_CHANGE(IDC_EDITUNIT_GAP, &CScalebarUnitPage::OnEnChangeEditunitGap)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_UNIT_GAP, &CScalebarUnitPage::OnDeltaposSpinUnitGap)
END_MESSAGE_MAP()

void CScalebarUnitPage::SetElement(Element::IScaleBarPtr pScaleBar)
{
	m_pElement= pScaleBar;

	m_pUnitTextSymbol = m_pElement->GetUnitTextSymbol();

	if(this->m_hWnd)
		SetCtrls();
}

// CScalebarUnitPage ��Ϣ�������
BOOL CScalebarUnitPage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	return SetCtrls();
}

BOOL CScalebarUnitPage::SetCtrls()
{
	if(m_pElement == NULL)
		return FALSE;

	m_nNumDiv = m_pElement->GetDivisionNum();
	CSpinButtonCtrl	* pSpinDivNum = NULL;
	pSpinDivNum = (CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_MAIN_DIVISION_NUM);
	if (pSpinDivNum)
		pSpinDivNum->SetRange(0, 1000);

	m_nNumSubDiv = m_pElement->GetSubDivisionNum();
	CSpinButtonCtrl	* pSpinSubDivNum = NULL;
	pSpinSubDivNum = (CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_SUB_DIVISION_NUM);
	if (pSpinSubDivNum)
		pSpinSubDivNum->SetRange(0, 1000);

	m_bDivBfZero = m_pElement->GetDrawDivisionBeforZero();

	m_cmbUnit.AddString(SYSTEM::UnitConverter::GetUnitLabelEN(SYSTEM::SYS_UNIT_MILLIMETER).c_str());
	m_cmbUnit.AddString(SYSTEM::UnitConverter::GetUnitLabelEN(SYSTEM::SYS_UNIT_CENTIMETER).c_str());
	m_cmbUnit.AddString(SYSTEM::UnitConverter::GetUnitLabelEN(SYSTEM::SYS_UNIT_DECIMETER).c_str());
	m_cmbUnit.AddString(SYSTEM::UnitConverter::GetUnitLabelEN(SYSTEM::SYS_UNIT_METER).c_str());
	m_cmbUnit.AddString(SYSTEM::UnitConverter::GetUnitLabelEN(SYSTEM::SYS_UNIT_KILOMETER).c_str());
	m_cmbUnit.AddString(SYSTEM::UnitConverter::GetUnitLabelEN(SYSTEM::SYS_UNIT_INCH).c_str());
	m_cmbUnit.AddString(SYSTEM::UnitConverter::GetUnitLabelEN(SYSTEM::SYS_UNIT_FEET).c_str());
	m_cmbUnit.AddString(SYSTEM::UnitConverter::GetUnitLabelEN(SYSTEM::SYS_UNIT_YARD).c_str());
	m_cmbUnit.AddString(SYSTEM::UnitConverter::GetUnitLabelEN(SYSTEM::SYS_UNIT_MILE).c_str());
	m_cmbUnit.AddString(SYSTEM::UnitConverter::GetUnitLabelEN(SYSTEM::SYS_UNIT_NAUTICALMILE).c_str());
	switch(m_pElement->GetUnit())
	{
	case SYSTEM::SYS_UNIT_MILLIMETER:
		m_cmbUnit.SetCurSel(0);
		break;
	case SYSTEM::SYS_UNIT_CENTIMETER:
		m_cmbUnit.SetCurSel(1);
		break;
	case SYSTEM::SYS_UNIT_DECIMETER:
		m_cmbUnit.SetCurSel(2);
		break;
	case SYSTEM::SYS_UNIT_METER:
		m_cmbUnit.SetCurSel(3);
		break;
	case SYSTEM::SYS_UNIT_KILOMETER:
		m_cmbUnit.SetCurSel(4);
		break;
	case SYSTEM::SYS_UNIT_INCH:
		m_cmbUnit.SetCurSel(5);
		break;
	case SYSTEM::SYS_UNIT_FEET:
		m_cmbUnit.SetCurSel(6);
		break;
	case SYSTEM::SYS_UNIT_YARD:
		m_cmbUnit.SetCurSel(7);
		break;
	case SYSTEM::SYS_UNIT_MILE:
		m_cmbUnit.SetCurSel(8);
		break;
	case SYSTEM::SYS_UNIT_NAUTICALMILE:
		m_cmbUnit.SetCurSel(9);
		break;
	default:
		break;
	}

	m_cmbUnitPos.AddString("������֮��");
	m_cmbUnitPos.AddString("������֮ǰ");
	m_cmbUnitPos.AddString("������֮��");
	m_cmbUnitPos.AddString("������֮��");
	m_cmbUnitPos.AddString("���̶ֿ�֮��");
	m_cmbUnitPos.AddString("���̶ֿ�֮ǰ");
	switch(m_pElement->GetUnitPos())
	{
	case Element::UP_AFTER_BAR:
		m_cmbUnitPos.SetCurSel(0);
		break;
	case Element::UP_BEFORE_BAR:
		m_cmbUnitPos.SetCurSel(1);
		break;
	case Element::UP_ABOVE_BAR:
		m_cmbUnitPos.SetCurSel(2);
		break;
	case Element::UP_BELOW_BAR:
		m_cmbUnitPos.SetCurSel(3);
		break;
	case Element::UP_AFTER_LABELS:
		m_cmbUnitPos.SetCurSel(4);
		break;
	case Element::UP_BEFORE_LABELS:
		m_cmbUnitPos.SetCurSel(5);
		break;
	default:
		break;
	}

	m_fUnitGap = m_pElement->GetUnitGap();
	CSpinButtonCtrl	* pSpinUnitGap = NULL;
	pSpinUnitGap = (CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_UNIT_GAP);
	if (pSpinUnitGap)
		pSpinUnitGap->SetRange(0, 1000);

	m_PreviewUnitBtn.SetSymbol(m_pUnitTextSymbol.get());

	UpdateData(FALSE);

	return TRUE;
}

BOOL CScalebarUnitPage::OnApply()
{
	if(!IsWindow(m_hWnd))
		return FALSE;

	if (m_pElement == NULL)
		return FALSE;

	UpdateData();

	m_pElement->SetDivisionNum(m_nNumDiv);
	m_pElement->SetSubDivisionNum(m_nNumSubDiv);
	m_pElement->SetDrawDivisionBeforZero(m_bDivBfZero);

	switch(m_cmbUnit.GetCurSel())
	{
	case 0:
		m_pElement->SetUnit(SYSTEM::SYS_UNIT_MILLIMETER);
		break;
	case 1:
		m_pElement->SetUnit(SYSTEM::SYS_UNIT_CENTIMETER);
		break;
	case 2:
		m_pElement->SetUnit(SYSTEM::SYS_UNIT_DECIMETER);
		break;
	case 3:
		m_pElement->SetUnit(SYSTEM::SYS_UNIT_METER);
		break;
	case 4:
		m_pElement->SetUnit(SYSTEM::SYS_UNIT_KILOMETER);
		break;
	case 5:
		m_pElement->SetUnit(SYSTEM::SYS_UNIT_INCH);
		break;
	case 6:
		m_pElement->SetUnit(SYSTEM::SYS_UNIT_FEET);
		break;
	case 7:
		m_pElement->SetUnit(SYSTEM::SYS_UNIT_YARD);
		break;
	case 8:
		m_pElement->SetUnit(SYSTEM::SYS_UNIT_MILE);
		break;
	case 9:
		m_pElement->SetUnit(SYSTEM::SYS_UNIT_NAUTICALMILE);
		break;
	}

	switch(m_cmbUnitPos.GetCurSel())
	{
	case 0:
		m_pElement->SetUnitPos(Element::UP_AFTER_BAR);
		break;
	case 1:
		m_pElement->SetUnitPos(Element::UP_BEFORE_BAR);
		break;
	case 2:
		m_pElement->SetUnitPos(Element::UP_ABOVE_BAR);
		break;
	case 3:
		m_pElement->SetUnitPos(Element::UP_BELOW_BAR);
		break;
	case 4:
		m_pElement->SetUnitPos(Element::UP_AFTER_LABELS);
		break;
	case 5:
		m_pElement->SetUnitPos(Element::UP_BEFORE_LABELS);
		break;
	}

	m_pElement->SetUnitGap(m_fUnitGap);
	m_pElement->SetUnitTextSymbol(m_pUnitTextSymbol);

	SetModified(FALSE);

	return TRUE;
}

void CScalebarUnitPage::OnBnClickedBtnSetUnitSymbol()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	Framework::ISymbolListCtrl *pCtrl =dynamic_cast<Framework::ISymbolListCtrl*>(Framework::IUIObject::GetUIObjectByName(Framework::CommonUIName::AppSymbolLstCtrl));
	if(pCtrl)
	{
		m_pUnitTextSymbol =pCtrl->SelectSymbol(m_pUnitTextSymbol);
		m_PreviewUnitBtn.SetSymbol(m_pUnitTextSymbol.get());
	}
	SetModified();
}

void CScalebarUnitPage::OnEnChangeEditMainDivisionNum()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CPropertyPage::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	SetModified();
}

void CScalebarUnitPage::OnDeltaposSpinMainDivisionNum(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	SetModified();
}

void CScalebarUnitPage::OnEnChangeEditSubDivisionNum()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CPropertyPage::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	SetModified();
}

void CScalebarUnitPage::OnDeltaposSpinSubDivisionNum(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	SetModified();
}

void CScalebarUnitPage::OnBnClickedChkDivisionBfZero()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	SetModified();
}

void CScalebarUnitPage::OnCbnSelchangeComboUnit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	SetModified();
}

void CScalebarUnitPage::OnCbnSelchangeComboUnitPos()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	SetModified();
}

void CScalebarUnitPage::OnEnChangeEditunitGap()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CPropertyPage::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	SetModified();
}

void CScalebarUnitPage::OnDeltaposSpinUnitGap(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	SetModified();
}
