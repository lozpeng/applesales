/* Generated by Together */
#include "stdafx.h"
#include "IElement.h"
#include "SimpleDisplay.h"
#include "SymbolFactory.h"
#include "CDC.h"

#include "GroupElement.h"
#include "SimpleMarkerElement.h"
#include "RectangleElement.h"
#include "PolygonElement.h"
#include "CircleElement.h"
#include "EllipseElement.h"
#include "PolylineElement.h"
#include "CurveElement.h"
#include "BezierCurveElement.h"
#include "SimpleTextElement.h"
#include "CalloutTextElement.h"
#include "ParagraphTextElement.h"
#include "MapFrame.h"
#include "ScaleLine.h"
#include "AlternatingScaleBar.h"
#include "Legend.h"
#include "MapTitle.h"
#include "NeatLine.h"
#include "MarkerNorthArrow.h"
#include "PictureElement.h"
#include "DistrictRelationTable.h"

#include "EnvelopeTracker.h"







namespace Element{
IElement::IElement()
{
	m_enumElementType = ET_ELEMENT_NONE;
	m_bActive = TRUE;
	m_bLocked = FALSE;
	m_AnchorPos = EAP_LEFT_BOTTOM;

	m_bCanSetWHRMode = TRUE;
	m_eWHRatio = EWHR_FREE_RATIO;

	m_EditMode = EEM_NO_EDIT;
	m_DrawMode = EDM_NORMAL;
	
	m_strName = "";

	m_pSymbol.reset(new Display::CSimpleFillSymbol);

	m_pEnvelopeSymbol.reset(new Display::CSimpleFillSymbol);
	m_pEnvelopeSymbol->SetDrawFill(FALSE);
	m_pEnvelopeSymbol->SetOutLineColor(RGB(0,0,0));

	m_pVertixMarkerSymbol.reset(new Display::CSimpleMarkerSymbol);
	m_pVertixMarkerSymbol->SetMarkerColor(RGB(0,255,255));
	m_pVertixMarkerSymbol->SetMarkerSize(5);
	m_pVertixMarkerSymbol->SetMarkerType(SIMPLE_MARKER_SQUARE);
	m_pVertixMarkerSymbol->SetOutLineColor(RGB(0,0,0));

	m_pControlPtMarkerSymbol.reset(new Display::CSimpleMarkerSymbol);
	m_pControlPtMarkerSymbol->SetMarkerColor(RGB(255,128,255));
	m_pControlPtMarkerSymbol->SetMarkerSize(5);
	m_pControlPtMarkerSymbol->SetMarkerType(SIMPLE_MARKER_SQUARE);
	m_pControlPtMarkerSymbol->SetOutLineColor(RGB(0,0,0));

	m_pTrakerLineSymbol.reset(new Display::CSimpleLineSymbol);
	m_pTrakerLineSymbol->SetLineColor(RGB(0,255,255));
	m_pTrakerLineSymbol->SetLineStyle(DOT);

	m_pGeometry = NULL;
}

IElement::IElement(const GEOMETRY::geom::Geometry& geometry)
{
	m_pGeometry = geometry.clone();	

	m_enumElementType = ET_ELEMENT_NONE;
	m_bActive = TRUE;
	m_bLocked = FALSE;
	m_AnchorPos = EAP_LEFT_BOTTOM;

	m_bCanSetWHRMode = TRUE;
	m_eWHRatio = EWHR_FREE_RATIO;

	m_EditMode = EEM_NO_EDIT;
	m_DrawMode = EDM_NORMAL;

	m_strName = "";

	m_pSymbol.reset(new Display::CSimpleFillSymbol);

	m_pEnvelopeSymbol.reset(new Display::CSimpleFillSymbol);
	m_pEnvelopeSymbol->SetDrawFill(FALSE);
	m_pEnvelopeSymbol->SetOutLineColor(RGB(0,0,0));

	m_pVertixMarkerSymbol.reset(new Display::CSimpleMarkerSymbol);
	m_pVertixMarkerSymbol->SetMarkerColor(RGB(0,255,255));
	m_pVertixMarkerSymbol->SetMarkerSize(1.5);
	m_pVertixMarkerSymbol->SetMarkerType(SIMPLE_MARKER_SQUARE);
	m_pVertixMarkerSymbol->SetOutLineColor(RGB(0,0,0));

	m_pControlPtMarkerSymbol.reset(new Display::CSimpleMarkerSymbol);
	m_pControlPtMarkerSymbol->SetMarkerColor(RGB(255,128,255));
	m_pControlPtMarkerSymbol->SetMarkerSize(5);
	m_pControlPtMarkerSymbol->SetMarkerType(SIMPLE_MARKER_SQUARE);
	m_pControlPtMarkerSymbol->SetOutLineColor(RGB(0,0,0));

	m_pTrakerLineSymbol.reset(new Display::CSimpleLineSymbol);
	m_pTrakerLineSymbol->SetLineColor(RGB(0,255,255));
	m_pTrakerLineSymbol->SetLineStyle(DOT);

}


IElement::~IElement()
{
	if(m_pGeometry)
	{
		GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(m_pGeometry);
		m_pGeometry =NULL;
	}
}


void IElement::serialization(SYSTEM::IArchive &ar)
{
	SYSTEM::ISerialization::serialization( ar );
	if(ar.IsRead() )
	{
		int i;
		ar & i;
		//ASSERT( m_enumElementType = (ELEMENT_TYPE)i);
		ar & m_strName;
		ar & m_bLocked;
		ar & m_bActive;
		ar & i;
		m_AnchorPos = (ELEMENT_ANCHOR_POS)i;

		m_pSymbol = Display::CSymbolFactory::CreateSymbolFromStream(ar);
		m_pEnvelopeSymbol = Display::CSymbolFactory::CreateSymbolFromStream(ar);
		ar & i;
		m_DrawMode = (ELEMENT_DRAW_MODE)i;

		m_pVertixMarkerSymbol = Display::CSymbolFactory::CreateSymbolFromStream(ar);
		m_pControlPtMarkerSymbol  = Display::CSymbolFactory::CreateSymbolFromStream(ar);
		m_pTrakerLineSymbol = Display::CSymbolFactory::CreateSymbolFromStream(ar);

		//GEOMETRY::io::WKTReader GeoReader;
		//std::string strGeo;
		//ar & strGeo-

		//m_pGeometry = GeoReader.read(strGeo);

		//GEOMETRY::io::GeometySerializor geoSerializor( m_pGeometry );
		//m_pGeometry = geoSerializor.serialization( ar );

		GeometryChangedEvents();
	}
	else
	{
		int i = m_enumElementType;
		ar & (i);
		ar & m_strName;
		ar & m_bLocked;
		ar & m_bActive;
		i = m_AnchorPos;
		ar & i;
		m_pSymbol->serialization( ar );
		m_pEnvelopeSymbol->serialization( ar );
		i =  m_DrawMode;
		ar & i;
		m_pVertixMarkerSymbol->serialization( ar );
		m_pControlPtMarkerSymbol->serialization( ar );
		m_pTrakerLineSymbol->serialization( ar );

		//GEOMETRY::io::WKTWriter GeoWriter;
		//std::string strGeo= GeoWriter.write(m_pGeometry); 
		//ar & strGeo;
		
		//GEOMETRY::io::GeometySerializor geoSerializor( m_pGeometry );
		//geoSerializor.serialization( ar );

	}
}

IElementPtr IElement::Clone()
{
	IElementPtr pElement;
	SYSTEM::CBinArchive ar;

	serialization( ar );
	ar.SetReadState();
	ar.SetPosToBegin();
	pElement = CreateElementFromStream( ar );

	if(pElement->GetType() & ET_MAP_SURROUND_ELEMENT)
		((IMapSurroundPtr)pElement)->SetMapFrame(((IMapSurround*)this)->GetMapFrame());
	else if(pElement->GetType() == ET_MAP_FRAME_ELEMENT)
		((CMapFramePtr)pElement)->SetMap(((CMapFrame*)this)->GetMap());

	return pElement;
}

IElementPtr  IElement::CreateElementFromStream(SYSTEM::IArchive &ar)
{
	int startpos = ar.GetCurrentPos();

	long type;
	ar & type;

	ar.GetCurrentPos() = startpos; 

	IElementPtr pElement = CreateElement( (ELEMENT_TYPE)type);

	if (pElement != NULL)
		pElement->serialization( ar );

	return pElement;

}

SYSTEM::CSmartPtr<IElement>  IElement::CreateElement( ELEMENT_TYPE type)
{
	switch(type)
	{
	case ET_SIMPLE_POINT_ELEMENT:
		return IElementPtr( new CSimpleMarkerElement() );
	case ET_POLYLINE_ELEMENT: 
		return IElementPtr( new CPolylineElement() );
	case ET_CURVE_ELEMENT:
		return IElementPtr( new CCurveElement() );
	case ET_BEZIERCURVE_ELEMENT:
		return IElementPtr( new CBezierCurveElement() );
	case ET_FILL_RECTANGLE_ELEMENT:
		return IElementPtr( new CRectangleElement() );
	case ET_FILL_POLYGON_ELEMENT:
		return IElementPtr( new CPolygonElement() );
	case ET_FILL_CIRCLE_ELEMENT:
		return IElementPtr( new CCircleElement() );
	case ET_FILL_ELLIPSE_ELEMENT:
		return IElementPtr( new CEllipseElement() );
	case ET_SIMPLE_TEXT_ELEMENT:
		return IElementPtr( new CSimpleTextElement() );
	case ET_CALLOUT_TEXT_ELEMENT:
		return IElementPtr( new CCalloutTextElement() );
	case ET_PARAGRAPH_TEXT_ELEMENT:
		return IElementPtr( new CParagraphTextElement() );
	case ET_GROUP_ELEMENT:
		return IElementPtr( new CGroupElement() );
	case ET_MAP_FRAME_ELEMENT:
		return IElementPtr( new CMapFrame() );
	case ET_ALTERNATING_SCALEBAR:
		return CAlternatingScaleBarPtr( new CAlternatingScaleBar() );
	case ET_SCALELINE:
		return CScaleLinePtr( new CScaleLine() );
	case ET_LEGEND:
		return CLegendPtr( new CLegend() );
	case ET_MAP_TITLE:
		return CMapTitlePtr( new CMapTitle() );
	case ET_MARKER_NORTH_ARROW:
		return CMarkerNorthArrowPtr( new CMarkerNorthArrow() );
	case ET_EXT_PICTURE_ELEMENT:
		return CPictureElementPtr( new CPictureElement() );
	case ET_RELATIONDISTRICT_TABLE:
		return CDistrictRelationTablePtr( new CDistrictRelationTable() );
	case ET_NEAT_LINE:
		return CNeatLinePtr( new CNeatLine() );
	default:
		return NULL;
	}
}

void IElement::Activate(Display::IDisplayPtr pDisplay)
{
	m_bActive = TRUE;
}

void IElement::Deactivate(Display::IDisplayPtr pDisplay)
{
	m_bActive = FALSE;
}

bool IElement::IsActive(Display::IDisplayPtr pDisplay)
{
	return m_bActive;
}

void IElement::Lock()
{
	m_bLocked = TRUE;
}

void IElement::UnLock()
{
	m_bLocked = FALSE;
}

BOOL IElement::IsLocked()
{
	return m_bLocked;
}

ELEMENT_TYPE IElement::GetType()
{
	return m_enumElementType;
}

void IElement::SetName(std::string strName)
{
	m_strName = strName;
}


std::string IElement::GetName()
{
	return m_strName;
}

GEOMETRY::geom::Envelope IElement::GetEnvelope()
{
	if(m_pGeometry)
		return *(m_pGeometry->getEnvelopeInternal());
	else
		return GEOMETRY::geom::Envelope();
	
}
void IElement::SetGeometry(GEOMETRY::geom::Geometry& geometry)
{
	if(m_pGeometry)
	{
		GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(m_pGeometry);
		m_pGeometry = NULL;
	}

	m_pGeometry = geometry.clone();
	GeometryChangedEvents();
}

void IElement::SetGeometry(GEOMETRY::geom::Geometry* geometry)
{
	if(m_pGeometry)
	{
		GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(m_pGeometry);
		m_pGeometry = NULL;
	}

	m_pGeometry = geometry;
	GeometryChangedEvents();
}

GEOMETRY::geom::Geometry* IElement::GetGeometry()
{
	return m_pGeometry;
}

BOOL IElement::Select(GEOMETRY::geom::Geometry* pSelectGeometry, long lSpatialRelation, CElementCollection& selectedSubElements,double dbTolerance)
{
	IElementPtr pElement;
	if(pSelectGeometry->getGeometryTypeId() == GEOMETRY::geom::GEOS_POINT)//点选情况下
	{
		GEOMETRY::geom::Envelope pointEnv(*pSelectGeometry->getCoordinate());
		pointEnv.expandBy(dbTolerance);
		GEOMETRY::geom::Geometry* pPointGeo = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->toGeometry(&pointEnv);

		BOOL bIntersect = FALSE;
		if(m_pGeometry->intersects(pPointGeo))
			bIntersect = TRUE;

		GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(pPointGeo);
		return bIntersect;
	}
	else//其他多边形选择情况下
	{
		switch(lSpatialRelation)
		{
			//多边形相交选择
		case Geodatabase::SpatialRelIntersects: 	
			{
				if(pSelectGeometry->intersects(m_pGeometry))
					return TRUE;
				else
					return FALSE;
			}
			break;
			//多边形包含选择
		case Geodatabase::SpatialRelContains:
			{
				if(pSelectGeometry->contains(m_pGeometry))
					return TRUE;
				else
					return FALSE;
			}
			break;
		default:
			{
				if(pSelectGeometry->contains(m_pGeometry))
					return TRUE;
				else
					return FALSE;
			}
			break;
		}
	}

}


void IElement::SetSymbol(Display::ISymbolPtr pSymbol)
{
	m_pSymbol = pSymbol;
}

Display::ISymbolPtr IElement::GetSymbol()
{
	return m_pSymbol;
}
/////////////////////////////////////////////////////////////////////////

void IElement::Scale(DIS_POINT pPoint, double sx, double sy)
{
	if(!m_pGeometry)
		return;

	m_pGeometry->Scale(GEOMETRY::geom::Coordinate(pPoint.p.x, pPoint.p.y), sx, sy);

	GeometryChangedEvents();
}


void IElement::Move(double dx, double dy)
{
	if(!m_pGeometry)
		return;

	m_pGeometry->Move(dx,dy);
	GeometryChangedEvents();
}


void IElement::Rotate(DIS_POINT pPoint, double rotationAngle)
{
	if(!m_pGeometry)
		return;

	m_pGeometry->Rotate(GEOMETRY::geom::Coordinate(pPoint.p.x, pPoint.p.y), rotationAngle);

	GeometryChangedEvents();
}


HIT_TEST_RES IElement::HitTest ( GEOMETRY::geom::Coordinate coord, double dbTolerance, HIT_MODE nHitMode)
{
	HIT_TEST_RES hitTestRes;
	if(HH_HIT_GEOMETRY == nHitMode )
	{
		GEOMETRY::geom::Geometry* pPoint = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->toGeometry(
			&GEOMETRY::geom::Envelope(coord.x - dbTolerance, coord.x + dbTolerance, coord.y - dbTolerance, coord.y + dbTolerance));
		if(m_pGeometry->intersects(pPoint)) 
			hitTestRes.lHitLocation = HH_HIT_INTERIOR;

		GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(pPoint);
	}
	else if(HH_HIT_HANDLE == nHitMode)
	{
		if(m_pSelectionHandle)
			hitTestRes.lHitLocation = m_pSelectionHandle->HitTest(coord, dbTolerance);
	}
	else if(HH_HIT_VERTIX == nHitMode)
	{
		GEOMETRY::geom::Coordinate coordOut;
		double dbSearchDis = 0;
		long lPartIndex, lVertixIndex;
		m_pGeometry->SnapVertex(&coord, dbTolerance, &coordOut, &dbSearchDis, &lPartIndex, &lVertixIndex);
		hitTestRes.lPartIndex= lPartIndex;
		hitTestRes.lHitLocation = lVertixIndex;
	}

	return hitTestRes;
	
}

void IElement::MoveHandleTo(HIT_HANDLE nHandle,GEOMETRY::geom::Coordinate coord)
{
	if(!m_pSelectionHandle)
		return;

	m_pSelectionHandle->MoveHandleTo(nHandle, coord);

	ChangeGeometryEnvelopTo(m_pSelectionHandle->GetEnvelope());
}

void IElement::ChangeGeometryEnvelopTo(GEOMETRY::geom::Envelope& newEnvelope)
{
	if(!m_pGeometry)
		return;

	m_pGeometry->FitEnvelope(newEnvelope);

	GeometryChangedEvents();
}

void IElement::GeometryChangedEvents()
{
	if(m_pSelectionHandle)
		m_pSelectionHandle->SetGeometry(*m_pGeometry);
}
void IElement::MoveVertixTo(long lIndex,GEOMETRY::geom::Coordinate coord)
{
	GeometryChangedEvents();
}

//////////////////////////////////////////////////////////////////////////

void IElement::SetDrawMode(ELEMENT_DRAW_MODE drawMode)
{
	m_DrawMode = drawMode;
}

ELEMENT_DRAW_MODE IElement::GetDrawMode()
{
	return m_DrawMode;
}

void IElement::SetEditMode(ELEMENT_EDIT_MODE editMode)
{
	m_EditMode = editMode;
}

ELEMENT_EDIT_MODE IElement::GetEditMode()
{
	return m_EditMode;
}

void IElement::Draw( Display::IDisplayPtr pDisplay)
{	
	switch(m_EditMode)
	{
	case EEM_NO_EDIT:
		DrawNoEditMode(pDisplay);
		break;
	case EEM_ONDRAW:
		DrawOnDrawMode(pDisplay);
		break;
	case EEM_SELECT:
		DrawSelectMode(pDisplay);
		break;
	case EEM_EDIT_VERTIX:
		DrawEditVertixMode(pDisplay);
		break;
	case EEM_MOVE:
		DrawMoveMode(pDisplay);
		break;
	default:
		DrawNoEditMode(pDisplay);
		break;
	}
}

void IElement::DrawEnvelope( Display::IDisplayPtr pDisplay)
{
	pDisplay->SetSymbol(m_pEnvelopeSymbol.get());
	
	pDisplay->Begin();

	if(m_pGeometry)
		pDisplay->Draw( &GetEnvelope() );

	pDisplay->End();

}


//////////////////////////////////////////////////////////////////////////
void IElement::DrawNoEditMode(Display::IDisplayPtr pDisplay)
{
	switch(m_DrawMode)
	{
	case EDM_NORMAL:
		DrawNormal(pDisplay);
		break;	
	case EDM_DRAFT:
		DrawDraft(pDisplay);
		break;
	case EDM_PRINT:
		DrawPrint(pDisplay);
		break;
	default:
		DrawNormal(pDisplay);
		break;
	}
}

void IElement::DrawEditVertixMode(Display::IDisplayPtr pDisplay)
{
	DrawNoEditMode(pDisplay);
	DrawVertixTracker(pDisplay);
}

void IElement::DrawSelectMode(Display::IDisplayPtr pDisplay)
{
	DrawNoEditMode(pDisplay);
	DrawSelectionTracker(pDisplay);
}

void IElement::DrawOnDrawMode(Display::IDisplayPtr pDisplay)
{
	DrawNoEditMode(pDisplay);
}
void IElement::DrawMoveMode(Display::IDisplayPtr pDisplay)
{
	DrawNoEditMode(pDisplay);
}
//////////////////////////////////////////////////////////////////////////

void IElement::DrawDraft(Display::IDisplayPtr pDisplay)
{
	DrawNormal(pDisplay);

}

void IElement::DrawPrint(Display::IDisplayPtr pDisplay)
{
	DrawNormal(pDisplay);
}

void IElement::DrawSelectionTracker(Display::IDisplayPtr pDisplay)
{
	if(m_pSelectionHandle)
		m_pSelectionHandle->Draw(pDisplay);
}

void IElement::DrawVertixTracker(Display::IDisplayPtr pDisplay)
{
	void *p = NULL;
	if( m_pGeometry == NULL )
		return;

	GEOMETRY::geom::GeometryTypeId GTypeID = m_pGeometry->getGeometryTypeId();

	if(GTypeID == GEOMETRY::geom::GEOS_LINESTRING/*||GTypeID == geos::geom::GEOS_LINEARRING*/)
	{
		GEOMETRY::geom::LineString* pLine = (GEOMETRY::geom::LineString*)m_pGeometry;
		p = (void*)pDisplay->GetDisplayTransformation().TransformToDisplay( pLine );
	}
	else if(GTypeID == GEOMETRY::geom::GEOS_POLYGON)
	{
		GEOMETRY::geom::Polygon* pPoly = (GEOMETRY::geom::Polygon*)m_pGeometry;
		p = (void*)pDisplay->GetDisplayTransformation().TransformToDisplay( pPoly );
	}
	else if(GTypeID == GEOMETRY::geom::GEOM_BEZIERSPLINE)
	{
		GEOMETRY::geom::BezierSpline* pBezierSpline = (GEOMETRY::geom::BezierSpline*)m_pGeometry;
		p = (void*)pDisplay->GetDisplayTransformation().TransformToDisplay( pBezierSpline );
	}
	else if(GTypeID == GEOMETRY::geom::GEOS_MULTILINESTRING || 
		GTypeID == GEOMETRY::geom::GEOS_MULTIPOLYGON )
	{
		GEOMETRY::geom::GeometryCollection *pGeoCol = (GEOMETRY::geom::GeometryCollection*)m_pGeometry;
		for(int i = 0 ; i < pGeoCol->getNumGeometries() ; i++ )
			pDisplay->Draw( pGeoCol->getGeometryN(i) );

		return;
	}
	else
	{
		return;
	}


	if(GTypeID == GEOMETRY::geom::GEOS_LINESTRING)
	{
		//Draw traker outline
		m_pTrakerLineSymbol->SelectDC(pDisplay->GetDrawDC());
		m_pTrakerLineSymbol->SetReadyDraw();
		DIS_LINE *pDIS_LINE = (DIS_LINE *)p;
		m_pTrakerLineSymbol->Draw(pDIS_LINE);


		//Draw vertix
		m_pVertixMarkerSymbol->SelectDC(pDisplay->GetDrawDC());
		m_pVertixMarkerSymbol->SetReadyDraw();
		DIS_POINT* pDIS_POINT;
		INT_POINT* pLinePt = pDIS_LINE->ps;
		CreateDisplayPoint(pDIS_POINT);
		for(unsigned int i = 0 ; i < pDIS_LINE->Count ; i++ )
		{
			pDIS_POINT->p.x = pLinePt->x;
			pDIS_POINT->p.y = pLinePt->y;
			pLinePt++;

			m_pVertixMarkerSymbol->Draw(pDIS_POINT);
		}	

		FreeDisplayObj( pDIS_POINT );
		m_pVertixMarkerSymbol->ClearDC();
	}
	else if(GTypeID == GEOMETRY::geom::GEOS_POLYGON)
	{
		//Draw traker outline
		m_pTrakerLineSymbol->SelectDC(pDisplay->GetDrawDC());
		m_pTrakerLineSymbol->SetReadyDraw();
		DIS_LINE* pDIS_LINE; 
		DIS_POLYGON  *pDIS_POLYGON = (DIS_POLYGON *)p;
		INT_POINT *pts = pDIS_POLYGON->GetPointAdr();
		for(unsigned int i = 0 ; i < pDIS_POLYGON->Count ; i++ )
		{
			CreateDisplayLine( pDIS_LINE , pDIS_POLYGON->RingCount[i] );

			memcpy( pDIS_LINE->ps , pts , sizeof(INT_POINT)*pDIS_LINE->Count );

			if( pDIS_LINE == NULL || pDIS_LINE->type != Dis_Line )
			{
				//FALSERETURN_NOVAL("Error:the param can't be NULL")
			}

			m_pTrakerLineSymbol->Draw(pDIS_LINE);


			FreeDisplayObj( pDIS_LINE );

			pts += pDIS_POLYGON->RingCount[i];
		}	
		m_pTrakerLineSymbol->ClearDC();

		//draw vertix
		m_pVertixMarkerSymbol->SelectDC(pDisplay->GetDrawDC());
		m_pVertixMarkerSymbol->SetReadyDraw();
		DIS_POINT* pDIS_POINT;
		CreateDisplayPoint(pDIS_POINT);
		pts = pDIS_POLYGON->GetPointAdr();
		for(unsigned int i = 0 ; i < pDIS_POLYGON->Count ; i++ )
		{
			for(unsigned int j = 0 ; j < pDIS_POLYGON->RingCount[i] ; j++ )
			{
				pDIS_POINT->p.x = pts->x;
				pDIS_POINT->p.y = pts->y;
				pts++;

				m_pVertixMarkerSymbol->Draw(pDIS_POINT);
			}
		}	

		FreeDisplayObj( pDIS_POINT );
		m_pVertixMarkerSymbol->ClearDC();
	}
	else if(GTypeID == GEOMETRY::geom::GEOM_BEZIERSPLINE)
	{
		//Draw traker outline
		m_pTrakerLineSymbol->SelectDC(pDisplay->GetDrawDC());
		m_pTrakerLineSymbol->SetReadyDraw();
		DIS_LINE *pDIS_LINE = (DIS_LINE *)p;
		m_pTrakerLineSymbol->Draw(pDIS_LINE);


		//Draw vertix
		DIS_POINT* pDIS_POINT;
		INT_POINT* pLinePt = pDIS_LINE->ps;
		CreateDisplayPoint(pDIS_POINT);
		unsigned int knoteCnt = (pDIS_LINE->Count-1)/3;

		m_pVertixMarkerSymbol->SelectDC(pDisplay->GetDrawDC());
		m_pVertixMarkerSymbol->SetReadyDraw();
		for(int i=0; i<knoteCnt+1; i++)
		{
			pDIS_POINT->p.x = pLinePt->x;
			pDIS_POINT->p.y = pLinePt->y;
			pLinePt+=3;

			m_pVertixMarkerSymbol->Draw(pDIS_POINT);
		}
		m_pVertixMarkerSymbol->ClearDC();
		FreeDisplayObj( pDIS_POINT );

		/*CreateDisplayPoint(pDIS_POINT);
		pLinePt = pDIS_LINE->ps;
		m_pControlPtMarkerSymbol->SelectDC(pDisplay->GetDrawDC());
		m_pControlPtMarkerSymbol->SetReadyDraw();
		for(int i=0; i<knoteCnt+1; i++)
		{
			pLinePt++;
			pDIS_POINT->p.x = pLinePt->x;
			pDIS_POINT->p.y = pLinePt->y;
			m_pControlPtMarkerSymbol->Draw(pDIS_POINT);

			pLinePt++;
			pDIS_POINT->p.x = pLinePt->x;
			pDIS_POINT->p.y = pLinePt->y;
			m_pControlPtMarkerSymbol->Draw(pDIS_POINT);

			pLinePt++;


		}
		FreeDisplayObj( pDIS_POINT );
		m_pControlPtMarkerSymbol->ClearDC();*/

	}

	////释放绘制对象
	if(p)
	{
		FreeDisplayObj(p);
	}
}

//////////////////////////////////////////////////////////////////////////
BOOL IElement::CanSetWHRMode()
{
	return m_bCanSetWHRMode;
}

void IElement::SetWHRatioMode(ELEMENT_WIDTH_HEIGHT_RATIO eWHRatio)
{
	if(!m_bCanSetWHRMode)
		return;

	if(m_eWHRatio == eWHRatio)
		return;
	else
		m_eWHRatio = eWHRatio;

	if(m_eWHRatio == EWHR_FIX_RATIO)
		m_pSelectionHandle.reset(new CEnvelopeTracker(*m_pGeometry->getEnvelopeInternal(), HT_FOUR));
	else if(m_eWHRatio == EWHR_FREE_RATIO)
		m_pSelectionHandle.reset(new CEnvelopeTracker(*m_pGeometry->getEnvelopeInternal(), HT_EIGHT));
}

ELEMENT_WIDTH_HEIGHT_RATIO IElement::GetWHRatioMode()
{
	return m_eWHRatio;
}

}
