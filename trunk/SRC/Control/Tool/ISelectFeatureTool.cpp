#include "stdafx.h"
#include "ISelectFeatureTool.h"

namespace Control
{

long ISelectFeatureTool::m_lSelMode =Carto::SELECT_REPLACE;

int  ISelectFeatureTool::m_SnapTol =3;

ISelectFeatureTool::ISelectFeatureTool(const char* name): Framework::ITool(name)
{
   m_pMapCtrl =NULL;
}
ISelectFeatureTool::~ISelectFeatureTool()
{

}




void ISelectFeatureTool::Select(Geodatabase::CSimpleQuery *pQuery)
{
	if(!m_pMapCtrl)
		return;


	//获取活动地区
	Carto::CMapPtr pMap = m_pMapCtrl->GetMap();
	if(!pMap)
		return;

	Carto::CLayerArray &layers =pMap->GetLayers();

	Carto::ILayerPtr pLayer;
	for(int i=0;i<layers.GetSize();i++)
	{
		pLayer =layers.GetAt(i);
		if(!pLayer->GetVisible())
		{
			continue;
		}
		if(pLayer->GetLayerType()!=Carto::FeatureLayer)
		{
			continue;
		}

		pLayer->Select(pQuery,Carto::SELECT_OPTION(m_lSelMode));


	}
	m_pMapCtrl->UpdateControl(drawGeoSelection);


}



}