#include "StdAfx.h"
#include "GraphicsContainer.h"


namespace Element{
	static boost::signal<void (Element::IElementPtr pElement)> gCallbackChangeGraphics;
CGraphicsContainer::CGraphicsContainer(void)
{
	Reset();
}

CGraphicsContainer::~CGraphicsContainer(void)
{
}

void CGraphicsContainer::serialization(SYSTEM::IArchive &ar)
{
	
	if( ar.IsRead() )
	{
		long lSize;
		ar & lSize;
		m_vecElements.clear();
		for(int i=0; i<lSize; i++)
		{
			IElementPtr pElement = IElement::CreateElementFromStream(ar);
			m_vecElements.push_back(pElement);
		}
	}
	else
	{
		long lSize = m_vecElements.size();
		ar & lSize;

		for(int i=0; i<lSize; i++)
			m_vecElements[i]->serialization( ar );

		
	}
}

void CGraphicsContainer::AddElement(IElementPtr pElement)
{	
	if(FindElement(pElement)>-1)
		return ;

	m_vecElements.push_back(pElement);

	ContainerChangedEvent(pElement);
}

void CGraphicsContainer::AddElements(CElementCollection elements, BOOL bFrontToBackOrder)
{
	if(bFrontToBackOrder)
	{
		for(int i=0; i<elements.Count();i++)
		{
			IElementPtr pEle= elements.QueryElement(i);
			AddElement(pEle);
		}
	}
	else
	{
		for(int i=elements.Count()-1; i>=0;i--)
		{
			IElementPtr pEle= elements.QueryElement(i);
			AddElement(pEle);
		}
	}
}

void CGraphicsContainer::SetElementAt(long lIndex, IElementPtr pElement)
{
	if(lIndex >= m_vecElements.size() || lIndex <0)
		return;

	m_vecElements[lIndex] = pElement;
	
	ContainerChangedEvent(pElement);
}

void CGraphicsContainer::InserElementAt(long lIndex, IElementPtr pElement)
{
	if(lIndex > m_vecElements.size() || lIndex <0)
		return;

	long oldSize = m_vecElements.size();
	m_vecElements.resize(oldSize+1);
	for(int i=oldSize-1; i>=lIndex; --i)
	{
		m_vecElements[i+1] = m_vecElements[i];
	}

	m_vecElements[lIndex] = pElement;
}

void CGraphicsContainer::RemoveElement(IElementPtr pElement)
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
	
	//ContainerChangedEvent(pElement);
}

void CGraphicsContainer::RemoveAllElements()
{
	m_vecElements.clear();
}

void CGraphicsContainer::BringForward(IElementPtr pElement)
{
	std::vector<IElementPtr>::iterator iter = m_vecElements.begin();
	for( ;iter!=m_vecElements.end(); iter++)
	{
		if(*iter == pElement)
			break;
	}

	if(iter != m_vecElements.begin())
	{
		IElementPtr pCur = *iter;
		IElementPtr pFront = *(iter-1);
		*iter = pFront;
		*(iter-1) = pCur;
	}
}

void CGraphicsContainer::BringForward(CElementCollection pElements)
{
	std::vector<IElementPtr>::iterator iter = m_vecElements.begin();
	for( ;iter!=m_vecElements.end(); iter++)
	{
		IElementPtr pElement = *iter;
		if( -1 != pElements.QueryElement(pElement))
		{
			if(iter != m_vecElements.begin())
			{
				IElementPtr pCur = *iter;
				IElementPtr pFront = *(iter-1);
				*iter = pFront;
				*(iter-1) = pCur;
			}
		}
	}
}

void CGraphicsContainer::SendBackward(IElementPtr pElement)
{
	std::vector<IElementPtr>::iterator iter = m_vecElements.begin();
	for( ;iter!=m_vecElements.end(); iter++)
	{
		if(*iter == pElement)
			break;
	}

	if(iter != m_vecElements.end())
	{
		IElementPtr pCur = *iter;
		IElementPtr pBack = *(iter+1);
		*iter = pBack;
		*(iter+1) = pCur;
	}
}

void CGraphicsContainer::SendBackward(CElementCollection pElements)
{
	if(m_vecElements.size() < 2)
		return;

	for(int i=m_vecElements.size()-1; i>=0; --i)
	{
		IElementPtr pElement = m_vecElements[i];
		if( -1 != pElements.QueryElement(pElement))
		{
			if(i != m_vecElements.size()-1)
			{
				IElementPtr pCur = m_vecElements[i];
				IElementPtr pBack = m_vecElements[i+1];
				m_vecElements[i] = pBack;
				m_vecElements[i+1] = pCur;
			}
		}
	}
}

