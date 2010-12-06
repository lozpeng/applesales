#include "stdafx.h"
#include "SymbolFactory.h"
#include "IFillSymbol.h"
#include "SimpleLineSymbol.h"
#include <math.h>
#include "IArchive.h"
#include "CDC.h"

Display::IFillSymbol::IFillSymbol()
{
	m_lRgnID=0;

	m_bOutLine = TRUE;
	m_OutLineSymbol.reset(new  CSimpleLineSymbol);
	COLORREF rgb = RGB( 255-GetRValue(m_lColor) , 255-GetGValue(m_lColor) , 255-GetBValue(m_lColor) );
	m_OutLineSymbol->SetLineColor( m_lColor );
	m_lColor = rgb;
}

Display::IFillSymbol::~IFillSymbol()
{
}

Display::IFillSymbol::IFillSymbol(const Display::IFillSymbol& FillSymbol)
{
	*this = FillSymbol;	
}

Display::IFillSymbol& Display::IFillSymbol::operator = (const Display::IFillSymbol & FillSymbol)
{


	m_bOutLine	    =			 FillSymbol.m_bOutLine;

	*(ISymbol*)this =			 *(ISymbol*)&FillSymbol;

	m_OutLineSymbol	    =			 FillSymbol.m_OutLineSymbol->Clone();

	return *this;
}

SYMBOL_TYPE Display::IFillSymbol::GetType()
{
	return FILL_SYMBOL;
}
void Display::IFillSymbol::SetOutLineSymbol(ILineSymbolPtr mOutLine)
{
	m_OutLineSymbol = mOutLine;
}
void Display::IFillSymbol::SetFillColor(unsigned long lColor)
{
	m_lColor = lColor;
}

unsigned long Display::IFillSymbol::GetFillColor()
{
	return m_lColor;
}

void Display::IFillSymbol::SetDrawFill(bool bFill)
{
	if(bFill)
		SetColor(SetHasColor);
	else
		SetColor(SetNoColor);
}

bool Display::IFillSymbol::GetDrawFill()
{
	return !CheckNoColor(m_lColor);
}

void Display::IFillSymbol::SetOutLineWidth(float size)
{
	m_OutLineSymbol->SetLineWidth(size);
}

float Display::IFillSymbol::GetOutLineWidth()
{
	return m_OutLineSymbol->GetLineWidth();
}

unsigned long Display::IFillSymbol::GetOutLineColor()
{
	return m_OutLineSymbol->GetLineColor();

}

void Display::IFillSymbol::SetOutLineColor(unsigned long lColor)
{
	m_OutLineSymbol->SetLineColor(lColor);
}

void Display::IFillSymbol::SetDrawOutLine(bool bline)
{
	m_bOutLine = bline;
}

bool Display::IFillSymbol::GetDrawOutLine()
{
	return m_bOutLine;
}


void Display::IFillSymbol::DrawOutLine(DIS_POLYGON *pDIS_POLYGON)
{

	if(m_bOutLine)
	{
		DIS_LINE *pDIS_LINE;
		INT_POINT *pts = pDIS_POLYGON->GetPointAdr();
		for(unsigned int i = 0 ; i < pDIS_POLYGON->Count ; i++ )
		{
			CreateDisplayLine( pDIS_LINE , pDIS_POLYGON->RingCount[i] );

			memcpy( pDIS_LINE->ps , pts , sizeof(INT_POINT)*pDIS_LINE->Count );

			m_OutLineSymbol->Draw( pDIS_LINE );

			FreeDisplayObj( pDIS_LINE );

			pts += pDIS_POLYGON->RingCount[i];
		}
	}

}

