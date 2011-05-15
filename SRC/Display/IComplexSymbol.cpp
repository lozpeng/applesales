#include "StdAfx.h"
#include "IComplexSymbol.h"
#include "SymbolFactory.h"
#include "IExtSymbol.h"
Display::IComplexSymbol::IComplexSymbol(void)
{
	m_arrayGroup.reset(new CSymbolArray()) ;
}

Display::IComplexSymbol::~IComplexSymbol(void)
{
	m_arrayGroup = NULL;
}

Display::IComplexSymbol::IComplexSymbol(const IComplexSymbol& ComplexSymbol)
{
	*this = ComplexSymbol;
}

Display::IComplexSymbol& Display::IComplexSymbol::operator = (const IComplexSymbol& ComplexSymbol)
{


	for( int i = 0 ; i < ComplexSymbol.m_arrayGroup->GetSize() ; i++ )
	{
		ISymbolPtr temp = ComplexSymbol.m_arrayGroup->GetAt(i)->Clone();
		this->m_arrayGroup->Add(temp);
	}

	this->m_arrayLock.Copy(ComplexSymbol.m_arrayLock);
	this->m_arrayView.Copy(ComplexSymbol.m_arrayView);
	return *this;
}

void Display::IComplexSymbol::SetSymbolVisible( int index , bool visible )				//设置是否可见
{
	m_arrayView.SetAt( index , visible );
}

bool Display::IComplexSymbol::IsVisible(int index)								//得到是否可见
{
	return m_arrayView.GetAt(index);
}

void Display::IComplexSymbol::RemoveSymbol(int index)								//删除加入的符号,根据索引号
{


		m_arrayGroup->RemoveAt(index);
		m_arrayLock.RemoveAt(index);
		m_arrayView.RemoveAt(index);


}

void Display::IComplexSymbol::LockSymbol( int index , bool bLock )				//根据索引号设置是否加锁
{


		m_arrayLock.SetAt( index , bLock );


}

Display::ISymbolPtr Display::IComplexSymbol::GetAt(int index)							//根据索引得到符号指针
{
	return m_arrayGroup->GetAt(index);
}

bool Display::IComplexSymbol::IsLocked(int index)							//根据索引号得到符号是否加锁了
{
	return m_arrayLock.GetAt(index);
}

int Display::IComplexSymbol::GetSize()									//得到加入的符号个数
{
	return m_arrayGroup->GetSize();
}

void Display::IComplexSymbol::serialization(SYSTEM::IArchive &ar)
{
	ISymbol::serialization(ar);
	if( ar.IsSave() )
	{
		int lens = m_arrayGroup->GetSize();
		ar & (lens);
		for( int i = 0 ; i < lens ; i++ )
		{
			int  type = m_arrayGroup->GetAt(i)->GetType();
			ar & (type);
			if (type & EXT_SYMBOL)
			{
				IExtSymbolPtr extSymbol = m_arrayGroup->GetAt(i);
				std::string symbolName = extSymbol->GetSymbolName();
				ar & symbolName;
			}
			m_arrayGroup->GetAt(i)->serialization( ar );

			bool lock = m_arrayLock.GetAt(i);
			ar & lock;

			bool iLock = m_arrayView.GetAt(i);
			ar & (iLock);
		}
	}
	else
	{
		int lens;
		ar & (lens);

		for( int i = 0 ; i < lens ; i++ )
		{
			int type;
			ar & (type);
			if (type & EXT_SYMBOL)
			{
				std::string symbolName;
				ar & symbolName;
				IExtSymbolPtr extSymbol = Display::CSymbolFactory::CreateExtSymbol(symbolName);
				if ( extSymbol != NULL )
					m_arrayGroup->Add(extSymbol);
			
			}
			else
				m_arrayGroup->Add( CSymbolFactory::CreateSymbol( (SYMBOL_TYPE)type ) );
			
			m_arrayGroup->GetAt(i)->serialization( ar );

			bool lock;
			ar & lock;
			m_arrayLock.Add( lock );

			bool iLock;
			ar & (iLock);
			m_arrayView.Add( iLock );
		}

	}
}

bool Display::IComplexSymbol::ExchangeOrder( int posX , int posY )
{

	if( posX < 0 || posY < 0 )
		return false;

	int arraySize = m_arrayGroup->GetSize();

	if ( (arraySize > posX) && (arraySize > posY))
	{
		ISymbolPtr symbolA = m_arrayGroup->GetAt(posX);
		ISymbolPtr symbolB = m_arrayGroup->GetAt(posY);

		m_arrayGroup->SetAt( posX , symbolB );
		m_arrayGroup->SetAt( posY , symbolA );

		bool lockA = m_arrayLock.GetAt(posX);
		bool lockB = m_arrayLock.GetAt(posY);

		m_arrayLock.SetAt( posX , lockB );
		m_arrayLock.SetAt( posY , lockA );

		bool viewA = m_arrayView.GetAt(posX);
		bool viewB = m_arrayView.GetAt(posY);

		m_arrayView.SetAt( posX , viewB );
		m_arrayView.SetAt( posY , viewA );		

		return true;
	}

	return false;

}

void Display::IComplexSymbol::DrawLegend(DIS_RECT * rect,int nFlag)
{
	for ( int i = m_arrayGroup->GetSize() - 1 ; i >= 0 ; i-- )
	{
		if( m_arrayView.GetAt(i) )
		{
			ISymbolPtr pSymbol = m_arrayGroup->GetAt(i);

			pSymbol->SetReadyDraw();							//选择绘制对象
			pSymbol->DrawLegend(rect,nFlag);					//实现绘制
		}
	}
}

void Display::IComplexSymbol::OnUnitChanged(SYSTEM::SYS_UNIT_TYPE oldUnit , SYSTEM::SYS_UNIT_TYPE newUnit)
{
	ISymbol::OnUnitChanged(oldUnit , newUnit);
}

void Display::IComplexSymbol::OnChangingInSelectDC()
{
	ISymbol::OnChangingInSelectDC();
}

void Display::IComplexSymbol::ClearDC()
{
	for( int i = 0 ; i < m_arrayGroup->GetSize() ; i++ )
	{
		ISymbolPtr temp = m_arrayGroup->GetAt(i);
		temp->ClearDC();
	}
}