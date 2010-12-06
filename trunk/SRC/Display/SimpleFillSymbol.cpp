#include "stdafx.h"
#include "SimpleFillSymbol.h"
#include "CDC.h"
#include "IArchive.h"
////////////////////////////////////////////////////////////////////////////////
//
// ¼òµ¥Ãæ·ûºÅ
//		£º Ìî³ä¼òµ¥ÑÕÉ«£¬¿ÉÒÔ»æÖÆ±ß½çÏß
//
////////////////////////////////////////////////////////////////////////////////
Display::CSimpleFillSymbol::CSimpleFillSymbol()
{
	m_hBrushHandle = NULL;

}
Display::CSimpleFillSymbol::CSimpleFillSymbol(const Display::CSimpleFillSymbol& SimpleFillSymbol)
{
	* this = SimpleFillSymbol;
}
Display::CSimpleFillSymbol::~CSimpleFillSymbol()
{

	ClearDC();

}
Display::CSimpleFillSymbol& Display::CSimpleFillSymbol::operator = (const Display::CSimpleFillSymbol& SimpleFillSymbol)
{


	if( this == &SimpleFillSymbol )
		return *this;

	*(IFillSymbol*)this = *(IFillSymbol*)&SimpleFillSymbol;



}
void Display::CSimpleFillSymbol::Draw(void* pObject)
{


	_ASSERT(pObject != NULL);

	DIS_OBJ_TYPE type =((DIS_POLYGON*)pObject)->type;

	if(type == Dis_Rect)
	{
		DIS_RECT  *pDIS_RECT = (DIS_RECT *)pObject;
		if( !CheckNoColor(m_lColor))
		{
			if( pDIS_RECT == NULL || pDIS_RECT->type != Dis_Rect )
				return;

			m_pDC->DrawAndFillRect( *pDIS_RECT );
		}

		if(m_bOutLine)
		{
			m_OutLineSymbol->SetReadyDraw();
			DrawOutLine( pDIS_RECT );
			SetReadyDraw();
		}
	}
	else if(type==Dis_Circle)
	{
		//»æÖÆÔ²
		DIS_CIRCLE* pCircle =(DIS_CIRCLE*)pObject;

		//Ìî³äÔ²
		if( !CheckNoColor(m_lColor))
		{

			m_pDC->FillCircle( *pCircle );
		}

		if(m_bOutLine)
		{
			m_OutLineSymbol->SetReadyDraw();
			DrawOutLine( pCircle );
			SetReadyDraw();
		}

	}
	else if(type==Dis_Ellipse)
	{
		//»æÖÆÍÖÔ²
		DIS_ELLIPSE* pEllipse =(DIS_ELLIPSE*)pObject;

		//Ìî³äÍÖÔ²
		if( !CheckNoColor(m_lColor))
		{

			DIS_RECT rect;
			rect.left =pEllipse->left;
			rect.right =pEllipse->right;
			rect.top =pEllipse->top;
			rect.bottom =pEllipse->bottom;

			m_pDC->FillEllipse( rect );
		}

		if(m_bOutLine)
		{
			m_OutLineSymbol->SetReadyDraw();
			DrawOutLine( pEllipse );
			SetReadyDraw();
		}


	}
	else if(type==Dis_ArcPolygon)
	{
		DIS_ARCPOLYGON *pArcPolygon =(DIS_ARCPOLYGON*)pObject;

		//Ìî³ä
		if( !CheckNoColor(m_lColor))
		{

			m_pDC->FillArcPolygon( pArcPolygon );
		}

		if(m_bOutLine)
		{
			m_OutLineSymbol->SetReadyDraw();
			DrawOutLine( pArcPolygon );
			SetReadyDraw();
		}
	}
	else
	{
		DIS_POLYGON  *pDIS_POLYGON = (DIS_POLYGON *)pObject;
		if( !CheckNoColor(m_lColor))
		{
			if( pDIS_POLYGON == NULL || pDIS_POLYGON->type != Dis_Polygon )
				return;

			m_pDC->DrawPolygon( *pDIS_POLYGON );
		}

		if(m_bOutLine)
		{
			m_OutLineSymbol->SetReadyDraw();
			DrawOutLine( pDIS_POLYGON );
			SetReadyDraw();
		}
	}


}

SYMBOL_TYPE Display::CSimpleFillSymbol::GetType()
{
	return SIMPLE_FILL_SYMBOL;
}

void Display::CSimpleFillSymbol::SelectDC(Display::CDC * pDC)
{


	ISymbol::SelectDC(pDC);

	BRUSH_STYLE bs;
	bs.lColor = GetFillColor();
	bs.Style = SOLID_BRUSH;

	DISPLAY_HANDLE Brush = m_pDC->CreateBrush( bs );
	m_hBrushHandle = CDisplayCache::AddToDisplayCache( Brush , m_pDC );

	if( m_bOutLine )
		m_OutLineSymbol->SelectDC( pDC );

}

void Display::CSimpleFillSymbol::SetReadyDraw()
{
	//m_pDC->SelectObjInto(m_lBrushID);
	CDisplayCache::UseCache( m_hBrushHandle , this );
	if(m_bOutLine)
		m_OutLineSymbol->SetReadyDraw();
}

void Display::CSimpleFillSymbol::Zoom(float rate)
{
	if (m_OutLineSymbol)
	{
		m_OutLineSymbol->Zoom(rate);
	}
}

void Display::CSimpleFillSymbol::serialization(SYSTEM::IArchive & ar)
{ 
	IFillSymbol::serialization(ar); 
}

void Display::CSimpleFillSymbol::ClearDC()
{
	if( m_hBrushHandle != NULL)
	{
		CDisplayCache::ReleaseCache( m_hBrushHandle );
		m_hBrushHandle = NULL;
	}
	if( m_OutLineSymbol != NULL )
		m_OutLineSymbol->ClearDC();

	IFillSymbol::ClearDC();
}

void Display::CSimpleFillSymbol::OnUnitChanged(SYSTEM::SYS_UNIT_TYPE oldUnit , SYSTEM::SYS_UNIT_TYPE newUnit)
{
	IFillSymbol::OnUnitChanged(oldUnit , newUnit);
}

void Display::CSimpleFillSymbol::OnChangingInSelectDC()
{
	IFillSymbol::OnChangingInSelectDC();
}