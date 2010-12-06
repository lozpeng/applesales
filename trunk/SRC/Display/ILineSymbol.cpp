#include "stdafx.h"
#include "ILineSymbol.h"

Display::ILineSymbol::ILineSymbol()
{
	m_lOffsetX = 0;

	m_lOffsetY = 0;

	m_lLineWidth = 1;

	m_fLineWidth = 0.300000f;
	m_fOffsetX = 0.000000f;
	m_fOffsetY = 0.000000f;

}

Display::ILineSymbol:: ~ILineSymbol()
{
}

Display::ILineSymbol::ILineSymbol(const Display::ILineSymbol& toLineSymbol)
{
	*this = toLineSymbol;	

}

Display::ILineSymbol& Display::ILineSymbol::operator = (const Display::ILineSymbol & toLineSymbol)
{
	m_fLineWidth		=		toLineSymbol.m_fLineWidth;
	m_fOffsetX			=		toLineSymbol.m_fOffsetX;
	m_fOffsetY			=		toLineSymbol.m_fOffsetY;

	*(ISymbol*)this = *(ISymbol*)&toLineSymbol;
	return *this;

}

SYMBOL_TYPE Display::ILineSymbol::GetType()
{
	return LINE_SYMBOL;
}
void Display::ILineSymbol::SetLineWidth(float nWidth)
{

	m_fLineWidth = nWidth;
	if ( m_enumUnit == SYSTEM::SYS_UNIT_PIXEL )
	{
		if ( m_fLineWidth < 1.000000f )
			m_fLineWidth = 1.000000f;
	}
	else
	{
		if ( m_fLineWidth < 0.000001f)
		{
			m_fLineWidth = 0.000001f;
		}
	}


}
float Display::ILineSymbol::GetLineWidth()
{	
	return m_fLineWidth;
}

void Display::ILineSymbol::SetLineColor(unsigned long lColor)
{
	m_lColor = lColor;
}

unsigned long Display::ILineSymbol::GetLineColor()
{
	return m_lColor;
}

void Display::ILineSymbol::SetOffset(float x , float y)
{
	m_fOffsetX = x;
	m_fOffsetY = y;

}
float Display::ILineSymbol::GetOffsetX()
{
	return m_fOffsetX;
}

float Display::ILineSymbol::GetOffsetY()
{
	return m_fOffsetY;
}

void Display::ILineSymbol::Zoom(float rate)				//实现符号缩放
{
	if ( rate < 0.000000f )
	{
		rate = 1.000000f;
	}
	m_fOffsetX = m_fOffsetX * rate;
	m_fOffsetY = m_fOffsetY * rate;

	m_fLineWidth = m_fLineWidth * rate;
}

void Display::ILineSymbol::SetProperties(const char* PropertyName,const _variant_t& PropertyValue)
{
#define SETPROP(inVal,Val,inName,Name,VT) if( stricmp(inName,Name) == 0 ) { Val = (VT)inVal;return; }
#define SETPROP2(Val,Name,VT) SETPROP( PropertyValue , Val , PropertyName , Name , VT )


	/*SETPROP2( m_fLineWidth , "LINEWIDTH" , float );*/
	if( stricmp(PropertyName , "LINEWIDTH") == 0 ) 
	{ 
		/*m_fMarkerSize = OnUnitChange(valUnit , m_enumUnit , (float)PropertyValue);*/
		m_fLineWidth = (float) PropertyValue;
		if ( m_enumUnit == SYSTEM::SYS_UNIT_PIXEL )
		{
			if ( m_fLineWidth < 1.000000f )
				m_fLineWidth = 1.000000f;
		}
		else
		{
			if ( m_fLineWidth < 0.000001f)
			{
				m_fLineWidth = 0.000001f;
			}
		}

		return; 
	}
	SETPROP2( m_fOffsetX , "LINEOFFSETX" , float );
	SETPROP2( m_fOffsetY , "LINEOFFSETY" , float );
	/*SETPROP2( m_lColor ,"LINECOLOR", unsigned long );*/
	if( stricmp(PropertyName , "LINECOLOR") == 0 ) 
	{
		SetColor((unsigned long)PropertyValue);
		return;
	}

	ISymbol::SetProperties(PropertyName , PropertyValue);

}

