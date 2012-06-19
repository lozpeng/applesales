// SuperClassDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "UAVSoft.h"
#include "SuperClassDlg.h"


// CSuperClassDlg �Ի���

IMPLEMENT_DYNAMIC(CSuperClassDlg, CDialog)

CSuperClassDlg::CSuperClassDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSuperClassDlg::IDD, pParent)
	, m_strInputFile(_T(""))
{

}

CSuperClassDlg::~CSuperClassDlg()
{
}

void CSuperClassDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_INPUTFILE, m_strInputFile);
	DDX_Control(pDX, IDC_LIST_CLASS, m_lstCls);
}


BEGIN_MESSAGE_MAP(CSuperClassDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CSuperClassDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CSuperClassDlg ��Ϣ�������

BOOL CSuperClassDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_strInputFile = m_strName.c_str();
	std::vector<ROI_INFO*>::iterator iter;
	int i =0;
	for (iter=m_Rois.begin(); iter!=m_Rois.end(); iter++)
	{
		ROI_INFO* pInfo = *iter;
		m_lstCls.InsertString(i++,pInfo->strClassNmae);
	}
	UpdateData(false);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CSuperClassDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnOK();
}
