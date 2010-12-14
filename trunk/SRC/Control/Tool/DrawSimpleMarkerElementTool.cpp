#include "StdAfx.h"
#include "DrawSimpleMarkerElementTool.h"
#include "MapControl.h"

static CDrawSimpleMarkerElementTool gDrawSimpleMarkerTool;

CDrawSimpleMarkerElementTool::CDrawSimpleMarkerElementTool(void): IDrawElementTool("DrawSimpleMarkerElementTool")
{
	m_pMarker.reset();
}

CDrawSimpleMarkerElementTool::~CDrawSimpleMarkerElementTool(void)
{
}

void CDrawSimpleMarkerElementTool::Initialize(Framework::IUIObject *pTargetControl)
{
	IDrawElementTool::Initialize(pTargetControl);
}

void CDrawSimpleMarkerElementTool::LButtonDownEvent (UINT nFlags, CPoint point)
{
	IDrawElementTool::LButtonDownEvent (nFlags, point);


	//获取活动地区
	Display::IDisplayPtr pDisplay = m_pMap->GetDisplay();
	if(!pDisplay)
		return;

	//displaytoGeo
	GEOMETRY::geom::Geometry* pGeo;
	GEOMETRY::geom::Coordinate coord;
	pDisplay->GetDisplayTransformation().ConvertDisplayToGeo(point.x, point.y, coord);
	pGeo = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->createPoint(coord);

	m_pMarker.reset(new Element::CSimpleMarkerElement(*pGeo));
	GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(pGeo);

	Display::IMarkerSymbol* pMarkerSymbol = dynamic_cast<Display::IMarkerSymbol*>(m_pMarker->GetSymbol().get());
	double markerSizeMM = SYSTEM::UnitConverter::ConvertUnits(pMarkerSymbol->GetMarkerSize(), SYSTEM::SYS_UNIT_POINT, SYSTEM::SYS_UNIT_MILLIMETER);
	long markerSizePixel = markerSizeMM*Display::CDC::GetCreateDCsRateOfPixelAndMillimeter();
	double markerSizeGeo;
	pDisplay->GetDisplayTransformation().ConvertDisplayToGeo(markerSizePixel, markerSizeGeo);


	GEOMETRY::geom::Envelope env(coord.x - markerSizePixel/2, coord.x + markerSizePixel/2,coord.y - markerSizePixel/2,coord.y + markerSizePixel/2);
	GEOMETRY::geom::Geometry* pTmpGeo = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->toGeometry(&env);
	m_pMarker->GetSelectionTracker()->SetGeometry(*pTmpGeo);
	GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(pTmpGeo);


	m_pMap->GetGraphicLayer()->UnselectAllElements();
	m_pMap->GetGraphicLayer()->AddElement(m_pMarker);
	m_pMap->GetGraphicLayer()->SelectElement(m_pMarker);	

	//加入回退堆栈
	//m_pMap->GetElementOperationStack()->AddOperation(Element::OPT_ADD, m_pMarker);

	//更新绘制
	m_pMapCtrl->UpdateControl(DrawContent(drawElement|drawEdit));
}

void CDrawSimpleMarkerElementTool::MouseMoveEvent (UINT nFlags, CPoint point)
{
}

void CDrawSimpleMarkerElementTool::LButtonUpEvent (UINT nFlags, CPoint point)
{
	IDrawElementTool::LButtonUpEvent(nFlags, point);

	//工具设为选择
	Framework::ITool* pTool = NULL;
	m_pMapCtrl->SetCurTool("SelectElementTool");

	pTool=Framework::ITool::FindTool("SelectElementTool");
	if(pTool)
	{
		pTool->Initialize(dynamic_cast<Framework::IUIObject*>(m_pMapCtrl));
	}
}