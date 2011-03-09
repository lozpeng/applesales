#include "stdafx.h"
#include "PolygonAdjacentTool.h"
#include "TT_LinePlgOPInterface.h"
#include "TT_PlgOPInterface.h"
#include "TT_LineOP.h"
#include "SnapAgent.h"
#include "IWorkspace.h"
#include "Editor.h"
#include "ILayer.h"
#include "SimpleFillSymbol.h"
#include <Geometry/geom/Coordinate.h>
using namespace GEOMETRY::geom;

namespace Editor
{
	static CActionPolygonAdjacent gActionPolygonAdjacent;

	CActionPolygonAdjacent::CActionPolygonAdjacent() : ITool("ActionPolygonAdjacent")
	{
		RegisterAction("ActionPolygonAdjacent", this);
	}


	CActionPolygonAdjacent::~CActionPolygonAdjacent(void)
	{
	}

	void CActionPolygonAdjacent::Clear()
	{
		for(size_t i=0; i < m_shapes.size(); i++)
		{
			delete m_shapes[i];
			m_shapes[i] = NULL;
		}

		m_shapes.clear();
		m_shapeIds.clear();
		m_players.clear();
	}


	void CActionPolygonAdjacent::Triger(void)
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
		Editor::CEditorPtr pEdit =pMap->GetEditor();
		if(!pEdit)
		{
			return;
		}

		//设置光标类型
		pMapCtrl->SetCursorType(cursorNormal);

		m_bIsDrawing = false;

		//获得当前图层选择集
		//获得当前编辑层的选择集
		Clear();

		pEdit->GetCurLayerSelection(m_shapes,m_shapeIds,m_players);
		//如果选择的不是一个图形，则返回
		if(m_shapes.size()!=1)
		{
			Clear();
			return;
		}

