// DlgTargetClip.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Control.h"
#include "DlgTargetClip.h"
#include "ImageClip.h"

// CDlgTargetClip �Ի���

IMPLEMENT_DYNAMIC(CDlgTargetClip, CDialog)

CDlgTargetClip::CDlgTargetClip(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTargetClip::IDD, pParent)
	, m_strInImg(_T(""))
	, m_strTargetFile(_T(""))
	, m_strOutPath(_T(""))
	, m_lWidth(200)
	, m_lHeight(200)
	, m_strInImg2(_T(""))
{

}

CDlgTargetClip::~CDlgTargetClip()
{
}

void CDlgTargetClip::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_INIMG, m_strInImg);
	DDX_Text(pDX, IDC_EDIT_TARGETFILE, m_strTargetFile);
	DDX_Text(pDX, IDC_EDIT_OUTPATH, m_strOutPath);
	DDX_Text(pDX, IDC_EDIT_WIDTH, m_lWidth);
	DDX_Text(pDX, IDC_EDIT_HEIGHT, m_lHeight);
	DDX_Text(pDX, IDC_EDIT_INIMG2, m_strInImg2);
}


BEGIN_MESSAGE_MAP(CDlgTargetClip, CDialog)
	ON_BN_CLICKED(IDOK, &CDlgTargetClip::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_INIMG, &CDlgTargetClip::OnBnClickedButtonInimg)
	ON_BN_CLICKED(IDC_BUTTON_INIMG2, &CDlgTargetClip::OnBnClickedButtonInimg2)
	ON_BN_CLICKED(IDC_BUTTON_TARGETFILE, &CDlgTargetClip::OnBnClickedButtonTargetfile)
END_MESSAGE_MAP()


// CDlgTargetClip ��Ϣ�������

void CDlgTargetClip::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);

	ImageProcess::TargetClip(m_strInImg, m_strTargetFile, m_lWidth, m_lHeight, m_strOutPath);

	ImageProcess::TargetClip(m_strInImg2, m_strTargetFile, m_lWidth, m_lHeight, m_strOutPath);

	OnOK();
}

void CDlgTargetClip::OnBnClickedButtonInimg()
{
	CFileDialog dlg(true, "*.*", "",OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,"Ӱ������(*.tif;*.img;*.tiff;*.bmp)|*.tif;*.img;*.tiff;*.bmp|All Files(*.*)|*.*||",this);
	if(dlg.DoModal()==IDOK) 
	{

		m_strInImg =dlg.GetPathName();
		UpdateData(FALSE);
	}
}

void CDlgTargetClip::OnBnClickedButtonInimg2()
{
	CFileDialog dlg(true, "*.*", "",OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,"Ӱ������(*.tif;*.img;*.tiff;*.bmp)|*.tif;*.img;*.tiff;*.bmp|All Files(*.*)|*.*||",this);
	if(dlg.DoModal()==IDOK) 
	{

		m_strInImg2 =dlg.GetPathName();
		UpdateData(FALSE);
	}
}

void CDlgTargetClip::OnBnClickedButtonTargetfile()
{

	CFileDialog dlg(true, "*.*", "",OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,"shapefile(*.shp)|*.shp|All file(*.*)|*.*|",this);

	if(dlg.DoModal()==IDOK) 
	{
		m_strTargetFile =dlg.GetPathName();
		UpdateData(FALSE);
	}
}
