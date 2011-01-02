#include "stdafx.h"
#include "SimpleMarkerSymbol.h"
#include "CDC.h"
#include "IArchive.h"
////////////////////////////////////////////////////////////////////////////////
//
// 简单点符号
//		： 可以绘制可设置颜色的五个简单形状
//			1为正方形，
//			2为圆形，
//			3为十字形，
//			4为x形，
//			5为菱形，
//			6为自定义，需要设置绘制函数
//
////////////////////////////////////////////////////////////////////////////////

void __stdcall DrawNULL( Display::CDC *pDC , const DIS_POINT* dSimpleMark , unsigned long m_lMarkerSize , long m_lOffsetX , long m_lOffsetY )
{

}

void __stdcall DrawSimpleSquare( Display::CDC *pDC , const DIS_POINT* dSimpleMark , unsigned long m_lMarkerSize , long m_lOffsetX , long m_lOffsetY )	//绘制正方形
{
	
		register DIS_RECT rect;																														//设置屏幕数据
		rect.left = dSimpleMark->p.x - m_lMarkerSize + m_lOffsetX;
		rect.top = dSimpleMark->p.y - m_lMarkerSize + m_lOffsetY;
		rect.right = dSimpleMark->p.x + m_lMarkerSize + m_lOffsetX;
		rect.bottom = dSimpleMark->p.y + m_lMarkerSize + m_lOffsetY;

		pDC->DrawAndFillRect( rect );																												//绘制形状和填充
	
}

void __stdcall DrawSimpleCircle( Display::CDC *pDC , const DIS_POINT* dSimpleMark , unsigned long m_lMarkerSize , long m_lOffsetX , long m_lOffsetY )	//绘制圆形
{
	

		register DIS_RECT circle;

		circle.left = dSimpleMark->p.x + m_lOffsetX - m_lMarkerSize;
		circle.top = dSimpleMark->p.y + m_lOffsetY - m_lMarkerSize;
		circle.right = circle.left + ( m_lMarkerSize << 1 );
		circle.bottom = circle.top + ( m_lMarkerSize << 1 );

		pDC->Circle( circle );																														//绘制线形并填充
		
	
}

void __stdcall DrawSimpleCross( Display::CDC *pDC , const DIS_POINT* dSimpleMark , unsigned long m_lMarkerSize , long m_lOffsetX , long m_lOffsetY )	//绘制十字形
{
	

		DIS_POINT points[4];

		points[0].p.x = dSimpleMark->p.x - m_lMarkerSize + m_lOffsetX;
		points[0].p.y = dSimpleMark->p.y + m_lOffsetY;
		points[1].p.x = dSimpleMark->p.x + m_lMarkerSize + m_lOffsetX;
		points[1].p.y = dSimpleMark->p.y + m_lOffsetY;

		points[2].p.x = dSimpleMark->p.x + m_lOffsetX;
		points[2].p.y = dSimpleMark->p.y - m_lMarkerSize + m_lOffsetY;
		points[3].p.x = dSimpleMark->p.x + m_lOffsetX;
		points[3].p.y = dSimpleMark->p.y + m_lMarkerSize + m_lOffsetY;

		pDC->DrawLine( points[0] , points[1] );																										//绘制线形
		pDC->DrawLine( points[2] , points[3] );

	
}

void __stdcall DrawSimpleX( Display::CDC *pDC , const DIS_POINT* dSimpleMark , unsigned long m_lMarkerSize , long m_lOffsetX , long m_lOffsetY )		//绘制x形	
{
	

		DIS_POINT points[4];

		points[0].p.x = dSimpleMark->p.x - m_lMarkerSize + m_lOffsetX;
		points[0].p.y = dSimpleMark->p.y - m_lMarkerSize + m_lOffsetY;
		points[1].p.x = dSimpleMark->p.x + m_lMarkerSize + m_lOffsetX;
		points[1].p.y = dSimpleMark->p.y + m_lMarkerSize + m_lOffsetY;

		points[2].p.x = dSimpleMark->p.x - m_lMarkerSize + m_lOffsetX;
		points[2].p.y = dSimpleMark->p.y + m_lMarkerSize + m_lOffsetY;
		points[3].p.x = dSimpleMark->p.x + m_lMarkerSize + m_lOffsetX;
		points[3].p.y = dSimpleMark->p.y - m_lMarkerSize + m_lOffsetY;

		pDC->DrawLine( points[0] , points[1] );																										//绘制线形
		pDC->DrawLine( points[2] , points[3] );

	
}

