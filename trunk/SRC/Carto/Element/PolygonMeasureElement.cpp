#include "StdAfx.h"
#include "PolygonMeasureElement.h"
#include "EnvelopeTracker.h"
#include "TextSymbol.h"

namespace Element{


	CPolygonMeasureElement::CPolygonMeasureElement()
	{
		m_enumElementType = ET_MEASURE_POLYGON_ELEMENT;
		m_pSelectionHandle.reset(new CEnvelopeTracker(GEOMETRY::geom::Envelope(0,0,0,0), HT_EIGHT));
		bDrawCloseButton = false;
	}

	CPolygonMeasureElement::CPolygonMeasureElement(const GEOMETRY::geom::Geometry& geometry):CPolygonElement(geometry)
	{
		m_enumElementType = ET_MEASURE_POLYGON_ELEMENT;
		m_pSelectionHandle.reset(new CEnvelopeTracker(*geometry.getEnvelopeInternal(), HT_EIGHT));
		bDrawCloseButton = false;
	}

	CPolygonMeasureElement::CPolygonMeasureElement(GEOMETRY::geom::Coordinate& coord)
	{
		m_enumElementType = ET_MEASURE_POLYGON_ELEMENT;

		GEOMETRY::geom::CoordinateSequence* pCoords = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->getCoordinateSequenceFactory()->create(NULL);
		for(int i=0; i<4; i++)
			pCoords->add(coord);


		GEOMETRY::geom::LinearRing* pRing = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->createLinearRing(pCoords);
		m_pGeometry = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->createPolygon(pRing, NULL);

		m_pSelectionHandle.reset(new CEnvelopeTracker(*m_pGeometry->getEnvelopeInternal(), HT_EIGHT));
		bDrawCloseButton = false;
	}

	CPolygonMeasureElement::~CPolygonMeasureElement(void)
	{

	}

	void CPolygonMeasureElement::serialization(SYSTEM::IArchive &ar)
	{
		IFillShapeElement::serialization(ar);
	}


	void CPolygonMeasureElement::DrawOnDrawMode(Display::IDisplayPtr pDisplay)
	{
		DrawNormal(pDisplay);
	}
	void CPolygonMeasureElement::DrawNormal(Display::IDisplayPtr pDisplay)
	{
		
		Display::CSimpleFillSymbolPtr pPolygonSymbol =m_pSymbol;
		pPolygonSymbol->SetDrawFill(false);
		pPolygonSymbol->SetOutLineWidth(2);
		pPolygonSymbol->SetOutLineColor(RGB(255,127,39));
		pDisplay->SetSymbol( pPolygonSymbol.get() );

		pDisplay->Begin();
		pDisplay->Draw( m_pGeometry );

		pDisplay->End();

		//绘制节点上圆圈
		Display::CSimpleFillSymbolPtr pFillSymbol;
		pFillSymbol.reset(new Display::CSimpleFillSymbol);
		pFillSymbol->SetDrawFill(false);
		pFillSymbol->SetOutLineColor(RGB(255,0,0));
		pFillSymbol->SetOutLineWidth(2);
		pDisplay->SetSymbol( pFillSymbol.get());

		pDisplay->Begin();
		DrawVertixCircle(pDisplay);
		pDisplay->End();

		//绘制量测值
		Display::CTextSymbolPtr pTextSymbol;
		pTextSymbol.reset(new Display::CTextSymbol);
		pTextSymbol->SetTextPosType(TXTPOS_RIGHTTOP);
		pTextSymbol->SetMaskDrawable(true);
		pDisplay->SetSymbol( pTextSymbol.get());

		pDisplay->Begin();
		DrawVertixLabel(pDisplay);
		pDisplay->End();


		//绘制关闭按钮
		if(bDrawCloseButton)
			DrawCloseButton(pDisplay);
	}

	//绘制量点，在节点上绘制圆圈
	void CPolygonMeasureElement::DrawVertixCircle(Display::IDisplayPtr pDisplay)
	{

		GEOMETRY::geom::Polygon* pPolygon = (GEOMETRY::geom::Polygon*)m_pGeometry;
		const GEOMETRY::geom::CoordinateSequence *pCoors =  pPolygon->getCoordinates();
		GEOMETRY::geom::Coordinate pFromPoint,pToPoint;

		double dbRadius = pDisplay->GetDisplayTransformation().TransformToGeo(5);;
		GEOMETRY::geom::Circle* pCircle= new GEOMETRY::geom::Circle();

		//标注圆圈
		for(int i = 0;i<pCoors->getSize();i++)
		{
			//起点
			pFromPoint = pCoors->getAt(i);

			pCircle->SetCenterPoint(pFromPoint);
			pCircle->SetRadius(dbRadius);
			pDisplay->Draw(pCircle);

		}
		delete pCircle;
	}


