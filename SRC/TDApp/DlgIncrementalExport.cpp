// DlgIncrementalExport.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TDApp.h"
#include "DlgIncrementalExport.h"


// CDlgIncrementalExport �Ի���

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


// CDlgIncrementalExport ��Ϣ�������

void CDlgIncrementalExport::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnOK();
}

void CDlgIncrementalExport::OnBnClickedBtnSlectpath()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();

	CString     strOpenFilter = "Incrementalfile(*.xml)|*.xml|All Files(*.*)|*.*||";
	CFileDialog FileDlg(FALSE, "", NULL,  OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, strOpenFilter);
	if(FileDlg.DoModal()!=IDOK)
		return;

	m_IncrementalPath = FileDlg.GetPathName();
	
	this->UpdateData(FALSE);
}
