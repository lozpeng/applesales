#include "stdafx.h"
#include "PicMarkerSymbol.h"
#include "CDC.h"
#include "String.h"
#include "IArchive.h"
Display::CPicMarkerSymbol::CPicMarkerSymbol()
{

	m_nSrcW = -1;
	m_nSrcH = -1;
	m_bReverseColor = false;
	m_bPng = false;
	m_lBackGroundColor = RGB(255,255,255);//透明色
	m_lTransparecyColor = RGB(255,255,255);//透明色	
	m_lInsideReviseX = 0;
	m_lInsideReviseY = 0;
	m_fMarkerSize = 10;
	m_bitmapData = NULL;
	m_bSetFileName = false;
	m_fScale = 0.0f;
    m_lDestW = 0;
    m_lDestH = 0;						
	m_bpp = -1;
	m_cPicPath = "";
	
}

Display::CPicMarkerSymbol::CPicMarkerSymbol(const Display::CPicMarkerSymbol& PicMarkSymbol)
{
	* this=PicMarkSymbol;

}

Display::CPicMarkerSymbol::~CPicMarkerSymbol()
{	
	if( m_MemDC.GetBitmap() != NULL )
	{
		m_MemDC.Destroy();
	}
	if(	m_bitmapData != NULL) 
	{
		m_MemDC.FreeImageBuffer( m_bitmapData );
		m_bitmapData = NULL;
	}
	ClearDC();
}

Display::CPicMarkerSymbol & Display::CPicMarkerSymbol::operator = (const Display::CPicMarkerSymbol & PicMarkSymbol)
{
		m_lBackGroundColor			=	PicMarkSymbol.m_lBackGroundColor;
		m_lTransparecyColor		    =	PicMarkSymbol.m_lTransparecyColor;
		m_nSrcW					    =	PicMarkSymbol.m_nSrcW;									
		m_nSrcH					    =	PicMarkSymbol.m_nSrcH;		
		m_bReverseColor			    =   PicMarkSymbol.m_bReverseColor;						
		m_bPng						=   PicMarkSymbol.m_bPng;														
		m_lInsideReviseX			=   PicMarkSymbol.m_lInsideReviseX;
		m_lInsideReviseY			=   PicMarkSymbol.m_lInsideReviseY;									
		m_fScale					=   PicMarkSymbol.m_fScale;										
		m_lDestW					=   PicMarkSymbol.m_lDestW;
		m_lDestH					=	PicMarkSymbol.m_lDestH;	
		m_bpp						=   PicMarkSymbol.m_bpp;
	//	PicMarkSymbol.m_MemDC.SaveToBuffer( m_bitmapData ,PicMarkSymbol.m_bitmapDataLens );
		*(IMarkerSymbol*)this=*(IMarkerSymbol*)&PicMarkSymbol;

	return *this;
}

SYMBOL_TYPE Display::CPicMarkerSymbol::GetType()
{	
	return PIC_MARKER_SYMBOL;
}
void Display::CPicMarkerSymbol::SetReverseColor(bool bReverseColor)//反转颜色//二值时可使用
{
	m_bReverseColor = bReverseColor;
}

void Display::CPicMarkerSymbol::SetBGColor(unsigned long nBGcolor)
{
	m_lBackGroundColor = nBGcolor;
}

void Display::CPicMarkerSymbol::SetTransparecyColor(unsigned long nTransparecyColor)
{
	m_lTransparecyColor = nTransparecyColor;
}

unsigned long Display::CPicMarkerSymbol::GetBGColor()
{
	return m_lBackGroundColor;
}

unsigned long Display::CPicMarkerSymbol::GetTransparecyColor()
{
	return m_lTransparecyColor;
}
void Display::CPicMarkerSymbol::SetFileName(std::string cFilename)
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

bool Display::CPicMarkerSymbol::GetReverseColor()
{
	return m_bReverseColor;
}

