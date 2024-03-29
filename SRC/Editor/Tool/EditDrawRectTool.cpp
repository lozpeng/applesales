#include "stdafx.h"
#include "EditDrawRectTool.h"
#include "IMapCtrl.h"
#include "SpatialQuery.h"
#include "SymbolFactory.h"
#include "SimpleMarkerSymbol.h"
#include "SimpleLineSymbol.h"
#include "ISymbol.h"
#include "DisplayDef.h"
#include "Editor.h"
#include "ILayer.h"
#include "IGeoDataObject.h"
#include "IWorkspace.h"
#include <Geometry/geom/GeometryFactory.h>
#include <Geometry/geom/Geometry.h>
#include <Geometry/geom/Coordinate.h>
#include <Geometry/geom/MultiLineString.h>
#include <Geometry/geom/Polygon.h>

namespace Editor
{

static CActionEditDrawRect gActionEditDrawRect;

CActionEditDrawRect::CActionEditDrawRect(void) : ITool("ActionEditDrawRect")
{
	
}

CActionEditDrawRect::~CActionEditDrawRect(void)
{

}


//初始化

void CActionEditDrawRect::Initialize(Framework::IUIObject *pTargetControl)
{
	ITool::Initialize(pTargetControl);
}
void CActionEditDrawRect::LButtonDownEvent(UINT nFlags, CPoint point)
{
	if (!m_bStartDraw)
	{
		m_ulPt = point;

		m_bStartDraw = true;
	}
	else
	{
		m_lrPt = point;

		m_bStartDraw = false;

		ActionDraw();

		AddRect(m_ulPt, m_lrPt);
	}
}

void CActionEditDrawRect::MouseMoveEvent(UINT nFlags, CPoint point)
{	
	if (m_bStartDraw)
	{
		m_lrPt = point;

		ActionDraw();
	}
}

/*--------------------将绘制的矩形添加到目标图层中---------------------*/
void CActionEditDrawRect::AddRect(CPoint ulPt, CPoint lrPt)
{
	//获取活动地图控件
	Framework::IMapCtrl *pMapCtrl = Framework::IMapCtrl::GetActiveMapCtrl();
	if(!pMapCtrl)
		return;

	//获取活动地区
	Carto::CMapPtr pMap = pMapCtrl->GetMap();
	if(!pMap)
		return;

	//获得编辑类
	//Editor::CEditorPtr pEdit =pMap->GetEditor();
	//if(!pEdit)
	//{
	//	return;
	//}

	//获得编辑图层的工作空间
	Carto::ILayer *pLayer ;//= pEdit->GetCurLayer();
	if (!pLayer)
	{
		return;
	}

	Geodatabase::IGeodataObjectPtr pDataObject = pLayer->GetDataObject();
	if (!pDataObject)
	{
		return;
	}

	Geodatabase::IWorkspace* pWorkspace = pDataObject->GetWorkspace();
	if (!pWorkspace)
	{
		return;
	}

	//目前只支持对文件进行编辑
	if(pWorkspace->GetType()!=Geodatabase::WT_FileSystem)
	{
		return;
	}

	double minx,miny,maxx,maxy;
	minx =min(ulPt.x,lrPt.x);
	miny =min(ulPt.y,lrPt.y);
	maxx =max(ulPt.x,lrPt.x);
	maxy =max(ulPt.y,lrPt.y);

	//四个角点坐标
	Coordinate p1;
	Coordinate p2;
	Coordinate p3;
	Coordinate p4;
	Coordinate p5;
	
	pMap->GetDisplay()->GetDisplayTransformation().ConvertDisplayToGeo(minx, maxy, p1);
	pMap->GetDisplay()->GetDisplayTransformation().ConvertDisplayToGeo(maxx, maxy, p2);
	pMap->GetDisplay()->GetDisplayTransformation().ConvertDisplayToGeo(maxx, miny, p3);
	pMap->GetDisplay()->GetDisplayTransformation().ConvertDisplayToGeo(minx, miny, p4);
	pMap->GetDisplay()->GetDisplayTransformation().ConvertDisplayToGeo(minx, maxy, p5);

	bool bz,bm;
	Geodatabase::IFeatureClass *pFeatureClass = dynamic_cast<Geodatabase::IFeatureClass*>(pDataObject.get());
	bz =pFeatureClass->HasZ();
	bm =pFeatureClass->HasM();

	//要添加的几何图形
	Geometry *pGeometry = NULL;

	long lShapeType= pFeatureClass->ShapeType();

	switch (lShapeType)
	{
	case GEOMETRY::geom::GEOS_LINESTRING:
		{
			pGeometry = (Geometry*) GeometryFactory::getDefaultInstance()->createLineString();
			pGeometry->SetbZ(bz);
			pGeometry->SetbM(bm);

			pGeometry->AddPoint(p1);
			pGeometry->AddPoint(p2);
			pGeometry->AddPoint(p3);
			pGeometry->AddPoint(p4);
			pGeometry->AddPoint(p5);
		}
		break;

	case GEOMETRY::geom::GEOS_MULTILINESTRING:
		{
			pGeometry = (Geometry*)GeometryFactory::getDefaultInstance()->createMultiLineString();
			pGeometry->SetbZ(bz);
			pGeometry->SetbM(bm);

			Geometry *pg =NULL;
			pg =(Geometry*) GeometryFactory::getDefaultInstance()->createLineString();
			pg->AddPoint(p1);
			pg->AddPoint(p2);
			pg->AddPoint(p3);
			pg->AddPoint(p4);
			pg->AddPoint(p5);

			((MultiLineString*)pGeometry)->AddGeometry(pg);
		}

		break;

	case GEOMETRY::geom::GEOS_POLYGON:
		{
			pGeometry = (Geometry*)GeometryFactory::getDefaultInstance()->createPolygon();
			pGeometry->SetbZ(bz);
			pGeometry->SetbM(bm);

			Geometry *pg =NULL;
			pg =(Geometry*) GeometryFactory::getDefaultInstance()->createLinearRing();
			pg->AddPoint(p1);
			pg->AddPoint(p2);
			pg->AddPoint(p3);
			pg->AddPoint(p4);
			pg->AddPoint(p5);

			((GEOMETRY::geom::Polygon*)pGeometry)->AddGeometry(pg);
		}

		break;

	default:
		return;
		break;
	}

	//pEdit->AppendGeometry(pGeometry);

	delete pGeometry;
	pGeometry =NULL;
	
	pMapCtrl->UpdateControl(drawAll);
}

/*--------------------在空间上绘制临时图形---------------------*/
void CActionEditDrawRect::ActionDraw()
{
	//获取活动地图控件
	Framework::IMapCtrl *pMapCtrl = Framework::IMapCtrl::GetActiveMapCtrl();
	if(!pMapCtrl)
		return;


	//获取活动地区
	Carto::CMapPtr pMap = pMapCtrl->GetMap();
	if(!pMap)
		return;

	//更新显示
	Display::IDisplayPtr dispaly = pMap->GetDisplay();
	dispaly->SetDrawBuffer(drawEdit);
	dispaly->DrawBackgroud();

	//构造矩形
	long left = m_ulPt.x;
	long top  = m_ulPt.y;
	long right = m_lrPt.x;
	long bottom = m_lrPt.y;

	DIS_RECT *pRect;
	CreateDisplayRect(pRect);
	pRect->left = left;
	pRect->right = right;
	pRect->top = top;
	pRect->bottom = bottom;

	//绘制矩形
	Display::CDC *pDC =dispaly->GetDrawDC();

	LINE_STYLE pLineStyle;
	pLineStyle.lColor = RGB(0, 0, 0);
	pLineStyle.lWidth = 0.6f;
	pLineStyle.eStyle = SOLID;
	DISPLAY_HANDLE pnewPen = pDC->CreatePen(pLineStyle);

	DISPLAY_HANDLE pold = pDC->SelectObject(pnewPen);

	pDC->DrawRect(*pRect);

	delete pRect;
	pRect = NULL;

	pDC->SelectObject(pold);
	pDC->RemoveHandle(pnewPen);

	pMapCtrl->RefreshScreen();
}


}