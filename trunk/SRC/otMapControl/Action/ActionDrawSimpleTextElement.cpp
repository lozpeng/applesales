#include "stdafx.h"
#include "ActionDrawSimpleTextElement.h"
#include "..\otMapControl.h"
#include "..\otMapCtrl.h"

CActionDrawSimpleTextElement::CActionDrawSimpleTextElement() : IActionDrawElement(actionDrawTextElement)
{
	m_pText.reset();
}

CActionDrawSimpleTextElement::~CActionDrawSimpleTextElement()
{

}

void CActionDrawSimpleTextElement::Init(CotMapCtrl *pMapCtrl,Carto::CMap *pMap)
{
	IActionDrawElement::Init(pMapCtrl,pMap);
}

void CActionDrawSimpleTextElement::LButtonDownEvent (UINT nFlags, CPoint point)
{
	IActionDrawElement::LButtonDownEvent (nFlags, point);

	
	//获取活动地区
	Display::IDisplayPtr pDisplay = m_pMap->GetDisplay();
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
	pGeo = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->toGeometry(&env);
	m_pText.reset(new Element::CSimpleTextElement(*pGeo));

	m_pMap->GetGraphicLayer()->UnselectAllElements();
	m_pMap->GetGraphicLayer()->AddElement(m_pText);
	m_pMap->GetGraphicLayer()->SelectElement(m_pText);	
	
	m_pText.reset();

	//更新绘制
	m_pMapCtrl->UpdateContent(otDrawContent(otDrawElement|otDrawEdit));

}

void CActionDrawSimpleTextElement::MouseMoveEvent (UINT nFlags, CPoint point)
{
}

void CActionDrawSimpleTextElement::LButtonUpEvent (UINT nFlags, CPoint point)
{
	IActionDrawElement::LButtonUpEvent(nFlags, point);

	//工具设为选择
	m_pMapCtrl->SetAction(actionSelectElement);
}
