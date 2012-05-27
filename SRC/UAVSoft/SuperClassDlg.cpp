// SuperClassDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "UAVSoft.h"
#include "SuperClassDlg.h"


// CSuperClassDlg 对话框

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


// CSuperClassDlg 消息处理程序

BOOL CSuperClassDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
