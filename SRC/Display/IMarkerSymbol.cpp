#include "stdafx.h"
#include "ISymbol.h"
#include "IMarkerSymbol.h"
#include "IArchive.h"
#include "CDC.h"

Display::IMarkerSymbol::IMarkerSymbol()
{


	m_lOffsetX = 0;							//设置偏移量初始值为0

	m_lOffsetY = 0;

	m_fAngle = 0.0f;						//设置默认角度为0

	m_lMarkerSize = 4;						//设置符号默认大小为10;

	m_bMask = false;						//设置默认是否绘制外围轮廓，默认false

	m_pSymbolMask = 0;						//初始化外围轮廓指针

	m_fMarkerSize = 7.0f;
	m_fOffsetX = 0.0000000f;
	m_fOffsetY = 0.0000000f;


}

Display::IMarkerSymbol:: ~IMarkerSymbol()
{

}

Display::IMarkerSymbol::IMarkerSymbol(const Display::IMarkerSymbol& toMarkSymbol)
{

	*this = toMarkSymbol;	

}

Display::IMarkerSymbol& Display::IMarkerSymbol::operator = (const Display::IMarkerSymbol & toMarkSymbol)
{

	this->m_bMask			=		toMarkSymbol.m_bMask;
	this->m_fAngle			=		toMarkSymbol.m_fAngle;			
	this->m_fMarkerSize		=		toMarkSymbol.m_fMarkerSize;
	this->m_fOffsetX		=		toMarkSymbol.m_fOffsetX;
	this->m_fOffsetY		=		toMarkSymbol.m_fOffsetY;

	*(ISymbol*)this = *(ISymbol*)&toMarkSymbol;
	return *this;
}

SYMBOL_TYPE Display::IMarkerSymbol::GetType()
{
	return MARKER_SYMBOL;
}
void Display::IMarkerSymbol::SetOffSet(float x , float y)
{

	m_fOffsetX = x;
	m_fOffsetY = y;

}
float Display::IMarkerSymbol::GetOffsetX()
{
	return m_fOffsetX;
}
float Display::IMarkerSymbol::GetOffsetY()
{
	return m_fOffsetY;
}
void Display::IMarkerSymbol::SetAngle(float fAngle)
{	


	m_fAngle = fAngle;

}
float Display::IMarkerSymbol::GetAngle()
{
	return m_fAngle;
}

void Display::IMarkerSymbol::SetMarkerSize(float marksize)
{


	m_fMarkerSize = marksize;

	if ( m_enumUnit == SYSTEM::SYS_UNIT_PIXEL )
	{
		if ( m_fMarkerSize < 1.000000f )
			m_fMarkerSize = 1.000000f;
	}
	else
	{
		if ( m_fMarkerSize < 0.000001f)
		{
			m_fMarkerSize = 0.000001f;
		}
	}


}
float Display::IMarkerSymbol::GetMarkerSize()
{
	return m_fMarkerSize;
}

void Display::IMarkerSymbol::SetMaskDrawable(bool bMask)
{


	m_bMask = bMask;

}

bool Display::IMarkerSymbol::GetMaskDrawable()
{
	return m_bMask;
}
void Display::IMarkerSymbol::SetMask(ISymbolPtr pSymbolMask)
{


	if(!pSymbolMask)
	{

	}

	m_pSymbolMask = pSymbolMask;

}

Display::ISymbolPtr Display::IMarkerSymbol::GetMask()
{
	if(!m_bMask)
		return NULL;
	else
		return m_pSymbolMask;
}

void Display::IMarkerSymbol::SetMarkerColor(unsigned long lColor)
{
	m_lColor = lColor;
}

unsigned long Display::IMarkerSymbol::GetMarkColor()
{
	return m_lColor;
}	

void Display::IMarkerSymbol::Zoom(float rate)			//实现符号缩放
{
	if ( rate < 0.000000f )
	{
		rate = 1.000000f;
	}
	m_fOffsetX = m_fOffsetX * rate;
	m_fOffsetY = m_fOffsetY * rate;

	m_fMarkerSize = m_fMarkerSize * rate;

}

