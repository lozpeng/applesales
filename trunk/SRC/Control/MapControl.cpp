#include "stdafx.h"
#include "MapControl.h"

namespace Control
{

IMPLEMENT_DYNAMIC(CMapControl, CWnd)

	CMapControl::CMapControl()
{
	m_bTimer = false;
	m_bMouseWheel = false;

	
}

CMapControl::~CMapControl()
{
}


BEGIN_MESSAGE_MAP(CMapControl, CWnd)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_KEYDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_MOUSEWHEEL()
	ON_WM_SETCURSOR()
	ON_WM_TIMER()

END_MESSAGE_MAP()


BOOL CMapControl::CreateControl( std::string Name, void *pParent , long nID )
{
	CreateAss(Name);

	SetAutoDetroy(true);

	return Create( "STATIC" , _T(""), WS_CHILD|WS_VISIBLE|SS_NOTIFY , CRect(0,0,0,0) , (CWnd*)pParent , nID );
}

void CMapControl::OnLButtonDown(UINT nFlags, CPoint point)
{
	
	SetFocus();

	__super::OnLButtonDown(nFlags, point);
}

void CMapControl::OnLButtonUp(UINT nFlags, CPoint point)
{
	

	__super::OnLButtonUp(nFlags, point);
}

void CMapControl::OnRButtonDown(UINT nFlags, CPoint point)
{
	
	__super::OnRButtonDown(nFlags, point);
}

void CMapControl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	

	__super::OnKeyDown( nChar , nRepCnt, nFlags );
}

void CMapControl::OnMouseMove(UINT nFlags, CPoint point)
{
	

	__super::OnMouseMove(nFlags, point);
}

void CMapControl::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	
	return CWnd::OnLButtonDblClk(nFlags, point);
}


int CMapControl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (__super::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_hClientDC = ::GetDC(GetSafeHwnd());
	m_hMemDC = ::CreateCompatibleDC(m_hClientDC);
	
	return 0;
}

void CMapControl::OnSize(UINT nType, int cx, int cy)
{

	__super::OnSize(nType, cx, cy);

	ControlResize(nType,cx,cy);

}

void CMapControl::OnPaint()
{
	CPaintDC dc(this); 
	if(m_pGeoMap)
	{
		::BitBlt(m_hClientDC,0,0,m_lSizeX,m_lSizeY,m_hMemDC,0,0,SRCCOPY);
	}
	else
	{
		HBRUSH hbrush = ::CreateSolidBrush( m_BgColor );
		RECT rc;
		rc.left=rc.top=0;
		rc.right=m_lSizeX;
		rc.bottom=m_lSizeY;
		::FillRect( (HDC)m_hClientDC , &rc , hbrush );

		::DeleteObject( hbrush );
	}	
}

void CMapControl::SetCursor()
{

}

BOOL CMapControl::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: �ڴ�������Ϣ������������/�����Ĭ��ֵ
	//SetCursor();

	return __super::OnSetCursor(pWnd,nHitTest,message);
	
}

void CMapControl::CalSrcRect(GEOMETRY::geom::Envelope extent,CRect &rect)
{
	//���Ŀ�귶Χ��ԭʼ��Χ����ȡ����memDC
	double xmin,xmax,ymin,ymax;
	if(extent.getMaxX()>=m_srcEnvelop.getMaxX() && extent.getMinX()<=m_srcEnvelop.getMinX() && extent.getMaxY()>=m_srcEnvelop.getMaxY() && extent.getMinY()<=m_srcEnvelop.getMinY())
	{
		rect =  m_pGeoMap->GetDisplay()->GetDisplayTransformation().GetViewBound().GetRect();
		return;
	}
	else
	{

		GEOMETRY::geom::Coordinate		 cp;
		GEOMETRY::geom::Coordinate	    cPoint, cCp;
		GEOMETRY::geom::Envelope	       cWrdExt;

		rect =  m_pGeoMap->GetDisplay()->GetDisplayTransformation().GetViewBound().GetRect();
		//
		cp.x = rect.CenterPoint().x;
		cp.y = rect.CenterPoint().y;

		cWrdExt = m_srcEnvelop;
		cWrdExt.centre(cCp);

		cPoint.x = extent.getMinX();
		cPoint.y = extent.getMinY();

		cPoint.x -= cCp.x;
		cPoint.y -= cCp.y;
		xmin = cp.x + cPoint.x / (m_srcScale);
		ymax = cp.y - cPoint.y / (m_srcScale);

		cPoint.x = extent.getMaxX();
		cPoint.y = extent.getMaxY();
		cPoint.x -= cCp.x;
		cPoint.y -= cCp.y;
		xmax = cp.x + cPoint.x / (m_srcScale);
		ymin = cp.y - cPoint.y / (m_srcScale);

		rect.left = (long)(xmin+0.5);
		rect.top = (long)(ymin+0.5);
		rect.right = (long)(xmax+0.5);
		rect.bottom = (long)(ymax+0.5);	

	}


}

