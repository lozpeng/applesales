#include "stdafx.h"
#include "CDC.h"
#include "BitmapOperation.h"

namespace Display
{

	CDC::CDC()
	{


		m_hDC = NULL;
		m_hOldPen = 0;
		m_hOldBrush = 0;
		m_hOlDIS_FONT = 0;
		m_bkOldColor = m_bkColor = 0;
		m_fgOldColor = m_fgColor = 0;
		m_fRateOfPixelAndMillimeter = 0.000000f;
		m_hBitmap = NULL;
		m_bSelfDC = false;
		m_hLockBitmap = NULL;
		m_PrintRgn = NULL;

		//1(CONSTRUCTIONEXCEPTION_EXP)

	}


	CDC::~CDC()
	{


		Destroy();
		//SetBkMode(m_hDC,OPAQUE);
		SetGraphicsMode( m_hDC , GM_COMPATIBLE );
		/////////清除CreateDC
		if( m_bSelfDC )
		{
			::DeleteDC( m_hDC );
			m_hDC = NULL;
			m_bSelfDC = false;
		}

		//
		if(m_elemBmp)
			::DeleteObject( m_elemBmp );
		if(m_geoBmp)
			::DeleteObject( m_geoBmp );
		if(m_geoSelBmp)
			::DeleteObject( m_geoSelBmp );
		if(m_elemBmp)
			::DeleteObject( m_elemBmp );
		if(m_editBmp)
			::DeleteObject( m_editBmp );
		if (m_tempBmp)
			::DeleteObject(m_tempBmp);

		if(m_hBitmap)
			::DeleteObject( m_hBitmap );
		if(m_hOldBitmap)
			::DeleteObject( m_hOldBitmap );
		if(m_hLockBitmap)
			::DeleteObject( m_hLockBitmap );
		///////////////////////////////////////////////////////////////////////////
		//1(DESTRUCTIONEXCEPTION_EXP)
	}



	Display::CDC* CDC::CloneDC()
	{
		//if ( m_hDC == NULL )
		//{
		//	return NULL;
		//}

		//HDC compatibleDC = NULL;
		//compatibleDC = ::CreateCompatibleDC( m_hDC );

		//if ( compatibleDC == NULL)
		//{
		//	return NULL;
		//}

		//HBITMAP compatibleBitmap = NULL;
		//long Width = GetDCWidth();
		//long Height= GetDCHeight();

		//compatibleBitmap = ::CreateCompatibleBitmap( m_hDC , Width , Height );

		//if ( compatibleBitmap == NULL )
		//{
		//	DeleteDC(compatibleDC);
		//	return NULL;
		//}

		//HBITMAP oldBitmap = (HBITMAP)::SelectObject(compatibleDC , compatibleBitmap);

		//Display::CDC *pDC = new Display::CDC;
		////pDC->m_hDC = compatibleDC;
		//pDC->SetDC((long)compatibleDC, Width, Height);
		//pDC->oldCloneBitmap = oldBitmap;

		//::BitBlt( compatibleDC , 0 , 0 , Width , Height , m_hDC , 0 , 0 , SRCCOPY);
		//return pDC;
		return NULL;

	}

	void CDC::ReleaseCloneDC(Display::CDC *destDC)
	{
		/*if ( destDC == NULL || destDC->oldCloneBitmap == NULL )
		{
		return;
		}
		DeleteObject(::SelectObject( destDC->m_hDC , destDC->oldCloneBitmap));
		DeleteDC(destDC->m_hDC);
		delete destDC;*/
	}

	long CDC::GetDCWidth()
	{
		return m_lDCWidth;
	}


	long CDC::GetDCHeight()
	{
		return m_lDCHeight;
	}

	///DrawPoint Method/////////////////////////////////////////////////////////////////////
	void CDC::DrawPoint(DIS_POINT& dPoint,unsigned long lColor)
	{

		SetPixel( m_hDC , dPoint.p.x , dPoint.p.y , lColor );

	}


	void CDC::DrawCharPoint(DIS_POINT& point,const wchar_t &wChar,int num)
	{

		TextOutW(m_hDC , point.p.x , point.p.y , &wChar , num);

	}

	void CDC::DrawCharMask(DIS_POINT pOffSet,LPCTSTR wStr)
	{

		BeginPath(m_hDC);
		TextOut(m_hDC , pOffSet.p.x , pOffSet.p.y , wStr , 2 );
		EndPath(m_hDC);
		StrokePath(m_hDC);

	}

	void CDC::MoveTo(int x, int y)
	{
		::MoveToEx(m_hDC,x,y,0);
	}

	void CDC::MoveTo(INT_POINT &point)
	{
		::MoveToEx(m_hDC,point.x,point.y,0);
	}

	void CDC::LineTo(int x, int y)
	{
		::LineTo(m_hDC,x,y);
	}

	//////DrawLine Method////////////////////////////////////////////////////////////////////
	inline void Display::CDC::DrawLine(DIS_POINT &from,DIS_POINT &to)
	{

		MoveToEx(m_hDC , from.p.x , from.p.y , 0);
		::LineTo(m_hDC , to.p.x , to.p.y);

	}

	//Draw PolyLine Method 
	inline void CDC::DrawPolyLines(const DIS_LINE &line)
	{
		
		/*POINT* pts = (POINT*)&(line.ps[0]);
		Gdiplus::PointF* pfs = new Gdiplus::PointF[line.Count];
		for(int i=0; i<line.Count; i++)
		{
		pfs[i].X = pts[i].x;
		pfs[i].Y = pts[i].y;
		}


		Gdiplus::Graphics graphics(m_hDC);
		Gdiplus::Pen pen(Gdiplus::Color(255,0,0),2);

		HPEN hPen = (HPEN)GetCurrentObject(m_hDC,OBJ_PEN);
		COLORREF  col = GetDCPenColor(m_hDC);
		int r= GetRValue(col);
		graphics.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);
		graphics.DrawLines(&pen,pfs,line.Count);

		delete []pfs;*/
		

		Polyline(m_hDC , (POINT*)&(line.ps[0]) , line.Count);

	}

