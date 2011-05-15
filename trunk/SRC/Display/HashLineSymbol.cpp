#include "stdafx.h"
#include "SymbolFactory.h"
#include "HashLineSymbol.h"
#include "DisOptimize.h"
#include "CDC.h"
#include "IArchive.h"

#pragma warning(disable:4996)

Display::CHashLineSymbol::CHashLineSymbol()
{
		m_enumLineJointType = EXT_JOIN_ROUND;

		m_fHashAngle = (float)_PI2;

		/*m_lLineWidth = 20;*/

		pMarkGroup = NULL;								

		pMarkAngle = NULL;

		m_fLineWidth = 5.0f;
		m_pLineSymbol.reset( new CSimpleLineSymbol );
		/*m_pLineSymbol->SetLineWidth(m_fLineWidth);*/
		m_lColor = m_pLineSymbol->GetLineColor();
}

Display::CHashLineSymbol::~CHashLineSymbol()
{
		ClearDC();
}

Display::CHashLineSymbol::CHashLineSymbol(const Display::CHashLineSymbol& HashLineSymbol)
{
		*this = HashLineSymbol;
}

Display::CHashLineSymbol& Display::CHashLineSymbol::operator = (const Display::CHashLineSymbol & HashLineSymbol)
{
		this->m_pLineSymbol  		=		HashLineSymbol.m_pLineSymbol->Clone();
		*(CAdvLineSymbol*)this		=		*(CAdvLineSymbol*)&HashLineSymbol;
		this->m_fHashAngle			=		HashLineSymbol.m_fHashAngle;
	return *this;
}


void Display::CHashLineSymbol::SetHashAngle(float fHashAngle)
{
		m_fHashAngle = fHashAngle;
}

float Display::CHashLineSymbol::GetHashAngle()
{
	return m_fHashAngle;
}

SYMBOL_TYPE Display::CHashLineSymbol::GetType()
{
	return HASH_LINE_SYMBOL;
}

void Display::CHashLineSymbol::SetLineSymbol(ILineSymbolPtr pLs)
{
		m_pLineSymbol = pLs;
}

Display::ILineSymbolPtr Display::CHashLineSymbol::GetLineSymbol()
{

	return m_pLineSymbol;

}

void Display::CHashLineSymbol::SelectDC(Display::CDC * pDC)
{
		ISymbol::SelectDC( pDC ); 

		if ( m_pLineSymbol.get() != NULL )
		{
			m_pLineSymbol->SelectDC(pDC);
		}
		else
		{
			return;
		}

		if ( m_enumArrowMarkerType != NOARROW )					//判断是否加入箭头装饰符部分代码
		{				
			if( m_pArrowMarkerSymbol.get() != NULL )
			{
				m_pArrowMarkerSymbol->SelectDC(pDC);
			}	
		}
}

void Display::CHashLineSymbol::SetReadyDraw()
{
		m_pLineSymbol->SetReadyDraw();
}

