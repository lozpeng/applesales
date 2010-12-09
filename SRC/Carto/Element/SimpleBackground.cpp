#include "StdAfx.h"
#include "SimpleBackground.h"
#include "SimpleFillSymbol.h"
#include "SymbolFactory.h"
namespace Element{
CSimpleBackground::CSimpleBackground(void)
{
	m_type = BT_SIMPLE_BG;
	InitFillSymbol();
}

CSimpleBackground::CSimpleBackground(const GEOMETRY::geom::Geometry& geometry)
:IBackground(geometry)
{
	m_type = BT_SIMPLE_BG;
	InitFillSymbol();
}

CSimpleBackground::~CSimpleBackground(void)
{
}

void CSimpleBackground::serialization(SYSTEM::IArchive &ar)
{
	IBackground::serialization(ar);

	if(ar.IsRead())
	{
		m_pFillSymbol = Display::CSymbolFactory::CreateSymbolFromStream(ar);
	}
	else
	{
		m_pFillSymbol->serialization(ar);
	}
}

SYSTEM::CSmartPtr<CSimpleBackground> CSimpleBackground::Clone()
{
	CSimpleBackground* pBackground = new CSimpleBackground;
	*pBackground = *this;
	pBackground->m_pFillSymbol = m_pFillSymbol->Clone();
	pBackground->m_pGeometry = m_pGeometry->clone();
	pBackground->m_pDrawGeometry = m_pDrawGeometry->clone();
	return CSimpleBackgroundPtr(pBackground);
}

void CSimpleBackground::Draw(Display::IDisplayPtr pDisplay)
{
	pDisplay->SetSymbol( m_pFillSymbol.get() );

	pDisplay->Begin();

	if(m_pDrawGeometry)
		pDisplay->Draw( m_pDrawGeometry );

	pDisplay->End();
}

void CSimpleBackground::SetSymbol(Display::IFillSymbolPtr pFillSymbol)
{
	m_pFillSymbol = pFillSymbol;
}

Display::IFillSymbolPtr CSimpleBackground::GetSymbol()
{
	return m_pFillSymbol;
}

void CSimpleBackground::InitFillSymbol()
{
	m_pFillSymbol.reset(new Display::CSimpleFillSymbol);
	m_pFillSymbol->SetDrawOutLine(FALSE);
	m_pFillSymbol->SetFillColor(RGB(255,255,255));
}

}
