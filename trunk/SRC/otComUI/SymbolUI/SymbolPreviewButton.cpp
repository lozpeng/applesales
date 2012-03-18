// otDrawButton.cpp : 实现文件
//

#include "stdafx.h"
#include "SymbolPreviewButton.h"
#include "CDC.h"

// CotDrawButton
IMPLEMENT_DYNAMIC(CSymbolPreviewButton, CButton)
CSymbolPreviewButton::CSymbolPreviewButton()
{
	m_pSymbol= NULL;
	

}
CSymbolPreviewButton::~CSymbolPreviewButton()
{
	
}

BEGIN_MESSAGE_MAP(CSymbolPreviewButton, CButton)
END_MESSAGE_MAP()

void CSymbolPreviewButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	//CButton::DrawItem(lpDrawItemStruct);

	CRect rect(lpDrawItemStruct->rcItem);

	if( m_pSymbol != NULL )
	{
		Display::CDC *pDrawDC =new Display::CDC();
		pDrawDC->SetDC((long)lpDrawItemStruct->hDC,rect.Width(),rect.Height());

		DIS_RECT DrawRect;
		DrawRect.top = rect.top;
		DrawRect.left = rect.left;
		DrawRect.right = rect.right;
		DrawRect.bottom= rect.bottom;


		m_pSymbol->SelectDC(pDrawDC);
		m_pSymbol->SetReadyDraw();
		//通过符号绘制图例
		m_pSymbol->DrawLegend(&DrawRect,0);

		m_pSymbol->ClearDC();	

		delete pDrawDC;
	}
}
void CSymbolPreviewButton::SetSymbol(Display::ISymbol* pSymbol)
{
	m_pSymbol = pSymbol;
	if(IsWindow(GetSafeHwnd()))
	{
		InvalidateRect(NULL);
	}
}




