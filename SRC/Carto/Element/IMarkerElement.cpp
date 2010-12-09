#include "StdAfx.h"
#include "IMarkerElement.h"
#include "EnvelopeTracker.h"

namespace Element{

IMarkerElement::IMarkerElement()
{
	m_bGeometryChanged = FALSE;
	m_AnchorPos = EAP_CENTER_CENTER;
}
IMarkerElement::IMarkerElement(const GEOMETRY::geom::Geometry& geometry):IGraphicElement(geometry)
{
	m_bGeometryChanged = FALSE;
	m_AnchorPos = EAP_CENTER_CENTER;
}

IMarkerElement::~IMarkerElement(void)
{
}

void IMarkerElement::serialization(SYSTEM::IArchive &ar)
{
	IElement::serialization(ar);
}

GEOMETRY::geom::Envelope IMarkerElement::GetEnvelope()
{
	//GEOMETRY::geom::Envelope env(*m_pGeometry->getCoordinate());
	/*Display::IMarkerSymbol* pMarkerSymbol = dynamic_cast<Display::IMarkerSymbol*>(m_pSymbol.get());
	double dblSize  = pMarkerSymbol->GetMarkerSize();*/
	//double envSize = dblSize * 25.4 / 72;/* *  / */;
	//env.expandBy(envSize/2);
	return m_pSelectionHandle->GetEnvelope();
}

BOOL IMarkerElement::Select(GEOMETRY::geom::Geometry* pSelectGeometry, long lSpatialRelation, CElementCollection& selectedSubElements,double dbTolerance)
{
	IElementPtr pElement;
	GEOMETRY::geom::Envelope markerEnv = GetEnvelope();
	if(pSelectGeometry->getGeometryTypeId() == GEOMETRY::geom::GEOS_POINT)//点选情况下
	{
		if(markerEnv.contains(*pSelectGeometry->getCoordinate()))
			return TRUE;
		else
			return FALSE;
	}
	else//其他多边形选择情况下
	{
		switch(lSpatialRelation)
		{
			//多边形相交选择
		case Geodatabase::SpatialRelIntersects: 	
			{
				if(pSelectGeometry->getEnvelopeInternal()->intersects(&markerEnv))
					return TRUE;
				else
					return FALSE;
			}
			break;
			//多边形包含选择
		case Geodatabase::SpatialRelContains:
			{
				if(pSelectGeometry->getEnvelopeInternal()->contains(&markerEnv))
					return TRUE;
				else
					return FALSE;
			}
			break;
		default:
			{
				if(pSelectGeometry->getEnvelopeInternal()->contains(&markerEnv))
					return TRUE;
				else
					return FALSE;
			}
			break;
		}
	}

}


void IMarkerElement::MoveHandleTo(HIT_HANDLE nHandle,GEOMETRY::geom::Coordinate coord)
{
	if(!m_pSelectionHandle)
		return;

	GEOMETRY::geom::Envelope oldEnvelope = GetEnvelope();
	GEOMETRY::geom::Coordinate coordStart, coordEnd;

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
			//coordEnd = coord;			
		}
		break;
	case HH_HIT_MAXX_MAXY:
		{
			coordStart = GEOMETRY::geom::Coordinate(oldEnvelope.getMinX(), oldEnvelope.getMinY());
			//coordEnd = coord;	
		}
		break;
	case HH_HIT_MINX_MAXY:
		{
			coordStart = GEOMETRY::geom::Coordinate(oldEnvelope.getMaxX(), oldEnvelope.getMinY());
			//coordEnd = coord;	
		}
		break;
	default:
		break;
	}

	double xDis = coord.x - coordStart.x;
	double yDis = coord.y - coordStart.y;
	double dSize = abs(xDis)<abs(yDis) ? abs(xDis) : abs(yDis);
	coordEnd.x = coordStart.x + dSize * (int)(abs(xDis)/xDis);
	coordEnd.y = coordStart.y + dSize * (int)(abs(yDis)/yDis);	

	GEOMETRY::geom::Envelope newEnvelope(coordStart, coordEnd);
	if(abs(newEnvelope.getWidth())<0.000001 || abs(newEnvelope.getHeight())<0.000001)
		return;

	GEOMETRY::geom::Geometry* pTmpGeo = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->toGeometry(&newEnvelope);
	m_pSelectionHandle->SetGeometry(*pTmpGeo);
	GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(pTmpGeo);

	ChangeGeometryEnvelopTo(newEnvelope);
}

void IMarkerElement::ChangeGeometryEnvelopTo(GEOMETRY::geom::Envelope& newEnvelope)
{
	if(m_pGeometry)
	{
		GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(m_pGeometry);
		m_pGeometry = NULL;
	}

	GEOMETRY::geom::Coordinate coordCenter;
	newEnvelope.centre(coordCenter);
	m_pGeometry = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->createPoint(coordCenter);

	/*GEOMETRY::geom::Envelope oldEnvelope = m_pSelectionHandle->GetEnvelope();
	double ratio = newEnvelope.getWidth()/oldEnvelope.getWidth();
	Display::IMarkerSymbol* pMarkerSymbol = dynamic_cast<Display::IMarkerSymbol*>(m_pSymbol.get());
	double dblSize = ratio * pMarkerSymbol->GetMarkerSize();	
	pMarkerSymbol->SetMarkerSize(dblSize);

	m_pGeometry->FitEnvelope(newEnvelope);*/

	m_bGeometryChanged = TRUE;
}


void IMarkerElement::DrawOnDrawMode(Display::IDisplayPtr pDisplay)
{
	DrawEnvelope(pDisplay);

	//DrawNoEditMode(pDisplay);
}

void IMarkerElement::DrawMoveMode(Display::IDisplayPtr pDisplay)
{
	DrawEnvelope(pDisplay);

	DrawNoEditMode(pDisplay);
}

void IMarkerElement::GeometryChangedEvents()
{
	GEOMETRY::geom::Envelope env = GetEnvelope();
	GEOMETRY::geom::Geometry* pGeo = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->toGeometry(&env);
	if(m_pSelectionHandle)
		m_pSelectionHandle->SetGeometry(*pGeo);

	GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(pGeo);
}

}