void Display::CPicMarkerSymbol::Draw(void* pObject)
{

		if( CheckNoColor(m_lColor))
			return;
		if( m_MemDC.GetBitmap() == NULL )
		{
			return ;
		}
		DIS_POINT dPoint=*(DIS_POINT*)(pObject);
		DIS_POINT dPoint1,dPoint2;
		dPoint1.p.x=dPoint1.p.y=0;

		dPoint2.p.x=dPoint.p.x;
		dPoint2.p.y=dPoint.p.y;

		dPoint.p.x =(dPoint.p.x+m_lOffsetX)  - (m_lInsideReviseX>>1) ;
		dPoint.p.y =(dPoint.p.y+m_lOffsetY)  - (m_lInsideReviseY>>1) ;
			
			XFORM old = m_pDC->SetWorldTransform( m_fAngle , 1.0f , 1.0f , dPoint2.p.x + m_lOffsetX , dPoint2.p.y + m_lOffsetY );

		if( m_bpp == 1 )
		{

			if(m_lInsideReviseX==m_nSrcW && m_lInsideReviseY==m_nSrcH )
			{
				m_MemDC.BitBlt(m_pDC,dPoint,m_lInsideReviseX,m_lInsideReviseY,dPoint1);
				m_pDC->SetWorldTransformBack( old );
				return ;
			}
			else
			{
				m_MemDC.StretchBlt(m_pDC,dPoint,m_lInsideReviseX,m_lInsideReviseY,dPoint1,(int)m_nSrcW,(int)m_nSrcH);
				m_pDC->SetWorldTransformBack( old );
				return ;
			}
		}
		if( m_bpp == 4 || m_bpp == 8 )
		{
			if(m_lTransparecyColor==RGB(255,255,255) && m_lBackGroundColor==RGB(255,255,255))
			{
				
				m_MemDC.StretchBlt(m_pDC,dPoint,m_lInsideReviseX,m_lInsideReviseY,dPoint1,(int)m_nSrcW,(int)m_nSrcH);
				m_pDC->SetWorldTransformBack( old );
				return ;

			}
			else
			{
				m_MemDC.ConvertColorBlt(m_pDC,dPoint,m_lInsideReviseX,m_lInsideReviseY,dPoint1,(int)m_nSrcW,(int)m_nSrcH,m_lBackGroundColor,m_lTransparecyColor);
				m_pDC->SetWorldTransformBack( old );
				return ;
			}

		}
		
		if(m_bpp == 24)
		{
			if(m_lTransparecyColor==RGB(255,255,255) && m_lBackGroundColor==RGB(255,255,255))
			{

				m_MemDC.StretchBlt(m_pDC,dPoint,m_lInsideReviseX,m_lInsideReviseY,dPoint1,(int)m_nSrcW,(int)m_nSrcH);
				m_pDC->SetWorldTransformBack( old );
				return ;

			}
			else
			{
				m_MemDC.TransparentBlt(m_pDC,dPoint.p.x,dPoint.p.y,m_lInsideReviseX,m_lInsideReviseY,dPoint1.p.x,dPoint1.p.y,(int)m_nSrcW,(int)m_nSrcH,m_lTransparecyColor);
	
				m_pDC->SetWorldTransformBack( old );
				return ;
			}
		}
		if( m_bPng )
		{
			m_MemDC.AlphaBlend(m_pDC,dPoint,m_lInsideReviseX,m_lInsideReviseY,dPoint1,(int)m_nSrcW,(int)m_nSrcH);
			m_pDC->SetWorldTransformBack( old );
			return ;
		}
		else
		{
			m_MemDC.StretchBlt(m_pDC,dPoint,m_lInsideReviseX,m_lInsideReviseY,dPoint1,(int)m_nSrcW,(int)m_nSrcH);
			m_pDC->SetWorldTransformBack( old );
			return ;

		}



}
void Display::CPicMarkerSymbol::SelectDC(Display::CDC * pDC)
{ 
	float DestW,DestH;
		ISymbol::SelectDC(pDC);
		if( m_MemDC.GetBitmap() == NULL )
		{
			return ;
		}
		m_MemDC.CreateCompatibleDC( pDC );
		if( m_bpp != 1 )
			m_MemDC.SelectBitmap();


		if( m_nSrcW == -1 || m_nSrcH ==-1 )
		{
			return;
		}

		if(m_nSrcW>m_nSrcH)
		{
			DestW=m_nSrcW/(m_nSrcH*1.0f);
			DestH=m_nSrcH/(m_nSrcH*1.0f);
		}
		else
		{
			DestW = m_nSrcW/(m_nSrcW*1.0f);
			DestH = m_nSrcH/(m_nSrcW*1.0f);
		}

		m_lInsideReviseX = DestW * m_lMarkerSize ;
		m_lInsideReviseY = DestH * m_lMarkerSize;
		if( m_bpp == 1)
		{
			if(m_bReverseColor)
			{
				m_MemDC.SetBGColor(GetRValue(GetMarkColor()),GetGValue(GetMarkColor()),GetBValue(GetMarkColor()));
				m_MemDC.SetFGColor(GetRValue(GetBGColor()),GetGValue(GetBGColor()),GetBValue(GetBGColor()));
			}
			else
			{
				m_MemDC.SetBGColor(GetRValue(GetBGColor()),GetGValue(GetBGColor()),GetBValue(GetBGColor()));
				m_MemDC.SetFGColor(GetRValue(GetMarkColor()),GetGValue(GetMarkColor()),GetBValue(GetMarkColor()));
			}
			m_MemDC.SelectBitmap();
		}
	}

