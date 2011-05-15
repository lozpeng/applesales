#include "stdafx.h"
#include "SymbolFactory.h"
#include "ComplexMarkerSymbol.h"
//#include "CDC.h"
#include "SimpleMarkerSymbol.h"
#include "IExtSymbol.h"

Display::CComplexMarkerSymbol::CComplexMarkerSymbol()
{
	m_fCurrentMarkerAngle=0.0000l;
}

Display::CComplexMarkerSymbol::CComplexMarkerSymbol(const CComplexMarkerSymbol& ComplexMarkSymbol)
{
	*this = ComplexMarkSymbol;
}

Display::CComplexMarkerSymbol& Display::CComplexMarkerSymbol::operator = (const CComplexMarkerSymbol & ComplexMarkerSymbol)
{
		if(this == &ComplexMarkerSymbol)
			return *this;

		this->m_fCurrentMarkerAngle   =		ComplexMarkerSymbol.m_fCurrentMarkerAngle;

		*(IMarkerSymbol*)this			=		*(IMarkerSymbol*)&ComplexMarkerSymbol;
		*(IComplexSymbol*)this		=		*(IComplexSymbol*)&ComplexMarkerSymbol;
		return *this;
}

Display::CComplexMarkerSymbol::~CComplexMarkerSymbol()
{

}

void Display::CComplexMarkerSymbol::Draw(void* pObject)
{
		for( int i = m_arrayGroup->GetSize() - 1 ; i >= 0 ; i-- )
		{		
			if( m_arrayView.GetAt(i) )
			{
				ISymbolPtr pMark = m_arrayGroup->GetAt(i);

				pMark->SetReadyDraw();							//选择绘制对象
				pMark->Draw(pObject);							//实现绘制
			}
		}

}

SYMBOL_TYPE Display::CComplexMarkerSymbol::GetType()
{
	return COMPLEX_MARKER_SYMBOL;
}

void Display::CComplexMarkerSymbol::SelectDC(CDC *pDC)
{
		ISymbol::SelectDC( pDC );

		for( int i = 0;i < m_arrayGroup->GetSize() ; i++ )						//为每一个点符号装入CDC
		{
			ISymbolPtr pMark = m_arrayGroup->GetAt(i);		
			pMark->SelectDC(m_pDC);
		}
}

bool Display::CComplexMarkerSymbol::Add(ISymbolPtr symbol)
{
		if (symbol == NULL)
			return false;
		if ( !( symbol->GetType() & MARKER_SYMBOL ) )
			return false;

		m_arrayGroup->Add(symbol);
		m_arrayLock.Add(false);
		m_arrayView.Add(true);

		IMarkerSymbolPtr toMarkerSymbol = symbol;
		if (toMarkerSymbol != NULL)
		{
			this->m_fAngle = toMarkerSymbol->GetAngle();	
			this->m_lColor = toMarkerSymbol->GetMarkColor();
			this->m_fMarkerSize = toMarkerSymbol->GetMarkerSize();
			this->m_fOffsetX = toMarkerSymbol->GetOffsetX();
			this->m_fOffsetY = toMarkerSymbol->GetOffsetY();
			this->m_enumUnit = toMarkerSymbol->GetUnit();
		}
		
		return true;
}

bool Display::CComplexMarkerSymbol::SetSymbol( int index , ISymbolPtr symbol )
{
	if (symbol == NULL)
		return false;
	if ( (!( symbol->GetType() & MARKER_SYMBOL )) || index < 0 )
		return false;

	m_arrayGroup->SetAt( index , symbol );
	return true;
}

void Display::CComplexMarkerSymbol::SetOffSet( float x , float y )
{


		for( int i = 0 ; i < m_arrayGroup->GetSize() ; i++ )						
		{
			IMarkerSymbolPtr pMark = m_arrayGroup->GetAt(i);
			if (pMark == NULL)
				continue;
			pMark->SetOffSet(x,y);
		}

}

void Display::CComplexMarkerSymbol::SetAngle(float fAngle)	
{
	
		float fMargin = fAngle - m_fCurrentMarkerAngle;

		for( int i = 0 ; i < m_arrayGroup->GetSize() ; i++ )						
		{
			IMarkerSymbolPtr pMark = m_arrayGroup->GetAt(i);
			if (pMark == NULL)
				continue;
			pMark->SetAngle(fMargin + pMark->GetAngle());
		}

		m_fCurrentMarkerAngle = fAngle;

}

void Display::CComplexMarkerSymbol::SetMarkerSize(float marksize)		
{

		for( int i = 0 ; i < m_arrayGroup->GetSize() ; i++ )						
		{
			IMarkerSymbolPtr pMark = m_arrayGroup->GetAt(i);
			if (pMark == NULL)
				continue;
			pMark->SetMarkerSize(marksize);
		}

}

void Display::CComplexMarkerSymbol::SetMaskDrawable(bool bMask)
{
		for( int i = 0 ; i < m_arrayGroup->GetSize() ; i++ )						
		{
			IMarkerSymbolPtr pMark = m_arrayGroup->GetAt(i);
			if (pMark == NULL)
				continue;
			pMark->SetMaskDrawable(bMask);
		}

}