void Display::CHashLineSymbol::Draw(void* pObject)
{
		if( CheckNoColor(m_lColor))
			return;

		if(((DIS_LINE *)pObject)->type == Dis_Line)
		{
			DIS_LINE* pDIS_LINE = (DIS_LINE*)pObject;
			if(pDIS_LINE == NULL)
				return;

			if(m_bDrawFlag)
				m_lOffsetLineCount = CDisOptimize::OffsetLineByMarkLine( pDIS_LINE->Count , &(pDIS_LINE->ps[0].x) , m_lOffsetX , m_lOffsetY , m_LineJointStyle , m_pDashGroup->GetDashGroupCount() , (long *)(m_pDashGroup->GetData()) , &pMarkGroup , &pMarkAngle );
		}
		else if(((DIS_BEZIER *)pObject)->type == Dis_Bezier)
		{
			DIS_BEZIER* pDIS_LINE = (DIS_BEZIER *)pObject;
			if(pDIS_LINE == NULL)
				return;
			if(m_bDrawFlag)
				m_lOffsetLineCount = CDisOptimize::OffsetLineByMarkLine( pDIS_LINE->Count , &(pDIS_LINE->ps[0].x) , m_lOffsetX , m_lOffsetY , m_LineJointStyle , m_pDashGroup->GetDashGroupCount() , (long *)(m_pDashGroup->GetData()) , &pMarkGroup , &pMarkAngle );
		}

		//////////////////////////////////////////////////////////////////////////
		//数据转换
		if(m_bDrawFlag)
		{

			//m_lOffsetLineCount = CDisOptimize::OffsetLineByMarkLine( pDIS_LINE->Count , &(pDIS_LINE->ps[0].x) , m_lOffsetX , m_lOffsetY , m_LineJointStyle , m_pDashGroup->GetDashGroupCount() , (long *)(m_pDashGroup->GetData()) , &pMarkGroup , &pMarkAngle );

			if ( m_lOffsetLineCount < 1 )		
			{
				/**pMarkGroup = *pMarkAngle = false;*/
				return;
			}

			long *tempMarkGroup = pMarkGroup;
			/*bool flag=false;
			if(m_pLineSymbol->GetType()==TO_HASH_LINE_SYMBOL||m_pLineSymbol->GetType()==TO_MARK_LINE_SYMBOL||m_pLineSymbol->GetType()==TO_COMPLEX_LINE_SYMBOL)
			{
				flag=true;
			}*/
			DIS_LINE tempLine;
			tempLine.type = Dis_Line;
			tempLine.Count = 2;
			//实现绘制
			for ( int i = 0 ; i < m_lOffsetLineCount ; ++i )
			{		
				XFORM old = m_pDC->SetWorldTransform((float)(_2PI - m_fHashAngle + (*(pMarkAngle + i))) , 1.0f , 1.0f , *(tempMarkGroup) , *(tempMarkGroup + 1));

				tempLine.ps[0].x = *tempMarkGroup - (m_lLineWidth >> 1);
				tempLine.ps[0].y = *(tempMarkGroup + 1);
				tempLine.ps[1].x = tempLine.ps[0].x + m_lLineWidth;
				tempLine.ps[1].y = tempLine.ps[0].y;
				m_pLineSymbol->SetReadyDraw();
				m_pLineSymbol->Draw(&tempLine);

				m_pDC->SetWorldTransformBack(old);

				tempMarkGroup = tempMarkGroup + 2;
			}

			if( m_enumArrowMarkerType != NOARROW )	
			{
				DrawArrow(pObject);
			}

			CDisOptimize::free_Group(&pMarkGroup);
			CDisOptimize::free_Group(&pMarkAngle);
		}
		
}

