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

		Framework::ITool *pTool =Framework::ITool::FindTool(m_curToolname);
		if (pTool != NULL)
		{
			pTool->LButtonDownEvent( nFlags, point);
		}


		__super::OnLButtonDown(nFlags, point);
	}

	void CMapControl::OnLButtonUp(UINT nFlags, CPoint point)
	{
		Framework::ITool *pTool =Framework::ITool::FindTool(m_curToolname);
		if (pTool != NULL)
		{
			pTool->LButtonUpEvent( nFlags, point);
		}

		__super::OnLButtonUp(nFlags, point);
	}

	void CMapControl::OnRButtonDown(UINT nFlags, CPoint point)
	{
		Framework::ITool *pTool =Framework::ITool::FindTool(m_curToolname);
		if (pTool != NULL)
		{
			pTool->RButtonDownEvent( nFlags, point);
		}

		__super::OnRButtonDown(nFlags, point);
	}

	void CMapControl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		Framework::ITool *pTool =Framework::ITool::FindTool(m_curToolname);
		if (pTool != NULL)
		{
			pTool->KeyDownEvent( nChar,nRepCnt,nFlags);
		}

		__super::OnKeyDown( nChar , nRepCnt, nFlags );
	}

	void CMapControl::OnMouseMove(UINT nFlags, CPoint point)
	{

		Framework::ITool *pTool =Framework::ITool::FindTool(m_curToolname);
		if (pTool != NULL)
		{
			pTool->MouseMoveEvent( nFlags, point);
		}

		GetExtractInfo();
		__super::OnMouseMove(nFlags, point);
	}

	void CMapControl::OnLButtonDblClk(UINT nFlags, CPoint point)
	{
		Framework::ITool *pTool =Framework::ITool::FindTool(m_curToolname);
		if (pTool != NULL)
		{
			pTool->LButtonDblClkEvent( nFlags, point);
		}

		return CWnd::OnLButtonDblClk(nFlags, point);
	}


	int CMapControl::OnCreate(LPCREATESTRUCT lpCreateStruct)
	{
		if (__super::OnCreate(lpCreateStruct) == -1)
			return -1;

		m_hClientDC = ::GetDC(GetSafeHwnd());
		m_hMemDC = ::CreateCompatibleDC(m_hClientDC);

		m_hCtrlWnd = this->GetSafeHwnd();

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



	BOOL CMapControl::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
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

	void CMapControl::CalSrcRect(GEOMETRY::geom::Envelope extent,CRect &rect)
	{
		//如果目标范围比原始范围大，则取整块memDC
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

		//绘制背景
		HBRUSH hbrush = ::CreateSolidBrush( RGB(255,255,255));

		::FillRect(hMemDC , &rect , hbrush );

		::DeleteObject( hbrush );

		double xmin,xmax,ymin,ymax;

		if (zDelta > 0) //放大
		{
			dblRatio = 0.8;

			m_dblScale *= dblRatio;

			m_pGeoMap->GetViewEnvelope().centre(point);

			xmin = point.x - lSceenWidth/2.0*m_dblScale;
			xmax = point.x + lSceenWidth/2.0*m_dblScale;
			ymin = point.y - lSceenHeight/2.0*m_dblScale;
			ymax = point.y + lSceenHeight/2.0*m_dblScale;

			GEOMETRY::geom::Envelope newExt(xmin,xmax,ymin,ymax);

			//改变地图的显示范围
			m_pGeoMap->GetDisplay()->GetDisplayTransformation().FitViewBound(newExt);

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

			::SetStretchBltMode(hMemDC,MAXSTRETCHBLTMODE);

			::StretchBlt(hMemDC,destRect.left,destRect.top,destRect.Width(),destRect.Height(),(HDC)pDispaly->GetDrawDC()->GetSafeHdc(),srcRect.left,srcRect.top,srcRect.Width(),srcRect.Height(),SRCCOPY);


			//::BitBlt(m_hMemDC,0,0,m_lSizeX,m_lSizeY,hMemDC,0,0,SRCCOPY);
			::BitBlt(m_hClientDC,0,0,m_lSizeX,m_lSizeY,hMemDC,0,0,SRCCOPY);

		}
		else if (zDelta < 0) //缩小
		{
			dblRatio = 1.2;

			m_dblScale *= dblRatio;

			m_pGeoMap->GetViewEnvelope().centre(point);

			xmin = point.x - lSceenWidth/2.0*m_dblScale;
			xmax = point.x + lSceenWidth/2.0*m_dblScale;
			ymin = point.y - lSceenHeight/2.0*m_dblScale;
			ymax = point.y + lSceenHeight/2.0*m_dblScale;

			GEOMETRY::geom::Envelope newExt(xmin,xmax,ymin,ymax);

			//改变地图的显示范围
			m_pGeoMap->GetDisplay()->GetDisplayTransformation().FitViewBound(newExt);


			CRect srcRect,destRect;

			CalSrcRect(m_pGeoMap->GetViewEnvelope(),srcRect);

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
		//如果在上个时间段，鼠标滚轮滑动,则将标记设为false
		if(m_bMouseWheel)
		{
			m_bMouseWheel =false;
		}
		else
		{

			m_pGeoMap->GetDisplay()->GetDisplayTransformation().ZoomToFixScale(m_dblScale);

			UpdateControl(drawAll);

			//记录视图范围
			GEOMETRY::geom::Envelope curExtent;
			m_pGeoMap->GetDisplay()->GetDisplayTransformation().GetGeoBound(curExtent);
			m_pGeoMap->GetDisplay()->GetDisplayTransformation().RecordCurExtent(curExtent);

			KillTimer(1);	
			m_bTimer = false;
		}

	}




	BOOL CMapControl::PreTranslateMessage(MSG* pMsg)
	{

		//用PreTranslateMessage的方法，判断Ctrl+C是否按下，按下就执行快捷键对应的操作
		if(pMsg->message == WM_KEYDOWN && pMsg->wParam == 'x')
		{
			//AfxMessageBox("Ctrl + X被按下");
			Framework::ICommand* pCommand = NULL;
			this->SetCurTool("CutElementCmd");
			pCommand=Framework::ICommand::FindCommand("CutElementCmd");
			if(pCommand)
			{
				pCommand->Initialize(dynamic_cast<Framework::IUIObject*>(this));
				pCommand->Click();
			}

			return TRUE;
		} 
		else if(pMsg->message == WM_KEYDOWN && pMsg->wParam == 'c')
		{
			Framework::ICommand* pCommand = NULL;
			this->SetCurTool("CopyElementCmd");
			pCommand=Framework::ICommand::FindCommand("CopyElementCmd");
			if(pCommand)
			{
				pCommand->Initialize(dynamic_cast<Framework::IUIObject*>(this));
				pCommand->Click();
			}
			return TRUE;
		} 
		else if(pMsg->message == WM_KEYDOWN && pMsg->wParam == 'v')
		{
			Framework::ICommand* pCommand = NULL;
			this->SetCurTool("PasteElementCmd");
			pCommand=Framework::ICommand::FindCommand("PasteElementCmd");
			if(pCommand)
			{
				pCommand->Initialize(dynamic_cast<Framework::IUIObject*>(this));
				pCommand->Click();
			}
			return TRUE;
		} 
		return __super::PreTranslateMessage(pMsg);
	}

	//获得状态栏
	IStatusInfo* CMapControl::GetStatusInfo()
	{
		if(m_pStatusInfo==NULL)
			return NULL;
		m_pStatusInfo->UpdateInfo(GetExtractInfo());
		return m_pStatusInfo;
	}
	
	std::string CMapControl::GetExtractInfo()
	{
		if(!m_pGeoMap)
			return "";
		IElementPtr ipElement = m_pGeoMap->GetGraphicLayer()->GetSelectedElement(0);
		if(ipElement==NULL)
			return "";

		if(ET_FILL_POLYGON_ELEMENT!=ipElement->GetType())
			return "";
		double dbArea = ipElement->GetGeometry()->getArea();
		
		double rate=1.0;
		std::string labelName ="总面积:";
		std::string strUnit ="平方米";
		char szLabelName[64];

		//投影
		
		if(SYSTEM::SYS_UNIT_TYPE::SYS_UNIT_METER != m_pGeoMap->GetUnit())
			rate =111;
		
		sprintf(szLabelName, "%.3f", dbArea*rate);
		labelName +=szLabelName+strUnit;
		return labelName;
	}
}