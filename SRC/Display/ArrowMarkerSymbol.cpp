#include "stdafx.h"
#include "ArrowMarkerSymbol.h"
#include <math.h>
#include "CDC.h"
#include "IArchive.h"
Display::CArrowMarkerSymbol::CArrowMarkerSymbol()
{

		m_fRate = 2.0f;						//符号比率默认为2

		m_lWidth = 6;						//符号宽度默认6

		m_lMarkerSize = 3;					//符号宽度默认为3

		m_fMarkerSize = 3.0f;

		m_hPenHandle = NULL;
		
		m_hBrushHandle = NULL;
		
		m_lInsideReviseX = 3;				//校正值默认为3
}

Display::CArrowMarkerSymbol::CArrowMarkerSymbol(const Display::CArrowMarkerSymbol& ArrowMarkSymbol)
{
		*this = ArrowMarkSymbol;
}

Display::CArrowMarkerSymbol& Display::CArrowMarkerSymbol::operator = (const Display::CArrowMarkerSymbol & ArrowMarkSymbol)
{

		this->m_fRate		=		ArrowMarkSymbol.m_fRate;
//		this->m_pSymbolMask	=		ArrowMarkSymbol.m_pSymbolMask;
	/*	this->m_lInsideReviseX=     ArrowMarkSymbol.m_lInsideReviseX;*/
		/*this->m_fWidth		=		ArrowMarkSymbol.m_fWidth;*/
		*(IMarkerSymbol*)this=*(IMarkerSymbol*)&ArrowMarkSymbol;
		return *this;
}

Display::CArrowMarkerSymbol::~CArrowMarkerSymbol()
{
	ClearDC();
}

SYMBOL_TYPE Display::CArrowMarkerSymbol::GetType()
{
	return ARROW_MARKER_SYMBOL;
}
void Display::CArrowMarkerSymbol::Draw(void* pObject)
{
		if( CheckNoColor(m_lColor))
			return;
		DIS_POINT *pPoint = (DIS_POINT*)pObject;

		if( pPoint == NULL || pPoint->type != Dis_Point )
		{
			return;
		}

		DIS_POINTs[0] = pPoint->p.x + m_lOffsetX - m_lInsideReviseX;
		DIS_POINTs[1] = pPoint->p.y + (m_lMarkerSize >> 1) + m_lOffsetY;
		DIS_POINTs[2] = pPoint->p.x + m_lWidth + m_lOffsetX - m_lInsideReviseX;
		DIS_POINTs[3] = pPoint->p.y + m_lOffsetY;
		DIS_POINTs[4] = pPoint->p.x + m_lOffsetX - m_lInsideReviseX;
		DIS_POINTs[5] = pPoint->p.y - (m_lMarkerSize >> 1) + m_lOffsetY;

		if(m_fAngle)							//弧度不为0，转世界坐标系
		{
			XFORM old = m_pDC->SetWorldTransform( -m_fAngle , 1.0f , 1.0f , pPoint->p.x + m_lOffsetX , pPoint->p.y + m_lOffsetY );

			m_pDC->DrawPolygon(3,*DIS_POINTs);		//实现绘制

			m_pDC->SetWorldTransformBack(old);
		}	
		else
		{
			m_pDC->DrawPolygon(3,*DIS_POINTs);		//实现绘制
		}
	
}
void Display::CArrowMarkerSymbol::SetRate(float fRate)
{
		if ( fRate < 0 )
		{
			fRate = -fRate;
		}

		m_fRate = fRate;

		m_lWidth = m_lMarkerSize * fRate;

		m_lInsideReviseX = (unsigned long)(m_lWidth >> 1);
}

float Display::CArrowMarkerSymbol::GetRate()
{
	return m_fRate;
}

