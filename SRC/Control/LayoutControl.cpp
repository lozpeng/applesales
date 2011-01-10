#include "StdAfx.h"
#include "LayoutControl.h"
#include "MapFrame.h"

namespace Control
{

	IMPLEMENT_DYNAMIC(CLayoutControl, CWnd)


	CLayoutControl::CLayoutControl(void)
	{
		m_bTimer = false;
		m_bMouseWheel = false;
	}

	CLayoutControl::~CLayoutControl(void)
	{
	}

	BEGIN_MESSAGE_MAP(CLayoutControl, CWnd)
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
	// CLayoutControl 消息处理程序

	BOOL CLayoutControl::CreateControl( std::string Name, void *pParent , long nID )
	{
		CreateAss(Name);

		SetAutoDetroy(true);

		return Create( "STATIC" , _T(""), WS_CHILD|WS_VISIBLE|SS_NOTIFY , CRect(0,0,0,0) , (CWnd*)pParent , nID );
	}


	int CLayoutControl::OnCreate(LPCREATESTRUCT lpCreateStruct)
	{
		if (__super::OnCreate(lpCreateStruct) == -1)
			return -1;

		//创建一个默认的制图对象
		m_hClientDC = ::GetDC(GetSafeHwnd());
		m_hMemDC = ::CreateCompatibleDC(m_hClientDC);

		m_hCtrlWnd = this->GetSafeHwnd();
		return 0;
	}

	void CLayoutControl::OnPaint()
	{
		CPaintDC dc(this); // device context for painting
		if(m_pPageLayout)
		{
			::BitBlt(m_hClientDC,0,0,m_lSizeX,m_lSizeY,m_hMemDC,0,0,SRCCOPY);
		}
		else
		{
			HBRUSH hbrush = ::CreateSolidBrush( RGB(255,255,255));
			RECT rc;
			rc.left=rc.top=0;
			rc.right=m_lSizeX;
			rc.bottom=m_lSizeY;
			::FillRect( (HDC)m_hClientDC , &rc , hbrush );

			::DeleteObject( hbrush );
		}

		CRect rect;
		GetClientRect(rect);
		//绘制边框
		dc.Draw3dRect (rect,	::GetSysColor (COLOR_3DSHADOW), 
			::GetSysColor (COLOR_3DSHADOW));
	}

	void CLayoutControl::OnSize(UINT nType, int cx, int cy)
	{
		__super::OnSize(nType, cx, cy);
		//if(IsWindowVisible())
			ControlResize(nType,cx,cy);

	}

	void CLayoutControl::OnLButtonDblClk(UINT nFlags, CPoint point)
	{
		Framework::ITool *pTool =Framework::ITool::FindTool(m_curToolname);
		if(pTool)
		{
			pTool->LButtonDblClkEvent(nFlags,point);
		}

		__super::OnLButtonDblClk(nFlags, point);
	}

	void CLayoutControl::OnLButtonDown(UINT nFlags, CPoint point)
	{
		Framework::ITool *pTool =Framework::ITool::FindTool(m_curToolname);
		if(pTool)
		{
			pTool->LButtonDownEvent(nFlags,point);
		}
		__super::OnLButtonDown(nFlags, point);
	}

	void CLayoutControl::OnLButtonUp(UINT nFlags, CPoint point)
	{
		Framework::ITool *pTool =Framework::ITool::FindTool(m_curToolname);
		if(pTool)
		{
			pTool->LButtonUpEvent(nFlags,point);
		}

		__super::OnLButtonUp(nFlags, point);
	}

	void CLayoutControl::OnMouseMove(UINT nFlags, CPoint point)
	{
		Framework::ITool *pTool =Framework::ITool::FindTool(m_curToolname);
		if(pTool)
		{
			pTool->MouseMoveEvent(nFlags,point);
		}

		__super::OnMouseMove(nFlags, point);
	}

	void CLayoutControl::OnRButtonDblClk(UINT nFlags, CPoint point)
	{
		// TODO: 在此添加消息处理程序代码和/或调用默认值

		__super::OnRButtonDblClk(nFlags, point);
	}

	void CLayoutControl::OnRButtonDown(UINT nFlags, CPoint point)
	{
		Framework::ITool *pTool =Framework::ITool::FindTool(m_curToolname);
		if(pTool)
		{
			pTool->RButtonDownEvent(nFlags,point);
		}
		__super::OnRButtonDown(nFlags, point);
	}

	void CLayoutControl::OnRButtonUp(UINT nFlags, CPoint point)
	{
		// TODO: 在此添加消息处理程序代码和/或调用默认值

		__super::OnRButtonUp(nFlags, point);
	}

