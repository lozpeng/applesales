#include "StdAfx.h"
#include "SimpleBorder.h"
#include "SimpleShadow.h"
#include "SymbolFactory.h"

namespace Element{
CSimpleBorder::CSimpleBorder(void)
{
	InitFillSymbol();
}

CSimpleBorder::CSimpleBorder(const GEOMETRY::geom::Geometry& geometry)
:IBorder(geometry)
{
	InitFillSymbol();
}

CSimpleBorder::~CSimpleBorder(void)
{
}

void CSimpleBorder::serialization(SYSTEM::IArchive &ar)
{
	IBorder::serialization(ar);

	if(ar.IsRead())
	{
		m_pFillSymbol = Display::CSymbolFactory::CreateSymbolFromStream(ar);
	}
	else
	{
		m_pFillSymbol->serialization(ar);
	}
}

SYSTEM::CSmartPtr<CSimpleBorder> CSimpleBorder::Clone()
{
	CSimpleBorder* pBorder = new CSimpleBorder;
	*pBorder = *this;
	pBorder->m_pFillSymbol = m_pFillSymbol->Clone();
	pBorder->m_pGeometry = m_pGeometry->clone();
	pBorder->m_pDrawGeometry = m_pDrawGeometry->clone();
	return CSimpleBorderPtr(pBorder);
}

void CSimpleBorder::Draw(Display::IDisplayPtr pDisplay)
{
	pDisplay->SetSymbol( m_pFillSymbol.get() );

	pDisplay->Begin();

	if(m_pDrawGeometry)
		pDisplay->Draw( m_pDrawGeometry );

	pDisplay->End();


}

void CSimpleBorder::SetSymbol(Display::ILineSymbolPtr pLineSymbol)
{
	m_pFillSymbol->SetOutLineSymbol(pLineSymbol);
}

Display::ILineSymbolPtr CSimpleBorder::GetSymbol()
{
	return m_pFillSymbol->GetOutLineSymbol();
}

void CSimpleBorder::InitFillSymbol()
{
	m_pFillSymbol.reset(new Display::CSimpleFillSymbol);
	m_pFillSymbol->SetDrawFill(FALSE);
	m_pFillSymbol->SetOutLineColor(RGB(0,0,0));
}



}

