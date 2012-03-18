// otGeoConvert.cpp : CotGeoConvert µÄÊµÏÖ

#include "stdafx.h"
#include "otGeoConvert.h"
#include "InterfaceConvert.h"

// CotGeoConvert


STDMETHODIMP CotGeoConvert::ConvertGeo(LONG p, VARIANT_BOOL bown, IotGeometry** retGeo)
{
	GEOMETRY::geom::Geometry *pGeometry =(GEOMETRY::geom::Geometry*)p;

	CInterfaceConvert::ConvertGeo(pGeometry,retGeo,(bown==VARIANT_FALSE)?false:true);


	return S_OK;
}

STDMETHODIMP CotGeoConvert::ConvertIGeo(IotGeometry* geometry, LONG* ret)
{
	GEOMETRY::geom::Geometry *pGeometry=NULL;

	pGeometry =CInterfaceConvert::ConvertIGeo(geometry);

	*ret =(long)pGeometry;
    
	return S_OK;
}