void Display::CHashLineSymbol::DrawArrow(void* pObject)
{
		//////////////////////////////////////////////////////////////////////////
		if ( m_enumArrowMarkerType == NOARROW )
		{
			return;
		}
		else if ( m_enumArrowMarkerType == ARROWBOTH )
		{
			DIS_POINT point1,point2;
			point1.type = Dis_Point;
			point2.type = Dis_Point;

			point1.p.x = *pMarkGroup;
			point1.p.y = *(pMarkGroup + 1);

			point2.p.x = *(pMarkGroup + 2 * (m_lOffsetLineCount - 1));
			point2.p.y = *(pMarkGroup + 2 * (m_lOffsetLineCount - 1) + 1);

			//起始点
			if ( m_pArrowMarkerSymbol->GetType() == COMPLEX_MARKER_SYMBOL )
			{
				m_pArrowMarkerSymbol->SetAngle(0);
				m_pArrowMarkerSymbol->SetAngle(_2PI - ((float)*(pMarkAngle) - PI));
			}
			else
			{
				m_pArrowMarkerSymbol->SetAngle(_2PI - (storeArrowAngle + (float)*(pMarkAngle) - PI));
			}

			m_pArrowMarkerSymbol->SetReadyDraw();
			m_pArrowMarkerSymbol->Draw(&point1);

			//终止点
			if ( m_pArrowMarkerSymbol->GetType() == COMPLEX_MARKER_SYMBOL )
			{
				m_pArrowMarkerSymbol->SetAngle(0);
				m_pArrowMarkerSymbol->SetAngle(_2PI - ((float)*(pMarkAngle + (m_lOffsetLineCount - 1))));
			}
			else
			{
				m_pArrowMarkerSymbol->SetAngle(_2PI - (storeArrowAngle + (float)*(pMarkAngle + (m_lOffsetLineCount - 1))));
			}

			//			m_pArrowMarkerSymbol->SetReadyDraw();						//上面已经调用，不必重复调用，设置角度，不影响笔，刷
			m_pArrowMarkerSymbol->Draw(&point2);

			this->SetReadyDraw();
		}
		else if ( m_enumArrowMarkerType == ARROWBEGIN )
		{
			DIS_POINT point1;
			point1.type = Dis_Point;

			point1.p.x = *pMarkGroup;
			point1.p.y = *(pMarkGroup + 1);
			//起始点
			if ( m_pArrowMarkerSymbol->GetType() == COMPLEX_MARKER_SYMBOL )
			{
				m_pArrowMarkerSymbol->SetAngle(0);
				m_pArrowMarkerSymbol->SetAngle(_2PI - ((float)*(pMarkAngle) - PI));
			}
			else
			{
				m_pArrowMarkerSymbol->SetAngle(_2PI - (storeArrowAngle + (float)*(pMarkAngle) - PI));
			}

			m_pArrowMarkerSymbol->SetReadyDraw();
			m_pArrowMarkerSymbol->Draw(&point1);

			this->SetReadyDraw();
		}
		else if ( m_enumArrowMarkerType == ARROWEND )
		{
			DIS_POINT point2;
			point2.type = Dis_Point;

			point2.p.x = *(pMarkGroup + 2 * (m_lOffsetLineCount - 1));
			point2.p.y = *(pMarkGroup + 2 * (m_lOffsetLineCount - 1) + 1);
			//终止点
			if ( m_pArrowMarkerSymbol->GetType() == COMPLEX_MARKER_SYMBOL )
			{
				m_pArrowMarkerSymbol->SetAngle(0);
				m_pArrowMarkerSymbol->SetAngle(_2PI - ((float)*(pMarkAngle + (m_lOffsetLineCount - 1))));
			}
			else
			{
				m_pArrowMarkerSymbol->SetAngle(_2PI - (storeArrowAngle + (float)*(pMarkAngle + (m_lOffsetLineCount - 1))));
			}

			m_pArrowMarkerSymbol->SetReadyDraw();		
			m_pArrowMarkerSymbol->Draw(&point2);
			this->SetReadyDraw();
		}

		if ( m_pArrowMarkerSymbol->GetType() == COMPLEX_MARKER_SYMBOL )
		{
			m_pArrowMarkerSymbol->SetAngle(0);
		}
		else
		{
			m_pArrowMarkerSymbol->SetAngle(storeArrowAngle);
		}
		
}

#define SETPROP(inVal,Val,inName,Name,VT) if( stricmp(inName,Name) == 0 ) { Val = (VT)inVal;return; }
#define SETPROP2(Val,Name,VT) SETPROP( PropertyValue , Val , PropertyName , Name , VT )
#define SETPROPEX(inVal,Val,inName,Name,VT,VT2) if( stricmp(inName,Name) == 0 ) { Val = (VT2)((VT)inVal);return; }
#define SETPROPEX2(Val,Name,VT,VT2) SETPROPEX( PropertyValue , Val , PropertyName , Name , VT , VT2)

