#include "stdafx.h"
#include "ActionSelByPolygon.h"
#include "SpatialQuery.h"
#include <geometry/geom/LinearRing.h>
#include <geometry/geom/Polygon.h>
#include "..\otMapControl.h"
#include "..\otMapCtrl.h"

CActionSelByPolygon::CActionSelByPolygon() : ISelectFeatureTool(actionSelectByPolygon)
{
	RegisterAction(actionSelectByPolygon,this);
}

CActionSelByPolygon::~CActionSelByPolygon()
{

}

void CActionSelByPolygon::Init(CotMapCtrl *pMapCtrl,Carto::CMap *pMap)
{
	ISelectFeatureTool::Init(pMapCtrl,pMap); 

	//创建一个画笔
	if(!m_pSketch)
	{
		m_pSketch.reset(new Display::CGeometrySketch(GEOMETRY::geom::GEOS_POLYGON));
	}
	m_pSketch->SetEmpty();


}

void CActionSelByPolygon::LButtonDownEvent(UINT nFlags, CPoint point)
{
	//如果当前点和之前的点坐标相同，则认为是误点
	if(point==m_lastPt)
	{
		return;
	}

	if(!m_pMap)
	{
		return;
	}

	GEOMETRY::geom::Coordinate coord;

	m_pMap->GetDisplay()->GetDisplayTransformation().ConvertDisplayToGeo(point.x,point.y,coord);

	//在画笔中添加点
	m_pSketch->AddPoint(coord);

	m_lastPt =point;

	//
	ActionDraw();


}

void CActionSelByPolygon::ActionDraw()
{

	

	//更新显示
	Display::IDisplayPtr dispaly = m_pMap->GetDisplay();
	dispaly->SetDrawBuffer(drawEdit);
	dispaly->DrawBackgroud();

	m_pSketch->Draw(dispaly);
	m_pMapCtrl->RefreshScreen();

}

void CActionSelByPolygon::MouseMoveEvent(UINT nFlags, CPoint point)
{
	

	GEOMETRY::geom::Coordinate coord;

	m_pMap->GetDisplay()->GetDisplayTransformation().ConvertDisplayToGeo(point.x,point.y,coord);
	m_pSketch->MouseMove(coord);

	//
	ActionDraw();


}

void CActionSelByPolygon::LButtonDblClkEvent(UINT nFlags, CPoint point)
{
	if(m_pSketch->GetGeometry()->PointCount()<2)
	{
		return;
	}
	
	GEOMETRY::geom::Geometry *pGeometry =m_pSketch->GetGeometry()->clone();
	//构造一个空间查询条件
	Geodatabase::CSpatialQuery queryfilter;
	queryfilter.SetGeometry(pGeometry);
	queryfilter.SetSpatialRel(Geodatabase::SpatialRelIntersects);

	ISelectFeatureTool::Select(&queryfilter);

	m_pSketch->SetEmpty();

    pGeometry->getFactory()->destroyGeometry(pGeometry);

	//重新刷新视图
	ActionDraw();

}


