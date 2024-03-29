#include "stdafx.h"
#include "ActionDrawPolylineElement.h"
#include "..\otMapControl.h"
#include "..\otMapCtrl.h"



CActionDrawPolylineElement::CActionDrawPolylineElement() : IActionDrawElement(actionDrawPolylineElement)
{
	m_pPolyline.reset();
	m_nLastVertixId = 0;
}

CActionDrawPolylineElement::~CActionDrawPolylineElement()
{

}

void CActionDrawPolylineElement::Init(CotMapCtrl *pMapCtrl,Carto::CMap *pMap)
{
	IActionDrawElement::Init(pMapCtrl,pMap);
}

void CActionDrawPolylineElement::LButtonDownEvent (UINT nFlags, CPoint point)
{
	IActionDrawElement::LButtonDownEvent (nFlags, point);

	

	//获取活动地区
	Display::IDisplayPtr pDisplay = m_pMap->GetDisplay();
	if(!pDisplay)
		return;

	//displaytoGeo
	GEOMETRY::geom::Coordinate coorCur;
	pDisplay->GetDisplayTransformation().ConvertDisplayToGeo(cPtStart.x, cPtStart.y, coorCur);

	if(!m_pPolyline)//创建一个矩形图元
	{
		m_pPolyline.reset(new Element::CPolylineElement(coorCur));

		m_pPolyline->SetEditMode(Element::EEM_ONDRAW);

		m_nLastVertixId = 1;
	}
	else //更新矩形角点坐标
	{	
		if(m_nLastVertixId==1)
		{
			m_pPolyline->MoveVertixTo( m_nLastVertixId, coorCur);
			m_pPolyline->AddVertix( coorCur);
			m_nLastVertixId++;
		}
		else
		{
			m_pPolyline->AddVertix( coorCur);
			m_nLastVertixId++;
		}
	}
}

void CActionDrawPolylineElement::MouseMoveEvent (UINT nFlags, CPoint point)
{
	if(!m_pPolyline)
		return;

	IActionDrawElement::MouseMoveEvent (nFlags, point);

	if(point.x == cPtStart.x || point.y == cPtStart.y)
		return;

	
	//获取活动地区
	Display::IDisplayPtr pDisplay = m_pMap->GetDisplay();
	if(!pDisplay)
		return;

	//displaytoGeo
	GEOMETRY::geom::Coordinate coorCur;
	pDisplay->GetDisplayTransformation().ConvertDisplayToGeo(point.x, point.y, coorCur);

	m_pPolyline->MoveVertixTo( m_nLastVertixId, coorCur);

	//更新绘制
	pDisplay->SetDrawBuffer(drawEdit);
	pDisplay->DrawBackgroud();
	m_pPolyline->Draw(pDisplay);
	m_pMapCtrl->RefreshScreen();
}

void CActionDrawPolylineElement::LButtonUpEvent (UINT nFlags, CPoint point)
{
}

void CActionDrawPolylineElement::LButtonDblClkEvent (UINT nFlags, CPoint point)
{
	if(!m_pPolyline)
		return;

	m_pPolyline->RemoveVertix(m_nLastVertixId);
	m_nLastVertixId--;

	if (m_nLastVertixId >= 2  )
	{
		
		m_pMap->GetGraphicLayer()->AddElement(m_pPolyline);
		m_pMap->GetGraphicLayer()->SelectElement(m_pPolyline);	
	}
	
	m_pPolyline.reset();

	IActionDrawElement::LButtonDblClkEvent(nFlags, point);
	//工具设为选择
	m_pMapCtrl->SetAction(actionSelectElement);
}
