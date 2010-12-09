#include "StdAfx.h"
#include "GraticuleGrid.h"
#include "MapFrame.h"
#include "AffineTransform.h"
//#include "TI_Project.h"

namespace Element{

static std::string TransformToGraticuleText(double graticule, GridLabelContent gridLabelContent)
{
	std::string strText;

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

	char labelText[100];
	memset(labelText,0 , 100*sizeof(char));

	if(gridLabelContent == GLC_D_M_S)
		sprintf(labelText, "%d°%d'%d\" ", deg, min, sec);
	else if(gridLabelContent == GLC_D_M)
		sprintf(labelText, "%d°%d'", deg, min);
	else if(gridLabelContent == GLC_D)
		sprintf(labelText, "%d°", deg);

	strText.append(labelText);
	return strText;
}

CGraticuleGrid::CGraticuleGrid():IMapGrid()
{
	m_strGridName = "经纬度网格";
}

CGraticuleGrid::CGraticuleGrid(CMapFrame* pMapFrame)
{
	m_pMapFrame = pMapFrame;

	m_gridLabelContent = GLC_D_M_S;

	m_GridType = GT_GRATICULE_GRID;
	
	m_XInterval = 0.01;
	m_YInterval = 0.01;

	m_strGridName = "经纬度网格";

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

CGraticuleGrid::~CGraticuleGrid(void)
{
}

void CGraticuleGrid::serialization(SYSTEM::IArchive &ar)
{
	IMapGrid::serialization(ar);

	if(ar.IsRead())
	{
		int content;
		ar & content;
		m_gridLabelContent = (GridLabelContent)content;
	}
	else
	{
		int content = (int)m_gridLabelContent;
		ar & content;
	}
}

void CGraticuleGrid::SetGridLabelContent(int enumGridLabelContent)
{
	m_gridLabelContent = (GridLabelContent)enumGridLabelContent;
}
int  CGraticuleGrid::GetGridLabelContent()
{
	return (int)m_gridLabelContent;
}



IGridPtr CGraticuleGrid::Clone()
{
	CGraticuleGrid* pClone = new CGraticuleGrid(m_pMapFrame);

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

	CGraticuleGridPtr pNewGrid(pClone);
	return pNewGrid;
}

void CGraticuleGrid::Draw(Display::IDisplayPtr pDisplay)
{
	IMapGrid::Draw(pDisplay);
	DrawBorder(pDisplay);
	DrawGrid(pDisplay);
	DrawTick(pDisplay);
	DrawSubTick(pDisplay);
	DrawLabel(pDisplay);
}

void CGraticuleGrid::DrawBorder(Display::IDisplayPtr pDisplay)
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

void CGraticuleGrid::DrawGrid(Display::IDisplayPtr pDisplay)
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
			affine.DynaProject(mapProj,cLLWkt,MapFrameGeoEnv);
			affine.Transform(MapFrameGeoEnv);
		}*/

		m_ActualXOrigin = m_XOrigin;
		m_ActualYOrigin = m_YOrigin;
		RegulateOrigin(m_bDynamicXYOrg, m_ActualXOrigin, m_ActualYOrigin, m_XInterval, m_YInterval, MapFrameGeoEnv);

		if(m_gridLineStyle == MGLS_LINE)
		{
			CalcGridLines(MapFrameGeoEnv, MapFramePageEnv, mapProj, cLLWkt, m_ActualXOrigin, m_ActualYOrigin, m_XInterval, m_YInterval, m_pLines);
		}
		else if(m_gridLineStyle == MGLS_MARKER)
		{
			CalcGridMarkers(MapFrameGeoEnv, MapFramePageEnv, mapProj, cLLWkt, m_ActualXOrigin, m_ActualYOrigin, m_XInterval, m_YInterval, m_pMarkers);
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

void CGraticuleGrid::DrawTick(Display::IDisplayPtr pDisplay)
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

void CGraticuleGrid::DrawSubTick(Display::IDisplayPtr pDisplay)
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

void CGraticuleGrid::DrawLabel(Display::IDisplayPtr pDisplay)
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
			vertLabelSym.SetAngle(PI/2);

		horiLabelSym = *m_pTextSym.get();
		if(m_bVertLeftRight)
			horiLabelSym.SetAngle(PI/2);

		m_vecVerLabels.clear();
		m_vecHorLabels.clear();

		CalLabels(pDisplay, m_vecVerticalLabel, m_vecHorizontalLabel,m_vecVerLabels, m_vecHorLabels, labelOffsetPage, 
			&vertLabelSym, &horiLabelSym, m_gridLabelContent, tickSpacePage);

		m_bLabelDirty = FALSE;
	}

	if(!m_bLabelVisibility|| !m_bActive)
		return;

