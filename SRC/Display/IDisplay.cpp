#include "stdafx.h"
#include "IDisplay.h"
#include "ISymbol.h"
#include "CDC.h"
#include "TextSymbol.h"

namespace Display
{

static boost::signal<void ()> gCallbackUpdteGeography;

IDisplay::IDisplay()
{
	m_BgColor = RGB(255,255,255);

	m_pDC = new CDC();
	m_pSymbol = NULL;
	bDraw = FALSE;

	m_pDC->SetBGColor(m_BgColor);

	m_bLayoutDis = FALSE;

	m_bPrint = FALSE;
	m_mapCaches.clear();
	m_sActiveCache = 0;
}



IDisplay::~IDisplay()
{
	if(m_pDC)
	{
		delete m_pDC;
		m_pDC = NULL;
	}
	this->RemoveAllCaches();
}

SYSTEM::CSmartPtr<IDisplay> IDisplay::Clone()
{
	IDisplay* pDisplay = new IDisplay;
	*pDisplay = *this;

	return IDisplayPtr(pDisplay);
}

void IDisplay::SetLayoutDisplay(BOOL bLayoutDis)
{
	m_bLayoutDis = bLayoutDis;
}

BOOL IDisplay::GetBeLayoutDisplay()
{
	return m_bLayoutDis;
}

Display::CDisplayTransformation& IDisplay::GetDisplayTransformation()
{
	return m_cDisplayTransformation;
}

/**
* 绘制图例
* @param pSymbol 符号
* @param rect 绘制区域
* @param nFlag 判断显示方式（直线或折线）
*/
void IDisplay::DrawLegend(ISymbol* pSymbol, DIS_RECT * rect, int nFlag)
{
	SetSymbol( pSymbol );

	Begin();

	m_pSymbol->DrawLegend( rect ,  nFlag );

	End();
}

/**
* 绘制图例
* @param pSymbol 符号
* @param lPosx 绘制区域起始位置x
* @param lPosy 绘制区域起始位置y
* @param lWidth 绘制区域宽度
* @param lHeight 绘制区域高度
* @param nFlag 判断显示方式（直线或折线）
*/
void IDisplay::DrawLegend(ISymbol* pSymbol,long lPosx,long lPosy,long lWidth,long lHeight, int nFlag)
{
	DIS_RECT  rect;
	rect.left = lPosx;
	rect.top = lPosy;
	rect.right = lPosx + lWidth;
	rect.bottom = lPosy + lHeight;

	DrawLegend(pSymbol,&rect,nFlag);
}

/**
* 偏移屏幕内容
* @param offset_x 偏移位置X
* @param offset_y 偏移位置Y
*/
void IDisplay::OffsetScreen(long offset_x,long offset_y)
{

}

/**
* 设置背景色
* @param color 颜色值
*/
void IDisplay::SetBgColor( COLORREF color)
{
	m_BgColor = color;
}

/**
* 获得颜色值
* @return 返回颜色值
*/
COLORREF IDisplay::GetBgColor()
{
	return m_BgColor;
}

/**
* 绘制背景
*/
void IDisplay::DrawBackgroud()
{
	if( CheckNoColor(m_BgColor) != 0xff )
	{
		HDC hDC = (HDC)m_pDC->GetSafeHdc();
		HBRUSH hbrush = ::CreateSolidBrush( m_BgColor );
		RECT rc = m_cDisplayTransformation.GetViewBound().GetRect();

		::FillRect( (HDC)hDC , &rc , hbrush );
		::DeleteObject( hbrush );
	}
}


void IDisplay::SetDC(long hDC, long lWidth, long lHeight )
{
		if(hDC == NULL)
			m_pDC->CreateExDC( lWidth , lHeight );
		else
			m_pDC->SetDC( hDC , lWidth , lHeight );
	m_cDisplayTransformation.SetViewBound(0, lWidth, 0, lHeight);

}

/**
* 获得绘制DC
* @return 若获得成功返回CDC
*/
Display::CDC* IDisplay::GetDrawDC()
{
	return m_pDC;
}



BOOL IDisplay::SetSymbol(Display::ISymbol* pSymbol)
{

	if( bDraw )
		return FALSE;
	if(pSymbol == NULL || m_pDC->GetSafeHdc() == NULL )
		return FALSE;

	//对符号进行缩放
	if(m_bLayoutDis)
	{
		float fScale =  1/m_cDisplayTransformation.GetMapScale();
		if (fScale != 1.000000)
		{
			if( pSymbol != NULL )
				pSymbol->Zoom( fScale );		
			//为打印缩放比例，为唯一值专题正确显示进行修改
		}
	}
	else if(m_cDisplayTransformation.GetReferenceScale() != 0)
	{
		float fScale =  m_cDisplayTransformation.GetReferenceScale()/m_cDisplayTransformation.GetMapScale();
		if (fScale != 1.000000)
		{
			if( pSymbol != NULL)
				pSymbol->Zoom( fScale );	
		}
	}
	
	m_pSymbol = pSymbol;
	m_pSymbol->SelectDC( m_pDC );

	m_stackpSymbol.push_back(m_pSymbol);

	return TRUE;
}


int IDisplay::SetSymbolInStack(ISymbol* pSymbol)
{
	if(pSymbol == NULL || m_pDC->GetSafeHdc() == NULL )
		return FALSE;

	//对符号进行缩放
	if(m_bLayoutDis)
	{
		float fScale =  1/m_cDisplayTransformation.GetMapScale();
		if (fScale != 1.000000)
		{
			if( pSymbol != NULL )
				pSymbol->Zoom( fScale );		
			//为打印缩放比例，为唯一值专题正确显示进行修改
		}
	}
	else if(m_cDisplayTransformation.GetReferenceScale() != 0)
	{
		float fScale =  m_cDisplayTransformation.GetReferenceScale()/m_cDisplayTransformation.GetMapScale();
		if (fScale != 1.000000)
		{
			if( pSymbol != NULL)
				pSymbol->Zoom( fScale );	
		}
	}

	pSymbol->SelectDC( m_pDC ); // 最好有返回BOOL，处理GDIHANDLE达到总数的情况

	m_stackpSymbol.push_back( pSymbol );

	return m_stackpSymbol.size()-1;
}

BOOL IDisplay::Begin()
{
	if( m_pDC->GetSafeHdc() == NULL )
		return FALSE;

	OnBeginDraw( m_pDC->GetSafeHdc() );

	m_pDC->BeginDisplay();

	if( m_pSymbol != NULL )
		m_pSymbol->SetReadyDraw();

	bDraw = TRUE;

	return bDraw;
	//IRasterSymbolPtr pRsSym = m_pSymbol;
	//if( pRsSym != NULL )
	//	pRsSym->BeginDrawRaster();

	
}

void IDisplay::End()
{
	/*IRasterSymbolPtr pRsSym = m_pSymbol;
	if( pRsSym != NULL )
		pRsSym->FinishDrawRaster();*/

	if(m_bLayoutDis)
	{
		float fScale =  m_cDisplayTransformation.GetMapScale();
		if (fScale != 1.000000)
		{
			/*if( m_pSymbol != NULL )
				m_pSymbol->Zoom( fScale );	*/	
			//为打印缩放比例，为唯一值专题正确显示进行修改
			for( int i = 0 ;i < m_stackpSymbol.size();i++ )
			{
				if(m_stackpSymbol[i] != NULL )
					m_stackpSymbol[i]->Zoom( fScale );
			}
		}
	}
	else if(m_cDisplayTransformation.GetReferenceScale() != 0)
	{
		float fScale =  m_cDisplayTransformation.GetMapScale()/m_cDisplayTransformation.GetReferenceScale();
		if (fScale != 1.000000)
		{
			/*if( m_pSymbol != NULL )
				m_pSymbol->Zoom( fScale );		*/
			//为打印缩放比例，为唯一值专题正确显示进行修改
			for( int i = 0 ;i < m_stackpSymbol.size();i++ )
			{
				if(m_stackpSymbol[i] != NULL )
					m_stackpSymbol[i]->Zoom( fScale );
			}
		}
	}

	//m_cDisplayTransformation.GetViewPosition().m_PrintScale = 1.0;
	if( m_pSymbol != NULL )
		m_pSymbol->ClearDC();

	m_pSymbol = NULL;

	m_pDC->EndDisplay();

	bDraw = FALSE;
	for (int i = 0 ; i < m_stackpSymbol.size() ; i++ )
	{
		m_stackpSymbol[i]->ClearDC();
	}
	m_stackpSymbol.clear();

	OnEndDraw( m_pDC->GetSafeHdc() );
}

void IDisplay::Draw(const GEOMETRY::geom::Geometry* pGeometry)
{
	void *p = NULL;
	if( pGeometry == NULL )
		return;

	//矢量切割
	BOOL bNewGeo = FALSE;
	GEOMETRY::geom::Geometry *pDrawGeometry = NULL;	
	if(m_bPrint)
	{
		GEOMETRY::geom::GeometryTypeId typeId = pGeometry->getGeometryTypeId();
		if(typeId != GEOM_CIRCLE && typeId != GEOM_ELLIPSE && typeId != GEOM_BEZIERSPLINE)
		{
			RECT rect; 
			DIS_RECT disrect;
			GEOMETRY::geom::Envelope viewEnv;
			GEOMETRY::geom::Geometry* pViewGeo = NULL;

			rect = m_cDisplayTransformation.GetViewBound().GetRect();
			disrect.left = rect.left;
			disrect.right = rect.right;
			disrect.top = rect.top;
			disrect.bottom = rect.bottom;
			m_cDisplayTransformation.TransformToGeo(disrect, &viewEnv);
			pViewGeo = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->toGeometry(&viewEnv);
			if(!pViewGeo->intersects(pGeometry))
				return;

			pDrawGeometry = pViewGeo->intersection(pGeometry);	
			bNewGeo = TRUE;
			GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(pViewGeo);
		}
		else
		{
			pDrawGeometry =  (GEOMETRY::geom::Geometry*)pGeometry;
		}
	}
	else
	{
		pDrawGeometry =  (GEOMETRY::geom::Geometry*)pGeometry;
	}


	//生成显示图形
	GEOMETRY::geom::GeometryTypeId GTypeID = pDrawGeometry->getGeometryTypeId();
	if(GTypeID == GEOMETRY::geom::GEOS_POINT)
	{
		GEOMETRY::geom::Point* pPoint= (GEOMETRY::geom::Point*)pDrawGeometry;
		p = (void*)m_cDisplayTransformation.TransformToDisplay( pPoint );
	}
	else if(GTypeID == GEOMETRY::geom::GEOS_LINESTRING|| GTypeID == GEOMETRY::geom::GEOS_LINEARRING)
	{
		GEOMETRY::geom::LineString* pLine = (GEOMETRY::geom::LineString*)pDrawGeometry;
		p = (void*)m_cDisplayTransformation.TransformToDisplay( pLine );
	}
	else if(GTypeID == GEOMETRY::geom::GEOS_POLYGON)
	{
		GEOMETRY::geom::Polygon* pPoly = (GEOMETRY::geom::Polygon*)pDrawGeometry;
		p = (void*)m_cDisplayTransformation.TransformToDisplay( pPoly );
	}
	else if(GTypeID ==GEOMETRY::geom::GEOM_CIRCLE)
	{
		GEOMETRY::geom::Circle *pc =(GEOMETRY::geom::Circle*)pDrawGeometry;
		p =(void*)m_cDisplayTransformation.TransformToDisplay(pc);	
	}
	else if(GTypeID ==GEOMETRY::geom::GEOM_ELLIPSE)
	{
		GEOMETRY::geom::Ellipse *pe =(GEOMETRY::geom::Ellipse*)pDrawGeometry;
		p =(void*)m_cDisplayTransformation.TransformToDisplay(pe);
	}
	else if(GTypeID == GEOMETRY::geom::GEOM_BEZIERSPLINE)
	{
		GEOMETRY::geom::BezierSpline *pb =(GEOMETRY::geom::BezierSpline*)pDrawGeometry;
		p =(void*)m_cDisplayTransformation.TransformToDisplay(pb);
	}
	else if(GTypeID == GEOMETRY::geom::GEOS_MULTIPOINT
		|| GTypeID == GEOMETRY::geom::GEOS_MULTILINESTRING || 
		GTypeID == GEOMETRY::geom::GEOS_MULTIPOLYGON )
	{
		GEOMETRY::geom::GeometryCollection *pGeoCol = (GEOMETRY::geom::GeometryCollection*)pDrawGeometry;
		for(int i = 0 ; i < pGeoCol->getNumGeometries() ; i++ )
			IDisplay::Draw( pGeoCol->getGeometryN(i) );

		return;
	}

	if(m_bPrint)
	{
		//设置DC切割范围
		RECT rect = m_cDisplayTransformation.GetViewBound().GetRect();
		DIS_RECT rc;
		rc.left = rect.left;
		rc.right = rect.right;
		rc.top = rect.top;
		rc.bottom = rect.bottom;
		m_pDC->SelectPrintClipRgn(&rc);
	}
	
	//绘制
	if(m_pSymbol != NULL && p)
		m_pSymbol->Draw( p );

	////释放绘制对象
	if(NULL != p)
	{
        FreeDisplayObj(p);
	}

	if(m_bPrint)
	{
		//DC恢复到窗口范围
		m_pDC->SelectPrintClipRgn(NULL);
	}

	if(bNewGeo)
		GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(pDrawGeometry);
}

/**
* 绘制
* @param pEnvelope 矩形
*/
void IDisplay::Draw(const GEOMETRY::geom::Envelope* pEnvelope)
{
	void *p = NULL;
	p = (void*)m_cDisplayTransformation.TransformToDisplay( pEnvelope);
	if(m_pSymbol != NULL)
		m_pSymbol->Draw( p);
	

	FreeDisplayObj(p);
}
DIS_RECT IDisplay::Draw(const GEOMETRY::geom::Envelope* pEnvelope,  const std::string strText, BOOL bScaleWithMap, unsigned int dwDTFormat)
{
	DIS_TEXT* pTextObj = m_cDisplayTransformation.TransformToDisplay( pEnvelope, strText );
	CTextSymbol* pTextSymbol = (CTextSymbol*)m_pSymbol; 

	if(pTextSymbol != NULL)
	{
		pTextSymbol->SetDrawFormat(dwDTFormat);
		pTextSymbol->Draw( pTextObj);
	
		DIS_RECT rect = pTextObj->textPos;
		FreeDisplayObj(pTextObj);

		return rect;
	}

	if(pTextObj)
	{
		FreeDisplayObj(pTextObj);
	}
	DIS_RECT rectDis;
	return rectDis;
}

DIS_RECT IDisplay::Draw(const DIS_RECT* rect,  const std::string strText, BOOL bScaleWithMap, unsigned int dwDTFormat)
{
	CTextSymbol* pTextSymbol = (CTextSymbol*)m_pSymbol; 

	DIS_TEXT* pTextObj = NULL;
	CreateDisplayText(pTextObj, strText.size());
	pTextObj->textPos = *rect;
	strcpy(pTextObj->cText, strText.c_str());

	if(pTextSymbol != NULL)
	{
		pTextSymbol->SetDrawFormat(dwDTFormat);
		pTextSymbol->Draw( pTextObj);

		DIS_RECT rect = pTextObj->textPos;
		FreeDisplayObj(pTextObj);
		return rect;
	}

	if(pTextObj)
	{
		FreeDisplayObj(pTextObj);
	}
	DIS_RECT rectDis;
	return rectDis;
}

void IDisplay::Draw(void* pObject)
{
	if(m_pSymbol != NULL)
		m_pSymbol->Draw( pObject );
}



BOOL IDisplay::SelectStackSymbol(int index)
{
	//if( index > m_stackpSymbol.size() - 1 )

	m_pSymbol = m_stackpSymbol[index];

	m_pSymbol->SetReadyDraw();

	return TRUE;
}

void IDisplay::OnBeginDraw( long hDC )
{

}

void IDisplay::OnEndDraw( long hDC )
{

}

//设置绘制缓冲区
void IDisplay::SetDrawBuffer(DRAW_CONTENT content)
{
	if(m_bPrint)
		return;
	m_pDC->SelectBitmap(content);
}

//刷新显示内存
void IDisplay::RefreshDisplay(long content)
{
	if(m_bPrint)
		return;
	m_pDC->BuildBitmap(content);
}

//重新设置显示缓冲大小
void IDisplay::CacheBuffer(long lWidth, long lHeight)
{
	m_pDC->CacheBitmap(lWidth,lHeight);

	//重建内存位图
	std::map<long,EP_CACHE*>::iterator it;
	for (it=m_mapCaches.begin(); it!=m_mapCaches.end(); ++it)
	{
		EP_CACHE* pCache = it->second;
		::SelectObject(pCache->hMemdc,pCache->oldBmp);
		::DeleteObject(pCache->bmp);
		pCache->bmp = ::CreateCompatibleBitmap(HDC(m_pDC->GetSafeHdc()), lWidth, lHeight); 
		pCache->oldBmp = (HBITMAP)::SelectObject(pCache->hMemdc, pCache->bmp);
	}


}

void IDisplay::get_ActiveCache(short& sIndex)
{
		sIndex = m_sActiveCache;
}
	void IDisplay::set_ActiveCache(short sIndex)
	{
		m_sActiveCache = sIndex;
	}
void IDisplay::AddCache(short& sCachId)
{
	if (NULL == m_pDC)
		return;

	HDC hdc = (HDC)m_pDC->GetSafeHdc();
	EP_CACHE* pCache = new EP_CACHE();
	long lWidth = m_pDC->GetDCWidth();
	long lHeight = m_pDC->GetDCHeight();

	
	pCache->hMemdc = ::CreateCompatibleDC(hdc);
	pCache->bmp = ::CreateCompatibleBitmap(hdc, lWidth, lHeight); 
	pCache->oldBmp = (HBITMAP)::SelectObject(pCache->hMemdc, pCache->bmp);

	long id = 0;
	int nSize = m_mapCaches.size();
	if (nSize > 0)
	{
		std::map<long,EP_CACHE*>::iterator it;
		it = m_mapCaches.end();
		it--;
		id = it->first + 1;
	}
	typedef std::pair< long , EP_CACHE*>  Cache_Pair;
	m_mapCaches.insert(Cache_Pair(id,pCache));

	sCachId = id;
}
void IDisplay::RemoveCache(short sCachId)
{
	std::map<long,EP_CACHE*>::iterator it;
	for (it=m_mapCaches.begin(); it!=m_mapCaches.end(); ++it)
	{
		if (it->first == sCachId)
		{
			EP_CACHE* pCache = it->second;
			::SelectObject(pCache->hMemdc,pCache->oldBmp);
			::DeleteObject(pCache->bmp);
			::DeleteDC(pCache->hMemdc);
			delete pCache;
			pCache = NULL;
			m_mapCaches.erase(it);
			return;
		}
	}

}
void IDisplay::RemoveAllCaches()
{
	std::map<long,EP_CACHE*>::iterator it;
	for (it=m_mapCaches.begin(); it!=m_mapCaches.end(); ++it)
	{
		RemoveCache(it->first);
	}

}
void IDisplay::get_CacheCount(short& sCount)
{
	sCount = m_mapCaches.size(); 
}
void IDisplay::get_CacheMemDC(short sIndex, long* plHdc)
{
	std::map<long,EP_CACHE*>::iterator it;
	for (it=m_mapCaches.begin(); it!=m_mapCaches.end();++it)
	{
		if (sIndex == it->first)
		{
			EP_CACHE* pCache = m_mapCaches[sIndex];
			*plHdc = (long)pCache->hMemdc;
		}
	}

}
void IDisplay::DrawCache(long lHdc, short sIndex, tagRECT& deviceRect, tagRECT& cacheRect)
{
	std::map<long,EP_CACHE*>::iterator theIterator;
	theIterator = m_mapCaches.find(sIndex);
	if(theIterator == m_mapCaches.end())
	{
		return;
	}
	EP_CACHE* pCache = m_mapCaches[sIndex];
	HDC pCacheDC = pCache->hMemdc;

	
		//拷贝
	::TransparentBlt((HDC)lHdc, deviceRect.left, deviceRect.top, deviceRect.right-deviceRect.left,
		deviceRect.bottom-deviceRect.top, pCacheDC, cacheRect.left, cacheRect.top, cacheRect.right-cacheRect.left,
		cacheRect.bottom-cacheRect.top, this->m_BgColor);

		

	/*CDC dcMask;
		dcMask.CreateCompatibleDC( CDC::FromHandle(m_pdc) );
		CBitmap cMaskBitmap;
		cMaskBitmap.CreateBitmap( m_drawRect.Width(),m_drawRect.Height(),1,1,NULL );
		CBitmap* pOldBitmap = dcMask.SelectObject( &cMaskBitmap );
		if (pLyr != pLayer)
		{
			dcMask.BitBlt( 0,0,m_drawRect.Width(),m_drawRect.Height(),pCacheDC,0,0,SRCCOPY );
			m_pMemDC->BitBlt( 0,0,m_drawRect.Width(),m_drawRect.Height(),pCacheDC,0,0,SRCINVERT );
			m_pMemDC->BitBlt( 0,0,m_drawRect.Width(),m_drawRect.Height(),&dcMask,0,0,SRCAND );
			m_pMemDC->BitBlt( 0,0,m_drawRect.Width(),m_drawRect.Height(),pCacheDC,0,0,SRCINVERT );
		}
		else
		{
			dcMask.BitBlt( startx,starty,rectWidth1,rectHeight1,pCacheDC,startx,starty,SRCCOPY );
			m_pMemDC->BitBlt( startx,starty,rectWidth1,rectHeight1,pCacheDC,startx,starty,SRCINVERT );
			m_pMemDC->BitBlt( startx,starty,rectWidth1,rectHeight1,&dcMask,startx,starty,SRCAND );
			m_pMemDC->BitBlt( startx,starty,rectWidth1,rectHeight1,pCacheDC,startx,starty,SRCINVERT );
		}
		dcMask.SelectObject(pOldBitmap);
		cMaskBitmap.DeleteObject();
		dcMask.DeleteDC();*/
	/*::BitBlt(HDC(lHdc), deviceRect.left,deviceRect.top,deviceRect.right-deviceRect.left,deviceRect.bottom-deviceRect.top,
		pCache->hMemdc,cacheRect.left,cacheRect.top,SRCAND);*/
}

void IDisplay::SetPrinting(BOOL bPrint)
{
	m_bPrint = bPrint;
}

void IDisplay::UpdateGeography()
{
    gCallbackUpdteGeography();
}

boost::signals::connection IDisplay::RegisterUpdateGeography(boost::function<void ()> fun)
{
    return gCallbackUpdteGeography.connect(fun);
}

}
