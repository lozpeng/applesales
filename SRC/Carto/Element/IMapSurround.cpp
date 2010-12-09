#include "StdAfx.h"
#include "IMapSurround.h"
#include "MapFrame.h"
namespace Element{
IMapSurround::IMapSurround(void)
{
	m_pMapFrame = NULL;
}

IMapSurround::IMapSurround(const GEOMETRY::geom::Geometry& geometry, CMapFrame* pMapFrame)
:IFrameElementBase(geometry)
{
	m_pMapFrame = pMapFrame;

	m_MapFrameID = m_pMapFrame->GetMapFrameID();
}

IMapSurround::IMapSurround(CMapFrame* pMapFrame)
{
	m_pMapFrame = pMapFrame;

	m_MapFrameID = m_pMapFrame->GetMapFrameID();
}

IMapSurround::~IMapSurround(void)
{
}

void IMapSurround::serialization(SYSTEM::IArchive &ar)
{
	IFrameElementBase::serialization( ar );

	ar & m_MapFrameID;
}

void IMapSurround::SetMapFrame(CMapFrame* pMapFrame)
{
	m_pMapFrame = pMapFrame;

	m_MapFrameID = m_pMapFrame->GetMapFrameID();

	MapFrameSettedEvent();
}

CMapFrame* IMapSurround::GetMapFrame()
{
	return m_pMapFrame;
}

void IMapSurround::MapFrameSettedEvent()
{

}

void IMapSurround::DelayEvent(BOOL bDelay)
{

}

void IMapSurround::Refresh()
{

}

IElementPtr IMapSurround::Clone()
{
	IMapSurroundPtr pElement = IElement::Clone();
	pElement->SetMapFrame(m_pMapFrame);

	return pElement;
}

}
