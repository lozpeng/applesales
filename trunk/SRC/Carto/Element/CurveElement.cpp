#include "StdAfx.h"
#include "CurveElement.h"
#include "EnvelopeTracker.h"

namespace Element{

CCurveElement::CCurveElement()
{
	m_enumElementType = ET_CURVE_ELEMENT;
	m_pSelectionHandle.reset(new CEnvelopeTracker(GEOMETRY::geom::Envelope(0,0,0,0), HT_EIGHT));
}

CCurveElement::CCurveElement(const GEOMETRY::geom::Geometry& geometry):IElement(geometry)
{
	m_enumElementType = ET_CURVE_ELEMENT;
	Display::CSimpleLineSymbol* pLineSymbol = new Display::CSimpleLineSymbol;
	pLineSymbol->SetLineColor(RGB(0,0,0));
	m_pSymbol.reset(pLineSymbol);
	m_pSelectionHandle.reset(new CEnvelopeTracker(*geometry.getEnvelopeInternal(), HT_EIGHT));
}

CCurveElement::~CCurveElement(void)
{
}

void CCurveElement::serialization(SYSTEM::IArchive &ar)
{
	IElement::serialization(ar);
}


//IElementPtr CCurveElement::Clone()
//{
//	CCurveElement* pElement = new CCurveElement(*m_pGeometry);
//	*pElement = *this;
//
//	//element
//	pElement->m_pSymbol = m_pSymbol->Clone();
//	pElement->m_pGeometry = m_pGeometry->clone();
//
//	return CCurveElementPtr(pElement);
//}

void CCurveElement::DrawNormal(Display::IDisplayPtr pDisplay)
{
	
}
}
