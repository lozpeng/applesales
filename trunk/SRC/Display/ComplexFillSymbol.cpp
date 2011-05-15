#include "StdAfx.h"
#include "ComplexFillSymbol.h"
#include "SymbolFactory.h"

Display::CComplexFillSymbol::CComplexFillSymbol()
{

}

Display::CComplexFillSymbol::CComplexFillSymbol(const Display::CComplexFillSymbol& ComplexFillSymbol)
{
	*this = ComplexFillSymbol;
}

Display::CComplexFillSymbol& Display::CComplexFillSymbol::operator = (const CComplexFillSymbol & ComplexFillSymbol)
{
		if( this == &ComplexFillSymbol )
			return *this;

		*(IFillSymbol*)this			=		*(IFillSymbol*)&ComplexFillSymbol;
		*(IComplexSymbol*)this		=		*(IComplexSymbol*)&ComplexFillSymbol;
		return *this;
}

Display::CComplexFillSymbol::~CComplexFillSymbol()
{
		ClearDC();
}
 
void Display::CComplexFillSymbol::Draw(void* pObject)
{

		for( int i = m_arrayGroup->GetSize() - 1 ; i >= 0 ; i-- )
		{
			if( m_arrayView.GetAt(i) )
			{
				ISymbolPtr pFill = m_arrayGroup->GetAt(i);

				pFill->SetReadyDraw();							//选择绘制对象
				pFill->Draw(pObject);							//实现绘制
			}
		}

}

SYMBOL_TYPE Display::CComplexFillSymbol::GetType()
{
	return COMPLEX_FILL_SYMBOL;
}

void Display::CComplexFillSymbol::SelectDC(Display::CDC *pDC)
{

		ISymbol::SelectDC( pDC );

		for( int i = 0 ; i < m_arrayGroup->GetSize() ; i++ )						//为每一个点符号装入CDC
		{
			ISymbolPtr pFill = m_arrayGroup->GetAt(i);
			pFill->SelectDC(m_pDC);
		}

}

bool Display::CComplexFillSymbol::Add(ISymbolPtr symbol)
{
		if (symbol == NULL)
			return false;
		if ( !( symbol->GetType() & FILL_SYMBOL ))
			return false;

		m_arrayGroup->Add(symbol);
		m_arrayLock.Add(false);
		m_arrayView.Add(true);

		IFillSymbolPtr fillSymbol = symbol;
		if (fillSymbol != NULL)
			this->m_lColor = fillSymbol->GetFillColor();	//2006.11.2 张维添加
	
	return true;
}

bool Display::CComplexFillSymbol::SetSymbol( int index , ISymbolPtr symbol )
{
	if ( (!( symbol->GetType() & FILL_SYMBOL )) || index < 0 )
		return false;

	m_arrayGroup->SetAt( index , symbol );
	return true;
}

void Display::CComplexFillSymbol::SetOutLine(ILineSymbolPtr mOutLine)	
{

		for( int i = 0 ; i < m_arrayGroup->GetSize() ; i++ )						
		{
			IFillSymbolPtr pFill = m_arrayGroup->GetAt(i);
			if (pFill == NULL)
				continue;
			pFill->SetOutLineSymbol(mOutLine);
		}

}

void Display::CComplexFillSymbol::SetbOutLine(bool bline)	
{

		for( int i = 0 ; i < m_arrayGroup->GetSize() ; i++ )						
		{
			IFillSymbolPtr pFill = m_arrayGroup->GetAt(i);
			if (pFill == NULL)
				continue;
			pFill->SetDrawOutLine(bline);
		}
}

void Display::CComplexFillSymbol::SetFillColor(unsigned long lColor)
{

		for( int i = 0 ; i < m_arrayGroup->GetSize() ; i++ )						
		{
			if( m_arrayLock.GetAt(i) )
				continue;

			IFillSymbolPtr pFill = m_arrayGroup->GetAt(i);
			if (pFill == NULL)
				m_arrayGroup->GetAt(i)->SetColor(lColor);
			else
				pFill->SetFillColor(lColor);
		}

}


void Display::CComplexFillSymbol::SetOutLineColor(unsigned long lColor)
{

		for( int i = 0 ; i < m_arrayGroup->GetSize() ; i++ )						
		{
			IFillSymbolPtr pFill = m_arrayGroup->GetAt(i);
			if (pFill == NULL)
				continue;
			pFill->SetOutLineColor(lColor);
		}

}
void Display::CComplexFillSymbol::SetOutLineWidth(unsigned long size)
{

		for( int i = 0 ; i < m_arrayGroup->GetSize() ; i++ )						
		{
			IFillSymbolPtr pFill = m_arrayGroup->GetAt(i);
			if (pFill == NULL)
				continue;
			pFill->SetOutLineWidth(size);
		}

}

bool Display::CComplexFillSymbol::Insert( int index , ISymbolPtr symbol , bool state )
{
	if (symbol == NULL)
		return false;
	if ( !(symbol->GetType() & FILL_SYMBOL)  || index <0)
		return false;

	m_arrayGroup->InsertAt( index , symbol );
	m_arrayLock.InsertAt( index , false );
	m_arrayView.InsertAt( index , state );	

	IFillSymbolPtr fillSymbol = symbol;
	if (fillSymbol != NULL)
		this->m_lColor = fillSymbol->GetFillColor();	//2006.11.2 张维添加
	return true;
}

void Display::CComplexFillSymbol::Zoom(float rate)
{
		for( int i = 0 ; i < GetSize() ; i++ )
		{
			GetAt(i)->Zoom(rate);
		}
}

void Display::CComplexFillSymbol::serialization(SYSTEM::IArchive & ar)
{ 
	ISymbol::serialization(ar); 

	IComplexSymbol::serialization( ar );
}

void Display::CComplexFillSymbol::DrawLegend( DIS_RECT * rect , int nFlag )
{
	IComplexSymbol::DrawLegend( rect , nFlag );
}

void Display::CComplexFillSymbol::SetProperties( const char* PropertyName , const _variant_t& PropertyValue)
{
//	DEBUG(false);
}

_variant_t Display::CComplexFillSymbol::GetProperties(const char* PropertyName)
{
//	DEBUG(false);
	return 0;
}

void Display::CComplexFillSymbol::OnUnitChanged(SYSTEM::SYS_UNIT_TYPE oldUnit , SYSTEM::SYS_UNIT_TYPE newUnit)
{
	for( int i = 0 ; i < this->GetSize() ; i++ )
	{
		this->GetAt(i)->SetUnit(newUnit);
	}
	IFillSymbol::OnUnitChanged(oldUnit , newUnit);
}

void Display::CComplexFillSymbol::OnChangingInSelectDC()
{
	IFillSymbol::OnChangingInSelectDC();
	IComplexSymbol::OnChangingInSelectDC();
}

void Display::CComplexFillSymbol::ClearDC()
{
	IComplexSymbol::ClearDC();
	IFillSymbol::ClearDC();
}