void Display::IFillSymbol::DrawOutLine(DIS_RECT *pDIS_RECT)
{

	if(m_bOutLine)
	{
		DIS_LINE *pDIS_LINE;
		INT_POINT pts[5];
		pts[0].x = pDIS_RECT->left; pts[0].y = pDIS_RECT->top;
		pts[1].x = pDIS_RECT->right; pts[1].y = pDIS_RECT->top;
		pts[2].x = pDIS_RECT->right; pts[2].y = pDIS_RECT->bottom;
		pts[3].x = pDIS_RECT->left; pts[3].y = pDIS_RECT->bottom;
		pts[4].x = pDIS_RECT->left; pts[4].y = pDIS_RECT->top;

		CreateDisplayLine( pDIS_LINE , 5);
		memcpy( pDIS_LINE->ps , pts , sizeof(INT_POINT)*5 );
		m_OutLineSymbol->Draw( pDIS_LINE );
		FreeDisplayObj( pDIS_LINE );

	}			

}

void Display::IFillSymbol::DrawOutLine(DIS_CIRCLE *pCircle)
{

	if(m_bOutLine)
	{
		m_OutLineSymbol->GetDC()->DrawCircle(*pCircle);
	}			

}

void Display::IFillSymbol::DrawOutLine(DIS_ELLIPSE *pEllipse)
{

	if(m_bOutLine)
	{
		DIS_RECT rect;
		rect.left = pEllipse->left;
		rect.right = pEllipse->right;
		rect.top = pEllipse->top;
		rect.bottom = pEllipse->bottom;
		m_OutLineSymbol->GetDC()->DrawEllipse(rect);
	}			

}

void Display::IFillSymbol::DrawOutLine(DIS_ARCPOLYGON *pPolygon)
{
	if(m_bOutLine)
	{

		m_OutLineSymbol->GetDC()->DrawArcPolygon(pPolygon);
	}	
}

int Display::IFillSymbol::GetSquare(DIS_RECT * rc)
{
	long p;

	p = rc->right - rc->left;
	p=(int)( sqrt( (float)((rc->right - rc->left) * (rc->right - rc->left) + (rc->bottom - rc->top) * (rc->bottom - rc->top))) + 0.5 );

	INT_POINT dp;
	dp.x = rc->left + ( (rc->right - rc->left) >> 1 );
	dp.y = rc->top + ( (rc->bottom - rc->top) >> 1 );
	rc->left = dp.x - ( p >> 1 ) - 1;
	rc->top = dp.y - ( p >> 1 ) - 1;
	rc->right = dp.x + ( p >> 1 ) + 1;
	rc->bottom = dp.y + ( p >> 1 ) + 1;
	p = ( p >> 1 ) + 1;

	return 1;
}

Display::ILineSymbolPtr Display::IFillSymbol::GetOutLineSymbol()
{
	return m_OutLineSymbol;
}

void Display::IFillSymbol::Zoom(float rate)			//实现符号缩放
{
	if (m_OutLineSymbol != NULL)
	{
		m_OutLineSymbol->Zoom(rate);
	}

}

void Display::IFillSymbol::SetProperties(const char* PropertyName , const _variant_t& PropertyValue)
{
#define SETPROP(inVal,Val,inName,Name,VT) if( stricmp(inName,Name) == 0 ) { Val = (VT)inVal;return; }
#define SETPROP2(Val,Name,VT) SETPROP( PropertyValue , Val , PropertyName , Name , VT )


	SETPROP2( m_bOutLine , "BOutLine" , bool );
	/*SETPROP2( m_lColor , "FillColor" , unsigned long );*/
	if( stricmp(PropertyName , "FillColor") == 0 ) 
	{
		SetColor((unsigned long)PropertyValue);
		return;
	}

	if( stricmp( PropertyName , "OutLine" ) == 0 ) 
	{
		if( PropertyValue.vt == VT_BSTR )
		{
			SYSTEM::CStringArchive ar;
			ar.ImportVariant( PropertyValue);
			ar.SetReadState();

			m_OutLineSymbol = Display::CSymbolFactory::CreateSymbolFromStream(ar);			//本想判断一下返回的符号是否是线符号。暂时不作判断了咧
			return;
		}
		else
		{
			SYSTEM::CBinArchive ar;
			ar.ImportVariant( PropertyValue);
			ar.SetReadState();

			m_OutLineSymbol = Display::CSymbolFactory::CreateSymbolFromStream(ar);
			return;
		}
	}

	ISymbol::SetProperties(PropertyName , PropertyValue);

}

