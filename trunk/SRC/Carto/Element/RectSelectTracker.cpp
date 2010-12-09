#include "StdAfx.h"
#include "RectSelectTracker.h"
#include "SimpleLineSymbol.h"

namespace Element{
	CRectSelectTracker::CRectSelectTracker():ISelectionTracker()
{
	m_startPt = m_EndPt = GEOMETRY::geom::Coordinate(0,0);
	m_pGeometry = NULL;

	//³õÊ¼»¯±ß¿ò·ûºÅ
	Display::CSimpleLineSymbol* pLineSymbol = dynamic_cast<Display::CSimpleLineSymbol*>(m_pFillSymbol->GetOutLineSymbol().get());
	pLineSymbol->SetLineStyle(DOT);
	m_pFillSymbol->SetDrawFill(FALSE);
	m_pFillSymbol->SetOutLineColor(RGB(0,0,0));
}

CRectSelectTracker::~CRectSelectTracker(void)
{
}

void CRectSelectTracker::Reset()
{
	if(m_pGeometry)
	{
		GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(m_pGeometry);
		m_pGeometry = NULL;
	}

	m_startPt = m_EndPt = GEOMETRY::geom::Coordinate(0,0);
}

void CRectSelectTracker::Init(const GEOMETRY::geom::Coordinate& startPt)
{
	m_startPt = m_EndPt = startPt;

	UpdateRect(GEOMETRY::geom::Envelope(m_startPt, m_EndPt));
	
}



void CRectSelectTracker::Update(const GEOMETRY::geom::Coordinate& EndPt)
{
	m_EndPt = EndPt;

	UpdateRect(GEOMETRY::geom::Envelope(m_startPt, m_EndPt));
}


GEOMETRY::geom::Geometry* CRectSelectTracker::GetGeometry()
{
	if(abs(m_startPt.x - m_EndPt.x)< 0.000002 && abs(m_startPt.y - m_EndPt.y)< 0.000002)
	{
		return GEOMETRY::geom::GeometryFactory::getDefaultInstance()->createPoint(GEOMETRY::geom::Coordinate(m_startPt.x,m_startPt.y));
	}
	else
	{
		return m_pGeometry;
	}
}

//////////////////////////////////////////////////////////////////////////
void CRectSelectTracker::UpdateRect(GEOMETRY::geom::Envelope envlope)
{
	if(envlope.getHeight()==0) 
	{
		envlope.expandBy(0, 0.000001);
	}
	else if(envlope.getWidth()==0)
	{
		envlope.expandBy(0.000001, 0);
	}

	if(m_pGeometry)
	{
		GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(m_pGeometry);
		m_pGeometry = NULL;
	}
	//³õÊ¼»¯±ß¿ò
	m_pGeometry = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->toGeometry(&envlope);
}

}
