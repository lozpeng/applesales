// DlgModifyUniClass.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DlgModifyUniClass.h"
#include "../CotSymbolList.h"

// CDlgModifyUniClass �Ի���

IMPLEMENT_DYNAMIC(CDlgModifyUniClass, CDialog)

CDlgModifyUniClass::CDlgModifyUniClass(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgModifyUniClass::IDD, pParent)
	, m_strValue(_T(""))
	, m_strLabel(_T(""))
{
    m_bUniqueRender =true;
}

CDlgModifyUniClass::~CDlgModifyUniClass()
{
}

void CDlgModifyUniClass::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_UNIVALUE, m_strValue);
	DDX_Text(pDX, IDC_EDIT_UNILABEL, m_strLabel);
	DDX_Control(pDX, IDC_BTN_UNIOV, m_btn);
}


BEGIN_MESSAGE_MAP(CDlgModifyUniClass, CDialog)
	ON_BN_CLICKED(IDC_BTN_UNIOV, &CDlgModifyUniClass::OnBnClickedBtnUniov)
END_MESSAGE_MAP()


// CDlgModifyUniClass ��Ϣ�������

void CDlgModifyUniClass::OnBnClickedBtnUniov()
{
	otComUI::CotSymbolList symlist;

	
	m_pSymbol =symlist.SelectSymbol(m_pSymbol);
	
	m_btn.SetSymbol(m_pSymbol.get());

}

BOOL CDlgModifyUniClass::OnInitDialog()
{
	CDialog::OnInitDialog();

	if(m_bUniqueRender)
	{
		GetDlgItem(IDC_EDIT_UNIVALUE)->EnableWindow(FALSE);
	}
	else
	{
		//��Χͼ�������
		GetDlgItem(IDC_VALUE_LABEL)->SetWindowText("��Χ����");
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CDlgModifyUniClass::Init(CString value, CString label, Display::ISymbolPtr pSymbol)
{
	m_strValue =value;
	m_strLabel =label;
	m_pSymbol =pSymbol;
	m_btn.SetSymbol(pSymbol.get());
}