	void CDC::DrawPolyLines(long &points,long count)
	{
		/*POINT* pts = (POINT*)&points;
		Gdiplus::PointF* pfs = new Gdiplus::PointF[count];
		for(int i=0; i<count; i++)
		{
		pfs[i].X = pts[i].x;
		pfs[i].Y = pts[i].y;
		}

		Gdiplus::Graphics graphics(m_hDC);
		Gdiplus::Pen pen(Gdiplus::Color(255,0,0),2);

		HPEN hPen = (HPEN)GetCurrentObject(m_hDC,OBJ_PEN);

		
		graphics.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);
		graphics.DrawLines(&pen,pfs,count);

		delete []pfs;*/
		
		Polyline(m_hDC , (POINT*)&points , count);

	}






	void CDC::DrawArc(DIS_RECT &rect,DIS_ENDPOINT &arc)
	{

		Arc( m_hDC , rect.left , rect.top , rect.right , rect.bottom , (int)arc.xRadial1 ,
			(int)arc.yRadial1 , (int)arc.xRadial2 , (int)arc.yRadial2 );

	}

	void CDC::DrawPolyBezier( DIS_BEZIER &bezier)
	{

		PolyBezier( m_hDC , (POINT*)&(bezier.ps[0]) , bezier.Count );

	}

	void CDC::DrawPolyBezier(long &points,long count)
	{

		PolyBezier(m_hDC , (POINT*)&points , count);

	}

	/////DrawPolygon Method/////////////////////////////////////////////////////////////////////
	inline void Display::CDC::DrawPolygon(DIS_POLYGON &polygon)
	{

		INT_POINT *pts = (INT_POINT*)polygon.GetPointAdr();

		HRGN hRgn = CreatePolyPolygonRgn(
			(POINT*)pts,        // pointer to array of points
			(const int *)polygon.RingCount,  // pointer to count of vertices
			polygon.Count,               // number of integers in array
			ALTERNATE        // polygon fill mode
			);

		HBRUSH hBrush = (HBRUSH)GetCurrentObject(m_hDC,OBJ_BRUSH);//(HBRUSH)CreateSolidBrush(RGB(0,0,255)); 

		::FillRgn( m_hDC , hRgn , hBrush);
		DeleteObject( hRgn );

	}

	void CDC::DrawPie(DIS_RECT &rect,DIS_ENDPOINT &pie)
	{

		BeginPath(m_hDC);
		Pie(m_hDC , rect.left , rect.top , rect.right , rect.bottom , (int)pie.xRadial1 , (int)pie.yRadial1 ,
			(int)pie.xRadial2 , (int)pie.yRadial2);
		EndPath(m_hDC);
		StrokePath(m_hDC);

	}

	void CDC::DrawEllipse(DIS_RECT &rect)
	{

		BeginPath(m_hDC);
		::Ellipse(m_hDC , rect.left , rect.top , rect.right , rect.bottom);
		EndPath(m_hDC);
		StrokePath(m_hDC);

	}

	void CDC::DrawCircle(DIS_CIRCLE &circle)
	{

		BeginPath(m_hDC);
		::Ellipse(m_hDC , (int)(circle.center.x - circle.Radio) , (int)(circle.center.y - circle.Radio) , 
			(int)(circle.center.x + circle.Radio) , (int)(circle.center.y + circle.Radio));
		EndPath(m_hDC);
		StrokePath(m_hDC);

	}

	void CDC::DrawArcPolygon(DIS_ARCPOLYGON *pArcPolygon)
	{
		if(pArcPolygon==NULL)
		{
			return;
		}
		DIS_SEGMENT *pSeg=NULL;
		RECT rect;
		BeginPath(m_hDC);
		for(long i=0;i<pArcPolygon->SegmentCount;i++)
		{
			pSeg =pArcPolygon->pSegments+i;
			//移动到第一个点
			if(i==0)
			{
				::MoveToEx(m_hDC,pSeg->points[0].x,pSeg->points[0].y,0);
			}
			switch(pSeg->type)
			{
			case ST_LINE:
				{
					::LineTo(m_hDC,pSeg->points[1].x,pSeg->points[1].y);
					break;
				}
			case ST_CIRCULARARC:
			case ST_ELLIPTICARC:
				{
					//设置弧段方向
					if(pSeg->direction==0)
					{
						SetArcDirection(m_hDC,AD_CLOCKWISE);
					}
					else
					{
						SetArcDirection(m_hDC,AD_COUNTERCLOCKWISE);
					}
					rect.left =pSeg->bound.left;
					rect.right =pSeg->bound.right;
					rect.top =pSeg->bound.top;
					rect.bottom =pSeg->bound.bottom;
					ArcTo(m_hDC,pSeg->bound.left,pSeg->bound.top,pSeg->bound.right,pSeg->bound.bottom,
						pSeg->points[0].x,pSeg->points[0].y,pSeg->points[1].x,pSeg->points[1].y);
					break;
				}
			case ST_BEZIERCURVE:
				{
					::PolyBezierTo(m_hDC,(const POINT*)(pSeg->points+1),3);
					break;
				}
			}
		}
		EndPath(m_hDC);
		StrokePath(m_hDC);
	}

	void CDC::DrawRect(DIS_RECT &rect)
	{

		BeginPath(m_hDC);
		Rectangle(m_hDC , rect.left , rect.top , rect.right , rect.bottom);
		EndPath(m_hDC);
		StrokePath(m_hDC);

	}

	void CDC::DrawRoundRect(DIS_RECT &rect,DIS_ELLIPSE &ellipse)
	{

		BeginPath(m_hDC);
		RoundRect(m_hDC , rect.left , rect.top , rect.right , rect.bottom , (int)ellipse.Width() , (int)ellipse.Height());
		EndPath(m_hDC);
		StrokePath(m_hDC);

	}

	//////Fill////////////////////////////////////////////////////////////////////
	void CDC::FillRgn(DISPLAY_HANDLE hRgn , DISPLAY_HANDLE hBrush )
	{

		::FillRgn(m_hDC , (HRGN)hRgn , (HBRUSH)hBrush);

	}

	void CDC::FillRect(DIS_RECT &rect)
	{
		RECT rc;
		rc.left =rect.left;
		rc.top =rect.top;
		rc.bottom =rect.bottom;
		rc.right =rect.right;

		::FillRect(m_hDC,&rc,(HBRUSH)GetCurrentObject(m_hDC,OBJ_BRUSH));
	}


	void CDC::FillPie(DIS_RECT &rect,DIS_ENDPOINT &pie)
	{

		BeginPath(m_hDC);
		Pie(m_hDC , rect.left , rect.top , rect.right , rect.bottom , (int)pie.xRadial1 ,
			(int)pie.yRadial1 , (int)pie.xRadial2 , (int)pie.yRadial2);
		EndPath(m_hDC);
		FillPath(m_hDC);

	}

