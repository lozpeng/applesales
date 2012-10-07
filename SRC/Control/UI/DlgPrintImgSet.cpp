// DlgPrintImgSet.cpp : implementation file
//

#include "stdafx.h"
#include "DlgPrintImgSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPrintImgSet dialog


CDlgPrintImgSet::CDlgPrintImgSet(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPrintImgSet::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPrintImgSet)
	m_dblDpi = 0.0;
	m_strPrintImg = _T("");
	m_strWidth = _T("");
	m_strHeight = _T("");
	//}}AFX_DATA_INIT
}


void CDlgPrintImgSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPrintImgSet)
	DDX_Text(pDX, IDC_EDIT_DPI, m_dblDpi);
	DDX_Text(pDX, IDC_STATIC_PRINTIMGFILE, m_strPrintImg);
	DDX_Text(pDX, IDC_STATIC_X, m_strWidth);
	DDX_Text(pDX, IDC_STATIC_Y, m_strHeight);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPrintImgSet, CDialog)
	//{{AFX_MSG_MAP(CDlgPrintImgSet)
	ON_BN_CLICKED(IDC_BUTTON_PRINTIMGFILE, OnButtonPrintimgfile)
	ON_EN_CHANGE(IDC_EDIT_DPI, OnChangeEditDpi)
	ON_EN_UPDATE(IDC_EDIT_DPI, OnUpdateEditDpi)
	ON_EN_KILLFOCUS(IDC_EDIT_DPI, OnKillfocusEditDpi)
	ON_BN_CLICKED(IDC_BUTTON_UpDate, OnBUTTONUpDate)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CDlgPrintImgSet::OnBnClickedOk)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPrintImgSet message handlers

void CDlgPrintImgSet::OnButtonPrintimgfile() 
{
	char csFilter[]=_T("TIFF (*.tif)|*.tif|JPEG(*.jpg)|*.jpg|BMP(*.bmp)||");
	CFileDialog dlgFile(TRUE,
						_T(".tif"),
						NULL,
						OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
						csFilter);

	if(dlgFile.DoModal()==IDCANCEL)
		return;

	m_strPrintImg=dlgFile.GetFileName();
	m_strPrintImgPath=dlgFile.GetPathName();
	UpdateData(FALSE);
}

void CDlgPrintImgSet::OnChangeEditDpi() 
{

}

void CDlgPrintImgSet::OnUpdateEditDpi() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_UPDATE flag ORed into the lParam mask.
	
	// TODO: Add your control notification handler code here

}

void CDlgPrintImgSet::OnKillfocusEditDpi() 
{
	UpdateData(TRUE);
	m_strWidth.Format("%d",INT(m_dblSizeX*m_dblDpi/25.4));
	m_strHeight.Format("%d",INT(m_dblSizeY*m_dblDpi/25.4));
	UpdateData(FALSE);		
}

void CDlgPrintImgSet::OnBUTTONUpDate() 
{
	int iWidth,iHeight;
	iWidth=INT(m_dblSizeX*m_dblDpi/25.4);
	iHeight=INT(m_dblSizeY*m_dblDpi/25.4);
	if(iWidth>10000&&iHeight>10000)
	{
		AfxMessageBox("请重新输入小于当前值的DPI");
	}
	
}

void CDlgPrintImgSet::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	OnOK();
}