void CMapControl::CalDestRect(GEOMETRY::geom::Envelope srcExtent,GEOMETRY::geom::Envelope destExtent,CRect &rect)
{

	GEOMETRY::geom::Coordinate	  cp;
	GEOMETRY::geom::Coordinate	  cPoint, cCp;
	GEOMETRY::geom::Envelope	     cWrdExt;
	double xmin,xmax,ymin,ymax;

	rect = m_pGeoMap->GetDisplay()->GetDisplayTransformation().GetViewBound().GetRect();
	//
	cp.x = rect.CenterPoint().x;
	cp.y = rect.CenterPoint().y;

	cWrdExt = destExtent;
	cWrdExt.centre(cCp);

	cPoint.x = srcExtent.getMinX();
	cPoint.y = srcExtent.getMinY();
	cPoint.x -= cCp.x;
	cPoint.y -= cCp.y;

	xmin = cp.x + cPoint.x / (m_dblScale);
	ymax = cp.y - cPoint.y / (m_dblScale);

	cPoint.x = srcExtent.getMaxX();
	cPoint.y = srcExtent.getMaxY();
	cPoint.x -= cCp.x;
	cPoint.y -= cCp.y;
	xmax = cp.x + cPoint.x / (m_dblScale);
	ymin = cp.y - cPoint.y / (m_dblScale);

	rect.left = (long)(xmin+0.5);
	rect.top = (long)(ymin+0.5);
	rect.right = (long)(xmax+0.5);
	rect.bottom = (long)(ymax+0.5);	


}

