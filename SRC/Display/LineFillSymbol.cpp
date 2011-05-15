#include "stdafx.h"
#include "SymbolFactory.h"
#include "LineFillSymbol.h"
#include "SimpleLineSymbol.h"
#include "CDC.h"
#include "IArchive.h"
Display::CLineFillSymbol::CLineFillSymbol()
{
	m_lOffset=0;
	m_fOffset = 0.000000f;
	m_lSeparation = 10;
	m_fSeparation = 10.000000f;
	m_fAngle=0;
	m_pLineSymbol.reset(new CSimpleLineSymbol);
	m_pLineSymbol->SetLineColor(RGB(255,0,0));
	m_pLineSymbol->SetLineWidth(1);
	m_lColor=m_pLineSymbol->GetLineColor();
	m_OutLineSymbol->SetLineColor(RGB(0,0,255));
}

Display::CLineFillSymbol::CLineFillSymbol(const Display::CLineFillSymbol& LineFillSymbol)
{
		*this = LineFillSymbol;

}
SYMBOL_TYPE Display::CLineFillSymbol::GetType()
{
	return LINE_FILL_SYMBOL;
}
Display::CLineFillSymbol&  Display::CLineFillSymbol::operator = (const Display::CLineFillSymbol& LineFillSymbol)
{
	m_lColor				   =		     LineFillSymbol.m_lColor;
	m_bOutLine				   =			 LineFillSymbol.m_bOutLine;
	m_fAngle				   =			 LineFillSymbol.m_fAngle;
	m_fOffset				   =             LineFillSymbol.m_fOffset;
	m_pLineSymbol			   =			 LineFillSymbol.m_pLineSymbol;
	*(IFillSymbol*)this	   =			*(IFillSymbol*)&LineFillSymbol;
	this->m_pLineSymbol		   =			LineFillSymbol.m_pLineSymbol->Clone();
	m_fSeparation				=			LineFillSymbol.m_fSeparation;
	return *this;
}

Display::CLineFillSymbol::~CLineFillSymbol()
{
	ClearDC();
}

void Display::CLineFillSymbol::SetOffset( float  Offset )
{

	m_fOffset = Offset;


}
void Display::CLineFillSymbol::SetSeparation(float Separation)
{
	m_fSeparation = abs(Separation);
}

float Display::CLineFillSymbol::GetOffset() 
{
	return m_fOffset;
}

float  Display::CLineFillSymbol::GetSeparation()
{
	return m_fSeparation;
}

void Display::CLineFillSymbol::SetLineSymbol(ILineSymbolPtr pLineSymbol)
{

		this->m_pLineSymbol = pLineSymbol;
		m_lColor = m_pLineSymbol->GetLineColor();

}

