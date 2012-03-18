#include "stdafx.h"
#include "actionDrawRectangleElement.h"
#include "..\otMapControl.h"
#include "..\otMapCtrl.h"



CActionDrawRectangleElement::CActionDrawRectangleElement() : IActionDrawElement(actionDrawRectElement)
{
	m_pRectangle.reset();
}

CActionDrawRectangleElement::~CActionDrawRectangleElement()
{

}

void CActionDrawRectangleElement::Init(CotMapCtrl *pMapCtrl,Carto::CMap *pMap)
{
	IActionDrawElement::Init(pMapCtrl,pMap);
}

void CActionDrawRectangleElement::LButtonDownEvent (UINT nFlags, CPoint point)
{
	IActionDrawElement::LButtonDownEvent (nFlags, point);
}

void CActionDrawRectangleElement::MouseMoveEvent (UINT nFlags, CPoint point)
{
	IActionDrawElement::MouseMoveEvent (nFlags, point);

	if(!(nFlags&MK_LBUTTON)) 
		return;

	if(point.x == cPtStart.x || point.y == cPtStart.y)
		return;

	
	//获取活动地区
	Display::IDisplayPtr pDisplay = m_pMap->GetDisplay();
	if(!pDisplay)
		return;

	//displaytoGeo
	double xStart,yStart, xEnd,yEnd;
	pDisplay->GetDisplayTransformation().ConvertDisplayToGeo(cPtStart.x, cPtStart.y, xStart, yStart);
	pDisplay->GetDisplayTransformation().ConvertDisplayToGeo(cPtEnd.x, cPtEnd.y, xEnd, yEnd);

	
	if(!m_pRectangle)//创建一个矩形图元
	{
		m_pRectangle.reset(new Element::CRectangleElement(xStart,yStart, xEnd,yEnd));
		m_pRectangle->SetEditMode(Element::EEM_ONDRAW);
	}
	else //更新矩形角点坐标
	{	
		m_pRectangle->Update( xStart, yStart, xEnd, yEnd);
	}

	//更新绘制
	pDisplay->SetDrawBuffer(drawEdit);
	pDisplay->DrawBackgroud();
	m_pRectangle->Draw(pDisplay);
	m_pMapCtrl->RefreshScreen();
}

void CActionDrawRectangleElement::LButtonUpEvent (UINT nFlags, CPoint point)
{
	
	
	//若大小为零，则删除该图元
	if(point.x != cPtStart.x || point.y != cPtStart.y)
	{
		m_pMap->GetGraphicLayer()->AddElement(m_pRectangle);
		m_pMap->GetGraphicLayer()->SelectElement(m_pRectangle);	
	}	
	m_pRectangle.reset();

	//更新绘制
	m_pMapCtrl->UpdateContent(otDrawContent(otDrawElement|otDrawEdit));

	IActionDrawElement::LButtonUpEvent(nFlags, point);

	//工具设为选择
	m_pMapCtrl->SetAction(actionSelectElement);
	

}
