#include "StdAfx.h"
#include "ElementCollection.h"

namespace Element{
CElementCollection::CElementCollection(void)
{
}

CElementCollection::~CElementCollection(void)
{
}

void CElementCollection::Add(IElementPtr pElement)
{
	m_vecElements.push_back(pElement);

	CollectionChangedEvent();
}

void CElementCollection::Remove(IElementPtr pElement)
{
	std::vector<IElementPtr>::iterator iter = m_vecElements.begin();
	for( ;iter!=m_vecElements.end(); iter++)
	{
		if(*iter == pElement)
		{
			m_vecElements.erase(iter);
			break;
		}
	}

	CollectionChangedEvent();
}

void CElementCollection::Clear()
{
	m_vecElements.clear();

	CollectionChangedEvent();
}

IElementPtr CElementCollection::QueryElement(const long lIndex)
{
	if(0<=lIndex && lIndex <Count())
		return m_vecElements[lIndex];
	else
		return NULL;
}

long CElementCollection::QueryElement(IElementPtr pElement)
{
	for(int i=0; i<m_vecElements.size(); i++)
	{
		if(m_vecElements[i] == pElement)
			return i;
	}
	return -1;
}

long CElementCollection::Count()
{
	return m_vecElements.size();
}

void CElementCollection::CollectionChangedEvent()
{

}
}