Display::ILineSymbolPtr  Display::CLineFillSymbol::GetLineSymbol()
{
	return m_pLineSymbol;
}
void Display::CLineFillSymbol::Draw(void * pObject )        
{
	
	DIS_OBJ_TYPE type =((DIS_POLYGON *)pObject)->type;

	if(type==Dis_Polygon)
	{
		DIS_POLYGON  *dp= (DIS_POLYGON *)pObject;    //得到的数据
		DIS_RECT     rect ,rect1;					  //裁减体的外接矩形和外接正方形；
		long      linesize,sum,offsetY=0;           //1。。线的宽度2。。在矩形里绘几条线3。。y周偏移
		int       lsize;					      //得到正方形边长的一半
		DIS_POINT	  pCenter;							//1。。中心点 2。。
		DIS_LINE dl;							   //线数据
		XFORM old;
		if( !CheckNoColor(m_lColor))
		{
			DISPLAY_HANDLE hRgn = m_pDC->CreateClipPolygon(* dp);//创建裁减体
			DISPLAY_HANDLE_NODE * pHRgn = CDisplayCache::AddToDisplayCache( hRgn , m_pDC );
			CDisplayCache::UseCache( pHRgn , this );

			m_pDC->GetClipRegionBox( rect, hRgn );
			m_pDC->GetClipRegionBox( rect1, hRgn );
			lsize=this->GetSquare(&rect);//得到裁减体的外接正方形和正方形的长度的一半
			//////////////////////////////////////////////////////////////////////////

			/*HRGN printRgn = m_pDC->GetPrintRgn();
			if(printRgn)
			{
				DIS_RECT rectPrint;
				m_pDC->GetClipRegionBox( rectPrint, printRgn );
			}*/

			//////////////////////////////////////////////////////////////////////////
			
			pCenter.p.x=rect1.left+((rect1.right-rect1.left)>>1)+1;
			pCenter.p.y=rect1.top+((rect1.bottom-rect1.top)>>1)+1;
			linesize=  m_lSeparation + m_pLineSymbol->GetLineWidth() ;//得到线的宽度
			if( linesize == 0 )
				linesize = 1;
			sum=(rect.bottom-rect.top) % linesize> m_lSeparation ? (rect.bottom-rect.top) /linesize+1:(rect.bottom-rect.top)/linesize+1;//y周的最大个数
			m_pLineSymbol->SetReadyDraw();
			if(m_lOffset != 0)
				offsetY=m_lOffset% linesize;

			if( m_fAngle != 0 )
			{
				old = m_pDC->SetWorldTransform( m_fAngle , 1.0f , 1.0f , pCenter.p.x  , pCenter.p.y  );
			}
			dl.type = Dis_Line;

			for(int iy=0;iy<sum;iy++)
			{
				dl.Count=2;
				dl.ps[0].x=pCenter.p.x-lsize;
				dl.ps[0].y=pCenter.p.y-lsize-offsetY+iy*linesize;
				dl.ps[1].x=pCenter.p.x+lsize;
				dl.ps[1].y=pCenter.p.y-lsize-offsetY+iy*linesize;
				m_pLineSymbol->Draw(&dl);
			}
			if( pHRgn != NULL)
			{
				CDisplayCache::ReleaseCache( pHRgn );
				pHRgn = NULL;
			}

			if ( m_fAngle != 0 )
			{
				m_pDC->SetWorldTransformBack(old);
			}
		}
		if(m_bOutLine)
		{
			m_OutLineSymbol->SetReadyDraw();
			DrawOutLine(dp);
			SetReadyDraw();
		}
	}
	else if(type==Dis_Circle ||type==Dis_Ellipse)
	{
		//圆或椭圆的外接矩形
		DIS_RECT boundRect;
		if(type ==Dis_Circle)
		{
			DIS_CIRCLE *pc =(DIS_CIRCLE*)pObject;
			boundRect.left =pc->center.x-pc->Radio;
			boundRect.right =pc->center.x+pc->Radio;
			boundRect.top = pc->center.y-pc->Radio;
			boundRect.bottom =pc->center.y+pc->Radio;
		}
		else
		{
			DIS_ELLIPSE *pc =(DIS_ELLIPSE*)pObject;
			boundRect.left =pc->left;
			boundRect.right =pc->right;
			boundRect.top =pc->top;
			boundRect.bottom =pc->bottom;
		}
		DIS_RECT     rect ,rect1;					  //裁减体的外接矩形和外接正方形；
		long      linesize,sum,offsetY=0;           //1。。线的宽度2。。在矩形里绘几条线3。。y周偏移
		int       lsize;					      //得到正方形边长的一半
		DIS_POINT	  pCenter;							//1。。中心点 2。。
		DIS_LINE dl;							   //线数据
		XFORM old;
		if( !CheckNoColor(m_lColor))
		{
			DISPLAY_HANDLE hRgn = m_pDC->CreateClipEllipse(boundRect);//创建裁减体
			DISPLAY_HANDLE_NODE * pHRgn = CDisplayCache::AddToDisplayCache( hRgn , m_pDC );
			CDisplayCache::UseCache( pHRgn , this );

			m_pDC->GetClipRegionBox( rect, hRgn );
			m_pDC->GetClipRegionBox( rect1, hRgn );
			lsize=this->GetSquare(&rect);//得到裁减体的外接正方形和正方形的长度的一半
			pCenter.p.x=rect1.left+((rect1.right-rect1.left)>>1)+1;
			pCenter.p.y=rect1.top+((rect1.bottom-rect1.top)>>1)+1;
			linesize=  m_lSeparation + m_pLineSymbol->GetLineWidth() ;//得到线的宽度
			if( linesize == 0 )
				linesize = 1;
			sum=(rect.bottom-rect.top) % linesize> m_lSeparation ? (rect.bottom-rect.top) /linesize+1:(rect.bottom-rect.top)/linesize+1;//y周的最大个数
			m_pLineSymbol->SetReadyDraw();
			if(m_lOffset != 0)
				offsetY=m_lOffset% linesize;

			if( m_fAngle != 0 )
			{
				old = m_pDC->SetWorldTransform( m_fAngle , 1.0f , 1.0f , pCenter.p.x  , pCenter.p.y  );
			}
			dl.type = Dis_Line;

			for(int iy=0;iy<sum;iy++)
			{
				dl.Count=2;
				dl.ps[0].x=pCenter.p.x-lsize;
				dl.ps[0].y=pCenter.p.y-lsize-offsetY+iy*linesize;
				dl.ps[1].x=pCenter.p.x+lsize;
				dl.ps[1].y=pCenter.p.y-lsize-offsetY+iy*linesize;
				m_pLineSymbol->Draw(&dl);
			}
			if( pHRgn != NULL)
			{
				CDisplayCache::ReleaseCache( pHRgn );
				pHRgn = NULL;
			}

			if ( m_fAngle != 0 )
			{
				m_pDC->SetWorldTransformBack(old);
			}
		}
		if(m_bOutLine)
		{
			m_OutLineSymbol->SetReadyDraw();
			if(type ==Dis_Circle)
			{
				DrawOutLine((DIS_CIRCLE*)pObject); 
			}
			else
			{
				DrawOutLine((DIS_ELLIPSE*)pObject); 
			}
			SetReadyDraw();
		}
	}
	else if(type==Dis_ArcPolygon)
	{
		DIS_ARCPOLYGON  *dp= (DIS_ARCPOLYGON *)pObject;    //得到的数据
		DIS_RECT     rect ,rect1;					  //裁减体的外接矩形和外接正方形；
		long      linesize,sum,offsetY=0;           //1。。线的宽度2。。在矩形里绘几条线3。。y周偏移
		int       lsize;					      //得到正方形边长的一半
		DIS_POINT	  pCenter;							//1。。中心点 2。。
		DIS_LINE dl;							   //线数据
		XFORM old;
		if( !CheckNoColor(m_lColor))
		{
			DISPLAY_HANDLE hRgn = m_pDC->CreateClipArcPolygon(dp);//创建裁减体
			DISPLAY_HANDLE_NODE * pHRgn = CDisplayCache::AddToDisplayCache( hRgn , m_pDC );
			CDisplayCache::UseCache( pHRgn , this );

			m_pDC->GetClipRegionBox( rect, hRgn );
			m_pDC->GetClipRegionBox( rect1, hRgn );
			lsize=this->GetSquare(&rect);//得到裁减体的外接正方形和正方形的长度的一半
			pCenter.p.x=rect1.left+((rect1.right-rect1.left)>>1)+1;
			pCenter.p.y=rect1.top+((rect1.bottom-rect1.top)>>1)+1;
			linesize=  m_lSeparation + m_pLineSymbol->GetLineWidth() ;//得到线的宽度
			if( linesize == 0 )
				linesize = 1;
			sum=(rect.bottom-rect.top) % linesize> m_lSeparation ? (rect.bottom-rect.top) /linesize+1:(rect.bottom-rect.top)/linesize+1;//y周的最大个数
			m_pLineSymbol->SetReadyDraw();
			if(m_lOffset != 0)
				offsetY=m_lOffset% linesize;

			if( m_fAngle != 0 )
			{
				old = m_pDC->SetWorldTransform( m_fAngle , 1.0f , 1.0f , pCenter.p.x  , pCenter.p.y  );
			}
			dl.type = Dis_Line;

			for(int iy=0;iy<sum;iy++)
			{
				dl.Count=2;
				dl.ps[0].x=pCenter.p.x-lsize;
				dl.ps[0].y=pCenter.p.y-lsize-offsetY+iy*linesize;
				dl.ps[1].x=pCenter.p.x+lsize;
				dl.ps[1].y=pCenter.p.y-lsize-offsetY+iy*linesize;
				m_pLineSymbol->Draw(&dl);
			}
			if( pHRgn != NULL)
			{
				CDisplayCache::ReleaseCache( pHRgn );
				pHRgn = NULL;
			}

			if ( m_fAngle != 0 )
			{
				m_pDC->SetWorldTransformBack(old);
			}
		}
		if(m_bOutLine)
		{
			m_OutLineSymbol->SetReadyDraw();
			DrawOutLine(dp);
			SetReadyDraw();
		}
	}

}

