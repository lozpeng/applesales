#include "StdAfx.h"
#include "NeatLine.h"
#include "EnvelopeTracker.h"

namespace Element{

CNeatLine::CNeatLine()
{
	m_enumElementType = ET_NEAT_LINE;

	m_bDrawBorder = TRUE;

	m_bDrawBackground = TRUE;

	m_bDrawShadow = TRUE;

	m_pSelectionHandle.reset(new CEnvelopeTracker(GEOMETRY::geom::Envelope(0,0,0,0), HT_EIGHT));

}
CNeatLine::CNeatLine(const GEOMETRY::geom::Geometry& geometry, CMapFrame* pMapFrame):IMapSurround(geometry, pMapFrame)
{
	m_enumElementType = ET_NEAT_LINE;

	m_bDrawBorder = TRUE;

	m_bDrawBackground = TRUE;

	m_bDrawShadow = TRUE;

	m_pBackground->GetSymbol()->SetFillColor(RGB(255,255,210));

	m_pSelectionHandle.reset(new CEnvelopeTracker(GetEnvelope(), HT_EIGHT));
}

CNeatLine::~CNeatLine(void)
{
}

void CNeatLine::DrawNormal(Display::IDisplayPtr pDisplay)
{

	IFrameElementBase::DrawBackground(pDisplay);

	IFrameElementBase::DrawForeground(pDisplay);
}

void CNeatLine::serialization(SYSTEM::IArchive &ar)
{
	IMapSurround::serialization( ar );
}

}

