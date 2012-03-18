// otMultiPolygon.cpp : CotMultiPolygon 的实现

#include "stdafx.h"
#include "otMultiPolygon.h"
#include "InterfaceConvert.h"

// CotMultiPolygon
CotMultiPolygon::CotMultiPolygon()
{
	m_pGeometry =GEOMETRY::geom::GeometryFactory::getDefaultInstance()->createMultiPolygon();
	m_bAutoDestroy =true;
}

CotMultiPolygon::~CotMultiPolygon()
{
	if(m_bAutoDestroy && m_pGeometry)
	{
		GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(m_pGeometry);
	}
}

STDMETHODIMP CotMultiPolygon::get_Area(DOUBLE* pVal)
{
	if(!m_pGeometry)
	{
		return E_FAIL;
	}
	*pVal =m_pGeometry->getArea();
    
	return S_OK;
}


/*****************************************************************************
* 实现IOriginData接口
******************************************************************************/
STDMETHODIMP CotMultiPolygon::get_OriginData(long * pVal)
{

	*pVal =(long)m_pGeometry;
	return S_OK;
}

STDMETHODIMP CotMultiPolygon::put_OriginData(long  pVal)
{

	if(m_pGeometry && m_bAutoDestroy)
	{
		delete m_pGeometry;
	}

	m_pGeometry =(GEOMETRY::geom::MultiPolygon*)(pVal);

	return S_OK;
}

STDMETHODIMP CotMultiPolygon::get_AutoDestroy(long * pVal)
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

STDMETHODIMP CotMultiPolygon::put_AutoDestroy(long  pVal)
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

STDMETHODIMP CotMultiPolygon::get_GeometryType( otGeometryType * pVal)
{
	*pVal =OT_GEOM_MULTIPOLYGON;
	return S_OK;
}
STDMETHODIMP CotMultiPolygon::get_PointCount( LONG * pVal)
{
	if(!m_pGeometry)
	{

		return E_FAIL;
	}
	*pVal =m_pGeometry->PointCount();

	return S_OK;
}
STDMETHODIMP CotMultiPolygon::GetEnvelope( IotEnvelope * * envelope)
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
STDMETHODIMP CotMultiPolygon::get_HasZ( VARIANT_BOOL * pVal)
{
	if(!m_pGeometry)
	{
		return E_FAIL;
	}
	*pVal =(m_pGeometry)->HasZ() ? VARIANT_TRUE:VARIANT_FALSE;
	return S_OK;
}
STDMETHODIMP CotMultiPolygon::put_HasZ( VARIANT_BOOL newVal)
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
STDMETHODIMP CotMultiPolygon::get_HasM( VARIANT_BOOL * pVal)
{
	if(!m_pGeometry)
	{
		return E_FAIL;
	}
	*pVal =(m_pGeometry)->HasM() ? VARIANT_TRUE:VARIANT_FALSE;
	return S_OK;
}
STDMETHODIMP CotMultiPolygon::put_HasM( VARIANT_BOOL newVal)
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
STDMETHODIMP CotMultiPolygon::get_IsEmpty( VARIANT_BOOL * pVal)
{
	if(!m_pGeometry)
	{
		return E_FAIL;
	}

	*pVal =m_pGeometry->isEmpty()? VARIANT_TRUE:VARIANT_FALSE;
	return S_OK;
}
STDMETHODIMP CotMultiPolygon::SetEmpty()
{
	if(!m_pGeometry)
	{
		return E_FAIL;
	}
	m_pGeometry->SetEmpty();
	return S_OK;
}
STDMETHODIMP CotMultiPolygon::Clone( IotGeometry * * geometry)
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
STDMETHODIMP CotMultiPolygon::get_IsValid( VARIANT_BOOL * pVal)
{
	if(!m_pGeometry)
	{
		return E_FAIL;
	}
	*pVal =(m_pGeometry->isValid())?VARIANT_TRUE:VARIANT_FALSE;

	return S_OK;
}
STDMETHODIMP CotMultiPolygon::Disjoint( IotGeometry * other,  VARIANT_BOOL * bRet)
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
STDMETHODIMP CotMultiPolygon::Touches( IotGeometry * other,  VARIANT_BOOL * bRet)
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
STDMETHODIMP CotMultiPolygon::Intersects( IotGeometry * other,  VARIANT_BOOL * bRet)
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
STDMETHODIMP CotMultiPolygon::Crosses( IotGeometry * other,  VARIANT_BOOL * bRet)
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
STDMETHODIMP CotMultiPolygon::Within( IotGeometry * other,  VARIANT_BOOL * bRet)
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
STDMETHODIMP CotMultiPolygon::Overlaps( IotGeometry * other,  VARIANT_BOOL * bRet)
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
STDMETHODIMP CotMultiPolygon::Equals( IotGeometry * other,  VARIANT_BOOL * bRet)
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
STDMETHODIMP CotMultiPolygon::Covers( IotGeometry * other,  VARIANT_BOOL * bRet)
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
STDMETHODIMP CotMultiPolygon::ConvexHull( IotGeometry * * retGeometry)
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

