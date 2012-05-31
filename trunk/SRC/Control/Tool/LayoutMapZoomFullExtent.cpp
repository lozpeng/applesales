#include "stdafx.h"
#include "LayoutMapZoomFullExtent.h"
#include "IMapCtrl.h"

namespace Control
{

	static CLayoutMapZoomFullExtent gActionLayoutMapZoomFullExtent;

	CLayoutMapZoomFullExtent::CLayoutMapZoomFullExtent() : ICommand("LayoutMapFullExtent")
	{

	}

	CLayoutMapZoomFullExtent::~CLayoutMapZoomFullExtent()
	{

	}

	void CLayoutMapZoomFullExtent::Initialize(Framework::IUIObject *pTargetControl)
	{
		ICommand::Initialize(pTargetControl);


		//获取活动地图控件
		m_pLayoutCtrl = dynamic_cast<Framework::ILayoutCtrl*>(pTargetControl);

	}
	void CLayoutMapZoomFullExtent::Click()
	{

		//获取活动地图控件
		Framework::IMapCtrl *pMapCtrl = Framework::IMapCtrl::GetActiveMapCtrl();
		if(!pMapCtrl)
			return;

		//获取活动地区
		Carto::CMapPtr pMap = pMapCtrl->GetMap();
		if(!pMap)
			return;

		pMap->GetDisplay()->GetDisplayTransformation().FitViewBound(pMap->GetExtent());

		GEOMETRY::geom::Envelope viewGeo;
		pMap->GetDisplay()->GetDisplayTransformation().GetGeoBound(viewGeo);
		pMap->SetViewEnvelope(viewGeo);

		Framework::ILayoutCtrl *pLayoutCtrl = Framework::ILayoutCtrl::GetActiveLayoutCtrl();
		if(!pLayoutCtrl)
			return;

		pLayoutCtrl->UpdateControl();


	}

}