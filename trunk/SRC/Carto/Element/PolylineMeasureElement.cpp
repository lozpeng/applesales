#include "StdAfx.h"
#include "PolylineMeasureElement.h"
#include "EnvelopeTracker.h"
#include "TextSymbol.h"

namespace Element{

	CPolylineMeasureElement::CPolylineMeasureElement(void)
	{
		m_enumElementType = ET_POLYLINE_ELEMENT;
		m_pSelectionHandle.reset(new CEnvelopeTracker(GEOMETRY::geom::Envelope(0,0,0,0), HT_EIGHT));
	}

	CPolylineMeasureElement::CPolylineMeasureElement(const GEOMETRY::geom::Geometry& geometry):CPolylineElement(geometry)
	{
		m_enumElementType = ET_POLYLINE_ELEMENT;

		m_pSymbol.reset(new Display::CSimpleLineSymbol);
		m_pSymbol->SetColor(RGB(0,0,0));

		m_pSelectionHandle.reset(new CEnvelopeTracker(*geometry.getEnvelopeInternal(), HT_EIGHT));
	}

	CPolylineMeasureElement::CPolylineMeasureElement(GEOMETRY::geom::Coordinate& coord)
	{
		m_enumElementType = ET_POLYLINE_ELEMENT;

		m_pSymbol.reset(new Display::CSimpleLineSymbol);
		m_pSymbol->SetColor(RGB(0,0,0));


		GEOMETRY::geom::CoordinateSequence* pCoords = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->getCoordinateSequenceFactory()->create(NULL);
		for(int i=0; i<2; i++)
			pCoords->add(coord);
		m_pGeometry = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->createLineString(pCoords);

		m_pSelectionHandle.reset(new CEnvelopeTracker(*m_pGeometry->getEnvelopeInternal(), HT_EIGHT));
	}

	CPolylineMeasureElement::~CPolylineMeasureElement(void)
	{

	}

	void CPolylineMeasureElement::serialization(SYSTEM::IArchive &ar)
	{
		IElement::serialization(ar);
	}

	void CPolylineMeasureElement::DrawNormal(Display::IDisplayPtr pDisplay)
	{
		pDisplay->SetSymbol( m_pSymbol.get() );

		pDisplay->Begin();

		pDisplay->Draw( m_pGeometry );

		pDisplay->End();

		//
		Display::ISymbolPtr pTextSymbol;
		pTextSymbol.reset(new Display::CTextSymbol);
		pDisplay->SetSymbol( pTextSymbol.get());

		pDisplay->Begin();

		DrawVertixLabel(pDisplay);

		pDisplay->End();
	}


	//绘制量测值，在节点上方
	void CPolylineMeasureElement::DrawVertixLabel(Display::IDisplayPtr pDisplay)
	{

		GEOMETRY::geom::LineString* pLine = (GEOMETRY::geom::LineString*)m_pGeometry;
		const GEOMETRY::geom::CoordinateSequence *pCoors = pLine->getCoordinatesRO();
		GEOMETRY::geom::Coordinate pGeo;

		std::string labelName="ok";
		for(int i = 0;i<pCoors->getSize();i++)
		{
			pGeo = pCoors->getAt(i);
			GEOMETRY::geom::Envelope textEnv(pGeo);
			textEnv.expandBy(5);
			pDisplay->Draw(&textEnv,labelName,TRUE);
		}
	}


}
