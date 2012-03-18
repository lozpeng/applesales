#include "stdafx.h"
#include "ActionDrawPolygonElement.h"
#include "..\otMapControl.h"
#include "..\otMapCtrl.h"



CActionDrawPolygonElement::CActionDrawPolygonElement() : IActionDrawElement(actionDrawPolygonElement)
{
	m_pPolygon.reset();
	m_nLastVertixId = 0;
}

CActionDrawPolygonElement::~CActionDrawPolygonElement()
{

}

void CActionDrawPolygonElement::Init(CotMapCtrl *pMapCtrl,Carto::CMap *pMap)
{
	IActionDrawElement::Init(pMapCtrl,pMap);
}

void CActionDrawPolygonElement::LButtonDownEvent (UINT nFlags, CPoint point)
{
	IActionDrawElement::LButtonDownEvent (nFlags, point);

	
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

void CActionDrawPolygonElement::MouseMoveEvent (UINT nFlags, CPoint point)
{
	if(!m_pPolygon)
		return;

	IActionDrawElement::MouseMoveEvent (nFlags, point);

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

void CActionDrawPolygonElement::LButtonUpEvent (UINT nFlags, CPoint point)
{
}

void CActionDrawPolygonElement::LButtonDblClkEvent (UINT nFlags, CPoint point)
{
	if(!m_pPolygon)
		return;

	m_pPolygon->RemoveVertix(m_nLastVertixId);
	m_nLastVertixId--;

	if (m_nLastVertixId >= 2  )
	{
		

		m_pMap->GetGraphicLayer()->AddElement(m_pPolygon);
		m_pMap->GetGraphicLayer()->SelectElement(m_pPolygon);	
	}
	
	m_pPolygon.reset();

	IActionDrawElement::LButtonDblClkEvent(nFlags, point);

	//������Ϊѡ��
	m_pMapCtrl->SetAction(actionSelectElement);
}