void Display::CArrowMarkerSymbol::SelectDC(Display::CDC * pDC)
{
		ISymbol::SelectDC( pDC ); 
		m_lWidth = m_lMarkerSize * m_fRate;
		m_lInsideReviseX = (unsigned long)(m_lWidth >> 1);

		LINE_STYLE ls;						//设置画笔
		memset( &ls , 0 , sizeof(ls) );
		ls.eStyle = SOLID;
		ls.lColor = m_lColor;
		ls.lWidth = 1;
		DISPLAY_HANDLE hPen = m_pDC->CreatePen(ls);
		m_hPenHandle = CDisplayCache::AddToDisplayCache( hPen , m_pDC );

		BRUSH_STYLE bs;						//设置刷子
		bs.lColor = m_lColor;
		bs.Style = SOLID_BRUSH;
		DISPLAY_HANDLE hBrush = m_pDC->CreateBrush(bs);
		m_hBrushHandle = CDisplayCache::AddToDisplayCache( hBrush , m_pDC );
}

void Display::CArrowMarkerSymbol::SetReadyDraw()
{ 
	CDisplayCache::UseCache( m_hPenHandle , this );
	CDisplayCache::UseCache( m_hBrushHandle , this );
}

#define SETPROP(inVal,Val,inName,Name,VT,VT2) if( stricmp(inName,Name) == 0 ) { Val = (VT2)((VT)inVal);return; }
#define SETPROP2(Val,Name,VT) SETPROP( PropertyValue , Val , PropertyName , Name , VT , VT )
#define SETPROP2E(Val,Name,VT,VT2) SETPROP( PropertyValue , Val , PropertyName , Name , VT , VT2 )
void Display::CArrowMarkerSymbol::SetProperties(const char* PropertyName , const _variant_t& PropertyValue)
{

		SETPROP2( m_fRate , "ARROWRATE" , float);
		if ( !strcmp( PropertyName , "MARKSIZE" ) )
		{
			m_fMarkerSize = (float)PropertyValue;
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

			m_lWidth = m_lMarkerSize * m_fRate;

			m_lInsideReviseX = (unsigned long)( m_lWidth >> 1 );
			return;
		}

		IMarkerSymbol::SetProperties( PropertyName , PropertyValue );
}

#define GETPROP(inName,Name,Val,T) if( stricmp(inName,Name) == 0 ) { vt = (T)Val;return vt; }
#define GETPROP2(Name,Val,T) GETPROP(PropertyName , Name , Val , T )
_variant_t Display::CArrowMarkerSymbol::GetProperties(const char* PropertyName)
{
	_variant_t vt;

	GETPROP2( "ARROWRATE" , m_fRate , _variant_t );

	return IMarkerSymbol::GetProperties(PropertyName);
	return NULL; 
}
void Display::CArrowMarkerSymbol::Zoom(float rate)
{
		IMarkerSymbol::Zoom(rate);

		m_lWidth = m_lMarkerSize * m_fRate;

		m_lInsideReviseX = (unsigned long)(m_lWidth >> 1);
}
void Display::CArrowMarkerSymbol::serialization(SYSTEM::IArchive & ar)
{ 
	IMarkerSymbol::serialization( ar ); 

	ar & (m_fRate);				 
	ar & (m_lInsideReviseX);				 
	ar & (m_lWidth);				 
	//for ( int  i = 0 ; i < 6; ++i)
	//{
	//	ar & DIS_POINTs[i];
	//}
}

void Display::CArrowMarkerSymbol::ClearDC()
{
	if( m_hPenHandle != NULL)
	{
		CDisplayCache::ReleaseCache( m_hPenHandle );
		m_hPenHandle = NULL;
	}
	if( m_hBrushHandle != NULL)
	{
		CDisplayCache::ReleaseCache( m_hBrushHandle );
		m_hBrushHandle = NULL;
	}
	IMarkerSymbol::ClearDC();
}

void  Display::CArrowMarkerSymbol::OnUnitChanged(SYSTEM::SYS_UNIT_TYPE oldUnit , SYSTEM::SYS_UNIT_TYPE newUnit)
{
	IMarkerSymbol::OnUnitChanged(oldUnit , newUnit);
}

void Display::CArrowMarkerSymbol::OnChangingInSelectDC()
{
	IMarkerSymbol::OnChangingInSelectDC();
}