// SuperClassDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "UAVSoft.h"
#include "SuperClassDlg.h"


// CSuperClassDlg �Ի���

IMPLEMENT_DYNAMIC(CSuperClassDlg, CDialog)

CSuperClassDlg::CSuperClassDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSuperClassDlg::IDD, pParent)
{

}

CSuperClassDlg::~CSuperClassDlg()
{
}

void CSuperClassDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSuperClassDlg, CDialog)
END_MESSAGE_MAP()


// CSuperClassDlg ��Ϣ�������

BOOL CSuperClassDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
