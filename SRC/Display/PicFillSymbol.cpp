#include "stdafx.h"
#include "PicFillSymbol.h"
#include "CDC.h"
#include "String.h"
#include "IArchive.h"
#include "DisplayCache.h"


Display::CPicFillSymbol::CPicFillSymbol()
{
	m_lDestW = 0;
	m_lDestH = 0;		
	m_bReverseColor=false;
	m_bPng=false;
	m_fAngle=0;
	m_lBackGroundColor=RGB(255,255,255);//白色
	m_lTransparecyColor=RGB(255,255,255);//白色	
	m_OffsetX=m_OffsetY=0;
	m_fOffsetX = m_fOffsetY = 0;
	m_fScaleX=m_fScaleY=0;
	m_SeparationX=m_SeparationY=0;
	m_fSeparationX = m_fSeparationY = 0;
	m_fScaleY= m_fScaleX=1;
	m_fZoom=0;
	m_bitmapData = NULL;
	m_cPicPath = "";
	m_bpp = -1;
}

Display::CPicFillSymbol::CPicFillSymbol(const Display::CPicFillSymbol& PicFillSymbol)
{
	* this=PicFillSymbol;

}

Display::CPicFillSymbol::~CPicFillSymbol()
{	
	if(	m_bitmapData != NULL) 
	{
		m_MemDC.FreeImageBuffer( m_bitmapData );
		m_bitmapData = NULL;
	}

	ClearDC();
}

Display::CPicFillSymbol & Display::CPicFillSymbol::operator = (const Display::CPicFillSymbol & PicFillSymbol)
{
	m_lColor				   =		     PicFillSymbol.m_lColor;
	m_lRgnID				   =			 PicFillSymbol.m_lRgnID;
	m_bOutLine				   =			 PicFillSymbol.m_bOutLine;
	m_fAngle				   =			 PicFillSymbol.m_fAngle;
	m_lBackGroundColor		   =			 PicFillSymbol.m_lBackGroundColor;
	m_lTransparecyColor	       =			 PicFillSymbol.m_lTransparecyColor;
	m_nSrcW					   =			 PicFillSymbol.m_lDestW;				
	m_nSrcH					   =			 PicFillSymbol.m_nSrcH;					
	m_bReverseColor			   =			 PicFillSymbol.m_bReverseColor;								
	m_bPng					   =			 PicFillSymbol.m_bPng;											
	m_fScaleX				   =			 PicFillSymbol.m_fScaleX;	
	m_fScaleY				   =			 PicFillSymbol.m_fScaleY;	
	m_fAngle				   =			 PicFillSymbol.m_fAngle;	
	m_lDestW				   =			 PicFillSymbol.m_lDestW;
	m_lDestH				   =			 PicFillSymbol.m_nSrcH;	
	m_fOffsetX			       =			 PicFillSymbol.m_fOffsetX;	
	m_fOffsetY			       =			 PicFillSymbol.m_fOffsetY;	
	m_fSeparationX		       =			 PicFillSymbol.m_fSeparationX;	
	m_fSeparationY		       =			 PicFillSymbol.m_fSeparationY;	
	*(IFillSymbol*)this	       =			*(IFillSymbol*)&PicFillSymbol;
	return *this;
}

SYMBOL_TYPE Display::CPicFillSymbol::GetType()
{	
	return PIC_FILL_SYMBOL;
}
void Display::CPicFillSymbol::SetReverseColor(bool bReverseColor)//反转颜色//二值时可使用
{
	m_bReverseColor=bReverseColor;
}

void Display::CPicFillSymbol::SetBGColor(unsigned long nBGcolor)
{
	this->m_lBackGroundColor=nBGcolor;
}

void Display::CPicFillSymbol::SetTransparecyColor(unsigned long nTransparecyColor)
{
	this->m_lTransparecyColor=nTransparecyColor;
}

unsigned long Display::CPicFillSymbol::GetBGColor()
{
	return m_lBackGroundColor;
}

