#include "stdafx.h"
#include "DrawEllipseElementTool.h"

namespace Control
{

	static CDrawEllipseElementTool gDrawEllipseElementTool;

	CDrawEllipseElementTool::CDrawEllipseElementTool() : IDrawElementTool("DrawEllipseElementTool")
	{
		m_pEllipse.reset();
	}

	CDrawEllipseElementTool::~CDrawEllipseElementTool()
	{

	}

	void CDrawEllipseElementTool::Initialize(Framework::IUIObject *pTargetControl)
	{
		IDrawElementTool::Initialize(pTargetControl);
	}

	void CDrawEllipseElementTool::LButtonDownEvent (UINT nFlags, CPoint point)
	{
		IDrawElementTool::LButtonDownEvent (nFlags, point);
	}

	void CDrawEllipseElementTool::MouseMoveEvent (UINT nFlags, CPoint point)
	{
		IDrawElementTool::MouseMoveEvent (nFlags, point);

		if(!(nFlags&MK_LBUTTON)) 
			return;

		if(point.x == cPtStart.x || point.y == cPtStart.y)
			return;

		//获取活动地图控件
		if(!m_pMapCtrl)
			return;

		//获取活动地区
		Display::IDisplayPtr pDisplay = m_pMapCtrl->GetMap()->GetDisplay();
		if(!pDisplay)
			return;

		//displaytoGeo
		double xStart,yStart, xEnd,yEnd;
		pDisplay->GetDisplayTransformation().ConvertDisplayToGeo(cPtStart.x, cPtStart.y, xStart, yStart);
		pDisplay->GetDisplayTransformation().ConvertDisplayToGeo(cPtEnd.x, cPtEnd.y, xEnd, yEnd);


		if(!m_pEllipse)//创建一个矩形图元
		{
			m_pEllipse.reset(new Element::CEllipseElement(GEOMETRY::geom::Envelope(xStart, xEnd, yStart, yEnd)));
			m_pEllipse->SetEditMode(Element::EEM_ONDRAW);
		}
		else //更新矩形角点坐标
		{	
			m_pEllipse->Update( GEOMETRY::geom::Envelope(xStart, xEnd,yStart , yEnd));
		}

		//更新绘制
		pDisplay->SetDrawBuffer(drawEdit);
		pDisplay->DrawBackgroud();
		m_pEllipse->Draw(pDisplay);
		m_pMapCtrl->RefreshScreen();
	}

	void CDrawEllipseElementTool::LButtonUpEvent (UINT nFlags, CPoint point)
	{

		if(!m_pMapCtrl)
			return;

		//若大小为零，则删除该图元
		if(point.x != cPtStart.x || point.y != cPtStart.y)
		{
			m_pMapCtrl->GetMap()->GetGraphicLayer()->AddElement(m_pEllipse);
			m_pMapCtrl->GetMap()->GetGraphicLayer()->SelectElement(m_pEllipse);	
			//加入回退堆栈
			//m_pMapCtrl->GetMap()->GetElementOperationStack()->AddOperation(Element::OPT_ADD, m_pEllipse);
		}	
		m_pEllipse.reset();

		//更新绘制
		m_pMapCtrl->UpdateControl(drawElement | drawEdit);

		IDrawElementTool::LButtonUpEvent(nFlags, point);

		//工具设为选择
		Framework::ITool* pTool = NULL;
		m_pMapCtrl->SetCurTool("SelectElementTool");

		pTool=Framework::ITool::FindTool("SelectElementTool");
		if(pTool)
		{
			pTool->Initialize(dynamic_cast<Framework::IUIObject*>(m_pMapCtrl));
		}

	}
}