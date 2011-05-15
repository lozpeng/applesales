#include "stdafx.h"
#include "ComplexLineSymbol.h"
#include "SymbolFactory.h"

using namespace Display;

Display::CComplexLineSymbol::CComplexLineSymbol()
{
	
}

Display::CComplexLineSymbol::~CComplexLineSymbol()
{

}

Display::CComplexLineSymbol::CComplexLineSymbol(const CComplexLineSymbol& ComplexLineSymbol)
{
	*this = ComplexLineSymbol;
}

Display::CComplexLineSymbol& Display::CComplexLineSymbol::operator = (const CComplexLineSymbol & ComplexLineSymbol)
{

		
		if(this == &ComplexLineSymbol)
			return *this;

		*(ILineSymbol*)this			=		*(ILineSymbol*)&ComplexLineSymbol;
		*(IComplexSymbol*)this		=		*(IComplexSymbol*)&ComplexLineSymbol;

		return *this;
}

void Display::CComplexLineSymbol::Draw(void* pObject)
{

		for( int i = m_arrayGroup->GetSize() - 1 ; i >= 0; i-- )
		{
			if( m_arrayView.GetAt(i) )
			{
				ISymbolPtr pLine = m_arrayGroup->GetAt(i);

				pLine->SetReadyDraw();									//选择绘制对象
				pLine->Draw(pObject);									//实现绘制
			}
		}

}

SYMBOL_TYPE Display::CComplexLineSymbol::GetType()
{
	return COMPLEX_LINE_SYMBOL;
}

void Display::CComplexLineSymbol::SelectDC(Display::CDC *pDC)
{

		ISymbol::SelectDC( pDC );

	for( int i = 0 ; i < m_arrayGroup->GetSize() ; i++ )						//为每一个线符号装入CDC
	{
		ISymbolPtr pLine = m_arrayGroup->GetAt(i);
		pLine->SelectDC(m_pDC);
	} 

}
bool Display::CComplexLineSymbol::Add(ISymbolPtr symbol)
{
		if (symbol == NULL)
			return false;
		if ( !(symbol->GetType() & LINE_SYMBOL) )
			return false;

		m_arrayGroup->Add(symbol);
		m_arrayLock.Add(false);
		m_arrayView.Add(true);

		ILineSymbolPtr lineSymbol = symbol;
		if (lineSymbol != NULL)
		{
			this->m_lColor = lineSymbol->GetLineColor();	
			this->m_fLineWidth = lineSymbol->GetLineWidth();
			this->m_fOffsetX = lineSymbol->GetOffsetX();
			this->m_fOffsetY = lineSymbol->GetOffsetY();
			this->m_enumUnit = lineSymbol->GetUnit();
		}

		return true;
}

bool Display::CComplexLineSymbol::SetSymbol( int index , ISymbolPtr symbol )
{
	if (symbol == NULL)
		return false;
	if ( (!(symbol->GetType() & LINE_SYMBOL)) || index < 0 )
		return false;

	m_arrayGroup->SetAt( index , symbol );
	return true;
}

void Display::CComplexLineSymbol::SetLineWidth(float nWidth)
{
		for( int i = 0 ; i < m_arrayGroup->GetSize() ; i++ )						
		{
			ILineSymbolPtr pLine = m_arrayGroup->GetAt(i);
			if (pLine == NULL)
				continue;
			pLine->SetLineWidth(nWidth);
		}

}

