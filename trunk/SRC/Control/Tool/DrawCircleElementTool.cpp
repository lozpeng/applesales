#include "StdAfx.h"
#include "DrawCircleElementTool.h"


namespace Control
{
	static CDrawCircleElementTool gDrawCiecleElementTool;


	CDrawCircleElementTool::CDrawCircleElementTool(): IDrawElementTool("DrawCircleElementTool")
	{
		m_pCircle.reset();
	}

	CDrawCircleElementTool::~CDrawCircleElementTool()
	{
	}

	void CDrawCircleElementTool::Initialize(Framework::IUIObject *pTargetControl)
	{
		IDrawElementTool::Initialize(pTargetControl);
	}

	void CDrawCircleElementTool::LButtonDownEvent (UINT nFlags, CPoint point)
	{
		IDrawElementTool::LButtonDownEvent (nFlags, point);
	}

	void CDrawCircleElementTool::MouseMoveEvent (UINT nFlags, CPoint point)
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

		GEOMETRY::geom::Coordinate TemCenter;
		TemCenter.x=xStart;
		TemCenter.y=yStart;
		double Radius=sqrt((xEnd - xStart) * (xEnd - xStart) + (yEnd - yStart) * (yEnd - yStart));

		if(!m_pCircle)//创建一个圆形图元
		{
			m_pCircle.reset(new Element::CCircleElement(TemCenter,Radius));
			m_pCircle->SetEditMode(Element::EEM_ONDRAW);
		}
		else //更新圆心和半径
		{	
			m_pCircle->Update(TemCenter, Radius);
		}

		//更新绘制
		pDisplay->SetDrawBuffer(drawEdit);
		pDisplay->DrawBackgroud();
		m_pCircle->Draw(pDisplay);
		m_pMapCtrl->RefreshScreen();

	}

	void CDrawCircleElementTool::LButtonUpEvent (UINT nFlags, CPoint point)
	{
		if(!m_pMapCtrl)
			return;

		//若大小为零，则删除该图元
		if(point.x != cPtStart.x || point.y != cPtStart.y)
		{
			m_pMapCtrl->GetMap()->GetGraphicLayer()->AddElement(m_pCircle);
			m_pMapCtrl->GetMap()->GetGraphicLayer()->SelectElement(m_pCircle);	
			//加入回退堆栈
			//m_pMapCtrl->GetMap()->GetElementOperationStack()->AddOperation(Element::OPT_ADD, m_pCircle);
		}	
		m_pCircle.reset();

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

