#include "StdAfx.h"
#include "SelectionSymbol.h"
#include "SymbolFactory.h"
#include "SimpleMarkerSymbol.h"
#include "SimpleLineSymbol.h"
#include "SimpleFillSymbol.h"

namespace Display
{
static CSelectionSymbol gStyleManger;

CSelectionSymbol::CSelectionSymbol(void)
{
     Init();
}

CSelectionSymbol::~CSelectionSymbol(void)
{
}

void CSelectionSymbol::Init()
{
	COLORREF HighlightColor =RGB(0,255,255); 
    
	//µã·ûºÅ
	m_pSelPtSymbol = Display::CSymbolFactory::CreateSymbol(SIMPLE_MARKER_SYMBOL);
	m_pSelPtSymbol->SetColor(HighlightColor);
	m_pSelPtSymbol->SetUnit(SYSTEM::SYS_UNIT_MILLIMETER);
	dynamic_cast<CSimpleMarkerSymbol*>(m_pSelPtSymbol.get())->SetMarkerSize(2.0f);

    //Ïß·ûºÅ
	m_pSelLineSymbol = Display::CSymbolFactory::CreateSymbol(SIMPLE_LINE_SYMBOL);
    m_pSelLineSymbol->SetColor(HighlightColor);
	m_pSelLineSymbol->SetUnit(SYSTEM::SYS_UNIT_MILLIMETER);
	dynamic_cast<CSimpleLineSymbol*>(m_pSelLineSymbol.get())->SetLineWidth(1.0f);

	//Ãæ·ûºÅ
	m_pSelAreaSymbol = Display::CSymbolFactory::CreateSymbol(SIMPLE_FILL_SYMBOL);
	CSimpleFillSymbol *pfillSymbol =dynamic_cast<CSimpleFillSymbol*>(m_pSelAreaSymbol.get());
    pfillSymbol->SetDrawFill(false);
	pfillSymbol->SetOutLineColor(HighlightColor);

	m_pSelAreaSymbol->SetUnit(SYSTEM::SYS_UNIT_MILLIMETER);
	pfillSymbol->SetOutLineWidth(1.0f);




}

CSelectionSymbol* CSelectionSymbol::GetInstance()
{
	return &gStyleManger;
}

ISymbolPtr CSelectionSymbol::GetHighLightPtSymbol()
{
	return m_pSelPtSymbol;
}

ISymbolPtr CSelectionSymbol::GetHighLightLineSymbol()
{
	return m_pSelLineSymbol;
}

ISymbolPtr CSelectionSymbol::GetHighLightAreaSymbol()
{
	return m_pSelAreaSymbol;
}

void CSelectionSymbol::SetHighLightPtSymbol(Display::ISymbolPtr pSymbol)
{
	m_pSelPtSymbol =pSymbol;
}

void CSelectionSymbol::SetHighLightLineSymbol(Display::ISymbolPtr pSymbol)
{
	m_pSelLineSymbol =pSymbol;
}

void CSelectionSymbol::SetHighLightAreaSymbol(Display::ISymbolPtr pSymbol)
{
	m_pSelAreaSymbol =pSymbol;
}



} 

