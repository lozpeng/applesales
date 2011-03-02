#include "stdafx.h"
#include "ActionEditDrawCircle.h"
#include "IMapCtrl.h"
#include "SpatialQuery.h"
#include "SymbolFactory.h"
#include "SimpleMarkerSymbol.h"
#include "SimpleLineSymbol.h"
#include "ISymbol.h"
#include "DisplayCommon.h"
#include "Editor.h"
#include "ILayer.h"
#include "IDataObject.h"
#include "IWorkspace.h"
#include "TT_Shape.hxx"
#include <Geometry/geom/GeometryFactory.h>
#include <Geometry/geom/Geometry.h>
#include <Geometry/geom/Coordinate.h>
#include <Geometry/geom/MultiLineString.h>
#include <Geometry/geom/Polygon.h>

namespace otEditor
{

static CActionEditDrawCircle gActionEditDrawCircle;

CActionEditDrawCircle::CActionEditDrawCircle(void) : IAction("ActionEditDrawCircle")
{
	RegisterAction("ActionEditDrawCircle", this);
}

CActionEditDrawCircle::~CActionEditDrawCircle(void)
{

}

//初始化
void CActionEditDrawCircle::Triger()
{
	m_bStartDraw = false;

	//获取活动地图控件
	otFramework::IMapCtrl *pMapCtrl = otFramework::IMapCtrl::GetActiveMapCtrl();
	if(!pMapCtrl)
		return;

	//设置光标类型
	pMapCtrl->SetCursorType(cursorNormal);
}

void CActionEditDrawCircle::LButtonDownEvent(UINT nFlags, CPoint point)
{
	if (!m_bStartDraw)
	{
		m_centralPt = point;

		m_bStartDraw = true;
	}
	else
	{
		m_endPt = point;

		m_bStartDraw = false;

		ActionDraw();

		AddCircle();
	}
}

void CActionEditDrawCircle::MouseMoveEvent(UINT nFlags, CPoint point)
{	
	if (m_bStartDraw)
	{
		m_endPt = point;

		ActionDraw();
	}
}

/*--------------------将绘制的矩形添加到目标图层中---------------------*/
void CActionEditDrawCircle::AddCircle(void)
{
	//获取活动地图控件
	otFramework::IMapCtrl *pMapCtrl = otFramework::IMapCtrl::GetActiveMapCtrl();
	if(!pMapCtrl)
		return;

	//获取活动地区
	otCarto::CGeoMapPtr pMap = pMapCtrl->GetActiveMap();
	if(!pMap)
		return;

	otEditor::CEditorPtr pEdit =pMap->GetEditor();
	if(!pEdit)
	{
		return;
	}

	//获得编辑图层的工作空间
	otCarto::ILayer *pLayer = pEdit->GetCurLayer();
	if (!pLayer)
	{
		return;
	}

	GeodataModel::IDataObjectPtr pDataObject = pLayer->GetDataObject();
	if (!pDataObject)
	{
		return;
	}

	GeodataModel::IWorkspace* pWorkspace = pDataObject->GetWorkspace();
	if (!pWorkspace)
	{
		return;
	}

	//目前只支持对文件进行编辑
	if(pWorkspace->GetType()!=GeodataModel::WT_FileSystem)
	{
		return;
	}

	bool bz,bm;
	GeodataModel::IFeatureClass *pFeatureClass = dynamic_cast<GeodataModel::IFeatureClass*>(pDataObject.get());
	bz =pFeatureClass->HasZ();
	bm =pFeatureClass->HasM();

	//要添加的几何图形
	Geometry *pGeometry = NULL;

	long lShapeType= pFeatureClass->ShapeType();

	switch (lShapeType)
	{
		case TT_GEOMETRY::geom::GEOS_LINESTRING:	

			{
				pGeometry = (Geometry*) GeometryFactory::getDefaultInstance()->createLineString();
				pGeometry->SetbZ(bz);
				pGeometry->SetbM(bm);

				SplitCircle(pGeometry);
			}
			break;
		case TT_GEOMETRY::geom::GEOS_MULTILINESTRING:
			{
				pGeometry = (Geometry*)GeometryFactory::getDefaultInstance()->createMultiLineString();
				pGeometry->SetbZ(bz);
				pGeometry->SetbM(bm);

				Geometry *pg =NULL;
				pg =(Geometry*) GeometryFactory::getDefaultInstance()->createLineString();
				SplitCircle(pg);

				((MultiLineString*)pGeometry)->AddGeometry(pg);
			}
			break;

		case TT_GEOMETRY::geom::GEOS_POLYGON:
			{
				pGeometry = (Geometry*)GeometryFactory::getDefaultInstance()->createPolygon();
				pGeometry->SetbZ(bz);
				pGeometry->SetbM(bm);

				Geometry *pg =NULL;
				pg =(Geometry*) GeometryFactory::getDefaultInstance()->createLinearRing();
				SplitCircle(pg);

				((TT_GEOMETRY::geom::Polygon*)pGeometry)->AddGeometry(pg);
			}

			break;

		default:
			return;
			break;
	}
	
	pEdit->AppendGeometry(pGeometry);

	delete pGeometry;
	pGeometry =NULL;

	pMapCtrl->UpdateControl(drawAll);
}

/*--------------------在空间上绘制临时图形---------------------*/
void CActionEditDrawCircle::ActionDraw()
{
	//获取活动地图控件
	otFramework::IMapCtrl *pMapCtrl = otFramework::IMapCtrl::GetActiveMapCtrl();
	if(!pMapCtrl)
		return;


	//获取活动地区
	otCarto::CGeoMapPtr pMap = pMapCtrl->GetActiveMap();
	if(!pMap)
		return;

	//更新显示
	otDisplay::IDisplayPtr dispaly = pMap->GetDisplay();
	dispaly->SetDrawBuffer(drawEdit);
	dispaly->DrawBackgroud();

	//构造圆
	double dRadius = ::sqrt((double)((m_centralPt.x - m_endPt.x) * (m_centralPt.x - m_endPt.x)) 
		+ (double)((m_centralPt.y - m_endPt.y) * (m_centralPt.y - m_endPt.y)));

	INT_POINT pCentralPt;
	pCentralPt.x = m_centralPt.x;
	pCentralPt.y = m_centralPt.y;

	DIS_CIRCLE *pCirlce;
	CreateDisplayCircle(pCirlce);
	pCirlce->center = pCentralPt;
	pCirlce->Radio = dRadius;

	//绘制圆
	otDisplay::CDC *pDC =dispaly->GetDrawDC();

	LINE_STYLE pLineStyle;
	pLineStyle.lColor = RGB(0, 0, 0);
	pLineStyle.lWidth = 0.6f;
	pLineStyle.eStyle = OT_SOLID;
	DISPLAY_HANDLE pnewPen = pDC->CreatePen(pLineStyle);

	DISPLAY_HANDLE pold = pDC->SelectObject(pnewPen);

	pDC->DrawCircle(*pCirlce);

	delete pCirlce;
	pCirlce = NULL;

	pDC->SelectObject(pold);
	pDC->RemoveHandle(pnewPen);

	pMapCtrl->RefreshScreen();
}

/*--------------------------将圆形打断----------------------------*/
void CActionEditDrawCircle::SplitCircle(TT_GEOMETRY::geom::Geometry *pGeometry)
{
	CttShape cShape;
	cShape.Create();
	
	STPoint centralPt;		//圆心
	STPoint endPt;			//圆周点
	
	//获取活动地图控件
	otFramework::IMapCtrl *pMapCtrl = otFramework::IMapCtrl::GetActiveMapCtrl();
	if(!pMapCtrl)
		return;

	//获取活动地区
	otCarto::CGeoMapPtr pMap = pMapCtrl->GetActiveMap();
	if(!pMap)
		return;

	//转化圆心为地理坐标
	pMap->GetDisplay()->GetDisplayTransformation().ConvertDisplayToGeo(m_centralPt.x, m_centralPt.y, centralPt.x, centralPt.y);
	pMap->GetDisplay()->GetDisplayTransformation().ConvertDisplayToGeo(m_endPt.x, m_endPt.y, endPt.x, endPt.y);
	
	double dRadius;			//半径
	dRadius = ::sqrt((double)((centralPt.x - endPt.x) * (centralPt.x - endPt.x)) 
		+ (double)((centralPt.y - endPt.y) * (centralPt.y - endPt.y))); 

	cShape.MakeCircle(centralPt, dRadius, 720, NULL, NULL);

	//将点塞入Geometry
	PSTPoint pstPoint = NULL;
	cShape.GetAllPointsPtr(NULL,&pstPoint,NULL,NULL,NULL);
	long lptnum;
	cShape.GetNumPoints(&lptnum);

	Coordinate coord;
	for(long i=0;i<lptnum;i++)
	{
		coord.x =pstPoint[i].x;
		coord.y =pstPoint[i].y;

		pGeometry->AddPoint(coord);
	}

	cShape.Free();
}

}