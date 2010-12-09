#include "StdAfx.h"
#include "PageGrid.h"
#include "SymbolFactory.h"

namespace Element{

CPageGrid::CPageGrid()
{
	m_XInterval = 1;
	m_YInterval = 1;

	m_bGridDirty = TRUE;

	m_bGridVisibility = FALSE;

	Display::CSimpleLineSymbol* pLineSym = new Display::CSimpleLineSymbol;
	pLineSym->SetLineColor(RGB(110,110,110));
	pLineSym->SetLineStyle(DOT);
	m_pGridLineSymbol.reset(pLineSym);

	m_pLines = NULL;
}

CPageGrid::~CPageGrid(void)
{
}

void CPageGrid::serialization(SYSTEM::IArchive &ar)
{
	SYSTEM::ISerialization::serialization(ar);

	ar & m_bGridVisibility;

	ar & m_XInterval;

	ar & m_YInterval;

	if(ar.IsRead())
	{
		long minx, maxx, miny, maxy;

		ar & minx;

		ar & maxx;

		ar & miny;

		ar & maxy;

		m_GridEnvelope.init(minx, maxx, miny, maxy);

		m_pGridLineSymbol = Display::CSymbolFactory::CreateSymbolFromStream(ar);
	}
	else
	{
		long minx, maxx, miny, maxy;
		minx = m_GridEnvelope.getMinX();
		maxx = m_GridEnvelope.getMaxX();
		miny = m_GridEnvelope.getMinY();
		maxy = m_GridEnvelope.getMaxY();

		ar & minx;

		ar & maxx;

		ar & miny;

		ar & maxy;

		m_pGridLineSymbol->serialization(ar);
	}
	
}

//grid
void CPageGrid::SetGridVisibility(BOOL bVisible)
{
	m_bGridVisibility = bVisible;
}
BOOL CPageGrid::GetGridVisibility()
{
	return m_bGridVisibility;
}

void CPageGrid::SetXInterval(double XInter)
{
	m_XInterval = XInter;
	m_bGridDirty = TRUE;
}
double CPageGrid::GetXInterval()
{
	return m_XInterval;
}

void CPageGrid::SetYInterval(double XInter)
{
	m_YInterval = XInter;
	m_bGridDirty = TRUE;
}
double CPageGrid::GetYInterval()
{
	return m_YInterval;
}

void CPageGrid::SetEnvelope(GEOMETRY::geom::Envelope GridEnvelope)
{
	m_GridEnvelope = GridEnvelope;
	m_bGridDirty = TRUE;
}

void CPageGrid::Draw(Display::IDisplayPtr pDisplay)
{
	DrawGrid(pDisplay);
}

void CPageGrid::DrawGrid(Display::IDisplayPtr pDisplay)
{
	if(m_bGridDirty && m_bGridVisibility)
	{	
		CalcGridLines(m_GridEnvelope, m_XInterval, m_YInterval, m_pLines);
		m_bGridDirty = FALSE;

	}

	if(!m_bGridVisibility)
		return;

	pDisplay->SetSymbol(m_pGridLineSymbol.get());

	pDisplay->Begin();

	pDisplay->Draw(m_pLines);

	pDisplay->End();
}

void CPageGrid::CalcGridLines(GEOMETRY::geom::Envelope GridEnvelope, double XInterval, double YInterval, GEOMETRY::geom::Geometry*&	pLines)
{
	int nVerLineNum = (int)(GridEnvelope.getWidth()/XInterval)+1;
	int nHorLineNum = (int)(GridEnvelope.getHeight()/YInterval)+1;

	std::vector<GEOMETRY::geom::Geometry*> vecLines;
	GEOMETRY::geom::Geometry* pLine = NULL;
	GEOMETRY::geom::CoordinateSequence* coords = NULL;
	GEOMETRY::geom::Coordinate coordStart, coordEnd;

	if(pLines)
	{
		GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(pLines);
		pLines = NULL;
	}
	pLines =(Geometry*)GeometryFactory::getDefaultInstance()->createMultiLineString();

	//pVerticalLines
	for(int i=0; i<nVerLineNum; i++)
	{		
		//网格线（单位：制图页面坐标）
		coordStart.x = GridEnvelope.getMinX() + XInterval*i;
		coordStart.y = GridEnvelope.getMinY();
		coordEnd.x = GridEnvelope.getMinX() + XInterval*i;
		coordEnd.y = GridEnvelope.getMaxY();

		coords = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->getCoordinateSequenceFactory()->create(NULL);
		coords->add(coordStart);
		coords->add(coordEnd);

		pLine = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->createLineString(coords);
		((MultiLineString*)pLines)->AddGeometry(pLine);
	}


	//pHorizontalLines
	for(int i=0; i<nHorLineNum; i++)
	{
		//网格线（单位：制图页面坐标）
		coordStart.x = GridEnvelope.getMinX();
		coordStart.y = GridEnvelope.getMinY() + YInterval*i;
		coordEnd.x = GridEnvelope.getMaxX();
		coordEnd.y = GridEnvelope.getMinY() + YInterval*i;

		coords = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->getCoordinateSequenceFactory()->create(NULL);
		coords->add(coordStart);
		coords->add(coordEnd);

		pLine = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->createLineString(coords);
		((MultiLineString*)pLines)->AddGeometry(pLine);
	}

	////生成多线几何图形
	//if(pLines)
	//{
	//	GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(pLines);
	//	pLines = NULL;
	//}

	//if(vecLines.size()>0)
	//	pLines = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->createMultiLineString(vecLines);
}


}