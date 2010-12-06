#include "stdafx.h"
#include "SimpleLineSymbol.h"
#include "CDC.h"


Display::CSimpleLineSymbol::CSimpleLineSymbol()
{
	m_enumLineType = SOLID;

	m_hPenHandle = NULL;
}

Display::CSimpleLineSymbol::CSimpleLineSymbol(const Display::CSimpleLineSymbol& SimpleLineSymbol)
{
	*this = SimpleLineSymbol;
}

Display::CSimpleLineSymbol& Display::CSimpleLineSymbol::operator = (const Display::CSimpleLineSymbol & SimpleLineSymbol)
{


	if( this == &SimpleLineSymbol )
		return *this;

	m_enumLineType		=		SimpleLineSymbol.m_enumLineType;

	*(ILineSymbol*)this =		*(ILineSymbol*)&SimpleLineSymbol;


}

Display::CSimpleLineSymbol::~CSimpleLineSymbol()
{
	ClearDC();
}

SIMLINE_STYLE Display::CSimpleLineSymbol::GetLineStyle()
{
	return m_enumLineType;
}

void Display::CSimpleLineSymbol::SetLineStyle(SIMLINE_STYLE nStyle)
{
	m_enumLineType = nStyle;
}

SYMBOL_TYPE Display::CSimpleLineSymbol::GetType()
{
	return SIMPLE_LINE_SYMBOL;
}

void Display::CSimpleLineSymbol::Draw(void* pObject)
{

	if(!pObject)
		return;

	if( CheckNoColor(m_lColor))
		return;

	if(((DIS_BEZIER *)pObject)->type == Dis_Bezier)
	{
		DIS_BEZIER  *pDIS_BEZIER = (DIS_BEZIER *)pObject;
		m_pDC->DrawPolyBezier( *pDIS_BEZIER );

	}
	else
	{
		DIS_LINE  *pDIS_LINE = (DIS_LINE *)pObject;

		if(pDIS_LINE->type != Dis_Line)
			return;

		m_pDC->DrawPolyLines( *pDIS_LINE );
	}


}

void Display::CSimpleLineSymbol::SelectDC(Display::CDC * pDC)
{ 


	ISymbol::SelectDC( pDC ); 

	LINE_STYLE ls;				//ÉèÖÃ»­±Ê
	memset( &ls , 0 , sizeof(ls) );
	ls.eStyle = m_enumLineType;
	ls.lColor = m_lColor;
	ls.lWidth = m_lLineWidth;

	DISPLAY_HANDLE hPen = m_pDC->CreatePen(ls);
	m_hPenHandle = Display::CDisplayCache::AddToDisplayCache( hPen , m_pDC );

}

void Display::CSimpleLineSymbol::SetReadyDraw()
{ 
	Display::CDisplayCache::UseCache( m_hPenHandle , this );

}

void Display::CSimpleLineSymbol::SetProperties(const char* PropertyName,const _variant_t& PropertyValue)
{
#define SETPROP(inVal,Val,inName,Name,VT) if( stricmp(inName,Name) == 0 ) { Val = (VT)inVal;return; }
#define SETPROP2(Val,Name,VT) SETPROP( PropertyValue , Val , PropertyName , Name , VT )
#define SETPROPEX(inVal,Val,inName,Name,VT,VT2) if( stricmp(inName,Name) == 0 ) { Val = (VT2)((VT)inVal);return; }
#define SETPROPEX2(Val,Name,VT,VT2) SETPROPEX( PropertyValue , Val , PropertyName , Name , VT , VT2)


	//		long t = 0;
	SETPROPEX2( m_enumLineType , "SIMLINESTYLE" , long , SIMLINE_STYLE );
	//		m_enumLineType = (SIMLINESTYLE)t;
	return ILineSymbol::SetProperties( PropertyName , PropertyValue);


}

_variant_t Display::CSimpleLineSymbol::GetProperties(const char* PropertyName)
{
	_variant_t vt;
#define GETPROP(inName,Name,Val,T) if( stricmp(inName,Name) == 0 ) { vt = (T)Val;return vt; }
#define GETPROP2(Name,Val,T) GETPROP(PropertyName , Name , Val , T )


	long t = m_enumLineType;
	GETPROP2("SIMLINESTYLE", t , _variant_t );

	return ILineSymbol::GetProperties(PropertyName);

}

void Display::CSimpleLineSymbol::Zoom(float rate)
{
	ILineSymbol::Zoom(rate);
}

void Display::CSimpleLineSymbol::serialization(SYSTEM::IArchive & ar)
{ 
	ILineSymbol::serialization(ar);

	if( ar.IsSave() )
	{
		int i = m_enumLineType;
		ar & (i);		
	}
	else
	{
		int i;
		ar & (i);		
		m_enumLineType=(SIMLINE_STYLE)i;
	}		 
}

void Display::CSimpleLineSymbol::ClearDC()
{
	if( m_hPenHandle != NULL )
	{
		Display::CDisplayCache::ReleaseCache( m_hPenHandle );
		m_hPenHandle = NULL;
	}
	ILineSymbol::ClearDC();
}


void Display::CSimpleLineSymbol::OnUnitChanged(SYSTEM::SYS_UNIT_TYPE oldUnit , SYSTEM::SYS_UNIT_TYPE newUnit)
{
	ILineSymbol::OnUnitChanged(oldUnit , newUnit);
}

void Display::CSimpleLineSymbol::OnChangingInSelectDC()
{
	ILineSymbol::OnChangingInSelectDC();
}