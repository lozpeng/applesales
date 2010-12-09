#include "StdAfx.h"
#include "GraphicsContainerSelect.h"

namespace Element{
CGraphicsContainerSelect::CGraphicsContainerSelect(void)
{
}

CGraphicsContainerSelect::~CGraphicsContainerSelect(void)
{
}

void CGraphicsContainerSelect::SelectElement(IElementPtr pElement)
{

	if(IsElementSelected(pElement))
	{
		UnselectElement(pElement);
		return;
	}
		
	m_SelElements.Add(pElement);
	pElement->SetEditMode(EEM_SELECT);
}
void CGraphicsContainerSelect::SelectElements(CElementCollection elements)
{
	for(int i=0; i<elements.Count();i++)
	{
		IElementPtr pElement= elements.QueryElement(i);
		SelectElement(pElement);
	}
}
IElementPtr CGraphicsContainerSelect::GetSelectedElement(const long lIndex)
{
	return m_SelElements.QueryElement(lIndex);
}
CElementCollection& CGraphicsContainerSelect::GetSelectedElements()
{
	return m_SelElements;
}
long CGraphicsContainerSelect::GetSelectedElementCount()
{
	return m_SelElements.Count();
}
void CGraphicsContainerSelect::UnselectAllElements()
{
	for(int i=m_SelElements.Count()-1; i>=0; i--)
	{
		IElementPtr pElement=m_SelElements.QueryElement(i);
		pElement->SetEditMode(Element::EEM_NO_EDIT);
		m_SelElements.Remove(pElement);
	}
}
void CGraphicsContainerSelect::UnselectElement(IElementPtr pElement)
{
	for(int i=0; i<m_SelElements.Count(); i++)
	{
		if(m_SelElements.QueryElement(i) == pElement)
		{
			m_SelElements.Remove(pElement);
			pElement->SetEditMode(Element::EEM_NO_EDIT);
			break;
		}
	}
}
void CGraphicsContainerSelect::UnselectElements(CElementCollection elements)
{
	for(int i=0; i<elements.Count(); i++)
	{
		IElementPtr pElement = elements.QueryElement(i);

		UnselectElement(pElement);
	}
	
}
DIS_RECT* CGraphicsContainerSelect::SelectionBounds(Display::IDisplayPtr pDisplay)
{	
	if(m_SelElements.IsEmpty())
		return NULL;

	IElementPtr pElement = m_SelElements.QueryElement(0);
	GEOMETRY::geom::Envelope env = pElement->GetEnvelope();

	for(int i=1 ;i<m_SelElements.Count(); i++)
	{
		pElement = m_SelElements.QueryElement(i);
		env.expandToInclude(&pElement->GetEnvelope());
	}

	return pDisplay->GetDisplayTransformation().TransformToDisplay(&env);
}

DIS_RECT* CGraphicsContainerSelect::SelectionTracker(Display::IDisplayPtr pDisplay, long lIndex)
{
	IElementPtr pElement = m_SelElements.QueryElement(lIndex);
	return pDisplay->GetDisplayTransformation().TransformToDisplay(&pElement->GetEnvelope());
}

BOOL CGraphicsContainerSelect::IsElementSelected(IElementPtr pElement)
{
	for(int i=0; i<m_SelElements.Count(); i++)
	{
		if(m_SelElements.QueryElement(i) == pElement)
		{
			return TRUE;
		}
	}

	return FALSE;
}




};
