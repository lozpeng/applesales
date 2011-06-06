// DlgIncrementalExport.cpp : 实现文件
//

#include "stdafx.h"
#include "TDApp.h"
#include "DlgIncrementalExport.h"


// CDlgIncrementalExport 对话框

IMPLEMENT_DYNAMIC(CDlgIncrementalExport, CDialog)

CDlgIncrementalExport::CDlgIncrementalExport(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgIncrementalExport::IDD, pParent)
	, m_IncrementalPath(_T(""))
{

}

CDlgIncrementalExport::~CDlgIncrementalExport()
{
}

void CDlgIncrementalExport::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_IncrementalPath);
}


BEGIN_MESSAGE_MAP(CDlgIncrementalExport, CDialog)
	ON_BN_CLICKED(IDOK, &CDlgIncrementalExport::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BTN_SLECTPATH, &CDlgIncrementalExport::OnBnClickedBtnSlectpath)
END_MESSAGE_MAP()


// CDlgIncrementalExport 消息处理程序

void CDlgIncrementalExport::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	OnOK();
}

void CDlgIncrementalExport::OnBnClickedBtnSlectpath()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();

	CString     strOpenFilter = "Incrementalfile(*.xml)|*.xml|All Files(*.*)|*.*||";
	CFileDialog FileDlg(FALSE, "", NULL,  OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, strOpenFilter);
	if(FileDlg.DoModal()!=IDOK)
		return;

	m_IncrementalPath = FileDlg.GetPathName();
	
	this->UpdateData(FALSE);
}
