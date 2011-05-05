// DlgChangeDetect.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Control.h"
#include "DlgChangeDetect.h"


// CDlgChangeDetect �Ի���

IMPLEMENT_DYNAMIC(CDlgChangeDetect, CDialog)

CDlgChangeDetect::CDlgChangeDetect(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgChangeDetect::IDD, pParent)
	, m_strResult(_T(""))
	, m_bLoadShp(FALSE)
{

}

CDlgChangeDetect::~CDlgChangeDetect()
{
}

void CDlgChangeDetect::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_ORIIMG, m_CmbSrc);
	DDX_Control(pDX, IDC_COMBO_DESTIMG, m_CmbDest);
	DDX_Text(pDX, IDC_EDIT_RELSHP, m_strResult);
	DDX_Check(pDX, IDC_CHECK_LOADCHANGE, m_bLoadShp);
}


BEGIN_MESSAGE_MAP(CDlgChangeDetect, CDialog)
	ON_BN_CLICKED(IDC_BTN_SELCHASHP, &CDlgChangeDetect::OnBnClickedBtnSelchashp)
	ON_BN_CLICKED(IDOK, &CDlgChangeDetect::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgChangeDetect ��Ϣ�������

void CDlgChangeDetect::OnBnClickedBtnSelchashp()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void CDlgChangeDetect::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnOK();
}

BOOL CDlgChangeDetect::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
