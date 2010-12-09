#include "StdAfx.h"
#include "GroupElement.h"
#include "SymbolFactory.h"
#include "EnvelopeTracker.h"

namespace Element{
CGroupElement::CGroupElement(void)
{
	m_enumElementType = ET_GROUP_ELEMENT;

	m_bCanSetWHRMode = TRUE;

	m_eWHRatio = Element::EWHR_FREE_RATIO;

	m_pSelectionHandle.reset();

}

CGroupElement::~CGroupElement(void)
{
}

void CGroupElement::serialization(SYSTEM::IArchive &ar)
{
	SYSTEM::ISerialization::serialization( ar );
	if(ar.IsRead() )
	{
		int i;
		ar & i;
		//ASSERT( m_enumElementType = (ELEMENT_TYPE)i);
		ar & m_strName;
		ar & m_bLocked;
		ar & m_bActive;
		ar & i;
		m_AnchorPos = (ELEMENT_ANCHOR_POS)i;

		m_pEnvelopeSymbol = Display::CSymbolFactory::CreateSymbolFromStream(ar);
		ar & i;
		m_DrawMode = (ELEMENT_DRAW_MODE)i;

		m_pVertixMarkerSymbol = Display::CSymbolFactory::CreateSymbolFromStream(ar);
		m_pTrakerLineSymbol = Display::CSymbolFactory::CreateSymbolFromStream(ar);

		GEOMETRY::io::WKTReader GeoReader;
		std::string strGeo;
		ar & strGeo;
		m_pGeometry = GeoReader.read(strGeo);

		long cnt;
		ar & cnt;

		for(int i=0; i<cnt; i++)
		{
			IElementPtr pElement = IElement::CreateElementFromStream(ar);
			m_vecElements.push_back(pElement);
		}

		CollectionChangedEvent();
	}
	else
	{
		int i = m_enumElementType;
		ar & (i);
		ar & m_strName;
		ar & m_bLocked;
		ar & m_bActive;
		i = m_AnchorPos;
		ar & i;
		m_pEnvelopeSymbol->serialization( ar );
		i =  m_DrawMode;
		ar & i;
		m_pVertixMarkerSymbol->serialization( ar );
		m_pTrakerLineSymbol->serialization( ar );

		GEOMETRY::io::WKTWriter GeoWriter;
		std::string strGeo= GeoWriter.write(m_pGeometry); 
		ar & strGeo;

		long cnt = Count();
		ar & cnt;

		for(int i=0; i<Count(); i++)
			m_vecElements[i]->serialization(ar);
	}
}

//SYSTEM::CSmartPtr<IElement> CGroupElement::Clone()
//{
//	CGroupElement* pGroup = new CGroupElement;
//
//	*pGroup = *this;
//
//	for(int i=0; i<Count(); i++)
//		pGroup->Add(m_vecElements[i]->Clone());
//
//	return CGroupElementPtr(pGroup);
//}
void CGroupElement::CollectionChangedEvent()
{
	if(m_pGeometry)
	{
		GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(m_pGeometry);
		m_pGeometry = NULL;
	}

	ELEMENT_WIDTH_HEIGHT_RATIO curEWHR = m_eWHRatio;
	GEOMETRY::geom::Envelope env(0,0,0,0);
	for(int i=0; i<Count(); i++)
	{
		IElementPtr pElement = QueryElement(i);
		if(i==0)
			env = pElement->GetEnvelope();
		else
			env.expandToInclude(&pElement->GetEnvelope());

		
		if(!pElement->CanSetWHRMode())
			m_bCanSetWHRMode = FALSE;

		if(pElement->GetWHRatioMode() == Element::EWHR_FIX_RATIO)
			curEWHR = Element::EWHR_FIX_RATIO;
	}

	m_pGeometry = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->toGeometry(&env);

	SetWHRatioMode(curEWHR);

}

void CGroupElement::ChangeGeometryEnvelopTo(GEOMETRY::geom::Envelope& newEnvelope)
{
	if(!m_pGeometry)
		return;

	GEOMETRY::geom::Envelope oldEnv = *m_pGeometry->getEnvelopeInternal();
	double scaleX, scaleY;
	scaleX = newEnvelope.getWidth()/oldEnv.getWidth();
	scaleY = newEnvelope.getHeight()/oldEnv.getHeight();

	for(int i=0; i<Count(); i++)
	{
		IElementPtr pElement = QueryElement(i);
		GEOMETRY::geom::Envelope subEnv = pElement->GetEnvelope();

		subEnv.init(newEnvelope.getMinX() + scaleX*(subEnv.getMinX()-oldEnv.getMinX()), newEnvelope.getMinX() + scaleX*(subEnv.getMaxX()-oldEnv.getMinX()),
			newEnvelope.getMinY() + scaleY*(subEnv.getMinY()-oldEnv.getMinY()), newEnvelope.getMinY() + scaleY*(subEnv.getMaxY()-oldEnv.getMinY()));
		
		pElement->ChangeGeometryEnvelopTo(subEnv);
	}


	CollectionChangedEvent();
}

void CGroupElement::Scale(DIS_POINT pPoint, double sx, double sy)
{
	for(int i=0; i<Count(); i++)
	{
		IElementPtr pElement = QueryElement(i);
		pElement->Scale(pPoint, sx, sy);
	}

	CollectionChangedEvent();
}


void CGroupElement::Move(double dx, double dy)
{
	for(int i=0; i<Count(); i++)
	{
		IElementPtr pElement = QueryElement(i);
		pElement->Move(dx, dy);
	}

	CollectionChangedEvent();
}

void CGroupElement::Rotate(DIS_POINT pPoint, double rotationAngle)
{
	for(int i=0; i<Count(); i++)
	{
		IElementPtr pElement = QueryElement(i);
		pElement->Rotate(pPoint, rotationAngle);
	}

	CollectionChangedEvent();
}


void CGroupElement::DrawNormal(Display::IDisplayPtr pDisplay)
{
	for(int i=0; i<Count(); i++)
	{
		IElementPtr pElement = QueryElement(i);
		pElement->Draw(pDisplay);
	}

//	CollectionChangedEvent();
}


void CGroupElement::SetWHRatioMode(ELEMENT_WIDTH_HEIGHT_RATIO eWHRatio)
{
	if(!m_bCanSetWHRMode)
	{
		m_eWHRatio = Element::EWHR_FIX_RATIO;
	}
	else
	{
		m_eWHRatio = eWHRatio;
		for(int i=0; i<Count(); i++)
		{
			IElementPtr pElement = QueryElement(i);

			if(!pElement->CanSetWHRMode())
				m_bCanSetWHRMode = FALSE;

			if(pElement->GetWHRatioMode() == Element::EWHR_FIX_RATIO)
				m_eWHRatio = Element::EWHR_FIX_RATIO;
		}
	}


	if(m_eWHRatio == EWHR_FIX_RATIO)
		m_pSelectionHandle.reset(new CEnvelopeTracker(*m_pGeometry->getEnvelopeInternal(), HT_FOUR));
	else if(m_eWHRatio == EWHR_FREE_RATIO)
		m_pSelectionHandle.reset(new CEnvelopeTracker(*m_pGeometry->getEnvelopeInternal(), HT_EIGHT));

}

BOOL CGroupElement::IsElementExist(IElementPtr pElement)
{
	BOOL exist = FALSE;
	for(int i=0; i<Count(); i++)
	{
		IElementPtr pSubElement = QueryElement(i);
		if(pElement == pSubElement)
			return TRUE;

		if(pSubElement->GetType() == ET_GROUP_ELEMENT)
		{
			CGroupElement* pSubGroupElement = dynamic_cast<CGroupElement*>(pSubElement.get());

			if(pSubGroupElement->IsElementExist(pElement))
				return TRUE;
		}
	}
	return FALSE;
}

BOOL CGroupElement::IsMapSurroundElementExist()
{
	BOOL exist = FALSE;
	for(int i=0; i<Count(); i++)
	{
		IElementPtr pSubElement = QueryElement(i);
		if(pSubElement->GetType() & ET_MAP_SURROUND_ELEMENT)
			return TRUE;

		if(pSubElement->GetType() == ET_GROUP_ELEMENT)
		{
			CGroupElement* pSubGroupElement = dynamic_cast<CGroupElement*>(pSubElement.get());

			if(pSubGroupElement->IsMapSurroundElementExist())
				return TRUE;
		}
	}
	return FALSE;
}
}
