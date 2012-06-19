// SuperClassDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "UAVSoft.h"
#include "SuperClassDlg.h"


// CSuperClassDlg 对话框

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


// CSuperClassDlg 消息处理程序

BOOL CSuperClassDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
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
	// 异常: OCX 属性页应返回 FALSE
}

void CSuperClassDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	OnOK();
}
