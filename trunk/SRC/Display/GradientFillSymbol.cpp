#include "stdafx.h"
#include "CDC.h"
#include "IArchive.h"
#include "GradientFillSymbol.h"

Display::CGradientFillSymbol::CGradientFillSymbol(void)
{
	m_typeGradientFill = Gradient_Linear;

	m_lBeginColor = RGB((((double) rand() / (double) 255) * 255 + 0) , (((double) rand() / (double) 255) * 255 + 0),
		(((double) rand() / (double) 255) * 255 + 0));
	
	m_lEndColor = RGB((((double) rand() / (double) 255) * 255 + 0) , (((double) rand() / (double) 255) * 255 + 0),
		(((double) rand() / (double) 255) * 255 + 0));
	
	m_nSegmentsNum = 30;

	m_nPercentage = 100;

	m_nAngle = 0;
}

Display::CGradientFillSymbol::CGradientFillSymbol(const Display::CGradientFillSymbol& toGradientFillSymbol)
{
	* this = toGradientFillSymbol;
}

Display::CGradientFillSymbol::~CGradientFillSymbol(void)
{
		ClearDC();
}


Display::CGradientFillSymbol& Display::CGradientFillSymbol::operator = (const Display::CGradientFillSymbol& toGradientFillSymbol)
{

		if( this == &toGradientFillSymbol )
			return *this;

	*(IFillSymbol*)this	= *(IFillSymbol*)&toGradientFillSymbol;

return *this;

}
void Display::CGradientFillSymbol::Draw(void* pObject)
{

	_ASSERT(pObject != NULL);
	
	std::vector<COLORREF> vecColorRamp;
	//创建渐变色
	CreateColorRamp( vecColorRamp );

	DIS_OBJ_TYPE type =((DIS_POLYGON *)pObject)->type;

	if(type==Dis_Polygon)
	{
		DIS_POLYGON  *dp= (DIS_POLYGON *)pObject;    //得到的数据
		DIS_RECT  rect ,rect1;					  //裁减体的外接矩形和外接正方形；
		int       lsize;					      //得到正方形边长的一半
		DIS_POINT pCenter;					  //1。。中心点 2。。
		XFORM old;

		DISPLAY_HANDLE hRgn = m_pDC->CreateClipPolygon(* dp);//创建裁减体
		
		DISPLAY_HANDLE_NODE * pHRgn = CDisplayCache::AddToDisplayCache( hRgn , m_pDC );
		CDisplayCache::UseCache( pHRgn , this );

		m_pDC->GetClipRegionBox( rect, hRgn );
		m_pDC->GetClipRegionBox( rect1, hRgn );
		lsize=this->GetSquare(&rect);//得到裁减体的外接正方形和正方形的长度的一半
		pCenter.p.x=rect1.left+((rect1.right-rect1.left)>>1)+1;
		pCenter.p.y=rect1.top+((rect1.bottom-rect1.top)>>1)+1;

		if( m_nAngle != 0 )
		{
			old = m_pDC->SetWorldTransform( m_nAngle , 1.0f , 1.0f , pCenter.p.x  , pCenter.p.y  );
		}
		
		DrawGradientSubparts( m_typeGradientFill, vecColorRamp, pCenter, rect, lsize );

		if( pHRgn != NULL)
		{
			CDisplayCache::ReleaseCache( pHRgn );
			pHRgn = NULL;
		}	

		if ( m_nAngle != 0 )
		{
			m_pDC->SetWorldTransformBack(old);
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
		int       lsize;					      //得到正方形边长的一半
		DIS_POINT	  pCenter;							//1。。中心点 2。。
		XFORM old;

		DISPLAY_HANDLE hRgn = m_pDC->CreateClipEllipse(boundRect);//创建裁减体
		DISPLAY_HANDLE_NODE * pHRgn = CDisplayCache::AddToDisplayCache( hRgn , m_pDC );
		CDisplayCache::UseCache( pHRgn , this );

		m_pDC->GetClipRegionBox( rect, hRgn );
		m_pDC->GetClipRegionBox( rect1, hRgn );
		lsize=this->GetSquare(&rect);//得到裁减体的外接正方形和正方形的长度的一半
		pCenter.p.x=rect1.left+((rect1.right-rect1.left)>>1)+1;
		pCenter.p.y=rect1.top+((rect1.bottom-rect1.top)>>1)+1;

		if( m_nAngle != 0 )
		{
			old = m_pDC->SetWorldTransform( m_nAngle , 1.0f , 1.0f , pCenter.p.x  , pCenter.p.y  );
		}



		DrawGradientSubparts( m_typeGradientFill, vecColorRamp, pCenter, rect, lsize );

		if( pHRgn != NULL)
		{
			CDisplayCache::ReleaseCache( pHRgn );
			pHRgn = NULL;
		}

		if ( m_nAngle != 0 )
		{
			m_pDC->SetWorldTransformBack(old);
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
		int       lsize;					      //得到正方形边长的一半
		DIS_POINT	  pCenter;							//1。。中心点 2。。
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

			if( m_nAngle != 0 )
			{
				old = m_pDC->SetWorldTransform( m_nAngle , 1.0f , 1.0f , pCenter.p.x  , pCenter.p.y  );
			}

			DrawGradientSubparts( m_typeGradientFill, vecColorRamp, pCenter, rect, lsize );

			if( pHRgn != NULL)
			{
				CDisplayCache::ReleaseCache( pHRgn );
				pHRgn = NULL;
			}

			if ( m_nAngle != 0 )
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

SYMBOL_TYPE Display::CGradientFillSymbol::GetType()
{
	return GRADIENT_FILL_SYMBOL;
}

void Display::CGradientFillSymbol::SelectDC(Display::CDC * pDC)
{

	ISymbol::SelectDC(pDC);


	if( m_bOutLine )
		m_OutLineSymbol->SelectDC( pDC );

}

void Display::CGradientFillSymbol::SetReadyDraw()
{
	//m_pDC->SelectObjInto(m_lBrushID);

	if(m_bOutLine)
		m_OutLineSymbol->SetReadyDraw();
}

void Display::CGradientFillSymbol::Zoom(float rate)
{
	if (m_OutLineSymbol)
	{
		m_OutLineSymbol->Zoom(rate);
	}
}

void Display::CGradientFillSymbol::serialization(SYSTEM::IArchive & ar)
{ 
	IFillSymbol::serialization(ar); 
	
	ar & m_lBeginColor;

	ar & m_lEndColor;

	ar & m_nSegmentsNum;

	ar & m_nPercentage;

	ar & m_nAngle;

	if( ar.IsSave() )
	{
		int i = m_typeGradientFill;
		ar & (i);
	}
	else
	{
		int i;
		ar & i;
		m_typeGradientFill = ( GRANDIENT_FILL_TYPE )i;
	}
}

void Display::CGradientFillSymbol::ClearDC()
{
	if( m_OutLineSymbol != NULL )
		m_OutLineSymbol->ClearDC();

	IFillSymbol::ClearDC();
}

void Display::CGradientFillSymbol::OnUnitChanged(SYSTEM::SYS_UNIT_TYPE oldUnit , SYSTEM::SYS_UNIT_TYPE newUnit)
{
	IFillSymbol::OnUnitChanged(oldUnit , newUnit);
}

void Display::CGradientFillSymbol::OnChangingInSelectDC()
{
	IFillSymbol::OnChangingInSelectDC();
}

void Display::CGradientFillSymbol::CreateColorRamp( std::vector<COLORREF> &vecColorRamp )
{

	vecColorRamp.clear();

	long lBeginR =GetRValue( m_lBeginColor );
	long lBeginG =GetGValue( m_lBeginColor );
	long lBeginB =GetBValue( m_lBeginColor );

	long lEndR =GetRValue( m_lEndColor );
	long lEndG =GetGValue( m_lEndColor );
	long lEndB =GetBValue( m_lEndColor );

	double dRInterVal = 0;
	double dGInterVal = 0;
	double dBInterVal = 0;

	dRInterVal = (double)( lEndR - lBeginR ) /  m_nSegmentsNum;
	dGInterVal = (double)( lEndG - lBeginG ) / m_nSegmentsNum;
	dBInterVal = (double)( lEndB - lBeginB ) / m_nSegmentsNum;
	
	for ( long i = 0; i < m_nSegmentsNum; ++i )
	{
		COLORREF color =  RGB( lBeginR + i*dRInterVal, lBeginG + i*dGInterVal, lBeginB + i*dBInterVal );

		vecColorRamp.push_back( color );
	}

}

void Display::CGradientFillSymbol::DrawGradientSubparts( GRANDIENT_FILL_TYPE type, const std::vector<COLORREF> &vecColorRamp, DIS_POINT &pCenter, DIS_RECT &rect, int lsize )
{
	switch( type )
	{
	//绘制线性渐变色
	case Gradient_Linear:
		{
			double dInterval = (double)( rect.right - rect.left ) * m_nPercentage  /  ( m_nSegmentsNum  * 100 );

			DISPLAY_HANDLE hPen = NULL;
			DISPLAY_HANDLE brush = NULL ;
			DISPLAY_HANDLE hOld;
			
			if ( m_nPercentage < 100 )
			{
				BRUSH_STYLE bs;
				bs.lColor = vecColorRamp[m_nSegmentsNum - 1];
				bs.Style = SOLID_BRUSH;

				brush = m_pDC->CreateBrush( bs );
				hOld = m_pDC->SelectObject( brush );

				m_pDC->FillRect( rect );
			}

			for ( long i = 0; i < m_nSegmentsNum; ++i )
			{
				DIS_RECT subRect;
				subRect.left  = rect.left + i * dInterval;
				subRect.right = rect.left + (i+1) * dInterval;
				subRect.bottom = rect.bottom;
				subRect.top = rect.top;

				if ( subRect.left == subRect.right )          //如果计算的彩色条宽度小于1 绘制短线 
				{
					LINE_STYLE ls;				//设置画笔
					memset( &ls , 0 , sizeof(ls) );
					ls.eStyle = SOLID;
					ls.lColor = vecColorRamp[i];
					ls.lWidth = 1;

					hPen = m_pDC->CreatePen( ls );
					hOld = m_pDC->SelectObject( hPen );


					DIS_LINE line;
					line.type = Dis_Line;
					line.Count=2;
					line.ps[0].x = subRect.left;
					line.ps[0].y = subRect.bottom;
					line.ps[1].x = subRect.left;
					line.ps[1].y = subRect.top;

					m_pDC->DrawPolyLines( line );
				}
				else
				{
					BRUSH_STYLE bs;
					bs.lColor = vecColorRamp[i];
					bs.Style = SOLID_BRUSH;

					brush = m_pDC->CreateBrush( bs );
					hOld = m_pDC->SelectObject( brush );

					m_pDC->FillRect( subRect );
				}

				if ( hPen != NULL )	
				{
                   DeleteObject( (HANDLE)hPen );
				   hPen =NULL;
				}
					
				if ( brush != NULL )
				{
                  DeleteObject( (HANDLE)brush );
				   brush =NULL;
				}
					
			}

			

		}
		break;
	
	//绘制矩形渐变
	case Gradient_Rectanglar:
		{
			long maxLength = rect.Width()/2;
			if ( rect.Height() > maxLength )
			{
				maxLength = rect.Height()/2;
			}

			double dInterval = (double)( maxLength ) * m_nPercentage  /  ( m_nSegmentsNum  * 100 );
			DIS_RECT subRect;

			BRUSH_STYLE bs;
			bs.Style = SOLID_BRUSH;

			DISPLAY_HANDLE brush = m_pDC->CreateBrush( bs );
			DISPLAY_HANDLE hOld = m_pDC->SelectObject( brush );
			
			if ( m_nPercentage < 100 )
			{
				BRUSH_STYLE bs;
				bs.lColor = vecColorRamp[m_nSegmentsNum - 1];
				bs.Style = SOLID_BRUSH;

				brush = m_pDC->CreateBrush( bs );
				hOld = m_pDC->SelectObject( brush );

				m_pDC->FillRect( rect );
			}

			for ( long i = m_nSegmentsNum; i > 0; i-- )
			{
				bs.lColor = vecColorRamp[i-1];
				brush = m_pDC->CreateBrush( bs );
				hOld = m_pDC->SelectObject( brush );

				subRect.left  = pCenter.p.x - i * dInterval;
				subRect.right = pCenter.p.x + i * dInterval;
				subRect.bottom = pCenter.p.y - i * dInterval;
				subRect.top = pCenter.p.y + i * dInterval;

				m_pDC->FillRect( subRect );
			}

			m_pDC->SelectObject( hOld );
			m_pDC->RemoveHandle( brush );
		}
		break;

	//绘制圆形渐变
	case Gradient_Circlar:
		{
			long maxLength = rect.Width()/2;
			if ( rect.Height() > maxLength )
			{
				maxLength = rect.Height()/2;
			}

			double dInterval = (double)( maxLength * 1.415 ) * m_nPercentage  /  ( m_nSegmentsNum  * 100 );

			//绘制圆
			DIS_CIRCLE circle;
			INT_POINT pt;
			pt.x = pCenter.p.x;
			pt.y = pCenter.p.y;
			circle.center = pt;

			BRUSH_STYLE bs;
			bs.Style = SOLID_BRUSH;

			DISPLAY_HANDLE brush = m_pDC->CreateBrush( bs );
			DISPLAY_HANDLE hOld = m_pDC->SelectObject( brush );

			if ( m_nPercentage < 100 )
			{
				BRUSH_STYLE bs;
				bs.lColor = vecColorRamp[m_nSegmentsNum - 1];
				bs.Style = SOLID_BRUSH;

				brush = m_pDC->CreateBrush( bs );
				hOld = m_pDC->SelectObject( brush );

				circle.Radio = maxLength * 1.415;

				m_pDC->FillCircle( circle );
			}

			for ( long i = m_nSegmentsNum; i > 0; i-- )
			{
				bs.lColor = vecColorRamp[i-1];
				bs.lColor = vecColorRamp[i-1];
				brush = m_pDC->CreateBrush( bs );
				hOld = m_pDC->SelectObject( brush );

				circle.Radio = dInterval * i;

				m_pDC->FillCircle( circle );
			}

			m_pDC->SelectObject( hOld );
			m_pDC->RemoveHandle( brush );
		}
		break;

	//默认绘制线性渐变
	default:
		{
			double dInterval = (double)( rect.right - rect.left ) * m_nPercentage  /  ( m_nSegmentsNum  * 100 );

			DISPLAY_HANDLE hPen = NULL;
			DISPLAY_HANDLE brush = NULL ;
			DISPLAY_HANDLE hOld;

			for ( long i = 0; i < m_nSegmentsNum; ++i )
			{
				DIS_RECT subRect;
				subRect.left  = rect.left + i * dInterval;
				subRect.right = rect.left + (i+1) * dInterval;
				subRect.bottom = rect.bottom;
				subRect.top = rect.top;

				if ( subRect.left == subRect.right )          //如果计算的彩色条宽度小于1 绘制短线 
				{
					LINE_STYLE ls;				//设置画笔
					memset( &ls , 0 , sizeof(ls) );
					ls.eStyle = SOLID;
					ls.lColor = vecColorRamp[i];
					ls.lWidth = 1;

					hPen = m_pDC->CreatePen( ls );
					hOld = m_pDC->SelectObject( hPen );


					DIS_LINE line;
					line.type = Dis_Line;
					line.Count=2;
					line.ps[0].x = subRect.left;
					line.ps[0].y = subRect.bottom;
					line.ps[1].x = subRect.left;
					line.ps[1].y = subRect.top;

					m_pDC->DrawPolyLines( line );
				}
				else
				{
					BRUSH_STYLE bs;
					bs.lColor = vecColorRamp[i];
					bs.Style = SOLID_BRUSH;

					brush = m_pDC->CreateBrush( bs );
					hOld = m_pDC->SelectObject( brush );

					m_pDC->FillRect( subRect );
				}
			}

			if ( hOld )
			{
				m_pDC->SelectObject( hOld );
				m_pDC->RemoveHandle( hOld );
			}

			if ( hPen != NULL )	
				m_pDC->RemoveHandle( hPen );
			if ( brush != NULL )
				m_pDC->RemoveHandle( brush );

		}
	}
}


void Display::CGradientFillSymbol::SetProperties(const char* PropertyName,const _variant_t& PropertyValue)
{
#define SETPROP(inVal,Val,inName,Name,VT,VT2) if( stricmp(inName,Name) == 0 ) { Val = (VT2)((VT)inVal);return; }
#define SETPROP2(Val,Name,VT) SETPROP( PropertyValue , Val , PropertyName , Name , VT , VT )
#define SETPROPEX(inVal,Val,inName,Name,VT,VT2) if( stricmp(inName,Name) == 0 ) { Val = (VT2)((VT)inVal);return; }
#define SETPROPEX2(Val,Name,VT,VT2) SETPROPEX( PropertyValue , Val , PropertyName , Name , VT , VT2)

	SETPROP2( m_nSegmentsNum, "SEGMENTCOUNT", long );
	SETPROP2( m_nAngle, "FILLANGLE", float );
	SETPROP2( m_nPercentage, "FILLPERCENT", long );
	SETPROPEX2( m_typeGradientFill, "GRADIENTTYPE", long,  GRANDIENT_FILL_TYPE );
	
	if( stricmp( PropertyName , "BEGINCOLOR" ) == 0 ) 
	{
		SetBeginColor((unsigned long)PropertyValue);
		return;
	}

	if( stricmp( PropertyName , "ENDCOLOR" ) == 0 ) 
	{
		SetEndColor((unsigned long)PropertyValue);
		return;
	}

	IFillSymbol::SetProperties( PropertyName, PropertyValue );
}

_variant_t Display::CGradientFillSymbol::GetProperties( const char* PropertyName )
{
	_variant_t vt;
#define GETPROP(inName,Name,Val,T) if( stricmp(inName,Name) == 0 ) { vt = (T)Val;return vt; }
#define GETPROP2(Val,Name,T) GETPROP(PropertyName , Name , Val , T )
	GETPROP2( m_typeGradientFill, "GRADIENTTYPE", int );
	GETPROP2( m_nSegmentsNum, "SEGMENTCOUNT", long );
	GETPROP2( m_nAngle, "FILLANGLE", float );
	GETPROP2( m_nPercentage, "FILLPERCENT", long );
	GETPROP2( m_lBeginColor, "BEGINCOLOR", unsigned long );
	GETPROP2( m_lEndColor, "ENDCOLOR", unsigned long );

	return IFillSymbol::GetProperties(PropertyName);
}

void Display::CGradientFillSymbol::SetBeginColor( COLORREF color)
{
	m_lBeginColor = color;
}

COLORREF Display::CGradientFillSymbol::GetBeginColor( void )
{
	return m_lBeginColor;
}

void Display::CGradientFillSymbol::SetEndColor( COLORREF color )
{
	m_lEndColor = color;
}

COLORREF Display::CGradientFillSymbol::GetEndColor( void )
{
	return m_lEndColor;
}

void Display::CGradientFillSymbol::SetGradientFillType( GRANDIENT_FILL_TYPE gradientType )
{
	m_typeGradientFill = gradientType;
}

GRANDIENT_FILL_TYPE Display::CGradientFillSymbol::GetGradientFillType( void )
{
		return m_typeGradientFill;
}

void Display::CGradientFillSymbol::SetSegmentsCount( long nCount )
{
	m_nSegmentsNum = nCount;
}

long Display::CGradientFillSymbol::GetSegmentsCount( void )
{
	return m_nSegmentsNum;
}

void Display::CGradientFillSymbol::SetPercent( long nPercent )
{
	m_nPercentage = nPercent;
}

long Display::CGradientFillSymbol::GetPercent( void )
{
	return m_nPercentage;
}

void Display::CGradientFillSymbol::SetAngle( float fAngle )
{
	m_nAngle = fAngle;
}

float Display::CGradientFillSymbol::GetAngle( void )
{
	return m_nAngle;
}