#include "stdafx.h"
#include "DrawRectangleElementTool.h"
#include "MapControl.h"

namespace Control
{

	static CDrawRectangleElementTool gDrawRectTool;

	CDrawRectangleElementTool::CDrawRectangleElementTool() : IDrawElementTool("DrawRectElementTool")
	{
		m_pRectangle.reset();
	}

	CDrawRectangleElementTool::~CDrawRectangleElementTool()
	{

	}

	void CDrawRectangleElementTool::Initialize(Framework::IUIObject *pTargetControl)
	{
		IDrawElementTool::Initialize(pTargetControl);
	}

	void CDrawRectangleElementTool::LButtonDownEvent (UINT nFlags, CPoint point)
	{
		IDrawElementTool::LButtonDownEvent (nFlags, point);
	}

	void CDrawRectangleElementTool::MouseMoveEvent (UINT nFlags, CPoint point)
	{
		IDrawElementTool::MouseMoveEvent (nFlags, point);

		if(!(nFlags&MK_LBUTTON)) 
			return;

		if(point.x == cPtStart.x || point.y == cPtStart.y)
			return;


		if(!m_pMapCtrl)
			return;

		//��ȡ�����
		Display::IDisplayPtr pDisplay = m_pMap->GetDisplay();
		if(!pDisplay)
			return;

		//displaytoGeo
		double xStart,yStart, xEnd,yEnd;
		pDisplay->GetDisplayTransformation().ConvertDisplayToGeo(cPtStart.x, cPtStart.y, xStart, yStart);
		pDisplay->GetDisplayTransformation().ConvertDisplayToGeo(cPtEnd.x, cPtEnd.y, xEnd, yEnd);


		if(!m_pRectangle)//����һ������ͼԪ
		{
			m_pRectangle.reset(new Element::CRectangleElement(xStart,yStart, xEnd,yEnd));
			m_pRectangle->SetEditMode(Element::EEM_ONDRAW);
		}
		else //���¾��νǵ�����
		{	
			m_pRectangle->Update( xStart, yStart, xEnd, yEnd);
		}

		//���»���
		pDisplay->SetDrawBuffer(drawEdit);
		pDisplay->DrawBackgroud();
		m_pRectangle->Draw(pDisplay);
		m_pMapCtrl->RefreshScreen();
	}

	void CDrawRectangleElementTool::LButtonUpEvent (UINT nFlags, CPoint point)
	{

		if(!m_pMapCtrl)
			return;

		//����СΪ�㣬��ɾ����ͼԪ
		if(point.x != cPtStart.x || point.y != cPtStart.y)
		{
			m_pMap->GetGraphicLayer()->AddElement(m_pRectangle);
			m_pMap->GetGraphicLayer()->SelectElement(m_pRectangle);	
		}	
		m_pRectangle.reset();

		//���»���
		m_pMapCtrl->UpdateControl(DrawContent(drawElement|drawEdit));

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