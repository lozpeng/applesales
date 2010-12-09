#include "StdAfx.h"
#include "SimpleMarkerElement.h"
#include "SimpleMarkerSymbol.h"
#include "EnvelopeTracker.h"

namespace Element{

CSimpleMarkerElement::CSimpleMarkerElement()
{
	m_enumElementType = ET_SIMPLE_POINT_ELEMENT;
	
	m_pSelectionHandle.reset(new CEnvelopeTracker(GEOMETRY::geom::Envelope(0,1,0,1), HT_FOUR));


	m_bCanSetWHRMode = FALSE;

}
CSimpleMarkerElement::CSimpleMarkerElement(const GEOMETRY::geom::Geometry& geometry)
:IMarkerElement(geometry)
{
	m_enumElementType = ET_SIMPLE_POINT_ELEMENT;

	Display::CSimpleMarkerSymbol* pMarkerSymbol = new Display::CSimpleMarkerSymbol;
	//
	//init symbol
	pMarkerSymbol->SetOutLineColor(RGB(0,0,0));
	pMarkerSymbol->SetMarkerColor(RGB(0,0,0));
	pMarkerSymbol->SetMarkerType(SIMPLE_MARKER_CIRCLE);
	pMarkerSymbol->SetMarkerSize(8);
	//
	m_pSymbol.reset(pMarkerSymbol);
	m_pSelectionHandle.reset(new CEnvelopeTracker(GetEnvelope(), HT_FOUR));

	m_bCanSetWHRMode = FALSE;
}

CSimpleMarkerElement::~CSimpleMarkerElement(void)
{
}

void CSimpleMarkerElement::serialization(SYSTEM::IArchive &ar)
{
	IMarkerElement::serialization(ar);

	if(ar.IsRead())
	{
		GeometryChangedEvents();
	}
}




GEOMETRY::geom::Envelope CSimpleMarkerElement::GetEnvelope()
{
	/*if(!m_pSymbol)
		return *m_pGeometry->getEnvelopeInternal();

	GEOMETRY::geom::Envelope env(*m->getCoordinate());*/
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

void CSimpleMarkerElement::DrawNormal(Display::IDisplayPtr pDisplay)
{
	Display::IMarkerSymbol* pMarkerSymbol = dynamic_cast<Display::IMarkerSymbol*>(m_pSymbol.get());

	if(m_bGeometryChanged)
	{
		
		DIS_RECT *pHandleDisBound = pDisplay->GetDisplayTransformation().TransformToDisplay(&GetEnvelope());
		long width = pHandleDisBound->Width()*Display::CDC::GetCreateDCsRateOfPixelAndMillimeter();
		long height = pHandleDisBound->Height()*Display::CDC::GetCreateDCsRateOfPixelAndMillimeter();

		long symbolSizeMM = width < height ? width : height;	
		float symbolSize = SYSTEM::UnitConverter::ConvertUnits(symbolSizeMM, SYSTEM::SYS_UNIT_MILLIMETER, pMarkerSymbol->GetUnit());
		
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
		//¸üÐÂselectionhandle
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
		double markerSizeGeo;
		pDisplay->GetDisplayTransformation().ConvertDisplayToGeo(markerSizePixel, markerSizeGeo);

		GEOMETRY::geom::Envelope env(*m_pGeometry->getCoordinate());
		env.expandBy(abs(markerSizeGeo)/2);
		GEOMETRY::geom::Geometry* pGeo = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->toGeometry(&env);
		m_pSelectionHandle->SetGeometry(*pGeo);
		GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(pGeo);
	}
	

	//»æÖÆ
	pDisplay->SetSymbol( m_pSymbol.get() );

	pDisplay->Begin();

	pDisplay->Draw( m_pGeometry );

	pDisplay->End();

}

//void Update
}
