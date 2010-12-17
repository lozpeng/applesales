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

		//��ȡ���ͼ�ؼ�
		if(!m_pMapCtrl)
			return;

		//��ȡ�����
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

		if(!m_pCircle)//����һ��Բ��ͼԪ
		{
			m_pCircle.reset(new Element::CCircleElement(TemCenter,Radius));
			m_pCircle->SetEditMode(Element::EEM_ONDRAW);
		}
		else //����Բ�ĺͰ뾶
		{	
			m_pCircle->Update(TemCenter, Radius);
		}

		//���»���
		pDisplay->SetDrawBuffer(drawEdit);
		pDisplay->DrawBackgroud();
		m_pCircle->Draw(pDisplay);
		m_pMapCtrl->RefreshScreen();

	}

	void CDrawCircleElementTool::LButtonUpEvent (UINT nFlags, CPoint point)
	{
		if(!m_pMapCtrl)
			return;

		//����СΪ�㣬��ɾ����ͼԪ
		if(point.x != cPtStart.x || point.y != cPtStart.y)
		{
			m_pMapCtrl->GetMap()->GetGraphicLayer()->AddElement(m_pCircle);
			m_pMapCtrl->GetMap()->GetGraphicLayer()->SelectElement(m_pCircle);	
			//������˶�ջ
			//m_pMapCtrl->GetMap()->GetElementOperationStack()->AddOperation(Element::OPT_ADD, m_pCircle);
		}	
		m_pCircle.reset();

		//���»���
		m_pMapCtrl->UpdateControl(drawElement | drawEdit);

		IDrawElementTool::LButtonUpEvent(nFlags, point);

		//������Ϊѡ��
		Framework::ITool* pTool = NULL;
		m_pMapCtrl->SetCurTool("SelectElementTool");

		pTool=Framework::ITool::FindTool("SelectElementTool");
		if(pTool)
		{
			pTool->Initialize(dynamic_cast<Framework::IUIObject*>(m_pMapCtrl));
		}
	}


}

