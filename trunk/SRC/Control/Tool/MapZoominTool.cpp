#include "stdafx.h"
#include "MapZoomintool.h"
#include "Control.h"


extern CControlApp theApp;
namespace Control
{


static CToolMapZoomin gToolMapZoomin;

CToolMapZoomin::CToolMapZoomin() : Framework::ITool("MapZoomin")
{
	m_pMapCtrl =NULL;

	m_hCursor =NULL;
}

CToolMapZoomin::~CToolMapZoomin()
{
	if(m_hCursor)
	{
		DeleteObject( m_hCursor );
	}
}

void CToolMapZoomin::Initialize(Framework::IUIObject *pTargetControl)
{
	ITool::Initialize(pTargetControl);

	//初始化光标
	if(m_hCursor==NULL)
	{
		m_hCursor =::LoadCursor( theApp.m_hInstance , MAKEINTRESOURCE( IDC_ZOOMIN) );
	}


	//获取活动地图控件
	m_pMapCtrl = dynamic_cast<Framework::IMapCtrl*>(pTargetControl);
	if(!m_pMapCtrl)
		return;

	//设置光标类型
	m_pMapCtrl->SetCursor(m_hCursor);


}

void CToolMapZoomin::LButtonDownEvent (UINT nFlags, CPoint point)
{
	//获取活动地图控件
	if(!m_pMapCtrl)
		return;

	//获取活动地区
	Carto::CMapPtr pMap = m_pMapCtrl->GetMap();
	if(!pMap)
		return;

	if(m_pMapCtrl->IsActiveX())
	{
		double geoCenterX, geoCenterY;
		pMap->GetDisplay()->GetDisplayTransformation().ConvertDisplayToGeo(point.x,point.y,geoCenterX, geoCenterY);
		pMap->GetDisplay()->GetDisplayTransformation().SetGeoCenterX(geoCenterX);
		pMap->GetDisplay()->GetDisplayTransformation().SetGeoCenterY(geoCenterY);
		pMap->GetDisplay()->GetDisplayTransformation().ZoomViewPosScale(0.667);
	}
	else
	{
		CRectTracker selectBox = CRectTracker(CRect(0,0,0,0),
			CRectTracker::solidLine +
			CRectTracker::resizeOutside );

		selectBox.m_sizeMin = 0;

		bool selected = selectBox.TrackRubberBand(dynamic_cast<CWnd*>(m_pMapCtrl), point, FALSE );

		CRect rect = selectBox.m_rect;
		rect.NormalizeRect();

		if( ( rect.BottomRight().x - rect.TopLeft().x ) < 10 &&
			( rect.BottomRight().y - rect.TopLeft().y ) < 10 )
			selected = false;


		if( selected == true )
		{
			GEOMETRY::geom::Envelope envelop;
			DIS_RECT disrect;
			disrect.left = rect.left;
			disrect.right = rect.right;
			disrect.top = rect.top;
			disrect.bottom = rect.bottom;

			pMap->GetDisplay()->GetDisplayTransformation().TransformToGeo(disrect,&envelop);
			pMap->GetDisplay()->GetDisplayTransformation().FitViewBound(envelop,true);

		}
		else
		{
			double geoCenterX, geoCenterY;
			pMap->GetDisplay()->GetDisplayTransformation().ConvertDisplayToGeo(point.x,point.y,geoCenterX, geoCenterY);
			pMap->GetDisplay()->GetDisplayTransformation().SetGeoCenterX(geoCenterX);
			pMap->GetDisplay()->GetDisplayTransformation().SetGeoCenterY(geoCenterY);
			pMap->GetDisplay()->GetDisplayTransformation().ZoomViewPosScale(0.667);
		}
		
	}
	
     m_pMapCtrl->UpdateControl(drawAll);
	//记录范围
    GEOMETRY::geom::Envelope curExtent;
    pMap->GetDisplay()->GetDisplayTransformation().GetGeoBound(curExtent);
    pMap->GetDisplay()->GetDisplayTransformation().RecordCurExtent(curExtent);

}

Framework::ITool* CToolMapZoomin::Clone()
{
	return new CToolMapZoomin();
}

}