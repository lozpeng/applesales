#include "StdAfx.h"
#include "HorizontalLegendItem.h"


namespace Element
{

CHorizontalLegendItem::CHorizontalLegendItem()
{
	m_type = LIT_HORIZONTAL;
}
CHorizontalLegendItem::CHorizontalLegendItem(Carto::ILayerPtr	pLayer):ILegendItem(pLayer)
{
	m_Arrange = LIA_PatchLabelDescription;
}

CHorizontalLegendItem::~CHorizontalLegendItem(void)
{
}

void CHorizontalLegendItem::serialization(SYSTEM::IArchive &ar)
{
	ILegendItem::serialization(ar);

	if(ar.IsRead())
	{
		int arrange;
		ar & arrange;
		m_Arrange = (LegendItemArrangement)arrange;
	}
	else
	{
		int arrange = (int)m_Arrange;
		ar & arrange;
	}
}

ILegendItemPtr CHorizontalLegendItem::Clone()
{
	CHorizontalLegendItem* pClone = new CHorizontalLegendItem(m_pLayer);

	*pClone = *this;

	pClone->m_pLayerNameSymbol = m_pLayerNameSymbol->Clone();
	pClone->m_pHeadingSymbol = m_pHeadingSymbol->Clone();
	pClone->m_pLabelSymbol = m_pLabelSymbol->Clone();
	pClone->m_pDescriptionSymbol = m_pDescriptionSymbol->Clone();

	CHorizontalLegendItemPtr pNewItem(pClone);
	return pNewItem;
}

void CHorizontalLegendItem::Draw(Display::IDisplayPtr pDisplay, DIS_RECT& rect)
{
	ILegendItem::Draw(pDisplay, rect);


	DrawLayerName(pDisplay, rect, m_pLayer->GetName());

	Carto::CLegendInfoPtr pInfo = m_pLayer->GetLegendInfo();
	if(!pInfo)
		return;

	for(int i=0; i<pInfo->LegendGroupCount(); i++)
	{
		Carto::CLegendGroupPtr pLegendGroup = m_pLayer->GetLegendInfo()->GetLegendGroup(i);

		DrawHeading(pDisplay, rect, pLegendGroup->GetHeading());

		switch(m_Arrange)
		{
		case LIA_PatchLabelDescription:
			DrawPatchLabelDesc(pDisplay, rect, pLegendGroup);
			break;
		case LIA_PatchDescricptionLabel:
			DrawPatchDescLabel(pDisplay, rect, pLegendGroup);
			break;
		case LIA_LabelPatchDescription:
			DrawLabelPatchDesc(pDisplay, rect, pLegendGroup);
			break;
		case LIA_LabelDescriptionPatch:
			DrawLabelDescPatch(pDisplay, rect, pLegendGroup);
			break;
		case LIA_DescriptionPatchLabel:
			DrawDescPatchLabel(pDisplay, rect, pLegendGroup);
			break;
		case LIA_DescriptionLabelPatch:
			DrawDescLabelPatch(pDisplay, rect, pLegendGroup);
			break;
		}
	}	
}


void CHorizontalLegendItem::DrawLayerName(Display::IDisplayPtr pDisplay, DIS_RECT& rect, std::string strLayerName)
{
	if(!m_bShowLayerName)
		return;

	//计算text绘制rect
	DIS_RECT layerNameSize = ILegendItem::GetTextSize(pDisplay, m_pLayerNameSymbol,  strLayerName);

	DIS_RECT layerNameRect;
	if(!m_bRightToLeft)
	{
		layerNameRect.left = rect.left;
		layerNameRect.right = rect.left + layerNameSize.Width();
		layerNameRect.top = rect.bottom;
		layerNameRect.bottom = rect.bottom + layerNameSize.Height() ;
		
	}
	else
	{
		layerNameRect.right = rect.right;
		layerNameRect.left = rect.right - layerNameSize.Width();
		layerNameRect.top = rect.bottom;
		layerNameRect.bottom = rect.bottom + layerNameSize.Height() ;
	}

	//绘制
	DrawText(pDisplay, m_pLayerNameSymbol, layerNameRect, m_pLayer->GetName(), DT_NOCLIP | DT_NOPREFIX | DT_LEFT | DT_TOP);
	
	//加入间隔
	layerNameRect.bottom += m_LayerNameAndGroupPixel;
	//更新rect
	RectExpandToInclude(rect, layerNameRect);	
}

void CHorizontalLegendItem::DrawHeading(Display::IDisplayPtr pDisplay, DIS_RECT& rect, std::string strHeading)
{
	if(!m_bShowHeading)
		return;
	//计算text绘制rect
	DIS_RECT headingSize = ILegendItem::GetTextSize(pDisplay, m_pHeadingSymbol,  strHeading);

	DIS_RECT headingRect;
	if(!m_bRightToLeft)
	{
		headingRect.left = rect.left;
		headingRect.right = rect.left + headingSize.Width();
		headingRect.top = rect.bottom;
		headingRect.bottom = rect.bottom + headingSize.Height() ;
	}
	else
	{
		headingRect.right = rect.right;
		headingRect.left = rect.right - headingSize.Width();
		headingRect.top = rect.bottom;
		headingRect.bottom = rect.bottom + headingSize.Height() ;
	}	
	//绘制
	DrawText(pDisplay, m_pHeadingSymbol, headingRect, strHeading, DT_NOCLIP | DT_NOPREFIX | DT_LEFT | DT_TOP);

	//加入间隔
	headingRect.bottom += m_HeadingAndClassesPixel;
	//更新rect
	RectExpandToInclude(rect, headingRect);	
}

void CHorizontalLegendItem::DrawPatchLabelDesc(Display::IDisplayPtr pDisplay, DIS_RECT& rect, Carto::CLegendGroupPtr pLegendGroup)
{
	Carto::LegendItem legendClassInfo;
	Display::ISymbolPtr pSymbol;
	DIS_RECT pathRect;
	DIS_RECT labelRect;
	DIS_RECT descriptionRect;
	if(!m_bRightToLeft)
	{
		for(int i=0; i< pLegendGroup->GetItemCount(); i++)
		{
			legendClassInfo = pLegendGroup->GetItem(i);

			//DrawPatch
			pathRect.left = rect.left;
			pathRect.right = rect.left + m_patchWidthPixel;
			pathRect.top = rect.bottom;
			pathRect.bottom = rect.bottom + m_patchHeightPixel ;

			
			pSymbol = legendClassInfo.pSymbol;
			if(pDisplay->GetBeLayoutDisplay())
			{
				float fScale =  1/pDisplay->GetDisplayTransformation().GetMapScale();
				if (fScale != 1.000000)
				{
					if( pSymbol != NULL )
						pSymbol->Zoom( fScale );		
				}
			}
			pSymbol->SelectDC(pDisplay->GetDrawDC());
			legendClassInfo.pSymbol->SetReadyDraw();
			
			if(pSymbol->GetType() & MARKER_SYMBOL || ((pSymbol->GetType() & COMPLEX_SYMBOL) == COMPLEX_MARKER_SYMBOL))
			{				
				legendClassInfo.pSymbol->DrawLegend(&pathRect, m_patchMarkerStyle);
			}
			if ( pSymbol->GetType() & LINE_SYMBOL || ((pSymbol->GetType() & COMPLEX_SYMBOL) == COMPLEX_LINE_SYMBOL) )													//当是线符号
			{
				legendClassInfo.pSymbol->DrawLegend(&pathRect, m_patchLineStyle);
			}
			else if ( pSymbol->GetType() & FILL_SYMBOL || ((pSymbol->GetType() & COMPLEX_SYMBOL) == COMPLEX_FILL_SYMBOL) )													//当是面符号
			{
				legendClassInfo.pSymbol->DrawLegend(&pathRect, m_patchAreaStyle);
			}
			legendClassInfo.pSymbol->ClearDC();
			if(pDisplay->GetBeLayoutDisplay())
			{
				float fScale =  pDisplay->GetDisplayTransformation().GetMapScale();
				if (fScale != 1.000000)
				{
					if( pSymbol != NULL )
						pSymbol->Zoom( fScale );		
				}
			}
			pathRect.right += m_PatchAndOtherPixel;//加入间隔
			RectExpandToInclude(rect, pathRect);	
		

			//DrawLabel
			if(m_bShowDescriptions)
			{
				DIS_RECT labelSize = ILegendItem::GetTextSize(pDisplay, m_pLabelSymbol,  legendClassInfo.strLabel);
				labelRect.left = pathRect.right;
				labelRect.right = labelRect.left + labelSize.Width();
				labelRect.top = pathRect.top;
				labelRect.bottom = labelRect.top + labelSize.Height();
				DrawText(pDisplay, m_pLabelSymbol, labelRect, legendClassInfo.strLabel, DT_NOCLIP | DT_NOPREFIX | DT_LEFT | DT_TOP);

				labelRect.right += m_LabelAndOtherPixel;//加入间隔
				RectExpandToInclude(rect, labelRect);	
			}
			
			

			//DrawDescription
			if(m_bShowDescriptions)
			{
				DIS_RECT DescSize = ILegendItem::GetTextSize(pDisplay, m_pDescriptionSymbol,  legendClassInfo.strDes);
				descriptionRect.left = labelRect.right;
				descriptionRect.right = descriptionRect.left + DescSize.Width();
				descriptionRect.top = labelRect.top;
				descriptionRect.bottom = descriptionRect.top + DescSize.Height();
				DrawText(pDisplay, m_pDescriptionSymbol, descriptionRect, legendClassInfo.strDes, DT_NOCLIP | DT_NOPREFIX | DT_LEFT | DT_TOP);

				rect.bottom += m_ClassesSpacesPixel;
				RectExpandToInclude(rect, descriptionRect);	
			}	

		}
	}
	else
	{
		for(int i=0; i< pLegendGroup->GetItemCount(); i++)
		{
			legendClassInfo = pLegendGroup->GetItem(i);
			
			//DrawPatch
			pathRect.right = rect.right;
			pathRect.left = rect.right - m_patchWidthPixel;
			pathRect.top = rect.bottom;
			pathRect.bottom = rect.bottom + m_patchHeightPixel ;
			
			pSymbol = legendClassInfo.pSymbol;
			pSymbol->SelectDC(pDisplay->GetDrawDC());
			if ( pSymbol->GetType() & LINE_SYMBOL || ((pSymbol->GetType() & COMPLEX_SYMBOL) == COMPLEX_LINE_SYMBOL) )													//当是线符号
			{
				legendClassInfo.pSymbol->DrawLegend(&pathRect, m_patchLineStyle);
			}
			else if ( pSymbol->GetType() & FILL_SYMBOL || ((pSymbol->GetType() & COMPLEX_SYMBOL) == COMPLEX_FILL_SYMBOL) )													//当是面符号
			{
				legendClassInfo.pSymbol->DrawLegend(&pathRect, m_patchAreaStyle);
			}
			pathRect.left -= m_PatchAndOtherPixel;//加入间隔
			RectExpandToInclude(rect, pathRect);	

			//DrawLabel
			if(m_bShowDescriptions)
			{
				DIS_RECT labelSize = ILegendItem::GetTextSize(pDisplay, m_pLabelSymbol,  legendClassInfo.strLabel);
				labelRect.right = pathRect.left;
				labelRect.left = labelRect.right - labelSize.Width();
				labelRect.top = pathRect.top;
				labelRect.bottom = labelRect.top + labelSize.Height();
				DrawText(pDisplay, m_pLabelSymbol, labelRect, legendClassInfo.strLabel, DT_NOCLIP | DT_NOPREFIX | DT_LEFT | DT_TOP);

				labelRect.left -= m_LabelAndOtherPixel;//加入间隔
				RectExpandToInclude(rect, labelRect);	
			}
			

			//DrawDescription
			if(m_bShowDescriptions)
			{
				DIS_RECT DescSize = ILegendItem::GetTextSize(pDisplay, m_pDescriptionSymbol,  legendClassInfo.strDes);
				descriptionRect.right = labelRect.left;
				descriptionRect.left = descriptionRect.right - DescSize.Width();
				descriptionRect.top = labelRect.top;
				descriptionRect.bottom = descriptionRect.top + DescSize.Height();
				DrawText(pDisplay, m_pLabelSymbol, descriptionRect, legendClassInfo.strDes, DT_NOCLIP | DT_NOPREFIX | DT_LEFT | DT_TOP);

				rect.bottom += m_ClassesSpacesPixel;
				RectExpandToInclude(rect, descriptionRect);	
			}
			
		}

	}
}

void CHorizontalLegendItem::DrawPatchDescLabel(Display::IDisplayPtr pDisplay, DIS_RECT& rect, Carto::CLegendGroupPtr pLegendGroup)
{

}


void CHorizontalLegendItem::DrawLabelPatchDesc(Display::IDisplayPtr pDisplay, DIS_RECT& rect, Carto::CLegendGroupPtr pLegendGroup)
{

}


void CHorizontalLegendItem::DrawLabelDescPatch(Display::IDisplayPtr pDisplay, DIS_RECT& rect, Carto::CLegendGroupPtr pLegendGroup)
{

}

void CHorizontalLegendItem::DrawDescPatchLabel(Display::IDisplayPtr pDisplay, DIS_RECT& rect, Carto::CLegendGroupPtr pLegendGroup)
{

}

void CHorizontalLegendItem::DrawDescLabelPatch(Display::IDisplayPtr pDisplay, DIS_RECT& rect, Carto::CLegendGroupPtr pLegendGroup)
{

}





}
