#include "StdAfx.h"
#include "DrawBezierCurveElementTool.h"



static CDrawBezierCurveElementTool gDrawPolylineTool;

CDrawBezierCurveElementTool::CDrawBezierCurveElementTool() : IDrawElementTool("DrawBezierCurveElementTool")
{
	m_pBezier.reset();
	m_nLastVertixId = 0;
}

CDrawBezierCurveElementTool::~CDrawBezierCurveElementTool()
{

}


void CDrawBezierCurveElementTool::Initialize(Framework::IUIObject *pTargetControl)
{
	IDrawElementTool::Initialize(pTargetControl);
}


void CDrawBezierCurveElementTool::LButtonDownEvent (UINT nFlags, CPoint point)
{
	IDrawElementTool::LButtonDownEvent (nFlags, point);
	

	//获取活动地区
	Display::IDisplayPtr pDisplay = m_pMap->GetDisplay();
	if(!pDisplay)
		return;


	//displaytoGeo
	GEOMETRY::geom::Coordinate coorCur;
	pDisplay->GetDisplayTransformation().ConvertDisplayToGeo(cPtStart.x, cPtStart.y, coorCur);

	if(!m_pBezier)
	{
		m_pBezier.reset(new Element::CBezierCurveElement(coorCur));

		m_pBezier->SetEditMode(Element::EEM_ONDRAW);

		m_nLastVertixId = 1;
	}
	else 
	{	
		if(m_nLastVertixId==1)
		{
			m_pBezier->MoveVertixTo( m_nLastVertixId, coorCur);
			m_pBezier->AddVertix( coorCur);
			m_nLastVertixId++;
		}
		else
		{
			m_pBezier->AddVertix( coorCur);
			m_nLastVertixId++;
		}
	}
}

void CDrawBezierCurveElementTool::MouseMoveEvent (UINT nFlags, CPoint point)
{
	if(!m_pBezier)
		return;

	IDrawElementTool::MouseMoveEvent (nFlags, point);

	if(point.x == cPtStart.x || point.y == cPtStart.y)
		return;

	//获取活动地区
	Display::IDisplayPtr pDisplay = m_pMap->GetDisplay();
	if(!pDisplay)
		return;

	//displaytoGeo
	GEOMETRY::geom::Coordinate coorCur;
	pDisplay->GetDisplayTransformation().ConvertDisplayToGeo(point.x, point.y, coorCur);

	m_pBezier->MoveVertixTo( m_nLastVertixId, coorCur);

	//更新绘制
	pDisplay->SetDrawBuffer(drawEdit);
	pDisplay->DrawBackgroud();
	m_pBezier->Draw(pDisplay);
	m_pMapCtrl->RefreshScreen();
}

void CDrawBezierCurveElementTool::LButtonUpEvent (UINT nFlags, CPoint point)
{
}

void CDrawBezierCurveElementTool::LButtonDblClkEvent (UINT nFlags, CPoint point)
{
	if(!m_pBezier)
		return;

	m_pBezier->RemoveVertix(m_nLastVertixId);
	m_nLastVertixId--;

	if (m_nLastVertixId >= 2  )
	{

		m_pMap->GetGraphicLayer()->AddElement(m_pBezier);
		m_pMap->GetGraphicLayer()->SelectElement(m_pBezier);	

		//加入回退堆栈
		//m_pMap->GetElementOperationStack()->AddOperation(Element::OPT_ADD, m_pBezier);
	}

	m_pBezier.reset();

	IDrawElementTool::LButtonDblClkEvent(nFlags, point);
	
	
}