#include "StdAfx.h"
#include "StdGraticuleGrid.h"
#include "MapFrame.h"
#include "ProjTransform.h"
#include "SpatialReference.h"
#include "SymbolFactory.h"
#include "AffineTransform.h"
//#include "TI_Project.h"

#include <string.h>

namespace Element{

CStdGraticuleGrid::CStdGraticuleGrid():IMapGrid()
{
	m_strGridName = "标准经纬网格";

	m_gridLabelContent = GLC_D_M_S;
}
CStdGraticuleGrid::CStdGraticuleGrid(CMapFrame* pMapFrame)
{
	m_gridLabelContent = GLC_D_M_S;

	m_pMapFrame = pMapFrame;

	m_GridType = GT_STANDARD_GRATICULE_GRID;

	m_lXDistanceToBorder = 20;
	m_lYDistanceToBorder = 20;
	
	m_strGridName = "标准经纬网格";

	m_pTextSym.reset(new Display::CTextSymbol);

	Display::IDisplayPtr pFrameDisplay = m_pMapFrame->GetMap()->GetDisplay();
	GEOMETRY::geom::Envelope MapFrameGeoEnv;
	pFrameDisplay->GetDisplayTransformation().GetGeoBound(MapFrameGeoEnv);

	std::string mapProj = m_pMapFrame->GetMap()->GetMapProjection();
	char cLLWkt[1024] = "GEOGCS[\"WGS84\",DATUM[\"WGS_1984\",SPHEROID[\"WGS_1984\",6378137.000000,298.257224]],PRIMEM[\"Greenwich\",0.000000],UNIT[\"Degree\",0.0174532925199433]]";

	//动态投影
	/*if(!IPE_IsWktEqual((const char*)mapProj.c_str(),(const char*)cLLWkt))
	{
		Carto::CAffineTransform affine;
		affine.DynaProject(mapProj,cLLWkt,MapFrameGeoEnv);

		affine.Transform(MapFrameGeoEnv);

	}*/

	m_XOrigin = MapFrameGeoEnv.getMinX();
	m_YOrigin = MapFrameGeoEnv.getMinY();
}

CStdGraticuleGrid::~CStdGraticuleGrid(void)
{
}

void CStdGraticuleGrid::serialization(SYSTEM::IArchive &ar)
{
	IMapGrid::serialization(ar);
	
	if(ar.IsRead())
	{
		int iLabelContent;
		ar & iLabelContent;
		m_gridLabelContent = (GridLabelContent)iLabelContent;
	}
	else
	{
	
		int iLabelContent;
		iLabelContent = (int) m_gridLabelContent;
		ar & iLabelContent;
	}


	ar & m_lXDistanceToBorder;

	ar & m_lYDistanceToBorder;

}

IGridPtr CStdGraticuleGrid::Clone()
{
	CStdGraticuleGrid* pClone = new CStdGraticuleGrid(m_pMapFrame);

	*pClone = *this;

	pClone->m_pGridLineSymbol = m_pGridLineSymbol->Clone();
	pClone->m_pTextSym = m_pTextSym->Clone();
	pClone->m_pTickLineSymbol = m_pTickLineSymbol->Clone();
	pClone->m_pSubTickLineSymbol = m_pSubTickLineSymbol->Clone();
	pClone->m_pGridMarkerSymbol = m_pGridMarkerSymbol->Clone();
	pClone->m_pBorderLineSymbol = m_pBorderLineSymbol->Clone();
	
	if(m_pLines)
		pClone->m_pLines = m_pLines->clone();
	if(m_pMarkers)
		pClone->m_pMarkers = m_pMarkers->clone();
	if(m_pTickLines)
		pClone->m_pTickLines = m_pTickLines->clone();
	if(m_pBorderLine)
		pClone->m_pBorderLine = m_pBorderLine->clone();

	CStdGraticuleGridPtr pNewGrid(pClone);
	return pNewGrid;
}

void CStdGraticuleGrid::Draw(Display::IDisplayPtr pDisplay)
{
	IMapGrid::Draw(pDisplay);

	DrawBorder(pDisplay);
	DrawGrid(pDisplay);
	DrawLabel(pDisplay);
}

void CStdGraticuleGrid::DrawGrid(Display::IDisplayPtr pDisplay)
{
	if(m_bGridDirty)
	{
		Display::IDisplayPtr pFrameDisplay = m_pMapFrame->GetMap()->GetDisplay();
		GEOMETRY::geom::Envelope MapFrameGeoEnv, MapFramePageEnv;
		pFrameDisplay->GetDisplayTransformation().GetGeoBound(MapFrameGeoEnv);
		MapFramePageEnv = m_pMapFrame->GetEnvelope();

		std::string mapProj = m_pMapFrame->GetMap()->GetMapProjection();
		char cLLWkt[1024] = "GEOGCS[\"WGS84\",DATUM[\"WGS_1984\",SPHEROID[\"WGS_1984\",6378137.000000,298.257224]],PRIMEM[\"Greenwich\",0.000000],UNIT[\"Degree\",0.0174532925199433]]";

		//动态投影
		/*if(!IPE_IsWktEqual((const char*)mapProj.c_str(),(const char*)cLLWkt))
		{
			Carto::CAffineTransform affine;
			affine.DynaProject(mapProj, cLLWkt, MapFrameGeoEnv);
			affine.Transform(MapFrameGeoEnv);
		}*/

		m_ActualXOrigin = m_XOrigin;
		m_ActualYOrigin = m_YOrigin;
		RegulateOrigin(m_bDynamicXYOrg, m_ActualXOrigin, m_ActualYOrigin, m_XInterval, m_YInterval, MapFrameGeoEnv);
		
		SYSTEM::SYS_UNIT_TYPE pageUnit = pDisplay->GetDisplayTransformation().GetUnit();
		long lXDisplay = SYSTEM::UnitConverter::ConvertUnits(m_lXDistanceToBorder, SYSTEM::SYS_UNIT_MILLIMETER, pageUnit);
		long lYDisplay = SYSTEM::UnitConverter::ConvertUnits(m_lYDistanceToBorder, SYSTEM::SYS_UNIT_MILLIMETER, pageUnit);
		
		double dXDistanceToBorder = lXDisplay * (MapFrameGeoEnv.getMaxX() - MapFrameGeoEnv.getMinX()) / ( MapFramePageEnv.getMaxX() - MapFramePageEnv.getMinX() ); 
		double dYDistanceToBorder = lYDisplay * (MapFrameGeoEnv.getMaxY() - MapFrameGeoEnv.getMinY()) / ( MapFramePageEnv.getMaxY() - MapFramePageEnv.getMinY() ); 			
		
		if(m_gridLineStyle == MGLS_LINE)
		{
			CalcGridLines(MapFrameGeoEnv, MapFramePageEnv, mapProj, cLLWkt, m_ActualXOrigin, m_ActualYOrigin, dXDistanceToBorder, dYDistanceToBorder, m_pLines);
		}
		else if(m_gridLineStyle == MGLS_MARKER)
		{
			CalcGridMarkers(MapFrameGeoEnv, MapFramePageEnv, mapProj, cLLWkt, m_ActualXOrigin, m_ActualYOrigin, dXDistanceToBorder, dYDistanceToBorder, m_pMarkers);
		}

		m_bGridDirty = FALSE;
	}

	if(!m_bGridVisibility || !m_bActive)
		return;

	if(m_gridLineStyle == MGLS_LINE)
	{
		pDisplay->SetSymbol(m_pGridLineSymbol.get());

		pDisplay->Begin();

		pDisplay->Draw(m_pLines);

		pDisplay->End();
	}
	else if(m_gridLineStyle == MGLS_MARKER)
	{
		pDisplay->SetSymbol(m_pGridMarkerSymbol.get());

		pDisplay->Begin();

		pDisplay->Draw(m_pMarkers);

		pDisplay->End();
	}
}

void CStdGraticuleGrid::DrawTick(Display::IDisplayPtr pDisplay)
{

	if(m_bTickDirty)
	{
		CalTickLines(pDisplay, m_vecVerticalLabel, m_vecHorizontalLabel,m_pTickLines, m_tickOffset, m_tickLength);
		m_bTickDirty = FALSE;
	}

	if(!m_bTickVisibility || !m_bActive)
		return;

	pDisplay->SetSymbol(m_pTickLineSymbol.get());

	pDisplay->Begin();

	pDisplay->Draw(m_pTickLines);

	pDisplay->End();
}

void CStdGraticuleGrid::DrawSubTick(Display::IDisplayPtr pDisplay)
{
	/*if(m_bSubTickDirty)
	{
	CalSubTickLines();
	m_bSubTickDirty = FALSE;
	}

	if(!m_bSubTickVisibility || !m_bActive)
	return;

	pDisplay->SetSymbol(m_pTickLineSymbol.get());

	pDisplay->Begin();

	pDisplay->Draw(m_pSubTickLines);

	pDisplay->End();*/
}

void CStdGraticuleGrid::DrawLabel(Display::IDisplayPtr pDisplay)
{
	if(m_bLabelDirty)
	{
		SYSTEM::SYS_UNIT_TYPE pageUnit;
		long offsetPage, tickLenPage, subTickLenPage, labelOffsetPage;
		pageUnit = pDisplay->GetDisplayTransformation().GetUnit();
		offsetPage = SYSTEM::UnitConverter::ConvertUnits(m_tickOffset, SYSTEM::SYS_UNIT_MILLIMETER, pageUnit);
		tickLenPage = SYSTEM::UnitConverter::ConvertUnits(m_tickLength, SYSTEM::SYS_UNIT_MILLIMETER, pageUnit);
		subTickLenPage = SYSTEM::UnitConverter::ConvertUnits(m_subTickLength, SYSTEM::SYS_UNIT_MILLIMETER, pageUnit);
		labelOffsetPage = SYSTEM::UnitConverter::ConvertUnits(m_labelOffset, SYSTEM::SYS_UNIT_MILLIMETER, pageUnit);

		double tickSpacePage;
		if(tickLenPage>subTickLenPage)
			tickSpacePage = offsetPage+tickLenPage;
		else
			tickSpacePage = offsetPage+subTickLenPage;

		Display::CTextSymbolPtr pVertLabelSym, pHoriLabelSym; 
		
		pVertLabelSym = m_pTextSym->Clone();
		if(m_bVertTopBottom)
			pVertLabelSym->SetAngle(3.1415926/2);

		pHoriLabelSym = m_pTextSym->Clone();
		m_bVertLeftRight = false;
		if(m_bVertTopBottom)
			pHoriLabelSym->SetAngle(3.1415926/2);


		m_vecVerDegreeLabels.clear();
		m_vecVerMinuteLabels.clear();
		m_vecVerSecondLabels.clear();

		m_vecHorDegreeLabels.clear();
		m_vecHorMinuteLabels.clear();
		m_vecHorSecondLabels.clear();

		CalLabels( pDisplay, m_vecVerticalLabel, m_vecHorizontalLabel, 
			pVertLabelSym.get(), pHoriLabelSym.get(), tickSpacePage, labelOffsetPage );

		m_bLabelDirty = FALSE;
	}

	if( !m_bLabelVisibility || !m_bActive)
		return;

	Display::CTextSymbolPtr pVertLabelSym, pHoriLabelSym; 

//	vertLabelSym = *m_pTextSym.get();
	pVertLabelSym = m_pTextSym->Clone();
	if(m_bVertTopBottom)
		pVertLabelSym->SetAngle(3.1415926/2);

	pDisplay->SetSymbol( pVertLabelSym.get() );

	pDisplay->Begin();

	for(int i=0; i<m_vecVerDegreeLabels.size(); i++)
	{
		pDisplay->Draw(&m_vecVerDegreeLabels[i].first, m_vecVerDegreeLabels[i].second, TRUE);

		if ( m_gridLabelContent == GLC_D_M_S || m_gridLabelContent == GLC_D_M)
			pDisplay->Draw(&m_vecVerMinuteLabels[i].first, m_vecVerMinuteLabels[i].second, TRUE);
		
		if ( m_gridLabelContent == GLC_D_M_S )
			pDisplay->Draw(&m_vecVerSecondLabels[i].first, m_vecVerSecondLabels[i].second, TRUE);
	}
		

	pDisplay->End();


	pHoriLabelSym = m_pTextSym->Clone();
	m_bVertLeftRight = false;
	if(m_bVertTopBottom)
		pHoriLabelSym->SetAngle(3.1415926/2);

	pDisplay->SetSymbol( pHoriLabelSym.get() );
	

	pDisplay->Begin();

	for(int i=0; i<m_vecHorDegreeLabels.size(); i++)
	{	
		pDisplay->Draw(&m_vecHorDegreeLabels[i].first, m_vecHorDegreeLabels[i].second, TRUE);
		
		if ( m_gridLabelContent == GLC_D_M_S || m_gridLabelContent == GLC_D_M)
		 pDisplay->Draw(&m_vecHorMinuteLabels[i].first, m_vecHorMinuteLabels[i].second, TRUE);

		if ( m_gridLabelContent == GLC_D_M_S )
			pDisplay->Draw(&m_vecHorSecondLabels[i].first, m_vecHorSecondLabels[i].second, TRUE);
	}

	pDisplay->End();
}

void CStdGraticuleGrid::DrawBorder(Display::IDisplayPtr pDisplay)
{
	//
	if(m_bBorderDirty)
	{
		m_envBorder = m_pMapFrame->GetEnvelope();
		m_envBorder.expandBy(m_borderExpandXPage, m_borderExpandYPage);

		GEOMETRY::geom::CoordinateSequence* pCoords = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->getCoordinateSequenceFactory()->create(NULL);
		pCoords->add(GEOMETRY::geom::Coordinate(m_envBorder.getMinX(), m_envBorder.getMinY()));
		pCoords->add(GEOMETRY::geom::Coordinate(m_envBorder.getMinX(), m_envBorder.getMaxY()));
		pCoords->add(GEOMETRY::geom::Coordinate(m_envBorder.getMaxX(), m_envBorder.getMaxY()));
		pCoords->add(GEOMETRY::geom::Coordinate(m_envBorder.getMaxX(), m_envBorder.getMinY()));
		pCoords->add(GEOMETRY::geom::Coordinate(m_envBorder.getMinX(), m_envBorder.getMinY()));

		if(m_pBorderLine)
		{
			GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(m_pBorderLine);
			m_pBorderLine = NULL;
		}

		m_pBorderLine = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->createLineString(pCoords);

		m_bBorderDirty = FALSE;
	}

	if(!m_bBorderVisibility || !m_pBorderLine || !m_bActive)
		return;

	pDisplay->SetSymbol(m_pBorderLineSymbol.get());

	pDisplay->Begin();

	pDisplay->Draw(m_pBorderLine);

	pDisplay->End();
}

void CStdGraticuleGrid::CalcGridLines(GEOMETRY::geom::Envelope& envGeo, GEOMETRY::geom::Envelope& envPage, std::string strMapProj, std::string strLLProj, double XOrigin, double YOrigin, 
								   double dXDistanceToBorder, double dYDistanceToBorder, GEOMETRY::geom::Geometry*& pLines)
{
	std::vector<GEOMETRY::geom::Geometry*> vecLines;
	GEOMETRY::geom::Geometry* pLine = NULL;
	GEOMETRY::geom::CoordinateSequence* coords = NULL;
	GEOMETRY::geom::Coordinate coord;
	int nSampleCoordsNum = 50;

	stGridLabel gridLabel;
	double XOriginPage = envPage.getMinX() + (XOrigin-envGeo.getMinX())/envGeo.getWidth()*envPage.getWidth();
	double YOriginPage = envPage.getMinY() + (YOrigin-envGeo.getMinY())/envGeo.getHeight()*envPage.getHeight();
	m_vecHorizontalLabel.clear();
	m_vecVerticalLabel.clear();

	Carto::CAffineTransform affine;
	affine.DynaProject(strMapProj,strLLProj,envGeo);

	if(pLines)
	{
		GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(pLines);
		pLines = NULL;
	}
	pLines =(Geometry*)GeometryFactory::getDefaultInstance()->createMultiLineString();

	//lonlines
	//-------------------------------- first lonline--------------------------------------------------------//
	coords = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->getCoordinateSequenceFactory()->create(NULL);
	for( int j = 0; j < nSampleCoordsNum; j++ )
	{	
		//逆投影
		coord.x = envGeo.getMinX() + dXDistanceToBorder;
		if( j == nSampleCoordsNum-1 )
			coord.y = envGeo.getMaxY();
		else
			coord.y = YOrigin + (double)j * (envGeo.getMaxY()-YOrigin) /(double)nSampleCoordsNum;

		//geo label 坐标（单位：地图坐标）
		if(j==0)
		{
			gridLabel.geoCoordStart.x = coord.x;
			gridLabel.geoCoordStart.y = coord.y;

			gridLabel.pageCoordStart.x = envPage.getMinX() + (coord.x-envGeo.getMinX())/envGeo.getWidth() * envPage.getWidth();
			gridLabel.pageCoordStart.y = m_envBorder.getMinY();

			coord.x = envPage.getMinX() + (coord.x - envGeo.getMinX())/envGeo.getWidth()*envPage.getWidth();
			coord.y = m_envBorder.getMinY();
		}
		else if(j==nSampleCoordsNum-1)
		{
			gridLabel.geoCoordEnd.x =coord.x;
			gridLabel.geoCoordEnd.y = coord.y;

			gridLabel.pageCoordEnd.x = envPage.getMinX() + (coord.x-envGeo.getMinX())/envGeo.getWidth() * envPage.getWidth();
			gridLabel.pageCoordEnd.y = m_envBorder.getMaxY();

			coord.x = envPage.getMinX() + (coord.x - envGeo.getMinX())/envGeo.getWidth()*envPage.getWidth();
			coord.y = m_envBorder.getMaxY();
		}
		else
		{
			//page lines 网格线（单位：制图页面坐标）
			coord.x = envPage.getMinX() + (coord.x - envGeo.getMinX())/envGeo.getWidth()*envPage.getWidth();
			coord.y = envPage.getMinY() + (coord.y - envGeo.getMinY())/envGeo.getHeight()*envPage.getHeight();
		}

		coords->add(coord);		
	}
	m_vecVerticalLabel.push_back(gridLabel);

	pLine = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->createLineString(coords);
	((MultiLineString*)pLines)->AddGeometry(pLine);
	//--------------------------------------------------------------------------------------------------------//

	//--------------------------------second lonline--------------------------------------------------------//
	coords = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->getCoordinateSequenceFactory()->create(NULL);
	for( int j = 0; j < nSampleCoordsNum; j++ )
	{	
		//逆投影
		coord.x = envGeo.getMaxX() - dXDistanceToBorder;
		if( j == nSampleCoordsNum-1 )
			coord.y = envGeo.getMaxY();
		else
			coord.y = YOrigin + (double)j * (envGeo.getMaxY()-YOrigin) /(double)nSampleCoordsNum;

		//geo label 坐标（单位：地图坐标）
		if(j==0)
		{
			gridLabel.geoCoordStart.x = coord.x;
			gridLabel.geoCoordStart.y = coord.y;

			gridLabel.pageCoordStart.x = envPage.getMinX() + (coord.x-envGeo.getMinX())/envGeo.getWidth() * envPage.getWidth();
			gridLabel.pageCoordStart.y = m_envBorder.getMinY();

			coord.x = envPage.getMinX() + (coord.x - envGeo.getMinX())/envGeo.getWidth()*envPage.getWidth();
			coord.y = m_envBorder.getMinY();
		}
		else if(j==nSampleCoordsNum-1)
		{
			gridLabel.geoCoordEnd.x =coord.x;
			gridLabel.geoCoordEnd.y = coord.y;

			gridLabel.pageCoordEnd.x = envPage.getMinX() + (coord.x-envGeo.getMinX())/envGeo.getWidth() * envPage.getWidth();
			gridLabel.pageCoordEnd.y = m_envBorder.getMaxY();

			coord.x = envPage.getMinX() + (coord.x - envGeo.getMinX())/envGeo.getWidth()*envPage.getWidth();
			coord.y = m_envBorder.getMaxY();
		}
		else
		{
			//page lines 网格线（单位：制图页面坐标）
			coord.x = envPage.getMinX() + (coord.x - envGeo.getMinX())/envGeo.getWidth()*envPage.getWidth();
			coord.y = envPage.getMinY() + (coord.y - envGeo.getMinY())/envGeo.getHeight()*envPage.getHeight();
		}

		coords->add(coord);		
	}
	m_vecVerticalLabel.push_back( gridLabel );

	pLine = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->createLineString(coords);
	((MultiLineString*)pLines)->AddGeometry(pLine);
	//------------------------------------------------------------------------------------------------------//

	//latLines
	//-------------------------------- first latline--------------------------------------------------------//
	coords = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->getCoordinateSequenceFactory()->create( NULL );
	for( int j = 0; j < nSampleCoordsNum; j++ )
	{
		//逆投影
		if( j == nSampleCoordsNum-1 )
			coord.x = envGeo.getMaxX();
		else
			coord.x = XOrigin + (double)j * (envGeo.getMaxX()-XOrigin) /(double)nSampleCoordsNum;

		coord.y = envGeo.getMinY() + dYDistanceToBorder ;
		//affine.TransformN(coord.x, coord.y);

		//geo label 坐标（单位：地图坐标）
		if(j==0)
		{
			gridLabel.geoCoordStart.x = coord.x;
			gridLabel.geoCoordStart.y = coord.y;

			gridLabel.pageCoordStart.x = m_envBorder.getMinX();
			gridLabel.pageCoordStart.y = envPage.getMinY() + (coord.y-envGeo.getMinY())/envGeo.getHeight() * envPage.getHeight();

			coord.x = m_envBorder.getMinX();
			coord.y = envPage.getMinY() + (coord.y - envGeo.getMinY())/envGeo.getHeight()*envPage.getHeight();
		}
		else if(j==nSampleCoordsNum-1)
		{
			gridLabel.geoCoordEnd = coord.x;
			gridLabel.geoCoordEnd.y = coord.y;

			gridLabel.pageCoordEnd.x = m_envBorder.getMaxX();
			gridLabel.pageCoordEnd.y = envPage.getMinY() + (coord.y-envGeo.getMinY())/envGeo.getHeight() * envPage.getHeight();

			coord.x = m_envBorder.getMaxX();
			coord.y = envPage.getMinY() + (coord.y - envGeo.getMinY())/envGeo.getHeight()*envPage.getHeight();}
		else
		{
			//page lines 网格线（单位：制图页面坐标）
			coord.x = envPage.getMinX() + (coord.x - envGeo.getMinX())/envGeo.getWidth()*envPage.getWidth();
			coord.y = envPage.getMinY() + (coord.y - envGeo.getMinY())/envGeo.getHeight()*envPage.getHeight();
		}


		coords->add(coord);		
	}

	m_vecHorizontalLabel.push_back(gridLabel);

	pLine = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->createLineString(coords);
	((MultiLineString*)pLines)->AddGeometry(pLine);
	//------------------------------------------------------------------------------------------------------//

	//-------------------------------- Second latline--------------------------------------------------------//
	coords = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->getCoordinateSequenceFactory()->create( NULL );
	for( int j = 0; j < nSampleCoordsNum; j++ )
	{
		//逆投影
		if( j == nSampleCoordsNum-1 )
			coord.x = envGeo.getMaxX();
		else
			coord.x = XOrigin + (double)j * (envGeo.getMaxX()-XOrigin) /(double)nSampleCoordsNum;

		coord.y = envGeo.getMaxY() - dYDistanceToBorder ;
		//affine.TransformN(coord.x, coord.y);

		//geo label 坐标（单位：地图坐标）
		if(j==0)
		{
			gridLabel.geoCoordStart.x = coord.x;
			gridLabel.geoCoordStart.y = coord.y;

			gridLabel.pageCoordStart.x = m_envBorder.getMinX();
			gridLabel.pageCoordStart.y = envPage.getMinY() + (coord.y-envGeo.getMinY())/envGeo.getHeight() * envPage.getHeight();

			coord.x = m_envBorder.getMinX();
			coord.y = envPage.getMinY() + (coord.y - envGeo.getMinY())/envGeo.getHeight()*envPage.getHeight();
		}
		else if(j==nSampleCoordsNum-1)
		{
			gridLabel.geoCoordEnd = coord.x;
			gridLabel.geoCoordEnd.y = coord.y;

			gridLabel.pageCoordEnd.x = m_envBorder.getMaxX();
			gridLabel.pageCoordEnd.y = envPage.getMinY() + (coord.y-envGeo.getMinY())/envGeo.getHeight() * envPage.getHeight();

			coord.x = m_envBorder.getMaxX();
			coord.y = envPage.getMinY() + (coord.y - envGeo.getMinY())/envGeo.getHeight()*envPage.getHeight();}
		else
		{
			//page lines 网格线（单位：制图页面坐标）
			coord.x = envPage.getMinX() + (coord.x - envGeo.getMinX())/envGeo.getWidth()*envPage.getWidth();
			coord.y = envPage.getMinY() + (coord.y - envGeo.getMinY())/envGeo.getHeight()*envPage.getHeight();
		}

		coords->add(coord);		
	}

	m_vecHorizontalLabel.push_back(gridLabel);

	pLine = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->createLineString(coords);
	((MultiLineString*)pLines)->AddGeometry(pLine);
	//------------------------------------------------------------------------------------------------------//
	
}

void CStdGraticuleGrid::CalcGridMarkers(GEOMETRY::geom::Envelope& envGeo, GEOMETRY::geom::Envelope& envPage, std::string strMapProj, std::string strLLProj, double XOrigin, double YOrigin, 
									 double dXDistanceToBorder, double dYDistanceToBorder, GEOMETRY::geom::Geometry*& pMarkers)
{
	int nLonLineNum = 2;
	int nLatLineNum = 2;

	GEOMETRY::geom::CoordinateSequence* coords = NULL;
	GEOMETRY::geom::Coordinate coord;

	stGridLabel gridLabel;
	double XOriginPage = envPage.getMinX() + (XOrigin-envGeo.getMinX())/envGeo.getWidth()*envPage.getWidth();
	double YOriginPage = envPage.getMinY() + (YOrigin-envGeo.getMinY())/envGeo.getHeight()*envPage.getHeight();
	m_vecHorizontalLabel.clear();
	m_vecVerticalLabel.clear();
	
	Carto::CAffineTransform affine;
	affine.DynaProject(strMapProj,strLLProj,envGeo);

	coords = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->getCoordinateSequenceFactory()->create(NULL);

	//lonlines
	for(int i=0; i<nLonLineNum; i++)
	{	
		if ( i == 0 )
			coord.x = envGeo.getMinX() + dXDistanceToBorder;
		else
			coord.x = envGeo.getMaxX() - dXDistanceToBorder;

		for( int j = 0; j < nLatLineNum; j++ )
		{			
			if ( j == 0 )
				coord.y = envGeo.getMinY() + dYDistanceToBorder;
			else
				coord.y = envGeo.getMaxY() - dYDistanceToBorder;

			//geo label 坐标（单位：地图坐标）
			if(j==0)
			{
				gridLabel.geoCoordStart.x = coord.x;
				gridLabel.geoCoordStart.y = coord.y;

				gridLabel.pageCoordStart.x = (envPage.getMinX() + coord.x-envGeo.getMinX())/envGeo.getWidth() * envPage.getWidth();
				gridLabel.pageCoordStart.y = (envPage.getMinY() + coord.y-envGeo.getMinY())/envGeo.getHeight() * envPage.getHeight();
			}
			else if(j==nLatLineNum-1)
			{
				gridLabel.geoCoordEnd.x = coord.x;
				gridLabel.geoCoordEnd.y = coord.y;

				gridLabel.pageCoordEnd.x = (envPage.getMinX() + coord.x-envGeo.getMinX())/envGeo.getWidth() * envPage.getWidth();
				gridLabel.pageCoordEnd.y = (envPage.getMinY() + coord.y-envGeo.getMinY())/envGeo.getHeight() * envPage.getHeight();

			}
			m_vecVerticalLabel.push_back(gridLabel);

			coord.x = envPage.getMinX() + (coord.x - envGeo.getMinX())/envGeo.getWidth()*envPage.getWidth();
			coord.y = envPage.getMinY() + (coord.y - envGeo.getMinY())/envGeo.getHeight()*envPage.getHeight();


			//page lines 网格点（单位：制图页面坐标）
			if(coord.x <= envPage.getMinX() || coord.x >= envPage.getMaxX() ||coord.y <= envPage.getMinY() || coord.y >= envPage.getMaxY())
				continue;

			coords->add(coord);		
		}
	}

	//latLines
	for( int i = 0; i < nLatLineNum; i++ )
	{
		if ( i == 0 )
			coord.x = envGeo.getMinX() + dXDistanceToBorder;
		else
			coord.x = envGeo.getMaxX() - dXDistanceToBorder;

		for(int j=0; j<nLonLineNum; j++)
		{
			if ( j == 0 )
				coord.y = envGeo.getMinY() + dYDistanceToBorder;
			else
				coord.y = envGeo.getMaxY() - dYDistanceToBorder;

			//geo label 坐标（单位：地图坐标）
			if(j==0)
			{
				gridLabel.geoCoordStart.x = coord.x;
				gridLabel.geoCoordStart.y = coord.y;

				gridLabel.pageCoordStart.x = (envPage.getMinX() + coord.x-envGeo.getMinX())/envGeo.getWidth() * envPage.getWidth();
				gridLabel.pageCoordStart.y = (envPage.getMinY() + coord.y-envGeo.getMinY())/envGeo.getHeight() * envPage.getHeight();

			}
			else if(j==nLonLineNum-1)
			{
				gridLabel.geoCoordEnd.x = coord.x;
				gridLabel.geoCoordEnd.y = coord.y;

				gridLabel.pageCoordEnd.x = (envPage.getMinX() + coord.x-envGeo.getMinX())/envGeo.getWidth() * envPage.getWidth();
				gridLabel.pageCoordEnd.y = (envPage.getMinY() + coord.y-envGeo.getMinY())/envGeo.getHeight() * envPage.getHeight();

			}
			m_vecHorizontalLabel.push_back(gridLabel);

			//page lines 网格线（单位：制图页面坐标）
			coord.x = envPage.getMinX() + (coord.x - envGeo.getMinX())/envGeo.getWidth()*envPage.getWidth();
			coord.y = envPage.getMinY() + (coord.y - envGeo.getMinY())/envGeo.getHeight()*envPage.getHeight();

			//page lines 网格点（单位：制图页面坐标）
			if(coord.x <= envPage.getMinX() || coord.x >= envPage.getMaxX() ||coord.y <= envPage.getMinY() || coord.y >= envPage.getMaxY())
				continue;

			coords->add(coord);		
		}
	}

	if(pMarkers)
	{
		GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(pMarkers);
		pMarkers = NULL;
	}

	if(coords->getSize()>0)
		pMarkers = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->createMultiPoint(*coords);

	delete coords;
}

void CStdGraticuleGrid::CalLabels(Display::IDisplayPtr pDisplay, 
						 std::vector<stGridLabel>& vecVerticalLabel, 
						 std::vector<stGridLabel>& vecHorizontalLabel, 
						 Display::CTextSymbol* pVerticalTextSym,
						 Display::CTextSymbol* pHorizontalTextSym, 
						 double tickSpacePage,
						 double labelOffset)
{
	int labelStep = 1;//label绘制的间隔
	DIS_RECT textRect;
	GEOMETRY::geom::Envelope textEnv;
	
	GEOMETRY::geom::Coordinate coordLabelPos, coordLabelGeo;

	//bottom
	if(m_bLabelBottom)
	{
		for(int i=0; i<vecVerticalLabel.size(); i+=labelStep)
		{
			coordLabelGeo = vecVerticalLabel[i].geoCoordStart;
			coordLabelPos = vecVerticalLabel[i].pageCoordStart;
			
			std::vector<std::string> vecDMS;	//degree/minute/second
			TransformToGraticuleText( coordLabelGeo.x, vecDMS );
						
			GEOMETRY::geom::Envelope envDegree;
			GEOMETRY::geom::Envelope envMinute;
			GEOMETRY::geom::Envelope envSecond;
			
			textRect = CalculateTextSize( pDisplay, pVerticalTextSym, vecDMS[0] );
			pDisplay->GetDisplayTransformation().TransformToGeo( textRect, &textEnv );
			envDegree.init( coordLabelPos.x - textEnv.getWidth()/2,
				coordLabelPos.x - textEnv.getWidth()/2,
				coordLabelPos.y + tickSpacePage + labelOffset + textEnv.getHeight()/2, 
				coordLabelPos.y + tickSpacePage + labelOffset + textEnv.getHeight()/2 );
			
			textRect = CalculateTextSize( pDisplay, pVerticalTextSym, vecDMS[1] );
			pDisplay->GetDisplayTransformation().TransformToGeo( textRect, &textEnv );
			envMinute.init( coordLabelPos.x + textEnv.getWidth()/2,
				coordLabelPos.x + textEnv.getWidth()/2,
				coordLabelPos.y + tickSpacePage + labelOffset + textEnv.getHeight()/2, 
				coordLabelPos.y + tickSpacePage + labelOffset + textEnv.getHeight()/2 );
			
			envSecond.init( coordLabelPos.x + textEnv.getWidth()*3/2,
				coordLabelPos.x + textEnv.getWidth()*3/2,
				coordLabelPos.y + tickSpacePage + labelOffset + textEnv.getHeight()/2, 
				coordLabelPos.y + tickSpacePage + labelOffset + textEnv.getHeight()/2 );
			
			
			std::pair<GEOMETRY::geom::Envelope, std::string> label;
			label.first = envDegree;
			label.second = vecDMS[0];
			m_vecVerDegreeLabels.push_back(label);
	
			label.first = envMinute;
			label.second = vecDMS[1];
			m_vecVerMinuteLabels.push_back(label);

			label.first = envSecond;
			label.second = vecDMS[2];
			m_vecVerSecondLabels.push_back(label);
		}	
	}

	//top
	if(m_bLabelTop)
	{
		for(int i=0; i<vecVerticalLabel.size(); i+=labelStep)
		{
			coordLabelGeo = vecVerticalLabel[i].geoCoordEnd;
			coordLabelPos = vecVerticalLabel[i].pageCoordEnd;

			std::vector<std::string> vecDMS;	//degree/minute/second
			TransformToGraticuleText( coordLabelGeo.x, vecDMS );

			GEOMETRY::geom::Envelope envDegree;
			GEOMETRY::geom::Envelope envMinute;
			GEOMETRY::geom::Envelope envSecond;

			textRect = CalculateTextSize( pDisplay, pVerticalTextSym, vecDMS[0] );
			pDisplay->GetDisplayTransformation().TransformToGeo( textRect, &textEnv );
			envDegree.init( coordLabelPos.x - textEnv.getWidth()/2,
				coordLabelPos.x - textEnv.getWidth()/2,
				coordLabelPos.y - tickSpacePage - labelOffset - textEnv.getHeight()/2, 
				coordLabelPos.y - tickSpacePage - labelOffset - textEnv.getHeight()/2 );

			textRect = CalculateTextSize( pDisplay, pVerticalTextSym, vecDMS[1] );
			pDisplay->GetDisplayTransformation().TransformToGeo( textRect, &textEnv );
			envMinute.init( coordLabelPos.x + textEnv.getWidth()/2,
				coordLabelPos.x + textEnv.getWidth()/2,
				coordLabelPos.y - tickSpacePage - labelOffset - textEnv.getHeight()/2, 
				coordLabelPos.y - tickSpacePage - labelOffset - textEnv.getHeight()/2 );

			envSecond.init( coordLabelPos.x + textEnv.getWidth()*3/2,
				coordLabelPos.x + textEnv.getWidth()*3/2,
				coordLabelPos.y - tickSpacePage - labelOffset - textEnv.getHeight()/2, 
				coordLabelPos.y - tickSpacePage - labelOffset - textEnv.getHeight()/2 );


			std::pair<GEOMETRY::geom::Envelope, std::string> label;
			label.first = envDegree;
			label.second = vecDMS[0];
			m_vecVerDegreeLabels.push_back(label);

			label.first = envMinute;
			label.second = vecDMS[1];
			m_vecVerMinuteLabels.push_back(label);

			label.first = envSecond;
			label.second = vecDMS[2];
			m_vecVerSecondLabels.push_back(label);
		}	
	}


	//left
	if ( m_bLabelLeft )
	{
		for(int i=0; i<vecHorizontalLabel.size(); i+=labelStep)
		{
			coordLabelGeo = vecHorizontalLabel[i].geoCoordStart;
			coordLabelPos = vecHorizontalLabel[i].pageCoordStart;

			std::vector<std::string> vecDMS;	//degree/minute/second
			TransformToGraticuleText( coordLabelGeo.x, vecDMS );

			GEOMETRY::geom::Envelope envDegree;
			GEOMETRY::geom::Envelope envMinute;
			GEOMETRY::geom::Envelope envSecond;

			SYSTEM::SYS_UNIT_TYPE pageUnit = pDisplay->GetDisplayTransformation().GetUnit();
			double dXDistanceToBorder = SYSTEM::UnitConverter::ConvertUnits(m_lXDistanceToBorder, SYSTEM::SYS_UNIT_MILLIMETER, pageUnit);
			
			textRect = CalculateTextSize( pDisplay, pVerticalTextSym, vecDMS[0] );
			pDisplay->GetDisplayTransformation().TransformToGeo( textRect, &textEnv );
			envDegree.init( coordLabelPos.x - tickSpacePage - labelOffset - textEnv.getWidth()/2 + dXDistanceToBorder,
				coordLabelPos.x - tickSpacePage - labelOffset - textEnv.getWidth()/2 + dXDistanceToBorder,
				coordLabelPos.y + textEnv.getHeight()/2, 
				coordLabelPos.y + textEnv.getHeight()/2 );

			textRect = CalculateTextSize( pDisplay, pVerticalTextSym, vecDMS[1] );
			pDisplay->GetDisplayTransformation().TransformToGeo( textRect, &textEnv );
			envMinute.init( coordLabelPos.x - tickSpacePage - labelOffset - textEnv.getWidth()*3/2 + dXDistanceToBorder,
				coordLabelPos.x - tickSpacePage - labelOffset - textEnv.getWidth()*3/2 + dXDistanceToBorder,
				coordLabelPos.y - textEnv.getHeight()/2, 
				coordLabelPos.y - textEnv.getHeight()/2 );

			envSecond.init( coordLabelPos.x - tickSpacePage - labelOffset - textEnv.getWidth()/2 + dXDistanceToBorder,
				coordLabelPos.x - tickSpacePage - labelOffset - textEnv.getWidth()/2 + dXDistanceToBorder,
				coordLabelPos.y - textEnv.getHeight()/2, 
				coordLabelPos.y - textEnv.getHeight()/2 );


			std::pair<GEOMETRY::geom::Envelope, std::string> label;
			label.first = envDegree;
			label.second = vecDMS[0];
			m_vecHorDegreeLabels.push_back(label);

			label.first = envMinute;
			label.second = vecDMS[1];
			m_vecHorMinuteLabels.push_back(label);

			label.first = envSecond;
			label.second = vecDMS[2];
			m_vecHorSecondLabels.push_back(label);
		}		
	}
	

	//right
	if ( m_bLabelLeft )
	{
		for(int i=0; i<vecHorizontalLabel.size(); i+=labelStep)
		{
			coordLabelGeo = vecHorizontalLabel[i].geoCoordEnd;
			coordLabelPos = vecHorizontalLabel[i].pageCoordEnd;

			std::vector<std::string> vecDMS;	//degree/minute/second
			TransformToGraticuleText( coordLabelGeo.x, vecDMS );

			GEOMETRY::geom::Envelope envDegree;
			GEOMETRY::geom::Envelope envMinute;
			GEOMETRY::geom::Envelope envSecond;

			SYSTEM::SYS_UNIT_TYPE pageUnit = pDisplay->GetDisplayTransformation().GetUnit();
			double dXDistanceToBorder = SYSTEM::UnitConverter::ConvertUnits(m_lXDistanceToBorder, SYSTEM::SYS_UNIT_MILLIMETER, pageUnit);

			textRect = CalculateTextSize( pDisplay, pVerticalTextSym, vecDMS[0] );
			pDisplay->GetDisplayTransformation().TransformToGeo( textRect, &textEnv );
			envDegree.init( coordLabelPos.x + tickSpacePage + labelOffset + textEnv.getWidth()/2 - dXDistanceToBorder,
				coordLabelPos.x + tickSpacePage + labelOffset + textEnv.getWidth()/2 - dXDistanceToBorder,
				coordLabelPos.y + textEnv.getHeight()/2, 
				coordLabelPos.y + textEnv.getHeight()/2 );

			textRect = CalculateTextSize( pDisplay, pVerticalTextSym, vecDMS[1] );
			pDisplay->GetDisplayTransformation().TransformToGeo( textRect, &textEnv );
			envMinute.init( coordLabelPos.x + tickSpacePage + labelOffset + textEnv.getWidth()/2 - dXDistanceToBorder,
				coordLabelPos.x + tickSpacePage + labelOffset + textEnv.getWidth()/2 - dXDistanceToBorder,
				coordLabelPos.y - textEnv.getHeight()/2, 
				coordLabelPos.y - textEnv.getHeight()/2 );

			envSecond.init( coordLabelPos.x + tickSpacePage + labelOffset + textEnv.getWidth()*3/2 - dXDistanceToBorder,
				coordLabelPos.x + tickSpacePage + labelOffset + textEnv.getWidth()*3/2 - dXDistanceToBorder,
				coordLabelPos.y - textEnv.getHeight()/2, 
				coordLabelPos.y - textEnv.getHeight()/2 );


			std::pair<GEOMETRY::geom::Envelope, std::string> label;
			label.first = envDegree;
			label.second = vecDMS[0];
			m_vecHorDegreeLabels.push_back(label);

			label.first = envMinute;
			label.second = vecDMS[1];
			m_vecHorMinuteLabels.push_back(label);

			label.first = envSecond;
			label.second = vecDMS[2];
			m_vecHorSecondLabels.push_back(label);
		}
	}

}

void CStdGraticuleGrid::RegulateOrigin(BOOL bDynamicXYOrg, double& XOrigin, double& YOrigin, double& XInterval, double& YInterval, GEOMETRY::geom::Envelope& Env)
{
	if(bDynamicXYOrg)//若使用地图原点，则不需调整
	{
		XOrigin = Env.getMinX();
		YOrigin = Env.getMinY();
	}

	//规范原点，寻找到从用户设置的原点O开始，距离地图原点DO最近的小于O整数倍Interval的点
	if(XOrigin>Env.getMaxX())
	{
		XOrigin = XOrigin - (int)((XOrigin- Env.getMinX())/XInterval) * XInterval;
	}
	else if(XOrigin<Env.getMinX())
	{
		XOrigin = XOrigin + (int)((Env.getMinX()- XOrigin + XInterval-1)/XInterval) * XInterval;
	}

	if(YOrigin>Env.getMaxY())
	{
		YOrigin = YOrigin - (int)((YOrigin- Env.getMaxY())/YInterval) * YInterval;
	}
	else if(YOrigin<Env.getMinY())
	{
		YOrigin = YOrigin + (int)((Env.getMinY()- YOrigin + YInterval-1)/YInterval) * YInterval;
	}

}

std::string CStdGraticuleGrid::CaculateProjStrapNode()
{
	//the projection parameters 
	char pszWktOut[1024] = "GEOGCS[\"WGS84\",DATUM[\"WGS_1984\",SPHEROID[\"WGS_1984\",6378137.000000,298.257224]],PRIMEM[\"Greenwich\",0.000000],UNIT[\"Degree\",0.0174532925199433]]";
	char pszWktIn[1024];
	strcpy( pszWktIn , m_pMapFrame->GetMap()->GetMapProjection().c_str() ); 
	
	//structure the projection machine
	Geodatabase::CSpatialReferencePtr pSpatialRIn;
	pSpatialRIn.reset( new Geodatabase::CSpatialReference() );
	pSpatialRIn->ImportFromESRI( pszWktIn);
	Geodatabase::CSpatialReferencePtr pSpatialROut;
	pSpatialROut.reset( new Geodatabase::CSpatialReference() );
	pSpatialROut->ImportFromESRI( pszWktOut);
	Geodatabase::CProjTransformPtr projTransform;
	projTransform.reset( new  Geodatabase::CProjTransform( pSpatialRIn, pSpatialROut ) );
	
	//transform the projection
	double llon[1];
	double llat[1];
	llon[0] = m_ActualYOrigin;
	llat[0] = m_ActualXOrigin;

	projTransform->Transform( 1, llat, llon );

	//calculate the projection strap
	long codeProjStrap = ( llon[0] - 0.0 ) / 6 + 1;
	char szProjStrap[20];
	memset( szProjStrap, 0, sizeof( char ) * 20 );
	sprintf( szProjStrap, "%d", codeProjStrap );
	
	std::string	szResult( szProjStrap );
	
	return szResult;
}

void CStdGraticuleGrid::SetGridLabelContent(int enumGridLabelContent)
{
	m_gridLabelContent = (GridLabelContent)enumGridLabelContent;
}

int  CStdGraticuleGrid::GetGridLabelContent()
{
	return (int)m_gridLabelContent;
}

void CStdGraticuleGrid::TransformToGraticuleText(double graticule, std::vector<std::string> &vecDMS )
{
	double x, y;
	long deg = (long)graticule;		

	y = graticule*60 - deg * 60 + 0.0000001;
	long min = (long)(y >= 0 ? y:(-1 * y));

	y = graticule * 3600 - deg*3600 - min*60 + 0.0000001;
	long sec = (y >= 0 ? y:(-1 * y));
	if(sec >= 60)
	{
		sec -= 60;
		min++;
		if(min >= 60)
		{
			min -= 60;
			deg ++;
		}
	}

	char labelDegreeText[100];
	memset(labelDegreeText, 0 , 100*sizeof(char));
	sprintf( labelDegreeText, "%d°", deg );

	char labelMinuteText[100];
	memset( labelMinuteText, 0 , 100*sizeof(char));
	sprintf( labelMinuteText, "%d'", min );

	char labelSecondText[100];
	memset( labelSecondText, 0 , 100*sizeof(char) );
	sprintf( labelSecondText, "%d\"", sec );

	vecDMS.clear();
	vecDMS.push_back( labelDegreeText );
	vecDMS.push_back( labelMinuteText );
	vecDMS.push_back( labelSecondText );
}

void CStdGraticuleGrid::SetXDistancetoBorder( long xDistance )
{
	m_lXDistanceToBorder = xDistance;
}

long CStdGraticuleGrid::GetXDistancetoBorder( void )
{
	return m_lXDistanceToBorder;
}

void CStdGraticuleGrid::SetYDistancetoBorder( long yDistance )
{
	m_lYDistanceToBorder = yDistance;
}

long CStdGraticuleGrid::GetYDistancetoBorder( void )
{
	return m_lYDistanceToBorder;
}

}