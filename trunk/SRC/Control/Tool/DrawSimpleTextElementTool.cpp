#include "stdafx.h"
#include "DrawSimpleTextElementTool.h"

static CDrawSimpleTextElementTool gDrawSimpleTextTool;

CDrawSimpleTextElementTool::CDrawSimpleTextElementTool() : IDrawElementTool("DrawTextElementTool")
{
	m_pText.reset();
}

CDrawSimpleTextElementTool::~CDrawSimpleTextElementTool()
{

}

void CDrawSimpleTextElementTool::Initialize(Framework::IUIObject *pTargetControl)
{
	IDrawElementTool::Initialize(pTargetControl);
}

void CDrawSimpleTextElementTool::LButtonDownEvent (UINT nFlags, CPoint point)
{
	IDrawElementTool::LButtonDownEvent (nFlags, point);

	
	//��ȡ�����
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

	//���»���
	m_pMapCtrl->UpdateControl(DrawContent(drawElement|drawEdit));

}

void CDrawSimpleTextElementTool::MouseMoveEvent (UINT nFlags, CPoint point)
{
}

void CDrawSimpleTextElementTool::LButtonUpEvent (UINT nFlags, CPoint point)
{
	IDrawElementTool::LButtonUpEvent(nFlags, point);
}
