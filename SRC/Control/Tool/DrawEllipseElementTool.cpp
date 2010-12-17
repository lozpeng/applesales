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


		if(!m_pEllipse)//����һ������ͼԪ
		{
			m_pEllipse.reset(new Element::CEllipseElement(GEOMETRY::geom::Envelope(xStart, xEnd, yStart, yEnd)));
			m_pEllipse->SetEditMode(Element::EEM_ONDRAW);
		}
		else //���¾��νǵ�����
		{	
			m_pEllipse->Update( GEOMETRY::geom::Envelope(xStart, xEnd,yStart , yEnd));
		}

		//���»���
		pDisplay->SetDrawBuffer(drawEdit);
		pDisplay->DrawBackgroud();
		m_pEllipse->Draw(pDisplay);
		m_pMapCtrl->RefreshScreen();
	}

	void CDrawEllipseElementTool::LButtonUpEvent (UINT nFlags, CPoint point)
	{

		if(!m_pMapCtrl)
			return;

		//����СΪ�㣬��ɾ����ͼԪ
		if(point.x != cPtStart.x || point.y != cPtStart.y)
		{
			m_pMapCtrl->GetMap()->GetGraphicLayer()->AddElement(m_pEllipse);
			m_pMapCtrl->GetMap()->GetGraphicLayer()->SelectElement(m_pEllipse);	
			//������˶�ջ
			//m_pMapCtrl->GetMap()->GetElementOperationStack()->AddOperation(Element::OPT_ADD, m_pEllipse);
		}	
		m_pEllipse.reset();

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