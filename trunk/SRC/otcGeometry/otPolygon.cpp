// otPolygon.cpp : CotPolygon 的实现

#include "stdafx.h"
#include "otPolygon.h"
#include "InterfaceConvert.h"

// CotPolygon
CotPolygon::CotPolygon()
{
	m_pGeometry =GEOMETRY::geom::GeometryFactory::getDefaultInstance()->createPolygon();
	m_bAutoDestroy =true;
}

CotPolygon::~CotPolygon()
{
	if(m_bAutoDestroy && m_pGeometry)
	{
		GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(m_pGeometry);
	}

}

/***************************************************************************************
* 实现IotPolygon接口
*
***************************************************************************************/

STDMETHODIMP CotPolygon::get_InteriorRingCount(LONG* pVal)
{
	if(!m_pGeometry)
	{
		return E_FAIL;
	}
	*pVal =m_pGeometry->getNumInteriorRing();
   
	return S_OK;
}

STDMETHODIMP CotPolygon::get_Area(DOUBLE* pVal)
{
	if(!m_pGeometry)
	{
		return E_FAIL;
	}
	*pVal =m_pGeometry->getArea();

	return S_OK;
}

STDMETHODIMP CotPolygon::get_ExteriorRing(IotLineRing** pVal)
{
	if(!m_pGeometry)
	{
		*pVal =NULL;
		return E_FAIL;
	}
	GEOMETRY::geom::LineString *pring =const_cast<GEOMETRY::geom::LineString*>(m_pGeometry->getExteriorRing());
	if(!pring)
	{
		*pVal =NULL;
		return E_FAIL;
	}

	IotGeometry *pg;
	CInterfaceConvert::ConvertGeo(dynamic_cast<GEOMETRY::geom::Geometry*>(pring),&pg,false);

	pg->QueryInterface(__uuidof(IotLineRing),(void**)pVal);

	pg->Release();

    
	return S_OK;
}

STDMETHODIMP CotPolygon::put_ExteriorRing(IotLineRing* newVal)
{
	if(!m_pGeometry || !newVal)
	{
		return E_FAIL;
	}
    IotGeometry *pg =NULL;
	newVal->QueryInterface(__uuidof(IotGeometry),(void**)&pg);
	GEOMETRY::geom::Geometry *pgeo =CInterfaceConvert::ConvertIGeo(pg);
	m_pGeometry->SetExteriorRing(dynamic_cast<GEOMETRY::geom::LinearRing*>(pgeo->clone()));

    pg->Release();

	return S_OK;
}

STDMETHODIMP CotPolygon::get_InteriorRing(LONG index, IotLineRing** pVal)
{
	
	if(!m_pGeometry)
	{
		*pVal =NULL;
		return E_FAIL;
	}

	GEOMETRY::geom::LineString *pring =const_cast<GEOMETRY::geom::LineString*>(m_pGeometry->getInteriorRingN(index));
	if(!pring)
	{
		*pVal =NULL;
		return E_FAIL;
	}

	IotGeometry *pg;
	CInterfaceConvert::ConvertGeo(dynamic_cast<GEOMETRY::geom::Geometry*>(pring),&pg,false);

	pg->QueryInterface(__uuidof(IotLineRing),(void**)pVal);

	pg->Release();
	return S_OK;
}

STDMETHODIMP CotPolygon::put_InteriorRing(LONG index, IotLineRing* newVal)
{
	// TODO: 在此添加实现代码

	return S_OK;
}

STDMETHODIMP CotPolygon::AddInteriorRing(IotLineRing* ring)
{
	// TODO: 在此添加实现代码

	return S_OK;
}

/*****************************************************************************
* 实现IOriginData接口
******************************************************************************/
STDMETHODIMP CotPolygon::get_OriginData(long * pVal)
{

	*pVal =(long)m_pGeometry;
	return S_OK;
}

STDMETHODIMP CotPolygon::put_OriginData(long  pVal)
{

	if(m_pGeometry && m_bAutoDestroy)
	{
		delete m_pGeometry;
	}

	m_pGeometry =(GEOMETRY::geom::Polygon*)(pVal);

	return S_OK;
}

STDMETHODIMP CotPolygon::get_AutoDestroy(long * pVal)
{

	if(m_bAutoDestroy)
	{
		*pVal =TRUE;
	}
	else
	{
		*pVal =FALSE;
	}
	return S_OK;
}

