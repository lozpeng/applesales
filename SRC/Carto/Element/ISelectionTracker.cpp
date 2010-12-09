#include "StdAfx.h"
#include "ISelectionTracker.h"

namespace Element{

ISelectionTracker::ISelectionTracker(void)
{
	m_pGeometry = NULL;
	m_pHandlePoints = NULL;
	m_pFillSymbol.reset(new Display::CSimpleFillSymbol);
	m_pMarkerSymbol.reset(new Display::CSimpleMarkerSymbol());

	
}

ISelectionTracker::~ISelectionTracker(void)
{
	if(m_pGeometry)
	{
		GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(m_pGeometry);
		m_pGeometry = NULL;
	}
}

void ISelectionTracker::Draw(Display::IDisplayPtr pDisplay)
{
	pDisplay->SetSymbol( m_pFillSymbol.get() );

	pDisplay->Begin();

	if(m_pGeometry)
		pDisplay->Draw( m_pGeometry );

	pDisplay->End();



	pDisplay->SetSymbol( m_pMarkerSymbol.get() );

	pDisplay->Begin();

	if(m_pHandlePoints)
		pDisplay->Draw( m_pHandlePoints );

	pDisplay->End();
}

void ISelectionTracker::SetGeometry(const GEOMETRY::geom::Geometry& geometry)
{
	if(m_pGeometry)
	{
		GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(m_pGeometry);
		m_pGeometry = NULL;
	}
	m_pGeometry = geometry.clone();
}

HIT_HANDLE ISelectionTracker::HitTest( GEOMETRY::geom::Coordinate coord, double dbTolerance)
{
	return HH_HIT_NONE;
}

void ISelectionTracker::MoveHandleTo(HIT_HANDLE nHandle,GEOMETRY::geom::Coordinate coord)
{

}

GEOMETRY::geom::Envelope ISelectionTracker::GetEnvelope()
{
	return *m_pGeometry->getEnvelopeInternal();
}

}
