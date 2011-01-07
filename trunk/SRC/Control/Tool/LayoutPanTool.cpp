#include "stdafx.h"
#include "LayoutPanTool.h"
#include "Control.h"

extern CControlApp theApp;

static CLayoutPanTool glayoutPanTool;

CLayoutPanTool::CLayoutPanTool() : ITool("LayoutPanTool")
{
	m_hCursor = NULL;
}

CLayoutPanTool::~CLayoutPanTool()
{
	if(m_hCursor)
	{
		DeleteObject( m_hCursor );
	}
}

void CLayoutPanTool::Initialize(Framework::IUIObject *pTargetControl)
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
void CLayoutPanTool::LButtonDownEvent (UINT nFlags, CPoint point)
{

	if(!m_pLayoutCtrl)
		return;


	if(!m_pLayoutCtrl->GetPageLayout())
		return;

	//记录移动起点
	cPt0 = cPt1 = point;

	//
	SetCapture(m_pLayoutCtrl->GetHWnd());

}

void CLayoutPanTool::MouseMoveEvent (UINT nFlags, CPoint point)
{

	if(!(nFlags&MK_LBUTTON)) 
		return;

	if(!m_pLayoutCtrl)
		return;


	if(!m_pLayoutCtrl->GetPageLayout())
		return;

	//记录移动点位置
	cPt2 = point;

	//移动拷屏
	m_pLayoutCtrl->OffsetClient(cPt2.x-cPt1.x, cPt2.y-cPt1.y);

	cPt1 = cPt2;

}

void CLayoutPanTool::LButtonUpEvent (UINT nFlags, CPoint point)
{
	if(!m_pLayoutCtrl)
		return;


	if(!m_pLayoutCtrl->GetPageLayout())
		return;

	//记录最后点位置
	cPt2=point;

	double dScale = m_pLayoutCtrl->GetPageLayout()->GetDisplay()->GetDisplayTransformation().GetScale();
	double OffsetX = dScale * (cPt2.x-cPt0.x);
	double OffsetY = dScale * (cPt0.y-cPt2.y);
	m_pLayoutCtrl->GetPageLayout()->GetDisplay()->GetDisplayTransformation().MoveViewBound(OffsetX,OffsetY);

	//
	m_pLayoutCtrl->UpdateControl(drawAll);

	//
	ReleaseCapture();

}
