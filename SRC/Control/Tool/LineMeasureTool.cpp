#include "stdafx.h"
#include "LineMeasureTool.h"
#include "Control.h"


extern CControlApp theApp;
namespace Control
{
	static CLineMeasureTool gLineMeasureTool;

	CLineMeasureTool::CLineMeasureTool() : IDrawElementTool("LineMeasureTool")
	{
		m_pPolyline.reset();
		m_nLastVertixId = 0;
	}


	CLineMeasureTool::~CLineMeasureTool()
	{

	}

	void CLineMeasureTool::Initialize(Framework::IUIObject *pTargetControl)
	{
		IDrawElementTool::Initialize(pTargetControl);
	}
	void CLineMeasureTool::LButtonDownEvent (UINT nFlags, CPoint point)
	{
		IDrawElementTool::LButtonDownEvent (nFlags, point);



		//��ȡ�����
		Display::IDisplayPtr pDisplay = m_pMap->GetDisplay();
		if(!pDisplay)
			return;

		//displaytoGeo
		GEOMETRY::geom::Coordinate coorCur;
		pDisplay->GetDisplayTransformation().ConvertDisplayToGeo(cPtStart.x, cPtStart.y, coorCur);

		if(!m_pPolyline)//����һ������ͼԪ
		{
			m_pPolyline.reset(new Element::CPolylineMeasureElement(coorCur));

			m_pPolyline->SetEditMode(Element::EEM_ONDRAW);

			m_nLastVertixId = 1;
		}
		else //���¾��νǵ�����
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

	void CLineMeasureTool::MouseMoveEvent (UINT nFlags, CPoint point)
	{
		if(!m_pPolyline)
			return;

		IDrawElementTool::MouseMoveEvent (nFlags, point);

		if(point.x == cPtStart.x || point.y == cPtStart.y)
			return;


		//��ȡ�����
		Display::IDisplayPtr pDisplay = m_pMap->GetDisplay();
		if(!pDisplay)
			return;

		//displaytoGeo
		GEOMETRY::geom::Coordinate coorCur;
		pDisplay->GetDisplayTransformation().ConvertDisplayToGeo(point.x, point.y, coorCur);

		m_pPolyline->MoveVertixTo( m_nLastVertixId, coorCur);

		//���»���
		pDisplay->SetDrawBuffer(drawEdit);
		pDisplay->DrawBackgroud();
		m_pPolyline->Draw(pDisplay);
		m_pMapCtrl->RefreshScreen();
	}

	void CLineMeasureTool::LButtonUpEvent (UINT nFlags, CPoint point)
	{
	}

	void CLineMeasureTool::LButtonDblClkEvent (UINT nFlags, CPoint point)
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

				//���»���
		m_pMapCtrl->UpdateControl((DrawContent)(drawElement));

		ReleaseCapture();

		//IDrawElementTool::LButtonDblClkEvent(nFlags, point);

	}
}