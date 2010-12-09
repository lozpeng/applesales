#include "StdAfx.h"
#include "EditVertixHandle.h"
#include "SimpleLineSymbol.h"

namespace Element{
CEditVertixHandle::CEditVertixHandle():ISelectionTracker()
{
	m_pGeometry = NULL;

	//初始化边框线符号
	Display::CSimpleLineSymbol* pLineSymbol = dynamic_cast<Display::CSimpleLineSymbol*>(m_pFillSymbol->GetOutLineSymbol().get());
	pLineSymbol->SetLineStyle(DOT);
	m_pFillSymbol->SetOutLineColor(RGB(0,255,255));
	m_pFillSymbol->SetDrawFill(FALSE);

	//初始化handle点符号
	m_pMarkerSymbol.reset(new Display::CSimpleMarkerSymbol);
	m_pMarkerSymbol->SetOutLineColor(RGB(0,0,0));
	m_pMarkerSymbol->SetMarkerColor(RGB(0,255,255));
	m_pMarkerSymbol->SetMarkerType(SIMPLE_MARKER_SQUARE);
	m_pMarkerSymbol->SetMarkerSize(1.5);
}

CEditVertixHandle::~CEditVertixHandle(void)
{
}

void CEditVertixHandle::Draw(const Display::IDisplayPtr pDisplay, const GEOMETRY::geom::Geometry* pGeometry)
{
	//更新形状
	UpdateGeometry(pGeometry);

	// 绘制边框
	pDisplay->SetSymbol( m_pFillSymbol.get() );

	pDisplay->Begin();

	if(m_pGeometry->getGeometryTypeId() == GEOMETRY::geom::GEOS_POLYGON && m_pGeometry)
		pDisplay->Draw( m_pGeometry );

	pDisplay->End();

	
	//绘制handle
	pDisplay->SetSymbol( m_pMarkerSymbol.get() );

	pDisplay->Begin();

	pDisplay->Draw(m_pHandlePoints);

	pDisplay->End();

	
}

void CEditVertixHandle::SetOutlineColor(COLORREF color)
{
	m_pFillSymbol->SetOutLineColor(color);
}

void CEditVertixHandle::UpdateGeometry(const GEOMETRY::geom::Geometry* pGeometry)
{
	//if(!m_pGeometry)
	//{
	//	//初始化边框
	//	m_pGeometry = pGeometry;

	//	//初始化handles

	//	GEOMETRY::geom::Coordinate center;
	//	GEOMETRY::geom::CoordinateSequence* pCoords = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->getCoordinateSequenceFactory()->create(NULL);
	//	envlope->centre(center);
	//	if(m_bEightHandles)
	//	{
	//		pCoords->add(GEOMETRY::geom::Coordinate(envlope->getMinX(), envlope->getMinY()));
	//		pCoords->add(GEOMETRY::geom::Coordinate(center.x, envlope->getMinY()));
	//		pCoords->add(GEOMETRY::geom::Coordinate(envlope->getMaxX(), envlope->getMinY()));
	//		pCoords->add(GEOMETRY::geom::Coordinate(envlope->getMaxX(), center.y));
	//		pCoords->add(GEOMETRY::geom::Coordinate(envlope->getMaxX(), envlope->getMaxY()));
	//		pCoords->add(GEOMETRY::geom::Coordinate(center.x, envlope->getMaxY()));
	//		pCoords->add(GEOMETRY::geom::Coordinate(envlope->getMinX(), envlope->getMaxY()));
	//		pCoords->add(GEOMETRY::geom::Coordinate(envlope->getMinX(), center.y));
	//	}
	//	else
	//	{
	//		pCoords->add(GEOMETRY::geom::Coordinate(envlope->getMinX(), envlope->getMinY()));
	//		pCoords->add(GEOMETRY::geom::Coordinate(envlope->getMaxX(), envlope->getMinY()));
	//		pCoords->add(GEOMETRY::geom::Coordinate(envlope->getMaxX(), envlope->getMaxY()));
	//		pCoords->add(GEOMETRY::geom::Coordinate(envlope->getMinX(), envlope->getMaxY()));
	//	}
	//	m_pHandlePoints = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->createMultiPoint(*pCoords);	
	//}
	//else
	//{
	//	GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(m_pGeometry);

	//	//更新边框
	//	m_pGeometry = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->toGeometry(envlope);

	//	//更新handles
	//	GEOMETRY::geom::Coordinate center;
	//	envlope->centre(center);
	//	if(m_bEightHandles)
	//	{
	//		m_pHandlePoints->ReplacePoint(0,GEOMETRY::geom::Coordinate(envlope->getMinX(), envlope->getMinY()));
	//		m_pHandlePoints->ReplacePoint(1,GEOMETRY::geom::Coordinate(center.x, envlope->getMinY()));
	//		m_pHandlePoints->ReplacePoint(2,GEOMETRY::geom::Coordinate(envlope->getMaxX(), envlope->getMinY()));
	//		m_pHandlePoints->ReplacePoint(3,GEOMETRY::geom::Coordinate(envlope->getMaxX(), center.y));
	//		m_pHandlePoints->ReplacePoint(4,GEOMETRY::geom::Coordinate(envlope->getMaxX(), envlope->getMaxY()));
	//		m_pHandlePoints->ReplacePoint(5,GEOMETRY::geom::Coordinate(center.x, envlope->getMaxY()));
	//		m_pHandlePoints->ReplacePoint(6,GEOMETRY::geom::Coordinate(envlope->getMinX(), envlope->getMaxY()));
	//		m_pHandlePoints->ReplacePoint(7,GEOMETRY::geom::Coordinate(envlope->getMinX(), center.y));
	//	}
	//	else
	//	{
	//		m_pHandlePoints->ReplacePoint(0,GEOMETRY::geom::Coordinate(envlope->getMinX(), envlope->getMinY()));
	//		m_pHandlePoints->ReplacePoint(1,GEOMETRY::geom::Coordinate(envlope->getMaxX(), envlope->getMinY()));
	//		m_pHandlePoints->ReplacePoint(2,GEOMETRY::geom::Coordinate(envlope->getMaxX(), envlope->getMaxY()));
	//		m_pHandlePoints->ReplacePoint(3,GEOMETRY::geom::Coordinate(envlope->getMinX(), envlope->getMaxY()));
	//	}
	//}
}

HIT_HANDLE CEditVertixHandle::HitTest ( GEOMETRY::geom::Coordinate coord, double dbTolerance)
{
	/*GEOMETRY::geom::Geometry *pHit = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->createPoint(coord);
	HIT_HANDLE nHandle = HH_HIT_NONE;
	
	if(m_bEightHandles)
	{
		for(int i=HH_HIT_MINX_MINY; i<=HH_HIT_MINX_MIDY; i++)
		{
			int nGeo = i - HH_HIT_MINX_MINY;
			const GEOMETRY::geom::Geometry* pHandle = m_pHandlePoints->getGeometryN(nGeo);
			GEOMETRY::geom::Geometry *pEnv = GetHandleEnv(pHandle, dbTolerance);
			if(pEnv->covers(pHit))
			{
				nHandle = (HIT_HANDLE)i;
				break;
			}
			GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(pEnv);
		}

	}
	else
	{
		for(int i=HH_HIT_MINX_MINY; i<=HH_HIT_MINX_MAXY; i+=2)
		{
			int nGeo = (i - HH_HIT_MINX_MINY)/2;
			const GEOMETRY::geom::Geometry* pHandle = m_pHandlePoints->getGeometryN(nGeo);
			GEOMETRY::geom::Geometry *pEnv = GetHandleEnv(pHandle, dbTolerance);
			if(pEnv->covers(pHit))
			{
				nHandle = (HIT_HANDLE)i;
				break;
			}
			GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(pEnv);
		}
	}

	if(nHandle == HH_HIT_NONE)
	{
		GEOMETRY::geom::Geometry* pBufferGeo = m_pGeometry->buffer(dbTolerance);
		if(pBufferGeo->covers(pHit))
			nHandle = HH_HIT_INTERIOR;

		GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(pBufferGeo);
	}
	
	GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(pHit);*/

	HIT_HANDLE nHandle = HH_HIT_NONE;
	return nHandle;
}

GEOMETRY::geom::Geometry* CEditVertixHandle::GetHandleEnv(const GEOMETRY::geom::Geometry* pHandle, double dbTolerance)
{
	const GEOMETRY::geom::Coordinate* coord = pHandle->getCoordinate();

	GEOMETRY::geom::Envelope handleEnv(coord->x-dbTolerance, coord->x+dbTolerance, coord->y-dbTolerance, coord->y+dbTolerance);

	return GEOMETRY::geom::GeometryFactory::getDefaultInstance()->toGeometry(&handleEnv);
}

}