	//绘制关闭按钮
	void CPolygonMeasureElement::DrawCloseButton(Display::IDisplayPtr pDisplay)
	{

		GEOMETRY::geom::Polygon* pPolygon = (GEOMETRY::geom::Polygon*)m_pGeometry;
		const GEOMETRY::geom::CoordinateSequence *pCoors =  pPolygon->getCoordinates();

		if(pCoors->getSize()<3)
			return;

		GEOMETRY::geom::Coordinate pCentroidPoint;
		pPolygon->getCentroid(pCentroidPoint);

		double dbExpand = pDisplay->GetDisplayTransformation().TransformToGeo(6);
		double dbOffset = pDisplay->GetDisplayTransformation().TransformToGeo(-12);
		
		GEOMETRY::geom::Envelope textEnvS(pCentroidPoint);
		textEnvS.expandBy(dbExpand);
		textEnvS.translate(dbOffset,-dbOffset);

		Display::CSimpleFillSymbolPtr pFillSymbol;
		pFillSymbol.reset(new Display::CSimpleFillSymbol);
		pFillSymbol->SetDrawFill(true);
		pFillSymbol->SetFillColor(RGB(255,225,0));
		pFillSymbol->SetOutLineColor(RGB(255,127,39));
		pFillSymbol->SetOutLineWidth(2);
		pDisplay->SetSymbol( pFillSymbol.get());

		pDisplay->Begin();
		pDisplay->Draw(&textEnvS);
		pDisplay->End();

		//绘制X
		Display::CSimpleLineSymbolPtr pLineSymbol;
		pLineSymbol.reset(new Display::CSimpleLineSymbol);

		pLineSymbol->SetColor(RGB(255,0,0));
		pLineSymbol->SetLineWidth(2);
		pDisplay->SetSymbol( pLineSymbol.get() );

		pDisplay->Begin();

		GEOMETRY::geom::Coordinate pFromCoord,pToCoord;
		GEOMETRY::geom::LineString* pDrawLine= GeometryFactory::getDefaultInstance()->createLineString();

		pFromCoord.x = textEnvS.getMinX();
		pFromCoord.y = textEnvS.getMaxY();
		pToCoord.x = textEnvS.getMaxX();
		pToCoord.y = textEnvS.getMinY();
		pDrawLine->AddPoint(pFromCoord);
		pDrawLine->AddPoint(pToCoord);

		pDisplay->Draw(pDrawLine);


		GEOMETRY::geom::LineString* pDrawLine2= GeometryFactory::getDefaultInstance()->createLineString();

		pFromCoord.x = textEnvS.getMinX();
		pFromCoord.y = textEnvS.getMinY();
		pToCoord.x = textEnvS.getMaxX();
		pToCoord.y = textEnvS.getMaxY();
		pDrawLine2->AddPoint(pFromCoord);
		pDrawLine2->AddPoint(pToCoord);

		pDisplay->Draw(pDrawLine2);

		pDisplay->End();

	}
	//绘制量测值，在节点右方
	void CPolygonMeasureElement::DrawVertixLabel(Display::IDisplayPtr pDisplay)
	{

		GEOMETRY::geom::Polygon* pPolygon = (GEOMETRY::geom::Polygon*)m_pGeometry;
		const GEOMETRY::geom::CoordinateSequence *pCoors = pPolygon->getCoordinates();
		GEOMETRY::geom::Coordinate pCentroidPoint;

		if(pCoors->getSize()<3)
			return;

		double dbArea = pPolygon->getArea();
		pPolygon->getCentroid(pCentroidPoint);

		std::string labelName="";
		char szLabelName[10];
		double dbGeoLen=0,dbTotalLen=0;
		double dbOffset = pDisplay->GetDisplayTransformation().TransformToGeo(10);
		double dbExpand = pDisplay->GetDisplayTransformation().TransformToGeo(3);
		

		//标注点
		GEOMETRY::geom::Envelope textEnvS(pCentroidPoint);
		textEnvS.expandBy(dbExpand);

		labelName ="总面积:";

		sprintf(szLabelName, "%.3f", dbArea);
		labelName +=szLabelName;

		pDisplay->Draw(&textEnvS,labelName,TRUE);

		
	}


}
