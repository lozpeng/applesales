#include "StdAfx.h"
#include "EllipseElement.h"
#include "EnvelopeTracker.h"

namespace Element{

CEllipseElement::CEllipseElement()
{
	m_enumElementType = ET_FILL_ELLIPSE_ELEMENT;
	m_pSelectionHandle.reset(new CEnvelopeTracker(GEOMETRY::geom::Envelope(0,0,0,0), HT_EIGHT));
}
CEllipseElement::CEllipseElement(const GEOMETRY::geom::Geometry& geometry):IFillShapeElement(geometry)
{
	m_enumElementType = ET_FILL_ELLIPSE_ELEMENT;
	m_pSelectionHandle.reset(new CEnvelopeTracker(*geometry.getEnvelopeInternal(), HT_EIGHT));
}

CEllipseElement::CEllipseElement(GEOMETRY::geom::Envelope env)
{
	m_enumElementType = ET_FILL_ELLIPSE_ELEMENT;
	m_pGeometry =GEOMETRY::geom::GeometryFactory::getDefaultInstance()->createEllipse(env);

	m_pSelectionHandle.reset(new CEnvelopeTracker(*m_pGeometry->getEnvelopeInternal(), HT_EIGHT));
}

CEllipseElement::~CEllipseElement(void)
{
}

void CEllipseElement::serialization(SYSTEM::IArchive &ar)
{
	IFillShapeElement::serialization(ar);
}

//IElementPtr CEllipseElement::Clone()
//{
//	CEllipseElement* pElement = new CEllipseElement(*m_pGeometry);
//	*pElement = *this;
//
//	//element
//	pElement->m_pSymbol = m_pSymbol->Clone();
//
//	//fill shape
//	m_pFillDraftSymbol = m_pFillDraftSymbol->Clone();
//	m_pOnDrawSymbol = m_pOnDrawSymbol->Clone();
//	m_pMoveSymbol = m_pMoveSymbol->Clone();
//
//	return CEllipseElementPtr(pElement);
//}

void CEllipseElement::Update(GEOMETRY::geom::Envelope& env)
{
	GEOMETRY::geom::Ellipse* pGeo = dynamic_cast<GEOMETRY::geom::Ellipse*>(m_pGeometry);
	GEOMETRY::geom::Coordinate center;
	env.centre(center);
	pGeo->SetCenterPoint(center);
	pGeo->SetAxes(env.getWidth()/2, env.getHeight()/2);
	GeometryChangedEvents();
}

}
