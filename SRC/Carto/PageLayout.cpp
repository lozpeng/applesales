#include "StdAfx.h"
#include "PageLayout.h"
#include "GraphicLayer.h"

namespace Carto{

	CPageLayout::CPageLayout()
	{
		m_pDisplay = new Display::IDisplay;
		m_bInitialized = FALSE;
		//m_pElementOperStack.reset(new Element::CElementOperationStack());
	}

	CPageLayout::~CPageLayout(void)
	{
	}

	void CPageLayout::serialization(SYSTEM::IArchive& ar)
	{
		SYSTEM::ISerialization::serialization(ar);

		if(ar.IsRead())
		{
			m_Page = Element::CPagePtr(new Element::CPage);
			m_Page->serialization(ar);

			m_pGraphicLayer = CGraphicLayerPtr(new CGraphicLayer);
			m_pGraphicLayer->serialization(ar);

			//m_pElementOperStack->SetLayer(m_pGraphicLayer);
		}
		else
		{
			m_Page->serialization(ar);

			m_pGraphicLayer->serialization(ar);
		}
	}

	void CPageLayout::Initialize(long memDC, long lDCSizeX, long lDCSizeY)
	{
		m_Page.reset(new Element::CPage());
		m_pGraphicLayer.reset(new CGraphicLayer(m_Page->GetPageEnvelope()));
		//m_pElementOperStack->SetLayer(m_pGraphicLayer);

		m_pDisplay->SetLayoutDisplay(TRUE);
		m_pDisplay->SetDC(memDC, lDCSizeX, lDCSizeY);
		m_pDisplay->GetDisplayTransformation().SetUnit(m_Page->GetUnit());
		m_pDisplay->GetDisplayTransformation().FitViewBound(GetExtent());

		m_bInitialized = TRUE;
	}

	Element::CPagePtr CPageLayout::GetPage()
	{
		return m_Page;
	}

	Display::IDisplayPtr CPageLayout::GetDisplay()
	{
		return m_pDisplay;
	}

	CGraphicLayerPtr CPageLayout::GetGraphicLayer()
	{
		return m_pGraphicLayer;
	}

	void CPageLayout::Draw(long content)
	{
		OnBeforeDraw();

		BOOL bPrint = m_pDisplay->GetPrinting();
		if(content&drawElement)
		{
			m_pDisplay->SetDrawBuffer(drawElement);

			m_pDisplay->DrawBackgroud();

			if(m_Page && !bPrint)
				m_Page->Draw(m_pDisplay);

			if(m_pGraphicLayer)
				m_pGraphicLayer->Draw( m_pDisplay,drawElement);
		}

		if((content&drawEdit)&&!bPrint )
		{
			m_pDisplay->SetDrawBuffer(drawEdit);

			if(!bPrint)
				m_pDisplay->DrawBackgroud();

			if(m_Page && !bPrint)
				m_Page->Draw(m_pDisplay);

			if(m_pGraphicLayer)
				m_pGraphicLayer->Draw( m_pDisplay,drawEdit);
		}


		OnAfterDraw();
	}


	void CPageLayout::OnAfterDraw()
	{

	}

	void CPageLayout::OnBeforeDraw()
	{
	}

	void CPageLayout::PrintToImg()
	{

	}

}

