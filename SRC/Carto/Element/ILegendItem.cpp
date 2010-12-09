#include "StdAfx.h"
#include "ILegendItem.h"
#include "HorizontalLegendItem.h"
#include "SymbolFactory.h"

namespace Element{

ILegendItem::ILegendItem()
{
	m_pLayer = NULL;
	m_pHeadingSymbol = NULL;
	m_pLayerNameSymbol = NULL;
	m_pLabelSymbol = NULL;
	m_pDescriptionSymbol = NULL;

}

ILegendItem::ILegendItem(Carto::ILayerPtr	pLayer)
{
	m_pLayer = pLayer;

	m_bRightToLeft = FALSE;

	m_bStartCol = FALSE;

	m_bCanDisplay = FALSE;	//是否可视
	m_nColumns = 1;		//item的列数
	m_nHeight = 6;		//item的高度（points）
	m_nWidth = 12;		//item的宽度（points）

	m_LayerNameAndGroup = 1;
	m_HeadingAndClasses = 1;
	m_ClassesSpaces = 2;
	m_PatchAndOther = 2;
	m_LabelAndOther = 2;

	m_itemStyle = LIS_H_SYM_LAYERNAME;	//item的显示风格

	m_patchWidth = 5;
	m_patchHeight = 5;
	m_patchLineStyle = LSLS_HORIZONTAL;	//线符号patch的显示样式
	m_patchAreaStyle = FSLS_RECT;		//面符号patch的显示样式
	m_patchMarkerStyle = MSLS_SIMPLE;	//点符号patch的显示样式

	m_bShowHeading = TRUE;
	m_bShowLayerName = TRUE;
	m_bShowLabels = TRUE;
	m_bShowDescriptions = TRUE;

	m_pHeadingSymbol.reset(new Display::CTextSymbol);	
	m_pLayerNameSymbol.reset(new Display::CTextSymbol);
	m_pLabelSymbol.reset(new Display::CTextSymbol);
	m_pDescriptionSymbol.reset(new Display::CTextSymbol);

	m_pHeadingSymbol->SetTextPosType(TXTPOS_RIGHTTOP);
	m_pLayerNameSymbol->SetTextPosType(TXTPOS_RIGHTTOP);
	m_pLabelSymbol->SetTextPosType(TXTPOS_RIGHTTOP);
	m_pDescriptionSymbol->SetTextPosType(TXTPOS_RIGHTTOP);
}

ILegendItem::~ILegendItem(void)
{
}

void ILegendItem::serialization(SYSTEM::IArchive &ar)
{
	SYSTEM::ISerialization::serialization(ar);

	ar & m_bRightToLeft;
	
	ar & m_bStartCol;

	ar & m_bCanDisplay;

	ar & m_nColumns;

	ar & m_nHeight;

	ar & m_nWidth;

	ar & m_LayerNameAndGroup;

	ar & m_HeadingAndClasses;

	ar & m_ClassesSpaces;

	ar & m_PatchAndOther;

	ar & m_LabelAndOther;

	ar & m_bShowHeading;

	ar & m_bShowLayerName;

	ar & m_bShowLabels;

	ar & m_bShowDescriptions;

	ar & m_patchWidth;

	ar & m_patchHeight;

	if(ar.IsRead())
	{
		int val;
		
		ar & val;
		m_type = (Legend_Item_Type)val;

		ar & val;
		m_itemStyle = (LegendItemStyle)val;

		ar & val;
		m_patchLineStyle = (LineSymbolLegendStyle)val;

		ar & val;
		m_patchAreaStyle = (FillSymbolLegendStyle)val;

		ar & val;
		m_patchMarkerStyle = (MarkerSymbolLegendStyle)val;

		m_pLayerNameSymbol = Display::CSymbolFactory::CreateSymbolFromStream(ar);

		m_pHeadingSymbol = Display::CSymbolFactory::CreateSymbolFromStream(ar);

		m_pLabelSymbol = Display::CSymbolFactory::CreateSymbolFromStream(ar);

		m_pDescriptionSymbol = Display::CSymbolFactory::CreateSymbolFromStream(ar);
	}
	else
	{
		int val;

		val = m_type;
		ar & val;

		val = m_itemStyle;
		ar & val;

		val = m_patchLineStyle;
		ar & val;

		val = m_patchAreaStyle;
		ar & val;

		val = m_patchMarkerStyle;
		ar & val;

		m_pLayerNameSymbol->serialization(ar);

		m_pHeadingSymbol->serialization(ar);

		m_pLabelSymbol->serialization(ar);

		m_pDescriptionSymbol->serialization(ar);
	}

}
SYSTEM::CSmartPtr<ILegendItem> ILegendItem::CreateLegendItemFromStream(SYSTEM::IArchive &ar)
{
	unsigned long pos = ar.GetCurrentPos();
	long type;
	ar & type;
	ar.GetCurrentPos() = pos;

	ILegendItemPtr pLegendItem = CreateLegendItem((Legend_Item_Type)type);

	if (pLegendItem != NULL)
		pLegendItem->serialization(ar);

	return pLegendItem;
}

SYSTEM::CSmartPtr<ILegendItem> ILegendItem::CreateLegendItem(Legend_Item_Type type)
{
	switch(type)
	{
	case LIT_HORIZONTAL:
		return CHorizontalLegendItemPtr(new CHorizontalLegendItem);
	case LIT_VERTICAL:
		return NULL;
	default:
		return NULL;
	}
}

void ILegendItem::Draw(Display::IDisplayPtr pDisplay, DIS_RECT& rect)
{
	ConvertPointToDisplay(pDisplay);

}

void ILegendItem::ConvertPointToDisplay(Display::IDisplayPtr pDisplay)
{
	pDisplay->GetDisplayTransformation().MillimeterToDisplay(m_nHeight, m_lHeightPixel);

	pDisplay->GetDisplayTransformation().MillimeterToDisplay(m_nWidth, m_lWidthPixel);

	pDisplay->GetDisplayTransformation().MillimeterToDisplay(m_LayerNameAndGroup, m_LayerNameAndGroupPixel);

	pDisplay->GetDisplayTransformation().MillimeterToDisplay(m_HeadingAndClasses, m_HeadingAndClassesPixel);

	pDisplay->GetDisplayTransformation().MillimeterToDisplay(m_ClassesSpaces, m_ClassesSpacesPixel);

	pDisplay->GetDisplayTransformation().MillimeterToDisplay(m_PatchAndOther, m_PatchAndOtherPixel);

	pDisplay->GetDisplayTransformation().MillimeterToDisplay(m_LabelAndOther, m_LabelAndOtherPixel);

	pDisplay->GetDisplayTransformation().MillimeterToDisplay(m_patchWidth, m_patchWidthPixel);

	pDisplay->GetDisplayTransformation().MillimeterToDisplay(m_patchHeight, m_patchHeightPixel);
}

void ILegendItem::SetLayer(Carto::ILayerPtr pLayer)
{
	m_pLayer = pLayer;
}

void ILegendItem::SetLayerID(long lID)
{
	m_LayerID = lID;
}

long ILegendItem::GetLayerID()
{
	return m_LayerID;
}


DIS_RECT ILegendItem::GetPatchSize()
{
	DIS_RECT rect;
	rect.left = rect.top = 0;
	rect.right = m_lWidthPixel;
	rect.bottom = m_lHeightPixel;
	return rect;
}


DIS_RECT ILegendItem::GetTextSize(Display::IDisplayPtr pDisplay, Display::CTextSymbolPtr pTextSymbol, std::string text)
{
	GEOMETRY::geom::Envelope env(0,0,1,1);

	DIS_RECT textSize;

	pDisplay->SetSymbol(pTextSymbol.get());

	pDisplay->Begin();

	textSize = pDisplay->Draw(&env, text, TRUE, DT_CALCRECT | DT_NOCLIP | DT_NOPREFIX | DT_LEFT | DT_TOP);

	pDisplay->End();

	return textSize;
}

void ILegendItem::DrawText(Display::IDisplayPtr pDisplay, Display::CTextSymbolPtr pTextSymbol, DIS_RECT& rect, std::string text, unsigned int dwDTFormat)
{
	GEOMETRY::geom::Envelope env;
	pDisplay->GetDisplayTransformation().TransformToGeo(rect, &env);

	pDisplay->SetSymbol(pTextSymbol.get());

	pDisplay->Begin();

	pDisplay->Draw(&env, text, TRUE, dwDTFormat);

	pDisplay->End();

}

void ILegendItem::SetReadDirection(BOOL bRightToLeft)
{
	m_bRightToLeft = bRightToLeft;
}
BOOL ILegendItem::GetReadDirection()
{
	return m_bRightToLeft;
}

void ILegendItem::SetPatchWidth(float fWidth)
{
	m_patchWidth = fWidth;
}
float ILegendItem::GetPatchWidth()
{
	return m_patchWidth;
}

void ILegendItem::SetPatchHeight(float fHeight)
{
	m_patchHeight = fHeight;
}
float ILegendItem::GetPatchHeight()
{
	return m_patchHeight;
}

void ILegendItem::SetPatchMarkerSymbolStyle(MarkerSymbolLegendStyle markerStyle)
{
	m_patchMarkerStyle = markerStyle;
}
MarkerSymbolLegendStyle ILegendItem::GetPatchMarkerSymbolStyle()
{
	return m_patchMarkerStyle;
}

void ILegendItem::SetPatchLineSymbolStyle(LineSymbolLegendStyle lineStyle)
{
	m_patchLineStyle = lineStyle;
}
LineSymbolLegendStyle ILegendItem::GetPatchLineSymbolStyle()
{
	return m_patchLineStyle;
}

void ILegendItem::SetPatchAreaSymbolStyle(FillSymbolLegendStyle areaStyle)
{
	m_patchAreaStyle = areaStyle;
}
FillSymbolLegendStyle ILegendItem::GetPatchAreaSymbolStyle()
{
	return m_patchAreaStyle;
}

void ILegendItem::SetLayerNameAndGroup(float fSpace)
{
	m_LayerNameAndGroup = fSpace;
}
float ILegendItem::GetLayerNameAndGroup()
{
	return m_LayerNameAndGroup;
}

void ILegendItem::SetHeadingAndClasses(float fSpace)
{
	m_HeadingAndClasses = fSpace;
}
float ILegendItem::GetHeadingAndClasses()
{
	return m_HeadingAndClasses;
}

void ILegendItem::SetClassesSpace(float fSpace)
{
	m_ClassesSpaces = fSpace;
}
float ILegendItem::GetClassesSpace()
{
	return m_ClassesSpaces;
}

void ILegendItem::SetPatchAndOther(float fSpace)
{
	m_PatchAndOther = fSpace;
}
float ILegendItem::GetPatchAndOther()
{
	return m_PatchAndOther;
}

void ILegendItem::SetLabelAndOther(float fSpace)
{
	m_LabelAndOther = fSpace;
}
float ILegendItem::GetLabelAndOther()
{
	return m_LabelAndOther;
}

void ILegendItem::SetLayerNameSymbol(Display::CTextSymbolPtr pLayerNameSymbol)
{
	m_pLayerNameSymbol = pLayerNameSymbol;
}
Display::CTextSymbolPtr ILegendItem::GetLayerNameSymbol()
{
	return m_pLayerNameSymbol;
}

void ILegendItem::SetHeadingSymbol(Display::CTextSymbolPtr pHeadingSymbol)
{
	m_pHeadingSymbol = pHeadingSymbol;
}
Display::CTextSymbolPtr ILegendItem::GetHeadingSymbol()
{
	return m_pHeadingSymbol;
}

void ILegendItem::SetLabelSymbol(Display::CTextSymbolPtr pLabelSymbol)
{
	m_pLabelSymbol = pLabelSymbol;
}
Display::CTextSymbolPtr ILegendItem::GetLabelSymbol()
{
	return m_pLabelSymbol;
}

void ILegendItem::SetDescSymbol(Display::CTextSymbolPtr pDescriptionSymbol)
{
	m_pDescriptionSymbol = pDescriptionSymbol;
}
Display::CTextSymbolPtr ILegendItem::GetDescSymbol()
{
	return m_pDescriptionSymbol;
}



}
