#include "StdAfx.h"
#include "MeasuredGrid.h"
#include "MapFrame.h"

namespace Element{

CMeasuredGrid::CMeasuredGrid():IMapGrid()
{
	m_strGridName = "公里网格";
}
CMeasuredGrid::CMeasuredGrid(CMapFrame* pMapFrame)
{
	m_pMapFrame = pMapFrame;

	m_GridType = GT_MEASURED_GRID;

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


	m_strGridName = "公里网格";
}

CMeasuredGrid::~CMeasuredGrid(void)
{
}

void CMeasuredGrid::serialization(SYSTEM::IArchive &ar)
{
	IMapGrid::serialization(ar);
}

IGridPtr CMeasuredGrid::Clone()
{
	CMeasuredGrid* pClone = new CMeasuredGrid(m_pMapFrame);

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

	CMeasuredGridPtr pNewGrid(pClone);
	return pNewGrid;
}

void CMeasuredGrid::Draw(Display::IDisplayPtr pDisplay)
{
	IMapGrid::Draw(pDisplay);

	DrawBorder(pDisplay);
	DrawGrid(pDisplay);
	DrawTick(pDisplay);
	DrawLabel(pDisplay);
}

void CMeasuredGrid::DrawGrid(Display::IDisplayPtr pDisplay)
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

void CMeasuredGrid::DrawTick(Display::IDisplayPtr pDisplay)
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

void CMeasuredGrid::DrawSubTick(Display::IDisplayPtr pDisplay)
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

void CMeasuredGrid::DrawLabel(Display::IDisplayPtr pDisplay)
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
		

		CalLabels(pDisplay, m_vecVerticalLabel, m_vecHorizontalLabel,m_vecVerLabels, m_vecHorLabels, labelOffsetPage, &vertLabelSym, &horiLabelSym, tickSpacePage);
	
		m_bLabelDirty = FALSE;
	}

	if(!m_bLabelVisibility || !m_bActive)
		return;

	Display::CTextSymbol vertLabelSym, horiLabelSym; 

	//垂直线文字
	vertLabelSym = *m_pTextSym.get();
	if(m_bVertTopBottom)
		vertLabelSym.SetAngle(PI/2);

	pDisplay->SetSymbol(&vertLabelSym);

	pDisplay->Begin();

	for(int i=0; i<m_vecVerLabels.size(); i++)
		pDisplay->Draw(&m_vecVerLabels[i].first, m_vecVerLabels[i].second, TRUE);

	pDisplay->End();

	//水平线文字
	horiLabelSym = *m_pTextSym.get();
	if(m_bVertLeftRight)
		horiLabelSym.SetAngle(PI/2);

	pDisplay->SetSymbol(&horiLabelSym);

	pDisplay->Begin();

	for(int i=0; i<m_vecHorLabels.size(); i++)
		pDisplay->Draw(&m_vecHorLabels[i].first, m_vecHorLabels[i].second, TRUE);

	pDisplay->End();
}

void CMeasuredGrid::DrawBorder(Display::IDisplayPtr pDisplay)
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

void CMeasuredGrid::CalcGridLines(GEOMETRY::geom::Envelope& envGeo, GEOMETRY::geom::Envelope& envPage, double XOrigin, double YOrigin, 
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

void CMeasuredGrid::CalcGridMarkers(GEOMETRY::geom::Envelope& envGeo, GEOMETRY::geom::Envelope& envPage, double XOrigin, double YOrigin, 
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

void CMeasuredGrid::CalLabels(Display::IDisplayPtr pDisplay, std::vector<stGridLabel>& vecVerticalLabel, std::vector<stGridLabel>& vecHorizontalLabel, 
			   std::vector<std::pair<GEOMETRY::geom::Envelope, std::string>>& vecVerLabels, std::vector<std::pair<GEOMETRY::geom::Envelope, std::string>>& vecHorLabels,
			   double labelOffset, Display::CTextSymbol* pVerticalTextSym, Display::CTextSymbol* pHorizontalTextSym, double tickSpacePage)
{
	int labelStep=1;

	char labelText[100];
	memset(labelText,0 , 100*sizeof(char));

	DIS_RECT maxRect, textRect;
	GEOMETRY::geom::Envelope maxEnv, textEnv;
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
			if(!vecVerticalLabel[i].bStartValid)
				continue;

			coordLabelGeo = vecVerticalLabel[i].geoCoordStart;

			sprintf(labelText, "%.2f", coordLabelGeo.x);
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

			textEnv.init(coordLabelPos.x/* - maxEnv.getWidth()/2*/, coordLabelPos.x/* + maxEnv.getWidth()/2*/, coordLabelPos.y - tickSpacePage - labelOffset - maxEnv.getHeight()/2, 
				coordLabelPos.y - tickSpacePage - labelOffset - maxEnv.getHeight()/2);
			sprintf(labelText, "%.2f", coordLabelGeo.x);

			std::pair<GEOMETRY::geom::Envelope, std::string> label;
			label.first = textEnv;
			label.second = labelText;

			vecVerLabels.push_back(label);
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

			sprintf(labelText, "%.2f", coordLabelGeo.x);
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

			textEnv.init(coordLabelPos.x/* - maxEnv.getWidth()/2*/, coordLabelPos.x/* + maxEnv.getWidth()/2*/, 
				coordLabelPos.y + tickSpacePage + labelOffset + maxEnv.getHeight()/2, coordLabelPos.y + tickSpacePage + labelOffset + maxEnv.getHeight()/2);
			sprintf(labelText, "%.2f", coordLabelGeo.x);

			std::pair<GEOMETRY::geom::Envelope, std::string> label;
			label.first = textEnv;
			label.second = labelText;

			vecVerLabels.push_back(label);
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

			sprintf(labelText, "%.2f", coordLabelGeo.y);
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

			textEnv.init(coordLabelPos.x - tickSpacePage - labelOffset - maxEnv.getWidth()/2 , coordLabelPos.x - tickSpacePage - labelOffset - maxEnv.getWidth()/2,
				coordLabelPos.y , coordLabelPos.y);
			sprintf(labelText, "%.2f", coordLabelGeo.y);

			std::pair<GEOMETRY::geom::Envelope, std::string> label;
			label.first = textEnv;
			label.second = labelText;

			vecHorLabels.push_back(label);
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

			sprintf(labelText, "%.2f", coordLabelGeo.y);
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

			textEnv.init(coordLabelPos.x + tickSpacePage + labelOffset + maxEnv.getWidth()/2 , coordLabelPos.x + tickSpacePage + labelOffset + maxEnv.getWidth()/2,
				coordLabelPos.y, coordLabelPos.y);
			sprintf(labelText, "%.2f", coordLabelGeo.y);

			std::pair<GEOMETRY::geom::Envelope, std::string> label;
			label.first = textEnv;
			label.second = labelText;

			vecHorLabels.push_back(label);
		}
	}	
}

void CMeasuredGrid::RegulateOrigin(BOOL bDynamicXYOrg, double& XOrigin, double& YOrigin, double& XInterval, double& YInterval, GEOMETRY::geom::Envelope& Env)
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





}