STDMETHODIMP CotMultiPolygon::Buffer( DOUBLE distance,  IotGeometry * * retGeometry)
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
STDMETHODIMP CotMultiPolygon::Intersection( IotGeometry * other,  IotGeometry * * retGeometry)
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
STDMETHODIMP CotMultiPolygon::Union( IotGeometry * other,  IotGeometry * * retGeometry)
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
STDMETHODIMP CotMultiPolygon::Difference( IotGeometry * other,  IotGeometry * * retGeometry)
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
STDMETHODIMP CotMultiPolygon::SymDifference( IotGeometry * other,  IotGeometry * * retGeometry)
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
* 实现IotGeometryCollection接口
*
***************************************************************************************/

STDMETHODIMP CotMultiPolygon::get_GeometryCount(LONG *pVal)
{
	if(!m_pGeometry)
	{
		return E_FAIL;
	}
	*pVal =(long)m_pGeometry->getNumGeometries();

	return S_OK;
}

STDMETHODIMP CotMultiPolygon::GetGeometry(LONG index, IotGeometry **retGeometry)
{
	if(!m_pGeometry)
	{
		return E_FAIL;
	}
	GEOMETRY::geom::Geometry *pg =m_pGeometry->GetGeometry(index);
	if(!pg)
	{
		*retGeometry =NULL;
		return E_FAIL;
	}
	//返回的图形对象不接管内部指针的控制权
	CInterfaceConvert::ConvertGeo(pg,retGeometry,false);

	return S_OK;
}

STDMETHODIMP CotMultiPolygon::AddGeometry(IotGeometry *geometry)
{

	if(!m_pGeometry)
	{
		return E_FAIL;
	}
	otGeometryType type;
	geometry->get_GeometryType(&type);

	//如果不是线类型，返回
	if(type!=OT_GEOM_POLYGON)
	{
		return E_FAIL;
	}

	GEOMETRY::geom::Geometry *pg =CInterfaceConvert::ConvertIGeo(geometry);

	if(!pg)
	{
		return E_FAIL;
	}
	m_pGeometry->AddGeometry(pg->clone());

	return S_OK;
}

/***************************************************************************************
* 实现IotTransform接口
*
***************************************************************************************/

STDMETHODIMP CotMultiPolygon::Move(DOUBLE dx, DOUBLE dy)
{
	if(!m_pGeometry)
	{
		return E_FAIL;
	}


	m_pGeometry->Move(dx,dy);

	return S_OK;

}

STDMETHODIMP CotMultiPolygon::Scale(IotPoint * Origin,  DOUBLE dx,  DOUBLE dy)
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

STDMETHODIMP CotMultiPolygon::Rotate( IotPoint * Origin,  DOUBLE angle)
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