void Display::IMarkerSymbol::SetProperties(const char* PropertyName,const _variant_t& PropertyValue)
{
#define SETPROP(inVal,Val,inName,Name,VT) if( stricmp(inName,Name) == 0 ) { Val = (VT)inVal;return; }
#define SETPROP2(Val,Name,VT) SETPROP( PropertyValue , Val , PropertyName , Name , VT )



	SETPROP2( m_fOffsetX , "MARKOFFSETX" , float );
	SETPROP2( m_fOffsetY , "MARKOFFSETY" , float );
	SETPROP2( m_fAngle , "MARKANGLE" , float );
	/*	SETPROP2( m_fMarkerSize , "MARKSIZE" , float );*/
	SETPROP2( m_bMask , "MASKDRAWABLE" , bool );
	//	SETPROP2( m_lColor , "MARKCOLOR" , unsigned long );
	if( stricmp(PropertyName , "MARKCOLOR") == 0 ) 
	{
		SetColor((unsigned long)PropertyValue);
		return;
	}

	if( stricmp(PropertyName , "MARKSIZE") == 0 ) 
	{ 
		/*m_fMarkerSize = OnUnitChange(valUnit , m_enumUnit , (float)PropertyValue);*/
		m_fMarkerSize = (float) PropertyValue;
		if ( m_enumUnit == SYSTEM::SYS_UNIT_PIXEL )
		{
			if ( m_fMarkerSize < 1.000000f )
				m_fMarkerSize = 1.000000f;
		}
		else
		{
			if ( m_fMarkerSize < 0.000001f)
			{
				m_fMarkerSize = 0.000001f;
			}
		}

		return; 
	}


	ISymbol::SetProperties(PropertyName , PropertyValue);

}

_variant_t Display::IMarkerSymbol::GetProperties(const char* PropertyName)
{
	_variant_t vt;
#define GETPROP(inName,Name,Val,T) if( stricmp(inName,Name) == 0 ) { vt = (T)Val;return vt; }
#define GETPROP2(Name,Val,T) GETPROP(PropertyName , Name , Val , T )



	GETPROP2( "MARKOFFSETX" , m_fOffsetX , _variant_t );
	GETPROP2( "MARKOFFSETY" , m_fOffsetY , _variant_t );
	GETPROP2( "MARKANGLE" , m_fAngle , _variant_t );
	GETPROP2( "MARKSIZE" , m_fMarkerSize , _variant_t );
	GETPROP2( "MASKDRAWABLE" , m_bMask , _variant_t );
	GETPROP2( "MARKCOLOR" , m_lColor , _variant_t );

	return ISymbol::GetProperties(PropertyName);



}

void Display::IMarkerSymbol::DrawLegend( DIS_RECT * rect , int nFlag )
{


	DIS_POINT*  CreateDisplayPoint( point );
	if( nFlag == 2)
	{
		goto DrawStyle;
	}
	else if( nFlag == 3)
	{
		point->p.x = rect->left + ((rect->right - rect->left)>>1) ;
		point->p.y = rect->top ;
		Draw(point);
		point->p.x = rect->left ;
		point->p.y = rect->top + ((rect->bottom - rect->top)>>1) ;
		Draw(point);
		point->p.x = rect->right - ((rect->right - rect->left)>>1) ;
		point->p.y = rect->bottom ;
		Draw(point);
		point->p.x = rect->right;
		point->p.y = rect->bottom - ((rect->bottom - rect->top)>>1);
		Draw(point);
		goto DrawStyle;

	}
	else
	{
		point->p.x = (rect->left + rect->right)>>1;
		point->p.y = (rect->top + rect->bottom)>>1;

		Draw(point);

		FreeDisplayObj( point );
		return;
	}


DrawStyle:
	point->p.x = rect->left ;
	point->p.y = rect->top;
	Draw(point);
	point->p.x = rect->right ;
	point->p.y = rect->top;
	Draw(point);
	point->p.x = rect->right ;
	point->p.y = rect->bottom ;
	Draw(point);
	point->p.x = rect->left ;
	point->p.y = rect->bottom ;
	Draw(point);
	FreeDisplayObj( point );

}

void Display::IMarkerSymbol::Draw(void* pObject)
{

}

void Display::IMarkerSymbol::serialization(SYSTEM::IArchive & ar)
{ 
	ISymbol::serialization(ar); 

	ar & m_fOffsetX;				 
	ar & m_fOffsetY;				 
	ar & m_fAngle;
	ar & m_fMarkerSize;				 
	ar & m_bMask;
	//m_pSymbolMask
}

void Display::IMarkerSymbol::OnUnitChanged(SYSTEM::SYS_UNIT_TYPE oldUnit , SYSTEM::SYS_UNIT_TYPE newUnit)
{
	ISymbol::OnUnitChanged(oldUnit , newUnit);

	m_fMarkerSize = UnitChangeTo( oldUnit , newUnit , m_fMarkerSize );
	m_fOffsetX = UnitChangeTo( oldUnit , newUnit , m_fOffsetX );
	m_fOffsetY = UnitChangeTo( oldUnit , newUnit , m_fOffsetY );
}

void Display::IMarkerSymbol::OnChangingInSelectDC()
{
	m_lMarkerSize = UnitChange( m_enumUnit , m_fMarkerSize );
	m_lOffsetX = UnitChange( m_enumUnit , m_fOffsetX );
	m_lOffsetY = UnitChange( m_enumUnit , m_fOffsetY );

	ISymbol::OnChangingInSelectDC();
}

void Display::IMarkerSymbol::ClearDC()
{
	ISymbol::ClearDC();
}