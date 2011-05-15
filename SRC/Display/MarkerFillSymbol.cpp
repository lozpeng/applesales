#include "stdafx.h"
#include "SymbolFactory.h"
#include "MarkerFillSymbol.h"
#include "CDC.h"
#include "IArchive.h"

#pragma warning(disable:4996)

Display::CMarkerFillSymbol::CMarkerFillSymbol()
{
	this->m_brand=false;
	this->m_lRgnID=0;

	m_OffsetX=m_OffsetY=0;
	m_SeparationY=m_SeparationX=10;

	m_fOffsetX = m_fOffsetY = 0.000000f;
	m_fSeparationX = m_fSeparationY = 10.000000f;

	CSimpleMarkerSymbol *pSym=new CSimpleMarkerSymbol;
	pSym->SetMarkerType(SIMPLE_MARKER_DIAMOND);
	m_pMSfill.reset( pSym );
	m_lColor = m_pMSfill->GetMarkColor();

	m_OutLineSymbol->SetLineColor(RGB(255,0,0));
	m_lColor=pSym->GetMarkColor();
}

Display::CMarkerFillSymbol::CMarkerFillSymbol(const Display::CMarkerFillSymbol& MarkFillSymbol)
{
		* this = MarkFillSymbol;

}
SYMBOL_TYPE Display::CMarkerFillSymbol::GetType()
{
	return MARKER_FILL_SYMBOL;
}
Display::CMarkerFillSymbol&   Display::CMarkerFillSymbol::operator = (const Display::CMarkerFillSymbol& MarkFillSymbol)
{
	m_fOffsetX				=          MarkFillSymbol.m_fOffsetX;
	m_fOffsetY				=			MarkFillSymbol.m_fOffsetY;
	m_pMSfill				=			MarkFillSymbol.m_pMSfill;
	m_fSeparationX			=			MarkFillSymbol.m_fSeparationX;
	m_fSeparationY			=			MarkFillSymbol.m_fSeparationY;
	m_lColor				=		    MarkFillSymbol.m_lColor;
	m_bOutLine				=			MarkFillSymbol.m_bOutLine;
	*(IFillSymbol*)this		=			*(IFillSymbol*)&MarkFillSymbol;
	m_pMSfill				=			MarkFillSymbol.m_pMSfill->Clone();
	return *this;
}

Display::CMarkerFillSymbol::~CMarkerFillSymbol()
{
		ClearDC();
}

void Display::CMarkerFillSymbol::SetOffsetXY( float OffsetX , float OffsetY )
{

	m_fOffsetX = OffsetX;
	m_fOffsetY = OffsetY;


}
void Display::CMarkerFillSymbol::SetSeparationXY(float SeparationX , float SeparationY)
{

	m_fSeparationX = abs(SeparationX);
	m_fSeparationY = abs(SeparationY);

}

float Display::CMarkerFillSymbol::GetOffsetX() 
{
	return m_fOffsetX;
}

float Display::CMarkerFillSymbol::GetOffsetY() 
{
	return m_fOffsetY;
}

float  Display::CMarkerFillSymbol::GetSeparationX()
{
	return m_fSeparationX;
}

float  Display::CMarkerFillSymbol::GetSeparationY()
{
	return m_fSeparationY;
}

void Display::CMarkerFillSymbol::SetMarkSymbol(IMarkerSymbolPtr makeSymbol)
{

		this->m_pMSfill = makeSymbol;
		m_lColor=makeSymbol->GetMarkColor();

}

Display::IMarkerSymbolPtr Display::CMarkerFillSymbol::GetMarkSymbol()
{
	return m_pMSfill;
	
}

void Display::CMarkerFillSymbol::SetMarkFillRand(bool brand)
{


		this->m_brand=brand;


}

bool Display::CMarkerFillSymbol::GetMarkFillRand( )
{
	return m_brand;


}
 
