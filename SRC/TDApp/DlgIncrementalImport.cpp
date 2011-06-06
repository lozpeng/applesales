// DlgIncrementalImport.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TDApp.h"
#include "DlgIncrementalImport.h"


// CDlgIncrementalImport �Ի���

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


// CDlgIncrementalImport ��Ϣ�������

void CDlgIncrementalImport::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnOK();
}

void CDlgIncrementalImport::OnBnClickedBtnSlectpath()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();

	CString     strOpenFilter = "Incrementalfile(*.xml)|*.xml|All Files(*.*)|*.*||";
	CFileDialog FileDlg(TRUE, "", NULL,  OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, strOpenFilter);
	if(FileDlg.DoModal()!=IDOK)
		return;

	m_IncrementalPath = FileDlg.GetPathName();

	this->UpdateData(FALSE);
}
