// otScreenSketch.cpp : CotScreenSketch µÄÊµÏÖ

#include "stdafx.h"
#include "otScreenSketch.h"
#include "InterfaceConvert.h"

// CotScreenSketch
CotScreenSketch::CotScreenSketch()
{
	m_pSketch =new Display::CScreenSketch();
}

CotScreenSketch::~CotScreenSketch()
{
    if(m_pSketch)
	{
		delete m_pSketch;
	}
}

STDMETHODIMP CotScreenSketch::Create(otGeometryType type)
{
	TT_GEOMETRY::geom::GeometryTypeId gtype;

    switch(type)
	{
	case OT_GEOM_POINT:
		gtype =TT_GEOMETRY::geom::GEOS_POINT;
		break;
	case OT_GEOM_MULTIPOINT:
		gtype =TT_GEOMETRY::geom::GEOS_MULTIPOINT;
		break;
	case OT_GEOM_LINESTRING:
		gtype =TT_GEOMETRY::geom::GEOS_LINESTRING;
		break;
	case OT_GEOM_LINERING:
		gtype =TT_GEOMETRY::geom::GEOS_LINEARRING;
		break;
	case OT_GEOM_MULTILINESTRING:
		gtype =TT_GEOMETRY::geom::GEOS_MULTILINESTRING;
		break;
	case OT_GEOM_POLYGON:
		gtype =TT_GEOMETRY::geom::GEOS_POLYGON;
		break;
	case OT_GEOM_MULTIPOLYGON:
		gtype =TT_GEOMETRY::geom::GEOS_MULTIPOLYGON;
		break;
	case OT_GEOM_BEZIERSPLINE:
		gtype =TT_GEOMETRY::geom::GEOM_BEZIERSPLINE;
		break;
	case OT_GEOM_CIRCLE:
		gtype =TT_GEOMETRY::geom::GEOM_CIRCLE;
		break;
	case OT_GEOM_ELLIPSE:
		gtype =TT_GEOMETRY::geom::GEOM_ELLIPSE;
		break;
	
	default:
		gtype =TT_GEOMETRY::geom::GEOM_NULL;
		break;

			
	}
    m_pSketch->Create(gtype);

	return S_OK;
}

STDMETHODIMP CotScreenSketch::put_ScreenCanvas(IotCanvas* newVal)
{
	IOriginDataPtr pData;
	newVal->QueryInterface(__uuidof(IOriginData),(void**)&pData);

	long ldata;
	pData->get_OriginData(&ldata);

	m_pSketch->SetScreenDisplay(*((Display::IDisplayPtr*)ldata));



	return S_OK;
}

STDMETHODIMP CotScreenSketch::put_Symbol(IotSymbol* newVal)
{
	m_pSketch->SetSymbol(CInterfaceConvert::ConvertISymbol(newVal));

	return S_OK;
}

STDMETHODIMP CotScreenSketch::Start(void)
{
	m_pSketch->Start();

	return S_OK;
}

STDMETHODIMP CotScreenSketch::Stop(IotGeometry** retGeometry)
{
	TT_GEOMETRY::geom::Geometry *pg =m_pSketch->Stop();

	if(!pg)
	{
	    *retGeometry =NULL;
		return E_FAIL;
	}

    IotGeoConvertPtr pCon;

	 CoCreateInstance(CLSID_otGeoConvert,NULL,CLSCTX_INPROC_SERVER,__uuidof(IotGeoConvert),(void**)&pCon);

	 pCon->ConvertGeo((long)pg,VARIANT_TRUE,retGeometry);

	return S_OK;
}

STDMETHODIMP CotScreenSketch::AddPoint(IotPoint* point)
{
	TT_GEOMETRY::geom::Coordinate coord;

	point->get_X(&coord.x);
	point->get_Y(&coord.y);
	
	m_pSketch->AddPoint(coord);

	return S_OK;
}

STDMETHODIMP CotScreenSketch::SetMousePoint(IotPoint* point)
{
	TT_GEOMETRY::geom::Coordinate coord;

	point->get_X(&coord.x);
	point->get_Y(&coord.y);

	m_pSketch->MouseMove(coord);

	return S_OK;
}

STDMETHODIMP CotScreenSketch::SetCircleCenter(IotPoint* point)
{
	TT_GEOMETRY::geom::Coordinate coord;

	point->get_X(&coord.x);
	point->get_Y(&coord.y);

	m_pSketch->SetCircleCenter(coord);

	return S_OK;
}

STDMETHODIMP CotScreenSketch::SetEllipseTopLeft(IotPoint* point)
{
	TT_GEOMETRY::geom::Coordinate coord;

	point->get_X(&coord.x);
	point->get_Y(&coord.y);

	m_pSketch->SetEllipseTopLeft(coord);

	return S_OK;
}

STDMETHODIMP CotScreenSketch::SetRectTopLeft(IotPoint* point)
{
	TT_GEOMETRY::geom::Coordinate coord;

	point->get_X(&coord.x);
	point->get_Y(&coord.y);

	m_pSketch->SetRectTopLeft(coord);

	return S_OK;
}
