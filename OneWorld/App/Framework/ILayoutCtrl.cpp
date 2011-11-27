#include "stdafx.h"
#include "ILayoutCtrl.h"
#include "ITool.h"
#include "MapFrame.h"

#include "GraphicLayer.h"
#include "IMapCtrl.h"
#include "Page.h"

namespace Framework
{

	ILayoutCtrl::ILayoutCtrl()
	{
		m_bInitialized = FALSE;
		m_BgColor = RGB(255,255,255);
		m_hClientDC = 0;
		m_hMemDC = 0;
		m_lSizeX=0;
		m_lSizeY=0;

		m_cursor =NULL;

		m_hCtrlWnd =NULL;
	}

	ILayoutCtrl::~ILayoutCtrl()
	{

	}

	ILayoutCtrl* ILayoutCtrl::GetActiveLayoutCtrl()
	{
		ILayoutCtrl* pLayoutCtrl = (ILayoutCtrl*)IUIObject::GetUIObjectByName(CommonUIName::AppLayoutControl);
		return pLayoutCtrl;
	}

	Carto::CPageLayoutPtr ILayoutCtrl::GetPageLayout()
	{
		return m_pPageLayout;
	}
	void ILayoutCtrl::SetPageLayout(Carto::CPageLayoutPtr pPageLayout)
	{		
		if(!pPageLayout)
		{
			return;
		}

		m_pPageLayout = pPageLayout;
		
		pPageLayout->GetDisplay()->SetDC((long)GetMemDC(),m_lSizeX, m_lSizeY);
		UpdateControl(drawAll);
	}
	BOOL ILayoutCtrl::Initialized()
	{
		return m_bInitialized;
	}

	void ILayoutCtrl::Initialize()
	{
		m_pPageLayout.reset(new Carto::CPageLayout());
		m_pPageLayout->Initialize((long)GetMemDC(),GetSizeX(),GetSizeY());

		m_bInitialized = TRUE;
	}

	void ILayoutCtrl::ClearCtrl()
	{
		m_pPageLayout.reset(new Carto::CPageLayout());
		m_pPageLayout->Initialize((long)GetMemDC(),GetSizeX(),GetSizeY());

		UpdateControl();
	}

	void ILayoutCtrl::UpdateControl(long content)
	{
		//
		ReDraw(content);

		//
		RefreshScreen();
	}

	// ���»��ƣ�ˢ�»�����������������Ļ
	void ILayoutCtrl::ReDraw(long content)
	{
		if(m_pPageLayout)
		{
			m_pPageLayout->Draw(content);
		}

	}

	// ������Ļ
	void ILayoutCtrl::RefreshScreen()
	{
		//
		if(m_pPageLayout)
		{
			m_pPageLayout->GetDisplay()->SetDrawBuffer(drawAll);
			m_pPageLayout->GetDisplay()->DrawBackgroud();
			m_pPageLayout->GetDisplay()->RefreshDisplay(drawElement | drawEdit);

			BitBlt(m_hClientDC, 0, 0, m_lSizeX, m_lSizeY, m_hMemDC, 0, 0, SRCCOPY);
		}	
	}

	void ILayoutCtrl::OffsetClient(long offset_x, long offset_y)
	{
		if(m_pPageLayout)
		{
			RECT rc;
			HBRUSH hbrush = ::CreateSolidBrush( m_BgColor );
			HDC hMemDC = ::CreateCompatibleDC(m_hClientDC);
			HBITMAP hOldBitmap,hBitmap = ::CreateCompatibleBitmap(m_hClientDC, m_lSizeX, m_lSizeY);

			rc.left=rc.top=0;rc.right=m_lSizeX;rc.bottom=m_lSizeY;

			hOldBitmap=(HBITMAP)::SelectObject(hMemDC,hBitmap);
			::FillRect(hMemDC , &rc , hbrush );
			::BitBlt(hMemDC,offset_x,offset_y,m_lSizeX,m_lSizeY,m_hMemDC,0,0,SRCCOPY);
			::BitBlt(m_hMemDC,0,0,m_lSizeX,m_lSizeY,hMemDC,0,0,SRCCOPY);
			::BitBlt(m_hClientDC,0,0,m_lSizeX,m_lSizeY,hMemDC,0,0,SRCCOPY);

			::SelectObject(hMemDC,hOldBitmap);
			::DeleteObject( hbrush );
			::DeleteObject(hBitmap);
			::DeleteDC(hMemDC);
		}
	}

