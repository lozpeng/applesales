#include "StdAfx.h"
#include "StdMeasuredGrid.h"
#include "MapFrame.h"
#include "ProjTransform.h"
#include "SpatialReference.h"
#include "SymbolFactory.h"

#include <string.h>

namespace Element{

CStdMeasuredGrid::CStdMeasuredGrid():IMapGrid()
{
	m_strGridName = "标准公里网格";
}
CStdMeasuredGrid::CStdMeasuredGrid(CMapFrame* pMapFrame)
{
	m_pMapFrame = pMapFrame;

	m_GridType = GT_STANDARD_MAPPING_GRID;

	m_bDynamicXYOrg = TRUE;

	m_pBorderLine = NULL;

	m_pLines = NULL;

	m_pMarkers = NULL;

	m_pTickLines = NULL;

	m_XInterval = 1000;
	m_YInterval = 1000;

	Display::IDisplayPtr pMapDisplay = m_pMapFrame->GetMap()->GetDisplay();
	GEOMETRY::geom::Envelope MapFrameGeoEnv;
	pMapDisplay->GetDisplayTransformation().GetGeoBound(MapFrameGeoEnv);

	m_XOrigin = MapFrameGeoEnv.getMinX();
	m_YOrigin = MapFrameGeoEnv.getMinY();

	m_bIsDrawKm = true;
	m_bIsDrawHundredKm = true;
	m_bIsDrawProjStrapCode = false;
	
	m_strGridName = "标准公里网格";

	m_pTextSym.reset(new Display::CTextSymbol);
	m_pHundredLabelSymbol.reset( new Display::CTextSymbol );
	m_pProjStrapLabelSymbol.reset( new Display::CTextSymbol );
}

CStdMeasuredGrid::~CStdMeasuredGrid(void)
{
}

void CStdMeasuredGrid::serialization(SYSTEM::IArchive &ar)
{
	IMapGrid::serialization(ar);
	
	if(ar.IsRead())
	{
		bool bIsDrawProj;
		ar & bIsDrawProj;
		m_bIsDrawProjStrapCode = bIsDrawProj;

		bool bIsDrawHundredKm;
		ar & bIsDrawHundredKm;
		m_bIsDrawHundredKm = bIsDrawHundredKm;

		bool bIsDrawKm;
		ar & bIsDrawKm;
		m_bIsDrawKm = bIsDrawKm;
		
		m_pTextSym = Display::CSymbolFactory::CreateSymbolFromStream(ar);
		
		m_pHundredLabelSymbol = Display::CSymbolFactory::CreateSymbolFromStream(ar);

		m_pProjStrapLabelSymbol = Display::CSymbolFactory::CreateSymbolFromStream(ar);
	}
	else
	{
		ar & m_bIsDrawProjStrapCode;

		ar& m_bIsDrawHundredKm;

		ar& m_bIsDrawKm;

		m_pTextSym->serialization(ar);

		m_pHundredLabelSymbol->serialization(ar);

		m_pProjStrapLabelSymbol->serialization(ar);
	}

	ar & m_bVertTopBottom;
	
	ar & m_bVertLeftRight;

}

IGridPtr CStdMeasuredGrid::Clone()
{
	CStdMeasuredGrid* pClone = new CStdMeasuredGrid(m_pMapFrame);

	*pClone = *this;

	pClone->m_pGridLineSymbol = m_pGridLineSymbol->Clone();
	pClone->m_pTextSym = m_pTextSym->Clone();
	pClone->m_pTickLineSymbol = m_pTickLineSymbol->Clone();
	pClone->m_pSubTickLineSymbol = m_pSubTickLineSymbol->Clone();
	pClone->m_pGridMarkerSymbol = m_pGridMarkerSymbol->Clone();
	pClone->m_pBorderLineSymbol = m_pBorderLineSymbol->Clone();
	
	pClone->m_pHundredLabelSymbol = m_pHundredLabelSymbol->Clone();
	pClone->m_pProjStrapLabelSymbol = m_pProjStrapLabelSymbol->Clone();

	if(m_pLines)
		pClone->m_pLines = m_pLines->clone();
	if(m_pMarkers)
		pClone->m_pMarkers = m_pMarkers->clone();
	if(m_pTickLines)
		pClone->m_pTickLines = m_pTickLines->clone();
	if(m_pBorderLine)
		pClone->m_pBorderLine = m_pBorderLine->clone();

	CStdMeasuredGridPtr pNewGrid(pClone);
	return pNewGrid;
}

void CStdMeasuredGrid::Draw(Display::IDisplayPtr pDisplay)
{
	IMapGrid::Draw(pDisplay);

	DrawBorder(pDisplay);
	DrawGrid(pDisplay);
	DrawTick(pDisplay);
	DrawLabel(pDisplay);
}

void CStdMeasuredGrid::DrawGrid(Display::IDisplayPtr pDisplay)
{
	if(m_bGridDirty)
	{
		Display::IDisplayPtr pFrameDisplay = m_pMapFrame->GetMap()->GetDisplay();
		GEOMETRY::geom::Envelope MapFrameGeoEnv;
		pFrameDisplay->GetDisplayTransformation().GetGeoBound(MapFrameGeoEnv);
		GEOMETRY::geom::Envelope MapFramePageEnv = m_pMapFrame->GetEnvelope();

		m_ActualXOrigin = m_XOrigin;
		m_ActualYOrigin = m_YOrigin;
		RegulateOrigin(m_bDynamicXYOrg, m_ActualXOrigin, m_ActualYOrigin, m_XInterval, m_YInterval, MapFrameGeoEnv);

		if(m_gridLineStyle == MGLS_LINE)
		{
			CalcGridLines(MapFrameGeoEnv, MapFramePageEnv, m_ActualXOrigin, m_ActualYOrigin, m_XInterval, m_YInterval, m_pLines);
		}
		else if(m_gridLineStyle == MGLS_MARKER)
		{
			CalcGridMarkers(MapFrameGeoEnv, MapFramePageEnv, m_ActualXOrigin, m_ActualYOrigin, m_XInterval, m_YInterval, m_pMarkers);
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

void CStdMeasuredGrid::DrawTick(Display::IDisplayPtr pDisplay)
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

void CStdMeasuredGrid::DrawSubTick(Display::IDisplayPtr pDisplay)
{
	if(m_bSubTickDirty)
	{
		CalSubTickLines();
		m_bSubTickDirty = FALSE;
	}

	if(!m_bSubTickVisibility || !m_bActive)
		return;

	pDisplay->SetSymbol(m_pTickLineSymbol.get());

	pDisplay->Begin();

	pDisplay->Draw(m_pSubTickLines);

	pDisplay->End();
}

void CStdMeasuredGrid::DrawLabel(Display::IDisplayPtr pDisplay)
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

		Display::CTextSymbol vertLabelSym, horiLabelSym; 

		vertLabelSym = *m_pTextSym.get();
		if(m_bVertTopBottom)
			vertLabelSym.SetAngle(3.1415926/2);

		horiLabelSym = *m_pTextSym.get();
		if(m_bVertLeftRight)
			horiLabelSym.SetAngle(3.1415926/2);

		m_vecVerLabels.clear();
		m_vecHorLabels.clear();
		
		m_vecVerHundredKmLabels.clear();
		m_vecHorHundredKmLabels.clear();
		m_vecVerKmLabels.clear();
		m_vecHorKmLabels.clear();

		CalLabels(pDisplay,
			m_vecVerticalLabel, 
			m_vecHorizontalLabel,
			m_vecVerLabels, 
			m_vecHorLabels, 
			labelOffsetPage, 
			&vertLabelSym, 
			&horiLabelSym, 
			tickSpacePage);
	
		m_bLabelDirty = FALSE;
	}

	if(!m_bLabelVisibility || !m_bActive)
		return;

	Display::CTextSymbolPtr pvertLabelSym, phoriLabelSym;				//百公里以下符号
	Display::CTextSymbolPtr pvHundredLabelSymbol, phHundredLabelSymbol;//百公里符号
	Display::CTextSymbolPtr pprojSymbol;								//投影符号

	/*------------------------垂直线文字-----------------------------*/
	pvertLabelSym = m_pTextSym->Clone();
	pvHundredLabelSymbol = m_pHundredLabelSymbol->Clone();
	pprojSymbol = m_pHundredLabelSymbol->Clone();

	/*vHundredLabelSymbol.SetTextSize( vHundredLabelSymbol.GetTextSize() - 2);
	projSymbol.SetTextSize( projSymbol.GetTextSize() - 1 );*/

	if(m_bVertTopBottom)
	{
		pvertLabelSym->SetAngle(PI/2);
		pvHundredLabelSymbol->SetAngle(PI/2);
		pprojSymbol->SetAngle(PI/2);
	}
	//绘制百公里以下
	if (m_bIsDrawKm)
	{
//		pDisplay->SetSymbol(&vertLabelSym);
		pDisplay->SetSymbol( pvertLabelSym.get() );
		pDisplay->Begin();
		for(int i=0; i<m_vecVerKmLabels.size(); i++)
			pDisplay->Draw(&m_vecVerKmLabels[i].first, m_vecVerKmLabels[i].second, TRUE);
		pDisplay->End();
	}
	
	//绘制百公里
	if ( m_bIsDrawHundredKm )
	{
		pDisplay->SetSymbol( pvHundredLabelSymbol.get() );
		pDisplay->Begin();
		for(int i=0; i<m_vecVerHundredKmLabels.size(); i++)
		{
			//只绘制图廓最近的公里线和整百公里位置的百公里数
			long nNum = m_vecVerticalLabel.size();
			if ( i == 0 
				|| i == nNum -1 
				|| i == nNum 
				|| i == nNum * 2 - 1
				|| m_vecVerHundredKmLabels[i].second == "00" )
			{
				pDisplay->Draw(&m_vecVerHundredKmLabels[i].first, m_vecVerHundredKmLabels[i].second, TRUE);
			}
		}
		pDisplay->End();
	}
	
	//绘制投影带号
	if ( m_bIsDrawProjStrapCode )
	{
		DIS_RECT textRect = CalculateTextSize( pDisplay, m_pTextSym.get(), "00" );
		pDisplay->SetSymbol( pprojSymbol.get() );
		pDisplay->Begin();
		for(int i=0; i<m_vecVerHundredKmLabels.size(); i++)
		{
			//只绘制图廓和整百公里位置的百公里数
			long nNum = m_vecVerticalLabel.size();
			if ( i == 0 
				|| i == nNum -1 
				|| i == nNum 
				|| i == nNum * 2 - 1
				|| m_vecVerHundredKmLabels[i].second == "00" )
			{
				//投影带号
				std::string szProjCode = CaculateProjStrapNode();
				//
				////位置
				GEOMETRY::geom::Envelope envVerHundredKmLabel = m_vecVerHundredKmLabels[i].first;
				GEOMETRY::geom::Envelope envWidth;
				pDisplay->GetDisplayTransformation().TransformToGeo( textRect, &envWidth );

				double dxoffset = envWidth.getWidth();
				GEOMETRY::geom::Envelope envProjStrap;
				envProjStrap.init( ( envVerHundredKmLabel.getMinX() + envVerHundredKmLabel.getMaxX() ) / 2 - dxoffset,
					( envVerHundredKmLabel.getMinX() + envVerHundredKmLabel.getMaxX() ) / 2 - dxoffset ,
					( envVerHundredKmLabel.getMinY() + envVerHundredKmLabel.getMaxY()) / 2,
					( envVerHundredKmLabel.getMinY() + envVerHundredKmLabel.getMaxY()) / 2 );

				pDisplay->Draw( &envProjStrap, szProjCode, TRUE);
			}
		}
		pDisplay->End();
	}
	/*----------------------水平线文字----------------------------*/
	phoriLabelSym = m_pTextSym->Clone();
	phHundredLabelSymbol = m_pHundredLabelSymbol->Clone();
	/*hHundredLabelSymbol.SetTextSize( hHundredLabelSymbol.GetTextSize() - 2);*/
	if(m_bVertLeftRight)
	{
		phoriLabelSym->SetAngle(PI/2);
		phHundredLabelSymbol->SetAngle(PI/2);
	}

	//绘制百公里以下
	if ( m_bIsDrawKm )
	{
		pDisplay->SetSymbol( phoriLabelSym.get() );
		pDisplay->Begin();
		for(int i=0; i<m_vecHorKmLabels.size(); i++)
			pDisplay->Draw(&m_vecHorKmLabels[i].first, m_vecHorKmLabels[i].second, TRUE);
		pDisplay->End();
	}
	
	//绘制百公里
	if ( m_bIsDrawHundredKm )
	{
		pDisplay->SetSymbol( phHundredLabelSymbol.get() );
		pDisplay->Begin();
		for(int i=0; i<m_vecHorHundredKmLabels.size(); i++)
		{
			//只绘制图廓和整百公里位置的百公里数
			long nNum = m_vecHorizontalLabel.size();
			if ( i == 0 
				|| i == nNum -1 
				|| i == nNum 
				|| i == nNum * 2 - 1
				|| m_vecHorHundredKmLabels[i].second == "00" )
			{
				pDisplay->Draw(&m_vecHorHundredKmLabels[i].first, m_vecHorHundredKmLabels[i].second, TRUE);
			}
		}
		pDisplay->End();
	}
}

void CStdMeasuredGrid::DrawBorder(Display::IDisplayPtr pDisplay)
{
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

void CStdMeasuredGrid::CalcGridLines(GEOMETRY::geom::Envelope& envGeo, GEOMETRY::geom::Envelope& envPage, double XOrigin, double YOrigin, 
									double XInterval, double YInterval, GEOMETRY::geom::Geometry*& pLines)
{
	stGridLabel gridLabel;
	m_vecVerticalLabel.clear();
	m_vecHorizontalLabel.clear();

	int nVerLineNum = (int)((envGeo.getMaxX()-XOrigin)/XInterval)+1;
	int nHorLineNum = (int)((envGeo.getMaxY()-YOrigin)/YInterval )+1;

	std::vector<GEOMETRY::geom::Geometry*> vecLines;
	GEOMETRY::geom::Geometry* pLine = NULL;
	GEOMETRY::geom::CoordinateSequence* coords = NULL;
	GEOMETRY::geom::Coordinate coordStart, coordEnd;

	double XIntervalPage = XInterval*envPage.getWidth()/envGeo.getWidth();
	double YIntervalPage = YInterval*envPage.getHeight()/envGeo.getHeight();
	double XOriginPage = envPage.getMinX() + (XOrigin-envGeo.getMinX())/envGeo.getWidth()*envPage.getWidth();
	double YOriginPage = envPage.getMinY() + (YOrigin-envGeo.getMinY())/envGeo.getHeight()*envPage.getHeight();

	if(pLines)
	{
		GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(pLines);
		pLines = NULL;
	}
	pLines =(Geometry*)GeometryFactory::getDefaultInstance()->createMultiLineString();


	//pVerticalLines
	for(int i=0; i<nVerLineNum; i++)
	{	
		//坐标（单位：地图坐标）
		gridLabel.geoCoordStart.x = XOrigin + XInterval*i;
		gridLabel.geoCoordStart.y = envGeo.getMinY();
		gridLabel.geoCoordEnd.x = XOrigin + XInterval*i;
		gridLabel.geoCoordEnd.y = envGeo.getMaxY();

		gridLabel.pageCoordStart.x = XOriginPage + XIntervalPage*i;
		gridLabel.pageCoordStart.y = m_envBorder.getMinY();
		gridLabel.pageCoordEnd.x = XOriginPage + XIntervalPage*i;
		gridLabel.pageCoordEnd.y = m_envBorder.getMaxY();

		m_vecVerticalLabel.push_back(gridLabel);

		//网格线（单位：制图页面坐标）
		coordStart.x = XOriginPage + XIntervalPage*i;
		coordStart.y = m_envBorder.getMinY();
		coordEnd.x = XOriginPage + XIntervalPage*i;
		coordEnd.y = m_envBorder.getMaxY();

		coords = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->getCoordinateSequenceFactory()->create(NULL);
		coords->add(coordStart);
		coords->add(coordEnd);

		pLine = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->createLineString(coords);
		((MultiLineString*)pLines)->AddGeometry(pLine);
	}

	
	//pHorizontalLines
	for(int i=0; i<nHorLineNum; i++)
	{
		//坐标（单位：地图坐标）
		gridLabel.geoCoordStart.x = envGeo.getMinX() ;
		gridLabel.geoCoordStart.y = YOrigin + YInterval*i;
		gridLabel.geoCoordEnd.x = envGeo.getMaxX();
		gridLabel.geoCoordEnd.y = YOrigin + YInterval*i;

		gridLabel.pageCoordStart.x = m_envBorder.getMinX();
		gridLabel.pageCoordStart.y = YOriginPage + YIntervalPage*i;
		gridLabel.pageCoordEnd.x = m_envBorder.getMaxX();
		gridLabel.pageCoordEnd.y = YOriginPage + YIntervalPage*i;

		m_vecHorizontalLabel.push_back(gridLabel);

		//网格线（单位：制图页面坐标）
		coordStart.x = m_envBorder.getMinX();
		coordStart.y = YOriginPage + YIntervalPage*i;
		coordEnd.x = m_envBorder.getMaxX();
		coordEnd.y = YOriginPage + YIntervalPage*i;

		coords = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->getCoordinateSequenceFactory()->create(NULL);
		coords->add(coordStart);
		coords->add(coordEnd);

		pLine = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->createLineString(coords);
		((MultiLineString*)pLines)->AddGeometry(pLine);
	}

	//生成多线几何图形
	/*if(pLines)
	{
		GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(pLines);
		pLines = NULL;
	}

	if(vecLines.size()>0)
		pLines = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->createMultiLineString(vecLines);

	for(int i=vecLines.size()-1; i>=0; i--)
	{
		GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(vecLines[i]);
	}
	vecLines.clear();*/
}

void CStdMeasuredGrid::CalcGridMarkers(GEOMETRY::geom::Envelope& envGeo, GEOMETRY::geom::Envelope& envPage, double XOrigin, double YOrigin, 
								 double XInterval, double YInterval, GEOMETRY::geom::Geometry*& pMarkers)
{
	stGridLabel gridLabel;
	m_vecVerticalLabel.clear();
	m_vecHorizontalLabel.clear();

	int nVerGeometryNum = (int)((envGeo.getMaxX()-XOrigin)/XInterval)+1;
	int nHorGeometryNum = (int)((envGeo.getMaxY()-YOrigin)/YInterval)+1;

	GEOMETRY::geom::CoordinateSequence* 	coords = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->getCoordinateSequenceFactory()->create(NULL);
	GEOMETRY::geom::Coordinate coord;

	double XIntervalPage = XInterval*envPage.getWidth()/envGeo.getWidth();
	double YIntervalPage = YInterval*envPage.getHeight()/envGeo.getHeight();
	double XOriginPage = envPage.getMinX() + (XOrigin-envGeo.getMinX())/envGeo.getWidth()*envPage.getWidth();
	double YOriginPage = envPage.getMinY() + (YOrigin-envGeo.getMinY())/envGeo.getHeight()*envPage.getHeight();
	
	//pVerticalLines
	for(int i=0; i<nVerGeometryNum; i++)
	{	
		//坐标（单位：地图坐标）
		gridLabel.geoCoordStart.x = XOrigin + XInterval*i;
		gridLabel.geoCoordStart.y = envGeo.getMinY();
		gridLabel.geoCoordEnd.x = XOrigin + XInterval*i;
		gridLabel.geoCoordEnd.y = envGeo.getMaxY();

		gridLabel.pageCoordStart.x = XOriginPage + XIntervalPage*i;
		gridLabel.pageCoordStart.y = envPage.getMinY();
		gridLabel.pageCoordEnd.x = XOriginPage + XIntervalPage*i;
		gridLabel.pageCoordEnd.y = envPage.getMaxY();

		m_vecVerticalLabel.push_back(gridLabel);

		//网格线（单位：制图页面坐标）
		for(int j=0; j<nHorGeometryNum; j++)
		{
			coord.x = XOriginPage + XIntervalPage*i;
			coord.y = YOriginPage + YIntervalPage*j;

			if(coord.x <= envPage.getMinX() || coord.x >= envPage.getMaxX() ||coord.y <= envPage.getMinY() || coord.y >= envPage.getMaxY())
				continue;

			coords->add(coord);
		}
	}

	//pHorizontalLines
	for(int i=0; i<nHorGeometryNum; i++)
	{
		//坐标（单位：地图坐标）
		gridLabel.geoCoordStart.x = envGeo.getMinX() ;
		gridLabel.geoCoordStart.y = YOrigin + YInterval*i;
		gridLabel.geoCoordEnd.x = envGeo.getMaxX();
		gridLabel.geoCoordEnd.y = YOrigin + YInterval*i;

		gridLabel.pageCoordStart.x = envPage.getMinX();
		gridLabel.pageCoordStart.y = YOriginPage + YIntervalPage*i;
		gridLabel.pageCoordEnd.x = envPage.getMaxX();
		gridLabel.pageCoordEnd.y = YOriginPage + YIntervalPage*i;

		m_vecHorizontalLabel.push_back(gridLabel);

		//网格线（单位：制图页面坐标）
		for(int j=0; j<nVerGeometryNum; j++)
		{
			coord.x = XOriginPage + XIntervalPage*j;
			coord.y = YOriginPage + YIntervalPage*i;
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

void CStdMeasuredGrid::CalLabels(Display::IDisplayPtr pDisplay, std::vector<stGridLabel>& vecVerticalLabel, std::vector<stGridLabel>& vecHorizontalLabel, 
			   std::vector<std::pair<GEOMETRY::geom::Envelope, std::string>>& vecVerLabels, std::vector<std::pair<GEOMETRY::geom::Envelope, std::string>>& vecHorLabels,
			   double labelOffset, Display::CTextSymbol* pVerticalTextSym, Display::CTextSymbol* pHorizontalTextSym, double tickSpacePage)
{
	int labelStep=1;

	char labelText[100];
	memset(labelText,0 , 100*sizeof(char));

	std::string hundredKmlabelText;

	std::string kmlabelText;

	/**
	/修改内容:添加 hundredKmRect kmRect, hundredKmRect和textRect
	/修改日期:2010-8-17
	*/
	DIS_RECT maxRect, hundredKmRect, kmRect, textRect;      
	GEOMETRY::geom::Envelope maxEnv, hundredKmEnv, kmEnv, textEnv;
	maxRect.left = maxRect.right = maxRect.top = maxRect.bottom = 0;

	GEOMETRY::geom::Coordinate coordLabelPos, coordLabelGeo;

	double x[2];
	int nFind = 0;

	//bottom
	if(m_bLabelBottom)
	{
		//计算最大的文字尺寸
		for(int i=0; i<vecVerticalLabel.size(); i++)
		{
			if(!vecVerticalLabel[i].bEndValid)
				continue;

			coordLabelGeo = vecVerticalLabel[i].geoCoordEnd;

			sprintf(labelText, "%d", (long)coordLabelGeo.x/1000 );
			textRect = CalculateTextSize(pDisplay, pVerticalTextSym, labelText);

			if(maxRect.Width()<textRect.Width())
				maxRect = textRect;
		}

		pDisplay->GetDisplayTransformation().TransformToGeo(maxRect, &maxEnv);		

		//计算互不重叠文字的间隔
		nFind = 0;
		for(int i=0; i<vecVerticalLabel.size(); i++)
		{
			if(nFind == 2)
				break;

			if( vecVerticalLabel[i].bStartValid)
			{
				x[nFind] = vecVerticalLabel[i].pageCoordStart.x;
				nFind++;
			}
		}

		if(nFind==2)
		{
			double interval = abs(x[1]- x[0]);
			if(maxEnv.getWidth()+4>interval)
				labelStep = (int)((maxEnv.getWidth()+4)/interval + 0.9999);
		}

		//保存文字
		for(int i=0; i<vecVerticalLabel.size(); i+=labelStep)
		{
			coordLabelGeo = vecVerticalLabel[i].geoCoordStart;
			coordLabelPos = vecVerticalLabel[i].pageCoordStart;
			sprintf(labelText, "%d", (long)coordLabelGeo.x/1000);

			//截取百位和百位以下公里数字符串
			std::string strtemp( labelText );
			long nLen = strtemp.size();
			if ( nLen < 1)
			{
				hundredKmlabelText = "00";
				kmlabelText = "00";
			}
			else if ( nLen == 1)
			{
				hundredKmlabelText = "00";
				kmlabelText = "0" + strtemp;
			}
			else if ( nLen == 2)
			{
				hundredKmlabelText = "00";
				kmlabelText = strtemp;
			}
			else if ( nLen == 3 )
			{
				hundredKmlabelText = "0" + strtemp.substr( 0, nLen - 2  );
				kmlabelText = strtemp.substr( nLen - 2, 2  );
			}
			else
			{
				hundredKmlabelText = strtemp.substr( 0, nLen - 2  );
				kmlabelText = strtemp.substr( nLen - 2, 2  );
			}
			
			textEnv.init(coordLabelPos.x/* - maxEnv.getWidth()/2*/, coordLabelPos.x/* + maxEnv.getWidth()/2*/, coordLabelPos.y - tickSpacePage - labelOffset - maxEnv.getHeight()/2, 
				coordLabelPos.y - tickSpacePage - labelOffset - maxEnv.getHeight()/2);

			hundredKmEnv.init( coordLabelPos.x - maxEnv.getWidth()/2*((double)( hundredKmlabelText.size() )/nLen ), 
				coordLabelPos.x - maxEnv.getWidth()/2*((double)( hundredKmlabelText.size() )/nLen ), 
				coordLabelPos.y - tickSpacePage - labelOffset + maxEnv.getHeight()/2, 
				coordLabelPos.y - tickSpacePage - labelOffset + maxEnv.getHeight()/2 );
			
			kmEnv.init( coordLabelPos.x + maxEnv.getWidth()/2, 
				coordLabelPos.x + maxEnv.getWidth()/2, 
				coordLabelPos.y - tickSpacePage - labelOffset + maxEnv.getHeight()/2, 
				coordLabelPos.y - tickSpacePage - labelOffset + maxEnv.getHeight()/2 );

			std::pair<GEOMETRY::geom::Envelope, std::string> label;
			
			label.first = textEnv;
			label.second = labelText;
			vecVerLabels.push_back( label );

			label.first = hundredKmEnv;
			label.second = hundredKmlabelText;
			m_vecVerHundredKmLabels.push_back( label );

			label.first = kmEnv;
			label.second = kmlabelText;
			m_vecVerKmLabels.push_back( label );
		}
	}
	

	//top
	if(m_bLabelTop)
	{
		maxRect.left = maxRect.right = maxRect.top = maxRect.bottom = 0;
		for(int i=0; i<vecVerticalLabel.size(); i++)
		{
			if(!vecVerticalLabel[i].bEndValid)
				continue;

			coordLabelGeo = vecVerticalLabel[i].geoCoordEnd;

			sprintf(labelText, "%d", (long)coordLabelGeo.x/1000 );
			textRect = CalculateTextSize(pDisplay, pVerticalTextSym, labelText);

			if(maxRect.Width()<textRect.Width())
				maxRect = textRect;
		}

		pDisplay->GetDisplayTransformation().TransformToGeo(maxRect, &maxEnv);	

		nFind = 0;
		for(int i=0; i<vecVerticalLabel.size(); i++)
		{
			if(nFind == 2)
				break;

			if( vecVerticalLabel[i].bEndValid)
			{
				x[nFind] = vecVerticalLabel[i].pageCoordEnd.x;
				nFind++;
			}
		}

		if(nFind==2)
		{
			double interval = abs(x[1]- x[0]);
			if(maxEnv.getWidth()+4>interval)
				labelStep = (int)((maxEnv.getWidth()+4)/interval + 0.9999);
		}

		for(int i=0; i<vecVerticalLabel.size(); i+=labelStep)
		{
			coordLabelGeo = vecVerticalLabel[i].geoCoordEnd;
			coordLabelPos = vecVerticalLabel[i].pageCoordEnd;
			sprintf(labelText, "%d", (long)coordLabelGeo.x/1000 );

			//截取百位和百位以下公里数字符串
			std::string strtemp( labelText );
			long nLen = strtemp.size();
			if ( nLen < 1)
			{
				hundredKmlabelText = "00";
				kmlabelText = "00";
			}
			else if ( nLen == 1)
			{
				hundredKmlabelText = "00";
				kmlabelText = "0" + strtemp;
			}
			else if ( nLen == 2)
			{
				hundredKmlabelText = "00";
				kmlabelText = strtemp;
			}
			else if ( nLen == 3 )
			{
				hundredKmlabelText = "0" + strtemp.substr( 0, nLen - 2  );
				kmlabelText = strtemp.substr( nLen - 2, 2  );
			}
			else
			{
				hundredKmlabelText = strtemp.substr( 0, nLen - 2  );
				kmlabelText = strtemp.substr( nLen - 2, 2  );
			}

			textEnv.init(coordLabelPos.x/* - maxEnv.getWidth()/2*/, coordLabelPos.x/* + maxEnv.getWidth()/2*/, 
				coordLabelPos.y + tickSpacePage + labelOffset + maxEnv.getHeight()/2, coordLabelPos.y + tickSpacePage + labelOffset + maxEnv.getHeight()/2);

			kmEnv.init( coordLabelPos.x + maxEnv.getWidth()/2,
				coordLabelPos.x + maxEnv.getWidth()/2,
				coordLabelPos.y + tickSpacePage + labelOffset - maxEnv.getHeight()/2, 
				coordLabelPos.y + tickSpacePage + labelOffset - maxEnv.getHeight()/2 );

			hundredKmEnv.init( coordLabelPos.x - maxEnv.getWidth()/2*((double)( hundredKmlabelText.size() )/nLen ),
				coordLabelPos.x - maxEnv.getWidth()/2*((double)( hundredKmlabelText.size() )/nLen ), 
				coordLabelPos.y + tickSpacePage + labelOffset - maxEnv.getHeight()/2, 
				coordLabelPos.y + tickSpacePage + labelOffset - maxEnv.getHeight()/2 );


			std::pair<GEOMETRY::geom::Envelope, std::string> label;

			label.first = textEnv;
			label.second = labelText;
			vecVerLabels.push_back( label );

			label.first = hundredKmEnv;
			label.second = hundredKmlabelText;
			m_vecVerHundredKmLabels.push_back( label );

			label.first = kmEnv;
			label.second = kmlabelText;
			m_vecVerKmLabels.push_back( label );
		}

	}
	
	//left
	double y[2];		
	if(m_bLabelLeft)
	{
		maxRect.left = maxRect.right = maxRect.top = maxRect.bottom = 0;
		for(int i=0; i<vecHorizontalLabel.size(); i++)
		{
			if(!vecHorizontalLabel[i].bStartValid)
				continue;

			coordLabelGeo = vecHorizontalLabel[i].geoCoordStart;

			sprintf(labelText, "%d", (long)coordLabelGeo.y/1000 );
			textRect = CalculateTextSize(pDisplay, pHorizontalTextSym, labelText);

			if(maxRect.Width()<textRect.Width())
				maxRect = textRect;
		}
		pDisplay->GetDisplayTransformation().TransformToGeo(maxRect, &maxEnv);	


		nFind = 0;
		for(int i=0; i<vecHorizontalLabel.size(); i++)
		{
			if(nFind == 2)
				break;

			if( vecHorizontalLabel[i].bStartValid)
			{
				y[nFind] = vecHorizontalLabel[i].pageCoordStart.y;
				nFind++;
			}
		}

		if(nFind==2)
		{
			double interval = abs(y[1]- y[0]);
			if(maxEnv.getHeight()+4>interval)
				labelStep = (int)((maxEnv.getHeight()+4)/interval + 0.9999);
		}

		for(int i=0; i<vecHorizontalLabel.size(); i+=labelStep)
		{
			coordLabelGeo = vecHorizontalLabel[i].geoCoordStart;
			coordLabelPos = vecHorizontalLabel[i].pageCoordStart;
			sprintf( labelText, "%d", (long)coordLabelGeo.y/1000 );
			
			//截取百位和百位以下公里数字符串
			std::string strtemp( labelText );
			long nLen = strtemp.size();
			if ( nLen < 1)
			{
				hundredKmlabelText = "00";
				kmlabelText = "00";
			}
			else if ( nLen == 1)
			{
				hundredKmlabelText = "00";
				kmlabelText = "0" + strtemp;
			}
			else if ( nLen == 2)
			{
				hundredKmlabelText = "00";
				kmlabelText = strtemp;
			}
			else if ( nLen == 3 )
			{
				hundredKmlabelText = "0" + strtemp.substr( 0, nLen - 2  );
				kmlabelText = strtemp.substr( nLen - 2, 2  );
			}
			else
			{
				hundredKmlabelText = strtemp.substr( 0, nLen - 2  );
				kmlabelText = strtemp.substr( nLen - 2, 2  );
			}

			textEnv.init(coordLabelPos.x - tickSpacePage - labelOffset - maxEnv.getWidth()/2 , coordLabelPos.x - tickSpacePage - labelOffset - maxEnv.getWidth()/2,
				coordLabelPos.y , coordLabelPos.y);
			
			hundredKmEnv.init( coordLabelPos.x - tickSpacePage - labelOffset + maxEnv.getWidth()/2 * ((double)( hundredKmlabelText.size() )/nLen), 
				coordLabelPos.x - tickSpacePage - labelOffset + maxEnv.getWidth()/2 * ((double)( hundredKmlabelText.size() )/nLen),
				coordLabelPos.y + maxEnv.getHeight()/2, 
				coordLabelPos.y + maxEnv.getHeight()/2 );
			
			/************************************************************************/
			//*左边计算百位以下数字位置比较特殊，需要考虑到不绘制百公里数字的情况
			/*日期:2010-09-18
			*/
			if ( ( i == 0 
				|| i == vecHorizontalLabel.size() - 1 
				|| kmlabelText == "00" ) 
				&& m_bIsDrawHundredKm  )
			{
				kmEnv.init( coordLabelPos.x - tickSpacePage - labelOffset + maxEnv.getWidth() * ((double)( hundredKmlabelText.size() )/nLen) + maxEnv.getWidth()/2*((double)( kmlabelText.size() )/nLen), 
					coordLabelPos.x - tickSpacePage - labelOffset + coordLabelPos.x - tickSpacePage - labelOffset + maxEnv.getWidth() * ((double)( hundredKmlabelText.size() )/nLen) + maxEnv.getWidth()/2*((double)( kmlabelText.size() )/nLen), 
					coordLabelPos.y + maxEnv.getHeight()/2,
					coordLabelPos.y + maxEnv.getHeight()/2 );
			}
			else
			{
				kmEnv.init( coordLabelPos.x - tickSpacePage - labelOffset + maxEnv.getWidth()/2 * ((double)( kmlabelText.size() )/nLen), 
					coordLabelPos.x - tickSpacePage - labelOffset + maxEnv.getWidth()/2 * ((double)( kmlabelText.size() )/nLen), 
					coordLabelPos.y + maxEnv.getHeight()/2,
					coordLabelPos.y + maxEnv.getHeight()/2 );
			}
			/************************************************************************/


			std::pair<GEOMETRY::geom::Envelope, std::string> label;

			label.first = textEnv;
			label.second = labelText;
			vecVerLabels.push_back( label );

			label.first = hundredKmEnv;
			label.second = hundredKmlabelText;
			m_vecHorHundredKmLabels.push_back( label );

			label.first = kmEnv;
			label.second = kmlabelText;
			m_vecHorKmLabels.push_back( label );
		}

	}

	if(m_bLabelRight)
	{
		//right
		maxRect.left = maxRect.right = maxRect.top = maxRect.bottom = 0;
		for(int i=0; i<vecHorizontalLabel.size(); i++)
		{
			if(!vecHorizontalLabel[i].bEndValid)
				continue;

			coordLabelGeo = vecHorizontalLabel[i].geoCoordEnd;

			sprintf(labelText, "%.d", (long)coordLabelGeo.y/1000 );
			textRect = CalculateTextSize(pDisplay, pHorizontalTextSym, labelText);

			if(maxRect.Width()<textRect.Width())
				maxRect = textRect;
		}
		pDisplay->GetDisplayTransformation().TransformToGeo(maxRect, &maxEnv);	

		nFind = 0;
		for(int i=0; i<vecHorizontalLabel.size(); i++)
		{
			if(nFind == 2)
				break;

			if( vecHorizontalLabel[i].bEndValid)
			{
				y[nFind] = vecHorizontalLabel[i].pageCoordEnd.y;
				nFind++;
			}
		}

		if(nFind==2)
		{
			double interval = abs(y[1]- y[0]);
			if(maxEnv.getHeight()+4>interval)
				labelStep = (int)((maxEnv.getHeight()+4)/interval + 0.9999);
		}

		for(int i=0; i<vecHorizontalLabel.size(); i+=labelStep)
		{
			coordLabelGeo = vecHorizontalLabel[i].geoCoordEnd;
			coordLabelPos = vecHorizontalLabel[i].pageCoordEnd;
			sprintf(labelText, "%d", (long)coordLabelGeo.y/1000 );

			//截取百位和百位以下公里数字符串
			std::string strtemp( labelText );
			long nLen = strtemp.size();
			if ( nLen < 1)
			{
				hundredKmlabelText = "00";
				kmlabelText = "00";
			}
			else if ( nLen == 1)
			{
				hundredKmlabelText = "00";
				kmlabelText = "0" + strtemp;
			}
			else if ( nLen == 2)
			{
				hundredKmlabelText = "00";
				kmlabelText = strtemp;
			}
			else if ( nLen == 3 )
			{
				hundredKmlabelText = "0" + strtemp.substr( 0, nLen - 2  );
				kmlabelText = strtemp.substr( nLen - 2, 2  );
			}
			else
			{
				hundredKmlabelText = strtemp.substr( 0, nLen - 2  );
				kmlabelText = strtemp.substr( nLen - 2, 2  );
			}

			textEnv.init(coordLabelPos.x + tickSpacePage + labelOffset + maxEnv.getWidth()/2 , coordLabelPos.x + tickSpacePage + labelOffset + maxEnv.getWidth()/2,
				coordLabelPos.y, coordLabelPos.y);

			hundredKmEnv.init(coordLabelPos.x + tickSpacePage + labelOffset - maxEnv.getWidth()*((double)( kmlabelText.size() )/nLen) - maxEnv.getWidth()/2 * ((double)( hundredKmlabelText.size() )/nLen), 
				coordLabelPos.x + tickSpacePage + labelOffset - maxEnv.getWidth()*((double)( kmlabelText.size() )/nLen) - maxEnv.getWidth()/2 * ((double)( hundredKmlabelText.size() )/nLen),
				coordLabelPos.y + maxEnv.getHeight()/2, 
				coordLabelPos.y + maxEnv.getHeight()/2 );

			kmEnv.init( coordLabelPos.x + tickSpacePage + labelOffset - maxEnv.getWidth()/2*((double)( kmlabelText.size() )/nLen),
				coordLabelPos.x + tickSpacePage + labelOffset - maxEnv.getWidth()/2*((double)( kmlabelText.size() )/nLen),
				coordLabelPos.y + maxEnv.getHeight()/2, 
				coordLabelPos.y + maxEnv.getHeight()/2 );

			std::pair<GEOMETRY::geom::Envelope, std::string> label;

			label.first = textEnv;
			label.second = labelText;
			vecVerLabels.push_back( label );

			label.first = hundredKmEnv;
			label.second = hundredKmlabelText;
			m_vecHorHundredKmLabels.push_back( label );

			label.first = kmEnv;
			label.second = kmlabelText;
			m_vecHorKmLabels.push_back( label );
		}
	}	
}

void CStdMeasuredGrid::RegulateOrigin(BOOL bDynamicXYOrg, double& XOrigin, double& YOrigin, double& XInterval, double& YInterval, GEOMETRY::geom::Envelope& Env)
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

std::string CStdMeasuredGrid::CaculateProjStrapNode()
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

bool CStdMeasuredGrid::GetProjStrapCodeVisible( void )
{
	return m_bIsDrawProjStrapCode;
}

void CStdMeasuredGrid::SetProjStrapCodeVisible( bool bVisible ) 
{
	m_bIsDrawProjStrapCode = bVisible; 
}

bool CStdMeasuredGrid::GetHundredKmVisible( void )
{ 
	return m_bIsDrawHundredKm; 
}
void CStdMeasuredGrid::SetHundredKmVisible( bool bVisible )
{
	m_bIsDrawHundredKm = bVisible;
}

bool CStdMeasuredGrid::GetKmVisible( void )
{
	return m_bIsDrawKm;
}

void CStdMeasuredGrid::SetKmVisible( bool bVisible )
{ 
	m_bIsDrawKm = bVisible;
}

Display::CTextSymbolPtr CStdMeasuredGrid::GetHundredLabelSymbol( void )
{ 
	return m_pHundredLabelSymbol;
}

void CStdMeasuredGrid::SetHundredLabelSymbol( Display::CTextSymbolPtr pTextSymbol )
{ 
	m_pHundredLabelSymbol = pTextSymbol;
	m_bLabelDirty = TRUE;
}

Display::CTextSymbolPtr CStdMeasuredGrid::GetProjLabelSymbol( void )
{ 
	return m_pProjStrapLabelSymbol;
}

void CStdMeasuredGrid::SetProjLabelSymbol( Display::CTextSymbolPtr pTextSymbol )
{
	m_pProjStrapLabelSymbol = pTextSymbol;
	m_bLabelDirty = TRUE;
}


}