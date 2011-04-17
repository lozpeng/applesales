#include "stdafx.h"
#include "ISymbol.h"
#include "CDC.h"
#include "ILineSymbol.h"
#include "IMarkerSymbol.h"
#include "IFillSymbol.h"
#include "TextSymbol.h"
#include "SymbolFactory.h"

namespace Display
{

	ISymbol::ISymbol()
	{
		m_lID=0;									//ID�ų�ʼΪ��
		m_strLabel = "Symbol";
		m_pDC=0;									//����ָ���声
		m_lColor = RGB((((double) rand() / (double) 255) * 255 + 0) , (((double) rand() / (double) 255) * 255 + 0),
			(((double) rand() / (double) 255) * 255 + 0));
		m_enumUnit = SYSTEM::SYS_UNIT_POINT;
	}

	ISymbol::ISymbol(const ISymbol& Symbol)
	{
		*this = Symbol;	
	}

	ISymbol::~ISymbol()
	{
	}

	long ISymbol::GetID()
{
	return m_lID;
}

/**
* ����ID��
* @param lID ���ű�ʶ
*/
void ISymbol::SetID(long lID)
{
	m_lID = lID;
}

/**
* �õ����ž��
* @return ��÷��ž��
*/
std::string ISymbol::GetLabel()
{
	return m_strLabel;
}

/**
* ���÷��ž��
* @param strLabel ���ž��
*/
void ISymbol::SetLabel(const char* strLabel)
{
	m_strLabel = strLabel;
}

/** 
* ����һ������
* @return �����Ƴɹ��򷵻�һ������
*/
ISymbolPtr ISymbol::Clone()
{
	ISymbolPtr pSym;
	SYSTEM::CBinArchive ar;

	serialization( ar );
	ar.SetReadState();
	ar.SetPosToBegin();
	pSym = CSymbolFactory::CreateSymbolFromStream( ar );

	return pSym;
}

/**
* �����ɫֵ
* @return ������ɫֵ
*/
COLORREF ISymbol::GetColor()
{
	
	return RGB(0 ,0 ,0);
}

/**
* ������ɫֵ
* @param color ��ɫֵ
*/
void ISymbol::SetColor( COLORREF color )
{
	if (color == SetNoColor)
	{
		color = m_lColor | 0xff000000;
	}
	else if (color == SetHasColor)
	{
		color = m_lColor & 0x00ffffff; 
	}
	if (this->GetType() & EXT_SYMBOL)
	{
		m_lColor = color;
		return;
	}

	if ( this->GetType() & MARKER_SYMBOL || ((this->GetType() & COMPLEX_SYMBOL) == COMPLEX_MARKER_SYMBOL) )//���ǵ����
	{
		(dynamic_cast<IMarkerSymbol*>(this))->SetMarkerColor(color);
	}
	else if ( this->GetType() & LINE_SYMBOL || ((this->GetType() & COMPLEX_SYMBOL) == COMPLEX_LINE_SYMBOL) )//�����߷���
	{
		(dynamic_cast<ILineSymbol*>(this))->SetLineColor(color);
	}
	else if ( this->GetType() & FILL_SYMBOL || ((this->GetType() & COMPLEX_SYMBOL) == COMPLEX_FILL_SYMBOL) )//���������
	{
		(dynamic_cast<IFillSymbol*>(this))->SetFillColor(color);
	}
	else if ( this->GetType() & TEXT_SYMBOL)//�������ַ���
	{
		(dynamic_cast<CTextSymbol*>(this))->SetTextColor(color);
	}
}

/**
* ��÷��ŵ�λ
* @return ���ط��ŵ�λ
*/
SYSTEM::SYS_UNIT_TYPE ISymbol::GetUnit()
{
	return m_enumUnit;
}

/**
* ���÷��ŵ�λ
* @param SYS_UNIT_TYPE ���ŵ�λ
*/
void ISymbol::SetUnit(SYSTEM::SYS_UNIT_TYPE  unitType)
{
	OnUnitChanged( m_enumUnit , unitType);
	m_enumUnit = unitType;
}

/**
* �ⲿ���ã�����һ��ԭʼֵ�����Ŀ�굥λ��Ӧ��ֵ
* @param valUnit
* @param aimUnit
* @param float val
*/
float ISymbol::UnitChangeTo(SYSTEM::SYS_UNIT_TYPE valUnit , SYSTEM::SYS_UNIT_TYPE aimUnit , float val)
{
	return 0;
}

/**
* ��SelectDC�е��ã���floatֵת��Ϊlong��ֵ
* @param Unit ��λ
* @param Val
*/
long ISymbol::UnitChange( SYSTEM::SYS_UNIT_TYPE Unit , float Val )
{
	if ( Unit == SYSTEM::SYS_UNIT_PIXEL )
	{
		return (long)( Val + 0.5 );
	}

	float rate = GetRateOfPixelAndMM();

	if ( Unit == SYSTEM::SYS_UNIT_MILLIMETER )
	{
		return (Val / rate + 0.5);
	}
	else if ( Unit == SYSTEM::SYS_UNIT_CENTIMETER )
	{
		return (long)((Val * (int)SYSTEM::SYS_UNIT_CENTIMETER / rate) + 0.5);
	}
	else if ( Unit == SYSTEM::SYS_UNIT_DECIMETER )
	{
		return (long)((Val * (int)SYSTEM::SYS_UNIT_DECIMETER / rate) + 0.5);
	}
	else if ( Unit == SYSTEM::SYS_UNIT_POINT)
	{
		return ( Val / 2.83464576 / rate + 0.5);
	}

	return 0;
}



float ISymbol::GetRateOfPixelAndMM()
{
	float rate = 0.000000f;
	if ( m_pDC != NULL )
	{
		rate = m_pDC->GetRateValueOfPixelAndMillimeter();
		if (rate == 0.000000f)
		{
			rate = Display::CDC::GetCreateDCsRateOfPixelAndMillimeter();
		}
	}
	else
	{
		rate = CDC::GetCreateDCsRateOfPixelAndMillimeter();
	}

	return rate;
}

void ISymbol::SetProperties(const char* PropertyName,const _variant_t& PropertyValue)
{
#define SETPROP(inVal,Val,inName,Name,VT) if( stricmp(inName,Name) == 0 ) { Val = (VT)inVal;return; }
#define SETPROP2(Val,Name,VT) SETPROP( PropertyValue , Val , PropertyName , Name , VT )

	SETPROP2(m_lID,"SYMBOLID",long);
	SETPROP2(m_strLabel,"SYMBOLLABEL", _bstr_t );
}

_variant_t ISymbol::GetProperties(const char* PropertyName)
{
	_variant_t vt;
#define GETPROP(inName,Name,Val,T) if( stricmp(inName,Name) == 0 ) { vt = (T)Val;return vt; }
#define GETPROP2(Name,Val,T) GETPROP(PropertyName , Name , Val , T )
	

	GETPROP2( "SYMBOLID" , m_lID , _variant_t );
	GETPROP2( "SYMBOLLABEL" , m_strLabel.c_str() , _variant_t );

	return 0;
}

void ISymbol::serialization(SYSTEM::IArchive &ar)
{ 
	//ISerialization::serialization( ar); 

	//long Type = (long)GetType();

	//ar & Type;

	//ar & m_lID;

	//ar & m_strLabel;

	//ar & m_lColor;

	//if(ar.IsSave() )
	//{
	//	int i = m_enumUnit;
	//	ar & (i);
	//}
	//else
	//{
	//	int i;
	//	ar & i;
	//	m_enumUnit = (SYSTEM::SYS_UNIT_TYPE)i;
	//}
}

void ISymbol::OnUnitChanged(SYSTEM::SYS_UNIT_TYPE oldUnit , SYSTEM::SYS_UNIT_TYPE newUnit) 
{
}


void ISymbol::OnChangingInSelectDC() 
{

}


void ISymbol::ClearDC()
{
	m_pDC = NULL;
}

void ISymbol::SelectDC(CDC *pDC)
{

		m_pDC = pDC;
		OnChangingInSelectDC();
}

void ISymbol::Zoom(float rate)
{
}
}