STDMETHODIMP CotPolygon::put_AutoDestroy(long  pVal)
{

	if(pVal)
	{
		m_bAutoDestroy =true;
	}
	else
	{
		m_bAutoDestroy =false;
	}
	return S_OK;
}

/***************************************************************************************
* 实现IotGeometry接口
*
***************************************************************************************/

STDMETHODIMP CotPolygon::get_GeometryType( otGeometryType * pVal)
{
	*pVal =OT_GEOM_POLYGON;
	return S_OK;
}
STDMETHODIMP CotPolygon::get_PointCount( LONG * pVal)
{
	if(!m_pGeometry)
	{

		return E_FAIL;
	}
	*pVal =m_pGeometry->PointCount();

	return S_OK;
}
STDMETHODIMP CotPolygon::GetEnvelope( IotEnvelope * * envelope)
{

	if(!m_pGeometry)
	{
		*envelope =NULL;
		return E_FAIL;
	}

	CoCreateInstance(CLSID_otEnvelope,NULL,CLSCTX_INPROC_SERVER,__uuidof(IotEnvelope),(void**)envelope);

	GEOMETRY::geom::Envelope extent =*(m_pGeometry->getEnvelopeInternal());

	(*envelope)->put_MinX(extent.getMinX());
	(*envelope)->put_MinY(extent.getMinY());
	(*envelope)->put_MaxX(extent.getMaxX());
	(*envelope)->put_MaxY(extent.getMaxY());


	return S_OK;
}
STDMETHODIMP CotPolygon::get_HasZ( VARIANT_BOOL * pVal)
{
	if(!m_pGeometry)
	{
		return E_FAIL;
	}
	*pVal =(m_pGeometry)->HasZ() ? VARIANT_TRUE:VARIANT_FALSE;
	return S_OK;
}
STDMETHODIMP CotPolygon::put_HasZ( VARIANT_BOOL newVal)
{
	if(!m_pGeometry)
	{
		return E_FAIL;
	}
	if(newVal ==VARIANT_FALSE)
	{
		(m_pGeometry)->SetbZ(false);
	}
	else
	{
		(m_pGeometry)->SetbZ(true);
	}
	return S_OK;
}
STDMETHODIMP CotPolygon::get_HasM( VARIANT_BOOL * pVal)
{
	if(!m_pGeometry)
	{
		return E_FAIL;
	}
	*pVal =(m_pGeometry)->HasM() ? VARIANT_TRUE:VARIANT_FALSE;
	return S_OK;
}
STDMETHODIMP CotPolygon::put_HasM( VARIANT_BOOL newVal)
{
	if(!m_pGeometry)
	{
		return E_FAIL;
	}
	if(newVal ==VARIANT_FALSE)
	{
		m_pGeometry->SetbM(false);
	}
	else
	{
		m_pGeometry->SetbM(true);
	}
	return S_OK;
}
STDMETHODIMP CotPolygon::get_IsEmpty( VARIANT_BOOL * pVal)
{
	if(!m_pGeometry)
	{
		return E_FAIL;
	}

	*pVal =m_pGeometry->isEmpty()? VARIANT_TRUE:VARIANT_FALSE;
	return S_OK;
}
STDMETHODIMP CotPolygon::SetEmpty()
{
	if(!m_pGeometry)
	{
		return E_FAIL;
	}
	m_pGeometry->SetEmpty();
	return S_OK;
}
STDMETHODIMP CotPolygon::Clone( IotGeometry * * geometry)
{


	if(!m_pGeometry)
	{
		*geometry =NULL;
		return E_FAIL;
	}
	GEOMETRY::geom::Geometry *pg =m_pGeometry->clone();
	CInterfaceConvert::ConvertGeo(pg,geometry);

	return S_OK;
}
STDMETHODIMP CotPolygon::get_IsValid( VARIANT_BOOL * pVal)
{
	if(!m_pGeometry)
	{
		return E_FAIL;
	}
	*pVal =(m_pGeometry->isValid())?VARIANT_TRUE:VARIANT_FALSE;

	return S_OK;
}
STDMETHODIMP CotPolygon::Disjoint( IotGeometry * other,  VARIANT_BOOL * bRet)
{
	if(!m_pGeometry)
	{
		return E_FAIL;
	}
	GEOMETRY::geom::Geometry *pg =CInterfaceConvert::ConvertIGeo(other);
	if(!pg)
	{
		return E_FAIL;
	}
	*bRet =(m_pGeometry->disjoint(pg))?VARIANT_TRUE:VARIANT_FALSE;
	return S_OK;
}
STDMETHODIMP CotPolygon::Touches( IotGeometry * other,  VARIANT_BOOL * bRet)
{
	if(!m_pGeometry)
	{
		return E_FAIL;
	}
	GEOMETRY::geom::Geometry *pg =CInterfaceConvert::ConvertIGeo(other);
	if(!pg)
	{
		return E_FAIL;
	}
	*bRet =(m_pGeometry->touches(pg))?VARIANT_TRUE:VARIANT_FALSE;

	return S_OK;
}
STDMETHODIMP CotPolygon::Intersects( IotGeometry * other,  VARIANT_BOOL * bRet)
{

	if(!m_pGeometry)
	{
		return E_FAIL;
	}
	GEOMETRY::geom::Geometry *pg =CInterfaceConvert::ConvertIGeo(other);
	if(!pg)
	{
		return E_FAIL;
	}
	*bRet =(m_pGeometry->intersects(pg))?VARIANT_TRUE:VARIANT_FALSE;

	return S_OK;
}
STDMETHODIMP CotPolygon::Crosses( IotGeometry * other,  VARIANT_BOOL * bRet)
{

	if(!m_pGeometry)
	{
		return E_FAIL;
	}
	GEOMETRY::geom::Geometry *pg =CInterfaceConvert::ConvertIGeo(other);
	if(!pg)
	{
		return E_FAIL;
	}
	*bRet =(m_pGeometry->crosses(pg))?VARIANT_TRUE:VARIANT_FALSE;

	return S_OK;
}
STDMETHODIMP CotPolygon::Within( IotGeometry * other,  VARIANT_BOOL * bRet)
{

	if(!m_pGeometry)
	{
		return E_FAIL;
	}
	GEOMETRY::geom::Geometry *pg =CInterfaceConvert::ConvertIGeo(other);
	if(!pg)
	{
		return E_FAIL;
	}
	*bRet =(m_pGeometry->within(pg))?VARIANT_TRUE:VARIANT_FALSE;
	return S_OK;
}
STDMETHODIMP CotPolygon::Overlaps( IotGeometry * other,  VARIANT_BOOL * bRet)
{
	if(!m_pGeometry)
	{
		return E_FAIL;
	}
	GEOMETRY::geom::Geometry *pg =CInterfaceConvert::ConvertIGeo(other);
	if(!pg)
	{
		return E_FAIL;
	}
	*bRet =(m_pGeometry->overlaps(pg))?VARIANT_TRUE:VARIANT_FALSE;
	return S_OK;
}
STDMETHODIMP CotPolygon::Equals( IotGeometry * other,  VARIANT_BOOL * bRet)
{
	if(!m_pGeometry)
	{
		return E_FAIL;
	}
	GEOMETRY::geom::Geometry *pg =CInterfaceConvert::ConvertIGeo(other);
	if(!pg)
	{
		return E_FAIL;
	}
	*bRet =(m_pGeometry->equals(pg))?VARIANT_TRUE:VARIANT_FALSE;
	return S_OK;
}
STDMETHODIMP CotPolygon::Covers( IotGeometry * other,  VARIANT_BOOL * bRet)
{

	if(!m_pGeometry)
	{
		return E_FAIL;
	}
	GEOMETRY::geom::Geometry *pg =CInterfaceConvert::ConvertIGeo(other);
	if(!pg)
	{
		return E_FAIL;
	}
	*bRet =(m_pGeometry->covers(pg))?VARIANT_TRUE:VARIANT_FALSE;
	return S_OK;
}
STDMETHODIMP CotPolygon::ConvexHull( IotGeometry * * retGeometry)
{
	if(!m_pGeometry)
	{
		return E_FAIL;
	}
	GEOMETRY::geom::Geometry *pg =m_pGeometry->convexHull();

	if(!pg)
	{
		*retGeometry =NULL;
		return E_FAIL;
	}
	CInterfaceConvert::ConvertGeo(pg,retGeometry);

	return S_OK;
}

