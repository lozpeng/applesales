// DlgChangeDetect.cpp : 实现文件
//

#include "stdafx.h"
#include "Control.h"
#include "DlgChangeDetect.h"


// CDlgChangeDetect 对话框

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


// CDlgChangeDetect 消息处理程序

void CDlgChangeDetect::OnBnClickedBtnSelchashp()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CDlgChangeDetect::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	OnOK();
}

BOOL CDlgChangeDetect::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
