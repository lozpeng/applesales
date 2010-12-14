#include "StdAfx.h"
#include "IFillShapeElement.h"
#include "SymbolFactory.h"

namespace Element{
IFillShapeElement::IFillShapeElement(void)
{
	InitFillShape();
}
IFillShapeElement::IFillShapeElement(const GEOMETRY::geom::Geometry& geometry):IGraphicElement(geometry)
{
	InitFillShape();	
}

IFillShapeElement::~IFillShapeElement(void)
{
}

void IFillShapeElement::serialization(SYSTEM::IArchive &ar)
{
	IElement::serialization( ar );
	if(ar.IsRead() )
	{
		m_pFillDraftSymbol = Display::CSymbolFactory::CreateSymbolFromStream(ar);
		m_pOnDrawSymbol = Display::CSymbolFactory::CreateSymbolFromStream(ar);
		m_pMoveSymbol = Display::CSymbolFactory::CreateSymbolFromStream(ar);
	}
	else
	{
		m_pMoveSymbol->serialization( ar );
		m_pFillDraftSymbol->serialization( ar );
		m_pOnDrawSymbol->serialization( ar );
	}
}

void IFillShapeElement::DrawNormal(Display::IDisplayPtr pDisplay)
{
	pDisplay->SetSymbol( m_pSymbol.get() );

	pDisplay->Begin();

	pDisplay->Draw( m_pGeometry );

	pDisplay->End();
}

void IFillShapeElement::DrawOnDrawMode(Display::IDisplayPtr pDisplay)
{
	pDisplay->SetSymbol( m_pOnDrawSymbol.get() );

	pDisplay->Begin();

	pDisplay->Draw( m_pGeometry );

	pDisplay->End();
}

void IFillShapeElement::DrawMoveMode(Display::IDisplayPtr pDisplay)
{
	pDisplay->SetSymbol( m_pMoveSymbol.get() );

	pDisplay->Begin();

	pDisplay->Draw( m_pGeometry );

	pDisplay->End();
}

void IFillShapeElement::InitFillShape()
{
	Display::CSimpleFillSymbol *pFillSymbol = new Display::CSimpleFillSymbol;
	pFillSymbol->SetFillColor(RGB(255,255,210));
	pFillSymbol->SetOutLineColor(RGB(0,0,0));
	m_pSymbol.reset(pFillSymbol);

	m_pOnDrawSymbol.reset(new Display::CSimpleFillSymbol);
	m_pOnDrawSymbol->SetDrawFill(FALSE);
	m_pOnDrawSymbol->SetOutLineColor(RGB(0,0,0));
	

	m_pMoveSymbol.reset(new Display::CSimpleFillSymbol);
	m_pMoveSymbol->SetDrawFill(FALSE);
	m_pMoveSymbol->SetOutLineColor(RGB(0,0,0));
	

	m_pFillDraftSymbol.reset(new Display::CSimpleFillSymbol);
	m_pFillDraftSymbol->SetFillColor(RGB(255,255,255));
	m_pFillDraftSymbol->SetOutLineColor(RGB(0,0,0));
}
}