	void CDC::FillEllipse(DIS_RECT &rect)
	{

		BeginPath(m_hDC);
		::Ellipse(m_hDC , rect.left , rect.top , rect.right , rect.bottom);
		EndPath(m_hDC);
		FillPath(m_hDC);

	}

	void CDC::FillCircle(DIS_CIRCLE &circle)
	{

		BeginPath(m_hDC);
		::Ellipse(m_hDC , (int)(circle.center.x - circle.Radio) , (int)(circle.center.y - circle.Radio) ,
			(int)(circle.center.x + circle.Radio) , (int)(circle.center.y + circle.Radio));
		EndPath(m_hDC);
		FillPath(m_hDC);

	}
	void CDC::FillRoundRect(DIS_RECT &rect , DIS_ELLIPSE &ellipse)
	{

		BeginPath(m_hDC);
		RoundRect(m_hDC , rect.left , rect.top , rect.right , rect.bottom , (int)ellipse.Width() , (int)ellipse.Height());
		EndPath(m_hDC);
		FillPath(m_hDC);

	}

	////////DrawAndFill/////////////////////////////////////////////////////////////////////////////
	void CDC::DrawAndFillRect(DIS_RECT &rect)
	{

		BeginPath(m_hDC);
		Rectangle(m_hDC , rect.left , rect.top , rect.right , rect.bottom);
		EndPath(m_hDC);
		StrokeAndFillPath(m_hDC);

	}
	void CDC::DrawAndFillPie(DIS_RECT &rect,DisEndPoint &pie)
	{

		BeginPath(m_hDC);
		Pie(m_hDC , rect.left , rect.top , rect.right , rect.bottom , (int)pie.xRadial1 , (int)pie.yRadial1 ,
			(int)pie.xRadial2 , (int)pie.yRadial2);
		EndPath(m_hDC);
		StrokeAndFillPath(m_hDC);

	}
	void CDC::DrawAndFillEllipse(DIS_RECT &rect)
	{

		BeginPath(m_hDC);
		::Ellipse(m_hDC , rect.left , rect.top , rect.right , rect.bottom);
		EndPath(m_hDC);
		StrokeAndFillPath(m_hDC);

	}

	void CDC::DrawAndFillRoundRect(DIS_RECT &rect,DIS_ELLIPSE &ellipse)
	{

		BeginPath(m_hDC);
		RoundRect(m_hDC , rect.left , rect.top , rect.right , rect.bottom, (int)ellipse.Width() , (int)ellipse.Height());
		EndPath(m_hDC);
		StrokeAndFillPath(m_hDC);

	}
	void CDC::DrawAndFillDiamond(DIS_POINT *points)
	{

		BeginPath(m_hDC);
		MoveToEx(m_hDC , points->p.x , points->p.y , 0);
		::LineTo(m_hDC , (points + 2)->p.x , (points+2)->p.y);
		::LineTo(m_hDC , (points + 1)->p.x , (points + 1)->p.y);
		::LineTo(m_hDC , (points + 3)->p.x , (points + 3)->p.y);
		::LineTo(m_hDC , points->p.x , points->p.y);

		EndPath(m_hDC);
		StrokeAndFillPath(m_hDC);

	}

	////Draw Text//////////////////////////////////////////////////////////////////////
	void CDC::DrawMultiText(DIS_RECT &rect,LPTSTR wStr,unsigned int dwDTFormat)
	{

		static RECT trect;
		trect.left =rect.left;
		trect.bottom =rect.bottom;
		trect.right =rect.right;
		trect.top =rect.top;
		DrawTextEx(m_hDC,wStr,(int)strlen(wStr),&trect,dwDTFormat,NULL);

	}

	void CDC::DrawText(DIS_RECT &rect,LPTSTR cStr,unsigned int dwDTFormat)
	{


		static RECT trect;
		trect.left =rect.left;
		trect.bottom =rect.bottom;
		trect.right =rect.right;
		trect.top =rect.top;

		//TextOut(m_hDC, rect.left, rect.top, cStr, 100);

		::DrawText(m_hDC , (LPCTSTR)cStr,(int)strlen(cStr) ,&trect, dwDTFormat);
		rect.left =trect.left;
		rect.bottom =trect.bottom;
		rect.right =trect.right;
		rect.top =trect.top;

	}


	//////////////////////////////////////////////////////////////////////////
	void CDC::RemoveHandle( void* handle)
	{
		//还原画布原设置
		::SelectObject( m_hDC , m_hOldPen);
		::SelectObject( m_hDC , m_hOldBrush);
		::SelectObject( m_hDC , m_hOlDIS_FONT);
		//::SelectObject( m_hDC , m_hOlDIS_FONT);
		SetBkColor( m_hDC , m_bkOldColor);
		SetTextColor( m_hDC , m_fgOldColor);
		HRGN tmp = 0;
		::SelectClipRgn(m_hDC , tmp);


		DeleteObject( (HANDLE)handle );
	}

	void CDC::SaveOldObj()
	{

	}

	void CDC::LoadOldObj()
	{

	}

	DISPLAY_HANDLE CDC::SelectObject(DISPLAY_HANDLE handle)
	{
		return (DISPLAY_HANDLE)::SelectObject( m_hDC , (HGDIOBJ)handle);
	}


	void CDC::SelectPrintClipRgn(DIS_RECT* disrect)
	{
		if(m_PrintRgn)
			DeleteObject((HRGN)m_PrintRgn);

		if(!disrect)
		{
			::SelectClipRgn(m_hDC, NULL);
			return;
		}

		m_PrintRgn = CreateClipRect(*disrect);
		::SelectClipRgn(m_hDC, (HRGN)m_PrintRgn);
	}

	HRGN CDC::GetPrintRgn()
	{
		return (HRGN)m_PrintRgn;
	}

	void CDC::BeginDisplay()
	{

		m_hOldPen=(HPEN)GetCurrentObject(m_hDC,OBJ_PEN);
		m_hOldBrush=(HBRUSH)GetCurrentObject(m_hDC,OBJ_BRUSH);
		m_hOlDIS_FONT=(HFONT)GetCurrentObject(m_hDC,OBJ_FONT);
		m_bkOldColor=GetBkColor(m_hDC);
		m_fgOldColor=GetTextColor(m_hDC);

	}

