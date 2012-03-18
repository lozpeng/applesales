#include "stdafx.h"
#include "ActionSelectByRect.h"
#include "SpatialQuery.h"
#include <geometry/geom/LinearRing.h>
#include <geometry/geom/Polygon.h>
#include "..\otMapControl.h"
#include "..\otMapCtrl.h"



CActionSelByRect::CActionSelByRect() : ISelectFeatureTool(actionSelectByRect)
{
	RegisterAction(actionSelectByRect,this);
}

CActionSelByRect::~CActionSelByRect()
{

}


void CActionSelByRect::LButtonDownEvent(UINT nFlags, CPoint point)
{
	

	//Selection Box
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

	if(!selected)
	{
		return;
	}

	GEOMETRY::geom::Envelope envelop;
	DIS_RECT disrect;
	disrect.left = rect.left;
	disrect.right = rect.right;
	disrect.top = rect.top;
	disrect.bottom = rect.bottom;
	m_pMap->GetDisplay()->GetDisplayTransformation().TransformToGeo(disrect,&envelop);

	//构造一个用于查询的多边形

	Geodatabase::CSpatialQuery queryfilter;

	//Coordinate coord;
	//LinearRing *pring = GeometryFactory::getDefaultInstance()->createLinearRing();

	/*coord.x =envelop.getMinX();
	coord.y =envelop.getMinY();
	pring->AddPoint(coord);

	coord.x =cExtent.xmax;
	coord.y =cExtent.ymin;
	pring->AddPoint(coord);

	coord.x =cExtent.xmax;
	coord.y =cExtent.ymax;
	pring->AddPoint(coord);

	coord.x =cExtent.xmin;
	coord.y =cExtent.ymax;
	pring->AddPoint(coord);

	coord.x =cExtent.xmin;
	coord.y =cExtent.ymin;
	pring->AddPoint(coord);*/



	//构造一个空间查询条件
	GEOMETRY::geom::Geometry *pGeometry =GEOMETRY::geom::GeometryFactory::getDefaultInstance()->toGeometry(&envelop);
	queryfilter.SetGeometry(pGeometry);
	queryfilter.SetSpatialRel(Geodatabase::SpatialRelIntersects);

	ISelectFeatureTool::Select(&queryfilter);

	GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(pGeometry);


}


