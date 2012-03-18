#include "stdafx.h"
#include "ActionPan.h"
#include "..\otMapControl.h"
#include "..\otMapCtrl.h"
#include "Map.h"



CActionPan::CActionPan() : IAction(actionPan)
{
	RegisterAction(actionPan,this);
}

CActionPan::~CActionPan()
{

}

void CActionPan::Init(CotMapCtrl *pMapCtrl,Carto::CMap *pMap)
{
	IAction::Init(pMapCtrl,pMap);

    
    pMapCtrl->SetCursorType(cursorPan);
	
}

void CActionPan::LButtonDownEvent (UINT nFlags, CPoint point)
{
	if(!m_pMapCtrl || !m_pMap)
	{
		return;
	}
	

	//记录移动起点
	cPt0 = cPt1 = point;

	//锁定鼠标
	m_pMapCtrl->SetCapture();

}

void CActionPan::MouseMoveEvent (UINT nFlags, CPoint point)
{
	if(!m_pMapCtrl || !m_pMap)
	{
		return;
	}


	if(!(nFlags&MK_LBUTTON)) 
		return;


	//记录移动点位置
	cPt2 = point;

	//移动拷屏
	m_pMapCtrl->OffsetClient(cPt2.x-cPt1.x, cPt2.y-cPt1.y);

	cPt1 = cPt2;

}

void CActionPan::LButtonUpEvent (UINT nFlags, CPoint point)
{
	if(!m_pMapCtrl || !m_pMap)
	{
		return;
	}
	

	//记录最后点位置
	cPt2=point;

	double dScale = m_pMap->GetDisplay()->GetDisplayTransformation().GetViewPosition().GetScale();
	double OffsetX = dScale * (cPt2.x-cPt0.x);
	double OffsetY = dScale * (cPt0.y-cPt2.y);
	m_pMap->GetDisplay()->GetDisplayTransformation().MoveViewBound(OffsetX,OffsetY);

	//
	m_pMapCtrl->Refresh();

	//
	//解除锁定鼠标
	m_pMapCtrl->ReleaseCapture();

}
