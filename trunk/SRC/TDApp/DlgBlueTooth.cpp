// DlgBlueTooth.cpp : 实现文件
//

#include "stdafx.h"
#include "TDApp.h"
#include "DlgBlueTooth.h"


// CDlgBlueTooth 对话框

IMPLEMENT_DYNAMIC(CDlgBlueTooth, CDialog)

CDlgBlueTooth::CDlgBlueTooth(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgBlueTooth::IDD, pParent)
	, m_BluetoothName(_T(""))
	, m_strFile(_T(""))
{

}

CDlgBlueTooth::~CDlgBlueTooth()
{
}

void CDlgBlueTooth::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_BluetoothName);
	DDX_Text(pDX, IDC_SFILENAME, m_strFile);
}


BEGIN_MESSAGE_MAP(CDlgBlueTooth, CDialog)
	ON_BN_CLICKED(IDC_SELSFILE, &CDlgBlueTooth::OnBnClickedSelsfile)
	ON_BN_CLICKED(IDC_TEST_CONNECT, &CDlgBlueTooth::OnBnClickedTestConnect)
	ON_BN_CLICKED(IDOK, &CDlgBlueTooth::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgBlueTooth 消息处理程序

void CDlgBlueTooth::OnBnClickedSelsfile()
{
	UpdateData();

	CString     strOpenFilter = "增量文件(*.xml)|*.xml||";
	CFileDialog FileDlg(TRUE, "", NULL,  OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, strOpenFilter);
	if(FileDlg.DoModal()==IDOK)
	{
        m_strFile =FileDlg.GetPathName();
		UpdateData(FALSE);
	}
		
}

void CDlgBlueTooth::OnBnClickedTestConnect()
{
	UpdateData();
	if(m_bluetooth.IsConnect())
	{
		//先关闭连接
		m_bluetooth.Close();
	}
	bool bret =m_bluetooth.Connect(m_BluetoothName);
	if(bret)
	{
		MessageBox("连接成功","消息");
		m_bluetooth.Close();
	}
	else
	{
        MessageBox("连接失败","消息");
	}
}

void CDlgBlueTooth::OnBnClickedOk()
{
	UpdateData();
	if(m_BluetoothName.IsEmpty())
	{
		MessageBox("蓝牙设备名称不能为空","提示");
		return;
	}
	if(m_strFile.IsEmpty())
	{
		MessageBox("传送文件名称不能为空","提示");
		return;
	}
	if(!m_bluetooth.Connect(m_BluetoothName))
	{
         MessageBox("连接失败","消息");
		 return;
	}
	if(!m_bluetooth.SendFile(m_strFile))
	{
         MessageBox("发送文件失败","消息");
		 return;
	}
	MessageBox("发送文件成功","消息");
	OnOK();
}