float Display::CComplexLineSymbol::GetLineWidth()
{
	long minY = 0 , maxY = 0;
	float lineWidth = 0;


		long offsetY = 0;

		for( int i = 0 ; i < m_arrayGroup->GetSize() ; i++ )
		{
			ILineSymbolPtr lineSymbol = m_arrayGroup->GetAt(i);
			if (lineSymbol == NULL)
				continue;
			unsigned long tempMaxValue = 0;
			
			if(lineSymbol->GetType() == HASH_LINE_SYMBOL )
			{
				tempMaxValue = 1;
			}
			else
				tempMaxValue =lineSymbol->GetLineWidth() / 2;	//得到线宽的一半

			offsetY = lineSymbol->GetOffsetY();

			if( offsetY < 0 )
			{
				long tempMinY = offsetY - tempMaxValue;

				if( minY > tempMinY )
					minY = tempMinY;
			}
			else
			{
				long tempMaxY = offsetY + tempMaxValue;
				if( maxY < tempMaxY )
					maxY = tempMaxY;
			}
		}

		lineWidth = -minY + maxY;

		return lineWidth;
}

void Display::CComplexLineSymbol::SetLineColor(unsigned long lColor)
{

		for( int i = 0 ; i < m_arrayGroup->GetSize() ; i++ )						
		{
			if( m_arrayLock.GetAt(i) )
				continue;

			ILineSymbolPtr pLine = m_arrayGroup->GetAt(i);
			if (pLine == NULL)
				m_arrayGroup->GetAt(i)->SetColor(lColor);
			else
				pLine->SetLineColor(lColor);
		}

}

void Display::CComplexLineSymbol::SetOffset( float x , float y )
{

		for( int i = 0 ; i < m_arrayGroup->GetSize() ; i++ )						
		{
			ILineSymbolPtr pLine = m_arrayGroup->GetAt(i);
			if (pLine == NULL)
				continue;
			pLine->SetOffset( x , y );
		}
}
bool Display::CComplexLineSymbol::Insert( int index , ISymbolPtr symbol , bool state )
{
	if (symbol == NULL)
		return false;
	if ( !( symbol->GetType() & LINE_SYMBOL)  || index < 0 )
		return false;

	m_arrayGroup->InsertAt( index , symbol );
	m_arrayLock.InsertAt( index , false );
	m_arrayView.InsertAt( index , state );

	ILineSymbolPtr lineSymbol = symbol;
	if (lineSymbol != NULL)
	{
		this->m_lColor = lineSymbol->GetLineColor();	
		this->m_fLineWidth = lineSymbol->GetLineWidth();
		this->m_fOffsetX = lineSymbol->GetOffsetX();
		this->m_fOffsetY = lineSymbol->GetOffsetY();
		this->m_enumUnit = lineSymbol->GetUnit();
	}
	
	return true;

}

void Display::CComplexLineSymbol::Zoom(float rate)
{

		for( int i = 0 ; i < this->GetSize() ; i++ )
		{
			this->GetAt(i)->Zoom(rate);
		}

}

void Display::CComplexLineSymbol::serialization(SYSTEM::IArchive & ar)
{ 
	ILineSymbol::serialization( ar ); 

	IComplexSymbol::serialization( ar );
}

void Display::CComplexLineSymbol::DrawLegend( DIS_RECT * rect , int nFlag )
{	
	IComplexSymbol::DrawLegend( rect , nFlag );
}

void Display::CComplexLineSymbol::SetProperties( const char* PropertyName , const _variant_t& PropertyValue )
{
//	DEBUG(false);
}

_variant_t Display::CComplexLineSymbol::GetProperties(const char* PropertyName)
{
//	DEBUG(false);
	return 0;
}

void Display::CComplexLineSymbol::OnUnitChanged(SYSTEM::SYS_UNIT_TYPE oldUnit , SYSTEM::SYS_UNIT_TYPE newUnit)
{
	for( int i = 0 ; i < this->GetSize() ; i++ )
	{
		this->GetAt(i)->SetUnit(newUnit);
	}
	ILineSymbol::OnUnitChanged(oldUnit , newUnit);
}

void Display::CComplexLineSymbol::OnChangingInSelectDC()
{
	ILineSymbol::OnChangingInSelectDC();
	IComplexSymbol::OnChangingInSelectDC();
}

void Display::CComplexLineSymbol::ClearDC()
{
	IComplexSymbol::ClearDC();
	ILineSymbol::ClearDC();
}