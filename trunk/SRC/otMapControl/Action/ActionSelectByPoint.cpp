#include "stdafx.h"
#include "ActionSelectByPoint.h"
#include "SpatialQuery.h"
#include <geometry/geom/LinearRing.h>
#include <geometry/geom/Polygon.h>
#include "../otMapControl.h"
#include "../otMapCtrl.h"


CActionSelByPoint::CActionSelByPoint() : ISelectFeatureTool(actionSelectByPoint)
{
	RegisterAction(actionSelectByPoint,this);
}

CActionSelByPoint::~CActionSelByPoint()
{

}


void CActionSelByPoint::LButtonDownEvent(UINT nFlags, CPoint point)
{
	


	GEOMETRY::geom::Envelope envelop;
	DIS_RECT rect;
	rect.left =point.x -m_SnapTol;
	rect.right =point.x+m_SnapTol;
	rect.top =point.y -m_SnapTol;
	rect.bottom =point.y+m_SnapTol;
	
	m_pMap->GetDisplay()->GetDisplayTransformation().TransformToGeo(rect,&envelop);
	//构造一个用于查询的多边形

	Geodatabase::CSpatialQuery queryfilter;


	//构造一个空间查询条件
	GEOMETRY::geom::Geometry *pGeometry =GEOMETRY::geom::GeometryFactory::getDefaultInstance()->toGeometry(&envelop);
	queryfilter.SetGeometry(pGeometry);
	queryfilter.SetSpatialRel(Geodatabase::SpatialRelIntersects);

	ISelectFeatureTool::Select(&queryfilter);
}


