#include "stdafx.h"
#include "DrawPolygonElementTool.h"

namespace Control
{

	static CDrawPolygonElementTool gDrawPolygonTool;

	CDrawPolygonElementTool::CDrawPolygonElementTool() : IDrawElementTool("DrawPolygonElementTool")
	{
		m_pPolygon.reset();
		m_nLastVertixId = 0;
	}

	CDrawPolygonElementTool::~CDrawPolygonElementTool()
	{

	}

	void CDrawPolygonElementTool::Initialize(Framework::IUIObject *pTargetControl)
	{
		IDrawElementTool::Initialize(pTargetControl);
	}
	void CDrawPolygonElementTool::LButtonDownEvent (UINT nFlags, CPoint point)
	{
		IDrawElementTool::LButtonDownEvent (nFlags, point);


		//��ȡ�����
		Display::IDisplayPtr pDisplay = m_pMap->GetDisplay();
		if(!pDisplay)
			return;


		//displaytoGeo
		GEOMETRY::geom::Coordinate coorCur;
		pDisplay->GetDisplayTransformation().ConvertDisplayToGeo(cPtStart.x, cPtStart.y, coorCur);

		if(!m_pPolygon)//����һ������ͼԪ
		{
			m_pPolygon.reset(new Element::CPolygonElement(coorCur));

			m_pPolygon->SetEditMode(Element::EEM_ONDRAW);

			m_nLastVertixId = 1;
		}
		else //���¾��νǵ�����
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

	void CDrawPolygonElementTool::MouseMoveEvent (UINT nFlags, CPoint point)
	{
		if(!m_pPolygon)
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

		m_pPolygon->MoveVertixTo( m_nLastVertixId, coorCur);

		//���»���
		pDisplay->SetDrawBuffer(drawEdit);
		pDisplay->DrawBackgroud();
		m_pPolygon->Draw(pDisplay);
		m_pMapCtrl->RefreshScreen();
	}

	void CDrawPolygonElementTool::LButtonUpEvent (UINT nFlags, CPoint point)
	{
	}

	void CDrawPolygonElementTool::LButtonDblClkEvent (UINT nFlags, CPoint point)
	{
		if(!m_pPolygon)
			return;

		m_pPolygon->RemoveVertix(m_nLastVertixId);
		m_nLastVertixId--;

		if (m_nLastVertixId >= 2  )
		{


			m_pMap->GetGraphicLayer()->AddElement(m_pPolygon);
			m_pMap->GetGraphicLayer()->SelectElement(m_pPolygon);
			//��ʾ���
			Framework::IStatusInfo *pSinfo=m_pMapCtrl->GetStatusInfo();
			if(pSinfo)
			{
				double area=m_pPolygon->GetGeometry()->getArea();
				area*=(111000.0*111000.0);
				std::ostringstream os;
				os<<"���:"<<area<<"ƽ���� ";

				pSinfo->UpdateInfo(os.str());
			}
		}

		m_pPolygon.reset();

		IDrawElementTool::LButtonDblClkEvent(nFlags, point);

	}

}