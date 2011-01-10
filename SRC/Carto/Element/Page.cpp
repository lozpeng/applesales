#include "StdAfx.h"
#include "Page.h"
#include "SimpleLineSymbol.h"

namespace Element{

CPage::CPage(void)
{
	m_nPrintPageNumX=1;
	m_nPrintPageNumY=1;

	m_pageInfo.bStandardPage = TRUE;
	m_pageInfo.name = "A4 Rotate";
	m_pageInfo.width = m_dbOnePrintPageWidth = 210;
	m_pageInfo.height = m_dbOnePrintPageHeight = 297;

	m_PageEnvelope = GEOMETRY::geom::Envelope(0,m_dbOnePrintPageWidth*m_nPrintPageNumX, 0,m_dbOnePrintPageHeight*m_nPrintPageNumY);//mm
	
	m_bOrientation = FALSE;
	Init();
}

CPage::CPage(int nPrintPageNumX, int nPrintPageNumY, double dbOnePrintPageWidth, double dbOnePrintPageHeight)
{
	m_nPrintPageNumX=nPrintPageNumX;
	m_nPrintPageNumY=nPrintPageNumY;

	m_pageInfo.bStandardPage = FALSE;
	m_pageInfo.name = "";
	m_pageInfo.width = m_dbOnePrintPageWidth = dbOnePrintPageWidth;
	m_pageInfo.height = m_dbOnePrintPageHeight = dbOnePrintPageHeight;
	m_PageEnvelope = GEOMETRY::geom::Envelope(0,m_dbOnePrintPageWidth*m_nPrintPageNumX, 0,m_dbOnePrintPageHeight*m_nPrintPageNumY);//mm

	m_bOrientation = FALSE;

	Init();
}

CPage::~CPage(void)
{
	if(m_pGeometry)
	{
		GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(m_pGeometry);
		m_pGeometry =NULL;
	}
}

void CPage::serialization(SYSTEM::IArchive& ar)
{
	IFrameProperty::serialization(ar);

	ar & m_pageInfo.bStandardPage;

	ar & m_pageInfo.name;

	ar & m_pageInfo.width;

	ar & m_pageInfo.height;

	ar & m_nPrintPageNumX;

	ar & m_nPrintPageNumY;

	ar & m_dbMargin;

	ar & m_bOrientation;

	ar & m_bPrintAreaVisible;

	ar & m_bDrawPageDiv;

	if(ar.IsRead())
	{
		int val;

		ar & val;

		m_unit = (SYSTEM::SYS_UNIT_TYPE)val;

		double minx, maxx, miny, maxy;
		
		ar & minx;

		ar & maxx;

		ar & miny;

		ar & maxy;
		
		m_PageEnvelope.init(minx, maxx, miny, maxy);

		ar & minx;

		ar & maxx;

		ar & miny;

		ar & maxy;

		m_PrintableEnvelope.init(minx, maxx, miny, maxy);

		ar & minx;

		ar & maxx;

		ar & miny;

		ar & maxy;

		m_MarginEnvelope.init(minx, maxx, miny, maxy);

		
		m_pPageGrid = CPageGridPtr(new CPageGrid);
		m_pPageGrid->serialization(ar);
	}
	else
	{
		int val;

		val = m_unit;
		ar & val;

		double minx, maxx, miny, maxy;

		minx = m_PageEnvelope.getMinX();

		maxx = m_PageEnvelope.getMaxX();

		miny = m_PageEnvelope.getMinY();

		maxy = m_PageEnvelope.getMaxY();

		ar & minx;

		ar & maxx;

		ar & miny;

		ar & maxy;


		minx = m_PrintableEnvelope.getMinX();

		maxx = m_PrintableEnvelope.getMaxX();

		miny = m_PrintableEnvelope.getMinY();

		maxy = m_PrintableEnvelope.getMaxY();

		ar & minx;

		ar & maxx;

		ar & miny;

		ar & maxy;


		minx = m_MarginEnvelope.getMinX();

		maxx = m_MarginEnvelope.getMaxX();

		miny = m_MarginEnvelope.getMinY();

		maxy = m_MarginEnvelope.getMaxY();

		ar & minx;

		ar & maxx;

		ar & miny;

		ar & maxy;


		m_pPageGrid->serialization(ar);
	}
}

CPagePtr CPage::Clone()
{
	return NULL;
}

void CPage::SetDrawPageGrid(BOOL bDraw)
{
	if(m_pPageGrid)
	{
		m_pPageGrid->SetGridVisibility(bDraw) ;
		PageSizeChangedEvents();
	}
}

BOOL CPage::GetDrawPageGrid()
{
	if(m_pPageGrid)
		return m_pPageGrid->GetGridVisibility();
	else
		return 0;
}

void CPage::SetPageGridIntervalX(double x)
{
	if(m_pPageGrid)
	{
		m_pPageGrid->SetXInterval(x);
		PageSizeChangedEvents();
	}
}
double CPage::GetPageGridIntervalX()
{
	if(m_pPageGrid)
		return m_pPageGrid->GetXInterval();
	else
		return 50;
}

void CPage::SetPageGridIntervalY(double y)
{
	if(m_pPageGrid)
	{
		m_pPageGrid->SetYInterval(y);
		PageSizeChangedEvents();
	}
}

double CPage::GetPageGridIntervalY()
{
	if(m_pPageGrid)
		return m_pPageGrid->GetYInterval();
	else
		return 50;
}

void CPage::SetDrawPageDiv(BOOL bDraw)
{
	m_bDrawPageDiv = bDraw;
}

BOOL CPage::GetDrawPageDiv()
{
	return m_bDrawPageDiv;
}

void  CPage::SetPrintPageNumX(int nNum)
{
	m_nPrintPageNumX = nNum;
	PageSizeChangedEvents();
}
int  CPage::GetPrintPageNumX()
{
	return m_nPrintPageNumX;
}

void  CPage::SetPrintPageNumY(int nNum)
{
	m_nPrintPageNumY = nNum;
	PageSizeChangedEvents();
}
int  CPage::GetPrintPageNumY()
{
	return m_nPrintPageNumY;
}

//void CPage::SetOnePrintPageWidth(double dbWidth)
//{
//	m_dbOnePrintPageWidth = dbWidth;
//	PageSizeChangedEvents();
//}
//double CPage::GetOnePrintPageWidth()
//{
//	return m_dbOnePrintPageWidth;
//}
//
//void CPage::SetOnePrintPageHeight(double dbHeight)
//{
//	m_dbOnePrintPageHeight = dbHeight;
//	PageSizeChangedEvents();
//}
//double CPage::GetOnePrintPageHeight()
//{
//	return m_dbOnePrintPageHeight;
//}

const GEOMETRY::geom::Envelope& CPage::GetPageEnvelope()
{
	return m_PageEnvelope;
}

const GEOMETRY::geom::Envelope& CPage::GetPageMarginEnvelope()
{
	return m_MarginEnvelope;
}


void CPage::Draw( Display::IDisplayPtr pDisplay , bool bPrint)
{
	if(m_pShadow)
		m_pShadow->Draw(pDisplay);

	if(m_pBackground)
		m_pBackground->Draw(pDisplay);

	if(m_pBorder)
		m_pBorder->Draw(pDisplay);

	if(m_pPageGrid)
		m_pPageGrid->Draw(pDisplay);
}

void CPage::PageSizeChangedEvents()
{
	m_MarginEnvelope = m_PageEnvelope = GEOMETRY::geom::Envelope(0,m_dbOnePrintPageWidth*m_nPrintPageNumX, 0,m_dbOnePrintPageHeight*m_nPrintPageNumY);//mm
	m_MarginEnvelope.expandBy(m_dbMargin);

	if(m_pGeometry)
	{
		GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(m_pGeometry);
		m_pGeometry = NULL;
	}
	m_pGeometry = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->toGeometry(&m_PageEnvelope);

	GEOMETRY::geom::Envelope* pEnv = (GEOMETRY::geom::Envelope*)m_pGeometry->getEnvelopeInternal();
	
	if(m_pBackground)
	{
		m_pBackground->SetGeometry(*m_pGeometry);
		pEnv->expandToInclude(m_pBackground->GetDrawGeometry()->getEnvelopeInternal());
	}

	if(m_pBorder)
	{
		m_pBorder->SetGeometry(*m_pGeometry);
		pEnv->expandToInclude(m_pBorder->GetDrawGeometry()->getEnvelopeInternal());
	}

	if(m_pShadow)
		m_pShadow->SetGeometry(*GEOMETRY::geom::GeometryFactory::getDefaultInstance()->toGeometry(pEnv));

	if(m_pPageGrid)
		m_pPageGrid->SetEnvelope(*pEnv);
	
}

void CPage::Init( )
{
	m_pGeometry = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->toGeometry(&m_PageEnvelope);

	m_dbMargin = 10;
	m_MarginEnvelope = m_PageEnvelope;
	m_MarginEnvelope.expandBy(m_dbMargin);

	m_pBackground.reset(new CSimpleBackground(*m_pGeometry));

	m_pBorder.reset(new CSimpleBorder(*m_pGeometry));

	m_pShadow.reset(new CSimpleShadow(*m_pGeometry));
	m_pShadow->SetGap(1,-1);
	m_pShadow->GetSymbol()->SetFillColor(RGB(100,100,100));

	m_unit = SYSTEM::SYS_UNIT_MILLIMETER;	
	
	m_pPageGrid.reset(new CPageGrid);
	m_pPageGrid->SetXInterval(50);
	m_pPageGrid->SetYInterval(50);
	m_pPageGrid->SetEnvelope(m_PageEnvelope);

	m_bDrawPageDiv  = FALSE;
}

void CPage::SetUnit(SYSTEM::SYS_UNIT_TYPE unit)
{
	m_unit = unit;
}

void CPage::SetPageInfo(PAGE_INFO pageInfo)
{
	m_pageInfo = pageInfo;

	m_dbOnePrintPageWidth = m_pageInfo.width;

	m_dbOnePrintPageHeight = m_pageInfo.height;
}

}