void Display::CLineFillSymbol::SelectDC(Display::CDC *pDC)
{
		ISymbol::SelectDC(pDC);
		if(m_bOutLine)
			m_OutLineSymbol->SelectDC(pDC);
		if (m_pLineSymbol != NULL)
			m_pLineSymbol->SelectDC(pDC);
}


void Display::CLineFillSymbol::SetReadyDraw()

{
		if (m_pLineSymbol != NULL)
			m_pLineSymbol->SetReadyDraw();

}

void Display::CLineFillSymbol::SetFillColor(unsigned long color)
{
		this->m_lColor=color;
		this->m_pLineSymbol->SetLineColor(color);
}

unsigned long Display::CLineFillSymbol::GetFillColor(void)
{

	return m_lColor;
}
void  Display::CLineFillSymbol::SetAngle(float Angle)
{

		m_fAngle=Angle;

}

float  Display::CLineFillSymbol::GetAngle()
{
	return m_fAngle;
}
void Display::CLineFillSymbol::SetProperties(const char* PropertyName , const _variant_t& PropertyValue)
{
#define SETPROP(inVal,Val,inName,Name,VT,VT2) if( stricmp(inName,Name) == 0 ) { Val = (VT2)((VT)inVal);return; }
#define SETPROP2(Val,Name,VT) SETPROP( PropertyValue , Val , PropertyName , Name , VT , VT )

		SETPROP2( m_fAngle, "FILLANGLE", float );
		SETPROP2( m_fOffset, "FILLOFFSETY", float );
		SETPROP2( m_fSeparation, "FILLSEPARATIONY", float );
		if( stricmp( PropertyName , "LINESYMBOL" ) == 0 ) 
		{
			if( PropertyValue.vt == VT_BSTR )
			{
				SYSTEM::CStringArchive ar;
				ar.ImportVariant( PropertyValue);
				ar.SetReadState();
				m_pLineSymbol = Display::CSymbolFactory::CreateSymbolFromStream(ar);		
			}
			else
			{
				SYSTEM::CBinArchive ar;
				ar.ImportVariant( PropertyValue);
				ar.SetReadState();
				m_pLineSymbol = Display::CSymbolFactory::CreateSymbolFromStream(ar);		
			}
			if (m_pLineSymbol != NULL)
				m_lColor = m_pLineSymbol->GetLineColor();
			return;
		}

		if( stricmp( PropertyName , "FILLCOLOR" ) == 0 ) 
		{
			SetColor((unsigned long)PropertyValue);
			//m_lColor = (unsigned long)PropertyValue;
			m_pLineSymbol->SetLineColor(m_lColor);
			return;
		}
		IFillSymbol::SetProperties(PropertyName , PropertyValue);

}

