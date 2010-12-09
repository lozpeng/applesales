#include "StdAfx.h"
#include "PolygonElement.h"
#include "EnvelopeTracker.h"

namespace Element{

CPolygonElement::CPolygonElement()
{
	m_enumElementType = ET_FILL_POLYGON_ELEMENT;
	m_pSelectionHandle.reset(new CEnvelopeTracker(GEOMETRY::geom::Envelope(0,0,0,0), HT_EIGHT));
}

CPolygonElement::CPolygonElement(const GEOMETRY::geom::Geometry& geometry):IFillShapeElement(geometry)
{
	m_enumElementType = ET_FILL_POLYGON_ELEMENT;
	m_pSelectionHandle.reset(new CEnvelopeTracker(*geometry.getEnvelopeInternal(), HT_EIGHT));
}

CPolygonElement::CPolygonElement(GEOMETRY::geom::Coordinate& coord)
{
	m_enumElementType = ET_FILL_POLYGON_ELEMENT;

	GEOMETRY::geom::CoordinateSequence* pCoords = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->getCoordinateSequenceFactory()->create(NULL);
	for(int i=0; i<4; i++)
		pCoords->add(coord);
	

	GEOMETRY::geom::LinearRing* pRing = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->createLinearRing(pCoords);
	m_pGeometry = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->createPolygon(pRing, NULL);

	m_pSelectionHandle.reset(new CEnvelopeTracker(*m_pGeometry->getEnvelopeInternal(), HT_EIGHT));
}

CPolygonElement::~CPolygonElement(void)
{
	
}

void CPolygonElement::serialization(SYSTEM::IArchive &ar)
{
	IFillShapeElement::serialization(ar);
}


void CPolygonElement::AddVertix(GEOMETRY::geom::Coordinate coord)
{
	GEOMETRY::geom::Geometry* pGeo = dynamic_cast<GEOMETRY::geom::Polygon*>(m_pGeometry)->GetGeometry(0);
	long lVerticCount = pGeo->getNumPoints();
	pGeo->InsertPoint(lVerticCount-2, coord);

	GeometryChangedEvents();
}

void CPolygonElement::InsertVertix(long lIndex, GEOMETRY::geom::Coordinate coord)
{
	m_pGeometry->InsertPoint(lIndex, coord);
	GeometryChangedEvents();
}

void CPolygonElement::RemoveVertix(long lIndex)
{	
	GEOMETRY::geom::Geometry* pGeo = dynamic_cast<GEOMETRY::geom::Polygon*>(m_pGeometry)->GetGeometry(0);
	pGeo->RemovePoint(lIndex);
	GeometryChangedEvents();
}

void CPolygonElement::MoveVertixTo(long lIndex, GEOMETRY::geom::Coordinate coord)
{
	GEOMETRY::geom::Geometry* pGeo = dynamic_cast<GEOMETRY::geom::Polygon*>(m_pGeometry)->GetGeometry(0);
	pGeo->ReplacePoint(lIndex,coord);
	GeometryChangedEvents();
}


}