	void CDC::EndDisplay()
	{

		//还原画布原设置
		::SelectObject( m_hDC , m_hOldPen);
		::SelectObject( m_hDC , m_hOldBrush);
		::SelectObject( m_hDC , m_hOlDIS_FONT);
		SetBkColor( m_hDC , m_bkOldColor);
		SetTextColor( m_hDC , m_fgOldColor);

	}

	void CDC::SetDC( long hDC, long lWidth , long lHeight )
	{

		if( m_bSelfDC )
		{
			::DeleteDC( m_hDC );
			m_bSelfDC = false;
		}
		m_lDCWidth = lWidth;
		m_lDCHeight = lHeight;
		m_hDC=( HDC )hDC;

		//GetCurrentDCsRateOfPixelAndMillimeter();
		CacheBitmap(lWidth,lHeight);

		SetBkMode(m_hDC,TRANSPARENT);

		SetGraphicsMode(m_hDC,GM_ADVANCED);	
	}

	void CDC::CacheBitmap(long lWidth, long lHeight)
	{
		HDC hScreenDC = ::CreateDC("DISPLAY", NULL, NULL, NULL);
		if(m_hBitmap)
			::DeleteObject(m_hBitmap);
		m_hBitmap = ::CreateCompatibleBitmap(hScreenDC, lWidth, lHeight);

		if(m_elemBmp)
			::DeleteObject(m_elemBmp);
		m_elemBmp = ::CreateCompatibleBitmap(hScreenDC, lWidth, lHeight);


		if(m_geoBmp)
			::DeleteObject(m_geoBmp);
		m_geoBmp = ::CreateCompatibleBitmap(hScreenDC, lWidth, lHeight);

		if(m_geoSelBmp)
			::DeleteObject(m_geoSelBmp);
		m_geoSelBmp = ::CreateCompatibleBitmap(hScreenDC, lWidth, lHeight);

		if(m_editBmp)
			::DeleteObject(m_editBmp);
		m_editBmp = ::CreateCompatibleBitmap(hScreenDC, lWidth, lHeight);

		if(m_tempBmp)
			::DeleteObject(m_tempBmp);
		m_tempBmp = ::CreateCompatibleBitmap(hScreenDC,lWidth,lHeight);

		DeleteDC(hScreenDC);

		m_lDCWidth = lWidth;
		m_lDCHeight = lHeight;
	}

	void CDC::CreateExDC( long lHeight, long lWidth )
	{

		if( m_bSelfDC )
		{
			::DeleteDC( m_hDC );
			m_bSelfDC = false;
		}
		m_lDCWidth = lWidth;
		m_lDCHeight = lHeight;

		HDC hdcScreen = ::CreateDCA("DISPLAY", NULL, NULL, NULL); 
		HDC hDC = ::CreateCompatibleDC(hdcScreen); 

		m_hBitmap = ::CreateCompatibleBitmap(hdcScreen,lWidth,lHeight);  
		m_hOldBitmap = (HBITMAP)::SelectObject( m_hDC , m_hBitmap );
		//	m_hBitmap = (HBITMAP)::SelectObject( m_hDC , m_hBitmap );//无用代码
		DeleteDC(hdcScreen);
		SetDC( (long)hDC , lWidth , lHeight );
		m_bSelfDC = false;

	}

	long CDC::GetSafeHdc()
	{
		return (long)m_hDC;
	}

	//HBITMAP& CDC::GetBitmap()
	//{
	//	return m_hBitmap;
	//}

	DISPLAY_HANDLE CDC::CreateBrush(const BRUSH_STYLE &style)
	{
		LOGBRUSH lb;
		memset(&lb,0,sizeof(lb));
		lb.lbColor = style.lColor;
		lb.lbHatch = style.Hatch;
		lb.lbStyle = style.Style;
		HBRUSH hBrush = CreateBrushIndirect(&lb);
		if( !hBrush )
			//OTFALSERETURN(0,"Error:Create brush fail");

			return (DISPLAY_HANDLE)hBrush;
	}


	/////////////////////////////////////////////////////////////////////////////////////
	XFORM CDC::SetWorldTransform(float angle, float scalex, float scaley, const long OffsetX, const long OffsetY)
	{
		XFORM oldxform;

		::GetWorldTransform( m_hDC , &oldxform );

		XFORM xf;
		xf.eM11=1;
		xf.eM12=0;
		xf.eM21=0;
		xf.eM22=1;
		xf.eDx=(float)OffsetX;
		xf.eDy=(float)OffsetY;
		ModifyWorldTransform(m_hDC,&xf,MWT_LEFTMULTIPLY);

		xf.eM11=(float)cos(angle);
		xf.eM12=(float)sin(angle);
		xf.eM21=-xf.eM12;
		xf.eM22=xf.eM11;
		xf.eDx=0.0;
		xf.eDy=0.0;
		ModifyWorldTransform(m_hDC,&xf,MWT_LEFTMULTIPLY);

		xf.eM11=scalex;
		xf.eM12=0.0;
		xf.eM21=0.0;
		xf.eM22=scaley;
		xf.eDx=0.0;
		xf.eDy=0.0;
		ModifyWorldTransform(m_hDC,&xf,MWT_LEFTMULTIPLY);

		xf.eM11=1;
		xf.eM12=0;
		xf.eM21=0;
		xf.eM22=1;
		xf.eDx=-(long)OffsetX;
		xf.eDy=-(long)OffsetY;
		ModifyWorldTransform(m_hDC,&xf,MWT_LEFTMULTIPLY);

		return oldxform;
		//OTEND(oldxform,oldxform);
	}

	void CDC::SetWorldTransformBack(XFORM oldform)
	{
		::SetWorldTransform( m_hDC , &oldform );
	}

	//////////////////////////////////////////////////////////////////////////

	bool CDC::SetBGColor(BYTE r,BYTE g,BYTE b)
	{
		return Display::CBitmapOperation::SetBGColor( m_hBitmap, r, g, b );

	}

	void CDC::SetBGColor(unsigned long lColor)
	{

		m_bkColor = lColor;
		SetBkColor( m_hDC , lColor );

	}

	bool CDC::SetFGColor(BYTE r,BYTE g,BYTE b)
	{
		return Display::CBitmapOperation::SetFGColor( m_hBitmap, r, g, b );

	}

	void CDC::SetFGColor(unsigned long lColor)
	{

		SetTextColor( m_hDC , lColor );

	}