void __stdcall DrawSimpleStar( Display::CDC *pDC , const DIS_POINT* dSimpleMark , unsigned long m_lMarkerSize , long m_lOffsetX , long m_lOffsetY )		//绘制x形	
{
	

		DIS_POINT points[8];

	points[0].p.x = dSimpleMark->p.x - m_lMarkerSize + m_lOffsetX;
	points[0].p.y = dSimpleMark->p.y + m_lOffsetY;
	points[1].p.x = dSimpleMark->p.x + m_lMarkerSize + m_lOffsetX;
	points[1].p.y = dSimpleMark->p.y + m_lOffsetY;

	points[2].p.x = dSimpleMark->p.x + m_lOffsetX;
	points[2].p.y = dSimpleMark->p.y - m_lMarkerSize + m_lOffsetY;
	points[3].p.x = dSimpleMark->p.x + m_lOffsetX;
	points[3].p.y = dSimpleMark->p.y + m_lMarkerSize + m_lOffsetY;

	points[4].p.x = dSimpleMark->p.x - m_lMarkerSize + m_lOffsetX;
	points[4].p.y = dSimpleMark->p.y + m_lMarkerSize + m_lOffsetY;
	points[5].p.x = dSimpleMark->p.x + m_lMarkerSize + m_lOffsetX;
	points[5].p.y = dSimpleMark->p.y - m_lMarkerSize + m_lOffsetY;

	points[6].p.x = dSimpleMark->p.x - m_lMarkerSize + m_lOffsetX;
	points[6].p.y = dSimpleMark->p.y - m_lMarkerSize + m_lOffsetY;
	points[7].p.x = dSimpleMark->p.x + m_lMarkerSize + m_lOffsetX;
	points[7].p.y = dSimpleMark->p.y + m_lMarkerSize + m_lOffsetY;

	pDC->DrawLine( points[0] , points[1] );																										//绘制线形
	pDC->DrawLine( points[2] , points[3] );
	pDC->DrawLine( points[4] , points[5] );
	pDC->DrawLine( points[6] , points[7] );

	
}



void __stdcall DrawSimpleDiamond( Display::CDC *pDC , const DIS_POINT* dSimpleMark , unsigned long m_lMarkerSize , long m_lOffsetX , long m_lOffsetY )	//绘制菱形
{
	

		DIS_POINT points[4];

		points[0].p.x = (long)( dSimpleMark->p.x - m_lMarkerSize + m_lOffsetX );
		points[0].p.y = (long)( dSimpleMark->p.y + m_lOffsetY );
		points[1].p.x = (long)( dSimpleMark->p.x + m_lMarkerSize + m_lOffsetX );
		points[1].p.y = (long)( dSimpleMark->p.y + m_lOffsetY );

		points[2].p.x = (long)( dSimpleMark->p.x + m_lOffsetX );
		points[2].p.y = (long)( dSimpleMark->p.y - m_lMarkerSize + m_lOffsetY);
		points[3].p.x = (long)( dSimpleMark->p.x + m_lOffsetX );
		points[3].p.y = (long)( dSimpleMark->p.y + m_lMarkerSize + m_lOffsetY);
		
		pDC->DrawAndFillDiamond( &points[0] );																										//绘制线形并填充	

	
}

Display::CSimpleMarkerSymbol::CSimpleMarkerSymbol()
{
	m_enumMarkType = SIMPLE_MARKER_CIRCLE;							//简单点符号的样式默认为无

	m_StyleFunc = DrawSimpleCircle;

	/*m_lOutLineWidth = 1;*/												//轮廓宽度默认为1
	m_fOutLineWidth = 0.300000f;

	/*srand( (unsigned)time( NULL ) );
	
	m_lOutLineColor = RGB((unsigned char)rand(),
		(unsigned char)rand(),
		(unsigned char)rand() );	*/									//设置轮廓颜色
	m_lOutLineColor = RGB((((double) rand() / (double) 255) * 255 + 0) , (((double) rand() / (double) 255) * 255 + 0),
		(((double) rand() / (double) 255) * 255 + 0));

	m_hBrushHandle = NULL;
	m_hPenHandle = NULL;

	m_bOutLine = true;
}

Display::CSimpleMarkerSymbol::CSimpleMarkerSymbol( const Display::CSimpleMarkerSymbol& SimpleMarkSymbol )
{
	*this = SimpleMarkSymbol;	
}

