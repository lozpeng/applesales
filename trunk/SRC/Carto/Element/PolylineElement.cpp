#include "StdAfx.h"
#include "PolylineElement.h"
#include "EnvelopeTracker.h"

namespace Element{

CPolylineElement::CPolylineElement(void)
{
	m_enumElementType = ET_POLYLINE_ELEMENT;
	m_pSelectionHandle.reset(new CEnvelopeTracker(GEOMETRY::geom::Envelope(0,0,0,0), HT_EIGHT));
}

CPolylineElement::CPolylineElement(const GEOMETRY::geom::Geometry& geometry):IElement(geometry)
{
	m_enumElementType = ET_POLYLINE_ELEMENT;

	m_pSymbol.reset(new Display::CSimpleLineSymbol);
	m_pSymbol->SetColor(RGB(0,0,0));

	m_pSelectionHandle.reset(new CEnvelopeTracker(*geometry.getEnvelopeInternal(), HT_EIGHT));
}

CPolylineElement::CPolylineElement(GEOMETRY::geom::Coordinate& coord)
{
	m_enumElementType = ET_POLYLINE_ELEMENT;

	m_pSymbol.reset(new Display::CSimpleLineSymbol);
	m_pSymbol->SetColor(RGB(0,0,0));


	GEOMETRY::geom::CoordinateSequence* pCoords = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->getCoordinateSequenceFactory()->create(NULL);
	for(int i=0; i<2; i++)
		pCoords->add(coord);
	m_pGeometry = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->createLineString(pCoords);
	
	m_pSelectionHandle.reset(new CEnvelopeTracker(*m_pGeometry->getEnvelopeInternal(), HT_EIGHT));
}

CPolylineElement::~CPolylineElement(void)
{
	
}

void CPolylineElement::serialization(SYSTEM::IArchive &ar)
{
	IElement::serialization(ar);
}

void CPolylineElement::DrawNormal(Display::IDisplayPtr pDisplay)
{
	pDisplay->SetSymbol( m_pSymbol.get() );

	pDisplay->Begin();

	pDisplay->Draw( m_pGeometry );

	pDisplay->End();
}

void CPolylineElement::AddVertix(GEOMETRY::geom::Coordinate coord)
{
	//GEOMETRY::geom::Geometry* pGeo = dynamic_cast<GEOMETRY::geom::LineString*>(m_pGeometry)->GetGeometry(0);
	m_pGeometry->AddPoint(coord);

	GeometryChangedEvents();
}

void CPolylineElement::InsertVertix(long lIndex, GEOMETRY::geom::Coordinate coord)
{
	m_pGeometry->InsertPoint(lIndex, coord);
	GeometryChangedEvents();
}

void CPolylineElement::RemoveVertix(long lIndex)
{	
	//GEOMETRY::geom::Geometry* pGeo = dynamic_cast<GEOMETRY::geom::LineString*>(m_pGeometry)->GetGeometry(0);
	m_pGeometry->RemovePoint(lIndex);
	GeometryChangedEvents();
}

void CPolylineElement::MoveVertixTo(long lIndex, GEOMETRY::geom::Coordinate coord)
{
	//GEOMETRY::geom::Geometry* pGeo = dynamic_cast<GEOMETRY::geom::LineString*>(m_pGeometry)->GetGeometry(0);
	m_pGeometry->ReplacePoint(lIndex,coord);
	GeometryChangedEvents();
}


}
