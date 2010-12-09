#include "StdAfx.h"
#include "CalloutTracker.h"
#include "SimpleLineSymbol.h"

namespace Element{

CCalloutTracker::CCalloutTracker()
{
	m_handleType = HT_ONE;

	//³õÊ¼»¯±ß¿ò·ûºÅ
	Display::CSimpleLineSymbol* pLineSymbol = dynamic_cast<Display::CSimpleLineSymbol*>(m_pFillSymbol->GetOutLineSymbol().get());
	pLineSymbol->SetLineStyle(DOT);
	m_pFillSymbol->SetDrawFill(FALSE);
	m_pFillSymbol->SetOutLineColor(RGB(0,255,255));


	m_pMarkerSymbol->SetOutLineColor(RGB(0,0,0));
	m_pMarkerSymbol->SetMarkerColor(RGB(0,255,255));
	m_pMarkerSymbol->SetMarkerType(SIMPLE_MARKER_SQUARE);
	m_pMarkerSymbol->SetMarkerSize(1.5);
}

CCalloutTracker::CCalloutTracker(const GEOMETRY::geom::Geometry& geometry)
{
	m_handleType = HT_ONE;

	SetGeometry(geometry);

	//³õÊ¼»¯±ß¿ò·ûºÅ
	Display::CSimpleLineSymbol* pLineSymbol = dynamic_cast<Display::CSimpleLineSymbol*>(m_pFillSymbol->GetOutLineSymbol().get());
	pLineSymbol->SetLineStyle(DOT);
	m_pFillSymbol->SetDrawFill(FALSE);
	m_pFillSymbol->SetOutLineColor(RGB(0,255,255));


	m_pMarkerSymbol->SetOutLineColor(RGB(0,0,0));
	m_pMarkerSymbol->SetMarkerColor(RGB(0,255,255));
	m_pMarkerSymbol->SetMarkerType(SIMPLE_MARKER_SQUARE);
	m_pMarkerSymbol->SetMarkerSize(1.5);
}

CCalloutTracker::~CCalloutTracker(void)
{
	if(m_pHandlePoints)
	{
		GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(m_pHandlePoints);
		m_pHandlePoints = NULL;
	}

}

void CCalloutTracker::SetGeometry(const GEOMETRY::geom::Geometry& geometry)
{
	ISelectionTracker::SetGeometry(geometry);
}

void CCalloutTracker::SetHandle(const GEOMETRY::geom::Coordinate& handle)
{
	if(m_pHandlePoints)
	{
		GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(m_pHandlePoints);
		m_pHandlePoints = NULL;
	}

	m_pHandlePoints = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->createPoint(handle);
}


HIT_HANDLE CCalloutTracker::HitTest ( GEOMETRY::geom::Coordinate coord, double dbTolerance)
{
	double dbSearchDis = 0;
	HIT_HANDLE nHandle = HH_HIT_NONE;

	long lPartIndex=-1, lVertixIndex=-1;
	GEOMETRY::geom::Coordinate coordOut;
	m_pHandlePoints->SnapVertex(&coord, dbTolerance, &coordOut, &dbSearchDis, &lPartIndex, &lVertixIndex);

	if(lPartIndex == -1)
	{
		GEOMETRY::geom::Geometry *pPt = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->createPoint(coord);
		GEOMETRY::geom::Geometry* pBufferGeo = m_pGeometry->buffer(dbTolerance);
		if(pBufferGeo->covers(pPt))
			nHandle = HH_HIT_INTERIOR;

		GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(pBufferGeo);
		GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(pPt);
	}
	else
	{
		nHandle = HH_HIT_ONE;
	}

	return nHandle;
}

void CCalloutTracker::MoveHandleTo(HIT_HANDLE nHandle,GEOMETRY::geom::Coordinate coord)
{
	SetHandle(coord);
}	

}