_variant_t Display::ILineSymbol::GetProperties(const char* PropertyName)
{
	_variant_t vt;
#define GETPROP(inName,Name,Val,T) if( stricmp(inName,Name) == 0 ) { vt = (T)Val;return vt; }
#define GETPROP2(Name,Val,T) GETPROP(PropertyName , Name , Val , T )


	GETPROP2( "LINEWIDTH" , m_fLineWidth , _variant_t );
	GETPROP2( "LINEOFFSETX" , m_fOffsetX , _variant_t );
	GETPROP2( "LINEOFFSETY" , m_fOffsetY , _variant_t );
	GETPROP2( "LINECOLOR" , m_lColor , _variant_t );

	return ISymbol::GetProperties(PropertyName);



}


// 函数名称   : Display::ILineSymbol::DrawLegend
// 描述       : 绘制标签
// 返回值     : void 
// 参数       : DIS_RECT * rect
// 参数       : int nFlag
void Display::ILineSymbol::DrawLegend( DIS_RECT * rect , int nFlag )
{


	DIS_LINE *pline;

	if(nFlag == 0)					//绘直线
	{
		CreateDisplayLine( pline , 2 );

		pline->ps[0].x = rect->left + 2;
		pline->ps[0].y = ( rect->bottom + rect->top )>>1;
		pline->ps[1].x = rect->right - 2;
		pline->ps[1].y = ( rect->bottom + rect->top )>>1;
	}
	else if(nFlag == 1)
	{
		CreateDisplayLine( pline , 4 );

		pline->ps[0].x = rect->left + 2;
		pline->ps[0].y = rect->top + 2;

		long templong = (long)( ( rect->bottom - rect->top ) * 0.4 );
		pline->ps[1].x = rect->left + templong;
		pline->ps[1].y = rect->bottom - 2;
		pline->ps[2].x = rect->right - templong;
		pline->ps[2].y = rect->top + 2;
		pline->ps[3].x = rect->right - 2;
		pline->ps[3].y = rect->bottom - 2;
	}
	else if( nFlag == 2 )
	{
		CreateDisplayLine( pline , 5 );
		pline->ps[0].x = rect->left + 2;
		pline->ps[0].y = rect->top + 2;
		pline->ps[1].x = rect->right - 2;
		pline->ps[1].y = rect->top + 2;
		pline->ps[2].x = rect->right - 2;
		pline->ps[2].y = rect->bottom - 2;
		pline->ps[3].x = rect->left + 2;
		pline->ps[3].y = rect->bottom - 2;
		pline->ps[4].x = rect->left + 2;
		pline->ps[4].y = rect->top + 2;
	}
	else if( nFlag == 3 )
	{
		CreateDisplayLine( pline , 5 );
		pline->ps[0].x = rect->left;
		pline->ps[0].y = rect->top;
		pline->ps[1].x = rect->right-1;
		pline->ps[1].y = rect->top;
		pline->ps[2].x = rect->right-1;
		pline->ps[2].y = rect->bottom-1;
		pline->ps[3].x = rect->left;
		pline->ps[3].y = rect->bottom-1;
		pline->ps[4].x = rect->left;
		pline->ps[4].y = rect->top;
	}

	Draw(pline);
	FreeDisplayObj( pline );


}

void Display::ILineSymbol::Draw(void* pObject)
{

}

void Display::ILineSymbol::serialization(SYSTEM::IArchive & ar)
{ 
	ISymbol::serialization(ar); 

	ar & m_fLineWidth;				 				 
	ar & m_fOffsetX;				 
	ar & m_fOffsetY;	

}

void Display::ILineSymbol::OnUnitChanged(SYSTEM::SYS_UNIT_TYPE oldUnit , SYSTEM::SYS_UNIT_TYPE newUnit)
{
	ISymbol::OnUnitChanged(oldUnit , newUnit);

	m_fLineWidth = UnitChangeTo( oldUnit , newUnit , m_fLineWidth );
	m_fOffsetX = UnitChangeTo( oldUnit , newUnit , m_fOffsetX );
	m_fOffsetY = UnitChangeTo( oldUnit , newUnit , m_fOffsetY );
}

void Display::ILineSymbol::OnChangingInSelectDC()
{
	m_lLineWidth = UnitChange( m_enumUnit , m_fLineWidth );
	m_lOffsetX = UnitChange( m_enumUnit , m_fOffsetX );
	m_lOffsetY = UnitChange( m_enumUnit , m_fOffsetY );
	ISymbol::OnChangingInSelectDC();
}

void Display::ILineSymbol::ClearDC()
{
	ISymbol::ClearDC();
}