_variant_t Display::IFillSymbol::GetProperties(const char* PropertyName)
{
	_variant_t vt;
#define GETPROP(inName,Name,Val,T) if( stricmp(inName,Name) == 0 ) { vt = (T)Val;return vt; }
#define GETPROP2(Name,Val,T) GETPROP(PropertyName , Name , Val , T )


	GETPROP2( "BOutLine" , m_bOutLine , _variant_t);
	GETPROP2( "FillColor" , m_lColor , unsigned long );

	if( stricmp(PropertyName, "OutLine" ) == 0 )
	{
		SYSTEM::CBinArchive ar;
		ar.SetWriteState();
		m_OutLineSymbol->serialization( ar );
		return ar.ExportToVariant();
	}
	return ISymbol::GetProperties(PropertyName);


	return ISymbol::GetProperties(PropertyName);
}
void Display::IFillSymbol::DrawLegend( DIS_RECT * rect , int nFlag )
{


	DIS_POLYGON  *pDIS_POLYGON;

	CreateDisplayPolygon( pDIS_POLYGON , 1 , 5 );

	pDIS_POLYGON->RingCount[0] = 5;

	INT_POINT *pts = pDIS_POLYGON->GetPointAdr();
	if( nFlag == 1 || nFlag == 0)
	{
		pts[0].x = rect->left + 2;
		pts[0].y = rect->top + 2;
		pts[1].x = rect->right - 3;
		pts[1].y = rect->top + 2;
		pts[2].x = rect->right - 3;
		pts[2].y = rect->bottom - 3;
		pts[3].x = rect->left + 2;
		pts[3].y = rect->bottom - 3;
		pts[4].x = rect->left + 2;
		pts[4].y = rect->top + 2;
	}
	else if( nFlag == 3 )
	{
		pts[0].x = rect->left ;
		pts[0].y = rect->top ;
		pts[1].x = rect->right ;
		pts[1].y = rect->top ;
		pts[2].x = rect->right ;
		pts[2].y = rect->bottom ;
		pts[3].x = rect->left ;
		pts[3].y = rect->bottom ;
		pts[4].x = rect->left ;
		pts[4].y = rect->top ;
	}
	Draw( pDIS_POLYGON );
	FreeDisplayObj( pDIS_POLYGON );

}
void Display::IFillSymbol::Draw(void* pObject)
{

}

void Display::IFillSymbol::serialization(SYSTEM::IArchive & ar)
{ 
	ISymbol::serialization(ar); 

	ar & m_lColor;				 
	ar & m_bOutLine;

	if( ar.IsSave() )
	{
		m_OutLineSymbol->serialization( ar );
	}
	else
	{
		m_OutLineSymbol = CSymbolFactory::CreateSymbolFromStream( ar );
	}
}

void Display::IFillSymbol::OnUnitChanged(SYSTEM::SYS_UNIT_TYPE oldUnit , SYSTEM::SYS_UNIT_TYPE newUnit)
{
	ISymbol::OnUnitChanged(oldUnit , newUnit);
	if ( m_OutLineSymbol != NULL )
	{
		m_OutLineSymbol->SetUnit(newUnit);
	}
}

void Display::IFillSymbol::OnChangingInSelectDC()
{
	ISymbol::OnChangingInSelectDC();
}

void Display::IFillSymbol::ClearDC()
{
	if (m_OutLineSymbol != NULL)
	{
		m_OutLineSymbol->ClearDC();
	}
	ISymbol::ClearDC();
}