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

	//��ʼ�����
	if(m_hCursor==NULL)
	{
		m_hCursor =::LoadCursor( theApp.m_hInstance , MAKEINTRESOURCE( IDC_PAN) );
	}

	//��ȡ���ͼ�ؼ�
	m_pLayoutCtrl = dynamic_cast<Framework::ILayoutCtrl*>(pTargetControl);
	if(!m_pLayoutCtrl)
		return;

	//���ù������
	m_pLayoutCtrl->SetCursor(m_hCursor);


}

void CLayoutMapPan::LButtonDownEvent (UINT nFlags, CPoint point)
{
	//��¼�ƶ����
	cPt0 = cPt1 = point;

	//��ȡ���ͼ�ؼ�
	Framework::IMapCtrl *pMapCtrl = Framework::IMapCtrl::GetActiveMapCtrl();
	if(!pMapCtrl)
		return;

	//��ȡ�����
	Carto::CMapPtr pActiveMap = pMapCtrl->GetMap();
	if(!pActiveMap)
		return;

	//����MapDC
	Display::CDC* pDC = pActiveMap->GetDisplay()->GetDrawDC();
	HDC mapHdc = (HDC)pDC->GetSafeHdc();
	m_lDCWidth = pDC->GetDCWidth();
	m_lDCHeight = pDC->GetDCHeight();

	m_mapBackHDC = (HDC)::CreateCompatibleDC((HDC)pDC->GetSafeHdc());
	m_hBitmap = ::CreateCompatibleBitmap(mapHdc, m_lDCWidth, m_lDCHeight);
	m_hOldBitmap=(HBITMAP)::SelectObject(m_mapBackHDC,m_hBitmap);
	::BitBlt(m_mapBackHDC,0,0,m_lDCWidth,m_lDCHeight,mapHdc,0,0,SRCCOPY);

	//��ȡ���ͼ�ؼ�
	Framework::ILayoutCtrl *pLayoutCtrl = Framework::ILayoutCtrl::GetActiveLayoutCtrl();
	if(!pLayoutCtrl)
		return;

	SetCapture(pLayoutCtrl->GetHWnd());

}

void CLayoutMapPan::MouseMoveEvent (UINT nFlags, CPoint point)
{

	if(!(nFlags&MK_LBUTTON)) 
		return;

	//��ȡ���ͼ�ؼ�
	Framework::IMapCtrl *pMapCtrl = Framework::IMapCtrl::GetActiveMapCtrl();
	if(!pMapCtrl)
		return;

	//��ȡ�����
	Carto::CMapPtr pMap = pMapCtrl->GetMap();
	if(!pMap)
		return;

	//��¼�ƶ���λ��
	cPt2 = point;
	long offset_x = cPt2.x-cPt0.x, offset_y = cPt2.y-cPt0.y; 

	//�ƶ�����
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
	//��ȡ���ͼ�ؼ�
	Framework::IMapCtrl *pMapCtrl = Framework::IMapCtrl::GetActiveMapCtrl();
	if(!pMapCtrl)
		return;

	//��ȡ�����
	Carto::CMapPtr pMap = pMapCtrl->GetMap();
	if(!pMap)
		return;

	//��¼����λ��
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