void CGraphicsContainer::BringToFront(IElementPtr pElement)
{
	std::vector<IElementPtr>::iterator iter = m_vecElements.begin();
	for( ;iter!=m_vecElements.end(); iter++)
	{
		if(*iter == pElement)
			break;
	}

	if(iter != m_vecElements.begin())
	{
		IElementPtr pCur = *iter;
		for( ;iter != m_vecElements.begin();iter--)
			*iter = *(iter-1);
		*iter = pCur;
	}
}

void CGraphicsContainer::BringToFront(CElementCollection pElements)
{
	if(m_vecElements.size() < 2)
		return;

	int nFind = 0;
	for(int i=0; i<m_vecElements.size(); ++i)
	{
		IElementPtr pElement = m_vecElements[i];
		if( -1 != pElements.QueryElement(pElement))
		{
			if(i != 0)
			{
				IElementPtr pCur = m_vecElements[i];
				for( int j=i; j>nFind; --j)
					m_vecElements[j] = m_vecElements[j-1];
				m_vecElements[nFind] = pCur;
			}
			nFind++;
		}
	}
}


void CGraphicsContainer::SendToBack(IElementPtr pElement)
{
	std::vector<IElementPtr>::iterator iter = m_vecElements.begin();
	for( ;iter!=m_vecElements.end(); iter++)
	{
		if(*iter == pElement)
			break;
	}

	if(iter+1 != m_vecElements.end())
	{
		IElementPtr pCur = *iter;
		for( ;(iter+1) != m_vecElements.end();iter++)
			*iter = *(iter+1);
		*iter = pCur;
	}
}

void CGraphicsContainer::SendToBack(CElementCollection pElements)
{
	if(m_vecElements.size() < 2)
		return;

	int nFind = 0;
	for(int i=m_vecElements.size()-1; i>=0; --i)
	{
		IElementPtr pElement = m_vecElements[i];
		if( -1 != pElements.QueryElement(pElement))
		{
			for(int j=i; j+1<m_vecElements.size()-nFind; j++)
			{
				m_vecElements[j] = m_vecElements[j+1];
			}

			m_vecElements[m_vecElements.size()-1 - nFind] = pElement;

			nFind++;
		}	
	}
}

void CGraphicsContainer::MoveElementToGroup(IElementPtr pElement, CGroupElementPtr pGroupElement)
{
	RemoveElement(pElement);

	pGroupElement->Add(pElement);
}

void CGraphicsContainer::MoveElementFromGroup(IElementPtr pElement, CGroupElementPtr pGroupElement)
{
	pGroupElement->Remove(pElement);

	AddElement(pElement);
}

IElementPtr CGraphicsContainer::Next()
{
	if(m_iter+1 != m_vecElements.end() && m_iter != m_vecElements.end())
	{
		m_iter++;
		return *m_iter;
	}
	else
	{
		return NULL;
	}
}

IElementPtr CGraphicsContainer::Pre()
{
	if(m_iter != m_vecElements.begin())
	{
		m_iter--; 
		return *m_iter;
	}
	else
	{
		return NULL;
	}
}

IElementPtr CGraphicsContainer::Reset(BOOL bFirst)
{
	if(bFirst)
	{
		m_iter = m_vecElements.begin();
		if(m_vecElements.empty())
			return NULL;
		else
			return *m_iter;
	}
	else
	{
		m_iter = m_vecElements.end();
		if(m_vecElements.empty())
			return NULL;
		else
		{
			m_iter--;
			return *m_iter;
		}
	}
	
}

long CGraphicsContainer::GetElementCount()
{
	return m_vecElements.size();
}

IElementPtr CGraphicsContainer::GetElement(long nIndex)
{
	if(nIndex<0 || nIndex>=m_vecElements.size())
		return NULL;
	else
		return m_vecElements[nIndex];
}

long CGraphicsContainer::FindElement(IElementPtr pElement)
{
	std::vector<IElementPtr>::iterator iter = m_vecElements.begin();
	for( long i=0;iter!=m_vecElements.end(); iter++, i++)
	{
		if(*iter == pElement)
			return i;
	}

	return -1;
}

CElementCollection& CGraphicsContainer::LocateElements(const GEOMETRY::geom::Coordinate *point)
{
	CElementCollection e;
	return e;
}

CElementCollection& CGraphicsContainer::LocateElementsByEnvelope(const GEOMETRY::geom::Envelope *pEnvlope, BOOL bContain)
{
	CElementCollection e;
	return e;
}
boost::signals::connection  Element::CGraphicsContainer::RegisterContainerChanged(boost::function<void (Element::IElementPtr pElement)> fun)
	{
		return gCallbackChangeGraphics.connect(fun);
	}
void CGraphicsContainer::ContainerChangedEvent(IElementPtr pElement)
{
	gCallbackChangeGraphics(pElement);
}

}
