// ImgProcessUI\Raster2VectorDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "Control.h"
#include "ImgProcessUI\Raster2VectorDialog.h"
#include "Image2Vec.h"

// CRaster2VectorDialog 对话框

IMPLEMENT_DYNAMIC(CRaster2VectorDialog, CDialog)

CRaster2VectorDialog::CRaster2VectorDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CRaster2VectorDialog::IDD, pParent)
	, m_strInputFile(_T(""))
	, m_strOutputFile(_T(""))
	, m_classValue(1)
	, m_lThres(100)
{

}

CRaster2VectorDialog::~CRaster2VectorDialog()
{
}

void CRaster2VectorDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_INPUTFILE, m_strInputFile);
	DDX_Text(pDX, IDC_EDIT_OUTPUTFILE, m_strOutputFile);
	DDX_Text(pDX, IDC_EDIT_CLASSVALUE, m_classValue);
	DDX_Text(pDX, IDC_EDIT_THREOLD, m_lThres);
}


BEGIN_MESSAGE_MAP(CRaster2VectorDialog, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_INPUTFILE, &CRaster2VectorDialog::OnBnClickedButtonInputfile)
	ON_BN_CLICKED(IDC_BUTTON_OUTPUTFILE, &CRaster2VectorDialog::OnBnClickedButtonOutputfile)
	ON_BN_CLICKED(IDOK2, &CRaster2VectorDialog::OnBnClickedOk2)
	ON_BN_CLICKED(IDCANCEL2, &CRaster2VectorDialog::OnBnClickedCancel2)
END_MESSAGE_MAP()


// CRaster2VectorDialog 消息处理程序

void CRaster2VectorDialog::OnBnClickedButtonInputfile()
{
	CString strFilter = "Image Files(*.tif)|*.tif|All Files(*.*)|*.*||";
	CFileDialog dlg(TRUE, "Image Files(*.tif)", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, strFilter);
	if(dlg.DoModal() == IDOK)
	{
		m_strInputFile = dlg.GetPathName();
	}

	UpdateData(FALSE);
}

void CRaster2VectorDialog::OnBnClickedButtonOutputfile()
{
	CString strFilter = "shape Files(*.shp)|*.shp|All Files(*.*)|*.*||";
	CFileDialog dlg(TRUE, "shape Files(*.shp)", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, strFilter);
	if(dlg.DoModal() == IDOK)
	{
		m_strOutputFile = dlg.GetPathName();
	}
	UpdateData(FALSE);
}

void CRaster2VectorDialog::OnBnClickedOk2()
{
	UpdateData(TRUE);
	//
	ImageProcess::ImgClass2Shp(m_strInputFile, m_strOutputFile, m_classValue, m_lThres);

	OnOK();
}

void CRaster2VectorDialog::OnBnClickedCancel2()
{
	OnCancel();
}
