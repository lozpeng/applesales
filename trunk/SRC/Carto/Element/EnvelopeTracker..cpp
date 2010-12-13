#include "StdAfx.h"
#include "EnvelopeTracker.h"
#include "SimpleLineSymbol.h"

namespace Element{

	CEnvelopeTracker::CEnvelopeTracker(const GEOMETRY::geom::Geometry& geometry,HANDLE_TYPE handleType):ISelectionTracker()
{
	m_handleType = handleType;

	SetGeometry(geometry);

	//³õÊ¼»¯±ß¿ò·ûºÅ
	Display::CSimpleLineSymbol* pLineSymbol = dynamic_cast<Display::CSimpleLineSymbol*>(m_pFillSymbol->GetOutLineSymbol().get());
	pLineSymbol->SetLineStyle(DOT);
	m_pFillSymbol->SetDrawFill(FALSE);
	m_pFillSymbol->SetOutLineColor(RGB(0,255,255));


	m_pMarkerSymbol->SetOutLineColor(RGB(0,0,0));
	m_pMarkerSymbol->SetMarkerColor(RGB(0,255,255));
	m_pMarkerSymbol->SetMarkerType(SIMPLE_MARKER_SQUARE);
	m_pMarkerSymbol->SetMarkerSize(5);
}

CEnvelopeTracker::CEnvelopeTracker(const GEOMETRY::geom::Envelope& envelope,HANDLE_TYPE handleType):ISelectionTracker()
{
	m_handleType = handleType;

	m_pHandlePoints = NULL;

	m_pGeometry = NULL;

	GEOMETRY::geom::Geometry* pTmpGeo = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->toGeometry(&envelope);
	SetGeometry(*pTmpGeo);
	GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(pTmpGeo);

	//³õÊ¼»¯±ß¿ò·ûºÅ
	Display::CSimpleLineSymbol* pLineSymbol = dynamic_cast<Display::CSimpleLineSymbol*>(m_pFillSymbol->GetOutLineSymbol().get());
	pLineSymbol->SetLineStyle(DOT);
	m_pFillSymbol->SetDrawFill(FALSE);
	m_pFillSymbol->SetOutLineColor(RGB(0,255,255));
	m_pFillSymbol->SetFillColor(RGB(0,255,255));

	m_pMarkerSymbol->SetOutLineColor(RGB(0,0,0));
	m_pMarkerSymbol->SetMarkerColor(RGB(0,255,255));
	m_pMarkerSymbol->SetMarkerType(SIMPLE_MARKER_SQUARE);
	m_pMarkerSymbol->SetMarkerSize(5);
}

CEnvelopeTracker::~CEnvelopeTracker(void)
{
	if(m_pHandlePoints)
	{
		GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(m_pHandlePoints);
		m_pHandlePoints = NULL;
	}	
}

void CEnvelopeTracker::SetGeometry(const GEOMETRY::geom::Geometry& geometry)
{
	m_envelope = *geometry.getEnvelopeInternal();

	UpdateEnvelope();

	UpdateHandle();

	UpdateGeometryByEnvelope();
}

void CEnvelopeTracker::UpdateGeometryByEnvelope()
{
	if(m_pGeometry)
	{
		GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(m_pGeometry);
		m_pGeometry = NULL;
	}

	m_pGeometry = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->toGeometry(&m_envelope);
}
void CEnvelopeTracker::UpdateEnvelope()
{
	if(m_envelope.getHeight()==0 || m_envelope.getWidth()==0)
	{
		m_envelope.expandBy(1);
	}

}

void CEnvelopeTracker::UpdateHandle()
{
	//³õÊ¼»¯handles
	if(m_handleType == HT_NONE)
	{
		return;
	}
	else if(m_handleType == HT_FOUR)
	{
		GEOMETRY::geom::Coordinate center;
		GEOMETRY::geom::MultiPoint* pMultiPoint = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->createMultiPoint();
		pMultiPoint->AddPoint(GEOMETRY::geom::Coordinate(m_envelope.getMinX(), m_envelope.getMinY()));
		pMultiPoint->AddPoint(GEOMETRY::geom::Coordinate(m_envelope.getMaxX(), m_envelope.getMinY()));
		pMultiPoint->AddPoint(GEOMETRY::geom::Coordinate(m_envelope.getMaxX(), m_envelope.getMaxY()));
		pMultiPoint->AddPoint(GEOMETRY::geom::Coordinate(m_envelope.getMinX(), m_envelope.getMaxY()));

		if(m_pHandlePoints)
			GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(m_pHandlePoints);

		m_pHandlePoints = (GEOMETRY::geom::Geometry*)pMultiPoint;	

		/*GEOMETRY::geom::CoordinateSequence* pCoords = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->getCoordinateSequenceFactory()->create(NULL);
		m_envelope.centre(center);

		pCoords->add(GEOMETRY::geom::Coordinate(m_envelope.getMinX(), m_envelope.getMinY()));
		pCoords->add(GEOMETRY::geom::Coordinate(m_envelope.getMaxX(), m_envelope.getMinY()));
		pCoords->add(GEOMETRY::geom::Coordinate(m_envelope.getMaxX(), m_envelope.getMaxY()));
		pCoords->add(GEOMETRY::geom::Coordinate(m_envelope.getMinX(), m_envelope.getMaxY()));*/

		/*if(m_pHandlePoints)
			 GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(m_pHandlePoints);

		m_pHandlePoints = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->createMultiPoint(*pCoords);	
		delete pCoords;*/
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

		if(m_pHandlePoints)
			GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(m_pHandlePoints);

		m_pHandlePoints = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->createMultiPoint(*pCoords);	
		delete pCoords;
	}
}


HIT_HANDLE CEnvelopeTracker::HitTest ( GEOMETRY::geom::Coordinate coord, double dbTolerance)
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

void CEnvelopeTracker::MoveHandleTo(HIT_HANDLE nHandle,GEOMETRY::geom::Coordinate coord)
{
	if(m_handleType == HT_NONE)
		return;

	GEOMETRY::geom::Envelope oldEnvelope = m_envelope;
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

		m_envelope = newEnvelope;

		UpdateEnvelope();

		UpdateHandle();

		UpdateGeometryByEnvelope();
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
		m_envelope = newEnvelope;

		UpdateEnvelope();

		UpdateHandle();

		UpdateGeometryByEnvelope();
	}	
}

}