Display::CSimpleMarkerSymbol::~CSimpleMarkerSymbol()
{	
	ClearDC();
}

Display::CSimpleMarkerSymbol& Display::CSimpleMarkerSymbol::operator = ( const Display::CSimpleMarkerSymbol & SimpleMarkSymbol )
{
		if( this == &SimpleMarkSymbol )
			return *this;

		this->m_bOutLine		=		SimpleMarkSymbol.m_bOutLine;
		this->m_enumMarkType	=		SimpleMarkSymbol.m_enumMarkType;
		this->m_lOutLineColor	=		SimpleMarkSymbol.m_lOutLineColor;	
		this->m_fOutLineWidth	=		SimpleMarkSymbol.m_fOutLineWidth;
//		this->m_pSymbolMask		=		SimpleMarkSymbol.m_pSymbolMask;
		this->m_StyleFunc       =		SimpleMarkSymbol.m_StyleFunc;
		*(IMarkerSymbol*)this = *(IMarkerSymbol*)&SimpleMarkSymbol;
}

void Display::CSimpleMarkerSymbol::Draw( void* pObject )
{
	
	if( CheckNoColor(m_lColor))
		return;
	DIS_POINT *pPoint = (DIS_POINT*)pObject;

	XFORM old = m_pDC->SetWorldTransform( m_fAngle , 1.0f , 1.0f , pPoint->p.x + m_lOffsetX , pPoint->p.y + m_lOffsetY );

	m_StyleFunc( m_pDC, pPoint , m_lMarkerSize>>1 , m_lOffsetX , m_lOffsetY );

	m_pDC->SetWorldTransformBack( old );

	
}

SYMBOL_TYPE Display::CSimpleMarkerSymbol::GetType()
{	
	return SIMPLE_MARKER_SYMBOL;
}

void Display::CSimpleMarkerSymbol::SetMarkerType(SIMPLE_MARKER_STYLE enumType, DRAWSTYLE_FUNC Func )
{
	m_enumMarkType = enumType;

	switch(m_enumMarkType)
	{
		case	SIMPLE_MARKER_NULL		:
			m_StyleFunc = DrawNULL;
			break;

		case	SIMPLE_MARKER_SQUARE	:
			m_StyleFunc = DrawSimpleSquare;
			break;

		case	SIMPLE_MARKER_CIRCLE	:
			m_StyleFunc = DrawSimpleCircle;
			break;

		case	SIMPLE_MARKER_CROSS	:
			m_StyleFunc = DrawSimpleCross;
			break;

		case SIMPLE_MARKER_STAR:
			m_StyleFunc = DrawSimpleStar;
			break;

		case	SIMPLE_MARKER_X		:
			m_StyleFunc = DrawSimpleX;
			break;

		case	SIMPLE_MARKER_DIAMOND	:
			m_StyleFunc = DrawSimpleDiamond;
			break;

		case	SIMPLE_MARKER_CUSTOM   :
			if( Func != NULL )
				m_StyleFunc = Func;
			else
				m_StyleFunc = DrawNULL;
			break;

		default:
			m_StyleFunc = DrawNULL;
		break;
	}
}

SIMPLE_MARKER_STYLE Display::CSimpleMarkerSymbol::GetMarkerType()
{
	return m_enumMarkType;
}

void  Display::CSimpleMarkerSymbol::SetOutLineWidth(float width)
{
	if( width < 0.000000f )
		width = 0.000001f;

	m_fOutLineWidth = width;
}

float Display::CSimpleMarkerSymbol::GetOutLineWidth()
{	
	return m_fOutLineWidth;
}

void Display::CSimpleMarkerSymbol::SetOutLineColor(unsigned long lColor)
{
	m_lOutLineColor = lColor;
}
unsigned long Display::CSimpleMarkerSymbol::GetOutLineColor()
{
	return	m_lOutLineColor;
}
void Display::CSimpleMarkerSymbol::SetOutLineFlag(bool bOutLine)
{
	m_bOutLine = bOutLine;
}
bool Display::CSimpleMarkerSymbol::GetOutLineFlag()
{
	return m_bOutLine;
}

