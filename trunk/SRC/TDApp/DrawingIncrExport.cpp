// DrawingIncrExport.cpp : 实现文件
//

#include "stdafx.h"
#include "TDApp.h"
#include "DrawingIncrExport.h"

#include "MainFrm.h"
#include "IDocument.h"
#include "ILayer.h"
#include "FeatureLayer.h"

// CDrawingIncrExport 对话框

IMPLEMENT_DYNAMIC(CDrawingIncrExport, CDialog)

CDrawingIncrExport::CDrawingIncrExport(CWnd* pParent /*=NULL*/)
	: CDialog(CDrawingIncrExport::IDD, pParent)
	, m_bExpoertAll(true)
	, m_ExportPath(_T(""))
{

}

CDrawingIncrExport::~CDrawingIncrExport()
{
}

void CDrawingIncrExport::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_DRAWINGTYPE, m_ComboxType);
	//DDX_Radio(pDX, IDC_RADIO_EXPORT_ALL, m_bExpoertAll);
	DDX_Control(pDX, IDC_COMBO_TargetLayer, m_Combo_TagertLayer);
	DDX_Text(pDX, IDC_EDIT_Export, m_ExportPath);
}


BEGIN_MESSAGE_MAP(CDrawingIncrExport, CDialog)
	ON_BN_CLICKED(IDC_BTN_SLECTPATH, &CDrawingIncrExport::OnBnClickedBtnSlectpath)
	ON_BN_CLICKED(IDOK, &CDrawingIncrExport::OnBnClickedOk)
	ON_CBN_SELENDCANCEL(IDC_COMBO_DRAWINGTYPE, &CDrawingIncrExport::OnCbnSelendcancelComboDrawingtype)
	ON_BN_CLICKED(IDC_RADIO_EXPORT_ALL, &CDrawingIncrExport::OnBnClickedRadioExportAll)
	ON_BN_CLICKED(IDC_RADIO_EXPOERT_SELECTED, &CDrawingIncrExport::OnBnClickedRadioExpoertSelected)
	ON_CBN_SELCHANGE(IDC_COMBO_DRAWINGTYPE, &CDrawingIncrExport::OnCbnSelchangeComboDrawingtype)
END_MESSAGE_MAP()


// CDrawingIncrExport 消息处理程序
BOOL CDrawingIncrExport::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	m_ComboxType.AddString("面");
	m_ComboxType.AddString("线");
	m_ComboxType.AddString("点");
	m_ComboxType.SetCurSel(0);
	m_DrawingType = 0;

	
	m_ExportPath ="D:\\expoert.xml";
	m_bExpoertAll = true;

	CButton* pFusionType =(CButton*)GetDlgItem(IDC_RADIO_EXPORT_ALL);
	pFusionType->SetCheck(1);

	this->UpdateData(false);

	Framework::IDocument *pDoc =(Framework::IDocument*)Framework::IUIObject::GetUIObjectByName(Framework::CommonUIName::AppDocument);
	Carto::CMapPtr pMap =pDoc->GetActiveMap();

	Carto::CLayerArray &layers =pMap->GetLayers();

	Carto::ILayerPtr pLayer;
	int index;
	bool bfind =false;
	for(int i=0;i<layers.GetSize();i++)
	{
		pLayer =layers.GetAt(i);
		if(!pLayer)
		{
			continue;
		}
		if(pLayer->GetLayerType()==Carto::FeatureLayer)
		{
			Carto::IFeatureLayerPtr pFeatureLayer = pLayer;
			if(pFeatureLayer->GetFeatureType() == GEOS_POLYGON || pFeatureLayer->GetFeatureType() == GEOS_MULTIPOLYGON)
			{
				index= m_Combo_TagertLayer.AddString(pLayer->GetName().c_str());
			}
		}
	}
	if(m_Combo_TagertLayer.GetCount() > 0)
		m_Combo_TagertLayer.SetCurSel(0);

	//if( GetFeatureType() == GEOS_POINT || GetFeatureType() == GEOS_MULTIPOINT )
	//else if( GetFeatureType() == GEOS_LINESTRING || GetFeatureType() == GEOS_MULTILINESTRING )
	
	return TRUE;

}
void CDrawingIncrExport::OnBnClickedBtnSlectpath()
{
	UpdateData();

	CString     strOpenFilter = "Incrementalfile(*.xml)|*.xml|All Files(*.*)|*.*||";
	CFileDialog FileDlg(FALSE, "", NULL,  OFN_HIDEREADONLY, strOpenFilter);
	if(FileDlg.DoModal()!=IDOK)
		return;

	m_ExportPath = FileDlg.GetPathName();
	
	this->UpdateData(FALSE);
}

void CDrawingIncrExport::OnBnClickedOk()
{
	this->UpdateData();

	m_DrawingType = m_ComboxType.GetCurSel();

	if(m_Combo_TagertLayer.GetCurSel() < 0)
	{
		MessageBox("请选择导出要素层！");
		return;
	}

	if(m_ExportPath.GetLength()<1)
	{
		MessageBox("请选择导出路径！");
		return;
	}

	m_Combo_TagertLayer.GetLBText(m_Combo_TagertLayer.GetCurSel(),m_TargetLayerName); 
	OnOK();
}

void CDrawingIncrExport::OnCbnSelendcancelComboDrawingtype()
{
	
}

void CDrawingIncrExport::OnBnClickedRadioExportAll()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bExpoertAll = true;
}

void CDrawingIncrExport::OnBnClickedRadioExpoertSelected()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bExpoertAll = false;
}

void CDrawingIncrExport::OnCbnSelchangeComboDrawingtype()
{
	// TODO: 在此添加控件通知处理程序代码
	this->UpdateData();

	m_DrawingType = m_ComboxType.GetCurSel();

	m_Combo_TagertLayer.ResetContent();

	
	Framework::IDocument *pDoc =(Framework::IDocument*)Framework::IUIObject::GetUIObjectByName(Framework::CommonUIName::AppDocument);
	Carto::CMapPtr pMap =pDoc->GetActiveMap();

	Carto::CLayerArray &layers =pMap->GetLayers();

	Carto::ILayerPtr pLayer;
	int index;
	bool bfind =false;
	for(int i=0;i<layers.GetSize();i++)
	{
		pLayer =layers.GetAt(i);
		if(!pLayer)
		{
			continue;
		}
		if(pLayer->GetLayerType()==Carto::FeatureLayer)
		{
			Carto::IFeatureLayerPtr pFeatureLayer = pLayer;
			if(pFeatureLayer->GetFeatureType() == GEOS_POLYGON || pFeatureLayer->GetFeatureType() == GEOS_MULTIPOLYGON)
			{
				if(m_DrawingType ==0)
					index= m_Combo_TagertLayer.AddString(pLayer->GetName().c_str());
			}
			else if(pFeatureLayer->GetFeatureType() == GEOS_LINESTRING || pFeatureLayer->GetFeatureType() == GEOS_MULTILINESTRING)
			{
				if(m_DrawingType ==1)
					index= m_Combo_TagertLayer.AddString(pLayer->GetName().c_str());
			}
			else if(pFeatureLayer->GetFeatureType() == GEOS_POINT || pFeatureLayer->GetFeatureType() == GEOS_MULTIPOINT)
			{
				if(m_DrawingType ==2)
					index= m_Combo_TagertLayer.AddString(pLayer->GetName().c_str());
			}

		}
	}
	if(m_Combo_TagertLayer.GetCount() > 0)
		m_Combo_TagertLayer.SetCurSel(0);

	this->UpdateData(FALSE);
}
