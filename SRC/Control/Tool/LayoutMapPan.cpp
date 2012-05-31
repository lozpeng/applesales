#include "stdafx.h"
#include "LayoutMapPan.h"
#include "IMapCtrl.h"
#include "Control.h"

extern CControlApp theApp;

namespace Control
{

static CLayoutMapPan gActionMapPanTool;


CLayoutMapPan::CLayoutMapPan() : ITool("Layout_MapPan")
{
	m_hCursor = NULL;
}

CLayoutMapPan::~CLayoutMapPan()
{

}
void CLayoutMapPan::Initialize(Framework::IUIObject *pTargetControl)
{
	ITool::Initialize(pTargetControl);

	//初始化光标
	if(m_hCursor==NULL)
	{
		m_hCursor =::LoadCursor( theApp.m_hInstance , MAKEINTRESOURCE( IDC_PAN) );
	}

	//获取活动地图控件
	m_pLayoutCtrl = dynamic_cast<Framework::ILayoutCtrl*>(pTargetControl);
	if(!m_pLayoutCtrl)
		return;

	//设置光标类型
	m_pLayoutCtrl->SetCursor(m_hCursor);


}

void CLayoutMapPan::LButtonDownEvent (UINT nFlags, CPoint point)
{
	//记录移动起点
	cPt0 = cPt1 = point;

	//获取活动地图控件
	Framework::IMapCtrl *pMapCtrl = Framework::IMapCtrl::GetActiveMapCtrl();
	if(!pMapCtrl)
		return;

	//获取活动地区
	Carto::CMapPtr pActiveMap = pMapCtrl->GetMap();
	if(!pActiveMap)
		return;

	//备份MapDC
	Display::CDC* pDC = pActiveMap->GetDisplay()->GetDrawDC();
	HDC mapHdc = (HDC)pDC->GetSafeHdc();
	m_lDCWidth = pDC->GetDCWidth();
	m_lDCHeight = pDC->GetDCHeight();

	m_mapBackHDC = (HDC)::CreateCompatibleDC((HDC)pDC->GetSafeHdc());
	m_hBitmap = ::CreateCompatibleBitmap(mapHdc, m_lDCWidth, m_lDCHeight);
	m_hOldBitmap=(HBITMAP)::SelectObject(m_mapBackHDC,m_hBitmap);
	::BitBlt(m_mapBackHDC,0,0,m_lDCWidth,m_lDCHeight,mapHdc,0,0,SRCCOPY);

	//获取活动地图控件
	Framework::ILayoutCtrl *pLayoutCtrl = Framework::ILayoutCtrl::GetActiveLayoutCtrl();
	if(!pLayoutCtrl)
		return;

	SetCapture(pLayoutCtrl->GetHWnd());

}

void CLayoutMapPan::MouseMoveEvent (UINT nFlags, CPoint point)
{

	if(!(nFlags&MK_LBUTTON)) 
		return;

	//获取活动地图控件
	Framework::IMapCtrl *pMapCtrl = Framework::IMapCtrl::GetActiveMapCtrl();
	if(!pMapCtrl)
		return;

	//获取活动地区
	Carto::CMapPtr pMap = pMapCtrl->GetMap();
	if(!pMap)
		return;

	//记录移动点位置
	cPt2 = point;
	long offset_x = cPt2.x-cPt0.x, offset_y = cPt2.y-cPt0.y; 

	//移动拷屏
	Display::CDC* pDC = pMap->GetDisplay()->GetDrawDC();
	HBRUSH hbrush = ::CreateSolidBrush( pDC->GetBGColor() );
	RECT rc;
	rc.left=rc.top=0;rc.right=m_lDCWidth;rc.bottom=m_lDCHeight;
	
	::FillRect((HDC)pDC->GetSafeHdc() , &rc , hbrush );
	::BitBlt((HDC)pDC->GetSafeHdc(),offset_x,offset_y,m_lDCWidth,m_lDCHeight,m_mapBackHDC,0,0,SRCCOPY);

	::DeleteObject( hbrush );

	cPt1 = cPt2;

	Framework::ILayoutCtrl *pLayoutCtrl = Framework::ILayoutCtrl::GetActiveLayoutCtrl();
	if(!pLayoutCtrl)
		return;

	pLayoutCtrl->UpdateControl(drawElement);
}

void CLayoutMapPan::LButtonUpEvent (UINT nFlags, CPoint point)
{
	//获取活动地图控件
	Framework::IMapCtrl *pMapCtrl = Framework::IMapCtrl::GetActiveMapCtrl();
	if(!pMapCtrl)
		return;

	//获取活动地区
	Carto::CMapPtr pMap = pMapCtrl->GetMap();
	if(!pMap)
		return;

	//记录最后点位置
	cPt2=point;

	double dScale = pMap->GetDisplay()->GetDisplayTransformation().GetScale();
	double OffsetX = dScale * (cPt2.x-cPt0.x);
	double OffsetY = dScale * (cPt0.y-cPt2.y);
	pMap->GetDisplay()->GetDisplayTransformation().MoveViewBound(OffsetX,OffsetY);
	GEOMETRY::geom::Envelope mapGeoEnv = pMap->GetViewEnvelope();
	mapGeoEnv.init(mapGeoEnv.getMinX()-OffsetX, mapGeoEnv.getMaxX()-OffsetX, 
		mapGeoEnv.getMinY()-OffsetY, mapGeoEnv.getMaxY()-OffsetY);

	pMap->SetViewEnvelope(mapGeoEnv);

	Framework::ILayoutCtrl *pLayoutCtrl = Framework::ILayoutCtrl::GetActiveLayoutCtrl();
	if(!pLayoutCtrl)
		return;

	pLayoutCtrl->UpdateControl();

	::SelectObject(m_mapBackHDC,m_hOldBitmap);
	::DeleteObject(m_hBitmap);
	::DeleteDC(m_mapBackHDC);


	ReleaseCapture();
}
}