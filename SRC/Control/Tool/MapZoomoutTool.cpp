#include "stdafx.h"
#include "MapZoomouttool.h"
#include "Control.h"


extern CControlApp theApp;
namespace Control
{


static CToolMapZoomout gToolMapZoomout;

CToolMapZoomout::CToolMapZoomout() : Framework::ITool("MapZoomout")
{
	m_pMapCtrl =NULL;

	m_hCursor =NULL;
}

CToolMapZoomout::~CToolMapZoomout()
{
	if(m_hCursor)
	{
		DeleteObject( m_hCursor );
	}
}

void CToolMapZoomout::Initialize(Framework::IUIObject *pTargetControl)
{
	ITool::Initialize(pTargetControl);

	//初始化光标
	if(m_hCursor==NULL)
	{
		m_hCursor =::LoadCursor( theApp.m_hInstance , MAKEINTRESOURCE( IDC_ZOOMOUT) );
	}


	//获取活动地图控件
	m_pMapCtrl = dynamic_cast<Framework::IMapCtrl*>(pTargetControl);
	if(!m_pMapCtrl)
		return;

	//设置光标类型
	m_pMapCtrl->SetCursor(m_hCursor);


}

void CToolMapZoomout::LButtonDownEvent (UINT nFlags, CPoint point)
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
		pMap->GetDisplay()->GetDisplayTransformation().ZoomViewPosScale(1.5);
	}
	else
	{
		CRectTracker selectBox = CRectTracker(CRect(0,0,0,0),
			CRectTracker::solidLine +
			CRectTracker::resizeOutside );

		selectBox.m_sizeMin = 0;

		bool selected = selectBox.TrackRubberBand(dynamic_cast<CWnd*>(m_pMapCtrl), point, TRUE );

		CRect rect = selectBox.m_rect;
		rect.NormalizeRect();

		if( ( rect.BottomRight().x - rect.TopLeft().x ) < 10 &&
			( rect.BottomRight().y - rect.TopLeft().y ) < 10 )
			selected = false;


		if( selected == true )
		{
			GEOMETRY::geom::Envelope envelop;

			pMap->GetDisplay()->GetDisplayTransformation().GetGeoBound(envelop);

			long lWidth = rect.Width();
			long lHeight = rect.Height();

			double rx = envelop.getWidth()/ lWidth;
			double ry = envelop.getHeight()/ lHeight;

			double dbScale = (rx > ry) ? rx : ry;

			pMap->GetDisplay()->GetDisplayTransformation().ZoomToFixScale(dbScale);

			CRect viewRect =pMap->GetDisplay()->GetDisplayTransformation().GetViewBound().GetRect();

			double dx=(rect.CenterPoint().x-viewRect.CenterPoint().x)*dbScale;
			double dy=(viewRect.CenterPoint().y-rect.CenterPoint().y)*dbScale;

			pMap->GetDisplay()->GetDisplayTransformation().MoveViewBound(dx,dy);

		}
		else
		{
			double geoCenterX, geoCenterY;
			pMap->GetDisplay()->GetDisplayTransformation().ConvertDisplayToGeo(point.x,point.y,geoCenterX, geoCenterY);
			pMap->GetDisplay()->GetDisplayTransformation().SetGeoCenterX(geoCenterX);
			pMap->GetDisplay()->GetDisplayTransformation().SetGeoCenterY(geoCenterY);
			pMap->GetDisplay()->GetDisplayTransformation().ZoomViewPosScale(1.5);
		}
	}
	
	m_pMapCtrl->UpdateControl(drawAll);

	//记录范围
	GEOMETRY::geom::Envelope curExtent;
	pMap->GetDisplay()->GetDisplayTransformation().GetGeoBound(curExtent);
	pMap->GetDisplay()->GetDisplayTransformation().RecordCurExtent(curExtent);

}

Framework::ITool* CToolMapZoomout::Clone()
{
	return new CToolMapZoomout();
}

}