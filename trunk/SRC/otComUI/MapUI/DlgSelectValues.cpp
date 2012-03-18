// DlgSelectValues.cpp : 实现文件
//

#include "stdafx.h"
#include "DlgSelectValues.h"


// CDlgSelectValues 对话框

IMPLEMENT_DYNAMIC(CDlgSelectValues, CDialog)

CDlgSelectValues::CDlgSelectValues(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSelectValues::IDD, pParent)
{

}

CDlgSelectValues::~CDlgSelectValues()
{
}

void CDlgSelectValues::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_ALLVALUES, m_listAllValues);
	DDX_Control(pDX, IDC_LIST_SELECTVALUE, m_listSelect);
}


BEGIN_MESSAGE_MAP(CDlgSelectValues, CDialog)
	ON_BN_CLICKED(IDC_ADDSELECT, &CDlgSelectValues::OnBnClickedAddselect)
	ON_BN_CLICKED(IDC_ADDALL_VALUE, &CDlgSelectValues::OnBnClickedAddallValue)
	ON_BN_CLICKED(IDC_REMOVE_SELECT, &CDlgSelectValues::OnBnClickedRemoveSelect)
	ON_BN_CLICKED(IDC_REMOVEALL_VALUE, &CDlgSelectValues::OnBnClickedRemoveallValue)
	ON_LBN_DBLCLK(IDC_LIST_ALLVALUES, &CDlgSelectValues::OnLbnDblclkListAllvalues)
	ON_LBN_DBLCLK(IDC_LIST_SELECTVALUE, &CDlgSelectValues::OnLbnDblclkListSelectvalue)
	ON_BN_CLICKED(IDOK, &CDlgSelectValues::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgSelectValues 消息处理程序

void CDlgSelectValues::OnBnClickedAddselect()
{
	CString TempStr;
	if(m_listAllValues.GetCurSel()!=LB_ERR)
	{
		int iCurSel=m_listAllValues.GetCurSel();
		m_listAllValues.GetText(iCurSel,TempStr);
		m_listAllValues.DeleteString(iCurSel);
		m_listSelect.AddString(TempStr);
		if(m_listAllValues.SetCurSel(iCurSel)==LB_ERR)
			m_listAllValues.SetCurSel(m_listAllValues.GetCount()-1);
	}
	else
		m_listAllValues.SetCurSel(0);
}

void CDlgSelectValues::OnBnClickedAddallValue()
{
	CString TempStr;
	int iCount=m_listAllValues.GetCount();
	for(int i=0;i<iCount;i++)
	{
		m_listAllValues.GetText(0,TempStr);
		m_listAllValues.DeleteString(0);
		m_listSelect.AddString(TempStr);
	}
}

void CDlgSelectValues::OnBnClickedRemoveSelect()
{
	CString TempStr;
	if(m_listSelect.GetCurSel()!=LB_ERR)
	{
		int iCurSel=m_listSelect.GetCurSel();
		m_listSelect.GetText(iCurSel,TempStr);
		m_listSelect.DeleteString(iCurSel);
		m_listAllValues.AddString(TempStr);
		if(m_listSelect.SetCurSel(iCurSel)==LB_ERR)
			m_listSelect.SetCurSel(m_listSelect.GetCount()-1);
	}
	else
		m_listSelect.SetCurSel(0);
}

void CDlgSelectValues::OnBnClickedRemoveallValue()
{
	CString TempStr;
	int iCount=m_listSelect.GetCount();
	for(int i=0;i<iCount;i++)
	{
		m_listSelect.GetText(0,TempStr);
		m_listSelect.DeleteString(0);
		m_listAllValues.AddString(TempStr);
	}
}

void CDlgSelectValues::OnLbnDblclkListAllvalues()
{
	CString TempStr;
	if(m_listAllValues.GetCurSel()!=LB_ERR)
	{
		int iCurSel=m_listAllValues.GetCurSel();
		m_listAllValues.GetText(iCurSel,TempStr);
		m_listAllValues.DeleteString(iCurSel);
		m_listSelect.AddString(TempStr);
		
	}
}

void CDlgSelectValues::OnLbnDblclkListSelectvalue()
{
	CString TempStr;
	if(m_listSelect.GetCurSel()!=LB_ERR)
	{
		int iCurSel=m_listSelect.GetCurSel();
		m_listSelect.GetText(iCurSel,TempStr);
		m_listSelect.DeleteString(iCurSel);
		m_listAllValues.AddString(TempStr);
		
	}
}

void CDlgSelectValues::OnBnClickedOk()
{
	UpdateData(TRUE);
	CString str;
	for(int i=0;i<m_listSelect.GetCount();i++)
	{
		m_listSelect.GetText(i,str);
		m_values.push_back(str);
	}
	OnOK();
}

BOOL CDlgSelectValues::OnInitDialog()
{
	CDialog::OnInitDialog();

	for(size_t i=0;i<m_allValues.size();i++)
	{
		m_listAllValues.AddString(m_allValues[i]);
	}


	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
