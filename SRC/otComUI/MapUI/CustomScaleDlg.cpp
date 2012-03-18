// CustomScaleDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CustomScaleDlg.h"


// CCustomScaleDlg 对话框

IMPLEMENT_DYNAMIC(CCustomScaleDlg, CDialog)

CCustomScaleDlg::CCustomScaleDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCustomScaleDlg::IDD, pParent)
{
	m_dbScale = 0;
}

CCustomScaleDlg::~CCustomScaleDlg()
{
}

void CCustomScaleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SCALE, m_dbScale);
}


BEGIN_MESSAGE_MAP(CCustomScaleDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CCustomScaleDlg::OnBnClickedOk)
END_MESSAGE_MAP()

BOOL CCustomScaleDlg::OnInitDialog()
{
	GetDlgItem(IDC_EDIT_SCALE)->SetWindowText("");
	return TRUE;
}
void CCustomScaleDlg::OnBnClickedOk()
{
	UpdateData();
	CString cs;
	cs.Format("%d", (long)(m_dbScale+0.5));
	m_csScale = "1:";
	m_csScale += cs;
	CDialog::OnOK();
}