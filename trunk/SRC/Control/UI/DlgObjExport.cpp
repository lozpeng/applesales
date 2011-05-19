// DlgObjExport.cpp : 实现文件
//

#include "stdafx.h"
#include "Control.h"
#include "DlgObjExport.h"
#include "IDocument.h"
#include "IMapCtrl.h"
#include "IWorkspace.h"
#include "IFeatureCursor.h"
// CDlgObjExport 对话框

IMPLEMENT_DYNAMIC(CDlgObjExport, CDialog)

CDlgObjExport::CDlgObjExport(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgObjExport::IDD, pParent)
{

	m_SrcFeatureLayer = NULL;
}

CDlgObjExport::~CDlgObjExport()
{
}

void CDlgObjExport::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_Export, m_Combox_Export);
}


BEGIN_MESSAGE_MAP(CDlgObjExport, CDialog)
	ON_BN_CLICKED(IDC_RADIO_EXPOERT_SELECTED, &CDlgObjExport::OnBnClickedRadioExpoertSelected)
	ON_BN_CLICKED(IDC_RADIO_EXPORT_ALL, &CDlgObjExport::OnBnClickedRadioExportAll)
	ON_BN_CLICKED(IDOK, &CDlgObjExport::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDlgObjExport::OnBnClickedCancel)
END_MESSAGE_MAP()

BOOL CDlgObjExport::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_bExpoertAll = true;

	CButton* pFusionType =(CButton*)GetDlgItem(IDC_RADIO_EXPORT_ALL);
	pFusionType->SetCheck(1);

	this->UpdateData(false);

	if (m_SrcFeatureLayer == NULL)
		return 0;

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
			
			Carto::IFeatureLayerPtr pFeaturelayer = pLayer;
			
			if(pFeaturelayer->GetFeatureType() == m_SrcFeatureLayer->GetFeatureType())
			{
				index= m_Combox_Export.AddString(pLayer->GetName().c_str());
			}
			
		}
	}
	if(m_Combox_Export.GetCount() > 0)
		m_Combox_Export.SetCurSel(0);

	return 1;
}
// CDlgObjExport 消息处理程序

void CDlgObjExport::OnBnClickedRadioExpoertSelected()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bExpoertAll = false;
}

void CDlgObjExport::OnBnClickedRadioExportAll()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bExpoertAll = true;
}

void CDlgObjExport::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	this->UpdateData();

	if(m_Combox_Export.GetCurSel() < 0)
	{
		MessageBox("请选择导出目标层！");
		return;

	}

	CString fileName;
	m_Combox_Export.GetLBText(m_Combox_Export.GetCurSel(),fileName); 

	Framework::IDocument *pDoc =(Framework::IDocument*)Framework::IUIObject::GetUIObjectByName(Framework::CommonUIName::AppDocument);
	Carto::CMapPtr pMap =pDoc->GetActiveMap();
	Framework::IMapCtrl* pMapCtrl = pDoc->GetLinkMapCtrl();
	Carto::CLayerArray &layers = pMap->GetLayers();

	Carto::ILayerPtr pLayer;
	Carto::IFeatureLayerPtr destFeaturelayer;
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
			if (strcmp(pLayer->GetName().c_str(),fileName) == 0)
			{
				destFeaturelayer = pLayer;
				break;
			}
		}
	}

	FeatureLayer2Featurelayer(m_SrcFeatureLayer,destFeaturelayer);

	pMapCtrl->UpdateControl((DrawContent)(drawElement | drawAll));
	OnOK();
}

void CDlgObjExport::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	OnCancel();
}
void CDlgObjExport::FeatureLayer2Featurelayer(Carto::IFeatureLayerPtr pSrcFeatureLayer,Carto::IFeatureLayerPtr pDestFeatureLayer)
{

	if (pSrcFeatureLayer==NULL || pDestFeatureLayer == NULL)
		return;



	Geodatabase::IWorkspace *pDestWorkspace = pDestFeatureLayer->GetDataObject()->GetWorkspace();
	//开始编辑
	bool srcState = pDestWorkspace->IsEditing();
	if(srcState== false)
		pDestWorkspace->StartEdit();
	Geodatabase::IFeatureClassPtr pDestFeatureClass =  (Geodatabase::IFeatureClassPtr) pDestFeatureLayer->GetDataObject();
	Geodatabase::IFeatureClassPtr pSrcFeatureClass =  (Geodatabase::IFeatureClassPtr) pSrcFeatureLayer->GetDataObject();

	GEOMETRY::geom::Geometry *pGeometry;

	if (m_bExpoertAll)
	{
		GEOMETRY::geom::Envelope pEnvelope;
		Geodatabase::CFeaturePtr pFeature;
		Geodatabase::CFeaturePtr pNewFeature;
		
		pSrcFeatureLayer->GetDataObject()->GetExtent(&pEnvelope);
		Geodatabase::CSimpleQuery query;
		std::string strFields =pSrcFeatureClass->ShapeFieldName();
		query.AddField(strFields.c_str());
		Geodatabase::ICursorPtr pCursor = pSrcFeatureClass->QueryByExtent(&pEnvelope,&query);
		Geodatabase::IFeatureCursorPtr pFeatureCursor = pCursor;
		while(!pFeatureCursor->IsEOF())
		{
			pFeature = pFeatureCursor->NextRow();
			pGeometry = pFeature->GetShapeClone();
			//产生一个新的要素
			pNewFeature =pDestFeatureClass->CreateFeature();
			pNewFeature->SetShape( pGeometry);

			//提交要素
			pDestFeatureClass->AddFeature(pNewFeature.get());

		}
		

	}
	else
	{
		Geodatabase::ISelctionSetPtr pSelectionSet = pSrcFeatureLayer->GetSelection();
		if(pSelectionSet == NULL)
			return;
		pSelectionSet->ResetIndex();
		long fid = 0;
		

		while(!pSelectionSet->IsEOF())
		{
			fid =pSelectionSet->NextID();
			pGeometry =pSrcFeatureClass->GetFeatureShape(fid);

			Geodatabase::CFeaturePtr pFeature;
			//产生一个新的要素
			pFeature =pDestFeatureClass->CreateFeature();
			pFeature->SetShape( pGeometry->clone());

			//提交要素
			pDestFeatureClass->AddFeature(pFeature.get());

		}
	}
	

	pDestWorkspace->StopEditOperation();
	if(srcState == false)
		pDestWorkspace->StopEdit(true);


	
}