#include "stdafx.h"
#include <Math.h>
#include "ActionSelByCircle.h"
#include "../otMapControl.h"
#include "../otMapCtrl.h"
#include "SpatialQuery.h"
#include "SymbolFactory.h"
#include "SimpleMarkerSymbol.h"
#include "SimpleLineSymbol.h"
#include "ISymbol.h"
#include <geometry/geom/CircularArc.h>
#include <geometry/geom/Circle.h>


CActionSelByCircle::CActionSelByCircle() : ISelectFeatureTool(actionSelectByCircle)
{
	RegisterAction(actionSelectByCircle,this);
}

CActionSelByCircle::~CActionSelByCircle()
{

}

void CActionSelByCircle::Init(CotMapCtrl *pMapCtrl,Carto::CMap *pMap)
{
	ISelectFeatureTool::Init(pMapCtrl,pMap); 

    m_bStartDraw = false;


}



void CActionSelByCircle::LButtonDownEvent(UINT nFlags, CPoint point)
{
	m_centralPt = point;

	//��ʼ��Բ
	m_bStartDraw = true;
}

void CActionSelByCircle::ActionDraw()
{

	//��ȡ���ͼ�ؼ�
	

	//������ʾ
	Display::IDisplayPtr dispaly = m_pMap->GetDisplay();
	dispaly->SetDrawBuffer(drawEdit);
	dispaly->DrawBackgroud();
	
	//����Բ
	double dRadius = ::sqrt((double)((m_centralPt.x - m_endPt.x) * (m_centralPt.x - m_endPt.x)) 
		+ (double)((m_centralPt.y - m_endPt.y) * (m_centralPt.y - m_endPt.y)));
	
	INT_POINT pCentralPt;
	pCentralPt.x = m_centralPt.x;
	pCentralPt.y = m_centralPt.y;

	DIS_CIRCLE *pCirlce;
	CreateDisplayCircle(pCirlce);
	pCirlce->center = pCentralPt;
	pCirlce->Radio = dRadius;

	//����Բ
	Display::CDC *pDC =dispaly->GetDrawDC();

	LINE_STYLE pLineStyle;
	pLineStyle.lColor = RGB(0, 0, 0);
	pLineStyle.lWidth = 0.6f;
	pLineStyle.eStyle = SOLID;
	DISPLAY_HANDLE pnewPen = pDC->CreatePen(pLineStyle);
	
	DISPLAY_HANDLE pold = pDC->SelectObject(pnewPen);
	
	pDC->DrawCircle(*pCirlce);

	delete pCirlce;
	pCirlce = NULL;
	
	pDC->SelectObject(pold);
	pDC->RemoveHandle(pnewPen);

	m_pMapCtrl->RefreshScreen();
}

void CActionSelByCircle::MouseMoveEvent(UINT nFlags, CPoint point)
{
	m_endPt = point;

	//��ͼ
	if (m_bStartDraw)
	{
		ActionDraw();
	}
}

void CActionSelByCircle::LButtonUpEvent(UINT nFlags, CPoint point)
{	
	//*-----------------ѡ��Ҫ��----------------------------*//
	

	//����Բ
	GEOMETRY::geom::Coordinate coordcentral;
	m_pMap->GetDisplay()->GetDisplayTransformation().ConvertDisplayToGeo(m_centralPt.x, m_centralPt.y, coordcentral);
	
	GEOMETRY::geom::Coordinate coordend;
	m_pMap->GetDisplay()->GetDisplayTransformation().ConvertDisplayToGeo(point.x, point.y, coordend);

	double dRadius;
	dRadius = sqrt((coordend.x - coordcentral.x) * (coordend.x - coordcentral.x) + (coordend.y - coordcentral.y) * (coordend.y - coordcentral.y));
	
	GEOMETRY::geom::Geometry  *pCircle = new Circle(coordcentral, dRadius);

	//����һ���ռ��ѯ����
	Geodatabase::CSpatialQuery queryfilter;
	queryfilter.SetGeometry(pCircle);
	queryfilter.SetSpatialRel(Geodatabase::SpatialRelIntersects);

	ISelectFeatureTool::Select(&queryfilter);

	//*-----------------Բ��Ϊ��----------------------------*//
	//delete pCircle;
	pCircle = NULL;
	m_centralPt = m_endPt;
	
	if (m_bStartDraw)
	{
		ActionDraw();
	}

	//ֹͣ��Բ
	m_bStartDraw = false;
}


