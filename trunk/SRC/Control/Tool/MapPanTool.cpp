#include "stdafx.h"
#include "MapPanTool.h"


namespace Control
{

static CToolMapPan gActionPan;

CToolMapPan::CToolMapPan() : Framework::ITool("MapPan")
{
	m_pMapCtrl =NULL;
}

CToolMapPan::~CToolMapPan()
{

}

void CToolMapPan::Initialize(Framework::IUIObject *pTargetControl)
{
	ITool::Initialize(pTargetControl);

	//获取活动地图控件
	m_pMapCtrl = dynamic_cast<Framework::IMapCtrl*>(pTargetControl);
	if(!m_pMapCtrl)
		return;

	//设置光标类型
	//pMapCtrl->SetCursorType(cursorPan);

	
}

void CToolMapPan::LButtonDownEvent (UINT nFlags, CPoint point)
{
	//获取活动地图控件
	if(!m_pMapCtrl)
		return;

	//记录移动起点
	cPt0 = cPt1 = point;

	//
	SetCapture(m_pMapCtrl->GetHWnd());

}

void CToolMapPan::MouseMoveEvent (UINT nFlags, CPoint point)
{

	if(!(nFlags&MK_LBUTTON)) 
		return;

	if(!m_pMapCtrl)
		return;

	//记录移动点位置
	cPt2 = point;

	//移动拷屏
	m_pMapCtrl->OffsetClient(cPt2.x-cPt1.x, cPt2.y-cPt1.y);

	cPt1 = cPt2;

}

void CToolMapPan::LButtonUpEvent (UINT nFlags, CPoint point)
{
	//获取活动地图控件
	if(!m_pMapCtrl)
		return;

	//获取活动地区
	Carto::CMapPtr pMap = m_pMapCtrl->GetMap();
	if(!pMap)
		return;

	//记录最后点位置
	cPt2=point;

	double dScale = pMap->GetDisplay()->GetDisplayTransformation().GetScale();
	double OffsetX = dScale * (cPt2.x-cPt0.x);
	double OffsetY = dScale * (cPt0.y-cPt2.y);
	pMap->GetDisplay()->GetDisplayTransformation().MoveViewBound(OffsetX,OffsetY);

	//
	m_pMapCtrl->UpdateControl(drawAll);

	//
	ReleaseCapture();

}
}