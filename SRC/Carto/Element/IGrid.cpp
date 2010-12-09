#include "StdAfx.h"
#include "IGrid.h"
#include "GraticuleGrid.h"
#include "MeasuredGrid.h"
#include "StdMeasuredGrid.h"
#include "StdGraticuleGrid.h"
#include "PageGrid.h"
#include "SymbolFactory.h"

namespace Element{

IGrid::IGrid()
{
	m_bActive = TRUE;

	m_bDynamicXYOrg = TRUE;

	m_pBorderLine = NULL;
	m_pLines = NULL;
	m_pMarkers = NULL;
	m_pTickLines = NULL;
	m_pSubTickLines = NULL;


	//border
	m_bBorderVisibility = TRUE;
	m_bBorderDirty = TRUE;
	m_pBorderLineSymbol.reset(new Display::CSimpleLineSymbol);
	m_pBorderLineSymbol->SetLineColor(RGB(110,110,110));
	m_borderExpandX = 0;
	m_borderExpandY = 0;

	//grid
	m_bGridVisibility = TRUE;
	m_bGridDirty = TRUE;
	m_pGridLineSymbol.reset(new Display::CSimpleLineSymbol);
	m_pGridLineSymbol->SetLineColor(RGB(110,110,110));


	Display::CSimpleMarkerSymbol* pMarkerSym = new Display::CSimpleMarkerSymbol;
	pMarkerSym->SetMarkerType(SIMPLE_MARKER_CROSS);
	pMarkerSym->SetMarkerSize(3);
	pMarkerSym->SetOutLineColor(RGB(110,110,110));
	m_pGridMarkerSymbol.reset(pMarkerSym);

	//label
	m_bLabelVisibility = TRUE;
	m_bLabelDirty = TRUE;
	m_labelOffset = 0;
	m_pTextSym.reset(new Display::CTextSymbol);
	m_pTextSym->SetTextPosType(TXTPOS_CENTERTOP);
	m_bLabelTop = TRUE;
	m_bLabelBottom = TRUE;
	m_bLabelLeft = TRUE;
	m_bLabelRight = TRUE;

	m_bVertTopBottom = FALSE;
	m_bVertLeftRight = TRUE;

	//tick
	m_bTickVisibility = TRUE;
	m_bTickDirty = TRUE;
	m_tickLength = 3;
	m_tickOffset = 0;
	m_pTickLineSymbol.reset(new Display::CSimpleLineSymbol);
	m_pTickLineSymbol->SetLineColor(RGB(110,110,110));

	//sub tick
	m_subTickLength = 0;
	m_pSubTickLineSymbol.reset(new Display::CSimpleLineSymbol);
	m_pSubTickLineSymbol->SetLineColor(RGB(110,110,110));

	m_gridLineStyle = MGLS_LINE;	
}

IGrid::~IGrid(void)
{
	if(m_pLines)
	{
		GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(m_pLines);
		m_pLines = NULL;
	}

	if(m_pMarkers)
	{
		GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(m_pMarkers);
		m_pMarkers = NULL;
	}

	if(m_pBorderLine)
	{
		GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(m_pBorderLine);
		m_pBorderLine = NULL;
	}

	if(m_pTickLines)
	{
		GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(m_pTickLines);
		m_pTickLines = NULL;
	}

	if(m_pSubTickLines)
	{
		GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(m_pSubTickLines);
		m_pSubTickLines = NULL;
	}
}

void IGrid::serialization(SYSTEM::IArchive &ar)
{
	SYSTEM::ISerialization::serialization(ar);

	if(ar.IsRead())
	{
		int type;
		ar & type;
		m_GridType = (GridType)type;

		int style;
		ar & style;
		style = (MapGridLineStyle)m_gridLineStyle;

		m_pGridLineSymbol = Display::CSymbolFactory::CreateSymbolFromStream(ar);

		m_pGridMarkerSymbol = Display::CSymbolFactory::CreateSymbolFromStream(ar);

		m_pBorderLineSymbol = Display::CSymbolFactory::CreateSymbolFromStream(ar);

		m_pTickLineSymbol = Display::CSymbolFactory::CreateSymbolFromStream(ar);

		m_pSubTickLineSymbol = Display::CSymbolFactory::CreateSymbolFromStream(ar);
	}
	else
	{
		int type;
		type = (int)m_GridType;
		ar & type;
		

		int style;
		style = (int)m_gridLineStyle;
		ar & style;

		m_pGridLineSymbol->serialization(ar);

		m_pGridMarkerSymbol->serialization(ar);

		m_pBorderLineSymbol->serialization(ar);

		m_pTickLineSymbol->serialization(ar);

		m_pSubTickLineSymbol->serialization(ar);	
	}

	ar & m_bActive;

	ar & m_strGridName;

	ar & m_bGridVisibility;

	ar & m_bDynamicXYOrg;

	ar & m_XOrigin;

	ar & m_YOrigin;

	ar & m_XInterval;

	ar & m_YInterval;

	ar & m_bBorderVisibility;

	ar & m_borderExpandX;

	ar & m_borderExpandY;


	ar & m_bLabelVisibility;

	ar & m_labelOffset;

	ar & m_bLabelTop;

	ar & m_bLabelBottom;

	ar & m_bLabelLeft;

	ar & m_bLabelRight;

	ar & m_bVertTopBottom;

	m_pTextSym->serialization(ar);

	
	ar & m_bTickVisibility;

	ar & m_tickCount;

	ar & m_tickLength;

	ar & m_tickOffset;


	ar & m_bSubTickVisibility;

	ar & m_subTickCount;

	
	
}

IGridPtr IGrid::CreateGridFromStream(SYSTEM::IArchive &ar)
{
	unsigned long lPos = ar.GetCurrentPos();

	int type;
	ar & type;
	
	ar.GetCurrentPos() = lPos;

	IGridPtr pGrid = CreateGrid((GridType)type);

	if (pGrid != NULL)
		pGrid->serialization(ar);

	return pGrid;

}

IGridPtr  IGrid::CreateGrid(GridType type)
{
	switch(type)
	{
	case GT_GRATICULE_GRID:
		return CGraticuleGridPtr(new CGraticuleGrid());
	case GT_MEASURED_GRID:
		return CMeasuredGridPtr(new CMeasuredGrid());
	case GT_STANDARD_MAPPING_GRID:
		return CStdMeasuredGridPtr(new CStdMeasuredGrid());
	case GT_STANDARD_GRATICULE_GRID:
		return CStdGraticuleGridPtr(new CStdGraticuleGrid());
	default:
		return NULL;
	}
}

void IGrid::Draw(Display::IDisplayPtr pDisplay)
{
	SYSTEM::SYS_UNIT_TYPE unit = pDisplay->GetDisplayTransformation().GetUnit();
	m_borderExpandXPage = SYSTEM::UnitConverter::ConvertUnits(m_borderExpandX,SYSTEM::SYS_UNIT_MILLIMETER,  unit);
	m_borderExpandYPage = SYSTEM::UnitConverter::ConvertUnits(m_borderExpandY,SYSTEM::SYS_UNIT_MILLIMETER,  unit);
	m_tickLengthPage = SYSTEM::UnitConverter::ConvertUnits(m_tickLength,SYSTEM::SYS_UNIT_MILLIMETER,  unit);
	m_tickOffsetPage = SYSTEM::UnitConverter::ConvertUnits(m_tickOffset,SYSTEM::SYS_UNIT_MILLIMETER,  unit);
	m_subTickLengthPage = SYSTEM::UnitConverter::ConvertUnits(m_subTickLength,SYSTEM::SYS_UNIT_MILLIMETER,  unit);
}

void IGrid::SetRecalcGrid()
{
	m_bGridDirty = TRUE;
	m_bBorderDirty = TRUE;
	m_bLabelDirty = TRUE;
	m_bTickDirty = TRUE;
	m_bSubTickDirty = TRUE;
}

void IGrid::SetGridActive(BOOL bActive)
{
	m_bActive = bActive;
}
BOOL IGrid::GetGridActive()
{
	return m_bActive;
}

void IGrid::SetGridName(std::string name)
{
	m_strGridName = name;
}
std::string IGrid::GetGridName()
{
	return m_strGridName;
}

//grid
void IGrid::SetGridVisibility(BOOL bVisible)
{
	m_bGridVisibility = bVisible;
}
BOOL IGrid::GetGridVisibility()
{
	return m_bGridVisibility;
}

void IGrid::SetMapGridLineStyle(int nStyle)
{
	m_gridLineStyle = (MapGridLineStyle)nStyle;
	m_bGridDirty = TRUE;
}
int IGrid::GetMapGridLineStyle()
{
	return (int)m_gridLineStyle;
}

void IGrid::SetGridLineSymbol(Display::ILineSymbolPtr pLineSymbol)
{
	m_pGridLineSymbol = pLineSymbol;
	m_bGridDirty = TRUE;
}
Display::ILineSymbolPtr IGrid::GetGridLineSymbol()
{
	return m_pGridLineSymbol;
}

void IGrid::SetGridMarkerSymbol(Display::IMarkerSymbolPtr pGridMarkerSymbol)
{
	m_pGridMarkerSymbol = pGridMarkerSymbol;
	m_bGridDirty = TRUE;
}
Display::IMarkerSymbolPtr IGrid::GetGridMarkerSymbol()
{
	return m_pGridMarkerSymbol;
}

void IGrid::SetUseDynamicXYOrigin(BOOL bDyn)
{
	m_bDynamicXYOrg = bDyn;
	m_bGridDirty = TRUE;
}
BOOL IGrid::GetUseDynamicXYOrigin()
{
	return m_bDynamicXYOrg;
}

void IGrid::SetXOrigin(double XOrg)
{
	m_XOrigin = XOrg;
	m_bGridDirty = TRUE;
}
double IGrid::GetXOrigin()
{
	return m_XOrigin;
}

void IGrid::SetYOrigin(double XOrg)
{
	m_YOrigin = XOrg;
	m_bGridDirty = TRUE;
}
double IGrid::GetYOrigin()
{
	return m_YOrigin;
}

void IGrid::SetXInterval(double XInter)
{
	m_XInterval = XInter;
	m_bGridDirty = TRUE;
}
double IGrid::GetXInterval()
{
	return m_XInterval;
}

void IGrid::SetYInterval(double XInter)
{
	m_YInterval = XInter;
	m_bGridDirty = TRUE;
}
double IGrid::GetYInterval()
{
	return m_YInterval;
}

//border
void IGrid::SetBorderVisibility(BOOL bVisible)
{
	m_bBorderVisibility = bVisible;
	m_bBorderDirty = TRUE;
}

BOOL IGrid::GetBorderVisibility()
{
	return m_bBorderVisibility;
}

void IGrid::SetBorderLineSymbol(Display::ILineSymbolPtr pLineSymbol)
{
	m_pBorderLineSymbol = pLineSymbol;
	m_bBorderDirty = TRUE;
}
Display::ILineSymbolPtr IGrid::GetBorderLineSymbol()
{
	return m_pBorderLineSymbol;
}

void IGrid::SetBorderExpandX(float x)
{
	m_borderExpandX = x;
	m_bBorderDirty = TRUE;
}
float IGrid::GetBorderExpandX()
{
	return m_borderExpandX;
}

void IGrid::SetBorderExpandY(float y)
{
	m_borderExpandY = y;
	m_bBorderDirty = TRUE;
}
float IGrid::GetBorderExpandY()
{
	return m_borderExpandY;
}

//label
void IGrid::SetLabelVisibility(BOOL bVisible)
{
	m_bLabelVisibility = bVisible;
	m_bLabelDirty = TRUE;
}
BOOL IGrid::GetLabelVisibility()
{
	return m_bLabelVisibility;
}

void IGrid::SetTextSymbol(Display::CTextSymbolPtr pTextSym)
{
	m_pTextSym = pTextSym;
	m_bLabelDirty = TRUE;
}

Display::CTextSymbolPtr IGrid::GetTextSymbol()
{
	return m_pTextSym;
}

void IGrid::SetLabelOffset(float fLabelOffset)
{
	m_labelOffset = fLabelOffset;
	m_bLabelDirty = TRUE;
}

float IGrid::GetLabelOffset()
{
	return m_labelOffset;
}


void IGrid::SetLabelTop(BOOL bLabel)
{
	m_bLabelTop = bLabel;
	m_bLabelDirty = TRUE;
}

BOOL IGrid::GetLabelTop()
{
	return m_bLabelTop;
}

void IGrid::SetLabelBottom(BOOL bLabel)
{
	m_bLabelBottom = bLabel;
}

BOOL IGrid::GetLabelBottom()
{
	return m_bLabelBottom;
}

void IGrid::SetLabelLeft(BOOL bLabel)
{
	m_bLabelLeft = bLabel;
	m_bLabelDirty = TRUE;
}

BOOL IGrid::GetLabelLeft()
{
	return m_bLabelLeft;
}

void IGrid::SetLabelRight(BOOL bLabel)
{
	m_bLabelRight = bLabel;
	m_bLabelDirty = TRUE;
}

BOOL IGrid::GetLabelRight()
{
	return m_bLabelRight;
}

void IGrid::SetVertTopBottom(BOOL bVert)
{
	m_bVertTopBottom = bVert;
	m_bLabelDirty = TRUE;
}

BOOL IGrid::GetVertTopBottom()
{
	return m_bVertTopBottom;
}

void IGrid::SetVertLeftRight(BOOL bVert)
{
	m_bVertLeftRight = bVert;
	m_bLabelDirty = TRUE;
}

BOOL IGrid::GetVertLeftRight()
{
	return m_bVertLeftRight;
}

//tick
void IGrid::SetTickVisibility(BOOL bVisible)
{
	m_bTickVisibility = bVisible;
}
BOOL IGrid::GetTickVisibility()
{
	return m_bTickVisibility;
}

void IGrid::SetTickCount(int nCount)
{
	m_tickCount = nCount;
}
int IGrid::GetTickCount()
{
	return m_tickCount;
}

void IGrid::SetTickLength(double dbLen)
{
	m_tickLength = dbLen;
}
double IGrid::GetTickLength()
{
	return m_tickLength;
}

void IGrid::SetTickOffset(double dbOffset)
{
	m_tickOffset = dbOffset;
}

double IGrid::GetTickOffset()
{
	return m_tickOffset;
}
void IGrid::SetTickLineSymbol(Display::ILineSymbolPtr pLineSym)
{
	m_pTickLineSymbol = pLineSym;
}
Display::ILineSymbolPtr IGrid::GetTickLineSymbol()
{
	return m_pTickLineSymbol;
}

//sub tick
void IGrid::SetSubTickVisibility(BOOL bVisible)
{
	m_bSubTickVisibility = bVisible;
}
BOOL IGrid::GetSubTickVisibility()
{
	return m_bSubTickVisibility;
}

void IGrid::SetSubTickCount(int nCount)
{
	m_subTickCount = nCount;
}
int IGrid::GetSubTickCount()
{
	return m_subTickCount;
}

void IGrid::SetSubTickLength(double dbLen)
{
	m_subTickLength = dbLen;
}
double IGrid::GetSubTickLength()
{
	return m_subTickLength;
}

void IGrid::SetSubTickLineSymbol(Display::ILineSymbolPtr pLineSym)
{
	m_pSubTickLineSymbol = pLineSym;
}
Display::ILineSymbolPtr IGrid::GetSubTickLineSymbol()
{
	return m_pSubTickLineSymbol;
}

GridType IGrid::GetGridType()
{
	return m_GridType;
}

//////////////////////////////////////////////////////////////////////////
void IGrid::CalTickLines(Display::IDisplayPtr pDisplay, std::vector<stGridLabel>& vecVerticalLabel, std::vector<stGridLabel>& vecHorizontalLabel,
								 GEOMETRY::geom::Geometry*& pTickLines, double tickOffset, double tickLength)
{
	SYSTEM::SYS_UNIT_TYPE pageUnit;
	long offsetPage, tickLenPage;
	pageUnit = pDisplay->GetDisplayTransformation().GetUnit();
	offsetPage = SYSTEM::UnitConverter::ConvertUnits(tickOffset, SYSTEM::SYS_UNIT_MILLIMETER, pageUnit);
	tickLenPage = SYSTEM::UnitConverter::ConvertUnits(tickLength, SYSTEM::SYS_UNIT_MILLIMETER, pageUnit);

	GEOMETRY::geom::Geometry* pTickLine = NULL;
	GEOMETRY::geom::CoordinateSequence* coords = NULL;
	GEOMETRY::geom::Coordinate coordStart, coordEnd;

	//建立一个空的多线要素
	if(pTickLines)
	{
		GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(pTickLines);
		pTickLines = NULL;
	}
	pTickLines =(Geometry*)GeometryFactory::getDefaultInstance()->createMultiLineString();

	for(int i=0; i<vecVerticalLabel.size(); i++)
	{
		coords = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->getCoordinateSequenceFactory()->create(NULL);
		coordStart.x = vecVerticalLabel[i].pageCoordStart.x;
		coordStart.y = vecVerticalLabel[i].pageCoordStart.y - offsetPage;
		coordEnd.x = vecVerticalLabel[i].pageCoordStart.x; 
		coordEnd.y = vecVerticalLabel[i].pageCoordStart.y - offsetPage - tickLenPage; 
		coords->add(coordStart);
		coords->add(coordEnd);

		pTickLine = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->createLineString(coords);
		((MultiLineString*)pTickLines)->AddGeometry(pTickLine);

		coords = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->getCoordinateSequenceFactory()->create(NULL);
		coordStart.x = vecVerticalLabel[i].pageCoordEnd.x;
		coordStart.y = vecVerticalLabel[i].pageCoordEnd.y + offsetPage;
		coordEnd.x = vecVerticalLabel[i].pageCoordEnd.x; 
		coordEnd.y = vecVerticalLabel[i].pageCoordEnd.y + offsetPage + tickLenPage; 
		coords->add(coordStart);
		coords->add(coordEnd);

		pTickLine = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->createLineString(coords);
		((MultiLineString*)pTickLines)->AddGeometry(pTickLine);
	}

	for(int i=0; i<vecHorizontalLabel.size(); i++)
	{
		coords = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->getCoordinateSequenceFactory()->create(NULL);
		coordStart.x = vecHorizontalLabel[i].pageCoordStart.x - offsetPage;
		coordStart.y = vecHorizontalLabel[i].pageCoordStart.y;
		coordEnd.x = vecHorizontalLabel[i].pageCoordStart.x - offsetPage - tickLenPage; 
		coordEnd.y = vecHorizontalLabel[i].pageCoordStart.y; 
		coords->add(coordStart);
		coords->add(coordEnd);

		pTickLine = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->createLineString(coords);
		((MultiLineString*)pTickLines)->AddGeometry(pTickLine);

		coords = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->getCoordinateSequenceFactory()->create(NULL);
		coordStart.x = vecHorizontalLabel[i].pageCoordEnd.x + offsetPage;
		coordStart.y = vecHorizontalLabel[i].pageCoordEnd.y;
		coordEnd.x = vecHorizontalLabel[i].pageCoordEnd.x + offsetPage + tickLenPage; 
		coordEnd.y = vecHorizontalLabel[i].pageCoordEnd.y; 
		coords->add(coordStart);
		coords->add(coordEnd);

		pTickLine = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->createLineString(coords);
		((MultiLineString*)pTickLines)->AddGeometry(pTickLine);
	}
}

void IGrid::CalSubTickLines()
{
}
}
