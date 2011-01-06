#include "StdAfx.h"
#include "LayoutControl.h"

namespace Control
{

	IMPLEMENT_DYNAMIC(CLayoutControl, CWnd)


	CLayoutControl::CLayoutControl(void)
	{
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
		//ON_WM_TIMER()

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


	/*void CLayoutControl::LoadTemplate(IGeoMap* map, BSTR templatefile)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		CRect rect;
		GetClientRect(rect);
		m_pPageLayout.reset(new Carto::CPageLayout());
		m_pPageLayout->Initialize((long)m_hMemDC,rect.Width(),rect.Height());

		CFile file;
		if(!file.Open(templatefile,CFile::modeRead))
		{
			return;
		}

		CString PrjPath =templatefile;
		CString basePath =PrjPath.Left(PrjPath.ReverseFind(_T('\\'))+1);

		_bstr_t strPath =basePath;

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

				IOriginDataPtr pData;


				map->QueryInterface(__uuidof(IOriginData),(void**)&pData);

				long ldata;
				pData->get_OriginData(&ldata);

				Carto::CMapPtr pMap =*((Carto::CMapPtr*)(ldata));


				pMapFrame->SetMap(pMap);

				break;
			}
			pElement = pLayer->Next();
		}


		delete[] pStart;

		Refresh();
	}
*/


}