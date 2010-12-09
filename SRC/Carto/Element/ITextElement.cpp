#include "StdAfx.h"
#include "ITextElement.h"
#include "SymbolFactory.h"


namespace Element{

ITextElement::ITextElement():IElement()
{
	m_bScaleWithMap = FALSE;
	m_text = "text";
	m_pSymbol.reset(new Display::CTextSymbol);

	m_bDrawBg = FALSE;

	m_pFillSymbol = Display::CSimpleFillSymbolPtr(new Display::CSimpleFillSymbol);

	m_bCanSetWHRMode = FALSE;
}

ITextElement::ITextElement(const GEOMETRY::geom::Geometry& geometry):IElement(geometry)
{
	m_bScaleWithMap = FALSE;
	m_text = "text";
	m_pSymbol.reset(new Display::CTextSymbol);

	m_bDrawBg = FALSE;

	m_pFillSymbol = Display::CSimpleFillSymbolPtr(new Display::CSimpleFillSymbol);
	

	m_coordOrg.x = geometry.getEnvelopeInternal()->getMinX();
	m_coordOrg.y = geometry.getEnvelopeInternal()->getMinY();

	m_bCanSetWHRMode = FALSE;
}

ITextElement::~ITextElement(void)
{
}

void ITextElement::serialization(SYSTEM::IArchive &ar)
{
	IElement::serialization(ar);

	ar & m_bScaleWithMap;

	ar & m_text;

	ar & m_coordOrg.x;

	ar & m_coordOrg.y;

	ar & m_bDrawBg;

	if(ar.IsRead())
	{
		m_pFillSymbol = Display::CSymbolFactory::CreateSymbolFromStream(ar);
	}
	else
	{
		m_pFillSymbol->serialization(ar);
	}
}

void ITextElement::SetDrawBg(BOOL bDraw)
{
	m_bDrawBg = bDraw;
}
BOOL ITextElement::GetDrawBg()
{
	return m_bDrawBg;
}

void ITextElement::SetFillSymbol(Display::CSimpleFillSymbolPtr pFillSymbol)
{
	m_pFillSymbol = pFillSymbol;
}
Display::CSimpleFillSymbolPtr ITextElement::GetFillSymbol()
{
	return m_pFillSymbol;
}

void ITextElement::SetScaleWithMap(BOOL bScaleWithMap)
{
	m_bScaleWithMap = bScaleWithMap;
}

void ITextElement::ChangeGeometryEnvelopTo(GEOMETRY::geom::Envelope& newEnvelope)
{
	GEOMETRY::geom::Envelope oldEnv = *m_pGeometry->getEnvelopeInternal();
	double scaleX, scaleY;
	scaleX = newEnvelope.getWidth()/oldEnv.getWidth();
	scaleY = newEnvelope.getHeight()/oldEnv.getHeight();

	m_coordOrg.x = newEnvelope.getMinX() + (m_coordOrg.x - oldEnv.getMinX())*scaleX;
	m_coordOrg.y = newEnvelope.getMinY() + (m_coordOrg.y - oldEnv.getMinY())*scaleY;

	Display::CTextSymbol* pTextSym = dynamic_cast<Display::CTextSymbol*>(m_pSymbol.get());
	pTextSym->SetTextSize(pTextSym->GetTextSize()*scaleY);

	IElement::ChangeGeometryEnvelopTo(newEnvelope);
}

void ITextElement::GeometryChangedEvents()
{
	if(m_pGeometry)
	{
		//改变文字的原点
		m_coordOrg.x = m_pGeometry->getEnvelopeInternal()->getMinX();
		m_coordOrg.y = m_pGeometry->getEnvelopeInternal()->getMinY();
	}
	IElement::GeometryChangedEvents();
}

}
