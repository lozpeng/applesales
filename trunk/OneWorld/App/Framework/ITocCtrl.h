#ifndef _ITocCtrl_h
#define _ITocCtrl_h

#include "ICtrl.h"
#include <owScene/Layer.h>
#include <owScene/Terrain.h>

class cOSG;

namespace Framework
{
	enum TOC_CONTROL_ITEM
	{
		ItemNone, 
		ItemMap,
		ItemLayer,
		ItemHeading,
		ItemLegend
	};

	class FRAMEWORK_DLL ITocCtrl : public ICtrl
	{
		struct TREESTATE
		{
			bool bExpand;
			bool bSelected;
		};

	public:
		ITocCtrl();
		virtual ~ITocCtrl();
	public:
		virtual void RefreshFromOSG(cOSG* pOsg) = 0;
		virtual void RefreshFromTerrain(owScene::Terrain* pTerrain) = 0;
		virtual void AddLayer(owScene::Layer* player, BOOL bExpand = TRUE) = 0;
		virtual void DeleteLayer(owScene::Layer* pLayer) = 0;
		virtual void DeleteAllLayers() = 0;
	};

}
#endif