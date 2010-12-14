#include "StdAfx.h"
#include "DrawFreehandLineTool.h"
#include "MapControl.h"

static CDrawFreehandLineTool gDrawFreehandLineTool;
CDrawFreehandLineTool::CDrawFreehandLineTool(void): IDrawElementTool("DrawFreehandLineElement")
{
	m_pFreehanline.reset();
	m_nLastVertixId = 1;
}

CDrawFreehandLineTool::~CDrawFreehandLineTool(void)
{
}

void CDrawFreehandLineTool::Initialize(Framework::IUIObject *pTargetControl)
{
	IDrawElementTool::Initialize(pTargetControl);
}
void CDrawFreehandLineTool::LButtonDownEvent(UINT nFlags, CPoint point)
{
	IDrawElementTool::LButtonDownEvent (nFlags, point);


	//获取活动地区
	Display::IDisplayPtr pDisplay = m_pMap->GetDisplay();
	if(!pDisplay)
		return;

	//displaytoGeo
	GEOMETRY::geom::Coordinate coorCur;
	pDisplay->GetDisplayTransformation().ConvertDisplayToGeo(cPtStart.x, cPtStart.y, coorCur);

	//创建一个线图元
	m_pFreehanline.reset(new Element::CPolylineElement(coorCur));

	m_pFreehanline->SetEditMode(Element::EEM_ONDRAW);

	m_pFreehanline->MoveVertixTo( m_nLastVertixId, coorCur);
	m_pFreehanline->AddVertix( coorCur);
	m_nLastVertixId++;

}

void CDrawFreehandLineTool::LButtonUpEvent(UINT nFlags, CPoint point)
{
	if(!m_pFreehanline)
		return;

	m_pFreehanline->RemoveVertix(m_nLastVertixId);
	m_nLastVertixId--;

	if (m_nLastVertixId >= 2  )
	{
		m_pMap->GetGraphicLayer()->AddElement(m_pFreehanline);
		m_pMap->GetGraphicLayer()->SelectElement(m_pFreehanline);	

		//加入回退堆栈
		//m_pMap->GetElementOperationStack()->AddOperation(Element::OPT_ADD, m_pFreehanline);
	}

	m_pFreehanline.reset();

	//更新绘制
	m_pMapCtrl->UpdateControl(DrawContent(drawElement|drawEdit));

	IDrawElementTool::LButtonDblClkEvent(nFlags, point);

	
}
void CDrawFreehandLineTool::MouseMoveEvent(UINT nFlags, CPoint point)
{
	if(!m_pFreehanline)
		return;

	IDrawElementTool::MouseMoveEvent (nFlags, point);


	//获取活动地区
	Display::IDisplayPtr pDisplay = m_pMap->GetDisplay();
	if(!pDisplay)
		return;

	//displaytoGeo
	GEOMETRY::geom::Coordinate coorCur;
	pDisplay->GetDisplayTransformation().ConvertDisplayToGeo(point.x, point.y, coorCur);

	m_pFreehanline->MoveVertixTo( m_nLastVertixId, coorCur);
	m_pFreehanline->AddVertix( coorCur);
	m_nLastVertixId++;
	//更新绘制
	pDisplay->SetDrawBuffer(drawEdit);
	pDisplay->DrawBackgroud();
	m_pFreehanline->Draw(pDisplay);
	m_pMapCtrl->RefreshScreen();
}
