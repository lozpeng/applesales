#include "StdAfx.h"
#include "SimpleShadow.h"
#include "SimpleFillSymbol.h"
#include "SymbolFactory.h"
namespace Element{
CSimpleShadow::CSimpleShadow(void)
{
	InitFillSymbol();
}

CSimpleShadow::CSimpleShadow(const GEOMETRY::geom::Geometry& geometry)
:IShadow(geometry)
{
	InitFillSymbol();
}

CSimpleShadow::~CSimpleShadow(void)
{
}

void CSimpleShadow::serialization(SYSTEM::IArchive &ar)
{
	IShadow::serialization(ar);

	if(ar.IsRead())
	{
		m_pFillSymbol = Display::CSymbolFactory::CreateSymbolFromStream(ar);
	}
	else
	{
		m_pFillSymbol->serialization(ar);
	}
}

SYSTEM::CSmartPtr<CSimpleShadow> CSimpleShadow::Clone()
{
	CSimpleShadow* pShadow = new CSimpleShadow;
	*pShadow = *this;
	pShadow->m_pFillSymbol = m_pFillSymbol->Clone();
	pShadow->m_pGeometry = m_pGeometry->clone();
	pShadow->m_pDrawGeometry = m_pDrawGeometry->clone();
	return CSimpleShadowPtr(pShadow);
}

void CSimpleShadow::Draw(Display::IDisplayPtr pDisplay)
{
	pDisplay->SetSymbol( m_pFillSymbol.get() );

	pDisplay->Begin();

	if(m_pDrawGeometry)
		pDisplay->Draw( m_pDrawGeometry );

	pDisplay->End();
}

void CSimpleShadow::SetSymbol(Display::IFillSymbolPtr pFillSymbol)
{
	m_pFillSymbol = pFillSymbol;
}

Display::IFillSymbolPtr CSimpleShadow::GetSymbol()
{
	return m_pFillSymbol;
}

void CSimpleShadow::InitFillSymbol()
{
	m_pFillSymbol.reset(new Display::CSimpleFillSymbol);
	m_pFillSymbol->SetDrawOutLine(FALSE);
	m_pFillSymbol->SetFillColor(RGB(200,200,200));
}

}
