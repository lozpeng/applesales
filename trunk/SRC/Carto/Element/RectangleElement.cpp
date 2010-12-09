#include "StdAfx.h"
#include "RectangleElement.h"
#include "EnvelopeTracker.h"

namespace Element{
	
CRectangleElement::CRectangleElement()
{
	m_enumElementType = ET_FILL_RECTANGLE_ELEMENT;
	m_pSelectionHandle.reset(new CEnvelopeTracker(GEOMETRY::geom::Envelope(0,0,0,0), HT_EIGHT));
}

CRectangleElement::CRectangleElement(const GEOMETRY::geom::Geometry& geometry):IFillShapeElement(geometry)
{
	m_enumElementType = ET_FILL_RECTANGLE_ELEMENT;
	m_pSelectionHandle.reset(new CEnvelopeTracker(*geometry.getEnvelopeInternal(), HT_EIGHT));
}
CRectangleElement::CRectangleElement(GEOMETRY::geom::Envelope& envelope)
{
	m_enumElementType = ET_FILL_RECTANGLE_ELEMENT;
	m_pGeometry = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->toGeometry(&envelope);

	m_pSelectionHandle.reset(new CEnvelopeTracker(*m_pGeometry->getEnvelopeInternal(), HT_EIGHT));
}

CRectangleElement::CRectangleElement(double xMin, double yMin, double xMax, double yMax)
{
	m_enumElementType = ET_FILL_RECTANGLE_ELEMENT;
	GEOMETRY::geom::Envelope envelope(xMin,xMax, yMin, yMax );
	m_pGeometry = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->toGeometry(&envelope);
	m_pSelectionHandle.reset(new CEnvelopeTracker(*m_pGeometry->getEnvelopeInternal(), HT_EIGHT));
}

CRectangleElement::~CRectangleElement(void)
{

}

void CRectangleElement::serialization(SYSTEM::IArchive &ar)
{
	IFillShapeElement::serialization(ar);
}
//
//IElementPtr CRectangleElement::Clone()
//{
//	CRectangleElement* pElement = new CRectangleElement();
//	*pElement = *this;
//
//	//element
//	pElement->m_pSymbol = m_pSymbol->Clone();
//	pElement->m_pGeometry = m_pGeometry->clone();
//
//	//fill shape
//	m_pFillDraftSymbol = m_pFillDraftSymbol->Clone();
//	m_pOnDrawSymbol = m_pOnDrawSymbol->Clone();
//	m_pMoveSymbol = m_pMoveSymbol->Clone();
//
//	return CRectangleElementPtr(pElement);
//}

void CRectangleElement::Update(double xStart,double yStart, double xEnd,double yEnd)
{
	GEOMETRY::geom::Geometry* pGeo = dynamic_cast<GEOMETRY::geom::Polygon*>(m_pGeometry)->GetGeometry(0);
	pGeo->ReplacePoint(0,GEOMETRY::geom::Coordinate(xStart,yStart));
	pGeo->ReplacePoint(1,GEOMETRY::geom::Coordinate(xEnd,yStart));
	pGeo->ReplacePoint(2,GEOMETRY::geom::Coordinate(xEnd,yEnd));
	pGeo->ReplacePoint(3,GEOMETRY::geom::Coordinate(xStart,yEnd));
	pGeo->ReplacePoint(4,GEOMETRY::geom::Coordinate(xStart,yStart));

	GeometryChangedEvents();
}


}
