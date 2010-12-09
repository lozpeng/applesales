#include "StdAfx.h"
#include "IScaleBar.h"
#include "TextSymbol.h"
#include "DisplayCache.h"
#include "MapFrame.h"
#include "SymbolFactory.h"
#include "ScaleLine.h"
#include "AlternatingScaleBar.h"
#include "EnvelopeTracker.h"
#include <boost/function.hpp>
#include <boost/bind.hpp>

namespace Element{

#define DEFAULT_DIVISION_LEN 10

IScaleBar::IScaleBar()
{
	m_contentChanged = TRUE;

	m_strName = "比例尺";

	m_pSelectionHandle.reset(new CEnvelopeTracker(GEOMETRY::geom::Envelope(0,0,0,0), HT_EIGHT));

	boost::function<void (CMapFrame*)> funmp = boost::bind(&IScaleBar::CallbackMapFrameProperChangedFun,this, _1);

	m_ConnectionMapFrameProperChanged = CMapFrame::RegisterMapFrameProperChanged(funmp);
}

IScaleBar::IScaleBar(const GEOMETRY::geom::Geometry& geometry, CMapFrame* pMapFrame):IMapSurround(geometry, pMapFrame)
{
	m_contentChanged = TRUE;

	m_strName = "比例尺";

	//设置比例尺的尺寸、颜色和形式
	m_pTextSymbol.reset(new Display::CTextSymbol);
	m_pTextSymbol->SetTextPosType(TXTPOS_RIGHTTOP);
	m_pForeSymbol = NULL;
	m_pBackSymbol = NULL;
	m_BarHeight = 2;//mm
	m_DivisionNum = 4;
	m_SubDivisionNum = 2;
	m_DrawDivBeforZero = FALSE;
	m_DivisionLen = 0;
	
	//设置比例尺的单位
	m_Unit = pMapFrame->GetMap()->GetUnit();
	m_UnitLabelGap = 1;//mm	
	m_UnitLabelPos = UP_AFTER_BAR;
	m_UnitTextSymbol.reset(new Display::CTextSymbol);
	m_UnitTextSymbol->SetTextPosType(TXTPOS_RIGHTTOP);

	m_NumLabelGap = 1;//mm
	m_NumLabelFreq = LF_DIVISIONS_FIRST_SUBDIVISION;
	m_NumLabelPos = NP_ABOVE_BAR;
	m_NumTextSymbol.reset(new Display::CTextSymbol);
	m_NumTextSymbol->SetTextPosType(TXTPOS_CENTER);
	
	m_DivisionMarkHeight = 2;//mm
	m_SubDivisionMarkHeight = 1;//mm
	m_MarkFreq = LF_DIVISIONS_FIRST_SUBDIVISION;
	m_MarkPos = MP_ABOVE_BAR;
	m_pMarkLineSymbol.reset(new Display::CSimpleLineSymbol);
	m_pMarkLineSymbol->SetLineColor(RGB(0,0,0));
		
	//设置选择框
	m_pSelectionHandle.reset(new CEnvelopeTracker(GetEnvelope(), HT_EIGHT));

	boost::function<void (CMapFrame*)> funmp = boost::bind(&IScaleBar::CallbackMapFrameProperChangedFun,this, _1);

	m_ConnectionMapFrameProperChanged = CMapFrame::RegisterMapFrameProperChanged(funmp);
}

IScaleBar::~IScaleBar(void)
{
	m_ConnectionMapFrameProperChanged.disconnect();
}

void IScaleBar::serialization(SYSTEM::IArchive &ar)
{
	IMapSurround::serialization( ar );

	ar & m_BarHeight;

	ar & m_DivisionLen;

	ar & m_DivisionNum;

	ar & m_SubDivisionNum;

	ar & m_DrawDivBeforZero;

	ar & m_DivisionMarkHeight;

	ar & m_SubDivisionMarkHeight;

	ar & m_NumLabelGap;

	ar & m_UnitLabelGap;

	if(ar.IsRead())
	{
		m_pTextSymbol = Display::CSymbolFactory::CreateSymbolFromStream(ar);

		m_pForeSymbol = Display::CSymbolFactory::CreateSymbolFromStream(ar);

		m_pBackSymbol = Display::CSymbolFactory::CreateSymbolFromStream(ar);

		m_NumTextSymbol = Display::CSymbolFactory::CreateSymbolFromStream(ar);

		m_UnitTextSymbol = Display::CSymbolFactory::CreateSymbolFromStream(ar);

		int markFreq;
		ar & markFreq;
		m_MarkFreq = (LabelFrequency)markFreq;

		int markPos;
		ar & markPos;
		m_MarkPos = (MarkPosition)markPos;

		m_pMarkLineSymbol = Display::CSymbolFactory::CreateSymbolFromStream(ar);
	
	
		int labelFreq;
		ar & labelFreq;
		m_NumLabelFreq = (LabelFrequency)labelFreq;

		int NumPos;
		ar & NumPos;
		m_NumLabelPos = (NumPosition)NumPos;

		int unit;
		ar & unit;
		m_Unit = (SYSTEM::SYS_UNIT_TYPE)unit;

		int UnitPos;
		ar & UnitPos;
		m_UnitLabelPos = (UnitPosition)UnitPos;
	}
	else
	{
		m_pTextSymbol->serialization(ar);

		m_pForeSymbol->serialization(ar);

		m_pBackSymbol->serialization(ar);

		m_NumTextSymbol->serialization(ar);

		m_UnitTextSymbol->serialization(ar);

		int markFreq = (int)m_MarkFreq;
		ar & markFreq;

		int markPos = (int)m_MarkPos;
		ar & markPos;

		m_pMarkLineSymbol->serialization(ar);


		int labelFreq = (int)m_NumLabelFreq;
		ar & labelFreq;

		int NumPos = (int)m_NumLabelPos;
		ar & NumPos;

		int unit = (int)m_Unit;
		ar & unit;

		int UnitPos = (int)m_UnitLabelPos;
		ar & UnitPos;
	}
}

SYSTEM::CSmartPtr<IScaleBar> IScaleBar::CreateScaleBarFromStream(SYSTEM::IArchive &ar)
{
	unsigned long pos = ar.GetCurrentPos();
	int type;
	ar & type;

	ar.GetCurrentPos() = pos;

	IScaleBarPtr pScaleBar = CreateScaleBar((ELEMENT_TYPE)type);

	if (pScaleBar != NULL)
		pScaleBar->serialization(ar);

	return pScaleBar;	
}

SYSTEM::CSmartPtr<IScaleBar> IScaleBar::CreateScaleBar(ELEMENT_TYPE type)
{
	switch(type)
	{
	case ET_ALTERNATING_SCALEBAR:
		return CAlternatingScaleBarPtr(new CAlternatingScaleBar());
	case ET_SCALELINE:
		return CScaleLinePtr(new CScaleLine());
	default:
		break;
	}
}

void IScaleBar::MoveHandleTo(HIT_HANDLE nHandle,GEOMETRY::geom::Coordinate coord)
{

}
void IScaleBar::UnitChanged(SYSTEM::SYS_UNIT_TYPE newUnit)
{
	m_DivisionLen = SYSTEM::UnitConverter::ConvertUnits(m_DivisionLen, m_Unit, newUnit);
	m_Unit = newUnit;
}

void IScaleBar::DrawNormal(Display::IDisplayPtr pDisplay)
{
	if(m_contentChanged)
		RecalcGeometry(pDisplay);

	DrawBackground(pDisplay);


	ConvertMillimeterToPixel(pDisplay);

	CDisRectSet ScaleBarRectSet;
	CalculateScalebarRectSet(pDisplay, &ScaleBarRectSet);
	DIS_RECT* rect = pDisplay->GetDisplayTransformation().TransformToDisplay(&GetEnvelope());
	ScaleBarRectSet.MoveTo(rect->left, rect->bottom);
	FreeDisplayObj(rect);


	//绘制比例尺及Label
	DrawBar(pDisplay, ScaleBarRectSet.GetRect(0));
	DrawMark(pDisplay, ScaleBarRectSet.GetRect(1));
	DrawNumLabel(pDisplay, ScaleBarRectSet.GetRect(2));
	DrawUnitLabel(pDisplay,ScaleBarRectSet.GetRect(3));

	DrawForeground(pDisplay);
}


void IScaleBar::RecalcGeometry(Display::IDisplayPtr pDisplay)
{
	ConvertMillimeterToPixel(pDisplay);

	CDisRectSet ScaleBarRectSet;
	CalculateScalebarRectSet(pDisplay, &ScaleBarRectSet);

	DIS_RECT* rect = pDisplay->GetDisplayTransformation().TransformToDisplay(&GetEnvelope());
	ScaleBarRectSet.MoveTo(rect->left, rect->bottom);
	FreeDisplayObj(rect);
	
	//
	GEOMETRY::geom::Envelope env;
	pDisplay->GetDisplayTransformation().TransformToGeo(ScaleBarRectSet.GetBound(), &env);
	m_pGeometry = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->toGeometry(&env);
	

	GeometryChangedEvents();

	m_contentChanged = FALSE;
}

void IScaleBar::ConvertMillimeterToPixel(Display::IDisplayPtr pDisplay)
{
	pDisplay->GetDisplayTransformation().MillimeterToDisplay(m_DivisionMarkHeight, m_DivisionMarkHeightPixel);
	pDisplay->GetDisplayTransformation().MillimeterToDisplay(m_BarHeight, m_BarHeightPixel);
	pDisplay->GetDisplayTransformation().MillimeterToDisplay(m_SubDivisionMarkHeight, m_SubDivisionMarkHeightPixel);
	pDisplay->GetDisplayTransformation().MillimeterToDisplay(m_NumLabelGap, m_NumLabelGapPixel);
	pDisplay->GetDisplayTransformation().MillimeterToDisplay(m_UnitLabelGap, m_UnitLabelGapPixel);
}
void IScaleBar::CalculateScalebarRectSet(Display::IDisplayPtr pDisplay, CDisRectSet* pScaleBarRectSet)
{

	DIS_RECT unitRect, numRect, barRect, markRect;	
	barRect = CalcBarSize(pDisplay);
	markRect = CalcMarkSize(pDisplay, barRect);
	numRect = CalcNumSize(pDisplay, barRect);
	unitRect = CalcUnitSize(pDisplay);

	if(m_DivisionLen == 0)
	{
		NormalizeRect(pDisplay, numRect);
		NormalizeRect(pDisplay, barRect);
		NormalizeRect(pDisplay, markRect);
	}
	

	//顺序:Bar,Mark,Num,unit
	AddBarRect(pDisplay, pScaleBarRectSet, barRect);
	AddMarkRect(pDisplay, pScaleBarRectSet, markRect);
	AddNumRect(pDisplay, pScaleBarRectSet, numRect);
	AddUnitRect(pDisplay, pScaleBarRectSet, unitRect);
}

DIS_RECT IScaleBar::CalcUnitSize(Display::IDisplayPtr pDisplay)
{
	std::string strUnitLabel=  SYSTEM::UnitConverter::GetUnitLabelEN(m_Unit);
	DIS_RECT rect = CalculateTextSize(pDisplay, m_UnitTextSymbol, strUnitLabel);
	rect.top = -rect.Height();
	rect.bottom = 0;
	return rect;
}

DIS_RECT IScaleBar::CalcBarSize(Display::IDisplayPtr pDisplay)
{
	DIS_RECT* elementRect = pDisplay->GetDisplayTransformation().TransformToDisplay(&GetEnvelope());
	DIS_RECT unitSize = CalcUnitSize(pDisplay);

	DIS_RECT barRect;
	barRect.top = -m_BarHeightPixel;
	barRect.bottom = 0;
	if(m_DivisionLen == 0)
	{
		double barLenMap;
		long barLenDisplay;
		barLenMap = DEFAULT_DIVISION_LEN*m_pMapFrame->GetMap()->GetMapToPageScale() ;
		barLenMap = SYSTEM::UnitConverter::ConvertUnits(barLenMap, SYSTEM::SYS_UNIT_MILLIMETER, m_pMapFrame->GetMap()->GetUnit());
		m_pMapFrame->GetMap()->GetDisplay()->GetDisplayTransformation().ConvertGeoToDisplay(barLenMap, barLenDisplay);
		barLenDisplay *=m_DivisionNum;
		m_contentChanged = TRUE;
		//计算宽度
		switch(m_UnitLabelPos)
		{
		case UP_BEFORE_BAR:
		case UP_AFTER_BAR:
		case UP_BEFORE_LABELS:
		case UP_AFTER_LABELS:
			barRect.left = 0;
			barRect.right = barLenDisplay;
			break;
		case UP_ABOVE_BAR:
		case UP_BELOW_BAR:
			barRect.left = 0;
			barRect.right = barLenDisplay;
			break;
		}
		
	}
	else
	{
		long barLen = 0;
		double dbDivMapLen = SYSTEM::UnitConverter::ConvertUnits(m_DivisionLen, m_Unit, m_pMapFrame->GetMap()->GetUnit());

		m_pMapFrame->GetMap()->GetDisplay()->GetDisplayTransformation().ConvertGeoToDisplay(dbDivMapLen, barLen);

		barLen*=m_DivisionNum;


		//计算宽度
		switch(m_UnitLabelPos)
		{
		case UP_BEFORE_BAR:
		case UP_AFTER_BAR:
		case UP_BEFORE_LABELS:
		case UP_AFTER_LABELS:
			barRect.left = 0;
			barRect.right = barLen;
			break;
		case UP_ABOVE_BAR:
		case UP_BELOW_BAR:
			barRect.left = 0;
			barRect.right = barLen;
			break;
		}
	}
	
	FreeDisplayObj(elementRect);
	return barRect;
}

DIS_RECT IScaleBar::CalcMarkSize(Display::IDisplayPtr pDisplay, DIS_RECT barRect)
{
	DIS_RECT* elementRect = pDisplay->GetDisplayTransformation().TransformToDisplay(&GetEnvelope());
	DIS_RECT unitSize = CalcUnitSize(pDisplay);
	DIS_RECT markRect;
	markRect.top = -(m_DivisionMarkHeightPixel > m_SubDivisionMarkHeightPixel?m_DivisionMarkHeightPixel:m_SubDivisionMarkHeightPixel);
	markRect.bottom = 0;
	markRect.left = barRect.left;
	markRect.right = barRect.right;


	////计算宽度
	//switch(m_UnitLabelPos)
	//{
	//case UP_BEFORE_BAR:
	//case UP_AFTER_BAR:
	//case UP_BEFORE_LABELS:
	//case UP_AFTER_LABELS:
	//	markRect.left = 0;
	//	markRect.right = elementRect->Width() - unitSize.Width() - m_UnitLabelGapPixel;
	//	break;
	//case UP_ABOVE_BAR:
	//case UP_BELOW_BAR:
	//	markRect.left = 0;
	//	markRect.right = elementRect->Width();
	//	break;
	//}
	FreeDisplayObj(elementRect);
	return markRect;
}

DIS_RECT IScaleBar::CalcNumSize(Display::IDisplayPtr pDisplay, DIS_RECT barRect)
{
	std::string strNumLabel=  SYSTEM::UnitConverter::GetUnitLabelEN(m_Unit);
	DIS_RECT rect = CalculateTextSize(pDisplay, m_NumTextSymbol, strNumLabel);

	rect.top = -rect.Height();
	rect.bottom = 0;
	rect.left = barRect.left;
	rect.right = barRect.right;
	return rect;
}
void IScaleBar::AddBarRect(Display::IDisplayPtr pDisplay, CDisRectSet* pScaleBarRectSet, DIS_RECT barRect)
{
	pScaleBarRectSet->AddRect(barRect);
	pScaleBarRectSet->MoveTo(0,0);
}

void IScaleBar::AddMarkRect(Display::IDisplayPtr pDisplay, CDisRectSet* pScaleBarRectSet, DIS_RECT markRect)
{
	if(m_MarkFreq == LF_NONE)
	{
		markRect.left = markRect.right = pScaleBarRectSet->GetBound().left;
		markRect.top = markRect.bottom = pScaleBarRectSet->GetBound().bottom;
	}
	else
	{
		//计算相对位置
		DIS_RECT barRect = pScaleBarRectSet->GetRect(0);
		float markHeight = markRect.Height();
		switch(m_MarkPos)
		{	
		case MP_ABOVE_BAR:
			{
				markRect.bottom = barRect.top;
				markRect.top = markRect.bottom - markHeight;
			}
			break;
		case MP_BELOW_BAR:
			{
				markRect.top = barRect.bottom;
				markRect.bottom = markRect.top + markHeight;
			}
			break;
		case MP_CENTER_BAR:
			{			
				markRect.bottom = (barRect.top+ barRect.bottom)/2 + markHeight/2;
				markRect.top = markRect.bottom - markHeight;
			}
			break;
		default:
			{
				//MP_ABOVE_BAR
				markRect.bottom = barRect.top;
				markRect.top = markRect.bottom - markHeight;
			}
			break;
		}
	}
	
	pScaleBarRectSet->AddRect(markRect);
	pScaleBarRectSet->MoveTo(0,0);		
}

void IScaleBar::AddNumRect(Display::IDisplayPtr pDisplay, CDisRectSet* pScaleBarRectSet, DIS_RECT numRect)
{
	if(m_NumLabelFreq == LF_NONE)
	{
		numRect.left = numRect.right = pScaleBarRectSet->GetBound().left;
		numRect.top = numRect.bottom = pScaleBarRectSet->GetBound().bottom;
	}
	else
	{
		float numHeight = numRect.Height();
		switch(m_NumLabelPos)
		{
		case NP_ABOVE_BAR:
			{
				numRect.bottom = pScaleBarRectSet->GetBound().top - m_NumLabelGapPixel;
				numRect.top = numRect.bottom - numHeight;
			}
			break;
		case NP_BELOW_BAR:
			{
				numRect.top = pScaleBarRectSet->GetBound().bottom + m_NumLabelGapPixel;
				numRect.bottom = numRect.top + numHeight;
			}
			break;
		default:
			{
				numRect.bottom = pScaleBarRectSet->GetBound().top - m_NumLabelGapPixel;
				numRect.top = numRect.bottom - numHeight;
			}
			break;
		}
	}

	pScaleBarRectSet->AddRect(numRect);
	pScaleBarRectSet->MoveTo(0,0);		
}


void IScaleBar::AddUnitRect(Display::IDisplayPtr pDisplay, CDisRectSet* pScaleBarRectSet, DIS_RECT unitRect)
{
	float unitHeight = unitRect.Height();
	float unitWidth = unitRect.Width();

	switch(m_UnitLabelPos)
	{
	case UP_BEFORE_BAR:
		{
			DIS_RECT barRect = pScaleBarRectSet->GetRect(0);	
			unitRect.bottom = barRect.bottom;
			unitRect.top = unitRect.bottom - unitHeight;
			unitRect.right = pScaleBarRectSet->GetBound().left - m_UnitLabelGapPixel;
			unitRect.left = unitRect.right - unitWidth;
		}
		break;
	case UP_AFTER_BAR:
		{
			DIS_RECT barRect = pScaleBarRectSet->GetRect(0);
			unitRect.bottom = barRect.bottom;
			unitRect.top = unitRect.bottom - unitHeight;
			unitRect.left = pScaleBarRectSet->GetBound().right + m_UnitLabelGapPixel;
			unitRect.right = unitRect.left+unitWidth;
		}
		break;
	case UP_BEFORE_LABELS:
		{
			DIS_RECT numRect = pScaleBarRectSet->GetRect(2);
			float numBottom = numRect.bottom;
			unitRect.bottom = numBottom;
			unitRect.top = unitRect.bottom - unitHeight;
			unitRect.right = pScaleBarRectSet->GetBound().left - m_UnitLabelGapPixel;
			unitRect.left = unitRect.left - unitWidth;
		}
		break;
	case UP_AFTER_LABELS:
		{
			DIS_RECT numRect = pScaleBarRectSet->GetRect(2);
			float numBottom = numRect.bottom;
			unitRect.bottom = numBottom;
			unitRect.top = unitRect.bottom - unitHeight;
			unitRect.left = pScaleBarRectSet->GetBound().right + m_UnitLabelGapPixel;
			unitRect.right = unitRect.left+unitWidth;
		}
		break;
	case UP_ABOVE_BAR:
		{
			float unitHeight = unitRect.Height();
			float unitWidth = unitRect.Width();
			unitRect.bottom = pScaleBarRectSet->GetBound().top - m_UnitLabelGapPixel;
			unitRect.top = unitRect.bottom - unitHeight;
			unitRect.left = (pScaleBarRectSet->GetBound().right + pScaleBarRectSet->GetBound().left)/2 - unitWidth/2;
			unitRect.right = unitRect.left+unitWidth;
		}
		break;
	case UP_BELOW_BAR:
		{
			float unitHeight = unitRect.Height();
			float unitWidth = unitRect.Width();
			unitRect.top = pScaleBarRectSet->GetBound().bottom + m_UnitLabelGapPixel;
			unitRect.bottom = unitRect.top + unitHeight;
			unitRect.left = (pScaleBarRectSet->GetBound().right + pScaleBarRectSet->GetBound().left)/2 - unitWidth/2;
			unitRect.right = unitRect.left+unitWidth;
		}
		break;
	}

	pScaleBarRectSet->AddRect(unitRect);
	pScaleBarRectSet->MoveTo(0,0);		
}

void IScaleBar::DrawMark(Display::IDisplayPtr pDisplay, DIS_RECT rect)
{
	INT_POINT pts_m[2];
	INT_POINT pts_s[2];

	

	switch(m_MarkPos)
	{	
	case MP_ABOVE_BAR:
		{
			pts_m[0].y = rect.bottom;
			pts_m[1].y = rect.bottom - m_DivisionMarkHeightPixel;

			pts_s[0].y = rect.bottom;
			pts_s[1].y = rect.bottom - m_SubDivisionMarkHeightPixel;
		}
		break;
	case MP_BELOW_BAR:
		{
			pts_m[0].y = rect.bottom;
			pts_m[1].y = rect.bottom - m_DivisionMarkHeightPixel;

			pts_s[1].y = rect.top;
			pts_s[0].y = rect.top + m_SubDivisionMarkHeightPixel;
		}
		break;
	case MP_CENTER_BAR:
		{			
			pts_m[0].y = rect.bottom;
			pts_m[1].y = rect.bottom - m_DivisionMarkHeightPixel;

			pts_s[0].y = (rect.bottom+rect.top)/2 + m_SubDivisionMarkHeightPixel/2;
			pts_s[1].y =(rect.bottom+rect.top)/2 - m_SubDivisionMarkHeightPixel/2;;
		}
		break;
	default:
		{
			//MP_ABOVE_BAR
			pts_m[0].y = rect.bottom;
			pts_m[1].y = rect.bottom - m_DivisionMarkHeightPixel;

			pts_s[0].y = rect.bottom;
			pts_s[1].y = rect.bottom - m_SubDivisionMarkHeightPixel;
		}
		break;
	}
	

	
	pDisplay->SetSymbol(m_pMarkLineSymbol.get());
	pDisplay->Begin();

	DIS_LINE* pLine = NULL;
	CreateDisplayLine( pLine , 2);
	switch(m_MarkFreq)
	{
	case LF_NONE:
		break;
	case LF_ONE:
		{
			pts_m[0].x = pts_m[1].x = (rect.left+rect.right)/2;
			memcpy( pLine->ps , pts_m , sizeof(INT_POINT)*2 );
			pDisplay->Draw(pLine);
		}
		break;
	case LF_MAIN_DIVISION:
		{
			for(int i=0; i<m_DivisionNum+1; i++)
			{
				pts_m[0].x = pts_m[1].x = rect.left + i*rect.Width()/(double)m_DivisionNum;;
				memcpy( pLine->ps , pts_m , sizeof(INT_POINT)*2 );
				pDisplay->Draw(pLine);
			}
		}
		break;
	case LF_ALL_DIVISIONS:
		{
			for(int i=0; i<m_DivisionNum+1; i++)
			{
				pts_m[0].x = pts_m[1].x = rect.left + i*rect.Width()/(double)m_DivisionNum;;
				memcpy( pLine->ps , pts_m , sizeof(INT_POINT)*2 );
				pDisplay->Draw(pLine);
			}

			for(int i=1; i<m_SubDivisionNum; i++)
			{
				pts_s[0].x = pts_s[1].x = rect.left + i*rect.Width()/(double)m_DivisionNum/(double)m_SubDivisionNum;
				memcpy( pLine->ps , pts_s , sizeof(INT_POINT)*2 );
				pDisplay->Draw(pLine);
			}
		}
		break;
	case LF_DIVISIONS_FIRST_MIDPOINT:
		{
			for(int i=0; i<m_DivisionNum+1; i++)
			{
				pts_m[0].x = pts_m[1].x = rect.left + i*rect.Width()/(double)m_DivisionNum;;
				memcpy( pLine->ps , pts_m , sizeof(INT_POINT)*2 );
				pDisplay->Draw(pLine);
			}

			pts_s[0].x = pts_s[1].x = rect.left + rect.Width()/(double)m_DivisionNum/2.0;
			memcpy( pLine->ps , pts_s , sizeof(INT_POINT)*2 );
			pDisplay->Draw(pLine);
		}
		break;
	case LF_DIVISIONS_FIRST_SUBDIVISION:
		{
			for(int i=0; i<m_DivisionNum+1; i++)
			{
				pts_m[0].x = pts_m[1].x = rect.left + i*rect.Width()/(double)m_DivisionNum;;
				memcpy( pLine->ps , pts_m , sizeof(INT_POINT)*2 );
				pDisplay->Draw(pLine);
			}

			pts_s[0].x = pts_s[1].x = rect.left + rect.Width()/(double)m_DivisionNum/(double)m_SubDivisionNum;
			memcpy( pLine->ps , pts_s , sizeof(INT_POINT)*2 );
			pDisplay->Draw(pLine);
		}
		break;
	default:
		{
			//LF_DIVISIONS_FIRST_MIDPOINT
			for(int i=0; i<m_DivisionNum+1; i++)
			{
				pts_m[0].x = pts_m[1].x = rect.left + i*rect.Width()/(double)m_DivisionNum;;
				memcpy( pLine->ps , pts_m , sizeof(INT_POINT)*2 );
				pDisplay->Draw(pLine);
			}

			pts_s[0].x = pts_s[1].x = rect.left + rect.Width()/(double)m_DivisionNum/(double)m_SubDivisionNum/2.0;
			memcpy( pLine->ps , pts_s , sizeof(INT_POINT)*2 );
			pDisplay->Draw(pLine);
		}
		break;	
	}

	FreeDisplayObj( pLine );
	pDisplay->End();
}

void IScaleBar::DrawNumLabel(Display::IDisplayPtr pDisplay, DIS_RECT rect)
{
	double number;
	double barLen = m_DivisionLen * m_DivisionNum;
	char cNum[100];
	memset(cNum,0 , 100*sizeof(char));
	DIS_RECT subRect = rect;
	GEOMETRY::geom::Envelope env;
	switch(m_NumLabelFreq)
	{
	case LF_NONE:
		break;
	case LF_ONE:
		{
			number = barLen/2; 
			TransferNumToDisplay(number, cNum);

			subRect.left = rect.left + rect.Width()/2;
			subRect.right = subRect.left;
			DrawText(pDisplay, m_NumTextSymbol, (LPTSTR)cNum, subRect, DT_NOCLIP | DT_NOPREFIX | DT_CENTER | DT_TOP);
		}
		break;
	case LF_MAIN_DIVISION:
		{
			for(int i=0; i<m_DivisionNum+1; i++)
			{
				if(!m_DrawDivBeforZero)
					number = i*m_DivisionLen;
				else
					number = abs((i-1)*m_DivisionLen);
				TransferNumToDisplay(number, cNum);

				subRect.left = rect.left + i*rect.Width()/(double)m_DivisionNum;
				subRect.right = subRect.left;
				DrawText(pDisplay, m_NumTextSymbol, (LPTSTR)cNum, subRect, DT_NOCLIP | DT_NOPREFIX | DT_CENTER | DT_TOP);
			}
		}
		break;
	case LF_ALL_DIVISIONS:
		{
			for(int i=0; i<m_DivisionNum+1; i++)
			{
				if(!m_DrawDivBeforZero)
					number = i*m_DivisionLen;
				else
					number = abs((i-1)*m_DivisionLen);
				TransferNumToDisplay(number, cNum);

				subRect.left = rect.left + i*rect.Width()/(double)m_DivisionNum;
				subRect.right = subRect.left;
				DrawText(pDisplay, m_NumTextSymbol, (LPTSTR)cNum, subRect, DT_NOCLIP | DT_NOPREFIX | DT_CENTER | DT_TOP);
			}

			for(int i=1; i<m_SubDivisionNum; i++)
			{
				if(!m_DrawDivBeforZero)
					number = i*m_DivisionLen/(double)m_SubDivisionNum;
				else
					number = (m_SubDivisionNum-i)*m_DivisionLen/(double)m_SubDivisionNum;
				
				TransferNumToDisplay(number, cNum);

				subRect.left = rect.left + i*rect.Width()/(double)m_DivisionNum/(double)m_SubDivisionNum;
				subRect.right = subRect.left;
				DrawText(pDisplay, m_NumTextSymbol, (LPTSTR)cNum, subRect, DT_NOCLIP | DT_NOPREFIX | DT_CENTER | DT_TOP);
			}
		}
		break;
	case LF_DIVISIONS_FIRST_MIDPOINT:
		{
			for(int i=0; i<m_DivisionNum+1; i++)
			{
				if(!m_DrawDivBeforZero)
					number = abs(i*m_DivisionLen);
				else
					number = abs((i-1)*m_DivisionLen);
				TransferNumToDisplay(number, cNum);

				subRect.left = rect.left + i*rect.Width()/(double)m_DivisionNum;
				subRect.right = subRect.left;
				DrawText(pDisplay, m_NumTextSymbol,(LPTSTR)cNum, subRect, DT_NOCLIP | DT_NOPREFIX | DT_CENTER | DT_TOP);
			}

			number = m_DivisionLen/2.0;
			TransferNumToDisplay(number, cNum);

			subRect.left = rect.left + rect.Width()/(double)m_DivisionNum/2.0;
			subRect.right = subRect.left;
			DrawText(pDisplay, m_NumTextSymbol, (LPTSTR)cNum, subRect, DT_NOCLIP | DT_NOPREFIX | DT_CENTER | DT_TOP);
		}
		break;
	case LF_DIVISIONS_FIRST_SUBDIVISION:
		{
			for(int i=0; i<m_DivisionNum+1; i++)
			{
				if(!m_DrawDivBeforZero)
					number = abs(i*m_DivisionLen);
				else
					number = abs((i-1)*m_DivisionLen);
				TransferNumToDisplay(number, cNum);

				subRect.left = rect.left + i*rect.Width()/(double)m_DivisionNum;
				subRect.right = subRect.left;
				DrawText(pDisplay, m_NumTextSymbol, (LPTSTR)cNum, subRect, DT_NOCLIP | DT_NOPREFIX | DT_CENTER | DT_TOP);
			}

			if(!m_DrawDivBeforZero)
				number = m_DivisionLen/(double)m_SubDivisionNum;
			else
				number = m_DivisionLen - m_DivisionLen/(double)m_SubDivisionNum;

			TransferNumToDisplay(number, cNum);

			subRect.left = rect.left + rect.Width()/(double)m_DivisionNum/(double)m_SubDivisionNum;
			subRect.right = subRect.left;
			DrawText(pDisplay, m_NumTextSymbol, (LPTSTR)cNum, subRect, DT_NOCLIP | DT_NOPREFIX | DT_CENTER | DT_TOP);
		}
		break;
	default:
		{
			//LF_DIVISIONS_FIRST_MIDPOINT
			for(int i=0; i<m_DivisionNum+1; i++)
			{
				if(!m_DrawDivBeforZero)
					number = abs(i*m_DivisionLen);
				else
					number = abs((i-1)*m_DivisionLen);
				TransferNumToDisplay(number, cNum);

				subRect.left = rect.left + i*rect.Width()/(double)m_DivisionNum;
				subRect.right = subRect.left;
				DrawText(pDisplay, m_NumTextSymbol, (LPTSTR)cNum, subRect, DT_NOCLIP | DT_NOPREFIX | DT_CENTER | DT_TOP);
			}

			number = m_DivisionLen/2.0;
			TransferNumToDisplay(number, cNum);

			subRect.left = rect.left + rect.Width()/(double)m_DivisionNum/2.0;
			subRect.right = subRect.left;
			DrawText(pDisplay, m_NumTextSymbol, (LPTSTR)cNum, subRect, DT_NOCLIP | DT_NOPREFIX | DT_CENTER | DT_TOP);
		}
		break;	
	}
}

void IScaleBar::DrawUnitLabel(Display::IDisplayPtr pDisplay, DIS_RECT rect)
{
	std::string strUnitLabel =  SYSTEM::UnitConverter::GetUnitLabelEN(m_Unit);
	DrawText(pDisplay, m_UnitTextSymbol, (LPTSTR)strUnitLabel.c_str(), rect, DT_NOCLIP | DT_NOPREFIX | DT_LEFT | DT_TOP);
}

//////////////////////////////////////////////////////////////////////////
DIS_RECT IScaleBar::CalculateTextSize(Display::IDisplayPtr pDisplay, Display::CTextSymbolPtr pTextSymbol, std::string text)
{
	DIS_RECT textSize;
	textSize.left = 0; textSize.right = 1;
	textSize.top = 0; textSize.bottom = 1;

	pDisplay->SetSymbol(pTextSymbol.get());

	pDisplay->Begin();

	textSize = pDisplay->Draw(&textSize, text, TRUE, DT_CALCRECT | DT_NOCLIP | DT_NOPREFIX | DT_LEFT | DT_TOP);

	pDisplay->End();

	return textSize;
}

void IScaleBar::DrawText(Display::IDisplayPtr pDisplay, Display::CTextSymbolPtr pTextSymbol, std::string text, DIS_RECT rect, unsigned int dwDTFormat)
{
	pDisplay->SetSymbol(pTextSymbol.get());

	pDisplay->Begin();

	pDisplay->Draw(&rect, text, TRUE, dwDTFormat);

	pDisplay->End();

}

void IScaleBar::NormalizeRect(Display::IDisplayPtr pDisplay, DIS_RECT& rect)
{
	//计算主分段在scalebar单位下的长度
	if(m_DivisionLen !=0 )
		return;

	double dbDivMapLen, dbDivBarLen;
	m_pMapFrame->GetMap()->GetDisplay()->GetDisplayTransformation().ConvertDisplayToGeo(rect.Width(), dbDivMapLen);
	dbDivBarLen = SYSTEM::UnitConverter::ConvertUnits(dbDivMapLen, m_pMapFrame->GetMap()->GetUnit(), m_Unit)/(double)m_DivisionNum;

	//长度保留两位有效数字
	int exp = log10(dbDivBarLen);
	m_DivisionLen = long(dbDivBarLen/pow(10.0, (double)(exp-1))) * pow(10.0, (double)(exp-1));

	//更新rect
	long nWidth;
	dbDivMapLen = SYSTEM::UnitConverter::ConvertUnits(m_DivisionLen*m_DivisionNum, m_Unit, m_pMapFrame->GetMap()->GetUnit());
	m_pMapFrame->GetMap()->GetDisplay()->GetDisplayTransformation().ConvertGeoToDisplay(dbDivMapLen, nWidth);
	rect.right = rect.left + nWidth;
}

void IScaleBar::TransferNumToDisplay(double number, char* cNum)
{
	//长度保留两位有效数字
	if(abs(number) < 0.000001)
	{
		sprintf(cNum, "%d", 0 );
		return;
	}

	int exp = log10(number);
	if(exp>0)
	{
		sprintf(cNum, "%d", (long)number );
	}	
	else
	{
		switch(exp)
		{
		case 0:
			sprintf(cNum, "%.1f", number );
			break;
		case -1:
			sprintf(cNum, "%.2f", number );
			break;
		case 2:
			sprintf(cNum, "%.3f", number );
			break;
		case 3:
			sprintf(cNum, "%.4f", number );
			break;
		case 4:
			sprintf(cNum, "%.5f", number );
			break;
		case 5:
			sprintf(cNum, "%.6f", number );
			break;
		case 6:
			sprintf(cNum, "%.7f", number );
			break;
		case 7:
			sprintf(cNum, "%.8f", number );
			break;
		case 8:
			sprintf(cNum, "%.9f", number );
			break;
		default:
			sprintf(cNum, "%.1f", number );
			break;
		}
	}
}

////属性编辑//////////////////////////////////////////////////////////////////////
//bar
void IScaleBar::SetTextSymbol(Display::CTextSymbolPtr pTextSymbol)
{
	m_pTextSymbol = pTextSymbol; 
	m_NumTextSymbol = pTextSymbol->Clone();
	m_UnitTextSymbol = pTextSymbol->Clone();
	m_contentChanged = TRUE;
}
Display::CTextSymbolPtr IScaleBar::GetTextSymbol()
{
	return m_pTextSymbol;
}

void IScaleBar::SetForeSymbol(Display::ISymbolPtr pBarSymbol)
{
	m_pForeSymbol = pBarSymbol; 
	m_contentChanged = TRUE;
}
Display::ISymbolPtr IScaleBar::GetForeSymbol()
{
	return m_pForeSymbol;
}

void IScaleBar::SetBackSymbol(Display::ISymbolPtr pBarSymbol)
{
	m_pBackSymbol = pBarSymbol; 
	m_contentChanged = TRUE;
}
Display::ISymbolPtr IScaleBar::GetBackSymbol()
{
	return m_pBackSymbol;
}

void IScaleBar::SetDivisionLen(double len)
{
	m_DivisionLen = len;
	m_contentChanged = TRUE;
}

double IScaleBar::GetDivisionLen()
{
	return m_DivisionLen;
}


void IScaleBar::SetDivisionNum(int num)
{
	m_DivisionNum = num;
	m_contentChanged = TRUE;
}


int IScaleBar:: GetDivisionNum()
{
	return m_DivisionNum;
}


void IScaleBar::SetSubDivisionNum(int num)
{
	m_SubDivisionNum = num;
	m_contentChanged = TRUE;
}

int IScaleBar::GetSubDivisionNum()
{
	return m_SubDivisionNum;
}


void IScaleBar::SetDrawDivisionBeforZero(BOOL isDraw)
{
	m_DrawDivBeforZero = isDraw;
	m_contentChanged = TRUE;
}

BOOL IScaleBar::GetDrawDivisionBeforZero()
{
	return m_DrawDivBeforZero;
}


//mark
void IScaleBar::SetDivMarkHeight(double markHeight)
{
	m_DivisionMarkHeight = markHeight;
	m_contentChanged = TRUE;
}

double IScaleBar::GetDivMarkHeight()
{
	return m_DivisionMarkHeight;
}


void IScaleBar::SetSubDivMarkHeight(double markHeight)
{
	m_SubDivisionMarkHeight = markHeight;
	m_contentChanged = TRUE;
}

double IScaleBar::GetSubDivMarkHeight()
{
	return m_SubDivisionMarkHeight;
}


void IScaleBar::SetMarkPos(MarkPosition pos)
{
	m_MarkPos = pos;
	m_contentChanged = TRUE;
}

MarkPosition IScaleBar::GetMarkPos()
{
	return m_MarkPos;
}


void IScaleBar::SetMarkFreq(LabelFrequency freq)
{
	m_MarkFreq = freq;
	m_contentChanged = TRUE;
}

LabelFrequency IScaleBar::GetMarkFreq()
{
	return m_MarkFreq;
}


void IScaleBar::SetMarkLineSymbol(Display::ILineSymbolPtr pLineSymbol)
{
	m_pMarkLineSymbol = pLineSymbol;
	m_contentChanged = TRUE;
}

Display::ILineSymbolPtr IScaleBar::GetMarkLineSymbol()
{
	return m_pMarkLineSymbol;
}


//num label
void IScaleBar::SetNumGap(double gap)
{
	m_NumLabelGap = gap;
	m_contentChanged = TRUE;
}

double IScaleBar::GetNumGap()
{
	return m_NumLabelGap;
}


void IScaleBar::SetNumFreq(LabelFrequency freq)
{
	m_NumLabelFreq = freq;
	m_contentChanged = TRUE;
}

LabelFrequency IScaleBar::GetNumFreq()
{
	return m_NumLabelFreq;
}

void IScaleBar::SetNumPos(NumPosition pos)
{
	m_NumLabelPos = pos;
	m_contentChanged = TRUE;
}

NumPosition IScaleBar::GetNumPos()
{
	return m_NumLabelPos;
}


void IScaleBar::SetNumTextSymbol(Display::CTextSymbolPtr pSymbol)
{
	m_NumTextSymbol = pSymbol;
	m_contentChanged = TRUE;
}

Display::CTextSymbolPtr IScaleBar::GetNumTextSymbol()
{
	return m_NumTextSymbol;
}


//unit
void IScaleBar::SetUnit(SYSTEM::SYS_UNIT_TYPE unit)
{
	if(m_Unit == unit)
		return;

	m_DivisionLen = SYSTEM::UnitConverter::ConvertUnits(m_DivisionLen, m_Unit,unit);

	m_Unit = unit;

	m_contentChanged = TRUE;
}
SYSTEM::SYS_UNIT_TYPE	IScaleBar::GetUnit()
{
	return m_Unit;
}

void IScaleBar::SetUnitGap(double gap)
{
	m_UnitLabelGap = gap;
	m_contentChanged = TRUE;
}

double IScaleBar::GetUnitGap()
{
	return m_UnitLabelGap;
}


void IScaleBar::SetUnitPos(UnitPosition pos)
{
	m_UnitLabelPos = pos;
	m_contentChanged = TRUE;
}

UnitPosition IScaleBar::GetUnitPos()
{
	return m_UnitLabelPos;
}


void IScaleBar::SetUnitTextSymbol(Display::CTextSymbolPtr pSymbol)
{
	m_UnitTextSymbol = pSymbol;
	m_contentChanged = TRUE;
}

Display::CTextSymbolPtr IScaleBar::GetUnitTextSymbol()
{
	return m_UnitTextSymbol;
}

void IScaleBar::CallbackMapFrameProperChangedFun(CMapFrame* pMapFram)
{
	if(pMapFram != m_pMapFrame)
		return;

	m_contentChanged = TRUE;
}

}