	Display::CTextSymbol vertLabelSym, horiLabelSym; 

	vertLabelSym = *m_pTextSym.get();
	if(m_bVertTopBottom)
		vertLabelSym.SetAngle(3.1415926/2);

	pDisplay->SetSymbol(&vertLabelSym);

	pDisplay->Begin();

	for(int i=0; i<m_vecVerLabels.size(); i++)
		pDisplay->Draw(&m_vecVerLabels[i].first, m_vecVerLabels[i].second, TRUE);

	pDisplay->End();


	horiLabelSym = *m_pTextSym.get();
	if(m_bVertLeftRight)
		horiLabelSym.SetAngle(3.1415926/2);

	pDisplay->SetSymbol(&horiLabelSym);

	pDisplay->Begin();

	for(int i=0; i<m_vecHorLabels.size(); i++)
		pDisplay->Draw(&m_vecHorLabels[i].first, m_vecHorLabels[i].second, TRUE);

	pDisplay->End();
}

void CGraticuleGrid::RegulateOrigin(BOOL bDynamicXYOrg, double& XOrigin, double& YOrigin, double& XInterval, double& YInterval, GEOMETRY::geom::Envelope& Env)
{
	if(bDynamicXYOrg)
	{

	}
	else
	{
		if(XOrigin - Env.getMinX()> 0.000001)
		{
			while(XOrigin>Env.getMinX()+ XInterval)
				XOrigin -= XInterval;
		}
		else if(Env.getMinX() - XOrigin > 0.000001)
		{
			while(XOrigin<Env.getMinX())
				XOrigin += XInterval;
		}

		if(YOrigin - Env.getMinY() > 0.000001)
		{
			while(YOrigin>Env.getMinY()+ YInterval)
				YOrigin -= YInterval;
		}
		else if(Env.getMinY()-YOrigin > 0.000001)
		{
			while(YOrigin<Env.getMinY())
				YOrigin += YInterval;
		}
	}
}