void Display::CMarkerFillSymbol::Draw(void * pObject )        
{

    DIS_OBJ_TYPE type =((DIS_POLYGON *)pObject)->type;

	if(type==Dis_Polygon)
	{
		DIS_POLYGON  *dp=(DIS_POLYGON *) pObject;    //得到的数据
		DIS_RECT     rect;					       //裁减体的外接矩形；
		DIS_POINT    markersize;                    //得到点符号的大小公式=间隔+点的大小
		long      xsum,ysum,offsetXsum=0,offsetYsum=0;				   //得到矩形x方向可填充几个点，y方向可填充几个点
		long       count=0;					   //点的个数
		if( !CheckNoColor(m_lColor))
		{
			DISPLAY_HANDLE hRgn = m_pDC->CreateClipPolygon(* dp);//创建裁减体
			DISPLAY_HANDLE_NODE * pHRgn = CDisplayCache::AddToDisplayCache( hRgn , m_pDC );
			CDisplayCache::UseCache( pHRgn , this );

			m_pDC->GetClipRegionBox( rect, hRgn );
			markersize.p.x=m_SeparationX+m_pMSfill->GetMarkerSize();//得到x轴符号大小

			markersize.p.y=(m_SeparationY+m_pMSfill->GetMarkerSize());//得到y轴符号大小
			if( markersize.p.x <= 0 )
			{
				markersize.p.x = 1; 
			}
			if( markersize.p.y <= 0 )
			{
				markersize.p.y = 1; 
			}
			xsum=(rect.right-rect.left) % markersize.p.x >  m_SeparationX ? (rect.right-rect.left) / markersize.p.x+1:(rect.right-rect.left)/markersize.p.x+1;
			//取矩形的x轴最大点个数
			ysum=(rect.bottom-rect.top) % markersize.p.y > m_SeparationX ? (rect.bottom-rect.top) / markersize.p.y+1:(rect.bottom-rect.top)/markersize.p.y+1;
			//取矩形的y轴最大点个数
			DIS_POINT Destp;
			Destp.type = Dis_Point; 
			if(m_OffsetX)
				offsetXsum=m_OffsetX% markersize.p.x;

			if(m_OffsetY)
				offsetYsum=m_OffsetY% markersize.p.y;

			for(int ix=0;ix<xsum+2;ix++)
			{			

				Destp.p.x=(rect.left-markersize.p.x)+offsetXsum+ix *markersize.p.x;
				for(int iy=0;iy<ysum+2;iy++)
				{
					Destp.p.y=(rect.top-markersize.p.y)+offsetYsum+iy * markersize.p.y;	
					m_pMSfill->Draw(&Destp);
				}
			}
			if( pHRgn != NULL)
			{
				CDisplayCache::ReleaseCache( pHRgn );
				pHRgn = NULL;
			}
		}
		if(m_bOutLine)
		{
			m_OutLineSymbol->SetReadyDraw();
			DrawOutLine(dp); 
			m_pMSfill->SetReadyDraw();
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

		DIS_RECT     rect;					       //裁减体的外接矩形；
		DIS_POINT    markersize;                    //得到点符号的大小公式=间隔+点的大小
		long      xsum,ysum,offsetXsum=0,offsetYsum=0;				   //得到矩形x方向可填充几个点，y方向可填充几个点
		long       count=0;					   //点的个数
		if( !CheckNoColor(m_lColor))
		{
			DISPLAY_HANDLE hRgn = m_pDC->CreateClipEllipse(boundRect);//创建裁减体
			DISPLAY_HANDLE_NODE * pHRgn = CDisplayCache::AddToDisplayCache( hRgn , m_pDC );
			CDisplayCache::UseCache( pHRgn , this );

			m_pDC->GetClipRegionBox( rect, hRgn );
			markersize.p.x=m_SeparationX+m_pMSfill->GetMarkerSize();//得到x轴符号大小

			markersize.p.y=(m_SeparationY+m_pMSfill->GetMarkerSize());//得到y轴符号大小
			if( markersize.p.x <= 0 )
			{
				markersize.p.x = 1; 
			}
			if( markersize.p.y <= 0 )
			{
				markersize.p.y = 1; 
			}
			xsum=(rect.right-rect.left) % markersize.p.x >  m_SeparationX ? (rect.right-rect.left) / markersize.p.x+1:(rect.right-rect.left)/markersize.p.x+1;
			//取矩形的x轴最大点个数
			ysum=(rect.bottom-rect.top) % markersize.p.y > m_SeparationX ? (rect.bottom-rect.top) / markersize.p.y+1:(rect.bottom-rect.top)/markersize.p.y+1;
			//取矩形的y轴最大点个数
			DIS_POINT Destp;
			Destp.type = Dis_Point; 
			if(m_OffsetX)
				offsetXsum=m_OffsetX% markersize.p.x;

			if(m_OffsetY)
				offsetYsum=m_OffsetY% markersize.p.y;

			for(int ix=0;ix<xsum+2;ix++)
			{			

				Destp.p.x=(rect.left-markersize.p.x)+offsetXsum+ix *markersize.p.x;
				for(int iy=0;iy<ysum+2;iy++)
				{
					Destp.p.y=(rect.top-markersize.p.y)+offsetYsum+iy * markersize.p.y;	
					m_pMSfill->Draw(&Destp);
				}
			}
			if( pHRgn != NULL)
			{
				CDisplayCache::ReleaseCache( pHRgn );
				pHRgn = NULL;
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
			
			m_pMSfill->SetReadyDraw();
		}
	}
	else if(type==Dis_ArcPolygon)
	{
		DIS_ARCPOLYGON  *dp=(DIS_ARCPOLYGON *) pObject;    //得到的数据
		DIS_RECT     rect;					       //裁减体的外接矩形；
		DIS_POINT    markersize;                    //得到点符号的大小公式=间隔+点的大小
		long      xsum,ysum,offsetXsum=0,offsetYsum=0;				   //得到矩形x方向可填充几个点，y方向可填充几个点
		long       count=0;					   //点的个数
		if( !CheckNoColor(m_lColor))
		{
			DISPLAY_HANDLE hRgn = m_pDC->CreateClipArcPolygon(dp);//创建裁减体
			DISPLAY_HANDLE_NODE * pHRgn = CDisplayCache::AddToDisplayCache( hRgn , m_pDC );
			CDisplayCache::UseCache( pHRgn , this );

			m_pDC->GetClipRegionBox( rect, hRgn );
			markersize.p.x=m_SeparationX+m_pMSfill->GetMarkerSize();//得到x轴符号大小

			markersize.p.y=(m_SeparationY+m_pMSfill->GetMarkerSize());//得到y轴符号大小
			if( markersize.p.x <= 0 )
			{
				markersize.p.x = 1; 
			}
			if( markersize.p.y <= 0 )
			{
				markersize.p.y = 1; 
			}
			xsum=(rect.right-rect.left) % markersize.p.x >  m_SeparationX ? (rect.right-rect.left) / markersize.p.x+1:(rect.right-rect.left)/markersize.p.x+1;
			//取矩形的x轴最大点个数
			ysum=(rect.bottom-rect.top) % markersize.p.y > m_SeparationX ? (rect.bottom-rect.top) / markersize.p.y+1:(rect.bottom-rect.top)/markersize.p.y+1;
			//取矩形的y轴最大点个数
			DIS_POINT Destp;
			Destp.type = Dis_Point; 
			if(m_OffsetX)
				offsetXsum=m_OffsetX% markersize.p.x;

			if(m_OffsetY)
				offsetYsum=m_OffsetY% markersize.p.y;

			for(int ix=0;ix<xsum+2;ix++)
			{			

				Destp.p.x=(rect.left-markersize.p.x)+offsetXsum+ix *markersize.p.x;
				for(int iy=0;iy<ysum+2;iy++)
				{
					Destp.p.y=(rect.top-markersize.p.y)+offsetYsum+iy * markersize.p.y;	
					m_pMSfill->Draw(&Destp);
				}
			}
			if( pHRgn != NULL)
			{
				CDisplayCache::ReleaseCache( pHRgn );
				pHRgn = NULL;
			}
		}
		if(m_bOutLine)
		{
			m_OutLineSymbol->SetReadyDraw();
			DrawOutLine(dp); 
			m_pMSfill->SetReadyDraw();
		}
	}

	

}
void Display::CMarkerFillSymbol::SelectDC(Display::CDC *pDC)
{
	ISymbol::SelectDC(pDC);
	if(m_bOutLine)
		m_OutLineSymbol->SelectDC(pDC);
	if( m_pMSfill != NULL )
		m_pMSfill->SelectDC(pDC);
}


void Display::CMarkerFillSymbol::SetReadyDraw()

{
		/*if(m_bOutLine)
			m_OutLineSymbol->SetReadyDraw();*/
		if(m_pMSfill)	
			m_pMSfill->SetReadyDraw();

}

void Display::CMarkerFillSymbol::SetFillColor(unsigned long color)
{
	m_lColor=color;
	if(m_pMSfill->GetType()==SIMPLE_MARKER_SYMBOL)
	{
			CSimpleMarkerSymbolPtr csms = m_pMSfill;

			if(csms->GetMarkerType()==3||csms->GetMarkerType()==4)
			{
				csms->SetOutLineColor(m_lColor);
			}
			else
			{
				csms->SetMarkerColor(m_lColor);
			}

	}
	else
	{
		m_pMSfill->SetMarkerColor(m_lColor);
	}
}

unsigned long Display::CMarkerFillSymbol::GetFillColor(void)
{
	return m_lColor;

}
void Display::CMarkerFillSymbol::SetProperties(const char* PropertyName , const _variant_t& PropertyValue)
{
	#define SETPROP(inVal,Val,inName,Name,VT,VT2) if( stricmp(inName,Name) == 0 ) { Val = (VT2)((VT)inVal);return; }
	#define SETPROP2(Val,Name,VT) SETPROP( PropertyValue , Val , PropertyName , Name , VT , VT )

	SETPROP2( m_fOffsetX, "FILLOFFSETX", float );
	SETPROP2( m_fOffsetY, "FILLOFFSETY", float );
	SETPROP2( m_fSeparationX, "FILLSEPARATIONX", float );
	SETPROP2( m_fSeparationY, "FILLSEPARATIONY", float );
	SETPROP2( m_brand, "MARKFILLRAND", bool );

	if( stricmp( PropertyName , "MARKSYMBOL" ) == 0 ) 
	{
		if( PropertyValue.vt == VT_BSTR )
		{
			SYSTEM::CStringArchive ar;
			ar.ImportVariant( PropertyValue);
			ar.SetReadState();
			m_pMSfill = Display::CSymbolFactory::CreateSymbolFromStream(ar);		
		}
		else
		{
			SYSTEM::CBinArchive ar;
			ar.ImportVariant( PropertyValue);
			ar.SetReadState();
			m_pMSfill = Display::CSymbolFactory::CreateSymbolFromStream(ar);		
		}

		if (m_pMSfill != NULL)
			m_lColor = m_pMSfill->GetMarkColor();
		return;
	}

	if( stricmp( PropertyName , "FILLCOLOR" ) == 0 ) 
	{
		/*m_lColor = (unsigned long)PropertyValue;*/
		SetColor((unsigned long)PropertyValue);
		m_pMSfill->SetMarkerColor(m_lColor);
		return;
	}
	IFillSymbol::SetProperties( PropertyName, PropertyValue );
}

_variant_t Display::CMarkerFillSymbol::GetProperties(const char* PropertyName)
{
	_variant_t vt;
	#define GETPROP(inName,Name,Val,T) if( stricmp(inName,Name) == 0 ) { vt = (T)Val;return vt; }
	#define GETPROP2(Val,Name,T) GETPROP(PropertyName , Name , Val , T )
	GETPROP2( m_fOffsetX, "FILLOFFSETX", float );
	GETPROP2( m_fOffsetX, "FILLOFFSETX", float );
	GETPROP2( m_fSeparationX, "FILLSEPARATIONX", float );
	GETPROP2( m_fSeparationY, "FILLSEPARATIONY", float );
	GETPROP2( m_brand, "MARKFILLRAND", bool );

	if( stricmp(PropertyName, "MARKSYMBOL" ) == 0 )
	{
		SYSTEM::CBinArchive ar;
		ar.SetWriteState();
		m_pMSfill->serialization( ar );
		return ar.ExportToVariant();
	}
	return IFillSymbol::GetProperties(PropertyName);
}

void Display::CMarkerFillSymbol::Zoom(float rate)
{
		IFillSymbol::Zoom( rate );
		m_fSeparationX = m_fSeparationX * rate;
		m_fSeparationY = m_fSeparationY * rate;
		m_OutLineSymbol->Zoom(rate);
		m_pMSfill->Zoom(rate);
}

void Display::CMarkerFillSymbol::serialization(SYSTEM::IArchive & ar)
{ 
	IFillSymbol::serialization(ar); 

	ar & (m_fOffsetX);				 
	ar & (m_fOffsetY);				 
	ar & (m_fSeparationX);
	ar & (m_fSeparationY);				 
	ar & (m_brand);				 

	if( ar.IsSave () )
	{
		int  type = m_pMSfill->GetType();
		ar & (type);
		m_pMSfill->serialization( ar );
	}
	else
	{
		int type;
		ar & type;
		m_pMSfill = CSymbolFactory::CreateSymbol( (SYMBOL_TYPE)type );
		m_pMSfill->serialization( ar );
	}
}
 void Display::CMarkerFillSymbol::ClearDC()
 {
	 if (m_pMSfill != NULL)
	 {
		 m_pMSfill->ClearDC();
	 }
	 IFillSymbol::ClearDC();
 }

 void Display::CMarkerFillSymbol::OnUnitChanged(SYSTEM::SYS_UNIT_TYPE oldUnit , SYSTEM::SYS_UNIT_TYPE newUnit)
 {
	 IFillSymbol::OnUnitChanged(oldUnit , newUnit);

	 m_fOffsetX = UnitChangeTo( oldUnit , newUnit , m_fOffsetX );
	 m_fOffsetY = UnitChangeTo( oldUnit , newUnit , m_fOffsetY );
	 m_fSeparationX = UnitChangeTo( oldUnit , newUnit , m_fSeparationX );
	 m_fSeparationY = UnitChangeTo( oldUnit , newUnit , m_fSeparationY );

	 /*if ( m_pMSfill != NULL )
	 {
		 m_pMSfill->SetUnit(newUnit);
	 }*/
 }

 void Display::CMarkerFillSymbol::OnChangingInSelectDC()
 {
	 m_OffsetX = UnitChange( m_enumUnit , m_fOffsetX );
	 m_OffsetY = UnitChange( m_enumUnit , m_fOffsetY );
	 m_SeparationX = UnitChange( m_enumUnit , m_fSeparationX );
	 m_SeparationY = UnitChange( m_enumUnit , m_fSeparationY );
	 IFillSymbol::OnChangingInSelectDC();
 }