#include "StdAfx.h"
#include "PolylineMeasureElement.h"
#include "EnvelopeTracker.h"
#include "TextSymbol.h"

namespace Element{

	CPolylineMeasureElement::CPolylineMeasureElement(void)
	{
		m_enumElementType = ET_MEASURE_POLYLINE_ELEMENT;
		m_pSelectionHandle.reset(new CEnvelopeTracker(GEOMETRY::geom::Envelope(0,0,0,0), HT_EIGHT));
		bDrawCloseButton = false;
	}

	CPolylineMeasureElement::CPolylineMeasureElement(const GEOMETRY::geom::Geometry& geometry):CPolylineElement(geometry)
	{
		m_enumElementType = ET_MEASURE_POLYLINE_ELEMENT;

		m_pSymbol.reset(new Display::CSimpleLineSymbol);
		m_pSymbol->SetColor(RGB(0,0,0));

		m_pSelectionHandle.reset(new CEnvelopeTracker(*geometry.getEnvelopeInternal(), HT_EIGHT));
		bDrawCloseButton = false;
	}

	CPolylineMeasureElement::CPolylineMeasureElement(GEOMETRY::geom::Coordinate& coord)
	{
		m_enumElementType = ET_MEASURE_POLYLINE_ELEMENT;

		m_pSymbol.reset(new Display::CSimpleLineSymbol);
		m_pSymbol->SetColor(RGB(0,0,0));


		GEOMETRY::geom::CoordinateSequence* pCoords = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->getCoordinateSequenceFactory()->create(NULL);
		for(int i=0; i<2; i++)
			pCoords->add(coord);
		m_pGeometry = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->createLineString(pCoords);

		m_pSelectionHandle.reset(new CEnvelopeTracker(*m_pGeometry->getEnvelopeInternal(), HT_EIGHT));
		bDrawCloseButton = false;
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
		m_pSymbol->SetColor(RGB(255,127,39));
		Display::CSimpleLineSymbolPtr pLineSymbol =m_pSymbol;
		pLineSymbol->SetLineWidth(2);
		pDisplay->SetSymbol( pLineSymbol.get() );

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
	void CPolylineMeasureElement::DrawVertixCircle(Display::IDisplayPtr pDisplay)
	{

		GEOMETRY::geom::LineString* pLineString = (GEOMETRY::geom::LineString*)m_pGeometry;
		const GEOMETRY::geom::CoordinateSequence *pCoors = pLineString->getCoordinatesRO();
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
	void CPolylineMeasureElement::DrawCloseButton(Display::IDisplayPtr pDisplay)
	{

		GEOMETRY::geom::LineString* pLineString = (GEOMETRY::geom::LineString*)m_pGeometry;
		const GEOMETRY::geom::CoordinateSequence *pCoors = pLineString->getCoordinatesRO();
		GEOMETRY::geom::Coordinate pToPoint;

		double dbExpand = pDisplay->GetDisplayTransformation().TransformToGeo(6);
		double dbOffset = pDisplay->GetDisplayTransformation().TransformToGeo(-12);
		pToPoint = pCoors->getAt(pCoors->getSize()-1);
		//pToPoint.x+=pToPoint.x +dbOffset;
		GEOMETRY::geom::Envelope textEnvS(pToPoint);
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
		m_pSymbol->SetColor(RGB(255,0,0));
		Display::CSimpleLineSymbolPtr pLineSymbol =m_pSymbol;
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
	void CPolylineMeasureElement::DrawVertixLabel(Display::IDisplayPtr pDisplay)
	{

		GEOMETRY::geom::LineString* pLineString = (GEOMETRY::geom::LineString*)m_pGeometry;
		const GEOMETRY::geom::CoordinateSequence *pCoors = pLineString->getCoordinatesRO();
		GEOMETRY::geom::Coordinate pFromPoint,pToPoint;

		
		std::string labelName="";
		char szLabelName[256];
		double dbGeoLen=0,dbTotalLen=0;
		double dbOffset = pDisplay->GetDisplayTransformation().TransformToGeo(10);
		double dbExpand = pDisplay->GetDisplayTransformation().TransformToGeo(3);
		GEOMETRY::geom::Line* pLine = new GEOMETRY::geom::Line();

		//标注起点
		pFromPoint = pCoors->getAt(0);
		GEOMETRY::geom::Envelope textEnvS(pFromPoint);
		textEnvS.expandBy(dbExpand);

		labelName ="起点";
		pDisplay->Draw(&textEnvS,labelName,TRUE);

		//标注量测值
		for(int i = 0;i<pCoors->getSize()-1;i++)
		{
			pFromPoint = pCoors->getAt(i);
			pToPoint = pCoors->getAt(i+1);

			pLine->setFromPoint(pFromPoint);
			pLine->setToPoint(pToPoint);

			dbGeoLen =  pLine->Length();
			dbTotalLen+=dbGeoLen;

			GEOMETRY::geom::Envelope textEnv(pToPoint.x+dbOffset,pToPoint.x+dbOffset+dbExpand,pToPoint.y,pToPoint.y+dbExpand);

			sprintf(szLabelName, "%.3f", dbTotalLen);
			labelName =szLabelName;
			if(i == pCoors->getSize()-2)
			{
				labelName ="总长度:";labelName+=szLabelName;
			}
			pDisplay->Draw(&textEnv,labelName,TRUE);
		}
		delete pLine;
	}


}