void Display::CPicMarkerSymbol::SetReadyDraw()
{

}
void Display::CPicMarkerSymbol::SetScale(float fScale)
{
		if(fScale<0)
		{
			return;
		}
		m_fScale=fScale;
		m_lDestW=(unsigned long)(m_lMarkerSize*m_fScale);
		m_lDestH=(unsigned long)(m_lMarkerSize*m_fScale);
}

float Display::CPicMarkerSymbol::GetScale()
{
	return m_fScale;

	

}

void Display::CPicMarkerSymbol::SetProperties(const char* PropertyName , const _variant_t& PropertyValue)
{
#define SETPROP(inVal,Val,inName,Name,VT,VT2) if( stricmp(inName,Name) == 0 ) { Val = (VT2)((VT)inVal);return; }
#define SETPROP2(Val,Name,VT) SETPROP( PropertyValue , Val , PropertyName , Name , VT , VT )


		SETPROP2( m_lBackGroundColor , "BACKGROUNDCOLOR" , unsigned long );
		SETPROP2( m_lTransparecyColor , "TRANSPARECYCOLOR" , unsigned long );
		SETPROP2( m_bReverseColor , "REVERSECOLOR" ,  bool );
		if( !stricmp( PropertyName, "PICMARKFILENAME" ) )
		{
			m_cPicPath = ( _bstr_t )PropertyValue;
			SetFileName( m_cPicPath );
			return;
		}

		IMarkerSymbol::SetProperties(PropertyName , PropertyValue);


}

_variant_t Display::CPicMarkerSymbol::GetProperties(const char* PropertyName)
{

	_variant_t vt;
	#define GETPROP(inName,Name,Val,T) if( stricmp(inName,Name) == 0 ) { vt = (T)Val;return vt; }
	#define GETPROP2(Val,Name,T) GETPROP(PropertyName , Name , Val , T )

		GETPROP2( m_lBackGroundColor , "BACKGROUNDCOLOR" , _variant_t );
		GETPROP2( m_lTransparecyColor , "TRANSPARECYCOLOR" , _variant_t);
		GETPROP2( m_bReverseColor , "REVERSECOLOR" ,  _variant_t );
		if( !stricmp( PropertyName,"IMAGEPALETTEARRAY" ))
		{      
			return ( long )m_MemDC.GetBitmapColor( m_bitmapData );
		}

		GETPROP2( m_bpp , "IMAGEBITCOUNT" ,  int );

		if( !stricmp( PropertyName, "PICMARKFILENAME" ) )
		{
			vt = m_cPicPath.c_str();
			return vt;
		}

	return IMarkerSymbol::GetProperties(PropertyName);

}

 void Display::CPicMarkerSymbol::Zoom(float rate)
 {
	 m_lMarkerSize=m_lMarkerSize * rate;
	
	 if( m_lMarkerSize < 1 )
	 { 
		 m_lMarkerSize=1;
	 }
	  IMarkerSymbol::Zoom(rate);
 }
 void * Display::CPicMarkerSymbol::GetPalColor()
 {

	 return NULL;
 }

 void Display::CPicMarkerSymbol::serialization(SYSTEM::IArchive & ar)
 { 

	 IMarkerSymbol::serialization(ar); 

	ar & (m_nSrcW);				
	ar & (m_nSrcH);				
	ar & (m_bPng);				
	ar & (m_bReverseColor);				
	ar & (m_lBackGroundColor);	
	ar & (m_lTransparecyColor); 
	ar & (m_lInsideReviseX);	
	ar & (m_lInsideReviseY);
 	ar & (m_fScale);
	ar & (m_lDestW);
	ar & (m_lDestH);
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

 void Display::CPicMarkerSymbol::OnUnitChanged(SYSTEM::SYS_UNIT_TYPE oldUnit , SYSTEM::SYS_UNIT_TYPE newUnit)
 {
	 IMarkerSymbol::OnUnitChanged(oldUnit , newUnit);

 }

 void Display::CPicMarkerSymbol::OnChangingInSelectDC()
 {
	 IMarkerSymbol::OnChangingInSelectDC();
 }

 void Display::CPicMarkerSymbol::ClearDC()
 {
	 IMarkerSymbol::ClearDC();
 }
