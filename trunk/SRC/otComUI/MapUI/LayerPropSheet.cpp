#include "StdAfx.h"
#include "LayerPropSheet.h"
#include "CommonPropPage.h"
#include "FeatureRenderPage.h"
#include "RasterPropShowPage.h"
#include "DlgRasGeoProperty.h"

IMPLEMENT_DYNAMIC(CLayerPropSheet, CPropertySheet)


BEGIN_MESSAGE_MAP(CLayerPropSheet, CPropertySheet)
	ON_BN_CLICKED(ID_APPLY_NOW , &CLayerPropSheet::OnApply)
END_MESSAGE_MAP()

CLayerPropSheet::CLayerPropSheet(CString name , CWnd *pWnd) : CPropertySheet(name , pWnd)
{
	m_psh.dwFlags &= ~PSH_HASHELP;

	m_pCallback =NULL;
}

CLayerPropSheet::~CLayerPropSheet(void)
{
}


void CLayerPropSheet::SetLayer(Carto::ILayerPtr layer)
{
	m_layer = layer;
}

INT_PTR CLayerPropSheet::DoModal()
{
	if (m_layer == NULL)
	{
		return -1;
	}

	CCommonPropPage commonPage;
	commonPage.SetLayer(m_layer.get());
	AddPage(&commonPage);

	CFeatureRenderPage featurePage;

	CRasterPropShowPage rasPage;		
	
	CDlgRasGeoProperty rasGeoPage;
	
	Carto::LAYER_TYPE layerType = m_layer->GetLayerType();
	if (layerType == Carto::FeatureLayer)
	{
		featurePage.SetLayer(m_layer.get());
		AddPage(&featurePage);
	}
	else if (layerType == Carto::RasterLayer)
	{

		Carto::CRasterLayerPtr pRasterLayer = (Carto::CRasterLayerPtr)m_layer;
		rasPage.SetLayer(pRasterLayer);
		AddPage(&rasPage);


		rasGeoPage.SetLayer(pRasterLayer);
		AddPage(&rasGeoPage);
	
	}


	return CPropertySheet::DoModal();
}

void CLayerPropSheet::OnApply()
{
	//调用每个页面的应用函数
	int pagecount =GetPageCount();
	for(int i=0;i<pagecount;i++)
	{
		CPropertyPage* page =GetPage(i);
		page->OnApply();
	}
	//刷新视图
	if(m_pCallback)
	{
		m_pCallback->UpdateMapCtrl();
	}
}
BOOL CLayerPropSheet::OnInitDialog()
{
	BOOL bResult = CPropertySheet::OnInitDialog();

	CWnd* pHelp = NULL;
	pHelp = GetDlgItem(ID_APPLY_NOW);

	if (pHelp != NULL)
	{
		CString text = "应用";
		pHelp->SetWindowText(text);
	}
	return bResult;
}