void Display::CSimpleMarkerSymbol::SelectDC(Display::CDC * pDC)
{ 
	

		ISymbol::SelectDC(pDC); 

		LINE_STYLE ls;
		memset(&ls,0,sizeof(ls));//设置画笔
		ls.eStyle = SOLID;
		if( m_bOutLine )
			ls.lColor = m_lOutLineColor;
		else
			ls.lColor = m_lColor;
		
		if (!m_bOutLine)
		{
			ls.lWidth = 1;
		}
		else
		{
			ls.lWidth = m_lOutLineWidth;
		}

		DISPLAY_HANDLE hPen = m_pDC->CreatePen(ls);
		m_hPenHandle = CDisplayCache::AddToDisplayCache( hPen , m_pDC );

		BRUSH_STYLE bs;									//设置刷子
		bs.lColor = m_lColor;
		bs.Style  = SOLID_BRUSH;

		DISPLAY_HANDLE hBrush = m_pDC->CreateBrush(bs);
		m_hBrushHandle = CDisplayCache::AddToDisplayCache( hBrush , m_pDC );

	
}

void Display::CSimpleMarkerSymbol::SetReadyDraw()
{
	CDisplayCache::UseCache( m_hPenHandle , this );
	CDisplayCache::UseCache( m_hBrushHandle , this );
}

#define SETPROP(inVal,Val,inName,Name,VT,VT2) if( stricmp(inName,Name) == 0 ) { Val = (VT2)((VT)inVal);return; }
#define SETPROP2(Val,Name,VT) SETPROP( PropertyValue , Val , PropertyName , Name , VT , VT )
#define SETPROP2E(Val,Name,VT,VT2) SETPROP( PropertyValue , Val , PropertyName , Name , VT , VT2 )

void Display::CSimpleMarkerSymbol::SetProperties( const char* PropertyName , const _variant_t& PropertyValue)
{
	

		if( stricmp(PropertyName , "OUTLINEWIDTH") == 0 ) 
		{ 
			m_fOutLineWidth = (float)PropertyValue;

			if ( m_enumUnit == SYSTEM::SYS_UNIT_PIXEL )
			{
				if ( m_fOutLineWidth < 1.000000f )
					m_fOutLineWidth = 1.000000f;
			}
			else
			{
				if ( m_fOutLineWidth < 0.000001f)
				{
					m_fOutLineWidth = 0.000001f;
				}
			}
			return; 
		}

		if( stricmp(PropertyName,"SIMPLE_MARKER_STYLE") == 0 ) 
		{ 
			m_enumMarkType = (SIMPLE_MARKER_STYLE)((long)PropertyValue);
			SetMarkerType(m_enumMarkType);
			return; 
		}

		SETPROP2( m_lOutLineColor , "OUTLINECOLOR" , unsigned long );
		SETPROP2( m_bOutLine , "OUTLINEDRAWABLE" , bool );

		IMarkerSymbol::SetProperties( PropertyName , PropertyValue);

	
}

#define GETPROP(inName,Name,Val,T) if( stricmp(inName,Name) == 0 ) { vt = (T)Val;return vt; }
#define GETPROP2(Name,Val,T) GETPROP(PropertyName , Name , Val , T )

_variant_t Display::CSimpleMarkerSymbol::GetProperties(const char* PropertyName)
{
	_variant_t vt;

	GETPROP2( "OUTLINEWIDTH" , m_fOutLineWidth , _variant_t );
	
	GETPROP2( "SIMPLE_MARKER_STYLE" , m_enumMarkType , _variant_t );
	GETPROP2( "OUTLINECOLOR" , m_lOutLineColor , _variant_t );
	GETPROP2( "OUTLINEDRAWABLE" , m_bOutLine , _variant_t );

	return IMarkerSymbol::GetProperties(PropertyName);
}

void Display::CSimpleMarkerSymbol::Zoom(float rate)
{
	

		m_lOutLineWidth = m_lOutLineWidth * rate;

		if ( m_lOutLineWidth < 1 )
			m_lOutLineWidth = 1;

		IMarkerSymbol::Zoom(rate);
	
}


void Display::CSimpleMarkerSymbol::ClearDC()
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

void Display::CSimpleMarkerSymbol::OnUnitChanged(SYSTEM::SYS_UNIT_TYPE oldUnit , SYSTEM::SYS_UNIT_TYPE newUnit)
{
	IMarkerSymbol::OnUnitChanged(oldUnit , newUnit);

	m_fOutLineWidth = UnitChangeTo( oldUnit , newUnit , m_fOutLineWidth );
}

void Display::CSimpleMarkerSymbol::OnChangingInSelectDC()
{
	m_lOutLineWidth = UnitChange( m_enumUnit , m_fOutLineWidth );

	IMarkerSymbol::OnChangingInSelectDC();
}