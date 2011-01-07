#include "stdafx.h"
#include "DrawCalloutTextElementTool.h"

namespace Control
{

static CDrawCalloutTextElementTool gDrawCalloutTextElementTool;

CDrawCalloutTextElementTool::CDrawCalloutTextElementTool() : IDrawElementTool("DrawCalloutTextElementTool")
{
	m_bLBtnDown = FALSE;
}

CDrawCalloutTextElementTool::~CDrawCalloutTextElementTool()
{

}

void CDrawCalloutTextElementTool::Initialize(Framework::IUIObject *pTargetControl)
{
	IDrawElementTool::Initialize(pTargetControl);
}

void CDrawCalloutTextElementTool::LButtonDownEvent (UINT nFlags, CPoint point)
{
	IDrawElementTool::LButtonDownEvent (nFlags, point);
	
	UpdateStartPoint(point);
	
	m_bLBtnDown = TRUE;

	
	if(!m_pMapCtrl)
		return;

	//获取活动地区
	Display::IDisplayPtr pDisplay = m_pMapCtrl->GetMap()->GetDisplay();
	if(!pDisplay)
		return;

	//displaytoGeo
	GEOMETRY::geom::Geometry* pGeo;
	GEOMETRY::geom::Envelope env;
	DIS_RECT rect;
	rect.left = point.x;
	rect.right = point.x + 10;
	rect.top = point.y;
	rect.bottom = point.y +10;
	pDisplay->GetDisplayTransformation().TransformToGeo(rect, &env);

	m_pText.reset(new Element::CCalloutTextElement(env));

	m_pMapCtrl->GetMap()->GetGraphicLayer()->UnselectAllElements();
	m_pMapCtrl->GetMap()->GetGraphicLayer()->AddElement(m_pText);
	m_pMapCtrl->GetMap()->GetGraphicLayer()->SelectElement(m_pText);	
	
	//加入回退堆栈
	//m_pMapCtrl->GetMap()->GetElementOperationStack()->AddOperation(Element::OPT_ADD, m_pText);
	

	//更新绘制
	m_pMapCtrl->UpdateControl(drawElement | drawEdit);

	SetCapture(m_pMapCtrl->GetHWnd());

}

void CDrawCalloutTextElementTool::MouseMoveEvent (UINT nFlags, CPoint point)
{

	//获取活动地图控件
	if(!m_pMapCtrl)
		return;

	Display::IDisplayPtr pDisplay = m_pMapCtrl->GetMap()->GetDisplay();
	if(!pDisplay)
		return;

	GEOMETRY::geom::Coordinate curCoord;
	//更新矩形角点坐标
	pDisplay->GetDisplayTransformation().ConvertDisplayToGeo(point.x, point.y, curCoord);

	if(m_bLBtnDown && m_pText)
	{
		m_pText->Move(curCoord.x-m_endCoord.x, curCoord.y-m_endCoord.y );
		if(!m_pMapCtrl)
			return;

		m_pMapCtrl->UpdateControl(drawEdit);
	}

	UpdateEndPoint(point);
}

void CDrawCalloutTextElementTool::LButtonUpEvent (UINT nFlags, CPoint point)
{
	IDrawElementTool::LButtonUpEvent(nFlags, point);
	m_bLBtnDown = FALSE;

	if(!m_pMapCtrl)
		return;

	m_pMapCtrl->UpdateControl(drawElement | drawEdit);
	//m_pMapCtrl->SetCursor(cursorNormal);

	ReleaseCapture();

	//工具设为选择
	Framework::ITool* pTool = NULL;
	m_pMapCtrl->SetCurTool("SelectElementTool");

	pTool=Framework::ITool::FindTool("SelectElementTool");
	if(pTool)
	{
		pTool->Initialize(dynamic_cast<Framework::IUIObject*>(m_pMapCtrl));
	}
}

void CDrawCalloutTextElementTool::UpdateStartPoint(CPoint pt)
{
	if(!m_pMapCtrl)
		return;

	Display::IDisplayPtr pDisplay = m_pMapCtrl->GetMap()->GetDisplay();
	if(!pDisplay)
		return;

	//更新矩形角点坐标
	pDisplay->GetDisplayTransformation().ConvertDisplayToGeo(pt.x, pt.y, m_startCoord);
}

void CDrawCalloutTextElementTool::UpdateEndPoint(CPoint pt)
{
	if(!m_pMapCtrl)
		return;

	Display::IDisplayPtr pDisplay = m_pMapCtrl->GetMap()->GetDisplay();
	if(!pDisplay)
		return;

	//更新矩形角点坐标
	pDisplay->GetDisplayTransformation().ConvertDisplayToGeo(pt.x, pt.y, m_endCoord);
}
}