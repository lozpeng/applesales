#include "stdafx.h"
#include "ActionZoomOut.h"
#include "../otMapControl.h"
#include "../otMapCtrl.h"
#include "Map.h"



CActionZoomOut::CActionZoomOut() : IAction(actionZoomOut)
{
	RegisterAction(actionZoomOut,this);
}

CActionZoomOut::~CActionZoomOut()
{

}

void CActionZoomOut::Init(CotMapCtrl *pMapCtrl,Carto::CMap *pMap)
{
	IAction::Init(pMapCtrl,pMap);


	pMapCtrl->SetCursorType(cursorZoomOut);

}

void CActionZoomOut::LButtonDownEvent (UINT nFlags, CPoint point)
{
	if(!m_pMapCtrl || !m_pMap)
	{
		return;
	}


	//Selection Box
	CRectTracker selectBox = CRectTracker(CRect(0,0,0,0),
		CRectTracker::solidLine +
		CRectTracker::resizeOutside );

	selectBox.m_sizeMin = 0;

	bool selected = selectBox.TrackRubberBand(m_pMapCtrl, point, TRUE );

	CRect rect = selectBox.m_rect;
	rect.NormalizeRect();

	if( ( rect.BottomRight().x - rect.TopLeft().x ) < 10 &&
		( rect.BottomRight().y - rect.TopLeft().y ) < 10 )
		selected = false;


	if( selected == true )
	{
		GEOMETRY::geom::Envelope envelop;

		m_pMap->GetDisplay()->GetDisplayTransformation().GetGeoBound(envelop);

		long lWidth = rect.Width();
		long lHeight = rect.Height();

		double rx = envelop.getWidth()/ lWidth;
		double ry = envelop.getHeight()/ lHeight;

		double dbScale = (rx > ry) ? rx : ry;

		m_pMap->GetDisplay()->GetDisplayTransformation().ZoomToFixScale(dbScale);

		CRect viewRect =m_pMap->GetDisplay()->GetDisplayTransformation().GetViewPosition().GetViewBound().GetRect();

		double dx=(rect.CenterPoint().x-viewRect.CenterPoint().x)*dbScale;
		double dy=(viewRect.CenterPoint().y-rect.CenterPoint().y)*dbScale;

		m_pMap->GetDisplay()->GetDisplayTransformation().MoveViewBound(dx,dy);

	}
	else
	{
		m_pMap->GetDisplay()->GetDisplayTransformation().ZoomViewPosScale(1.5);
	}
	
	m_pMapCtrl->Refresh();

}