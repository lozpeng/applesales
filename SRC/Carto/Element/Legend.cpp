#include "StdAfx.h"
#include "Legend.h"
#include "SymbolFactory.h"
#include "HorizontalLegendItem.h"
#include "SimpleBackground.h"
#include "SimpleBorder.h"
#include "MapFrame.h"
#include "EnvelopeTracker.h"

#include <boost/function.hpp>
#include <boost/bind.hpp>
namespace Element{

CLegend::CLegend()
{
	m_enumElementType = ET_LEGEND;

	m_strName = "比例尺";

	m_pSelectionHandle.reset(new CEnvelopeTracker(GEOMETRY::geom::Envelope(0,0,0,0), HT_FOUR));

	m_bCanSetWHRMode = FALSE;

	m_eWHRatio = EWHR_FIX_RATIO;

	m_pMapFrame = NULL;

	//////////////////////////////////////////////////////////////////////////

	boost::function<void (CMapFrame*)> funms = boost::bind(&CLegend::CallbackMapFrameMapSettedFun,this, _1);

	m_ConnectionMapFrameMapSetted = CMapFrame::RegisterMapFrameMapSetted(funms);

	boost::function<void (CMapFrame*)> funmp = boost::bind(&CLegend::CallbackMapFrameProperChangedFun,this, _1);

	m_ConnectionMapFrameProperChanged = CMapFrame::RegisterMapFrameProperChanged(funmp);

	boost::function<void (Carto::ILayerPtr)> fundl = boost::bind(&CLegend::CallbackMapLayerDeleted,this, _1);

	m_ConnectionMapLayerDeleted = Carto::CMap::RegisterDeleteLayer(fundl);
}

CLegend::CLegend(const GEOMETRY::geom::Geometry& geometry,CMapFrame* pMapFrame):IMapSurround(geometry, pMapFrame)
{
	m_enumElementType = ET_LEGEND;

	m_strName = "比例尺";

	m_strLegendTitle = "图例";
	m_pTitleSymbol.reset(new Display::CTextSymbol);
	m_pTitleSymbol->SetTextPosType(TXTPOS_RIGHTTOP);
	DIS_FONT font = m_pTitleSymbol->GetTextFont();
	font.lfHeight = 16;
	m_pTitleSymbol->SetTextFont(font);
	m_titlePos = TDS_CENTER;

	//
	m_TitleToItems = 2;//mm
	m_ColumnSpace = 2;//mm

	for(int i=0; i<pMapFrame->GetMap()->GetLayers().GetSize(); i++ )
	{
		CHorizontalLegendItemPtr pItem(new CHorizontalLegendItem(pMapFrame->GetMap()->GetLayers().GetAt(i)));
		AddItem(pItem);
	}

	m_bDrawBackground = TRUE;
	m_pBackground->SetGap(2,2);
	((CSimpleBackgroundPtr)m_pBackground)->GetSymbol()->SetFillColor(RGB(255,255,210));

	m_bDrawBorder = TRUE;
	m_pBorder->SetGap(2,2);

	m_patchWidth = 5;
	m_patchHeight = 5;
	m_patchLineStyle = LSLS_HORIZONTAL;	//线符号patch的显示样式
	m_patchAreaStyle = FSLS_RECT;		//面符号patch的显示样式
	m_patchMarkerStyle = MSLS_SIMPLE;	//点符号patch的显示样式

	m_LayerNameAndGroup = 1;
	m_HeadingAndClasses = 1;
	m_ClassesSpaces = 2;
	m_PatchAndOther = 2;
	m_LabelAndOther = 2;

	m_pAllTextSymbol.reset(new Display::CTextSymbol);
	m_pLayerNameSymbol.reset(new Display::CTextSymbol);
	m_pHeadingSymbol.reset(new Display::CTextSymbol);
	m_pLabelSymbol.reset(new Display::CTextSymbol);
	m_pDescriptionSymbol.reset(new Display::CTextSymbol);

	m_pAllTextSymbol->SetTextPosType(TXTPOS_RIGHTTOP);
	m_pLayerNameSymbol->SetTextPosType(TXTPOS_RIGHTTOP);
	m_pHeadingSymbol->SetTextPosType(TXTPOS_RIGHTTOP);
	m_pLabelSymbol->SetTextPosType(TXTPOS_RIGHTTOP);
	m_pDescriptionSymbol->SetTextPosType(TXTPOS_RIGHTTOP);

	m_contentChanged = TRUE;

	m_pSelectionHandle.reset(new CEnvelopeTracker(*geometry.getEnvelopeInternal(), HT_FOUR));

	m_bCanSetWHRMode = FALSE;

	m_eWHRatio = EWHR_FIX_RATIO;

	//////////////////////////////////////////////////////////////////////////

	boost::function<void (CMapFrame*)> funms = boost::bind(&CLegend::CallbackMapFrameMapSettedFun,this, _1);

	m_ConnectionMapFrameMapSetted = CMapFrame::RegisterMapFrameMapSetted(funms);

	boost::function<void (CMapFrame*)> funmp = boost::bind(&CLegend::CallbackMapFrameProperChangedFun,this, _1);

	m_ConnectionMapFrameProperChanged = CMapFrame::RegisterMapFrameProperChanged(funmp);

	boost::function<void (Carto::ILayerPtr)> fundl = boost::bind(&CLegend::CallbackMapLayerDeleted,this, _1);

	m_ConnectionMapLayerDeleted = Carto::CMap::RegisterDeleteLayer(fundl);

}

CLegend::~CLegend(void)
{
	m_ConnectionMapFrameMapSetted.disconnect();

	m_ConnectionMapFrameProperChanged.disconnect();

	m_ConnectionMapLayerDeleted.disconnect();
}

void CLegend::serialization(SYSTEM::IArchive &ar)
{
	IMapSurround::serialization( ar );

	ar & m_bRightToLeft;

	ar & m_strLegendTitle;

	ar & m_bAutoAdd;

	ar & m_bAutoReorder;

	ar & m_bAutoVisilility;

	m_legendFormat.serialization(ar);

	ar & m_bDrawTitle;

	ar & m_strLegendTitle;

	ar & m_TitleToItems;

	ar & m_ColumnSpace;

	ar & m_patchWidth;

	ar & m_patchHeight;

	ar & m_LayerNameAndGroup;

	ar & m_HeadingAndClasses;

	ar & m_ClassesSpaces;

	ar & m_PatchAndOther;

	ar & m_LabelAndOther;

	if(ar.IsRead())
	{
		int input;
		ar & input;
		m_vecLegendItems.clear();
		for(int i=0; i<input; i++)
		{
			int layerID ;
			ar & layerID;

			ILegendItemPtr pLegendItem = ILegendItem::CreateLegendItemFromStream(ar);
			pLegendItem->SetLayerID(layerID);	

			m_vecLegendItems.push_back(pLegendItem);
		}

		m_pTitleSymbol = Display::CSymbolFactory::CreateSymbolFromStream(ar);

		ar & input;
		m_titlePos = (TITLE_DRAW_STYLE)input;

		ar & input;
		m_patchLineStyle = (LineSymbolLegendStyle)input;

		ar & input;
		m_patchAreaStyle = (FillSymbolLegendStyle)input;

		ar & input;
		m_patchMarkerStyle = (MarkerSymbolLegendStyle)input;

		m_pAllTextSymbol = Display::CSymbolFactory::CreateSymbolFromStream(ar);

		m_pLayerNameSymbol = Display::CSymbolFactory::CreateSymbolFromStream(ar);;

		m_pHeadingSymbol = Display::CSymbolFactory::CreateSymbolFromStream(ar);;

		m_pLabelSymbol = Display::CSymbolFactory::CreateSymbolFromStream(ar);;

		m_pDescriptionSymbol = Display::CSymbolFactory::CreateSymbolFromStream(ar);

		MapFrameSettedEvent();
	}
	else
	{
		int input = m_vecLegendItems.size();
		ar & input;
		for(int i=0; i<input; i++)
		{
			ILegendItemPtr pLegendItem = m_vecLegendItems[i];
			int layerID = m_pMapFrame->GetMap()->GetLayers().FindIndex(pLegendItem->GetLayer());
			if(layerID != -1)
			{
				ar & layerID;

				pLegendItem->serialization(ar);		
			}		
		}

		m_pTitleSymbol->serialization(ar);

		input = (int)m_titlePos;
		ar & input;

		input = (int)m_patchLineStyle;
		ar & input;
		
		input = (int)m_patchAreaStyle;
		ar & input;
		
		input = (int)m_patchMarkerStyle;
		ar & input;
		
		m_pAllTextSymbol->serialization(ar);

		m_pLayerNameSymbol->serialization(ar);

		m_pHeadingSymbol->serialization(ar);

		m_pLabelSymbol->serialization(ar);

		m_pDescriptionSymbol->serialization(ar);

	}
}

void CLegend::DrawNormal(Display::IDisplayPtr pDisplay)
{

	if(m_contentChanged)
		RecalcGeometry(pDisplay);

	DrawBackground(pDisplay);


	DIS_RECT* pRect = pDisplay->GetDisplayTransformation().TransformToDisplay(m_pGeometry->getEnvelopeInternal());
	pRect->right = pRect->left;
	pRect->bottom = pRect->top;

	//留出title的位置
	long disTitleToItem;
	pDisplay->GetDisplayTransformation().MillimeterToDisplay(m_TitleToItems, disTitleToItem);
	DIS_RECT titleRect = GetTitleSize(pDisplay, m_pTitleSymbol);
	pRect->right = pRect->left+titleRect.Width();
	pRect->bottom = pRect->top+titleRect.Height()+disTitleToItem;
	titleRect = *pRect;

	//按列绘制图例项
	long disCol;
	pDisplay->GetDisplayTransformation().MillimeterToDisplay(m_ColumnSpace, disCol);

	DIS_RECT itemsRect, colRect, itemRect;
	itemsRect.left = pRect->left;
	itemsRect.right = pRect->right;
	itemsRect.top = itemsRect.bottom = pRect->bottom;

	colRect.left = colRect.right = itemsRect.left;
	colRect.top = colRect.bottom = itemsRect.top;

	for(int i=0;i< m_vecLegendItems.size(); i++)
	{
		if(m_vecLegendItems[i]->GetStartCol())
		{
			if(i!=0)
			{
				colRect.left = colRect.right  = colRect.right + disCol;
				colRect.top = colRect.bottom  = itemsRect.top;
			}
		}

		itemRect.left = itemRect.right = colRect.left;
		itemRect.top = itemRect.bottom = colRect.bottom;
		m_vecLegendItems[i]->Draw(pDisplay, itemRect);

		RectExpandToInclude(colRect, itemRect);
		RectExpandToInclude(itemsRect, colRect);
	}

	RectExpandToInclude(*pRect, itemsRect);

	//绘制图例标题
	titleRect.left = pRect->left;
	titleRect.right = pRect->right;
	DrawLegendTitle(pDisplay, titleRect);

	DrawForeground(pDisplay);

	FreeDisplayObj(pRect);
}

void CLegend::DrawLegendTitle(Display::IDisplayPtr pDisplay, DIS_RECT& rect)
{
	GEOMETRY::geom::Envelope env(0,1,0,1);

	DIS_RECT textSize, textRect;

	//计算title大小	
	textSize = GetTitleSize(pDisplay, m_pTitleSymbol);

	textRect.bottom = rect.top+textSize.Height();
	textRect.top = rect.top;
	if(m_titlePos == TDS_LEFT)
	{
		textRect.right = rect.left+textSize.Width();
		textRect.left = rect.left;
	}
	else if(m_titlePos == TDS_CENTER)
	{
		textRect.right = (rect.left+rect.right)/2 + textSize.Width()/2;
		textRect.left = (rect.left+rect.right)/2 - textSize.Width()/2;
	}
	else if(m_titlePos == TDS_RIGHT)
	{
		textRect.right = rect.right;
		textRect.left = rect.right - textSize.Width();
	}

	
	//绘制title
	pDisplay->GetDisplayTransformation().TransformToGeo(textRect, &env);
	pDisplay->SetSymbol(m_pTitleSymbol.get());
	pDisplay->Begin();
	pDisplay->Draw(&env, m_strLegendTitle, TRUE);
	pDisplay->End();
}


void CLegend::RecalcGeometry(Display::IDisplayPtr pDisplay)
{
	DIS_RECT *pRect = pDisplay->GetDisplayTransformation().TransformToDisplay(m_pGeometry->getEnvelopeInternal());
	pRect->right = pRect->left;
	pRect->bottom = pRect->top;

	//留出title空间
	DIS_RECT titleRect = GetTitleSize(pDisplay, m_pTitleSymbol);
	pRect->right = pRect->left+titleRect.Width();
	pRect->bottom = pRect->top+titleRect.Height();

	long disPixel;
	pDisplay->GetDisplayTransformation().MillimeterToDisplay(m_ColumnSpace, disPixel);

	DIS_RECT itemsRect, colRect, itemRect;
	itemsRect.left = pRect->left;
	itemsRect.right = pRect->right;
	itemsRect.top = itemsRect.bottom = pRect->bottom;

	colRect.left = colRect.right = itemsRect.left;
	colRect.top = colRect.bottom = itemsRect.top;

	for(int i=0;i< m_vecLegendItems.size(); i++)
	{
		if(m_vecLegendItems[i]->GetStartCol())
		{
			if(i!=0)
			{
				colRect.left = colRect.right  = colRect.right + disPixel;
				colRect.top = colRect.bottom  = itemsRect.top;
			}
		}

		itemRect.left = itemRect.right = colRect.left;
		itemRect.top = itemRect.bottom = colRect.bottom;
		m_vecLegendItems[i]->Draw(pDisplay, itemRect);
		
		RectExpandToInclude(colRect, itemRect);
		RectExpandToInclude(itemsRect, colRect);
	}

	RectExpandToInclude(*pRect, itemsRect);

	

	GEOMETRY::geom::Envelope env;
	DIS_RECT rect;
	rect.top = pRect->top;
	rect.bottom = pRect->bottom;
	rect.left = pRect->left;
	rect.right = pRect->right;
	pDisplay->GetDisplayTransformation().TransformToGeo(rect, &env);
	m_pGeometry = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->toGeometry(&env);

	GeometryChangedEvents();

	m_contentChanged = FALSE;

	FreeDisplayObj(pRect);
}

DIS_RECT CLegend::GetTitleSize(Display::IDisplayPtr pDisplay, Display::CTextSymbolPtr pTextSymbol)
{
	GEOMETRY::geom::Envelope env(0,0,1,1);

	DIS_RECT textSize;

	pDisplay->SetSymbol(m_pTitleSymbol.get());

	pDisplay->Begin();

	textSize = pDisplay->Draw(&env, m_strLegendTitle, TRUE, DT_CALCRECT | DT_NOCLIP | DT_NOPREFIX | DT_LEFT | DT_TOP);

	pDisplay->End();

	return textSize;
}

void CLegend::DelayEvent(BOOL bDelay)
{

}

void CLegend::FitToEnvelope(Display::IDisplayPtr pDisplay, GEOMETRY::geom::Envelope *pEnvelope, BOOL bSizeChanged)
{

}
void CLegend::GetEnvelope(Display::IDisplayPtr pDisplay, GEOMETRY::geom::Envelope *pEnvelope)
{

}
void CLegend::Refresh()
{

}

//////////////////////////////////////////////////////////////////////////
void CLegend::AddItem(ILegendItemPtr pLegendItem)
{
	m_vecLegendItems.push_back(pLegendItem);
	m_contentChanged = TRUE;
}
void CLegend::ClearItem()
{
	m_vecLegendItems.clear();
	m_contentChanged = TRUE;
}
void CLegend::InsertItem(long lIndex, ILegendItemPtr pLegendItem)
{
	std::vector<ILegendItemPtr>::iterator iter = m_vecLegendItems.begin() + lIndex;
	m_vecLegendItems.insert(iter, pLegendItem);
	m_contentChanged = TRUE;
}
void CLegend::RemoveIntem(long lIndex)
{
	std::vector<ILegendItemPtr>::iterator iter = m_vecLegendItems.begin() + lIndex;
	m_vecLegendItems.erase(iter);
	m_contentChanged = TRUE;
}
int CLegend::GetItemCount()
{
	return m_vecLegendItems.size();
}

ILegendItemPtr CLegend::GetItem(long lIndex)
{
	return m_vecLegendItems[lIndex];
}

//////////////////////////////////////////////////////////////////////////
void CLegend::SetReadDirection(BOOL bRightToLeft)
{
	if(m_bRightToLeft != bRightToLeft)
		m_contentChanged = TRUE;

	m_bRightToLeft = bRightToLeft;
	for(int i=0;i< m_vecLegendItems.size(); i++)
		m_vecLegendItems[i]->SetReadDirection(bRightToLeft);
}
BOOL CLegend::GetReadDirection()
{
	return m_bRightToLeft;
}

void CLegend::SetDrawTitle(BOOL bDrawTitle)
{
	if(m_bDrawTitle != bDrawTitle)
		m_contentChanged = TRUE;
	m_bDrawTitle = bDrawTitle;

}
BOOL CLegend::GetDrawTitle()
{
	return m_bDrawTitle;
}

void CLegend::SetTitleSymbol(Display::CTextSymbolPtr titleSymbol)
{
	m_pTitleSymbol = titleSymbol;
	m_contentChanged = TRUE;
}
Display::CTextSymbolPtr CLegend::GetTitleSymbol()
{
	return m_pTitleSymbol;
}

void  CLegend::SetTitlePos(TITLE_DRAW_STYLE titlePos)
{
	m_titlePos = titlePos;
}

TITLE_DRAW_STYLE  CLegend::GetTitlePos()
{
	return m_titlePos;
}

void CLegend::SetColumnSpace(float fSpace)
{
	m_ColumnSpace = fSpace;
}
float CLegend::GetColumnSpace()
{
	return m_ColumnSpace;
}

void CLegend::SetTitleItemSpace(float fSpace)
{
	m_TitleToItems = fSpace;
}
float CLegend::GetTitleItemSpace()
{
	return m_TitleToItems;
}

void CLegend::SetPatchWidth(float fWidth)
{
	m_patchWidth = fWidth;
	for(int i=0;i< m_vecLegendItems.size(); i++)
		m_vecLegendItems[i]->SetPatchWidth(m_patchWidth);

	m_contentChanged = TRUE;
}
float CLegend::GetPatchWidth()
{
	return m_patchWidth;
}

void CLegend::SetPatchHeight(float fHeight)
{
	m_patchHeight = fHeight;
	for(int i=0;i< m_vecLegendItems.size(); i++)
		m_vecLegendItems[i]->SetPatchHeight(fHeight);

	m_contentChanged = TRUE;
}
float CLegend::GetPatchHeight()
{
	return m_patchHeight;
}

void CLegend::SetPatchMarkerSymbolStyle(MarkerSymbolLegendStyle markerStyle)
{
	m_patchMarkerStyle = markerStyle;
	for(int i=0;i< m_vecLegendItems.size(); i++)
		m_vecLegendItems[i]->SetPatchMarkerSymbolStyle(markerStyle);

	m_contentChanged = TRUE;
}
MarkerSymbolLegendStyle CLegend::GetPatchMarkerSymbolStyle()
{
	return m_patchMarkerStyle;
}

void CLegend::SetPatchLineSymbolStyle(LineSymbolLegendStyle lineStyle)
{
	m_patchLineStyle = lineStyle;
	for(int i=0;i< m_vecLegendItems.size(); i++)
		m_vecLegendItems[i]->SetPatchLineSymbolStyle(lineStyle);

	m_contentChanged = TRUE;
}
LineSymbolLegendStyle CLegend::GetPatchLineSymbolStyle()
{
	return m_patchLineStyle;
}

void CLegend::SetPatchAreaSymbolStyle(FillSymbolLegendStyle areaStyle)
{
	m_patchAreaStyle = areaStyle;
	for(int i=0;i< m_vecLegendItems.size(); i++)
		m_vecLegendItems[i]->SetPatchAreaSymbolStyle(areaStyle);

	m_contentChanged = TRUE;
}
FillSymbolLegendStyle CLegend::GetPatchAreaSymbolStyle()
{
	return m_patchAreaStyle;
}

void CLegend::SetLayerNameAndGroup(float fSpace)
{
	m_LayerNameAndGroup = fSpace;
	for(int i=0;i< m_vecLegendItems.size(); i++)
		m_vecLegendItems[i]->SetLayerNameAndGroup(fSpace);

	m_contentChanged = TRUE;
}
float CLegend::GetLayerNameAndGroup()
{
	return m_LayerNameAndGroup;
}

void CLegend::SetHeadingAndClasses(float fSpace)
{
	m_HeadingAndClasses = fSpace;
	for(int i=0;i< m_vecLegendItems.size(); i++)
		m_vecLegendItems[i]->SetHeadingAndClasses(fSpace);

	m_contentChanged = TRUE;
}
float CLegend::GetHeadingAndClasses()
{
	return m_HeadingAndClasses;
}

void CLegend::SetClassesSpace(float fSpace)
{
	m_ClassesSpaces = fSpace;
	for(int i=0;i< m_vecLegendItems.size(); i++)
		m_vecLegendItems[i]->SetClassesSpace(fSpace);

	m_contentChanged = TRUE;
}
float CLegend::GetClassesSpace()
{
	return m_ClassesSpaces;
}

void CLegend::SetPatchAndOther(float fSpace)
{
	m_PatchAndOther = fSpace;
	for(int i=0;i< m_vecLegendItems.size(); i++)
		m_vecLegendItems[i]->SetPatchAndOther(fSpace);

	m_contentChanged = TRUE;
}
float CLegend::GetPatchAndOther()
{
	return m_PatchAndOther;
}

void CLegend::SetLabelAndOther(float fSpace)
{
	m_LabelAndOther = fSpace;
	for(int i=0;i< m_vecLegendItems.size(); i++)
		m_vecLegendItems[i]->SetLabelAndOther(fSpace);

	m_contentChanged = TRUE;
}
float CLegend::GetLabelAndOther()
{
	return m_LabelAndOther;
}

void CLegend::SetAllTextSymbol(Display::CTextSymbolPtr pAllTextSymbol)
{
	m_pAllTextSymbol = pAllTextSymbol;
}
Display::CTextSymbolPtr CLegend::GetAllTextSymbol()
{
	return m_pAllTextSymbol;
}

void CLegend::SetLayerNameSymbol(Display::CTextSymbolPtr pLayerNameSymbol)
{
	m_pLayerNameSymbol = pLayerNameSymbol;
}
Display::CTextSymbolPtr CLegend::GetLayerNameSymbol()
{
	return m_pLayerNameSymbol;
}

void CLegend::SetHeadingSymbol(Display::CTextSymbolPtr pHeadingSymbol)
{
	m_pHeadingSymbol = pHeadingSymbol;
}
Display::CTextSymbolPtr CLegend::GetHeadingSymbol()
{
	return m_pHeadingSymbol;
}

void CLegend::SetLabelSymbol(Display::CTextSymbolPtr pLabelSymbol)
{
	m_pLabelSymbol = pLabelSymbol;
}
Display::CTextSymbolPtr CLegend::GetLabelSymbol()
{
	return m_pLabelSymbol;
}

void CLegend::SetDescSymbol(Display::CTextSymbolPtr pDescriptionSymbol)
{
	m_pDescriptionSymbol = pDescriptionSymbol;
}
Display::CTextSymbolPtr CLegend::GetDescSymbol()
{
	return m_pDescriptionSymbol;
}

void CLegend::MapSettedEvent()
{
	Carto::CMapPtr pMap = m_pMapFrame->GetMap();
	if(!pMap)
		return;

	Carto::CLayerArray LayerArray = pMap->GetLayers();
	for(int i=0;i< m_vecLegendItems.size(); i++)
		m_vecLegendItems[i]->SetLayer(LayerArray[m_vecLegendItems[i]->GetLayerID()]);
}

void CLegend::MapFrameSettedEvent()
{
	if(!m_pMapFrame)
		return;

	Carto::CMapPtr pMap = m_pMapFrame->GetMap();
	if(!pMap)
		return;

	Carto::CLayerArray LayerArray = pMap->GetLayers();
	for(int i=0;i< m_vecLegendItems.size(); i++)
		m_vecLegendItems[i]->SetLayer(LayerArray[m_vecLegendItems[i]->GetLayerID()]);
}

void CLegend::CallbackMapFrameMapSettedFun(CMapFrame* pMapFram)
{
	if(pMapFram == m_pMapFrame)
		MapFrameSettedEvent();
}

void CLegend::CallbackMapFrameProperChangedFun(CMapFrame* pMapFram)
{
	
}

void CLegend::CallbackMapLayerDeleted(Carto::ILayerPtr pLayer)
{
	for(int i=0;i< m_vecLegendItems.size(); i++)
	{
		ILegendItemPtr pItem = m_vecLegendItems[i];
		if(pLayer == pItem->GetLayer())
			m_vecLegendItems.erase(m_vecLegendItems.begin()+i);
	}
	m_contentChanged = TRUE;
}

}
