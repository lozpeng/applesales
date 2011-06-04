#include "StdAfx.h"
#include "DitillTool.h"

namespace Control
{
	static CDitillTool distillTool;

	CDitillTool::CDitillTool(void): IDrawElementTool("DiTillTool")
	{
		m_pPolygon.reset();
		m_nLastVertixId = 0;
	}
	CDitillTool::~CDitillTool(void)
	{
	}
	void CDitillTool::Initialize(Framework::IUIObject *pTargetControl)
	{
		IDrawElementTool::Initialize(pTargetControl);
	}
	void CDitillTool::LButtonDownEvent (UINT nFlags, CPoint point)
	{
		IDrawElementTool::LButtonDownEvent (nFlags, point);


		//获取活动地区
		Display::IDisplayPtr pDisplay = m_pMap->GetDisplay();
		if(!pDisplay)
			return;


		//displaytoGeo
		GEOMETRY::geom::Coordinate coorCur;
		pDisplay->GetDisplayTransformation().ConvertDisplayToGeo(cPtStart.x, cPtStart.y, coorCur);

		if(!m_pPolygon)//创建一个矩形图元
		{
			m_pPolygon.reset(new Element::CPolygonElement(coorCur));

			m_pPolygon->SetEditMode(Element::EEM_ONDRAW);

			m_nLastVertixId = 1;
		}
		else //更新矩形角点坐标
		{	
			if(m_nLastVertixId==1)
			{
				m_pPolygon->MoveVertixTo( m_nLastVertixId, coorCur);	
				m_nLastVertixId++;
			}
			else if(m_nLastVertixId==2)
			{
				m_pPolygon->MoveVertixTo( m_nLastVertixId, coorCur);
				m_pPolygon->AddVertix( coorCur);
				m_nLastVertixId++;
			}
			else
			{
				m_pPolygon->AddVertix( coorCur);
				m_nLastVertixId++;
			}
		}
	}

	void CDitillTool::MouseMoveEvent (UINT nFlags, CPoint point)
	{
		if(!m_pPolygon)
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

		m_pPolygon->MoveVertixTo( m_nLastVertixId, coorCur);

		//更新绘制
		pDisplay->SetDrawBuffer(drawEdit);
		pDisplay->DrawBackgroud();
		m_pPolygon->Draw(pDisplay);
		m_pMapCtrl->RefreshScreen();
	}

	void CDitillTool::LButtonUpEvent (UINT nFlags, CPoint point)
	{
	}

	void CDitillTool::LButtonDblClkEvent (UINT nFlags, CPoint point)
	{
		if(!m_pPolygon)
			return;

		m_pPolygon->RemoveVertix(m_nLastVertixId);
		m_nLastVertixId--;

		if (m_nLastVertixId >= 2  )
		{
			m_pPolygon->SetUserdata(2);
			m_pMap->GetGraphicLayer()->AddElement(m_pPolygon);
			//设置符号
			Display::CSimpleFillSymbolPtr pFillSymbol =m_pPolygon->GetSymbol();
			pFillSymbol->SetDrawFill(false);
			pFillSymbol->SetOutLineWidth(1);
			pFillSymbol->SetOutLineColor(RGB(0,255,0));

			//m_pMap->GetGraphicLayer()->SelectElement(m_pPolygon);	
		}

		m_pPolygon.reset();

		IDrawElementTool::LButtonDblClkEvent(nFlags, point);

	}
}