	unsigned long  CDC::GetFGColor()
	{
		return GetTextColor(m_hDC);
	}
	unsigned long  CDC::GetBGColor()
	{
		return ::GetBkColor(m_hDC);
	}

	//////////////////////////////////////////////////////////////////////////
	void  CDC::LoadImageFromBuffer( void * pBitmapInfo )
	{
		if(m_hBitmap != NULL)
		{
			DeleteObject(m_hBitmap);
		}
		m_hBitmap = Display::CBitmapOperation::LoadIMG( pBitmapInfo);
	}
	void* CDC::LoadImageFromFile( std::string strFile, bool & bPNG ,int & nLens)
	{
		if(m_hBitmap != NULL)
		{
			DeleteObject(m_hBitmap);
		}
		void * bitmapData = Display::CBitmapOperation::LoadIMG( strFile , bPNG ,m_hBitmap ,nLens);
		m_bPNG = bPNG;

		return bitmapData;
	}

	void  CDC::GetImageInfo( IMAGE_INFO & Image_Info ,void * BitmapData )
	{
		if( BitmapData == NULL )
		{
			Image_Info.vDataColor = NULL;
			return ;
		}
		Display::CBitmapOperation::GetImageInfo(  Image_Info, BitmapData );
	}

	void CDC::GetFontInfo(long &lWidth,long &lHeight,LPCTSTR wChar,int num)
	{
		SIZE ls;
		GetTextExtentPoint32(m_hDC,wChar,num,&ls);
		lWidth=ls.cx;
		lHeight=ls.cy;
	}

	void CDC::FreeImageBuffer( void * pBitmapInfo )
	{

		free( pBitmapInfo );

	}

	void* CDC::SaveFromBuffer( void* pBITMAPINFO , int & nLens )
	{
		if( pBITMAPINFO != NULL )
		{
			FreeImageBuffer( pBITMAPINFO );
		}
		return Display::CBitmapOperation::SaveToBuffer( m_hBitmap, nLens );
	}

	void* CDC::NewImageBuffer( int BufferSize )
	{
		return ( void * )malloc( BufferSize);
	}

	//////////////////////////////////////////////////////////////////////////
	void CDC::DrawPolygon(long lCount,long &dPoints)
	{

		::Polygon(m_hDC , (POINT*)&dPoints , lCount);

	}



	inline void CDC::Circle(const DIS_RECT &circle)
	{

		::Ellipse(m_hDC , circle.left , circle.top , circle.right , circle.bottom);

	}

	//////////////////////////////////////////////////////////////////////////
	void CDC::PolyBezierTo(DIS_POINT* points , unsigned long cCount)
	{

		::PolyBezierTo(m_hDC, (POINT*)&points, cCount);

	}


	//////////////////////////////////////////////////////////////////////////
	void CDC::Destroy()
	{
		if( m_hBitmap != NULL )
		{
			::SelectObject( m_hDC , m_hOldBitmap );
			::DeleteObject( m_hBitmap );
		}
	}

	void CDC::CreateCompatibleDC( Display::CDC *pDC)
	{

		if( m_bSelfDC )
		{
			::DeleteDC( m_hDC );
			m_bSelfDC = false;
		}
		m_hDC = ::CreateCompatibleDC( pDC->m_hDC );
		m_bSelfDC = true;

	}

	void CDC::CreateCompatibleBitmap( Display::CDC *pDC,long lWidth, long lHeight)
	{

		if( m_hDC != NULL && m_hBitmap == NULL)
		{
			m_hBitmap = ::CreateCompatibleBitmap(pDC->m_hDC,lWidth,lHeight);
			if( m_hBitmap != NULL )
			{
				m_hOldBitmap = (HBITMAP)::SelectObject(m_hDC ,m_hBitmap);
			}
		}
		else
		{
			::SelectObject( m_hDC , m_hOldBitmap );
			::DeleteObject( m_hBitmap );
			m_hBitmap = ::CreateCompatibleBitmap(pDC->m_hDC,lWidth,lHeight);
			if( m_hBitmap != NULL )
			{
				m_hOldBitmap = (HBITMAP)::SelectObject(m_hDC ,m_hBitmap);
			}
		}


	}

	void CDC::FillArcPolygon(DIS_ARCPOLYGON *pArcPolygon)
	{
		if(pArcPolygon==NULL)
		{
			return;
		}
		DIS_SEGMENT *pSeg=NULL;
		RECT rect;
		BeginPath(m_hDC);
		for(long i=0;i<pArcPolygon->SegmentCount;i++)
		{
			pSeg =pArcPolygon->pSegments+i;
			//移动到第一个点
			if(i==0)
			{
				::MoveToEx(m_hDC,pSeg->points[0].x,pSeg->points[0].y,0);
			}
			switch(pSeg->type)
			{
			case ST_LINE:
				{
					::LineTo(m_hDC,pSeg->points[1].x,pSeg->points[1].y);
					break;
				}
			case ST_CIRCULARARC:
			case ST_ELLIPTICARC:
				{
					//设置弧段方向
					if(pSeg->direction==0)
					{
						SetArcDirection(m_hDC,AD_CLOCKWISE);
					}
					else
					{
						SetArcDirection(m_hDC,AD_COUNTERCLOCKWISE);
					}
					rect.left =pSeg->bound.left;
					rect.right =pSeg->bound.right;
					rect.top =pSeg->bound.top;
					rect.bottom =pSeg->bound.bottom;
					ArcTo(m_hDC,pSeg->bound.left,pSeg->bound.top,pSeg->bound.right,pSeg->bound.bottom,
						pSeg->points[0].x,pSeg->points[0].y,pSeg->points[1].x,pSeg->points[1].y);
					break;
				}
			case ST_BEZIERCURVE:
				{
					::PolyBezierTo(m_hDC,(const POINT*)(pSeg->points+1),3);
					break;
				}
			}
		}
		EndPath(m_hDC);
		FillPath(m_hDC);


	}

