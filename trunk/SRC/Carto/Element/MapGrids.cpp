#include "StdAfx.h"
#include "MapGrids.h"
namespace Element{
CMapGrids::CMapGrids(void)
{
}

CMapGrids::~CMapGrids(void)
{
}

void CMapGrids::serialization(SYSTEM::IArchive &ar)
{
	if(ar.IsRead())
	{
		long lSize;
		ar & lSize;
		m_vecMapGrids.clear();
		for(int i=0; i<lSize; i++)
		{
			IMapGridPtr pMapGrid = IMapGrid::CreateGridFromStream(ar);
			m_vecMapGrids.push_back(pMapGrid);
		}
	}
	else
	{
		long lSize = m_vecMapGrids.size();
		ar & lSize;
		for(int i=0; i<m_vecMapGrids.size(); i++)
			m_vecMapGrids[i]->serialization(ar);
	}
}

void CMapGrids::AddMapGrid (IMapGridPtr pMapGird)
{
	m_vecMapGrids.push_back(pMapGird);
}

void CMapGrids::DeleteMapGrid (IMapGridPtr pMapGird)
{
	std::vector<IMapGridPtr>::iterator iter = m_vecMapGrids.begin();
	while(iter != m_vecMapGrids.end())
	{
		if(*iter == pMapGird)
		{
			m_vecMapGrids.erase(iter);
			break;
		}
	}
}

void CMapGrids::DeleteMapGridByIndex (int nIndex)
{
	if(nIndex<0 || nIndex>m_vecMapGrids.size())
		return;

	std::vector<IMapGridPtr>::iterator iter = m_vecMapGrids.begin()+nIndex;	
	m_vecMapGrids.erase(iter);
}

void CMapGrids::ClearMapGrids()
{
	m_vecMapGrids.clear();
}

void CMapGrids::SetMapGrid(int nIndex, IMapGridPtr pMapGird)
{
	if(nIndex<0 || nIndex>m_vecMapGrids.size())
		return;

	m_vecMapGrids[nIndex] = pMapGird;
}

IMapGridPtr CMapGrids::GetMapGrid(int nIndex)
{
	if(nIndex<0 || nIndex>m_vecMapGrids.size()-1)
		return NULL;
	else
		return m_vecMapGrids[nIndex];
}

int CMapGrids::GetGridCount()
{
	return m_vecMapGrids.size();
}
}