	void ILayoutCtrl::serialization(SYSTEM::IArchive &ar)
	{
		IUIObject::serialization(ar);

		if (ar.IsRead())
		{
			// TODO: add loading code here
			m_pPageLayout.reset(new Carto::CPageLayout());
			m_pPageLayout->Initialize((long)GetMemDC(),GetSizeX(),GetSizeY());
			m_pPageLayout->serialization(ar);
			m_bInitialized = TRUE;

			Carto::CGraphicLayerPtr pLayer = m_pPageLayout->GetGraphicLayer();

			IMapCtrl* pMapCtrl = (IMapCtrl*)IUIObject::GetUIObjectByName("STANDARD_MAPCTRL");

			Element::IElementPtr pElement = pLayer->Reset();
			while(pElement)
			{
				if(pElement->GetType() == Element::ET_MAP_FRAME_ELEMENT)
				{
					Element::CMapFrame* pMapFrame = dynamic_cast<Element::CMapFrame*>(pElement.get());
					long mapID = pMapFrame->GetMapID();
					Carto::CMapPtr pMap ;//= pMapCtrl->GetMapByID(mapID);

					pMapFrame->SetMap(pMap);
				}
				pElement = pLayer->Next();
			}

			m_bInitialized = TRUE;

			UpdateControl();
		}
		else
		{
			// TODO: add storing code here
			m_pPageLayout->serialization(ar);		
		}
	}

	void ILayoutCtrl::OnBeginPrinting(CDC* pDC)
	{	
		Display::IDisplayPtr pDisplay =  m_pPageLayout->GetDisplay();
		Display::CDC* pDrawDC = pDisplay->GetDrawDC();

		//����DC����Լ���ǰ��ʾ��Χ
		m_bakDCWidth = pDrawDC->GetDCWidth();
		m_bakDCHeight = pDrawDC->GetDCHeight();
		m_bakHdc = pDrawDC->GetSafeHdc();
		pDisplay->GetDisplayTransformation().GetGeoBound(m_bakEnv);

		//��page����page�ڴ�ӡ�豸�еĿ�ߵľ�����
		long logx = pDC->GetDeviceCaps(LOGPIXELSX);//��ӡ�豸����������/inch
		long logy = pDC->GetDeviceCaps(LOGPIXELSY);

		Element::CPagePtr pPage = m_pPageLayout->GetPage();
		double ratio = SYSTEM::UnitConverter::ConvertUnits(1, SYSTEM::SYS_UNIT_INCH, pPage->GetUnit());
		double logxPageUnit = logx/ratio;//��ӡ�豸����������/ֽ�ŵ�λ
		double logyPageUnit = logy/ratio;

		GEOMETRY::geom::Envelope envGeo = pPage->GetPageEnvelope();
		long pageWidthPixel = envGeo.getWidth()*logxPageUnit;//page�ڴ�ӡ�豸�Ŀ���ӡ�豸���أ�
		long pageHeightPixel = envGeo.getHeight()*logyPageUnit;

		DIS_BOUND rect;
		rect.left = rect.top = 0;
		rect.right = pageWidthPixel;
		rect.bottom = pageHeightPixel;

		pDisplay->GetDisplayTransformation().SetViewBound(rect);
		pDisplay->GetDisplayTransformation().FitViewBound(envGeo);

		pDisplay->SetPrinting(TRUE);
	}

	void ILayoutCtrl::OnEndPrinting(CDC* pDC)
	{
		//��ԭDC
		Display::IDisplayPtr pDisplay = m_pPageLayout->GetDisplay();
		Display::CDC* pDrawDC = pDisplay->GetDrawDC();
		pDrawDC->SetDC(m_bakHdc, m_bakDCWidth,m_bakDCHeight);

		//��ԭ��С
		DIS_BOUND rect;
		rect.left = rect.top = 0;
		rect.right = m_bakDCWidth;
		rect.bottom = m_bakDCHeight;

		pDisplay->GetDisplayTransformation().SetViewBound(rect);
		pDisplay->GetDisplayTransformation().FitViewBound(m_bakEnv);

		pDisplay->SetPrinting(FALSE);

		UpdateControl();
	}

	void ILayoutCtrl::OnPrint(CDC* pDC)
	{
		//�����µ�DC
		Display::CDC* pDrawDC = m_pPageLayout->GetDisplay()->GetDrawDC();

		long printDCWidth = pDC->GetDeviceCaps(HORZRES);//��ӡ�豸����������

		long printDCHeight = pDC->GetDeviceCaps(VERTRES);//��ӡ�豸��ֱ������

		pDrawDC->SetDC((long)pDC->GetSafeHdc(), printDCWidth, printDCHeight);

		m_pPageLayout->Draw(drawElement);
	}

	void ILayoutCtrl::ControlResize(UINT nType, int cx, int cy)
	{
		m_lSizeX =cx;
		m_lSizeY =cy;

		if(cx!=0 && cy!=0)
		{
			DIS_BOUND rect;
			rect.left = rect.top = 0;
			rect.right = cx;
			rect.bottom = cy;

			if(m_pPageLayout)
			{		

				//������ʾ����Ĵ�С
				m_pPageLayout->GetDisplay()->CacheBuffer(cx,cy);

				//���¿��ӷ�Χ�Ĵ�С
				m_pPageLayout->GetDisplay()->GetDisplayTransformation().SetViewBound(rect);

				
				//���µ�ͼ
				UpdateControl(drawAll);

			}
		}

	}

	void ILayoutCtrl::SetCursor(HCURSOR cursor)
	{
		m_cursor =cursor;
	}

	HWND ILayoutCtrl::GetHWnd()
	{
		return m_hCtrlWnd;
	}
}