	DISPLAY_HANDLE CDC::CreateFont(const DIS_FONT &font)
	{

		if( m_hDC == NULL )
		{   
			//OTFALSERETURN(0,"Error:CtoDC is not exist")
		}
		LOGFONT lf;	 
		lf.lfHeight		    =font.lfHeight;
		lf.lfWidth          = font.lfWidth;
		lf.lfEscapement     = font.lfEscapement ;
		lf.lfOrientation    = font.lfOrientation ;
		lf.lfWeight         = font.lfWeight;
		lf.lfItalic         = font.lfItalic;
		lf.lfUnderline      = font.lfUnderline;
		lf.lfStrikeOut      = font.lfStrikeOut;
		lf.lfCharSet        = font.lfCharSet ;
		lf.lfOutPrecision   = font.lfOutPrecision;
		lf.lfClipPrecision  = font.lfClipPrecision;
		lf.lfQuality        = font.lfQuality;
		lf.lfPitchAndFamily = font.lfPitchAndFamily;
		strcpy(lf.lfFaceName,font.lfFaceName) ;

		HFONT tmpFont=0;
		tmpFont=CreateFontIndirect(&lf);
		if( tmpFont == NULL )
		{
			//OTFALSERETURN(NULL,"Error:Create pen fail")
		}
		else
		{
			return (DISPLAY_HANDLE)tmpFont;
		}
		return NULL;
	}

	DISPLAY_HANDLE CDC::CreateSolidBrush(unsigned long color)
	{
		return ::CreateSolidBrush(color);
	}

	DISPLAY_HANDLE CDC::CreatePen(const LINE_STYLE &style)
	{

		HPEN hPen = NULL;

		if(m_hDC )
		{
			if( style.bExt )	
			{
				//启用扩展笔
				LOGBRUSH lb;
				lb.lbStyle=style.lbStyle;
				lb.lbColor=style.lColor;
				lb.lbHatch=style.lbHatch;
				hPen = ExtCreatePen( style.eExtStyle , style.lWidth , &lb , style.dwStyleCount , style.lpStyle );
			}
			else
			{	
				hPen = ::CreatePen( style.eStyle , (int)style.lWidth , style.lColor );
			}

			if( !hPen )
			{
				//OTFALSERETURN(NULL,"Error:Create pen fail")
			}
			else
			{
				return (DISPLAY_HANDLE)hPen;
			}
		}
	}


	void* CDC::GetBitmapColor( void * Bitmapdata )
	{
		return Display::CBitmapOperation::GetBitmapColor( Bitmapdata );
	}

	void CDC::SelectBitmap(DRAW_CONTENT drawcontent)
	{
		switch(drawcontent)
		{
		case drawGeography:
			::SelectObject(m_hDC, m_geoBmp);
			break;
		case drawGeoSelection:
			::SelectObject(m_hDC, m_geoSelBmp);
			break;
		case drawEdit:
			::SelectObject(m_hDC, m_editBmp);
			break;
		case drawElement:
			::SelectObject(m_hDC, m_elemBmp);
			break;
		case drawTempObj:
			::SelectObject(m_hDC,m_tempBmp);
			break;
		case drawAll:
			::SelectObject(m_hDC, m_hBitmap);
			break;
		default:
			::SelectObject(m_hDC, m_hBitmap);
			break;
		}
	}

	HBITMAP& CDC::GetBitmap(DRAW_CONTENT drawcontent)
	{
		switch(drawcontent)
		{
		case drawGeography:
			return m_geoBmp;
			break;
		case drawGeoSelection:
			return m_geoSelBmp;
			break;
		case drawEdit:
			return m_editBmp;
			break;
		case drawElement:
			return m_elemBmp;
			break;
		case drawTempObj:
			return m_tempBmp;
			break;
		case drawAll:
			return m_hBitmap;
			break;
		default:
			return m_hBitmap;
			break;
		}
	}


	//////////////////////////////////////////////////////////////////////////
	void CDC::ConvertColorBlt( CDC  *dcDest,   
		DIS_POINT PointDest,	
		int nWidthDest,     
		int nHeightDest,    
		DIS_POINT PointSrc,	
		int nWidthSrc,      
		int nHeightSrc,     
		UINT uSrcColor,		
		UINT uDestColor		
		)
	{

		if(!m_hDC)
		{
			//OTFALSERETURN_NOVAL("Error:Handle to DC is invalid")
		}
		if(!dcDest->m_hDC)
		{
			//OTFALSERETURN_NOVAL("Error:Handle to DC is invalid")
		}
		SetStretchBltMode(dcDest->m_hDC,COLORONCOLOR);
		HBITMAP hOldImageBMP, hImageBMP = ::CreateCompatibleBitmap(dcDest->m_hDC, nWidthDest, nHeightDest);	// 创建兼容位图
		HBITMAP hOldMaskBMP, hMaskBMP = CreateBitmap(nWidthDest, nHeightDest, 1, 1, NULL);			// 创建单色掩码位图
		HDC		hImageDC = ::CreateCompatibleDC(dcDest->m_hDC);
		HDC		hMaskDC = ::CreateCompatibleDC(dcDest->m_hDC);
		hOldImageBMP = (HBITMAP)::SelectObject(hImageDC, hImageBMP);
		hOldMaskBMP = (HBITMAP)::SelectObject(hMaskDC, hMaskBMP);

		// 将源DC中的位图拷贝到临时DC中
		if (nWidthDest == nWidthSrc )
			::BitBlt(hImageDC, 0, 0, nWidthDest, nHeightDest, m_hDC, PointSrc.p.x, PointSrc.p.y, SRCCOPY);
		else
			::StretchBlt(hImageDC, 0, 0, nWidthDest, nHeightDest, 
			m_hDC, PointSrc.p.x, PointSrc.p.y, nWidthSrc, nHeightSrc, SRCCOPY);

		// 设置透明色
		SetBkColor(hImageDC, uSrcColor);

		// 生成透明区域为白色，其它区域为黑色的掩码位图
		::BitBlt(hMaskDC, 0, 0, nWidthDest, nHeightDest, hImageDC, 0, 0, SRCCOPY);

		// 生成透明区域为黑色，其它区域保持不变的位图
		SetBkColor(hImageDC, RGB(1,2,2));
		SetTextColor(hImageDC, RGB(255,255,255));
		::BitBlt(hImageDC, 0, 0, nWidthDest, nHeightDest, hMaskDC, 0, 0, SRCAND);

		// 透明部分保持屏幕不变，其它部分变成黑色
		SetBkColor(dcDest->m_hDC,uDestColor);
		SetTextColor(dcDest->m_hDC,RGB(1,2,2));
		::BitBlt(dcDest->m_hDC, PointDest.p.x, PointDest.p.y, nWidthDest, nHeightDest, hMaskDC, 0, 0, SRCAND);

		// "或"运算,生成最终效果
		::BitBlt(dcDest->m_hDC, PointDest.p.x, PointDest.p.y, nWidthDest, nHeightDest, hImageDC, 0, 0, SRCPAINT);

		::SelectObject(hImageDC, hOldImageBMP);
		DeleteDC(hImageDC);
		::SelectObject(hMaskDC, hOldMaskBMP);
		DeleteDC(hMaskDC);
		DeleteObject(hImageBMP);
		DeleteObject(hMaskBMP);

	}


