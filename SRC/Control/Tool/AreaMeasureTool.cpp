#include "stdafx.h"
#include "AreaMeasureTool.h"
#include "Control.h"


extern CControlApp theApp;
namespace Control
{
	static CAreaMeasureTool gAreaMeasureTool;

	CAreaMeasureTool::CAreaMeasureTool() : IDrawElementTool("AreaMeasureTool")
	{
		m_pPolygon.reset();
		m_nLastVertixId = 0;
		m_hCursor =NULL;
	}


	CAreaMeasureTool::~CAreaMeasureTool()
	{

	}

	void CAreaMeasureTool::Initialize(Framework::IUIObject *pTargetControl)
	{
		IDrawElementTool::Initialize(pTargetControl);

		//初始化光标
		//if(m_hCursor==NULL)
		{
			m_hCursor =::LoadCursor( theApp.m_hInstance , MAKEINTRESOURCE( IDC_Measure) );
		}


		//获取活动地图控件
		m_pMapCtrl = dynamic_cast<Framework::IMapCtrl*>(pTargetControl);
		if(!m_pMapCtrl)
			return;

		//设置光标类型
		m_pMapCtrl->SetCursor(m_hCursor);

	}
	void CAreaMeasureTool::LButtonDownEvent (UINT nFlags, CPoint point)
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
			m_pPolygon.reset(new Element::CPolygonMeasureElement(coorCur));

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

	void CAreaMeasureTool::MouseMoveEvent (UINT nFlags, CPoint point)
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

	void CAreaMeasureTool::LButtonUpEvent (UINT nFlags, CPoint point)
	{
	}

	void CAreaMeasureTool::LButtonDblClkEvent (UINT nFlags, CPoint point)
	{
		if(!m_pPolygon)
			return;

		m_pPolygon->RemoveVertix(m_nLastVertixId);
		m_nLastVertixId--;

		if (m_nLastVertixId >= 2  )
		{


			m_pMap->GetGraphicLayer()->AddElement(m_pPolygon);
			//m_pMap->GetGraphicLayer()->SelectElement(m_pPolygon);	
		}

		m_pPolygon->bDrawCloseButton = true;
		m_pPolygon.reset();

		
				//更新绘制
		m_pMapCtrl->UpdateControl((DrawContent)(drawElement));

		ReleaseCapture();

		//IDrawElementTool::LButtonDblClkEvent(nFlags, point);

	}
}