BOOL CMapControl::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	if(!m_pGeoMap)
		return false;

	if(m_pGeoMap->GetExtentMode() != Carto::EEM_AUTO)
		return false;

	double dblRatio = 1;
	long lSceenWidth,lSceenHeight;
	GEOMETRY::geom::Coordinate point;
	CRect rect;
	GetClientRect(&rect);
	lSceenWidth = rect.Width();
	lSceenHeight = rect.Height();

	Display::IDisplayPtr pDispaly = m_pGeoMap->GetDisplay();

	if (!m_bTimer)
	{
		m_srcEnvelop = m_pGeoMap->GetViewEnvelope();
		SetTimer(1,300,NULL);
		m_dblScale = pDispaly->GetDisplayTransformation().GetScale();

		m_srcScale = m_dblScale;

		m_bTimer = true;
	}

	m_bMouseWheel = true;

	HDC hMemDC = ::CreateCompatibleDC(m_hClientDC);

	HBITMAP hOldBitmap,hBitmap = ::CreateCompatibleBitmap(m_hClientDC,m_lSizeX,m_lSizeY);

	hOldBitmap = (HBITMAP)::SelectObject(hMemDC,hBitmap);

	//���Ʊ���
	HBRUSH hbrush = ::CreateSolidBrush( RGB(255,255,255));

	::FillRect(hMemDC , &rect , hbrush );

	::DeleteObject( hbrush );

	double xmin,xmax,ymin,ymax;

	if (zDelta > 0) //�Ŵ�
	{
		dblRatio = 0.8;

		m_dblScale *= dblRatio;

		m_pGeoMap->GetViewEnvelope().centre(point);

		xmin = point.x - lSceenWidth/2.0*m_dblScale;
		xmax = point.x + lSceenWidth/2.0*m_dblScale;
		ymin = point.y - lSceenHeight/2.0*m_dblScale;
		ymax = point.y + lSceenHeight/2.0*m_dblScale;

		GEOMETRY::geom::Envelope newExt(xmin,xmax,ymin,ymax);

		//�ı��ͼ����ʾ��Χ
		m_pGeoMap->GetDisplay()->GetDisplayTransformation().FitViewBound(newExt);

		CRect srcRect,destRect;

		CalSrcRect(newExt,srcRect);

		//���Ŀ�귶Χ��ԭʼ��ΧС����Ŀ�����������View�Ŀͻ���
		if(newExt.getMaxX()<=m_srcEnvelop.getMaxX() 
			&& newExt.getMinX()>=m_srcEnvelop.getMinX() 
			&& newExt.getMaxY()<=m_srcEnvelop.getMaxY()
			&& newExt.getMinY()>=m_srcEnvelop.getMinY())
		{
			destRect = rect;
		}
		else
		{
			GEOMETRY::geom::Envelope srcExtent =m_srcEnvelop;
			CalDestRect(srcExtent,newExt,destRect);

		}

		::SetStretchBltMode(hMemDC,MAXSTRETCHBLTMODE);

		::StretchBlt(hMemDC,destRect.left,destRect.top,destRect.Width(),destRect.Height(),(HDC)pDispaly->GetDrawDC()->GetSafeHdc(),srcRect.left,srcRect.top,srcRect.Width(),srcRect.Height(),SRCCOPY);


		//::BitBlt(m_hMemDC,0,0,m_lSizeX,m_lSizeY,hMemDC,0,0,SRCCOPY);
		::BitBlt(m_hClientDC,0,0,m_lSizeX,m_lSizeY,hMemDC,0,0,SRCCOPY);

	}
	else if (zDelta < 0) //��С
	{
		dblRatio = 1.2;

		m_dblScale *= dblRatio;

		m_pGeoMap->GetViewEnvelope().centre(point);

		xmin = point.x - lSceenWidth/2.0*m_dblScale;
		xmax = point.x + lSceenWidth/2.0*m_dblScale;
		ymin = point.y - lSceenHeight/2.0*m_dblScale;
		ymax = point.y + lSceenHeight/2.0*m_dblScale;

		GEOMETRY::geom::Envelope newExt(xmin,xmax,ymin,ymax);

		//�ı��ͼ����ʾ��Χ
		m_pGeoMap->GetDisplay()->GetDisplayTransformation().FitViewBound(newExt);


		CRect srcRect,destRect;

		CalSrcRect(m_pGeoMap->GetViewEnvelope(),srcRect);

		//���Ŀ�귶Χ��ԭʼ��ΧС����Ŀ�����������View�Ŀͻ���
		if(newExt.getMaxX()<=m_srcEnvelop.getMaxX() 
			&& newExt.getMinX()>=m_srcEnvelop.getMinX() 
			&& newExt.getMaxY()<=m_srcEnvelop.getMaxY()
			&&newExt.getMinY()>=m_srcEnvelop.getMinY())
		{
			destRect = rect;
		}
		else
		{
			GEOMETRY::geom::Envelope srcExtent =m_srcEnvelop;
			CalDestRect(srcExtent,newExt,destRect);

		}

		::SetStretchBltMode(hMemDC,MAXSTRETCHBLTMODE);

		::StretchBlt(hMemDC,destRect.left,destRect.top,destRect.Width(),destRect.Height(),(HDC)pDispaly->GetDrawDC()->GetSafeHdc(),srcRect.left,srcRect.top,srcRect.Width(),srcRect.Height(),SRCCOPY);

		//::BitBlt(m_hMemDC,0,0,m_lSizeX,m_lSizeY,hMemDC,0,0,SRCCOPY);
		::BitBlt(m_hClientDC,0,0,m_lSizeX,m_lSizeY,hMemDC,0,0,SRCCOPY);

	}

	::SelectObject(hMemDC,hOldBitmap);
	::DeleteObject(hBitmap);
	::DeleteDC(hMemDC);


	return TRUE;

}

void CMapControl::OnTimer(UINT_PTR nIDEvent)
{
	//������ϸ�ʱ��Σ������ֻ���,�򽫱����Ϊfalse
	if(m_bMouseWheel)
	{
		m_bMouseWheel =false;
	}
	else
	{
		/*if(m_pGeoMap->GetExtentMode() == otCarto::EEM_AUTO)
		{*/
			m_pGeoMap->GetDisplay()->GetDisplayTransformation().ZoomToFixScale(m_dblScale);

			UpdateControl(drawAll);			
		/*}	
		KillTimer(1);	
		m_bTimer = false;*/
	}

}


}