#include "StdAfx.h"
#include "BezierCurveElement.h"
#include "EnvelopeTracker.h"

namespace Element{

CBezierCurveElement::CBezierCurveElement(void)
{
	m_enumElementType = ET_BEZIERCURVE_ELEMENT;
	m_pSelectionHandle.reset(new CEnvelopeTracker(GEOMETRY::geom::Envelope(0,0,0,0), HT_EIGHT));
}

CBezierCurveElement::CBezierCurveElement(const GEOMETRY::geom::Geometry& geometry):IElement(geometry)
{
	m_enumElementType = ET_BEZIERCURVE_ELEMENT;
	Display::CSimpleLineSymbol* pLineSymbol = new Display::CSimpleLineSymbol;
	pLineSymbol->SetLineColor(RGB(0,0,0));
	m_pSymbol.reset(pLineSymbol);
	m_pSelectionHandle.reset(new CEnvelopeTracker(*geometry.getEnvelopeInternal(), HT_EIGHT));
}

CBezierCurveElement::CBezierCurveElement(GEOMETRY::geom::Coordinate& coord)
{
	m_enumElementType = ET_BEZIERCURVE_ELEMENT;
	Display::CSimpleLineSymbol* pLineSymbol = new Display::CSimpleLineSymbol;
	pLineSymbol->SetLineColor(RGB(0,0,0));
	m_pSymbol.reset(pLineSymbol);

	std::vector<GEOMETRY::geom::Coordinate> coordinates;

	coordinates.push_back(coord);
	coordinates.push_back(coord);

	m_pGeometry = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->createBezierSpline(coordinates);
	
	m_pSelectionHandle.reset(new CEnvelopeTracker(*m_pGeometry->getEnvelopeInternal(), HT_EIGHT));
}

CBezierCurveElement::~CBezierCurveElement(void)
{
	
}

void CBezierCurveElement::serialization(SYSTEM::IArchive &ar)
{
	IElement::serialization(ar);
}

void CBezierCurveElement::DrawNormal(Display::IDisplayPtr pDisplay)
{
	pDisplay->SetSymbol( m_pSymbol.get() );

	pDisplay->Begin();

	pDisplay->Draw( m_pGeometry );

	pDisplay->End();
}

void CBezierCurveElement::AddVertix(GEOMETRY::geom::Coordinate coord)
{
	m_pGeometry->AddPoint(coord);

	GeometryChangedEvents();
}

void CBezierCurveElement::InsertVertix(long lIndex, GEOMETRY::geom::Coordinate coord)
{
	m_pGeometry->InsertPoint(lIndex, coord);
	GeometryChangedEvents();
}

void CBezierCurveElement::RemoveVertix(long lIndex)
{	
	m_pGeometry->RemovePoint(lIndex);
	GeometryChangedEvents();
}

void CBezierCurveElement::MoveVertixTo(long lIndex, GEOMETRY::geom::Coordinate coord)
{
	m_pGeometry->ReplacePoint(lIndex,coord);
	GeometryChangedEvents();
}

}
