// FuzzyKMeanDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "Control.h"
#include "FuzzyKMeanDialog.h"
#include "FuzzyKmeanClass.h"
#include "ProgressBar.h"

// CFuzzyKMeanDialog 对话框

IMPLEMENT_DYNAMIC(CFuzzyKMeanDialog, CDialog)

CFuzzyKMeanDialog::CFuzzyKMeanDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CFuzzyKMeanDialog::IDD, pParent)
	, m_strInputFile(_T(""))
	, m_strOutputFile(_T(""))
	, m_lClassNum(3)
	, m_lSampleCount(1)
	, m_lIterCount(20)
	, m_dblThreold(0.01)
{

}

CFuzzyKMeanDialog::~CFuzzyKMeanDialog()
{
}

void CFuzzyKMeanDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_INPUTFILE, m_strInputFile);
	DDX_Text(pDX, IDC_EDIT_OUTPUTFILE, m_strOutputFile);
	DDX_Text(pDX, IDC_EDIT_CLASSNUM, m_lClassNum);
	DDX_Text(pDX, IDC_EDIT_SAMPLECOUNT, m_lSampleCount);
	DDX_Text(pDX, IDC_EDIT_ITERCOUNT, m_lIterCount);
	DDX_Text(pDX, IDC_EDIT_THREOLD, m_dblThreold);
}


BEGIN_MESSAGE_MAP(CFuzzyKMeanDialog, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_INPUTFILE, &CFuzzyKMeanDialog::OnBnClickedButtonInputfile)
	ON_BN_CLICKED(IDC_BUTTON_OUTPUTFILE, &CFuzzyKMeanDialog::OnBnClickedButtonOutputfile)
	ON_BN_CLICKED(IDOK, &CFuzzyKMeanDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// CFuzzyKMeanDialog 消息处理程序

void CFuzzyKMeanDialog::OnBnClickedButtonInputfile()
{

	CString strFilter = "Image Files(*.tif)|*.tif|All Files(*.*)|*.*||";
	CFileDialog dlg(TRUE, "Image Files(*.tif)", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, strFilter);
	if(dlg.DoModal() == IDOK)
	{
		m_strInputFile = dlg.GetPathName();
	}

	UpdateData(FALSE);
	
}

void CFuzzyKMeanDialog::OnBnClickedButtonOutputfile()
{
	CString strFilter = "Image Files(*.tif)|*.tif|All Files(*.*)|*.*||";
	CFileDialog dlg(TRUE, "Image Files(*.tif)", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, strFilter);
	if(dlg.DoModal() == IDOK)
	{
		m_strOutputFile = dlg.GetPathName();
	}
	UpdateData(FALSE);
}

void CFuzzyKMeanDialog::OnBnClickedOk()
{
	Control::CProgressBar progress;

	ImageProcess::FuzzyKmeanClass(m_strInputFile, m_strOutputFile, m_lSampleCount, m_lClassNum, m_lIterCount, m_dblThreold, &progress);

	OnOK();
}