		m_Points.clear();
	}

	void CActionPolygonAdjacent::LButtonDownEvent (UINT nFlags, CPoint point)
	{
		if (m_shapes.size() != 1)
		{
			return;
		}

		m_bIsDrawing = true;

		m_Points.push_back(point);
		
		ActionDraw();
	}

	void CActionPolygonAdjacent::MouseMoveEvent (UINT nFlags, CPoint point)
	{
		if (m_bIsDrawing)
		{
			if (m_shapes.size() != 1)
			{
				return;
			}

			m_Points.push_back(point);

			ActionDraw();

			m_Points.erase(m_Points.end() - 1);
		}
		
	}

	void CActionPolygonAdjacent::LButtonDblClkEvent (UINT nFlags, CPoint point)
	{
		if (m_shapes.size() != 1)
		{
			return;
		}

		m_bIsDrawing = false;
		
		//生成邻接多边形
		AdjacentPolygon();

		m_Points.clear();
	}

	void CActionPolygonAdjacent::ActionDraw()
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

		//构造多边形
		size_t ptCount = m_Points.size();
		if (ptCount < 2)
		{
			return;
		}

		DIS_POLYGON *pPolygon = NULL;
		if (ptCount == 2)
		{
			CreateDisplayPolygon(pPolygon, 1, ptCount + 1);
			pPolygon->RingCount[0] = ptCount + 1;
			INT_POINT *pPoints = pPolygon->GetPointAdr();
			for (int i = 0; i < ptCount; i++)
			{
				pPoints[i].x = m_Points[i].x;
				pPoints[i].y = m_Points[i].y;
			}
			pPoints[ptCount].x = m_Points[0].x;
			pPoints[ptCount].y = m_Points[0].y;
		}
		else
		{
			CreateDisplayPolygon(pPolygon, 1, ptCount);
			pPolygon->RingCount[0] = ptCount;
			INT_POINT *pPoints = pPolygon->GetPointAdr();
			for (int i = 0; i < ptCount; i++)
			{
				pPoints[i].x = m_Points[i].x;
				pPoints[i].y = m_Points[i].y;
			}
		}

		//绘制多边形外边线
		DIS_LINE *pDIS_LINE;
		INT_POINT *pts = pPolygon->GetPointAdr();
		for(unsigned int i = 0 ; i < pPolygon->Count ; i++ )
		{
			CreateDisplayLine( pDIS_LINE , pPolygon->RingCount[i] );
			memcpy( pDIS_LINE->ps , pts , sizeof(INT_POINT)*pDIS_LINE->Count );
			
			LINE_STYLE pLineStyle;
			pLineStyle.lColor = RGB(0, 0, 0);
			pLineStyle.lWidth = 0.6f;
			pLineStyle.eStyle = SOLID;

			Display::CDC *pDC = dispaly->GetDrawDC();
			DISPLAY_HANDLE pnewPen = pDC->CreatePen(pLineStyle);
			DISPLAY_HANDLE pold = pDC->SelectObject(pnewPen);
			
			pDC->DrawPolyLines(*pDIS_LINE);

			pDC->SelectObject(pold);
			pDC->RemoveHandle(pnewPen);

			FreeDisplayObj( pDIS_LINE );
		}
		
		pMapCtrl->RefreshScreen();
	}

	void CActionPolygonAdjacent::AdjacentPolygon()
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
		Editor::CEditorPtr pEdit =pMap->GetEditor();
		if(!pEdit)
		{
			return;
		}

		//获得编辑图层的工作空间
		Carto::ILayer *pLayer = pEdit->GetCurLayer();
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

		//把第一个点加入到最后
		m_Points.push_back(m_Points[0]);

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

				for (int i = 0; i < m_Points.size(); i++)
				{
					Coordinate pt;
					pMap->GetDisplay()->GetDisplayTransformation().ConvertDisplayToGeo(m_Points[i].x, m_Points[i].y, pt);
					pGeometry->AddPoint(pt);
				}
			}
			break;

		case GEOMETRY::geom::GEOS_MULTILINESTRING:
			{
				pGeometry = (Geometry*)GeometryFactory::getDefaultInstance()->createMultiLineString();
				pGeometry->SetbZ(bz);
				pGeometry->SetbM(bm);

				Geometry *pg =NULL;
				pg =(Geometry*) GeometryFactory::getDefaultInstance()->createLineString();
				for (int i = 0; i < m_Points.size(); i++)
				{
					Coordinate pt;
					pMap->GetDisplay()->GetDisplayTransformation().ConvertDisplayToGeo(m_Points[i].x, m_Points[i].y, pt);
					pg->AddPoint(pt);
				}

				((GEOMETRY::geom::MultiLineString*)pGeometry)->AddGeometry(pg);
			}

			break;

		case GEOMETRY::geom::GEOS_POLYGON:
			{
	 			pGeometry = (Geometry*)GeometryFactory::getDefaultInstance()->createPolygon();
				pGeometry->SetbZ(bz);
				pGeometry->SetbM(bm);

				Geometry *pg =NULL;
				pg =(Geometry*) GeometryFactory::getDefaultInstance()->createLinearRing();
				for (int i = 0; i < m_Points.size(); i++)
				{
					Coordinate pt;
					pMap->GetDisplay()->GetDisplayTransformation().ConvertDisplayToGeo(m_Points[i].x, m_Points[i].y, pt);
					pg->AddPoint(pt);
				}

				((GEOMETRY::geom::Polygon*)pGeometry)->AddGeometry(pg);
			}

			break;

		default:
			return;
			break;
		}
		
		//是否相交
		if (!pGeometry->intersects(m_shapes[0]))
		{
			return;
		}

		//通过拓扑操作获得邻接多边形:求其差集

		pGeometry = pGeometry->difference(m_shapes[0]);

		pEdit->AppendGeometry(pGeometry);

		delete pGeometry;
		pGeometry = NULL;

		pMapCtrl->UpdateControl(drawAll);
	}

}


