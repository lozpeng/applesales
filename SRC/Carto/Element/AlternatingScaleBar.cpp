#include "StdAfx.h"
#include "AlternatingScaleBar.h"
#include "MapFrame.h"

namespace Element{

CAlternatingScaleBar::CAlternatingScaleBar()
{
	m_enumElementType = ET_ALTERNATING_SCALEBAR;
}
CAlternatingScaleBar::CAlternatingScaleBar(const GEOMETRY::geom::Geometry& geometry, CMapFrame* pMapFrame)
:IScaleBar(geometry, pMapFrame)
{
	m_enumElementType = ET_ALTERNATING_SCALEBAR;
	
	Display::CSimpleFillSymbol* pForeSymbol = new Display::CSimpleFillSymbol;
	pForeSymbol->SetOutLineColor(RGB(0,0,0));
	pForeSymbol->SetFillColor(RGB(255,255,255));
	m_pForeSymbol.reset(pForeSymbol);

	Display::CSimpleFillSymbol* pBackSymbol = new Display::CSimpleFillSymbol;
	pBackSymbol->SetOutLineColor(RGB(0,0,0));
	pBackSymbol->SetFillColor(RGB(0,0,0));
	m_pBackSymbol.reset(pBackSymbol);
}

CAlternatingScaleBar::~CAlternatingScaleBar(void)
{
}

void CAlternatingScaleBar::serialization(SYSTEM::IArchive &ar)
{
	IScaleBar::serialization( ar );
}

void CAlternatingScaleBar::DrawNormal(Display::IDisplayPtr pDisplay)
{
	SYSTEM::SYS_UNIT_TYPE mapUnit = m_pMapFrame->GetMap()->GetUnit();
	double dDivisionLen = SYSTEM::UnitConverter::ConvertUnits(m_DivisionLen, m_Unit, mapUnit);

	IScaleBar::DrawNormal(pDisplay);

}

void CAlternatingScaleBar::DrawBar(Display::IDisplayPtr pDisplay, DIS_RECT rect)
{
	DIS_RECT run;
	for(int i=0; i<m_DivisionNum + m_SubDivisionNum -1; i++)
	{
		run = rect;

		if(i<m_SubDivisionNum)
		{
			run.left = rect.left + i*rect.Width() / double(m_DivisionNum)/double(m_SubDivisionNum) ;
			run.right = rect.left + (i+1)*rect.Width()  / double(m_DivisionNum)/double(m_SubDivisionNum);
		}
		else
		{
			run.left = rect.left + (i-m_SubDivisionNum+1)*rect.Width() / double(m_DivisionNum);
			run.right = rect.left + (i-m_SubDivisionNum+2)*rect.Width() / double(m_DivisionNum);
		}	

		if(1 == i%2)
			pDisplay->SetSymbol(m_pBackSymbol.get());
		else
			pDisplay->SetSymbol(m_pForeSymbol.get());

		pDisplay->Begin();
		pDisplay->Draw(&run);
		pDisplay->End();
	}
}
}
