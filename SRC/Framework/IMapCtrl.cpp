#include "stdafx.h"
#include "IMapCtrl.h"

namespace Framework
{


IMapCtrl::IMapCtrl()
{
	m_BgColor = RGB(255,255,255);
	m_hClientDC = 0;
	m_hMemDC = 0;
	m_lSizeX=0;
	m_lSizeY=0;

	m_cursor =NULL;

	m_hCtrlWnd =NULL;
}

IMapCtrl::~IMapCtrl()
{
	
}



// 重新绘制，刷新缓冲区，但不更新屏幕
void IMapCtrl::ReDraw(long content)
{
	if(m_pGeoMap)
	{
		m_pGeoMap->Draw(content);
	}

}

void IMapCtrl::SetMap(Carto::CMapPtr pGeoMap)
{
	m_pGeoMap = pGeoMap;

	if(!pGeoMap)
	{
		return;
	}

	m_pGeoMap->GetDisplay()->SetDC((long)GetMemDC(),m_lSizeX, m_lSizeY);
	UpdateControl(drawAll);

}

Carto::CMapPtr IMapCtrl::GetMap()
{
	return m_pGeoMap;
}



void IMapCtrl::ControlResize(UINT nType, int cx, int cy)
{
	m_lSizeX = cx;
	m_lSizeY = cy;

	if(cx!=0 && cy!=0)
	{
		DIS_BOUND rect;
		rect.left = rect.top = 0;
		rect.right = cx;
		rect.bottom = cy;

		if(m_pGeoMap == NULL)
			return;
		//更新显示缓存的大小
		m_pGeoMap->GetDisplay()->GetDrawDC()->CacheBitmap(cx,cy);

		//更新可视范围的大小
		m_pGeoMap->SetViewBound(rect);

		//重新地图
		UpdateControl(drawAll);

	}

}

void IMapCtrl::UpdateControl(long content)
{
	//
	ReDraw(content);

	//
	RefreshScreen();
}


void IMapCtrl::OffsetClient(long offset_x, long offset_y)
{
	if(m_pGeoMap)
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


void IMapCtrl::RefreshScreen()
{

	//
	if(m_pGeoMap)
	{
		m_pGeoMap->GetDisplay()->SetDrawBuffer(drawAll);
		m_pGeoMap->GetDisplay()->DrawBackgroud();
		m_pGeoMap->GetDisplay()->RefreshDisplay(drawAll);

		//
		BitBlt(m_hClientDC, 0, 0, m_lSizeX, m_lSizeY, m_hMemDC, 0, 0, SRCCOPY);
	}
}

void IMapCtrl::RefreshGeography()
{
	if(m_pGeoMap)
	{
		BitBlt(m_hClientDC, 0, 0, m_lSizeX, m_lSizeY, m_hMemDC, 0, 0, SRCCOPY);
	}
}

HWND IMapCtrl::GetHWnd()
{
	return m_hCtrlWnd;
}

void IMapCtrl::SetCursor(HCURSOR cursor)
{
	m_cursor =cursor;
}

IMapCtrl* IMapCtrl::GetActiveMapCtrl()
{
	IMapCtrl* pMapCtrl = (IMapCtrl*)IUIObject::GetUIObjectByName(CommonUIName::AppMapControl);
	return pMapCtrl;
}

}