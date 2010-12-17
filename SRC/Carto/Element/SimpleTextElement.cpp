#include "StdAfx.h"
#include "SimpleTextElement.h"
#include "EnvelopeTracker.h"

namespace Element{

	CSimpleTextElement::CSimpleTextElement():ITextElement()
	{
		m_enumElementType = ET_SIMPLE_TEXT_ELEMENT;
		m_pSelectionHandle.reset(new CEnvelopeTracker(GEOMETRY::geom::Envelope(0,0,0,0)));

		m_pFillSymbol->SetFillColor(RGB(255,255,210));
		m_pFillSymbol->SetDrawOutLine(FALSE);
	}

	CSimpleTextElement::CSimpleTextElement(const GEOMETRY::geom::Geometry& geometry):ITextElement(geometry)
	{
		m_enumElementType = ET_SIMPLE_TEXT_ELEMENT;
		m_pSelectionHandle.reset(new CEnvelopeTracker(*geometry.getEnvelopeInternal()));

		m_pFillSymbol->SetFillColor(RGB(255,255,210));
		m_pFillSymbol->SetDrawOutLine(FALSE);
	}

	CSimpleTextElement::~CSimpleTextElement(void)
	{
	}

	void CSimpleTextElement::serialization(SYSTEM::IArchive &ar)
	{
		ITextElement::serialization(ar);
	}


	void CSimpleTextElement::Move(double dx, double dy)
	{
		if(!m_pGeometry)
			return;

		m_pGeometry->Move(dx,dy);

		m_coordOrg.x += dx;
		m_coordOrg.y += dy;

		IElement::GeometryChangedEvents();
	}

	void CSimpleTextElement::DrawNormal(Display::IDisplayPtr pDisplay)
	{
		DIS_RECT textRect;
		//	GEOMETRY::geom::Envelope env(m_coordOrg.x,m_coordOrg.x,m_coordOrg.y,m_coordOrg.y);
		const GEOMETRY::geom::Envelope *pGeoEnv = m_pGeometry->getEnvelopeInternal();
		GEOMETRY::geom::Envelope env( ( pGeoEnv->getMinX() + pGeoEnv->getMaxX() ) / 2, ( pGeoEnv->getMinX() + pGeoEnv->getMaxX() ) / 2, ( pGeoEnv->getMinY() + pGeoEnv->getMaxY() ) / 2, ( pGeoEnv->getMinY() + pGeoEnv->getMaxY() ) / 2);

		//计算envelope，更新geometry
		pDisplay->SetSymbol(m_pSymbol.get());
		pDisplay->Begin();
		textRect = pDisplay->Draw(&env, m_text, m_bScaleWithMap);
		pDisplay->End();


		GEOMETRY::geom::Envelope envelope;
		pDisplay->GetDisplayTransformation().TransformToGeo(textRect, &envelope);
		if(m_pGeometry)
		{
			GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(m_pGeometry);
			m_pGeometry = NULL;
		}
		m_pGeometry = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->toGeometry(&envelope);

		IElement::GeometryChangedEvents();


		//绘制背景
		if(m_bDrawBg)
		{
			pDisplay->SetSymbol( m_pFillSymbol.get() );

			pDisplay->Begin();

			pDisplay->Draw( m_pGeometry );

			pDisplay->End();
		}

		//绘制文字
		pDisplay->SetSymbol(m_pSymbol.get());
		pDisplay->Begin();
		textRect = pDisplay->Draw(&env, m_text, m_bScaleWithMap);
		pDisplay->End();

	}

}
