#include "stdafx.h"
#include "ActionZoomIn.h"
#include "..\otMapControl.h"
#include "..\otMapCtrl.h"
#include "Map.h"



CActionZoomin::CActionZoomin() : IAction(actionZoomIn)
{
	RegisterAction(actionZoomIn,this);
}

CActionZoomin::~CActionZoomin()
{

}

void CActionZoomin::Init(CotMapCtrl *pMapCtrl,Carto::CMap *pMap)
{
	IAction::Init(pMapCtrl,pMap);


	pMapCtrl->SetCursorType(cursorZoomIn);

}

void CActionZoomin::LButtonDownEvent (UINT nFlags, CPoint point)
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

	bool selected = selectBox.TrackRubberBand(m_pMapCtrl, point, FALSE );

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

		m_pMap->GetDisplay()->GetDisplayTransformation().TransformToGeo(disrect,&envelop);
		m_pMap->GetDisplay()->GetDisplayTransformation().FitViewBound(envelop,true);

	}
	else
	{
		m_pMap->GetDisplay()->GetDisplayTransformation().ZoomViewPosScale(0.667);
	}
	m_pMapCtrl->Refresh();

}