#include "stdafx.h"
#include "CharMarkerSymbol.h"

#pragma warning(disable:4996)

namespace Display {
CCharMarkerSymbol::CCharMarkerSymbol()
{
		m_hFontHandle = NULL;								//字体ID初始为0

		m_wcMarker = (wchar_t)38;								

		m_cpFaceName = "BatangChe";				//指针清零

		m_btCharSet = 1;									//默认字符集为中文简体字符集

		m_lMarkerSize = 20;
		m_fMarkerSize = 5.0f;

		m_lInsideReviseX = 0;								//内部x方向校正,默认为0

		m_lInsideReviseY = 0;								//内部y方向校正,默认为0

		m_bCharMapChange = true;

		m_lCharWidth = 0;
		m_fCharWidth = 0.0f;

}

CCharMarkerSymbol::CCharMarkerSymbol(const CCharMarkerSymbol& CharMarkSymbol)
{
		*this = CharMarkSymbol;
}

CCharMarkerSymbol::~CCharMarkerSymbol()
{	
		ClearDC();
}

CCharMarkerSymbol& CCharMarkerSymbol::operator = (const CCharMarkerSymbol & CharMarkSymbol)
{	
		if(this == &CharMarkSymbol)
			return *this;

		this->m_btCharSet	=		CharMarkSymbol.m_btCharSet;
		this->m_cpFaceName	=		CharMarkSymbol.m_cpFaceName;

	//		this->m_pSymbolMask	=		toCharMarkSymbol.m_pSymbolMask;
		this->m_wcMarker		=		CharMarkSymbol.m_wcMarker;
		*(IMarkerSymbol*)this = *(IMarkerSymbol*)&CharMarkSymbol;
		m_bCharMapChange = true;
		m_fCharWidth = CharMarkSymbol.m_fCharWidth;
}

void CCharMarkerSymbol::Draw(void* pObject)
{
		if( CheckNoColor(m_lColor))
			return;
		DIS_POINT *pPoint = (DIS_POINT*)pObject;

		if( pPoint == NULL || pPoint->type != Dis_Point )
		{
			return;
		}

		if (m_bCharMapChange)
		{
			if (m_wcMarker <= 0xff)
			{
				DIS_RECT rect;
				rect.left = 0;
				rect.top = 0;
				rect.right = 1;
				rect.bottom = 1;

				m_pDC->DrawText(rect , (LPTSTR)&m_wcMarker ,DT_CALCRECT | DT_NOCLIP | DT_NOPREFIX | DT_LEFT | DT_TOP);
				m_lInsideReviseX = rect.right;
				m_lInsideReviseY = rect.bottom;
			}
			else
			{
				int charNum = 0;
				char m_cMark[4];
				if(wcslen(&m_wcMarker))
				{
					m_cMark[0] = '\0';
					m_cMark[1] = '\0';
					m_cMark[2] = '\0';
					m_cMark[3] = '\0';
					m_pDC->ConverChar(&m_wcMarker,&m_cMark[0]);

				}
				m_pDC->GetFontInfo( m_lInsideReviseX , m_lInsideReviseY , m_cMark , 2 );		//得到字
			}
			
			m_bCharMapChange = false;
		}

		unsigned long tmpColor = m_pDC->GetFGColor();
		m_pDC->SetFGColor(m_lColor);

		DIS_POINT dCenter;
		dCenter.p.x = pPoint->p.x + m_lOffsetX - ( m_lInsideReviseX >> 1 );
		dCenter.p.y = pPoint->p.y + m_lOffsetY - ( m_lInsideReviseY >> 1 );

		if(m_fAngle)
		{
			XFORM old = m_pDC->SetWorldTransform( -m_fAngle , 1.0f , 1.0f , pPoint->p.x /*+ m_lInsideReviseX*/  , pPoint->p.y /*+ m_lInsideReviseY*/ );

			m_pDC->DrawCharPoint( dCenter , m_wcMarker , 1 );	//实现绘制	

			m_pDC->SetWorldTransformBack(old);
		}
		else
		{
			m_pDC->DrawCharPoint( dCenter , m_wcMarker , 1 );	//实现绘制	
		}
		
		m_pDC->SetFGColor(tmpColor);

}

SYMBOL_TYPE CCharMarkerSymbol::GetType()
{
	return CHAR_MARKER_SYMBOL;
}

void CCharMarkerSymbol::SetCharMap(const wchar_t wMark)
{

		if( wMark == NULL )
		{
			return;
		}	

		m_wcMarker = wMark;
		m_bCharMapChange = true;
}
wchar_t* CCharMarkerSymbol::GetCharMap()
{
	return &m_wcMarker;
}
void CCharMarkerSymbol::SetFaceName(const char *name)
{
	if( name == NULL )
	{
		return;
	}
	m_cpFaceName = name;

}
char* CCharMarkerSymbol::GetFaceName()
{
	return (char*)m_cpFaceName.c_str();
}
void CCharMarkerSymbol::SetCharSet(byte charSet)
{
		if( charSet < 0 )
		{
			return;
		}
		m_btCharSet = charSet;
}
byte CCharMarkerSymbol::GetCharSet()
{
	return m_btCharSet;
}

DISPLAY_HANDLE CCharMarkerSymbol::SetFont()
{
	DIS_FONT df;
	df.lfHeight = m_lMarkerSize;				//设置字符高度
	if ( m_lMarkerSize == 0 )
	{
		df.lfHeight = 1;
	}
	df.lfWidth = 0;/*m_lCharWidth;*/				//设置字符宽度
	df.lfEscapement = 0;					//设置字符旋转角度
	df.lfOrientation=0;
	df.lfWeight = 0;						//设置字符重量,0为默认值
	df.lfItalic = false;					//设置字符是否为斜体
	df.lfUnderline = false;					//设置字符是否有下划线
	df.lfStrikeOut = false;					//设置字体是否有删除线
	df.lfCharSet = m_btCharSet;				//设置字体的字符集
	df.lfOutPrecision = 0;					//设置字体的输出精确度,0为默认
	df.lfClipPrecision = 0;					//设置字体的裁剪精确度,0为默认
	df.lfQuality = 0;						//设置字体的质量,0为默认质量
	df.lfPitchAndFamily = 0 | 0 << 4;		//设置字体的斜率和家族样式

	if(m_cpFaceName.length()>1)
		strcpy(df.lfFaceName,(char*)m_cpFaceName.c_str());
	else
		strcpy(df.lfFaceName,"BatangChe");

	DISPLAY_HANDLE hFont = NULL;
	hFont = m_pDC->CreateFont(df);

	return hFont;
}


void CCharMarkerSymbol::SelectDC(CDC *pDC)
{
		ISymbol::SelectDC(pDC); 

		DISPLAY_HANDLE hFont = SetFont();
		
		if ( hFont == NULL )
		{
			return;
		} 
		else
		{
			m_hFontHandle = CDisplayCache::AddToDisplayCache( hFont , m_pDC );
		}

		//CDisplayCache::UseCache( m_hFontHandle , this );
		m_bCharMapChange = true;
}

void CCharMarkerSymbol::SetReadyDraw()
{
	CDisplayCache::UseCache( m_hFontHandle , this );
}

#define SETPROP(inVal,Val,inName,Name,VT,VT2) if( stricmp(inName,Name) == 0 ) { Val = (VT2)((VT)inVal);return; }
#define SETPROP2(Val,Name,VT) SETPROP( PropertyValue , Val , PropertyName , Name , VT , VT )
#define SETPROP2E(Val,Name,VT,VT2) SETPROP( PropertyValue , Val , PropertyName , Name , VT , VT2 )
void CCharMarkerSymbol::SetProperties(const char* PropertyName , const _variant_t& PropertyValue)
{
	
		SETPROP2( m_cpFaceName , "FACENAME" , _bstr_t );

		if( stricmp( PropertyName , "MARKMAP" ) == 0 ) 
		{
			m_wcMarker = (wchar_t)((unsigned short)(PropertyValue));
			m_bCharMapChange = true;
			return;
		}

		if( stricmp( PropertyName , "CHARSET" ) == 0 ) 
		{ 
			m_btCharSet = (unsigned char)PropertyValue;
			
			return; 
		}
	
		IMarkerSymbol::SetProperties( PropertyName , PropertyValue);

}

#define GETPROP(inName,Name,Val,T) if( stricmp(inName,Name) == 0 ) { vt = (T)Val;return vt; }
#define GETPROP2(Name,Val,T) GETPROP(PropertyName , Name , Val , T )
_variant_t CCharMarkerSymbol::GetProperties(const char* PropertyName)
{

	_variant_t vt;

	GETPROP2( "FACENAME" , m_cpFaceName.c_str() , _variant_t );
	GETPROP2( "CHARSET" , (long)m_btCharSet , _variant_t );
	GETPROP2( "MARKMAP" , m_wcMarker , _variant_t );
	return IMarkerSymbol::GetProperties(PropertyName);
	
}

void CCharMarkerSymbol::Zoom(float rate)
{
		m_fCharWidth *= rate;
		IMarkerSymbol::Zoom(rate);
}

void CCharMarkerSymbol::serialization(SYSTEM::IArchive & ar)
{
	IMarkerSymbol::serialization( ar );

	ar & (m_cpFaceName);		
	ar & (m_btCharSet);	
	ar & m_fCharWidth;
	ar & (m_wcMarker);	
	m_bCharMapChange = true;
	/*ar & (m_lInsideReviseX);				 
	ar & (m_lInsideReviseY);*/			
}

void CCharMarkerSymbol::ClearDC()
{	
	if( m_hFontHandle != NULL)
	{
		CDisplayCache::ReleaseCache( m_hFontHandle );
		m_hFontHandle = NULL;
	}
	IMarkerSymbol::ClearDC();
}

void CCharMarkerSymbol::OnUnitChanged(SYSTEM::SYS_UNIT_TYPE oldUnit , SYSTEM::SYS_UNIT_TYPE newUnit)
{
	IMarkerSymbol::OnUnitChanged(oldUnit , newUnit);

	m_fCharWidth = UnitChangeTo( oldUnit , newUnit , m_fCharWidth );
}

void CCharMarkerSymbol::OnChangingInSelectDC()
{
	m_lCharWidth = UnitChange( m_enumUnit , m_fCharWidth );
	IMarkerSymbol::OnChangingInSelectDC();
}

void CCharMarkerSymbol::SetCharWidth(float width)
{
	m_fCharWidth = width;
}

float CCharMarkerSymbol::GetCharWidth()
{
	return m_fCharWidth;
}

}