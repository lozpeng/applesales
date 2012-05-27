#include "StdAfx.h"
#include "LayerPropSheet.h"
#include "IMapCtrl.h"
#include "LayerBasepropPage.h"
#include "RasterPropPage.h"
#include "FeatureRenderPage.h"
#include "RasterRenderPage.h"

IMPLEMENT_DYNAMIC(CLayerPropSheet, CPropertySheet)


BEGIN_MESSAGE_MAP(CLayerPropSheet, CPropertySheet)
	ON_BN_CLICKED(ID_APPLY_NOW , &CLayerPropSheet::OnApply)
	ON_BN_CLICKED(IDOK, &CLayerPropSheet::OnOK)
END_MESSAGE_MAP()

CLayerPropSheet::CLayerPropSheet(CString name , CWnd *pWnd) : CPropertySheet(name , pWnd)
{
	m_psh.dwFlags &= ~PSH_HASHELP;
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

	CLayerBasepropPage commonPage;
	CFeatureRenderPage featurePage;
	CRasterPropPage rasterPage;
	CRasterRenderPage rasterRenderPage;

	commonPage.SetLayer(m_layer.get());
	AddPage(&commonPage);

	
	
	Carto::LAYER_TYPE layerType = m_layer->GetLayerType();
	if (layerType == Carto::FeatureLayer)
	{
		featurePage.SetLayer(m_layer.get());
		AddPage(&featurePage);
	}
	else if (layerType == Carto::RasterLayer)
	{
		rasterPage.SetLayer(m_layer.get());
		AddPage(&rasterPage);

		rasterRenderPage.SetLayer(m_layer.get());
		AddPage(&rasterRenderPage);
	
	}


	return CPropertySheet::DoModal();
}

void CLayerPropSheet::OnOK()
{
	OnApply();
	CPropertySheet::OnClose();
	
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
	Framework::IMapCtrl *pMapCtrl =Framework::IMapCtrl::GetActiveMapCtrl();
	if(!pMapCtrl)
	{
		return;
	}
	pMapCtrl->UpdateControl(drawAll);
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
