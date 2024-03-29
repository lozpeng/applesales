/* Generated by gether */
#include "stdafx.h"
#include "SymbolFactory.h"
#include "MarkerLineSymbol.h"
#include "IMarkerSymbol.h"
#include "DisOptimize.h"
#include "CDC.h"
#include "IArchive.h"

Display::CMarkerLineSymbol::CMarkerLineSymbol()
{
		m_enumLineJointType = EXT_JOIN_ROUND;
		pMarkGroup = NULL;								
		pMarkAngle = NULL;

		CSimpleMarkerSymbol * pSms = new CSimpleMarkerSymbol;
		pSms->SetMarkerSize(1.000000f);
		pSms->SetMarkerType(SIMPLE_MARKER_SQUARE);
		m_pMarkSymbol.reset( pSms );

		m_fLineWidth = pSms->GetMarkerSize();
		m_lColor = pSms->GetMarkColor();
}

Display::CMarkerLineSymbol::~CMarkerLineSymbol()
{
		ClearDC();
}

Display::CMarkerLineSymbol::CMarkerLineSymbol(const Display::CMarkerLineSymbol& MarkLineSymbol)
{
		*this = MarkLineSymbol;
}

Display::CMarkerLineSymbol& Display::CMarkerLineSymbol::operator = (const Display::CMarkerLineSymbol & MarkLineSymbol)
{
		this->m_pMarkSymbol  		=		 MarkLineSymbol.m_pMarkSymbol->Clone();
		*(CAdvLineSymbol*)this		=		*(CAdvLineSymbol*)& MarkLineSymbol;
		return *this;
}

void Display::CMarkerLineSymbol::SetMarkerSymbol(Display::IMarkerSymbolPtr pSym)
{
		m_pMarkSymbol = pSym;
}

Display::IMarkerSymbolPtr Display::CMarkerLineSymbol::GetMarkerSymbol()
{
	return m_pMarkSymbol;
}

SYMBOL_TYPE Display::CMarkerLineSymbol::GetType()
{
	return MARKER_LINE_SYMBOL;
}

void Display::CMarkerLineSymbol::SelectDC(Display::CDC * pDC)
{
		ISymbol::SelectDC( pDC ); 
		
		if(m_pMarkSymbol.get())
		{
			m_pMarkSymbol->SelectDC(pDC);
		}
		
		
		if ( m_enumArrowMarkerType != NOARROW )							//判断是否加入箭头装饰符部分代码
		{				
			if( m_pArrowMarkerSymbol.get() != NULL )
			{
				m_pArrowMarkerSymbol->SelectDC(pDC);
			}	
		
		}	
}

void Display::CMarkerLineSymbol::SetReadyDraw()
{
		m_pMarkSymbol->SetReadyDraw();
}