	void CDC::BitBlt( CDC *dcDest,  DIS_POINT PointDest,  int cx,  int cy, 
		DIS_POINT PointSrc,unsigned long rop  )
	{

		::BitBlt(dcDest->m_hDC,PointDest.p.x,PointDest.p.y,cx,cy,m_hDC, PointSrc.p.x,PointSrc.p.y,rop);

	}



	void  CDC::StretchBlt( CDC *dcDest,  DIS_POINT PointDest, int wDest, int hDest, 
		DIS_POINT PointSrc,  int wSrc,  int hSrc,unsigned long rop )
	{

		SetStretchBltMode( dcDest->m_hDC , COLORONCOLOR );

		::StretchBlt(dcDest->m_hDC,PointDest.p.x,PointDest.p.y,wDest,hDest,m_hDC,PointSrc.p.x,PointSrc.p.y,wSrc,hSrc,rop);


	}

	void CDC::TransparentBlt(CDC *dcDest, int x, int y,int wDest, int hDest, int x1, int y1, int wSrc,int hSrc,unsigned long backColor )
	{
		::TransparentBlt(dcDest->m_hDC, x, y, wDest, hDest, m_hDC, x1, y1, wSrc,hSrc, backColor);
	}

	void  CDC::AlphaBlend( CDC * dcDest,  DIS_POINT PointDest,int wDest, int hDest,
		DIS_POINT PointSrc,  int wSrc,int hSrc, unsigned char AlphaVal,unsigned char AlphaFormat)
	{

		SetStretchBltMode(dcDest->m_hDC,COLORONCOLOR);

		BLENDFUNCTION  bl;
		bl.AlphaFormat = AlphaFormat ;
		bl.BlendFlags = 0;
		bl.BlendOp = AC_SRC_OVER;
		bl.SourceConstantAlpha = AlphaVal;
		::AlphaBlend( dcDest->m_hDC ,PointDest.p.x,PointDest.p.y,wDest,hDest,m_hDC, PointSrc.p.x ,PointSrc.p.y ,wSrc,hSrc,bl );

	}

	//////////////////////////////////////////////////////////////////////////
	DISPLAY_HANDLE CDC::CreateClipPolygon(const DIS_POLYGON &polygon)
	{

		if(!m_hDC)
		{	
			//OTFALSERETURN(0,"Error:CtoDC is not exist")			
		}

		return CreatePolyPolygonRgn((POINT*)(const_cast<DIS_POLYGON&>(polygon).GetPointAdr()), (int*)&polygon.RingCount[0] , polygon.Count , ALTERNATE);  
		//OTEND(0,0)
	}

	DISPLAY_HANDLE CDC::CreateClipArcPolygon(const DIS_ARCPOLYGON *pArcPolygon)
	{
		if(!m_hDC)
		{	
			return NULL;			
		}
		DIS_SEGMENT *pSeg=NULL;
		BeginPath(m_hDC);
		for(long i=0;i<pArcPolygon->SegmentCount;i++)
		{
			pSeg =pArcPolygon->pSegments+i;
			//移动到第一个点
			if(i==0)
			{
				::MoveToEx(m_hDC,pSeg->points[0].x,pSeg->points[0].y,0);
			}
			switch(pSeg->type)
			{
			case ST_LINE:
				{
					::LineTo(m_hDC,pSeg->points[1].x,pSeg->points[1].y);
					break;
				}
			case ST_CIRCULARARC:
			case ST_ELLIPTICARC:
				{
					//设置弧段方向
					if(pSeg->direction==0)
					{
						SetArcDirection(m_hDC,AD_CLOCKWISE);
					}
					else
					{
						SetArcDirection(m_hDC,AD_COUNTERCLOCKWISE);
					}

					ArcTo(m_hDC,pSeg->bound.left,pSeg->bound.top,pSeg->bound.right,pSeg->bound.bottom,
						pSeg->points[0].x,pSeg->points[0].y,pSeg->points[1].x,pSeg->points[1].y);
					break;
				}
			case ST_BEZIERCURVE:
				{
					::PolyBezierTo(m_hDC,(const POINT*)(pSeg->points+1),3);
					break;
				}
			}
		}
		EndPath(m_hDC);

		return PathToRegion(m_hDC);

	}

	DISPLAY_HANDLE CDC::CreateClipEllipse(const DIS_RECT &rect)
	{
		if(!m_hDC)
		{	
			return NULL;			
		}
		return CreateEllipticRgn(rect.left,rect.top,rect.right,rect.bottom);

	}

	DIS_RECT& CDC::GetClipRegionBox(DIS_RECT& rect,DISPLAY_HANDLE handle)
	{
		static RECT trect;
		GetRgnBox((HRGN)handle , &trect);
		rect.top =trect.top;
		rect.bottom =trect.bottom;
		rect.left =trect.left;
		rect.right =trect.right;
		return rect;
	}


	DISPLAY_HANDLE CDC::CreateClipRect(const DIS_RECT& rect)
	{

		if(!m_hDC)
		{	
			//OTFALSERETURN(0,"Error:CtoDC is not exist")			
		}

		return (HRGN)CreateRectRgn(rect.left , rect.top , rect.right , rect.bottom);
		//OTEND(0,0)
	}

	//////////////////////////////////////////////////////////////////////////
	DISPLAY_HANDLE CDC::CreateExtRegion(DISPLAY_HANDLE handle , XFORM form)
	{

		DWORD gdiHandle_Num = GetRegionData((HRGN)handle , 0 , NULL);
		LPRGNDATA data=(LPRGNDATA)malloc(sizeof(byte) * gdiHandle_Num);

		GetRegionData((HRGN)handle , gdiHandle_Num , data);
		return ::ExtCreateRegion(&form , gdiHandle_Num , data);	
		//OTEND(0,0)
	}

	DISPLAY_HANDLE CDC::CreatePolygonRgn(CONST DIS_POINT *lppt, int cPoints, int fnPolyFillMode )
	{
		return (DISPLAY_HANDLE)::CreatePolygonRgn( (POINT*)lppt , cPoints ,fnPolyFillMode);
	}