_variant_t Display::CLineFillSymbol::GetProperties(const char* PropertyName)
{
	_variant_t vt;
	#define GETPROP(inName,Name,Val,T) if( stricmp(inName,Name) == 0 ) { vt = (T)Val;return vt; }
	#define GETPROP2(Val,Name,T) GETPROP(PropertyName , Name , Val , T )
	GETPROP2( m_fAngle, "FILLANGLE", float );
	GETPROP2( m_fOffset, "FILLOFFSETY", float );
	GETPROP2( m_fSeparation, "FILLSEPARATIONY", float );

	if( stricmp(PropertyName, "LINESYMBOL" ) == 0 )
	{
		SYSTEM::CBinArchive ar;
		ar.SetWriteState();
		m_pLineSymbol->serialization( ar );
		return ar.ExportToVariant();
	}

	return IFillSymbol::GetProperties(PropertyName);
	
}

void Display::CLineFillSymbol::Zoom(float rate)
{
		IFillSymbol::Zoom( rate );
		m_fOffset = m_fOffset * rate;
		m_fSeparation = m_fSeparation * rate;
		m_OutLineSymbol->Zoom(rate);
		m_pLineSymbol->Zoom(rate);
}

void Display::CLineFillSymbol::serialization(SYSTEM::IArchive & ar)
{
	IFillSymbol::serialization( ar ); 
	ar & (m_fAngle);				 
	ar & (m_fOffset);				 
	ar & (m_fSeparation);	
	if( ar.IsSave() )
	{
		int Type=m_pLineSymbol->GetType();
		ar & (Type);
		m_pLineSymbol->serialization( ar );
	}
	else
	{
		int Type;
		ar & (Type);
		m_pLineSymbol = CSymbolFactory::CreateSymbolFromStream( ar);;
	}
}

void Display::CLineFillSymbol::OnUnitChanged(SYSTEM::SYS_UNIT_TYPE oldUnit , SYSTEM::SYS_UNIT_TYPE newUnit)
{
	IFillSymbol::OnUnitChanged(oldUnit , newUnit);

	m_fOffset = UnitChangeTo( oldUnit , newUnit , m_fOffset );
	m_fSeparation = UnitChangeTo( oldUnit , newUnit , m_fSeparation );

	/*if ( m_pLineSymbol != NULL )
	{
		m_pLineSymbol->SetUnit(newUnit);
	}*/
}

void Display::CLineFillSymbol::OnChangingInSelectDC()
{
	m_lOffset = UnitChange( m_enumUnit , m_fOffset );
	m_lSeparation = UnitChange( m_enumUnit , m_fSeparation );
	IFillSymbol::OnChangingInSelectDC();
}

void Display::CLineFillSymbol::ClearDC()
{
	if (m_pLineSymbol != NULL)
	{
		m_pLineSymbol->ClearDC();
	}
	IFillSymbol::ClearDC();
}