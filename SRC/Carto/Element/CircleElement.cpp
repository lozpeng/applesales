#include "StdAfx.h"
#include "CircleElement.h"
#include "EnvelopeTracker.h"
namespace Element{

CCircleElement::CCircleElement()
{
	m_enumElementType = ET_FILL_CIRCLE_ELEMENT;
	m_pSelectionHandle.reset(new CEnvelopeTracker(GEOMETRY::geom::Envelope(0,0,0,0), HT_FOUR));
	m_bCanSetWHRMode = FALSE;
}
CCircleElement::CCircleElement(const GEOMETRY::geom::Geometry& geometry):IFillShapeElement(geometry)
{
	m_enumElementType = ET_FILL_CIRCLE_ELEMENT;
	m_pSelectionHandle.reset(new CEnvelopeTracker(*geometry.getEnvelopeInternal(), HT_FOUR));
	m_bCanSetWHRMode = FALSE;
}
CCircleElement::CCircleElement(GEOMETRY::geom::Coordinate& center, double radius)
{
	m_enumElementType = ET_FILL_CIRCLE_ELEMENT;
	m_pGeometry =(GEOMETRY::geom::Geometry*) GEOMETRY::geom::GeometryFactory::getDefaultInstance()->createCircle(center,radius);

	m_pSelectionHandle.reset(new CEnvelopeTracker(*m_pGeometry->getEnvelopeInternal(), HT_FOUR));
	m_bCanSetWHRMode = FALSE;
}

CCircleElement::~CCircleElement(void)
{
}

void CCircleElement::serialization(SYSTEM::IArchive &ar)
{
	IFillShapeElement::serialization(ar);
}

void CCircleElement::Update(GEOMETRY::geom::Coordinate center, double radius)
{
	GEOMETRY::geom::Circle* pGeo = dynamic_cast<GEOMETRY::geom::Circle*>(m_pGeometry);
	pGeo->SetCenterPoint(center);
	pGeo->SetRadius(radius);
	GeometryChangedEvents();
}

}