	//////////////////////////////////////////////////////////////////////////
	float CDC::GetCreateDCsRateOfPixelAndMillimeter()		//创建屏幕dc得到毫米与像素的比例
	{
		float fPelsToMmRate = 0.000000f;
		HDC dis = NULL;
		dis = CreateDC( "DISPLAY" , NULL , NULL , NULL );
		if ( dis == NULL ) 
		{
			return 0.000000f;
		}

		float vertRate,herzRate;
		if( GetDeviceCaps( dis , PHYSICALWIDTH ) == 0 && GetDeviceCaps( dis , PHYSICALHEIGHT )== 0 )
		{
			vertRate = (double)::GetDeviceCaps( dis , VERTSIZE )  / (double)GetDeviceCaps( dis , VERTRES );
			herzRate = (double)::GetDeviceCaps( dis , HORZSIZE )  / (double)GetDeviceCaps( dis , HORZRES );
		}
		else
		{
			vertRate = (double)::GetDeviceCaps( dis , VERTSIZE )  / (double)(GetDeviceCaps( dis , PHYSICALWIDTH ) + GetDeviceCaps( dis , PHYSICALOFFSETX ));
			herzRate = (double)::GetDeviceCaps( dis , HORZSIZE )  / (double)(GetDeviceCaps( dis , PHYSICALHEIGHT ) + GetDeviceCaps( dis , PHYSICALOFFSETY ));
		}
		fPelsToMmRate = (vertRate + herzRate) / 2;
		DeleteDC(dis);

		return fPelsToMmRate;
	}

	float CDC::GetRateValueOfPixelAndMillimeter()
	{
		return m_fRateOfPixelAndMillimeter;
	}

	void CDC::ConverChar(LPCWSTR wStr,char *pStore)
	{

		DWORD charset=(DWORD)GetTextCharset(m_hDC);
		CHARSETINFO csinfo={0};
		TranslateCharsetInfo(&charset,&csinfo,TCI_SRCCHARSET);
		//WideCharToMultiByte(CP_ACP,WC_COMPOSITECHECK,wStr , 1,pStore, 2 ,NULL,NULL);
		//WideCharToMultiByte(CP_UTF8 , NULL ,wStr , 0,pStore, 3 ,NULL,NULL);
		int size = WideCharToMultiByte(CP_UTF8 , 0 ,wStr , -1, NULL, 0 , NULL, NULL);
		WideCharToMultiByte(CP_UTF8 ,0 ,wStr , -1, pStore, size , NULL, NULL);
		//WideCharToMultiByte(CP_UTF8 , NULL ,wStr , 1,pStore, WideCharToMultiByte(CP_UTF8 , NULL ,wStr , 0,pStore, 3 ,NULL,NULL) ,NULL,NULL);

	}

	BOOL CDC::IsPTInRect(DIS_RECT &rect,DIS_POINT &point)
	{
		static RECT trect;
		trect.left =rect.left;
		trect.bottom =rect.bottom;
		trect.right =rect.right;
		trect.top =rect.top;
		return PtInRect(&trect , *(POINT*)&point.p);
	}

	BOOL CDC::IsPTInRegion(DIS_POINT &point , DISPLAY_HANDLE handle)
	{
		return PtInRegion((HRGN)handle , point.p.x , point.p.y);
	}

	void  CDC::BitBlt( DRAW_CONTENT BmpDest,  int x, int y,  int cx,  int cy, 
		DRAW_CONTENT BmpSrc, int x1, int y1, unsigned long rop)
	{
		//创建临时destHdc，选择BmpDest
		HBITMAP oldDestBmp = (HBITMAP)::SelectObject(m_hDC, GetBitmap(BmpDest));

		//创建临时SrcHdc，选择BmpSrc
		HDC SrcHdc = ::CreateCompatibleDC(m_hDC);
		HBITMAP oldSrcBmp = (HBITMAP)::SelectObject(SrcHdc, GetBitmap(BmpSrc));

		//拷贝
		::BitBlt(m_hDC, x, y, cx, cy, SrcHdc, x1, y1, rop);

		//释放句柄
		::SelectObject(m_hDC, oldDestBmp);
		::SelectObject(SrcHdc, oldSrcBmp);
		::DeleteObject(SrcHdc);
	}

	void CDC::TransparentBlt( DRAW_CONTENT BmpDest,  int x, int y,int wDest, int hDest,
		DRAW_CONTENT BmpSrc,  int x1, int y1, int wSrc,int hSrc,unsigned long backColor )
	{
		//创建临时destHdc，选择BmpDest
		HBITMAP oldDestBmp = (HBITMAP)::SelectObject(m_hDC, GetBitmap(BmpDest));

		//创建临时SrcHdc，选择BmpSrc
		HDC SrcHdc = ::CreateCompatibleDC(m_hDC);
		HBITMAP oldSrcBmp = (HBITMAP)::SelectObject(SrcHdc, GetBitmap(BmpSrc));

		//拷贝
		::TransparentBlt(m_hDC, x, y, wDest, hDest, SrcHdc, x1, y1, wSrc,hSrc, backColor);

		//释放句柄
		::SelectObject(m_hDC, oldDestBmp);
		::SelectObject(SrcHdc, oldSrcBmp);
		::DeleteObject(SrcHdc);
	}

	void CDC::BuildBitmap(long content)
	{
		if(content&drawGeography)
			TransparentBlt(drawAll, 0,0, m_lDCWidth, m_lDCHeight, drawGeography, 0,0,m_lDCWidth, m_lDCHeight,m_bkColor);

		if(content&drawGeoSelection)
			TransparentBlt(drawAll, 0,0, m_lDCWidth, m_lDCHeight, drawGeoSelection, 0,0, m_lDCWidth, m_lDCHeight,m_bkColor);

		if(content&drawElement)
			TransparentBlt(drawAll, 0,0, m_lDCWidth, m_lDCHeight, drawElement, 0,0, m_lDCWidth, m_lDCHeight,m_bkColor);

		if(content&drawEdit)
			TransparentBlt(drawAll, 0,0, m_lDCWidth, m_lDCHeight, drawEdit, 0,0, m_lDCWidth, m_lDCHeight,m_bkColor);

		if(content&drawTempObj)
			TransparentBlt(drawAll, 0,0, m_lDCWidth, m_lDCHeight, drawTempObj, 0,0, m_lDCWidth, m_lDCHeight,m_bkColor);


	}

}