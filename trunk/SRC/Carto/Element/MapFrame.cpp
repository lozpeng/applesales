#include "StdAfx.h"
#include "MapFrame.h"
#include "Legend.h"
#include "MarkerNorthArrow.h"
#include "DistrictRelationTable.h"
#include "ScaleLine.h"
#include "AlternatingScaleBar.h"
#include "MapTitle.h"
#include "NeatLIne.h"
#include "MapGrids.h"
#include "MeasuredGrid.h"
#include "EnvelopeTracker.h"

#include <boost/function.hpp>
#include <boost/bind.hpp>

namespace Element{

static boost::signal<void (CMapFrame*)> gCallbackMapFrameProperChanged;

static boost::signal<void (CMapFrame*)> gCallbackMapFrameMapSetted;

CMapFrame::CMapFrame():IFrameElementBase()
{
	m_enumElementType = ET_MAP_FRAME_ELEMENT;

	m_bMapProperChanged = TRUE;

	m_bNewMapScale = FALSE;

	m_bNewFixViewExtent = FALSE;

	CMeasuredGridPtr pNewGrid(new CMeasuredGrid());

	pNewGrid->SetGridActive(FALSE);

	m_Grids.AddMapGrid(pNewGrid);

	m_pSelectionHandle.reset(new CEnvelopeTracker(GEOMETRY::geom::Envelope(0,0,0,0), HT_EIGHT));


	boost::function<void (Carto::CMap*)> funmem = boost::bind(&CMapFrame::CallbackMapExtentModeChangedFun,this, _1);

	m_ConnectionMapExtentModeChange = Carto::CMap::RegisterChangeMapExtentMode(funmem);

	boost::function<void (Carto::CMap*)> funmp = boost::bind(&CMapFrame::CallbackMapRedrawedFun,this, _1);

	m_ConnectionMapRedrawed = Carto::CMap::RegisterMapReDrawed(funmp);

	boost::function<void (Display::VIEW_POSITION)> funvc = boost::bind(&CMapFrame::CallbackViewPosChange,this, _1);

	m_ConnectionViewChange = Display::CDisplayTransformation::RegisterChangeViewPos(funvc);
}

CMapFrame::CMapFrame(const GEOMETRY::geom::Geometry& geometry, Carto::CMapPtr pGeoMap):IFrameElementBase(geometry)
{
	m_bStandardMap = FALSE;

	m_pGeoMap = pGeoMap;

	m_enumElementType = ET_MAP_FRAME_ELEMENT;

	m_bDrawBorder = TRUE;

	m_bNewFixViewExtent = FALSE;

	m_bNewMapScale = FALSE;

	m_pSelectionHandle.reset(new CEnvelopeTracker(*geometry.getEnvelopeInternal(), HT_EIGHT));


	m_bMapProperChanged = TRUE;

	CMeasuredGridPtr pNewGrid(new CMeasuredGrid(this));

	pNewGrid->SetGridActive(FALSE);

	m_Grids.AddMapGrid(pNewGrid);

	boost::function<void (Carto::CMap*)> funmem = boost::bind(&CMapFrame::CallbackMapExtentModeChangedFun,this, _1);

	m_ConnectionMapExtentModeChange = Carto::CMap::RegisterChangeMapExtentMode(funmem);

	boost::function<void (Carto::CMap*)> funmp = boost::bind(&CMapFrame::CallbackMapRedrawedFun,this, _1);

	m_ConnectionMapRedrawed = Carto::CMap::RegisterMapReDrawed(funmp);

	boost::function<void (Display::VIEW_POSITION)> funvc = boost::bind(&CMapFrame::CallbackViewPosChange,this, _1);

	m_ConnectionViewChange = Display::CDisplayTransformation::RegisterChangeViewPos(funvc);

}

CMapFrame::~CMapFrame(void)
{	
	m_ConnectionMapExtentModeChange.disconnect();

	m_ConnectionViewChange.disconnect();

	m_ConnectionMapRedrawed.disconnect();
}

void CMapFrame::serialization(SYSTEM::IArchive &ar)
{
	IFrameElementBase::serialization(ar);

	m_Grids.serialization(ar);

	long id;
	if(ar.IsRead())
	{
		ar & id;

		m_mapID = id;

		for(int i=0; i<m_Grids.GetGridCount(); i++)
			m_Grids.GetMapGrid(i)->SetMapFrame(this);
	}
	else
	{
		id = m_pGeoMap->GetID();
		ar & id;
	}

	ar & m_MapFrameID;

	ar & m_bStandardMap;

	ar & m_dbMapScale;

	ar & m_coordLeftBottom.x;

	ar & m_coordLeftBottom.y;

}




long CMapFrame::GetMapID()
{
	return m_mapID;
}

void CMapFrame::SetMap(Carto::CMapPtr pMap)
{
	m_pGeoMap = pMap;

	m_mapID = pMap->GetID();

	gCallbackMapFrameMapSetted(this);
}

Carto::CMapPtr CMapFrame::GetMap()
{
	return m_pGeoMap;
}

CMapGrids&	CMapFrame::GetMapGrids()
{
	return m_Grids;
}

IMapSurroundPtr CMapFrame::CreateMapSurroundElement(ELEMENT_TYPE enumElementType)
{
	IMapSurroundPtr pMapSurround = NULL; 

	switch(enumElementType)
	{
	case ET_MARKER_NORTH_ARROW:
		{
			GEOMETRY::geom::Geometry* pGeometry = m_pGeometry->getCentroid();	
			pMapSurround.reset(new CMarkerNorthArrow(*pGeometry, this));
			GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(pGeometry);
		}
		break;
	case ET_SCALELINE:
		{
			GEOMETRY::geom::Coordinate center;
			GEOMETRY::geom::Geometry* pGeometry = NULL;
			m_pGeometry->getCentroid( center);
			pGeometry = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->toGeometry(&GEOMETRY::geom::Envelope(center.x-40, center.x+40, center.y-10, center.y+10));	
			pMapSurround.reset(new CScaleLine(*pGeometry, this));
			GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(pGeometry);
		}		
		break;
	case ET_ALTERNATING_SCALEBAR:
		{
			GEOMETRY::geom::Coordinate center;
			GEOMETRY::geom::Geometry* pGeometry = NULL;
			m_pGeometry->getCentroid( center);
			pGeometry = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->toGeometry(&GEOMETRY::geom::Envelope(center.x-40, center.x+40, center.y-10, center.y+10));	
			pMapSurround.reset(new CAlternatingScaleBar(*pGeometry, this));
			GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(pGeometry);
		}		
		break;
		
	case ET_LEGEND:
		{
			GEOMETRY::geom::Coordinate center;
			GEOMETRY::geom::Geometry* pGeometry = NULL;
			m_pGeometry->getCentroid( center);
			pGeometry = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->toGeometry(&GEOMETRY::geom::Envelope(center.x-1, center.x+1, center.y-1, center.y+1));	
			pMapSurround.reset(new CLegend(*pGeometry, this));
			GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(pGeometry);
		}
		break;
	case ET_MAP_TITLE:
		{
			GEOMETRY::geom::Coordinate center;
			GEOMETRY::geom::Geometry* pGeometry = NULL;
			m_pGeometry->getCentroid( center);
			pGeometry = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->toGeometry(&GEOMETRY::geom::Envelope(center.x-1, center.x+1, center.y-1, center.y+1));	
			pMapSurround.reset(new CMapTitle(*pGeometry, this));
			GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(pGeometry);
		}
		break;
	case ET_RELATIONDISTRICT_TABLE:
		{
			GEOMETRY::geom::Coordinate center;
			GEOMETRY::geom::Geometry* pGeometry = NULL;
			m_pGeometry->getCentroid( center);
			pGeometry = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->toGeometry(&GEOMETRY::geom::Envelope(center.x-1, center.x+1, center.y-1, center.y+1));	
			pMapSurround.reset(new CDistrictRelationTable(*pGeometry, this));
			GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(pGeometry);
		}
		break;
	case ET_NEAT_LINE:
		{
			GEOMETRY::geom::Envelope env = GetEnvelope();
			const GEOMETRY::geom::Envelope *envBorder = m_pBorder->GetGeometry()->getEnvelopeInternal();
			const GEOMETRY::geom::Envelope *envShadow = m_pShadow->GetGeometry()->getEnvelopeInternal();
			const GEOMETRY::geom::Envelope *envBackground = m_pBackground->GetGeometry()->getEnvelopeInternal();
			env.expandToInclude(envBorder);
			env.expandToInclude(envShadow);
			env.expandToInclude(envBackground);

			env.expandBy(env.getWidth()/50);
			
			GEOMETRY::geom::Geometry* pGeometry = NULL;
			pGeometry = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->toGeometry(&env);	
			pMapSurround.reset(new CNeatLine(*pGeometry, this));
			GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(pGeometry);
		}
		break;
	default:
		break;
	}

	return pMapSurround;
}



void CMapFrame::GeometryChangedEvents()
{
	m_bMapProperChanged = TRUE;
	IFrameElementBase::GeometryChangedEvents();
}

//////////////////////////////////////////////////////////////////////////

void CMapFrame::DrawNormal(Display::IDisplayPtr pDisplay)
{
	UpdateMapFrame(pDisplay);

	//绘制
	DrawBackground(pDisplay);

	DrawMap(pDisplay);

	DrawGrids(pDisplay);

	DrawForeground(pDisplay);
}


void CMapFrame::DrawMap(Display::IDisplayPtr pDisplay)
{
	if(!m_pGeoMap)
		return;

	//将map贴到pDisplay的dc上
	if(pDisplay->GetPrinting())
	{
		DIS_BOUND bakBound = m_pGeoMap->GetDisplay()->GetDisplayTransformation().GetViewBound();
		DIS_BOUND *rect = pDisplay->GetDisplayTransformation().TransformToDisplayBound(m_pGeometry->getEnvelopeInternal());
		GEOMETRY::geom::Envelope mapViewEnv = m_pGeoMap->GetViewEnvelope();
		m_pGeoMap->SetViewBound(*rect);
		m_pGeoMap->GetDisplay()->GetDisplayTransformation().FitViewBound(mapViewEnv);

		//绘制map
		Display::CDC*pDrawDC = m_pGeoMap->GetDisplay()->GetDrawDC();
		long bakWidth = pDrawDC->GetDCWidth();
		long bakHeight = pDrawDC->GetDCHeight();
		long bakHDC = pDrawDC->GetSafeHdc();

		Display::CDC*pPrintDC = pDisplay->GetDrawDC();
		long printWidth = pPrintDC->GetDCWidth();
		long printHeight = pPrintDC->GetDCHeight();
		long printHDC = pPrintDC->GetSafeHdc();

		pDrawDC->SetDC(printHDC, printWidth, printHeight);
		m_pGeoMap->GetDisplay()->SetPrinting(TRUE);
		m_pGeoMap->Draw(drawAll);

		pDrawDC->SetDC(bakHDC, bakWidth, bakHeight);
		m_pGeoMap->GetDisplay()->SetPrinting(FALSE);
		m_pGeoMap->SetViewBound(bakBound);

		FreeDisplayObj(rect);
	}
	else
	{
		DIS_RECT *rect = pDisplay->GetDisplayTransformation().TransformToDisplay(m_pGeometry->getEnvelopeInternal());

		Display::CDC *pLayoutDC = pDisplay->GetDrawDC();

		Display::CDC *pMapDC = m_pGeoMap->GetDisplay()->GetDrawDC();


	/*	BitBlt((HDC)pLayoutDC->GetSafeHdc(), rect->left, rect->top, rect->Width(), rect->Height(),
			(HDC)pMapDC->GetSafeHdc(), 0,0,SRCCOPY);*/

		BitBlt((HDC)pLayoutDC->GetSafeHdc(), m_drawBound.left, m_drawBound.top, m_drawBound.Width(), m_drawBound.Height(),
		(HDC)pMapDC->GetSafeHdc(), 0,0,SRCCOPY);

		FreeDisplayObj(rect);


	}
	
	
}

void CMapFrame::DrawGrids(Display::IDisplayPtr pDisplay)
{
	for(int i=0; i<m_Grids.GetGridCount(); i++)
		m_Grids.GetMapGrid(i)->Draw(pDisplay);
}

void CMapFrame::UpdateMapFrame(Display::IDisplayPtr pDisplay)
{
	if(m_bNewFixViewExtent && m_pGeoMap->GetExtentMode() == Carto::EEM_FIX_EXTENT)
	{
		GEOMETRY::geom::Envelope mapViewExtent = m_pGeoMap->GetViewEnvelope();
		GEOMETRY::geom::Envelope MapFrameEnv = *(m_pGeometry->getEnvelopeInternal());
		double unitRatio = SYSTEM::UnitConverter::ConvertUnits(1,m_pGeoMap->GetDisplay()->GetDisplayTransformation().GetUnit(), pDisplay->GetDisplayTransformation().GetUnit() );
		double mapViewWidthPage = mapViewExtent.getWidth()/m_dbMapScale*unitRatio;
		double mapViewHeightPage = mapViewExtent.getHeight()/m_dbMapScale*unitRatio;
		MapFrameEnv.init(MapFrameEnv.getMinX(), MapFrameEnv.getMinX()+mapViewWidthPage, MapFrameEnv.getMinY(), MapFrameEnv.getMinY()+mapViewHeightPage);
	
		GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(m_pGeometry);
		m_pGeometry = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->toGeometry(&MapFrameEnv);
		GeometryChangedEvents();

		m_bNewFixViewExtent = FALSE;
	}

	if(m_bMapProperChanged) //|| m_bFrameChanged
	{
		ReDrawMap(pDisplay);

		ReCalcMapToPageScale(pDisplay);

		ReCalcGrid();

		gCallbackMapFrameProperChanged(this);
	}

	SetMapFrameDirty(FALSE);
}


//重绘map
void CMapFrame::ReDrawMap(Display::IDisplayPtr pDisplay)
{
	ReCalcMapToPageScale(pDisplay);
	m_pGeoMap->SetFramePageScale(pDisplay->GetDisplayTransformation().GetMapScale(), m_dbMapScale);

	DIS_BOUND *frameBound = pDisplay->GetDisplayTransformation().TransformToDisplayBound(m_pGeometry->getEnvelopeInternal());

	////更新Frame内地图范围的大小
	DIS_BOUND frmBnd;
	frmBnd.left = 0;
	frmBnd.right = frameBound->Width();
	frmBnd.top = 0;
	frmBnd.bottom = frameBound->Height();

	m_pGeoMap->SetViewBound(frmBnd);

	//更新可视范围
	DIS_BOUND screenBound = pDisplay->GetDisplayTransformation().GetViewBound();
	m_drawBound.left = frameBound->left > screenBound.left ? frameBound->left : screenBound.left;
	m_drawBound.right = frameBound->right < screenBound.right ? frameBound->right : screenBound.right;
	m_drawBound.top = frameBound->top > screenBound.top ? frameBound->top : screenBound.top;
	m_drawBound.bottom = frameBound->bottom < screenBound.bottom ? frameBound->bottom : screenBound.bottom;

	DIS_BOUND drawBound;
	drawBound.left = m_drawBound.left - frameBound->left;
	drawBound.right = drawBound.left + m_drawBound.Width();
	drawBound.top = m_drawBound.top - frameBound->top;
	drawBound.bottom = drawBound.top + m_drawBound.Height();

	m_pGeoMap->SetDrawBound(drawBound);

	//绘制map
	m_pGeoMap->Draw(drawAll);
	m_pGeoMap->GetDisplay()->SetDrawBuffer(drawAll);
	m_pGeoMap->GetDisplay()->DrawBackgroud();
	m_pGeoMap->GetDisplay()->RefreshDisplay(drawAll);

	m_pGeoMap->SetDrawBound(frmBnd, TRUE);

	FreeDisplayObj(frameBound);

	
}

void CMapFrame::ReCalcMapToPageScale(Display::IDisplayPtr pDisplay)
{
	double bb=m_pGeoMap->GetDisplay()->GetDisplayTransformation().GetMapScale();
	m_dbMapScale = m_pGeoMap->GetDisplay()->GetDisplayTransformation().GetMapScale()/pDisplay->GetDisplayTransformation().GetMapScale();
}

void CMapFrame::ReCalcGrid()
{
	for(int i=0; i<m_Grids.GetGridCount(); i++)
	{
		//map与layout切换时出错，grid如果未激活就不执行下面语句
		if(m_Grids.GetMapGrid(i)->GetGridActive())
			m_Grids.GetMapGrid(i)->SetRecalcGrid();
	}
}



////属性编辑//////////////////////////////////////////////////////////////////////
void CMapFrame::SetViewExtAutoMode()
{
	m_pGeoMap->SetExtentMode(Carto::EEM_AUTO);
	
	SetWHRatioMode(EWHR_FREE_RATIO);
		

	m_bMapProperChanged = TRUE;
}

void CMapFrame::SetViewExtFixScaleMode(double dbMapScale, GEOMETRY::geom::Coordinate coordLeftBottom)
{
	m_pGeoMap->SetExtentMode(Carto::EEM_FIX_SCALE);
	m_pGeoMap->m_dbMapFixScale = dbMapScale;

	//更新地图比例尺
	double dbOldMapScale = m_pGeoMap->GetDisplay()->GetDisplayTransformation().GetMapScale();
	m_pGeoMap->GetDisplay()->GetDisplayTransformation().SetMapScale(dbOldMapScale*dbMapScale/m_dbMapScale);
	m_dbMapScale = dbMapScale;	

	//更新地图可视范围，保持尺寸不变
	GEOMETRY::geom::Envelope env;
	m_pGeoMap->GetDisplay()->GetDisplayTransformation().GetGeoBound(env);
	env.init(coordLeftBottom.x, coordLeftBottom.x+env.getWidth(), coordLeftBottom.y, coordLeftBottom.y+env.getHeight());
	m_pGeoMap->SetViewEnvelope(env);
	m_pGeoMap->GetDisplay()->GetDisplayTransformation().FitViewBound(env);

	SetWHRatioMode(EWHR_FREE_RATIO);

	m_bMapProperChanged = TRUE;
}

void CMapFrame::SetViewExtFixExtentMode(GEOMETRY::geom::Envelope viewExtent)
{
	m_pGeoMap->SetExtentMode(Carto::EEM_FIX_EXTENT);
	m_pGeoMap->SetViewEnvelope(viewExtent);

	SetWHRatioMode(EWHR_FIX_RATIO);

	m_bNewFixViewExtent = TRUE;
	m_bMapProperChanged = TRUE;
}

GEOMETRY::geom::Envelope CMapFrame::GetViewEnvelope()
{
	GEOMETRY::geom::Envelope env;
	m_pGeoMap->GetDisplay()->GetDisplayTransformation().GetGeoBound(env);
	return env;
}

void CMapFrame::SetMapToPageScale(double scale)
{
	m_pGeoMap->m_dbMapFixScale = scale;

	//更新地图比例尺
	double dbOldMapScale = m_pGeoMap->GetDisplay()->GetDisplayTransformation().GetMapScale();
	m_pGeoMap->GetDisplay()->GetDisplayTransformation().SetMapScale(dbOldMapScale*scale/m_dbMapScale);
	m_dbMapScale = scale;	

	//更新地图可视范围，保持尺寸不变
	GEOMETRY::geom::Envelope env;
	m_pGeoMap->GetDisplay()->GetDisplayTransformation().GetGeoBound(env);
	m_pGeoMap->SetViewEnvelope(env);
	m_pGeoMap->GetDisplay()->GetDisplayTransformation().FitViewBound(env);

	m_bMapProperChanged = TRUE;
}

double	CMapFrame::GetMapToPageScale()
{
	return m_dbMapScale;
}

void CMapFrame::SetMapFrameDirty(BOOL bDirty)
{
	m_bNewMapScale = bDirty;
	m_bNewFixViewExtent = bDirty;
	m_bMapProperChanged = bDirty;
}


//////////////////////////////////////////////////////////////////////////
void CMapFrame::CallbackMapExtentModeChangedFun(Carto::CMap* pMap)
{
	if(pMap != m_pGeoMap.get())
		return;

	if(m_pGeoMap->GetExtentMode() == Carto::EEM_FIX_EXTENT)
		m_bNewFixViewExtent = TRUE;

	if(m_pGeoMap->GetExtentMode() == Carto::EEM_FIX_EXTENT)
		SetWHRatioMode(EWHR_FIX_RATIO);
	else
		SetWHRatioMode(EWHR_FREE_RATIO);
}

void CMapFrame::CallbackMapRedrawedFun(Carto::CMap* pMap)
{
	if(pMap != m_pGeoMap.get())
		return;

	m_bMapProperChanged = TRUE;
}

void CMapFrame::CallbackViewPosChange(Display::VIEW_POSITION viewPosition)
{
	m_bMapProperChanged = TRUE;
}

boost::signals::connection  CMapFrame::RegisterMapFrameProperChanged(boost::function<void (CMapFrame*)> fun)
{
	return gCallbackMapFrameProperChanged.connect(fun);
}

boost::signals::connection  CMapFrame::RegisterMapFrameMapSetted(boost::function<void (CMapFrame*)> fun)
{
	return gCallbackMapFrameMapSetted.connect(fun);
}

void CMapFrame::SetStandardMappingState( BOOL bIsStdMap )
{
	m_bStandardMap = bIsStdMap;
}

BOOL CMapFrame::GetStandardMappingState( void )
{
	return m_bStandardMap;
}



}