void Display::CHashLineSymbol::SetProperties(const char* PropertyName , const _variant_t& PropertyValue)
{	
		if( stricmp( PropertyName , "LINESYMBOL" ) == 0 ) 
		{
			if( PropertyValue.vt == VT_BSTR )
			{
				SYSTEM::CStringArchive ar;
				ar.ImportVariant( PropertyValue);
				ar.SetReadState();
				/*m_OutLineSymbol->serialization( ar );*/
				m_pLineSymbol = Display::CSymbolFactory::CreateSymbolFromStream(ar);			//本想判断一下返回的符号是否是线符号。暂时不作判断了咧			
			}
			else
			{
				SYSTEM::CBinArchive ar;
				ar.ImportVariant( PropertyValue);
				ar.SetReadState();
				/*m_OutLineSymbol->serialization( ar );*/
				m_pLineSymbol = Display::CSymbolFactory::CreateSymbolFromStream(ar);		
			}
			if (m_pLineSymbol != NULL)
			{
				m_lColor = m_pLineSymbol->GetLineColor();
			}
			return;
		}

		if( stricmp( PropertyName , "LINEWIDTH") == 0 )
		{
			m_fLineWidth = (float)PropertyValue;
			return;
		}

		if( stricmp(PropertyName , "LINECOLOR") == 0 )
		{
			/*m_lColor = (unsigned long)PropertyValue;*/
			SetColor((unsigned long)PropertyValue);
		//	m_pLineSymbol->SetLineColor(this->m_lColor);
			return;
		}

		if( stricmp(PropertyName , "HASHANGLE") == 0 )
		{
			m_fHashAngle = (float)PropertyValue;
			return;
		}

		return CAdvLineSymbol::SetProperties( PropertyName , PropertyValue);
}

#define GETPROP(inName,Name,Val,T) if( stricmp(inName,Name) == 0 ) { vt = (T)Val;return vt; }
#define GETPROP2(Name,Val,T) GETPROP(PropertyName , Name , Val , T )

_variant_t Display::CHashLineSymbol::GetProperties(const char* PropertyName)
{
		_variant_t vt;

		if( stricmp(PropertyName, "LINESYMBOL" ) == 0 )
		{
			SYSTEM::CBinArchive ar;
			ar.SetWriteState();
			m_pLineSymbol->serialization( ar );
			return ar.ExportToVariant();
		}

		GETPROP2("HASHANGLE" , m_fHashAngle  , _variant_t );

	return CAdvLineSymbol::GetProperties(PropertyName);
	return 0;

}

void Display::CHashLineSymbol::Zoom(float rate)
{
		ILineSymbol::Zoom(rate);

		m_pArrowMarkerSymbol->Zoom(rate);
		m_pLineSymbol->Zoom(rate);

		for ( unsigned long i = 0 ; i < m_pDashGroup->GetDashGroupCount() ; ++i)
		{
			float tempData = m_pDashGroup->GetDash(i);
			m_pDashGroup->SetDash( tempData * rate , i );
		}
}

void Display::CHashLineSymbol:: SetLineColor(unsigned long lColor)
{
	this->m_lColor = lColor;
	m_pLineSymbol->SetLineColor(this->m_lColor);
}

void Display::CHashLineSymbol::serialization(SYSTEM::IArchive & ar)
{ 
	CAdvLineSymbol::serialization( ar ); 

	ar & m_fHashAngle;				 

	if( ar.IsSave() )
	{
		int Type = m_pLineSymbol->GetType();
		ar & (Type);
		m_pLineSymbol->serialization( ar );
	}
	else
	{
		int Type;
		ar & (Type);
		m_pLineSymbol = CSymbolFactory::CreateSymbol( (SYMBOL_TYPE)Type );
		m_pLineSymbol->serialization( ar );
		
	}		 
}

void Display::CHashLineSymbol::ClearDC()
{
	if ( m_pLineSymbol != NULL )
	{
		m_pLineSymbol->ClearDC();
	}

	CAdvLineSymbol::ClearDC();
}

void Display::CHashLineSymbol::OnUnitChanged(SYSTEM::SYS_UNIT_TYPE oldUnit , SYSTEM::SYS_UNIT_TYPE newUnit)
{
	CAdvLineSymbol::OnUnitChanged(oldUnit , newUnit);
	/*if ( m_pLineSymbol != NULL )
	{
		m_pLineSymbol->SetUnit(newUnit);
	}*/
}

void Display::CHashLineSymbol::OnChangingInSelectDC()
{
	ILineSymbol::OnChangingInSelectDC();
}