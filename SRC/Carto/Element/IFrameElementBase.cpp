#include "StdAfx.h"
#include "IFrameElementBase.h"
#include "SymbolFactory.h"

namespace Element{

IFrameElementBase::IFrameElementBase(void): IFrameProperty()
{
	m_bDrawBackground = FALSE;

	m_bDrawBorder = FALSE;

	m_bDrawShadow = FALSE;
}

IFrameElementBase::IFrameElementBase(const GEOMETRY::geom::Geometry& geometry):IElement(geometry), IFrameProperty(geometry)
{
	m_bDrawBackground = FALSE;

	m_bDrawBorder = FALSE;

	m_bDrawShadow = FALSE;

	m_strName = "地图";

	Display::CTextSymbol* pTextSymbol = new Display::CTextSymbol;
	DIS_FONT font = pTextSymbol->GetTextFont();
	font.lfHeight = 16;
	pTextSymbol->SetTextFont(font);
	m_FrameNameSymbol.reset(pTextSymbol);

}
IFrameElementBase::~IFrameElementBase(void)
{
}
//////////////////////////////////////////////////////////////////////////
void IFrameElementBase::serialization(SYSTEM::IArchive &ar)
{
	IElement::serialization(ar);
	IFrameProperty::serialization(ar);

	ar & m_bDrawBorder;

	ar & m_bDrawBackground;

	ar & m_bDrawShadow;

	if(ar.IsRead())
	{
		m_FrameNameSymbol = Display::CSymbolFactory::CreateSymbolFromStream(ar);
	}
	else
	{
		m_FrameNameSymbol->serialization(ar);
	}
}
void IFrameElementBase::SetDrawBorder(BOOL bDrawBorder)
{
	m_bDrawBorder= bDrawBorder;
}
BOOL IFrameElementBase::GetDrawBorder()
{
	return m_bDrawBorder;
}

void IFrameElementBase::SetDrawBackground(BOOL bDrawBackground)
{
	m_bDrawBackground= bDrawBackground;
}
BOOL IFrameElementBase::GetDrawBackground()
{
	return m_bDrawBackground;
}

void IFrameElementBase::SetDrawShadow(BOOL bDrawShadow)
{
	m_bDrawShadow= bDrawShadow;
}
BOOL IFrameElementBase::GetDrawShadow()
{
	return m_bDrawShadow;
}

void IFrameElementBase::GetThumbnail(long* bitmapHandle)
{

}
//////////////////////////////////////////////////////////////////////////
BOOL IFrameElementBase::Select(GEOMETRY::geom::Geometry* pSelectGeometry, long lSpatialRelation, CElementCollection& selectedSubElements,double dbTolerance)
{
	IElementPtr pElement;
	GEOMETRY::geom::Envelope envelope = GetEnvelope();
	if(pSelectGeometry->getGeometryTypeId() == GEOMETRY::geom::GEOS_POINT)//点选情况下
	{
		if(envelope.contains(*pSelectGeometry->getCoordinate()))
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
				if(pSelectGeometry->getEnvelopeInternal()->intersects(&envelope))
					return TRUE;
				else
					return FALSE;
			}
			break;
			//多边形包含选择
		case Geodatabase::SpatialRelContains:
			{
				if(pSelectGeometry->getEnvelopeInternal()->contains(&envelope))
					return TRUE;
				else
					return FALSE;
			}
			break;
		default:
			{
				if(pSelectGeometry->getEnvelopeInternal()->contains(&envelope))
					return TRUE;
				else
					return FALSE;
			}
			break;
		}
	}
}


//////////////////////////////////////////////////////////////////////////
void IFrameElementBase::DrawBackground(Display::IDisplayPtr pDisplay)
{
	if(m_bDrawShadow)
		m_pShadow->Draw(pDisplay);
	if(m_bDrawBackground)
		m_pBackground->Draw(pDisplay);
}

void IFrameElementBase::DrawForeground(Display::IDisplayPtr pDisplay)
{	
	if(m_bDrawBorder)
		m_pBorder->Draw(pDisplay);
}



void IFrameElementBase::DrawOnDrawMode(Display::IDisplayPtr pDisplay)
{
	DrawEnvelope(pDisplay);

	DrawBackground(pDisplay);

	DrawForeground(pDisplay);
}

void IFrameElementBase::DrawMoveMode(Display::IDisplayPtr pDisplay)
{
	DrawEnvelope(pDisplay);

	DrawBackground(pDisplay);

	DrawForeground(pDisplay);
}

void IFrameElementBase::DrawDraft( Display::IDisplayPtr pDisplay)
{
	DrawBackground(pDisplay);

	pDisplay->SetSymbol(m_FrameNameSymbol.get());

	pDisplay->Begin();
	
	GEOMETRY::geom::Coordinate cood;
	m_pGeometry->getCentroid(cood);
	pDisplay->Draw(&GEOMETRY::geom::Envelope(cood.x-10, cood.x+10, cood.y-10, cood.y+10), m_strName, TRUE, DT_NOCLIP | DT_NOPREFIX | DT_LEFT | DT_TOP);

	pDisplay->End();

	DrawForeground(pDisplay);
}

void IFrameElementBase::DrawPrint(Display::IDisplayPtr pDisplay)
{
	IElement::DrawPrint(pDisplay);
}

void IFrameElementBase::GeometryChangedEvents()
{
	GEOMETRY::geom::Envelope* pEnv = (GEOMETRY::geom::Envelope*)m_pGeometry->getEnvelopeInternal();
	if(m_pBackground)
	{
		m_pBackground->SetGeometry(*m_pGeometry);
		pEnv->expandToInclude(m_pBackground->GetDrawGeometry()->getEnvelopeInternal());
	}

	if(m_pBorder)
	{
		m_pBorder->SetGeometry(*m_pGeometry);
		pEnv->expandToInclude(m_pBorder->GetDrawGeometry()->getEnvelopeInternal());
	}

	GEOMETRY::geom::Geometry* pGeoShadow = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->toGeometry(pEnv);
	if(m_pShadow)
		m_pShadow->SetGeometry(*pGeoShadow);

	GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(pGeoShadow);

	IElement::GeometryChangedEvents();
}
}