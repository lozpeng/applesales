#include "StdAfx.h"
#include "ScaleLine.h"
#include "MapFrame.h"

namespace Element{

CScaleLine::CScaleLine()
{
	m_enumElementType = ET_SCALELINE;
}
CScaleLine::CScaleLine(const GEOMETRY::geom::Geometry& geometry, CMapFrame* pMapFrame)
:IScaleBar(geometry, pMapFrame)
{
	m_enumElementType = ET_SCALELINE;

	Display::CSimpleLineSymbol* pBackSymbol = new Display::CSimpleLineSymbol;
	pBackSymbol->SetLineColor(RGB(0,0,0));
	pBackSymbol->SetLineWidth(1);
	m_pBackSymbol.reset(pBackSymbol);

	Display::CSimpleLineSymbol* pForeSymbol = new Display::CSimpleLineSymbol;
	pForeSymbol->SetLineColor(RGB(0,0,0));
	pForeSymbol->SetLineWidth(1);
	m_pForeSymbol.reset(pForeSymbol);

	m_BarHeight = SYSTEM::UnitConverter::ConvertUnits(pBackSymbol->GetLineWidth(), SYSTEM::SYS_UNIT_POINT, SYSTEM::SYS_UNIT_MILLIMETER);
	/*if(m_BarHeight<1)
		m_BarHeight = 1;*/
}

CScaleLine::~CScaleLine(void)
{
}

void CScaleLine::serialization(SYSTEM::IArchive &ar)
{
	IScaleBar::serialization( ar );
}

void CScaleLine::ConvertMillimeterToPixel(Display::IDisplayPtr pDisplay)
{
	IScaleBar::ConvertMillimeterToPixel(pDisplay);

	Display::CSimpleLineSymbol* pBackSymbol = dynamic_cast<Display::CSimpleLineSymbol*>(m_pBackSymbol.get());
	
	m_BarHeight = SYSTEM::UnitConverter::ConvertUnits(pBackSymbol->GetLineWidth(), SYSTEM::SYS_UNIT_POINT, SYSTEM::SYS_UNIT_MILLIMETER);

	/*if(m_BarHeight<1)
		m_BarHeight = 1;*/

	pDisplay->GetDisplayTransformation().MillimeterToDisplay(m_BarHeight, m_BarHeightPixel);
}

void CScaleLine::DrawNormal(Display::IDisplayPtr pDisplay)
{
	SYSTEM::SYS_UNIT_TYPE mapUnit = m_pMapFrame->GetMap()->GetUnit();
	double dDivisionLen = SYSTEM::UnitConverter::ConvertUnits(m_DivisionLen, m_Unit, mapUnit);

	IScaleBar::DrawNormal(pDisplay);

}

void CScaleLine::DrawBar(Display::IDisplayPtr pDisplay, DIS_RECT rect)
{
	DIS_LINE run;
	run.Count = 2;
	run.ps[0].x = rect.left;
	run.ps[0].y = rect.bottom - m_BarHeightPixel/2;
	run.ps[1].x = rect.right;
	run.ps[1].y = rect.bottom - m_BarHeightPixel/2;

	pDisplay->SetSymbol(m_pBackSymbol.get());
		
	pDisplay->Begin();
		
	pDisplay->Draw(&run);
		
	pDisplay->End();
}
}