void Display::CMarkerLineSymbol::Draw(void* pObject)
{
		if( CheckNoColor(m_lColor))
			return;

		if(((DIS_LINE *)pObject)->type == Dis_Line)
		{
			DIS_LINE* pDIS_LINE = (DIS_LINE*)pObject;
			if(pDIS_LINE == NULL)
				return;

			if(m_bDrawFlag)
				m_lOffsetLineCount = CDisOptimize::OffsetLineByMarkLine( pDIS_LINE->Count , &(pDIS_LINE->ps[0].x) , m_lOffsetX , 
				m_lOffsetY , m_LineJointStyle , m_pDashGroup->GetDashGroupCount() ,
				(long *)(m_pDashGroup->GetData()) , &pMarkGroup , &pMarkAngle );
		}
		else if(((DIS_BEZIER *)pObject)->type == Dis_Bezier)
		{
			DIS_BEZIER* pDIS_LINE = (DIS_BEZIER *)pObject;
			if(pDIS_LINE == NULL)
				return;
			if(m_bDrawFlag)
				m_lOffsetLineCount = CDisOptimize::OffsetLineByMarkLine( pDIS_LINE->Count , &(pDIS_LINE->ps[0].x) , m_lOffsetX , 
				m_lOffsetY , m_LineJointStyle , m_pDashGroup->GetDashGroupCount() ,
				(long *)(m_pDashGroup->GetData()) , &pMarkGroup , &pMarkAngle );
		}

	
		//数据转换
		if( m_bDrawFlag )
		{
		/*	m_lOffsetLineCount = CDisOptimize::OffsetLineByMarkLine( pDIS_LINE->Count , &(pDIS_LINE->ps[0].x) , m_lOffsetX , 
												m_lOffsetY , m_LineJointStyle , m_pDashGroup->GetDashGroupCount() ,
												(long *)(m_pDashGroup->GetData()) , &pMarkGroup , &pMarkAngle );*/

			if( m_lOffsetLineCount < 1 )			
			{
				/**pMarkGroup = *pMarkAngle = false;*/
				return;
			}
			
			long *tempMarkGroup= pMarkGroup;

			DIS_POINT tmpPoint;
			tmpPoint.type = Dis_Point;
			//实现绘制
			for( int i = 0 ; i < m_lOffsetLineCount ; ++i )
			{				
				XFORM old = m_pDC->SetWorldTransform( (float)*(pMarkAngle+i) , 1.0 , 1.0 , *(tempMarkGroup) , *(tempMarkGroup + 1) );
				
				tmpPoint.p.x = *tempMarkGroup;
				tmpPoint.p.y = *(tempMarkGroup + 1);
				m_pMarkSymbol->Draw(&tmpPoint);
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

void Display::CMarkerLineSymbol::DrawArrow(void* pObject)
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
				m_pArrowMarkerSymbol->SetAngle(_2PI - ((float) * (pMarkAngle + (m_lOffsetLineCount - 1))));
			}
			else
			{
				m_pArrowMarkerSymbol->SetAngle(_2PI - (storeArrowAngle + (float)*(pMarkAngle + (m_lOffsetLineCount - 1))));
			}
			//			m_pArrowMarkerSymbol->SetReadyDraw();						//上面已经调用，不必重复调用，设置角度，不影响笔，刷
			m_pArrowMarkerSymbol->Draw(&point2);

			this->SetReadyDraw();
		}
		else if(m_enumArrowMarkerType==ARROWBEGIN)
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
		else if( m_enumArrowMarkerType == ARROWEND )
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

void Display::CMarkerLineSymbol::Zoom(float rate)
{
	
		ILineSymbol::Zoom(rate);
		m_pArrowMarkerSymbol->Zoom(rate);
		m_pMarkSymbol->Zoom(rate);

		//变换破折号数组的间距
		for ( unsigned long i = 0 ; i < m_pDashGroup->GetDashGroupCount() ; ++i )
		{
			float tempData = m_pDashGroup->GetDash(i);
			m_pDashGroup->SetDash(tempData * rate , i);
		}
}
void Display::CMarkerLineSymbol::SetLineColor(unsigned long lColor)			//设置线宽
{
	this->m_lColor = lColor;
	//if(m_pMarkSymbol->GetType()!= OT_COMPLEX_MARK_SYMBOL)
		m_pMarkSymbol->SetMarkerColor(this->m_lColor);

}
void Display::CMarkerLineSymbol::SetLineWidth(float nWidth)
{
	this->m_fLineWidth = nWidth;
	/*if(m_pMarkSymbol->GetType()!= OT_COMPLEX_MARK_SYMBOL)*/
		m_pMarkSymbol->SetMarkerSize(this->m_fLineWidth);
}

#define SETPROP(inVal,Val,inName,Name,VT) if( stricmp(inName,Name) == 0 ) { Val = (VT)inVal;return; }
#define SETPROP2(Val,Name,VT) SETPROP( PropertyValue , Val , PropertyName , Name , VT )
#define SETPROPEX(inVal,Val,inName,Name,VT,VT2) if( stricmp(inName,Name) == 0 ) { Val = (VT2)((VT)inVal);return; }
#define SETPROPEX2(Val,Name,VT,VT2) SETPROPEX( PropertyValue , Val , PropertyName , Name , VT , VT2)

void Display::CMarkerLineSymbol::SetProperties(const char* PropertyName,const _variant_t& PropertyValue)
{
		if( stricmp( PropertyName , "MARKSYMBOL" ) == 0 ) 
		{
			if( PropertyValue.vt == VT_BSTR )
			{
				SYSTEM::CStringArchive ar;
				ar.ImportVariant( PropertyValue);
				ar.SetReadState();
				/*m_OutLineSymbol->serialization( ar );*/
				m_pMarkSymbol = Display::CSymbolFactory::CreateSymbolFromStream(ar);			//本想判断一下返回的符号是否是线符号。暂时不作判断了咧
			}
			else
			{
				SYSTEM::CBinArchive ar;
				ar.ImportVariant( PropertyValue);
				ar.SetReadState();
				/*m_OutLineSymbol->serialization( ar );*/
				m_pMarkSymbol = Display::CSymbolFactory::CreateSymbolFromStream(ar);
			}

			if (m_pMarkSymbol != NULL)
			{
				m_lColor = m_pMarkSymbol->GetMarkColor();
			}

			return;
		}

		if( stricmp( PropertyName , "LINEWIDTH") == 0 )
		{
			m_fLineWidth = (float)PropertyValue;
			m_pMarkSymbol->SetMarkerSize(this->m_fLineWidth);
			return;
		}

		if( stricmp(PropertyName , "LINECOLOR") == 0 )
		{
			/*m_lColor = (unsigned long)PropertyValue;*/
			SetColor((unsigned long)PropertyValue);
		//	m_pMarkSymbol->SetMarkerColor(m_lColor);

			return;
		}
		
		return CAdvLineSymbol::SetProperties( PropertyName , PropertyValue);

}

#define GETPROP(inName,Name,Val,T) if( stricmp(inName,Name) == 0 ) { vt = (T)Val;return vt; }
#define GETPROP2(Name,Val,T) GETPROP(PropertyName , Name , Val , T )

_variant_t Display::CMarkerLineSymbol::GetProperties(const char* PropertyName)
{

		_variant_t vt;

		if( stricmp(PropertyName, "MARKSYMBOL" ) == 0 )
		{
			SYSTEM::CBinArchive ar;
			ar.SetWriteState();
			m_pMarkSymbol->serialization( ar );
			return ar.ExportToVariant();
		}
		return CAdvLineSymbol::GetProperties(PropertyName);
	return 0;
return CAdvLineSymbol::GetProperties(PropertyName);
}

void Display::CMarkerLineSymbol::serialization(SYSTEM::IArchive & ar)
{ 
	CAdvLineSymbol::serialization( ar ); 

	if( ar.IsSave() )
	{
		int  type=m_pMarkSymbol->GetType();
		ar & (type);
		m_pMarkSymbol->serialization( ar );
	}
	else
	{
		int type;
		ar & (type);
		m_pMarkSymbol = CSymbolFactory::CreateSymbol( (SYMBOL_TYPE)type );
		m_pMarkSymbol->serialization( ar );
	}
}

void Display::CMarkerLineSymbol::ClearDC()
{
	if ( m_pMarkSymbol != NULL )
	{
		m_pMarkSymbol->ClearDC();
	}
	CAdvLineSymbol::ClearDC();
}

void Display::CMarkerLineSymbol::OnUnitChanged(SYSTEM::SYS_UNIT_TYPE oldUnit , SYSTEM::SYS_UNIT_TYPE newUnit)
{
	CAdvLineSymbol::OnUnitChanged(oldUnit , newUnit);
	/*if ( m_pMarkSymbol != NULL )
	{
		m_pMarkSymbol->SetUnit(newUnit);
	}*/
}

void Display::CMarkerLineSymbol::OnChangingInSelectDC()
{
	ILineSymbol::OnChangingInSelectDC();
}