void Display::CComplexMarkerSymbol::SetMask(ISymbolPtr pSymbolMask)
{
		for( int i = 0 ; i < m_arrayGroup->GetSize() ; i++ )						
		{
			IMarkerSymbolPtr pMark = m_arrayGroup->GetAt(i);
			if (pMark == NULL)
				continue;
			//	pMark->SetMask(pSymbolMask);
		}

}

void Display::CComplexMarkerSymbol::SetMarkerColor(unsigned long lColor)
{


		for( int i = 0 ; i < m_arrayGroup->GetSize() ; i++ )						
		{
			if( m_arrayLock.GetAt(i) )
				continue;

			IMarkerSymbolPtr pMark = m_arrayGroup->GetAt(i);
			if (pMark == NULL)
				m_arrayGroup->GetAt(i)->SetColor(lColor);
			else
				pMark->SetMarkerColor(lColor);
		}

}

bool Display::CComplexMarkerSymbol::Insert( int index , ISymbolPtr symbol , bool state )
{
		if (symbol == NULL)
			return false;
		if ( !( symbol->GetType() & MARKER_SYMBOL )  ||  index < 0 )
			return false;

		m_arrayGroup->InsertAt( index , symbol );
		m_arrayLock.InsertAt( index , false );
		m_arrayView.InsertAt( index , state );

		IMarkerSymbolPtr toMarkerSymbol = symbol;
		if (toMarkerSymbol != NULL)
		{
			this->m_fAngle = toMarkerSymbol->GetAngle();	
			this->m_lColor = toMarkerSymbol->GetMarkColor();
			this->m_fMarkerSize = toMarkerSymbol->GetMarkerSize();
			this->m_fOffsetX = toMarkerSymbol->GetOffsetX();
			this->m_fOffsetY = toMarkerSymbol->GetOffsetY();
			this->m_enumUnit = toMarkerSymbol->GetUnit();
		}
		
		return true;
}

void Display::CComplexMarkerSymbol::Zoom(float rate)
{
		for( int i = 0 ; i < this->GetSize() ; i++ )
		{
			this->GetAt(i)->Zoom(rate);
		}

}


float Display::CComplexMarkerSymbol::GetMarkerSize()
{
	float maxValue = 0.000000f;
		float offsetX = 0.000000f , offsetY = 0.000000f;

		for(int i = 0;i < m_arrayGroup->GetSize() ; i++ )
		{
			IMarkerSymbolPtr markSymbol = m_arrayGroup->GetAt(i);
			if (markSymbol != NULL)
			{	
				float tempMaxValue =markSymbol->GetMarkerSize();

				offsetX = abs(markSymbol->GetOffsetX());
				offsetY = abs(markSymbol->GetOffsetY());

				if( offsetX >= offsetY )
					tempMaxValue = tempMaxValue + offsetX;
				else
					tempMaxValue = tempMaxValue + offsetY;
				
				if( markSymbol->GetType() == SIMPLE_MARKER_SYMBOL )
				{
					CSimpleMarkerSymbolPtr simpleMarkSymbol = markSymbol;
					unsigned long tempOutLineWidth =simpleMarkSymbol->GetOutLineWidth();
					tempMaxValue=tempMaxValue + (tempOutLineWidth >> 1);
				}

				if( maxValue < tempMaxValue )
					maxValue = tempMaxValue;
			}
			else
			{
				IExtSymbolPtr extSymbol = m_arrayGroup->GetAt(i);
				_variant_t size = extSymbol->GetProperties("SYMBOLSIZE");
				float tempMaxValue = (float)size;

				if( maxValue < tempMaxValue )
					maxValue = tempMaxValue;
			}
		}

		return maxValue;

}

void Display::CComplexMarkerSymbol::serialization(SYSTEM::IArchive & ar)
{ 
	IMarkerSymbol::serialization( ar ); 

	IComplexSymbol::serialization( ar );

	ar & m_fCurrentMarkerAngle;
}

void Display::CComplexMarkerSymbol::DrawLegend( DIS_RECT * rect , int nFlag )
{
	IComplexSymbol::DrawLegend( rect , nFlag );
}

void Display::CComplexMarkerSymbol::SetProperties( const char* PropertyName , const _variant_t& PropertyValue )
{
//	DEBUG(false);
}

_variant_t Display::CComplexMarkerSymbol::GetProperties(const char* PropertyName)
{
//	DEBUG(false);
	return 0;
}

void Display::CComplexMarkerSymbol::OnUnitChanged(SYSTEM::SYS_UNIT_TYPE oldUnit , SYSTEM::SYS_UNIT_TYPE newUnit)
{
	for( int i = 0 ; i < this->GetSize() ; i++ )
	{
		this->GetAt(i)->SetUnit(newUnit);
	}
	IMarkerSymbol::OnUnitChanged(oldUnit , newUnit);
}

void Display::CComplexMarkerSymbol::OnChangingInSelectDC()
{
	IMarkerSymbol::OnChangingInSelectDC();
	IComplexSymbol::OnChangingInSelectDC();
}

void Display::CComplexMarkerSymbol::ClearDC()
{
	IComplexSymbol::ClearDC();
	IMarkerSymbol::ClearDC();
}