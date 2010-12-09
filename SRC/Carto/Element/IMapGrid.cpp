#include "StdAfx.h"
#include "IMapGrid.h"
#include "MapFrame.h"

namespace Element{

IMapGrid::IMapGrid()
{
	m_pMapFrame = NULL;
}

IMapGrid::IMapGrid(CMapFrame* pMapFrame)
{
	m_pMapFrame = pMapFrame;
}

IMapGrid::~IMapGrid(void)
{
}

void IMapGrid::serialization(SYSTEM::IArchive &ar)
{
	IGrid::serialization(ar);
}

CMapFrame* IMapGrid::GetMapFrame()
{
	return m_pMapFrame;
}

void IMapGrid::SetMapFrame(CMapFrame* mapFrame)
{
	m_pMapFrame = mapFrame;
}
}