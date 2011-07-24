// DlgBlueTooth.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TDApp.h"
#include "DlgBlueTooth.h"


// CDlgBlueTooth �Ի���

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


// CDlgBlueTooth ��Ϣ�������

void CDlgBlueTooth::OnBnClickedSelsfile()
{
	UpdateData();

	CString     strOpenFilter = "�����ļ�(*.xml)|*.xml||";
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
		//�ȹر�����
		m_bluetooth.Close();
	}
	bool bret =m_bluetooth.Connect(m_BluetoothName);
	if(bret)
	{
		MessageBox("���ӳɹ�","��Ϣ");
		m_bluetooth.Close();
	}
	else
	{
        MessageBox("����ʧ��","��Ϣ");
	}
}

void CDlgBlueTooth::OnBnClickedOk()
{
	UpdateData();
	if(m_BluetoothName.IsEmpty())
	{
		MessageBox("�����豸���Ʋ���Ϊ��","��ʾ");
		return;
	}
	if(m_strFile.IsEmpty())
	{
		MessageBox("�����ļ����Ʋ���Ϊ��","��ʾ");
		return;
	}
	if(!m_bluetooth.Connect(m_BluetoothName))
	{
         MessageBox("����ʧ��","��Ϣ");
		 return;
	}
	if(!m_bluetooth.SendFile(m_strFile))
	{
         MessageBox("�����ļ�ʧ��","��Ϣ");
		 return;
	}
	MessageBox("�����ļ��ɹ�","��Ϣ");
	OnOK();
}
