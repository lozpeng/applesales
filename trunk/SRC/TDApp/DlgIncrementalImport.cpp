// DlgIncrementalImport.cpp : 实现文件
//

#include "stdafx.h"
#include "TDApp.h"
#include "DlgIncrementalImport.h"


// CDlgIncrementalImport 对话框

IMPLEMENT_DYNAMIC(CDlgIncrementalImport, CDialog)

CDlgIncrementalImport::CDlgIncrementalImport(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgIncrementalImport::IDD, pParent)
	, m_IncrementalPath(_T(""))
{

}

CDlgIncrementalImport::~CDlgIncrementalImport()
{
}

void CDlgIncrementalImport::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_IncrementalPath);
}


BEGIN_MESSAGE_MAP(CDlgIncrementalImport, CDialog)
	ON_BN_CLICKED(IDOK, &CDlgIncrementalImport::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BTN_SLECTPATH, &CDlgIncrementalImport::OnBnClickedBtnSlectpath)
END_MESSAGE_MAP()


// CDlgIncrementalImport 消息处理程序

void CDlgIncrementalImport::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	OnOK();
}

void CDlgIncrementalImport::OnBnClickedBtnSlectpath()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();

	CString     strOpenFilter = "Incrementalfile(*.xml)|*.xml|All Files(*.*)|*.*||";
	CFileDialog FileDlg(TRUE, "", NULL,  OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, strOpenFilter);
	if(FileDlg.DoModal()!=IDOK)
		return;

	m_IncrementalPath = FileDlg.GetPathName();

	this->UpdateData(FALSE);
}
