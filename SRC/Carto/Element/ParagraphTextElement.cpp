#include "StdAfx.h"
#include "ParagraphTextElement.h"
#include "EnvelopeTracker.h"

namespace Element{

CParagraphTextElement::CParagraphTextElement()
{
	m_enumElementType = ET_FILL_RECTANGLE_ELEMENT;
	m_pSelectionHandle.reset(new CEnvelopeTracker(GEOMETRY::geom::Envelope(0,0,0,0)));
}
CParagraphTextElement::CParagraphTextElement(const GEOMETRY::geom::Geometry& geometry):ITextElement(geometry)
{
	m_enumElementType = ET_PARAGRAPH_TEXT_ELEMENT;
	m_pSelectionHandle.reset(new CEnvelopeTracker(*geometry.getEnvelopeInternal()));
}

CParagraphTextElement::~CParagraphTextElement(void)
{
}

void CParagraphTextElement::DrawNormal(Display::IDisplayPtr pDisplay)
{
	DIS_RECT textSize, textRect;
	GEOMETRY::geom::Envelope env(0,1,0,1);

	//¼ÆËãtitle´óĞ¡
	pDisplay->SetSymbol(m_pSymbol.get());
	pDisplay->Begin();
	textSize = pDisplay->Draw(&env, m_text, m_bScaleWithMap, DT_CALCRECT | DT_NOCLIP | DT_NOPREFIX | DT_LEFT | DT_TOP);
	pDisplay->End();	
	pDisplay->GetDisplayTransformation().TransformToGeo(textSize, &env);

	GEOMETRY::geom::Envelope oldEnv = *m_pGeometry->getEnvelopeInternal();
	oldEnv = GEOMETRY::geom::Envelope(oldEnv.getMinX(), oldEnv.getMinX()+env.getWidth(), oldEnv.getMinY(), oldEnv.getMinY()+env.getHeight());

	if(m_pGeometry)
	{
		GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(m_pGeometry);
		m_pGeometry = NULL;
	}
	m_pGeometry = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->toGeometry(&oldEnv);
	IElement::GeometryChangedEvents();

	pDisplay->SetSymbol( m_pSymbol.get() );
	pDisplay->Begin();
	pDisplay->Draw( &oldEnv, m_text , m_bScaleWithMap);
	pDisplay->End();

}


	
}