	BOOL CLayoutControl::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
	{
		if(m_cursor)
		{
			::SetCursor(m_cursor);
		}
		else
		{
			//设置默认光标
			::SetCursor(LoadCursor(NULL,IDC_ARROW));
		}

		return TRUE;
	}

	void CLayoutControl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		Framework::ITool *pTool =Framework::ITool::FindTool(m_curToolname);
		if(pTool)
		{
			pTool->KeyDownEvent(nChar,nRepCnt,nFlags);
		}


		__super::OnKeyDown(nChar, nRepCnt, nFlags);
	}

	void CLayoutControl::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		Framework::ITool *pTool =Framework::ITool::FindTool(m_curToolname);
		if(pTool)
		{
			pTool->KeyUpEvent(nChar,nRepCnt,nFlags);
		}

		__super::OnKeyUp(nChar, nRepCnt, nFlags);
	}

	void CLayoutControl::CalSrcRect(GEOMETRY::geom::Envelope extent,CRect &rect)
	{
		//如果目标范围比原始范围大，则取整块memDC
		double xmin,xmax,ymin,ymax;
		if(extent.getMaxX()>=m_srcEnvelop.getMaxX() && extent.getMinX()<=m_srcEnvelop.getMinX() && extent.getMaxY()>=m_srcEnvelop.getMaxY() && extent.getMinY()<=m_srcEnvelop.getMinY())
		{
			rect =  m_pPageLayout->GetDisplay()->GetDisplayTransformation().GetViewBound().GetRect();
			return;
		}
		else
		{

			GEOMETRY::geom::Coordinate		 cp;
			GEOMETRY::geom::Coordinate	    cPoint, cCp;
			GEOMETRY::geom::Envelope	       cWrdExt;

			rect =  m_pPageLayout->GetDisplay()->GetDisplayTransformation().GetViewBound().GetRect();
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

	void CLayoutControl::CalDestRect(GEOMETRY::geom::Envelope srcExtent,GEOMETRY::geom::Envelope destExtent,CRect &rect)
	{

		GEOMETRY::geom::Coordinate	  cp;
		GEOMETRY::geom::Coordinate	  cPoint, cCp;
		GEOMETRY::geom::Envelope	     cWrdExt;
		double xmin,xmax,ymin,ymax;

		rect = m_pPageLayout->GetDisplay()->GetDisplayTransformation().GetViewBound().GetRect();
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

	BOOL CLayoutControl::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
	{
		if(!m_pPageLayout)
			return false;
		double dblRatio = 1;
		long lSceenWidth,lSceenHeight;
		GEOMETRY::geom::Coordinate point;
		CRect rect;
		GetClientRect(&rect);
		lSceenWidth = rect.Width();
		lSceenHeight = rect.Height();

		Display::IDisplayPtr pDispaly = m_pPageLayout->GetDisplay();

		if (!m_bTimer)
		{
			m_pPageLayout->GetDisplay()->GetDisplayTransformation().GetGeoBound(m_srcEnvelop);
			SetTimer(2,300,NULL);
			m_dblScale = pDispaly->GetDisplayTransformation().GetScale();

			m_srcScale = m_dblScale;

			m_bTimer = true;
		}

		m_bMouseWheel = true;

		HDC hMemDC = ::CreateCompatibleDC(m_hClientDC);

		HBITMAP hOldBitmap,hBitmap = ::CreateCompatibleBitmap(m_hClientDC,m_lSizeX,m_lSizeY);

		hOldBitmap = (HBITMAP)::SelectObject(hMemDC,hBitmap);

		//绘制背景
		HBRUSH hbrush = ::CreateSolidBrush( RGB(255,255,255));

		::FillRect(hMemDC , &rect , hbrush );

		::DeleteObject( hbrush );

		double xmin,xmax,ymin,ymax;

		if (zDelta > 0) //放大
		{
			dblRatio = 0.8;

			m_dblScale *= dblRatio;

			double centerX = m_pPageLayout->GetDisplay()->GetDisplayTransformation().GetGeoCenterX();
			double centerY = m_pPageLayout->GetDisplay()->GetDisplayTransformation().GetGeoCenterY();

			xmin = centerX - lSceenWidth/2.0*m_dblScale;
			xmax = centerX + lSceenWidth/2.0*m_dblScale;
			ymin = centerY - lSceenHeight/2.0*m_dblScale;
			ymax = centerY + lSceenHeight/2.0*m_dblScale;

			GEOMETRY::geom::Envelope newExt(xmin,xmax,ymin,ymax);

			//改变地图的显示范围
			m_pPageLayout->GetDisplay()->GetDisplayTransformation().FitViewBound(newExt);

			CRect srcRect,destRect;

			CalSrcRect(newExt,srcRect);

			//如果目标范围比原始范围小，则目标矩形是整个View的客户区
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

			::SetStretchBltMode(hMemDC,COLORONCOLOR);

			::StretchBlt(hMemDC,destRect.left,destRect.top,destRect.Width(),destRect.Height(),(HDC)pDispaly->GetDrawDC()->GetSafeHdc(),srcRect.left,srcRect.top,srcRect.Width(),srcRect.Height(),SRCCOPY);

			::BitBlt(m_hClientDC,0,0,m_lSizeX,m_lSizeY,hMemDC,0,0,SRCCOPY);

		}
		else if (zDelta < 0) //缩小
		{
			dblRatio = 1.2;

			m_dblScale *= dblRatio;

			double centerX = m_pPageLayout->GetDisplay()->GetDisplayTransformation().GetGeoCenterX();
			double centerY = m_pPageLayout->GetDisplay()->GetDisplayTransformation().GetGeoCenterY();

			xmin = centerX - lSceenWidth/2.0*m_dblScale;
			xmax = centerX + lSceenWidth/2.0*m_dblScale;
			ymin = centerY - lSceenHeight/2.0*m_dblScale;
			ymax = centerY + lSceenHeight/2.0*m_dblScale;

			GEOMETRY::geom::Envelope newExt(xmin,xmax,ymin,ymax);

			//改变地图的显示范围
			m_pPageLayout->GetDisplay()->GetDisplayTransformation().FitViewBound(newExt);


			m_pPageLayout->GetDisplay()->GetDisplayTransformation().GetGeoBound(newExt);

			CRect srcRect,destRect;

			CalSrcRect(newExt,srcRect);

			//如果目标范围比原始范围小，则目标矩形是整个View的客户区
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

			::SetStretchBltMode(hMemDC,COLORONCOLOR);

			::StretchBlt(hMemDC,destRect.left,destRect.top,destRect.Width(),destRect.Height(),(HDC)pDispaly->GetDrawDC()->GetSafeHdc(),srcRect.left,srcRect.top,srcRect.Width(),srcRect.Height(),SRCCOPY);

			::BitBlt(m_hClientDC,0,0,m_lSizeX,m_lSizeY,hMemDC,0,0,SRCCOPY);

		}

		::SelectObject(hMemDC,hOldBitmap);
		::DeleteObject(hBitmap);
		::DeleteDC(hMemDC);


		return TRUE;

	}

	void CLayoutControl::OnTimer(UINT_PTR nIDEvent)
	{
		//如果在上个时间段，鼠标滚轮滑动,则将标记设为false
		if(m_bMouseWheel)
		{
			m_bMouseWheel =false;
		}
		else
		{

			m_pPageLayout->GetDisplay()->GetDisplayTransformation().ZoomToFixScale(m_dblScale);

			UpdateControl(drawAll);			

			KillTimer(2);	
			m_bTimer = false;
		}

	}

	void CLayoutControl::LoadTemplate(Carto::CMapPtr map, BSTR templatefile)
	{
		CRect rect;
		GetClientRect(rect);
		m_pPageLayout.reset(new Carto::CPageLayout());
		m_pPageLayout->Initialize((long)m_hMemDC,rect.Width(),rect.Height());

		USES_CONVERSION; 
		
		LPCTSTR pFileName = OLE2T(templatefile);
		
		CFile file;
		if(!file.Open(pFileName,CFile::modeRead))
		{
			return;
		}

		CString PrjPath =pFileName;
		CString basePath =PrjPath.Left(PrjPath.ReverseFind(_T('\\'))+1);

		CArchive ar(&file,CArchive::load);

		unsigned long Size;
		ar >> Size;

		BYTE * pStart = new BYTE[Size];

		ar.Read( pStart , Size );

		SYSTEM::CBinArchive bin( pStart , Size );

		bin.SetReadState();

		BOOL bLayoutExist ;
		bin & bLayoutExist;

		serialization(bin);

		Carto::CGraphicLayerPtr pLayer = m_pPageLayout->GetGraphicLayer();

		Element::IElementPtr pElement = pLayer->Reset();
		while(pElement)
		{
			if(pElement->GetType() == Element::ET_MAP_FRAME_ELEMENT)
			{
				Element::CMapFrame* pMapFrame = dynamic_cast<Element::CMapFrame*>(pElement.get());
				pMapFrame->SetMap(map);

				break;
			}
			pElement = pLayer->Next();
		}


		delete[] pStart;

		UpdateControl(drawAll);
	}



}