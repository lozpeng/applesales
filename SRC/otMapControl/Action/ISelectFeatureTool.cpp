#include "stdafx.h"
#include "ISelectFeatureTool.h"
#include "ISelectionSet.h"
#include "ILayer.h"
#include "FeatureLayer.h"
#include "..\otMapControl.h"
#include "..\otMapCtrl.h"


long ISelectFeatureTool::m_lSelMode =Carto::SELECT_REPLACE;

int  ISelectFeatureTool::m_SnapTol =3;

ISelectFeatureTool::ISelectFeatureTool(long id):IAction(id)
{
	
}
ISelectFeatureTool::~ISelectFeatureTool()
{

}

 

void ISelectFeatureTool::Init(CotMapCtrl *pMapCtrl,Carto::CMap *pMap)
{
	if((!pMapCtrl) ||(!pMap))
	{
		return;
	}

	//设置光标类型
	pMapCtrl->SetCursorType(cursorNormal);

	IAction::Init(pMapCtrl,pMap);
}

void ISelectFeatureTool::Select(Geodatabase::CSimpleQuery *pQuery)
{
	

	Carto::CLayerArray &layers =m_pMap->GetLayers();
    
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
	m_pMapCtrl->UpdateContent(otDrawGeoSelection);

	
}

void ISelectFeatureTool::SelecRowsInAttributeTable()
{

}	