unsigned long Display::CPicFillSymbol::GetTransparecyColor()
{
	return m_lTransparecyColor;

}

void Display::CPicFillSymbol::Draw(void* pObject)
{	

	DIS_OBJ_TYPE type =((DIS_POLYGON *)pObject)->type;



	if(type==Dis_Polygon)
	{
		DIS_POLYGON  *dp=(DIS_POLYGON *) pObject;			//得到的数据
		DIS_RECT     rect,rect1;						//裁减体的外接矩形；
		int       lsize;							//得到正方形边长的一半
		DIS_POINT	  pCenter;							//1。。中心点 2。。
		long      xsum,ysum,offsetXsum=0,offsetYsum=0;	//得到矩形x方向可填充几个图片，y方向可填充几个图片
		DIS_POINT Destp;
		long drawWidth, drawHeight;


		if( m_MemDC.GetSafeHdc() == NULL )
		{
			return ;
		}
		if( !CheckNoColor(m_lColor))
		{
			DISPLAY_HANDLE hRgn = m_pDC->CreateClipPolygon(* dp);//创建裁减体
			DISPLAY_HANDLE_NODE * pHRgn = CDisplayCache::AddToDisplayCache( hRgn , m_pDC );
			CDisplayCache::UseCache( pHRgn , this );

			m_pDC->GetClipRegionBox( rect, hRgn );
			m_pDC->GetClipRegionBox( rect1, hRgn );

			lsize=this->GetSquare(&rect);//得到裁减体的外接正方形和正方形的长度的一半

			//////////////////////////////////////////////////////////////////////////

			HRGN printRgn = m_pDC->GetPrintRgn();
			if(printRgn)
			{
				DIS_RECT rectPrint;
				m_pDC->GetClipRegionBox( rectPrint, printRgn );

				rect1.left = rectPrint.left > rect.left ? rectPrint.left : rect.left;
				rect1.right = rectPrint.right < rect.right ? rectPrint.right : rect.right;
				rect1.top = rectPrint.top > rect.top ? rectPrint.top : rect.top;
				rect1.bottom = rectPrint.bottom < rect.bottom ? rectPrint.bottom : rect.bottom;

				rect.left = rect1.left;
				rect.right = rect1.right;
				rect.top = rect1.top;
				rect.bottom = rect1.bottom;
			}


			//////////////////////////////////////////////////////////////////////////

			pCenter.p.x=((rect1.right-rect1.left)>>1)+1;
			pCenter.p.y=((rect1.bottom-rect1.top)>>1)+1;

			if(!m_lDestW|| !m_lDestH)
			{
				return ;
			}
			xsum=(rect.right-rect.left) %m_lDestW >  m_SeparationX ? (rect.right-rect.left) / m_lDestW/*+1*/:(rect.right-rect.left)/m_lDestW/*+1*/;
			//取矩形的x轴最大点个数
			ysum=(rect.bottom-rect.top) % m_lDestH > m_SeparationY ? (rect.bottom-rect.top) / m_lDestH/*+1*/:(rect.bottom-rect.top)/m_lDestH/*+1*/;
			//取矩形的y轴最大点个数

			if( m_OffsetX != 0 )
				offsetXsum=m_OffsetX%  (m_lDestW+m_SeparationX);
			if( m_OffsetY != 0 )
				offsetYsum=m_OffsetY%  (m_lDestH+m_SeparationY);	

			XFORM old = m_pDC->SetWorldTransform( m_fAngle , 1.0f , 1.0f , rect1.left + pCenter.p.x + m_OffsetX ,rect1.top + pCenter.p.y + m_OffsetX );

			for(int ix=0;ix<xsum+1;ix++)
			{			
				Destp.p.x=(rect.left/*-m_lDestW*/+m_SeparationX)+offsetXsum+ix * (m_lDestW+m_SeparationX);
				drawWidth = Destp.p.x + m_lDestW > rect.right ? rect.right - Destp.p.x : m_lDestW;
				for(int iy=0;iy<ysum+1;iy++)
				{
					Destp.p.y=(rect.top/*-m_lDestH*/+m_SeparationY)+offsetYsum+iy*(m_lDestH+m_SeparationY);	

					drawHeight = Destp.p.y + m_lDestH > rect.bottom ? rect.bottom - Destp.p.y : m_lDestH;
					DrawPic(Destp, drawWidth, drawHeight);
				}
			}
			if( pHRgn != NULL)
			{
				CDisplayCache::ReleaseCache( pHRgn );
				pHRgn = NULL;
			}
			m_pDC->SetWorldTransformBack( old );
		}
		if(m_bOutLine)
		{
			m_OutLineSymbol->SetReadyDraw();
			DrawOutLine(dp); 
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

		DIS_RECT     rect,rect1;						//裁减体的外接矩形；
		int       lsize;							//得到正方形边长的一半
		DIS_POINT	  pCenter;							//1。。中心点 2。。
		long      xsum,ysum,offsetXsum=0,offsetYsum=0;	//得到矩形x方向可填充几个图片，y方向可填充几个图片
		DIS_POINT Destp;
		long drawWidth, drawHeight;


		if( m_MemDC.GetSafeHdc() == NULL )
		{
			return ;
		}
		if( !CheckNoColor(m_lColor))
		{
			DISPLAY_HANDLE hRgn =  m_pDC->CreateClipEllipse(boundRect);//创建裁减体
			DISPLAY_HANDLE_NODE * pHRgn = CDisplayCache::AddToDisplayCache( hRgn , m_pDC );
			CDisplayCache::UseCache( pHRgn , this );

			m_pDC->GetClipRegionBox( rect, hRgn );
			m_pDC->GetClipRegionBox( rect1, hRgn );
			lsize=this->GetSquare(&rect);//得到裁减体的外接正方形和正方形的长度的一半
			//////////////////////////////////////////////////////////////////////////

			HRGN printRgn = m_pDC->GetPrintRgn();
			if(printRgn)
			{
				DIS_RECT rectPrint;
				m_pDC->GetClipRegionBox( rectPrint, printRgn );

				rect1.left = rectPrint.left > rect.left ? rectPrint.left : rect.left;
				rect1.right = rectPrint.right < rect.right ? rectPrint.right : rect.right;
				rect1.top = rectPrint.top > rect.top ? rectPrint.top : rect.top;
				rect1.bottom = rectPrint.bottom < rect.bottom ? rectPrint.bottom : rect.bottom;

				rect.left = rect1.left;
				rect.right = rect1.right;
				rect.top = rect1.top;
				rect.bottom = rect1.bottom;
			}


			//////////////////////////////////////////////////////////////////////////
			pCenter.p.x=((rect1.right-rect1.left)>>1)+1;
			pCenter.p.y=((rect1.bottom-rect1.top)>>1)+1;

			if(!m_lDestW|| !m_lDestH)
			{
				return ;
			}
			xsum=(rect.right-rect.left) %m_lDestW >  m_SeparationX ? (rect.right-rect.left) / m_lDestW+1:(rect.right-rect.left)/m_lDestW+1;
			//取矩形的x轴最大点个数
			ysum=(rect.bottom-rect.top) % m_lDestH > m_SeparationY ? (rect.bottom-rect.top) / m_lDestH+1:(rect.bottom-rect.top)/m_lDestH+1;
			//取矩形的y轴最大点个数

			if( m_OffsetX != 0 )
				offsetXsum=m_OffsetX%  (m_lDestW+m_SeparationX);
			if( m_OffsetY != 0 )
				offsetYsum=m_OffsetY%  (m_lDestH+m_SeparationY);	

			XFORM old = m_pDC->SetWorldTransform( m_fAngle , 1.0f , 1.0f , rect1.left + pCenter.p.x + m_OffsetX ,rect1.top + pCenter.p.y + m_OffsetX );

			for(int ix=0;ix<xsum+1;ix++)
			{	
				Destp.p.x=(rect.left/*-m_lDestW*/+m_SeparationX)+offsetXsum+ix * (m_lDestW+m_SeparationX);
				drawWidth = Destp.p.x + m_lDestW > rect.right ? rect.right - Destp.p.x : m_lDestW;
				for(int iy=0;iy<ysum+1;iy++)
				{
					Destp.p.y=(rect.top/*-m_lDestH*/+m_SeparationY)+offsetYsum+iy*(m_lDestH+m_SeparationY);	

					drawHeight = Destp.p.y + m_lDestH > rect.bottom ? rect.bottom - Destp.p.y : m_lDestH;
					DrawPic(Destp, drawWidth, drawHeight);
				}
			}
			if( pHRgn != NULL)
			{
				CDisplayCache::ReleaseCache( pHRgn );
				pHRgn = NULL;
			}
			m_pDC->SetWorldTransformBack( old );
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

		}
	}
	else if(type==Dis_ArcPolygon)
	{
		DIS_ARCPOLYGON  *dp=(DIS_ARCPOLYGON *) pObject;			//得到的数据
		DIS_RECT     rect,rect1;						//裁减体的外接矩形；
		int       lsize;							//得到正方形边长的一半
		DIS_POINT	  pCenter;							//1。。中心点 2。。
		long      xsum,ysum,offsetXsum=0,offsetYsum=0;	//得到矩形x方向可填充几个图片，y方向可填充几个图片
		DIS_POINT Destp;
		long drawWidth, drawHeight;

		if( m_MemDC.GetSafeHdc() == NULL )
		{
			return ;
		}
		if( !CheckNoColor(m_lColor))
		{
			DISPLAY_HANDLE hRgn = m_pDC->CreateClipArcPolygon(dp);//创建裁减体
			DISPLAY_HANDLE_NODE * pHRgn = CDisplayCache::AddToDisplayCache( hRgn , m_pDC );
			CDisplayCache::UseCache( pHRgn , this );

			m_pDC->GetClipRegionBox( rect, hRgn );
			m_pDC->GetClipRegionBox( rect1, hRgn );
			lsize=this->GetSquare(&rect);//得到裁减体的外接正方形和正方形的长度的一半

			//////////////////////////////////////////////////////////////////////////

			HRGN printRgn = m_pDC->GetPrintRgn();
			if(printRgn)
			{
				DIS_RECT rectPrint;
				m_pDC->GetClipRegionBox( rectPrint, printRgn );

				rect1.left = rectPrint.left > rect.left ? rectPrint.left : rect.left;
				rect1.right = rectPrint.right < rect.right ? rectPrint.right : rect.right;
				rect1.top = rectPrint.top > rect.top ? rectPrint.top : rect.top;
				rect1.bottom = rectPrint.bottom < rect.bottom ? rectPrint.bottom : rect.bottom;

				rect.left = rect1.left;
				rect.right = rect1.right;
				rect.top = rect1.top;
				rect.bottom = rect1.bottom;
			}


			//////////////////////////////////////////////////////////////////////////
			pCenter.p.x=((rect1.right-rect1.left)>>1)+1;
			pCenter.p.y=((rect1.bottom-rect1.top)>>1)+1;

			if(!m_lDestW|| !m_lDestH)
			{
				return ;
			}
			xsum=(rect.right-rect.left) %m_lDestW >  m_SeparationX ? (rect.right-rect.left) / m_lDestW+1:(rect.right-rect.left)/m_lDestW+1;
			//取矩形的x轴最大点个数
			ysum=(rect.bottom-rect.top) % m_lDestH > m_SeparationY ? (rect.bottom-rect.top) / m_lDestH+1:(rect.bottom-rect.top)/m_lDestH+1;
			//取矩形的y轴最大点个数

			if( m_OffsetX != 0 )
				offsetXsum=m_OffsetX%  (m_lDestW+m_SeparationX);
			if( m_OffsetY != 0 )
				offsetYsum=m_OffsetY%  (m_lDestH+m_SeparationY);	

			XFORM old = m_pDC->SetWorldTransform( m_fAngle , 1.0f , 1.0f , rect1.left + pCenter.p.x + m_OffsetX ,rect1.top + pCenter.p.y + m_OffsetX );

			for(int ix=0;ix<xsum+1;ix++)
			{	
				Destp.p.x=(rect.left/*-m_lDestW*/+m_SeparationX)+offsetXsum+ix * (m_lDestW+m_SeparationX);
				drawWidth = Destp.p.x + m_lDestW > rect.right ? rect.right - Destp.p.x : m_lDestW;
				for(int iy=0;iy<ysum+1;iy++)
				{
					Destp.p.y=(rect.top/*-m_lDestH*/+m_SeparationY)+offsetYsum+iy*(m_lDestH+m_SeparationY);	

					drawHeight = Destp.p.y + m_lDestH > rect.bottom ? rect.bottom - Destp.p.y : m_lDestH;
					DrawPic(Destp, drawWidth, drawHeight);
				}
			}
			if( pHRgn != NULL)
			{
				CDisplayCache::ReleaseCache( pHRgn );
				pHRgn = NULL;
			}
			m_pDC->SetWorldTransformBack( old );
		}
		if(m_bOutLine)
		{
			m_OutLineSymbol->SetReadyDraw();
			DrawOutLine(dp); 
		}
	}



}
void Display::CPicFillSymbol::SelectDC(Display::CDC * pDC)
{ 
	IFillSymbol::SelectDC(pDC);
	if( m_MemDC.GetBitmap() == NULL )
	{
		return ;
	}
	if( m_bpp != 1 )
		m_MemDC.SelectBitmap();
	m_MemDC.CreateCompatibleDC( pDC );
	m_MemDC.SelectBitmap();

	if(m_fZoom<=0)
		m_fZoom=1.0f;
	if(m_fScaleX<=0)
		m_fScaleX=1.0f;
	if(m_fScaleY<=0)
		m_fScaleY=1.0f;
	m_lDestW=m_nSrcW * abs(m_fScaleX)*abs(m_fZoom);
	m_lDestH=m_nSrcH * abs(m_fScaleY)*abs(m_fZoom);
	if(m_bOutLine)
		m_OutLineSymbol->SelectDC(pDC);
	if( m_bpp == 1)
	{
		if(m_bReverseColor)
		{
			m_MemDC.SetBGColor(GetRValue(GetFillColor()),GetGValue(GetFillColor()),GetBValue(GetFillColor()));
			m_MemDC.SetFGColor(GetRValue(GetBGColor()),GetGValue(GetBGColor()),GetBValue(GetBGColor()));
		}
		else
		{
			m_MemDC.SetBGColor(GetRValue(GetBGColor()),GetGValue(GetBGColor()),GetBValue(GetBGColor()));
			m_MemDC.SetFGColor(GetRValue(GetFillColor()),GetGValue(GetFillColor()),GetBValue(GetFillColor()));
		}
		m_MemDC.SelectBitmap();
	}

}

void Display::CPicFillSymbol::SetReadyDraw()
{
	if( m_MemDC.GetBitmap() == NULL )
	{
		return;
	}

	if(m_bOutLine)
	{
		m_OutLineSymbol->SetReadyDraw();
	}
}
void Display::CPicFillSymbol::SetWidthScale (float Scale)
{

	if(Scale<0)
	{
		return;
	}

	m_fScaleX=Scale;
	m_lDestW=(m_nSrcW*Scale);

}

float Display::CPicFillSymbol::GetWidthScale ()	
{
	return m_fOffsetX;
}
void Display::CPicFillSymbol::SetHeightScale(float Scale)
{
	if(Scale<0)
	{
		return;
	}

	m_fScaleY=Scale;
	m_lDestH=(m_nSrcH*Scale);
}

float Display::CPicFillSymbol::GetHeightScale()
{
	return m_fScaleY;

}

void Display::CPicFillSymbol::SetOffsetXY( float OffsetX , float OffsetY )
{
	m_fOffsetX = OffsetX;
	m_fOffsetY = OffsetY;

}
void Display::CPicFillSymbol::SetSeparationXY(float SeparationX , float SeparationY)
{
	m_fSeparationX = abs(SeparationX);
	m_fSeparationY = abs(SeparationY);

}

float Display::CPicFillSymbol::GetOffsetX() 
{
	return m_fOffsetX;
}

float Display::CPicFillSymbol::GetOffsetY() 
{
	return m_fOffsetY;
}

float Display::CPicFillSymbol::GetSeparationX()
{
	return m_fSeparationX;
}

float Display::CPicFillSymbol::GetSeparationY()
{
	return m_fSeparationY;
}

void Display::CPicFillSymbol::SetAngle(float Angle)
{

	m_fAngle=Angle;

}

float Display::CPicFillSymbol::GetAngle()
{


	return m_fAngle;

}
void Display::CPicFillSymbol::DrawPic(DIS_POINT & Destpoint, long destW, long destH)
{

	DIS_POINT DIS_POINT1;
	DIS_POINT1.p.x=0;
	DIS_POINT1.p.y=0;

	if( m_bpp==1 )
	{

		if(m_lDestW==m_nSrcW && m_lDestH==m_nSrcH )
		{
			m_MemDC.BitBlt(m_pDC,Destpoint,destW/*m_lDestW*/,destH/*m_lDestH*/,DIS_POINT1);
			return ;
		}
		else
		{
			m_MemDC.StretchBlt(m_pDC,Destpoint,destW/*m_lDestW*/,destH/*m_lDestH*/,DIS_POINT1,(int)m_nSrcW,(int)m_nSrcH);
			return ;
		}
	}
	if( m_bpp ==4 || m_bpp == 8 )
	{
		if(m_lTransparecyColor==RGB(255,255,255) && m_lBackGroundColor==RGB(255,255,255))
		{
			m_MemDC.StretchBlt(m_pDC,Destpoint,m_lDestW,m_lDestH,DIS_POINT1,(int)m_nSrcW,(int)m_nSrcH);
			return ;
		}
		else
		{
			m_MemDC.ConvertColorBlt(m_pDC,Destpoint,m_lDestW,m_lDestH,DIS_POINT1,(int)m_nSrcW,(int)m_nSrcH,m_lBackGroundColor,m_lTransparecyColor);
			return ;
		}
	}
	if(m_bpp == 24)
	{
		if(m_lTransparecyColor==RGB(255,255,255) && m_lBackGroundColor==RGB(255,255,255))
		{
			m_MemDC.StretchBlt(m_pDC,Destpoint,m_lDestW,m_lDestH,DIS_POINT1,(int)m_nSrcW,(int)m_nSrcH);
			return ;
		}
		else
		{
			m_MemDC.TransparentBlt(m_pDC,Destpoint.p.x,Destpoint.p.y,m_lDestW,m_lDestH,DIS_POINT1.p.x,DIS_POINT1.p.y,(int)m_nSrcW,(int)m_nSrcH,m_lTransparecyColor);
			return ;
		}

	}
	if( this->m_bPng )
	{
		m_MemDC.AlphaBlend(m_pDC,Destpoint,m_lDestW,m_lDestH,DIS_POINT1,(int)m_nSrcW,(int)m_nSrcH);
		return ;
	}
	else
	{
		m_MemDC.StretchBlt(m_pDC,Destpoint,m_lDestW,m_lDestH,DIS_POINT1,(int)m_nSrcW,(int)m_nSrcH);
		return ;
	}

}


bool Display::CPicFillSymbol::GetReverseColor()
{
	return m_bReverseColor;
}


void Display::CPicFillSymbol::SetProperties(const char* PropertyName , const _variant_t& PropertyValue)
{
#define SETPROP(inVal,Val,inName,Name,VT,VT2) if( stricmp(inName,Name) == 0 ) { Val = (VT2)((VT)inVal);return; }
#define SETPROP2(Val,Name,VT) SETPROP( PropertyValue , Val , PropertyName , Name , VT , VT )
	SETPROP2( m_lBackGroundColor , "BACKGROUNDCOLOR" , unsigned long );
	SETPROP2( m_fOffsetX , "OFFSETX" ,  float );
	SETPROP2( m_fOffsetY , "OFFSETY" ,  float );
	SETPROP2( m_fSeparationX , "SEPARATIONX" ,  float );
	SETPROP2( m_fSeparationY , "SEPARATIONY" ,  float );
	SETPROP2( m_lTransparecyColor , "TRANSPARECYCOLOR" , unsigned long );
	SETPROP2( m_bReverseColor , "REVERSECOLOR" ,  bool );
	SETPROP2( m_fScaleX , "FILLPICHEIGHTSCALE" ,  float );
	SETPROP2( m_fScaleY , "FILLPICWIDTHSCALE" ,  float );
	SETPROP2( m_fAngle , "FILLANGLE" ,  float );
	if( !stricmp( PropertyName, "PICFILLFILENAME" ) )
	{
		m_cPicPath = ( _bstr_t )PropertyValue;
		SetFileName( m_cPicPath );
	}

	IFillSymbol::SetProperties(PropertyName , PropertyValue);

}

_variant_t Display::CPicFillSymbol::GetProperties(const char* PropertyName)
{

	_variant_t vt;
#define GETPROP(inName,Name,Val,T) if( stricmp(inName,Name) == 0 ) { vt = (T)Val;return vt; }
#define GETPROP2(Val,Name,T) GETPROP(PropertyName , Name , Val , T )

	GETPROP2( m_lBackGroundColor , "BACKGROUNDCOLOR" , unsigned long );
	GETPROP2( m_fOffsetX , "OFFSETX" ,  float );
	GETPROP2( m_fOffsetY , "OFFSETY" ,  float );
	GETPROP2( m_fSeparationX , "SEPARATIONX" ,  float );
	GETPROP2( m_fSeparationY , "SEPARATIONY" ,  float );
	GETPROP2( m_lTransparecyColor , "TRANSPARECYCOLOR" , unsigned long );
	GETPROP2( m_bReverseColor , "REVERSECOLOR" ,  bool );
	GETPROP2( m_fScaleX , "FILLPICHEIGHTSCALE" ,  float );
	GETPROP2( m_fScaleY , "FILLPICWIDTHSCALE" ,  float );
	GETPROP2( m_fAngle , "FILLANGLE" ,  float );
	if( !stricmp( PropertyName,"IMAGEPALETTEARRAY" ))
	{
		return ( long )m_MemDC.GetBitmapColor( m_bitmapData );
	}
	GETPROP2( m_bpp , "IMAGEBITCOUNT" ,  int );
	if( !stricmp( PropertyName, "PICFILLFILENAME" ) )
	{
		vt = m_cPicPath.c_str();
		return vt;
	}
	return IFillSymbol::GetProperties(PropertyName);
}

void Display::CPicFillSymbol::Zoom(float rate)
{
	IFillSymbol::Zoom( rate );
	if(rate==0.0f)
		m_fZoom=1.0f;
	else
		m_fZoom=rate;
	if ( m_OutLineSymbol != NULL )
	{
		m_OutLineSymbol->Zoom(rate);
	}
}

void Display::CPicFillSymbol::serialization(SYSTEM::IArchive & ar)
{ 
	IFillSymbol::serialization( ar); 

	ar & (m_nSrcW);
	ar & (m_nSrcH);
	ar & (m_bPng);
	ar & (m_bReverseColor);		 
	ar & (m_lBackGroundColor);	
	ar & (m_lTransparecyColor);
	ar & (m_fSeparationX);
	ar & (m_fSeparationY);
	ar & (m_fOffsetX);
	ar & (m_fOffsetY);
	ar & (m_fScaleX);
	ar & (m_fScaleY);
	ar & (m_lDestW);
	ar & (m_lDestH);
	ar & (m_fAngle);
	ar & (m_bpp);
	ar & (m_bitmapDataLens);

	if( ar.IsSave() )
	{
		if( m_MemDC.GetBitmap() == NULL )
		{
			m_bSetFileName = false;
			ar & (m_bSetFileName);
			return ;
		}
		else
		{
			m_bSetFileName = true;
			ar & (m_bSetFileName);
		}
		if( m_bitmapData == NULL )
		{
			m_bitmapData = m_MemDC.SaveFromBuffer( m_bitmapData ,m_bitmapDataLens );
		}
		ar.Write( m_bitmapData , m_bitmapDataLens );

	}
	else
	{
		ar & (m_bSetFileName);
		if( !m_bSetFileName )
		{
			return ;
		}
		if( m_bitmapData != NULL )
		{
			m_MemDC.Destroy();
			m_MemDC.FreeImageBuffer( m_bitmapData );
			m_bitmapData = NULL;
		}
		m_bitmapData = m_MemDC.NewImageBuffer( m_bitmapDataLens );
		ar.Read( m_bitmapData ,m_bitmapDataLens );
		m_MemDC.LoadImageFromBuffer( m_bitmapData );

		IMAGE_INFO ImageInfo;                          
		m_MemDC.GetImageInfo( ImageInfo,m_bitmapData );
		m_nSrcW = ImageInfo.lWidth;
		m_nSrcH = ImageInfo.lHeight;
		m_bpp =  ImageInfo.lBitCount;
	}

}
void Display::CPicFillSymbol::SetFileName(std::string cFilename)
{
	if(	m_bitmapData != NULL) 
	{
		m_MemDC.Destroy();
		m_MemDC.FreeImageBuffer( m_bitmapData );
		m_bitmapData = NULL;
	}

	m_bitmapData = m_MemDC.LoadImageFromFile( cFilename , m_bPng ,m_bitmapDataLens);
	if( m_bitmapData == NULL )
	{
		m_cPicPath = "";
		return;
	}
	m_cPicPath =cFilename;

	IMAGE_INFO ImageInfo;                          
	m_MemDC.GetImageInfo( ImageInfo,m_bitmapData );
	m_nSrcW = ImageInfo.lWidth;
	m_nSrcH = ImageInfo.lHeight;
	m_bpp =  ImageInfo.lBitCount;
}

void Display::CPicFillSymbol::OnUnitChanged(SYSTEM::SYS_UNIT_TYPE oldUnit , SYSTEM::SYS_UNIT_TYPE newUnit)
{
	IFillSymbol::OnUnitChanged(oldUnit , newUnit);

	m_fOffsetX = UnitChangeTo( oldUnit , newUnit , m_fOffsetX );
	m_fOffsetY = UnitChangeTo( oldUnit , newUnit , m_fOffsetY );
	m_fSeparationX = UnitChangeTo( oldUnit , newUnit , m_fSeparationX );
	m_fSeparationY = UnitChangeTo( oldUnit , newUnit , m_fSeparationY );
}

void Display::CPicFillSymbol::OnChangingInSelectDC()
{
	m_OffsetX = UnitChange( m_enumUnit , m_fOffsetX );
	m_OffsetY = UnitChange( m_enumUnit , m_fOffsetY );
	m_SeparationX = UnitChange( m_enumUnit , m_fSeparationX );
	m_SeparationY = UnitChange( m_enumUnit , m_fSeparationY );

	IFillSymbol::OnChangingInSelectDC();
}

void Display::CPicFillSymbol::ClearDC()
{
	IFillSymbol::ClearDC();
}