STDMETHODIMP CotPolygon::Buffer( DOUBLE distance,  IotGeometry * * retGeometry)
{
	if(!m_pGeometry)
	{
		return E_FAIL;
	}
	GEOMETRY::geom::Geometry *pg =m_pGeometry->buffer(distance);

	if(!pg)
	{
		*retGeometry =NULL;
		return E_FAIL;
	}
	CInterfaceConvert::ConvertGeo(pg,retGeometry);

	return S_OK;
}
STDMETHODIMP CotPolygon::Intersection( IotGeometry * other,  IotGeometry * * retGeometry)
{
	if(!m_pGeometry)
	{
		return E_FAIL;
	}
	GEOMETRY::geom::Geometry *pother =CInterfaceConvert::ConvertIGeo(other);
	if(!pother)
	{
		return E_FAIL;
	}
	GEOMETRY::geom::Geometry *pg =m_pGeometry->intersection(pother);

	if(!pg)
	{
		*retGeometry =NULL;
		return E_FAIL;
	}
	CInterfaceConvert::ConvertGeo(pg,retGeometry);

	return S_OK;
}
STDMETHODIMP CotPolygon::Union( IotGeometry * other,  IotGeometry * * retGeometry)
{
	if(!m_pGeometry)
	{
		return E_FAIL;
	}
	GEOMETRY::geom::Geometry *pother =CInterfaceConvert::ConvertIGeo(other);
	if(!pother)
	{
		return E_FAIL;
	}
	GEOMETRY::geom::Geometry *pg =m_pGeometry->Union(pother);

	if(!pg)
	{
		*retGeometry =NULL;
		return E_FAIL;
	}
	CInterfaceConvert::ConvertGeo(pg,retGeometry);
	return S_OK;
}
STDMETHODIMP CotPolygon::Difference( IotGeometry * other,  IotGeometry * * retGeometry)
{
	if(!m_pGeometry)
	{
		return E_FAIL;
	}
	GEOMETRY::geom::Geometry *pother =CInterfaceConvert::ConvertIGeo(other);
	if(!pother)
	{
		return E_FAIL;
	}
	GEOMETRY::geom::Geometry *pg =m_pGeometry->difference(pother);

	if(!pg)
	{
		*retGeometry =NULL;
		return E_FAIL;
	}
	CInterfaceConvert::ConvertGeo(pg,retGeometry);
	return S_OK;
}
STDMETHODIMP CotPolygon::SymDifference( IotGeometry * other,  IotGeometry * * retGeometry)
{
	if(!m_pGeometry)
	{
		return E_FAIL;
	}
	GEOMETRY::geom::Geometry *pother =CInterfaceConvert::ConvertIGeo(other);
	if(!pother)
	{
		return E_FAIL;
	}
	GEOMETRY::geom::Geometry *pg =m_pGeometry->symDifference(pother);

	if(!pg)
	{
		*retGeometry =NULL;
		return E_FAIL;
	}
	CInterfaceConvert::ConvertGeo(pg,retGeometry);
	return S_OK;
}

/***************************************************************************************
* 实现IotTransform接口
*
***************************************************************************************/

STDMETHODIMP CotPolygon::Move(DOUBLE dx, DOUBLE dy)
{
	if(!m_pGeometry)
	{
		return E_FAIL;
	}


	m_pGeometry->Move(dx,dy);

	return S_OK;

}

STDMETHODIMP CotPolygon::Scale(IotPoint * Origin,  DOUBLE dx,  DOUBLE dy)
{
	if(!m_pGeometry)
	{
		return E_FAIL;
	}
	if(!Origin)
	{
		return E_FAIL;
	}
    
	GEOMETRY::geom::Coordinate coord;
	Origin->get_X(&coord.x);
	Origin->get_Y(&coord.y);
	m_pGeometry->Scale(coord,dx,dy);

	return S_OK;

}

STDMETHODIMP CotPolygon::Rotate( IotPoint * Origin,  DOUBLE angle)
{
	if(!m_pGeometry)
	{
		return E_FAIL;
	}
	if(!Origin)
	{
		return E_FAIL;
	}

	GEOMETRY::geom::Coordinate coord;
	Origin->get_X(&coord.x);
	Origin->get_Y(&coord.y);
	m_pGeometry->Rotate(coord,angle);
	return S_OK;

}

