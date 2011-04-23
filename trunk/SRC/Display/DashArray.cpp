#include "stdafx.h"
#include "DisplayHeader.h"
#include "DashArray.h"
#include "IArchive.h"
#include "SymbolFactory.h"

Display::CDashArray::CDashArray(Display::ISymbolPtr symbol)
{
	m_lCount = 0;
	m_enumUnit = symbol->GetUnit();
	m_pSymbol = symbol;
}

Display::CDashArray::CDashArray()
{
	m_lCount = 0;
	m_enumUnit = SYSTEM::SYS_UNIT_MILLIMETER;
	m_pSymbol = NULL;
}

Display::CDashArray::~CDashArray()
{
}

Display::CDashArray::CDashArray(const Display::CDashArray& toDashArray)
{
	*this = toDashArray;
}

//Display::CDashArray& Display::CDashArray::operator = (const Display::CDashArray & toDashArray)
//{
//	if(this == &toDashArray)
//		return *this;
//
//	m_lCount = toDashArray.m_lCount;
//	m_dashArray.clear();
//	m_dashArray.Copy(toDashArray.m_dashArray);
//	m_lDashArray.clear();
//	m_lDashArray.Copy(toDashArray.m_lDashArray);
//	m_enumUnit = toDashArray.m_enumUnit;
//	m_pSymbol = toDashArray.m_pSymbol;
//	return *this;
//}

void Display::CDashArray::SetDashGroupCount(unsigned long lCount)
{
	m_lCount = lCount;
}

unsigned long Display::CDashArray::GetDashGroupCount()
{
	return m_lCount;
}

void Display::CDashArray::AddDash(float lData)
{
	if (m_pSymbol == NULL)
	{
		return;
	}
	m_dashArray.push_back(lData);
	m_lDashArray.push_back((unsigned long)m_pSymbol->UnitChange(m_enumUnit , lData));
}

float Display::CDashArray::GetDash(unsigned long lIndex)
{
	return m_dashArray[lIndex];
}

void Display::CDashArray::RemoveDash(unsigned long lIndex)
{
	std::vector<float>::iterator it;
	int nIndex = 0;
	it = m_dashArray.begin();

	m_dashArray.erase(it+nIndex);

	std::vector<unsigned long>::iterator itL;
	m_lDashArray.erase(itL+lIndex);
}

int Display::CDashArray::GetDashSize()
{
	return m_dashArray.size();
}

unsigned long* Display::CDashArray::GetData()
{
	return &m_lDashArray[0];
	//return m_lDashArray.GetData();
}

void Display::CDashArray::SetDash(float lData , unsigned long lIndex)
{
	if (m_pSymbol == NULL)
	{
		return;
	}
	if((lIndex) >= (unsigned long)(m_dashArray.size()))
	{
		return;
	}
	m_dashArray[lIndex] = lData;
	m_lDashArray[lIndex] = (unsigned long)m_pSymbol->UnitChange(m_enumUnit , lData);
}

void Display::CDashArray::serialization(SYSTEM::IArchive &ar)
{ 
	ISerialization::serialization( ar ); 

	ar & m_lCount;
	long lCount = m_dashArray.size();
	ar & lCount;

	if( ar.IsSave() )
	{
		int i = (int)m_enumUnit;
		ar & (i);

		for ( long i = 0 ; i < lCount ; ++i )
		{	
			ar & m_dashArray[i];
		}

		for ( long i = 0 ; i < lCount ; ++i )
		{	
			ar & m_lDashArray[i];
		}

		int  type = m_pSymbol->GetType();
		ar & (type);
	}
	else
	{
		int i;
		ar & i;
		m_enumUnit = (SYSTEM::SYS_UNIT_TYPE)i;

		float data = 0;
		m_dashArray.clear();
		for ( long i = 0 ; i < lCount ; ++i )
		{	
			ar & data;
			m_dashArray.push_back(data);
		}

		unsigned long lData = 0;
		m_lDashArray.clear();
		for ( long i = 0 ; i < lCount ; ++i )
		{	
			ar & lData;
			m_lDashArray.push_back(lData);
		}

		int type;
		ar & (type);
		m_pSymbol = CSymbolFactory::CreateSymbol( (SYMBOL_TYPE)type );
	}
}

SYSTEM::SYS_UNIT_TYPE Display::CDashArray::GetUnit()
{
	return m_enumUnit;
}