void CGraticuleGrid::CalcGridLines(GEOMETRY::geom::Envelope& envGeo, GEOMETRY::geom::Envelope& envPage, std::string strMapProj, std::string strLLProj, double XOrigin, double YOrigin, 
									double XInterval, double YInterval, GEOMETRY::geom::Geometry*& pLines)
{
	int nLonLineNum = (int)((envGeo.getMaxX()-XOrigin)/XInterval + 0.5);
	int nLatLineNum = (int)((envGeo.getMaxY()-YOrigin)/YInterval + 0.5);

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
	for(int i=0; i<nLonLineNum; i++)
	{		
		coords = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->getCoordinateSequenceFactory()->create(NULL);
		for(int j=0; j<nSampleCoordsNum; j++)
		{	
			//逆投影
			coord.x = XOrigin + XInterval*i;
			if(j==nSampleCoordsNum-1)
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
	}

	//latLines
	for(int i=0; i<nLatLineNum; i++)
	{
		coords = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->getCoordinateSequenceFactory()->create(NULL);
		for(int j=0; j<nSampleCoordsNum; j++)
		{
			//逆投影
			if(j==nSampleCoordsNum-1)
				coord.x = envGeo.getMaxX();
			else
				coord.x = XOrigin + (double)j * (envGeo.getMaxX()-XOrigin) /(double)nSampleCoordsNum;
			
			coord.y = YOrigin + YInterval*i;
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
	}

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

void CGraticuleGrid::CalcGridMarkers(GEOMETRY::geom::Envelope& envGeo, GEOMETRY::geom::Envelope& envPage, std::string strMapProj, std::string strLLProj, double XOrigin, double YOrigin, 
							  double XInterval, double YInterval, GEOMETRY::geom::Geometry*& pMarkers)
{
	int nLonLineNum = (int)((envGeo.getMaxX()-XOrigin)/XInterval)+1;
	int nLatLineNum = (int)((envGeo.getMaxY()-YOrigin)/YInterval)+1;

	GEOMETRY::geom::CoordinateSequence* coords = NULL;
	GEOMETRY::geom::Coordinate coord;

	stGridLabel gridLabel;
	double XOriginPage = envPage.getMinX() + (XOrigin-envGeo.getMinX())/envGeo.getWidth()*envPage.getWidth();
	double YOriginPage = envPage.getMinY() + (YOrigin-envGeo.getMinY())/envGeo.getHeight()*envPage.getHeight();
	m_vecHorizontalLabel.clear();
	m_vecVerticalLabel.clear();

	coords = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->getCoordinateSequenceFactory()->create(NULL);

	//lonlines
	for(int i=0; i<nLonLineNum; i++)
	{		
		for(int j=0; j<nLatLineNum; j++)
		{	
			coord.x = XOrigin + XInterval*i;
			coord.y = YOrigin + YInterval*j;

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
	for(int i=0; i<nLatLineNum; i++)
	{
		for(int j=0; j<nLonLineNum; j++)
		{
			coord.x = XOrigin + XInterval*j;
			coord.y = YOrigin + YInterval*i;

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

void CGraticuleGrid::CalLabels(Display::IDisplayPtr pDisplay, std::vector<stGridLabel>& vecVerticalLabel, std::vector<stGridLabel>& vecHorizontalLabel, 
							  std::vector<std::pair<GEOMETRY::geom::Envelope, std::string>>& vecVerLabels, std::vector<std::pair<GEOMETRY::geom::Envelope, std::string>>& vecHorLabels,
							  double labelOffset, Display::CTextSymbol* pVerticalTextSym, Display::CTextSymbol* pHorizontalTextSym, GridLabelContent gridLabelContent, double tickSpacePage)
{

	int labelStep=1;//label绘制的间隔
	DIS_RECT maxRect, textRect;
	GEOMETRY::geom::Envelope maxEnv, textEnv;
	maxRect.left = maxRect.right = maxRect.top = maxRect.bottom = 0;

	GEOMETRY::geom::Coordinate coordLabelPos, coordLabelGeo;

	double x[2];
	int nFind = 0;

	std::string strLabel;

	//bottom
	if(m_bLabelBottom)
	{
		for(int i=0; i<vecVerticalLabel.size(); i++) //计算最大的rect
		{
			if(!vecVerticalLabel[i].bStartValid)
				continue;

			coordLabelGeo = vecVerticalLabel[i].geoCoordStart;

			strLabel = TransformToGraticuleText(coordLabelGeo.x, gridLabelContent);

			textRect = CalculateTextSize(pDisplay, pVerticalTextSym, strLabel);

			if(maxRect.Width()<textRect.Width())
				maxRect = textRect;
		}

		pDisplay->GetDisplayTransformation().TransformToGeo(maxRect, &maxEnv);	

		//计算是否需要调整间距（如果当前线上只有一个label，则不需要调整）
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
			if(maxEnv.getWidth()+ 4>interval)
				labelStep = (int)((maxEnv.getWidth()+4)/interval + 0.9999);
		}

		//保存调整间距后的label
		for(int i=0; i<vecVerticalLabel.size(); i+=labelStep)
		{
			coordLabelGeo = vecVerticalLabel[i].geoCoordStart;
			coordLabelPos = vecVerticalLabel[i].pageCoordStart;

			textEnv.init(coordLabelPos.x/* - maxEnv.getWidth()/2*/, coordLabelPos.x/* + maxEnv.getWidth()/2*/, coordLabelPos.y - tickSpacePage - labelOffset - maxEnv.getHeight()/2, 
				coordLabelPos.y - tickSpacePage - labelOffset - maxEnv.getHeight()/2);

			strLabel = TransformToGraticuleText(coordLabelGeo.x, gridLabelContent);

			std::pair<GEOMETRY::geom::Envelope, std::string> label;
			label.first = textEnv;
			label.second = strLabel;

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

			strLabel = TransformToGraticuleText(coordLabelGeo.x, gridLabelContent);
			textRect = CalculateTextSize(pDisplay, pVerticalTextSym, strLabel);

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
			strLabel = TransformToGraticuleText(coordLabelGeo.x, gridLabelContent);

			std::pair<GEOMETRY::geom::Envelope, std::string> label;
			label.first = textEnv;
			label.second = strLabel;

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

			strLabel = TransformToGraticuleText(coordLabelGeo.y, gridLabelContent);
			textRect = CalculateTextSize(pDisplay, pHorizontalTextSym, strLabel);

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
			strLabel = TransformToGraticuleText(coordLabelGeo.y, gridLabelContent);

			std::pair<GEOMETRY::geom::Envelope, std::string> label;
			label.first = textEnv;
			label.second = strLabel;

			vecHorLabels.push_back(label);
		}

	}
	

	//right
	if(m_bLabelRight)
	{
		maxRect.left = maxRect.right = maxRect.top = maxRect.bottom = 0;
		for(int i=0; i<vecHorizontalLabel.size(); i++)
		{
			if(!vecHorizontalLabel[i].bEndValid)
				continue;

			coordLabelGeo = vecHorizontalLabel[i].geoCoordEnd;

			strLabel = TransformToGraticuleText(coordLabelGeo.y, gridLabelContent);
			textRect = CalculateTextSize(pDisplay, pHorizontalTextSym, strLabel);

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

			strLabel = TransformToGraticuleText(coordLabelGeo.y, gridLabelContent);

			std::pair<GEOMETRY::geom::Envelope, std::string> label;
			label.first = textEnv;
			label.second = strLabel;

			vecHorLabels.push_back(label);
		}
	}
	
}

}