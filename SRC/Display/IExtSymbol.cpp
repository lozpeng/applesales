#include "StdAfx.h"
#include "IExtSymbol.h"


namespace Display{
IExtSymbol::IExtSymbol(void)
{
	m_sDescription = "扩展符号";
	m_sSymbolName = "未命名扩展符号";
}

IExtSymbol::~IExtSymbol(void)
{

}

Display::IExtSymbol& Display::IExtSymbol::operator = (const IExtSymbol& extSymbol)
{
		m_sSymbolName = extSymbol.m_sSymbolName;
		m_sDescription = extSymbol.m_sDescription;
		*(ISymbol*)this = *(ISymbol*)&extSymbol;
	return *this;
}

Display::IExtSymbol::IExtSymbol(const IExtSymbol& extSymbol)
{

		*this = extSymbol;	

}

bool IExtSymbol::ValidatePropValueAndGetInfo(Geodatabase::ICursorPtr pCursor , CPropRecordIndexGroup &exchangInfo)
{
	return false;
}

//void IExtSymbol::SetPropValue(void *propValueStream)
//{
//
//}

const std::string IExtSymbol::GetDescription()
{
	return m_sDescription;
}

const std::string IExtSymbol::GetSymbolName()
{
	return m_sSymbolName;
}

void IExtSymbol::ClearDC()
{
	ISymbol::ClearDC();
}

void IExtSymbol::OnUnitChanged(SYSTEM::SYS_UNIT_TYPE oldUnit , SYSTEM::SYS_UNIT_TYPE newUnit)
{
	ISymbol::OnUnitChanged(oldUnit , newUnit);
	//实现
}

void IExtSymbol::OnChangingInSelectDC()
{
	//实现
	ISymbol::OnChangingInSelectDC();
}

void IExtSymbol::serialization(SYSTEM::IArchive & ar)
{
	ISymbol::serialization(ar);
	ar & m_sSymbolName;
	ar & m_sDescription;
}

#define SETPROP(inVal,Val,inName,Name,VT) if( stricmp(inName,Name) == 0 ) { Val = (VT)inVal;return; }
#define SETPROP2(Val,Name,VT) SETPROP( PropertyValue , Val , PropertyName , Name , VT )
void IExtSymbol::SetProperties(const char* PropertyName , const _variant_t& PropertyValue)
{
	if( stricmp(PropertyName , "EXTSYMBOLNAME") == 0 ) 
	{
		m_sSymbolName = (_bstr_t)PropertyValue;
		return;
	}

	if( stricmp(PropertyName , "EXTSYMBOLDESCRIPTION") == 0 ) 
	{
		m_sDescription=(_bstr_t)PropertyValue;
		return;
	}

	ISymbol::SetProperties(PropertyName , PropertyValue);
}

#define GETPROP(inName,Name,Val,T) if( stricmp(inName,Name) == 0 ) { vt = (T)Val;return vt; }
#define GETPROP2(Name,Val,T) GETPROP(PropertyName , Name , Val , T )
_variant_t IExtSymbol::GetProperties(const char* PropertyName)
{
	_variant_t vt;
	GETPROP2( "EXTSYMBOLNAME" , m_sSymbolName.c_str() , _variant_t );
	GETPROP2( "EXTSYMBOLDESCRIPTION" , m_sDescription.c_str() , _variant_t );

	return ISymbol::GetProperties(PropertyName);
}

void IExtSymbol::SelectDC(Display::CDC *pDC)
{
	ISymbol::SelectDC(pDC);
}

void IExtSymbol::Zoom(float rate)
{
	ISymbol::Zoom(rate);
}
}