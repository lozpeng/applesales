// DlgDrawingExport.cpp : 实现文件
//

#include "stdafx.h"
#include "TDApp.h"
#include "DlgDrawingExport.h"


// CDlgDrawingExport 对话框

IMPLEMENT_DYNAMIC(CDlgDrawingExport, CDialog)

CDlgDrawingExport::CDlgDrawingExport(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDrawingExport::IDD, pParent)
	, m_ExportPath(_T(""))
	, m_CheckAddMap(FALSE)
	, m_bExpoertAll(false)
{

}

CDlgDrawingExport::~CDlgDrawingExport()
{
}

void CDlgDrawingExport::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_DRAWINGTYPE, m_ComboxType);
	DDX_Text(pDX, IDC_EDIT1, m_ExportPath);
	DDX_Check(pDX, IDC_CHECK_ISADD, m_CheckAddMap);
}


BEGIN_MESSAGE_MAP(CDlgDrawingExport, CDialog)
	ON_BN_CLICKED(IDC_BTN_SLECTPATH, &CDlgDrawingExport::OnBnClickedBtnSlectpath)
	ON_BN_CLICKED(IDC_RADIO_EXPORT_ALL, &CDlgDrawingExport::OnBnClickedRadioExportAll)
	ON_BN_CLICKED(IDC_RADIO_EXPOERT_SELECTED, &CDlgDrawingExport::OnBnClickedRadioExpoertSelected)
	ON_BN_CLICKED(IDOK, &CDlgDrawingExport::OnBnClickedOk)
END_MESSAGE_MAP()


BOOL CDlgDrawingExport::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_ComboxType.AddString("点");
	m_ComboxType.AddString("线");
	m_ComboxType.AddString("面");
	m_ComboxType.SetCurSel(0);
	m_DrawingType = 0;

	m_CheckAddMap = TRUE;
	m_ExportPath ="D:\\expoert.shp";
	m_bExpoertAll = true;

	CButton* pFusionType =(CButton*)GetDlgItem(IDC_RADIO_EXPORT_ALL);
	pFusionType->SetCheck(1);

	this->UpdateData(false);
	return TRUE;

}
// CDlgDrawingExport 消息处理程序

void CDlgDrawingExport::OnBnClickedBtnSlectpath()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();

	CString     strOpenFilter = "shapefile(*.shp)|*.shp|All Files(*.*)|*.*||";
	CFileDialog FileDlg(TRUE, "", NULL,  OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, strOpenFilter);
	if(FileDlg.DoModal()!=IDOK)
		return;
	m_ExportPath=FileDlg.GetPathName();
	this->UpdateData(FALSE);
}

void CDlgDrawingExport::OnBnClickedRadioExportAll()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bExpoertAll = true;
}

void CDlgDrawingExport::OnBnClickedRadioExpoertSelected()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bExpoertAll = false;
}

void CDlgDrawingExport::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	this->UpdateData();

	m_DrawingType = m_ComboxType.GetCurSel();

	OnOK();
}
