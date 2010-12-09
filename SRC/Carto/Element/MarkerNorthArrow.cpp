#include "StdAfx.h"
#include "MarkerNorthArrow.h"
#include "EnvelopeTracker.h"
#include "SimpleBackground.h"
#include "SimpleBorder.h"
#include "SimpleShadow.h"

//#include "CharMarkerSymbol.h"

namespace Element{

CMarkerNorthArrow::CMarkerNorthArrow()
{
	m_enumElementType = ET_MARKER_NORTH_ARROW;

	m_strName = "指北针";

	m_bGeometryChanged = FALSE;

	m_AnchorPos = EAP_CENTER_CENTER;

	m_pSelectionHandle.reset(new CEnvelopeTracker(GEOMETRY::geom::Envelope(0,0,0,0), HT_FOUR));
}

CMarkerNorthArrow::CMarkerNorthArrow(const GEOMETRY::geom::Geometry& geometry, CMapFrame* pMapFrame)
:IMapSurround(geometry, pMapFrame)
{
	m_enumElementType = ET_MARKER_NORTH_ARROW;

	m_strName = "指北针";

	m_bGeometryChanged = FALSE;

	m_AnchorPos = EAP_CENTER_CENTER;

	//m_pSymbol.reset(new Display::CCharMarkerSymbol);
	
	m_pSelectionHandle.reset(new CEnvelopeTracker(GetEnvelope(), HT_FOUR));
}

CMarkerNorthArrow::~CMarkerNorthArrow(void)
{
}

void CMarkerNorthArrow::serialization(SYSTEM::IArchive &ar)
{
	IMapSurround::serialization( ar );

	if(ar.IsRead())
	{
		GeometryChangedEvents();
	}
}

GEOMETRY::geom::Envelope CMarkerNorthArrow::GetEnvelope()
{
	if(m_pSelectionHandle)
	{
		return m_pSelectionHandle->GetEnvelope();
	}
	else
	{
		GEOMETRY::geom::Envelope env(*m_pGeometry->getCoordinate());
		return env;
	}
}

void CMarkerNorthArrow::ChangeGeometryEnvelopTo(GEOMETRY::geom::Envelope& newEnvelope)
{
	if(m_pGeometry)
	{
		GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(m_pGeometry);
		m_pGeometry = NULL;
	}

	GEOMETRY::geom::Coordinate coordCenter;
	
	newEnvelope.centre(coordCenter);
	
	m_pGeometry = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->createPoint(coordCenter);

	m_bGeometryChanged = TRUE;
}

void CMarkerNorthArrow::GeometryChangedEvents()
{
	GEOMETRY::geom::Envelope env = GetEnvelope();
	GEOMETRY::geom::Geometry* pGeo = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->toGeometry(&env);
	if(m_pSelectionHandle)
		m_pSelectionHandle->SetGeometry(*pGeo);

	GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(pGeo);
}

void CMarkerNorthArrow::DrawOnDrawMode(Display::IDisplayPtr pDisplay)
{
	DrawEnvelope(pDisplay);

	DrawNoEditMode(pDisplay);
}

void CMarkerNorthArrow::DrawMoveMode(Display::IDisplayPtr pDisplay)
{
	DrawEnvelope(pDisplay);

	DrawNoEditMode(pDisplay);
}


void CMarkerNorthArrow::DrawNormal(Display::IDisplayPtr pDisplay)
{
	Display::IMarkerSymbol* pMarkerSymbol = dynamic_cast<Display::IMarkerSymbol*>(m_pSymbol.get());

	if(m_bGeometryChanged)
	{

		DIS_RECT *pHandleDisBound = pDisplay->GetDisplayTransformation().TransformToDisplay(&GetEnvelope());
		long width = pHandleDisBound->Width()*Display::CDC::GetCreateDCsRateOfPixelAndMillimeter();
		long height = pHandleDisBound->Height()*Display::CDC::GetCreateDCsRateOfPixelAndMillimeter();

		long symbolSizeMM = width < height ? width : height;	
		float symbolSize = SYSTEM::UnitConverter::ConvertUnits(symbolSizeMM, SYSTEM::SYS_UNIT_MILLIMETER, pMarkerSymbol->GetUnit());
		symbolSize /= pDisplay->GetDisplayTransformation().GetMapScale();

		if(pDisplay->GetDisplayTransformation().GetReferenceScale() != 0)
		{
			float fScale =  pDisplay->GetDisplayTransformation().GetReferenceScale()/pDisplay->GetDisplayTransformation().GetMapScale();
			if (fScale != 1.000000)
			{
				symbolSize /=  fScale;	
			}
		}

		pMarkerSymbol->SetMarkerSize(symbolSize);

		m_bGeometryChanged = FALSE;
	}
	else
	{
		//更新selectionhandle
		double dblSize  = 	pMarkerSymbol->GetMarkerSize();

		if(pDisplay->GetDisplayTransformation().GetReferenceScale() != 0)
		{
			float fScale =  pDisplay->GetDisplayTransformation().GetReferenceScale()/pDisplay->GetDisplayTransformation().GetMapScale();
			if (fScale != 1.000000)
			{
				dblSize *=  fScale;	
			}
		}
		double dbSizeMM = SYSTEM::UnitConverter::ConvertUnits(dblSize, pMarkerSymbol->GetUnit(), SYSTEM::SYS_UNIT_MILLIMETER);
		long markerSizePixel = dbSizeMM/Display::CDC::GetCreateDCsRateOfPixelAndMillimeter();
		markerSizePixel /= pDisplay->GetDisplayTransformation().GetMapScale();
		double markerSizeGeo;
		pDisplay->GetDisplayTransformation().ConvertDisplayToGeo(markerSizePixel, markerSizeGeo);

		GEOMETRY::geom::Envelope env(*m_pGeometry->getCoordinate());
		env.expandBy(abs(markerSizeGeo)/2);
		GEOMETRY::geom::Geometry* pGeo = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->toGeometry(&env);
		m_pSelectionHandle->SetGeometry(*pGeo);
		GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(pGeo);
	}


	//绘制
	pDisplay->SetSymbol( m_pSymbol.get() );

	pDisplay->Begin();

	pDisplay->Draw( m_pGeometry );

	pDisplay->End();
}


}
