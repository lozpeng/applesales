#include "StdAfx.h"
#include "otLayerProp.h"
#include "LayerPropSheet.h"
namespace otComUI
{

CotLayerProp::CotLayerProp(void)
{

}

CotLayerProp::~CotLayerProp(void)
{

}

int CotLayerProp::ShowLayerProp(Carto::ILayerPtr pLayer, otComUI::ILayerPropCallback *pCallback)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CLayerPropSheet sheet("Õº≤„ Ù–‘");
	sheet.SetLayer(pLayer);
	sheet.SetCallback(pCallback);

	int ret =sheet.DoModal();

	return ret;
}

}
