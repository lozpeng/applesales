#include "StdAfx.h"
#include "SelectionHandle.h"
#include "SimpleLineSymbol.h"

namespace Element{

CSelectionHandle::CSelectionHandle(const GEOMETRY::geom::Envelope& envlope,HANDLE_TYPE handleType)
{
	m_handleType = handleType;

	m_pHandlePoints = NULL;

	m_pGeometry = NULL;

	SetEnvelope(envlope);

	m_color = RGB(0,255,255);
}

CSelectionHandle::~CSelectionHandle(void)
{
	if(m_pHandlePoints)
	{
		GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(m_pHandlePoints);
		m_pHandlePoints = NULL;
	}
	
}

CSelectionHandlePtr CSelectionHandle::Clone()
{
	CSelectionHandle* pHandle = new CSelectionHandle(m_envelope, m_handleType);
	*pHandle = *this;
	pHandle->m_pFillSymbol = m_pFillSymbol->Clone();
	
	return CSelectionHandlePtr(pHandle);
}
void CSelectionHandle::DrawBorderLine(const Display::IDisplayPtr pDisplay)
{
	INT_POINT pt;
	long lNumPoints;
	GEOMETRY::geom::Coordinate coord;
	CoordinateSequence* coordSeq = NULL;
	
	coordSeq =m_pGeometry->getCoordinates();
	lNumPoints =coordSeq->getSize();

	//构造一个线对象 
	DIS_LINE *pline;
	CreateDisplayLine(pline,lNumPoints);

	for( int i = 0;i < lNumPoints;i++ )
	{
		coord = coordSeq->getAt(i);

		pDisplay->GetDisplayTransformation().ConvertGeoToDisplay(coord.x,coord.y,pt.x,pt.y);
		pline->ps[i] = pt;	
	}
	delete coordSeq;


	//绘制边框线
	Display::CDC *pDC =pDisplay->GetDrawDC();

	LINE_STYLE bs;
	bs.lColor = m_color;
	bs.eStyle = DOT;
	bs.lWidth = 1;
	bs.bExt = FALSE;
	DISPLAY_HANDLE pBorderBrush =pDC->CreatePen(bs);
	DISPLAY_HANDLE pOld =pDC->SelectObject(pBorderBrush);

	pDC->DrawPolyLines(*pline);

	FreeDisplayObj(pline);

	pDC->SelectObject(pOld);
	pDC->RemoveHandle(pBorderBrush);

}

void CSelectionHandle::DrawHandlePoint(const Display::IDisplayPtr pDisplay)
{
	INT_POINT pt;
	GEOMETRY::geom::Coordinate coord;
	long lNumPoints =m_pHandlePoints->getNumGeometries();

	INT_POINT*	pts = new INT_POINT[lNumPoints];
	for(int i=0; i<lNumPoints; i++)
	{
		coord = *m_pHandlePoints->getGeometryN(i)->getCoordinate();
		pDisplay->GetDisplayTransformation().ConvertGeoToDisplay(coord.x,coord.y,pt.x,pt.y);
		pts[i] = pt;
	}

	//绘制handle
	Display::CDC *pDC =pDisplay->GetDrawDC();

	BRUSH_STYLE bs;
	bs.lColor = m_color;
	bs.Style = SOLID_BRUSH;
	DISPLAY_HANDLE pHandleBorderBrush =pDC->CreateBrush(bs);
	DISPLAY_HANDLE pOld =pDC->SelectObject(pHandleBorderBrush);

	int nSize =4;
	DIS_RECT rect;
	for( int i = 0;i < lNumPoints;i++ )
	{
		//构造一个线对象 

		rect.left = pts[i].x - nSize;
		rect.right = pts[i].x + nSize;
		rect.top = pts[i].y - nSize;
		rect.bottom = pts[i].y + nSize;
		pDC->DrawAndFillRect(rect);
	}

	pDC->SelectObject(pOld);
	pDC->RemoveHandle(pHandleBorderBrush);
	delete []pts;
}

void CSelectionHandle::Draw(const Display::IDisplayPtr pDisplay)
{
	// 绘制边框

	DrawBorderLine(pDisplay);

	//绘制handle
	if(m_handleType != HT_NONE)
		DrawHandlePoint(pDisplay);
}

void CSelectionHandle::SetOutlineColor(COLORREF color)
{
	m_pFillSymbol->SetOutLineColor(color);
}

void CSelectionHandle::SetEnvelope(const GEOMETRY::geom::Envelope& envlope)
{
	m_envelope = envlope;
	if(m_envelope.getHeight()==0 || m_envelope.getWidth()==0)
	{
		m_envelope.expandBy(1);
	}

	if(!m_pGeometry)
	{
		//初始化边框
		m_pGeometry = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->toGeometry(&m_envelope);

		//初始化handles
		if(m_handleType == HT_NONE)
		{
			return;
		}
		else if(m_handleType == HT_FOUR)
		{
			GEOMETRY::geom::Coordinate center;
			GEOMETRY::geom::CoordinateSequence* pCoords = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->getCoordinateSequenceFactory()->create(NULL);
			m_envelope.centre(center);

			pCoords->add(GEOMETRY::geom::Coordinate(m_envelope.getMinX(), m_envelope.getMinY()));
			pCoords->add(GEOMETRY::geom::Coordinate(m_envelope.getMaxX(), m_envelope.getMinY()));
			pCoords->add(GEOMETRY::geom::Coordinate(m_envelope.getMaxX(), m_envelope.getMaxY()));
			pCoords->add(GEOMETRY::geom::Coordinate(m_envelope.getMinX(), m_envelope.getMaxY()));

			m_pHandlePoints = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->createMultiPoint(*pCoords);	
			delete pCoords;
		}	
		else if(m_handleType == HT_EIGHT)
		{
			GEOMETRY::geom::Coordinate center;
			GEOMETRY::geom::CoordinateSequence* pCoords = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->getCoordinateSequenceFactory()->create(NULL);
			m_envelope.centre(center);
		
			pCoords->add(GEOMETRY::geom::Coordinate(m_envelope.getMinX(), m_envelope.getMinY()));
			pCoords->add(GEOMETRY::geom::Coordinate(center.x, m_envelope.getMinY()));
			pCoords->add(GEOMETRY::geom::Coordinate(m_envelope.getMaxX(), m_envelope.getMinY()));
			pCoords->add(GEOMETRY::geom::Coordinate(m_envelope.getMaxX(), center.y));
			pCoords->add(GEOMETRY::geom::Coordinate(m_envelope.getMaxX(), m_envelope.getMaxY()));
			pCoords->add(GEOMETRY::geom::Coordinate(center.x, m_envelope.getMaxY()));
			pCoords->add(GEOMETRY::geom::Coordinate(m_envelope.getMinX(), m_envelope.getMaxY()));
			pCoords->add(GEOMETRY::geom::Coordinate(m_envelope.getMinX(), center.y));

			m_pHandlePoints = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->createMultiPoint(*pCoords);	
			delete pCoords;
		}
		
	}
	else
	{
		GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(m_pGeometry);

		//更新边框
		m_pGeometry = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->toGeometry(&m_envelope);

		//更新handles
		
		if(m_handleType == HT_NONE)
		{
			return;
		}
		else if(m_handleType == HT_FOUR)
		{
			GEOMETRY::geom::Coordinate center;
			m_envelope.centre(center);
			m_pHandlePoints->ReplacePoint(0,GEOMETRY::geom::Coordinate(m_envelope.getMinX(), m_envelope.getMinY()));
			m_pHandlePoints->ReplacePoint(1,GEOMETRY::geom::Coordinate(m_envelope.getMaxX(), m_envelope.getMinY()));
			m_pHandlePoints->ReplacePoint(2,GEOMETRY::geom::Coordinate(m_envelope.getMaxX(), m_envelope.getMaxY()));
			m_pHandlePoints->ReplacePoint(3,GEOMETRY::geom::Coordinate(m_envelope.getMinX(), m_envelope.getMaxY()));
		}
		else if(m_handleType == HT_EIGHT)
		{
			GEOMETRY::geom::Coordinate center;
			m_envelope.centre(center);
			m_pHandlePoints->ReplacePoint(0,GEOMETRY::geom::Coordinate(m_envelope.getMinX(), m_envelope.getMinY()));
			m_pHandlePoints->ReplacePoint(1,GEOMETRY::geom::Coordinate(center.x, m_envelope.getMinY()));
			m_pHandlePoints->ReplacePoint(2,GEOMETRY::geom::Coordinate(m_envelope.getMaxX(), m_envelope.getMinY()));
			m_pHandlePoints->ReplacePoint(3,GEOMETRY::geom::Coordinate(m_envelope.getMaxX(), center.y));
			m_pHandlePoints->ReplacePoint(4,GEOMETRY::geom::Coordinate(m_envelope.getMaxX(), m_envelope.getMaxY()));
			m_pHandlePoints->ReplacePoint(5,GEOMETRY::geom::Coordinate(center.x, m_envelope.getMaxY()));
			m_pHandlePoints->ReplacePoint(6,GEOMETRY::geom::Coordinate(m_envelope.getMinX(), m_envelope.getMaxY()));
			m_pHandlePoints->ReplacePoint(7,GEOMETRY::geom::Coordinate(m_envelope.getMinX(), center.y));
		}
	
	}
}

HIT_HANDLE CSelectionHandle::HitTest ( GEOMETRY::geom::Coordinate coord, double dbTolerance)
{
	double dbSearchDis = 0;
	HIT_HANDLE nHandle = HH_HIT_NONE;
	if(m_handleType == HT_NONE)
	{
		GEOMETRY::geom::Geometry *pPt = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->createPoint(coord);
		GEOMETRY::geom::Geometry* pBufferGeo = m_pGeometry->buffer(dbTolerance);
		if(pBufferGeo->covers(pPt))
			nHandle = HH_HIT_INTERIOR;

		GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(pBufferGeo);
		GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(pPt);
	}
	else
	{		
		long lPartIndex=-1, lVertixIndex=-1;
		GEOMETRY::geom::Coordinate coordOut;
		m_pHandlePoints->SnapVertex(&coord, dbTolerance, &coordOut, &dbSearchDis, &lPartIndex, &lVertixIndex);
		
		if(lPartIndex == -1)
		{
			GEOMETRY::geom::Geometry *pPt = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->createPoint(coord);
			GEOMETRY::geom::Geometry* pBufferGeo = m_pGeometry->buffer(dbTolerance);
			if(pBufferGeo->covers(pPt))
				nHandle = HH_HIT_INTERIOR;

			GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(pBufferGeo);
			GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(pPt);
		}
		else
		{
			if(m_handleType == HT_FOUR)
			{
				nHandle = (HIT_HANDLE)(lPartIndex*2+HH_HIT_MINX_MINY);
				
			}
			else if(m_handleType == HT_EIGHT)
			{
				nHandle = (HIT_HANDLE)(lPartIndex+HH_HIT_MINX_MINY);
			}
		}
	}
	return nHandle;
}

void CSelectionHandle::MoveHandleTo(HIT_HANDLE nHandle,GEOMETRY::geom::Coordinate coord)
{
	if(m_handleType == HT_NONE)
		return;

	GEOMETRY::geom::Envelope oldEnvelope = GetEnvelope();
	GEOMETRY::geom::Coordinate coordStart, coordEnd;

	if(m_handleType == HT_FOUR)
	{
		switch(nHandle)
		{
		case HH_HIT_MINX_MINY:
			{
				coordStart = GEOMETRY::geom::Coordinate(oldEnvelope.getMaxX(), oldEnvelope.getMaxY());
			}
			break;
		case HH_HIT_MAXX_MINY:
			{
				coordStart = GEOMETRY::geom::Coordinate(oldEnvelope.getMinX(), oldEnvelope.getMaxY());		
			}
			break;
		case HH_HIT_MAXX_MAXY:
			{
				coordStart = GEOMETRY::geom::Coordinate(oldEnvelope.getMinX(), oldEnvelope.getMinY());	
			}
			break;
		case HH_HIT_MINX_MAXY:
			{
				coordStart = GEOMETRY::geom::Coordinate(oldEnvelope.getMaxX(), oldEnvelope.getMinY());
			}
			break;
		default:
			break;
		}

		double xDis = coord.x - coordStart.x;
		double yDis = coord.y - coordStart.y;
		double xRatio = xDis/oldEnvelope.getWidth();
		double yRatio = yDis/oldEnvelope.getHeight(); 
		double ratio = abs(xRatio) < abs(yRatio) ? abs(xRatio) : abs(yRatio);
		coordEnd.x = coordStart.x + oldEnvelope.getWidth() * ratio * (xRatio/abs(xRatio));
		coordEnd.y = coordStart.y + oldEnvelope.getHeight() * ratio* (yRatio/abs(yRatio));	

		GEOMETRY::geom::Envelope newEnvelope(coordStart, coordEnd);
		if(abs(newEnvelope.getWidth())<0.000001 || abs(newEnvelope.getHeight())<0.000001)
			return;

		SetEnvelope(newEnvelope);
	}	
	else if(m_handleType == HT_EIGHT)
	{
		switch(nHandle)
		{
		case HH_HIT_MINX_MINY:
			{
				coordStart = coord;
				coordEnd = GEOMETRY::geom::Coordinate(oldEnvelope.getMaxX(), oldEnvelope.getMaxY());	
			}
			break;
		case HH_HIT_MIDX_MINY:
			{
				coordStart = GEOMETRY::geom::Coordinate(oldEnvelope.getMaxX(), coord.y);;
				coordEnd = GEOMETRY::geom::Coordinate(oldEnvelope.getMinX(), oldEnvelope.getMaxY());				
			}
			break;
		case HH_HIT_MAXX_MINY:
			{
				coordStart = coord;
				coordEnd = GEOMETRY::geom::Coordinate(oldEnvelope.getMinX(), oldEnvelope.getMaxY());			
			}
			break;
		case HH_HIT_MAXX_MIDY:
			{
				coordStart = GEOMETRY::geom::Coordinate(coord.x, oldEnvelope.getMaxY());
				coordEnd = GEOMETRY::geom::Coordinate(oldEnvelope.getMinX(), oldEnvelope.getMinY());		
			}
			break;
		case HH_HIT_MAXX_MAXY:
			{
				coordStart = coord;
				coordEnd = GEOMETRY::geom::Coordinate(oldEnvelope.getMinX(), oldEnvelope.getMinY());	
			}
			break;
		case HH_HIT_MIDX_MAXY:
			{
				coordStart = GEOMETRY::geom::Coordinate(oldEnvelope.getMaxX(), coord.y);
				coordEnd = GEOMETRY::geom::Coordinate(oldEnvelope.getMinX(), oldEnvelope.getMinY());			
			}
			break;
		case HH_HIT_MINX_MAXY:
			{
				coordStart = coord;
				coordEnd = GEOMETRY::geom::Coordinate(oldEnvelope.getMaxX(), oldEnvelope.getMinY());	
			}
			break;
		case HH_HIT_MINX_MIDY:
			{
				coordStart = GEOMETRY::geom::Coordinate(coord.x, oldEnvelope.getMaxY());
				coordEnd = GEOMETRY::geom::Coordinate(oldEnvelope.getMaxX(), oldEnvelope.getMinY());	
			}
			break;
		default:
			break;
		}

		GEOMETRY::geom::Envelope newEnvelope(coordStart, coordEnd);
		SetEnvelope(newEnvelope);
	}

	
	
}

}
