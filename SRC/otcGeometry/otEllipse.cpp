// otEllipse.cpp : CotEllipse 的实现

#include "stdafx.h"
#include "otEllipse.h"
#include "InterfaceConvert.h"

// CotEllipse
CotEllipse::CotEllipse()
{
	m_pGeometry =GEOMETRY::geom::GeometryFactory::getDefaultInstance()->createEllipse();
	m_bAutoDestroy =true;
}

CotEllipse::~CotEllipse()
{
	if(m_bAutoDestroy && m_pGeometry)
	{
		GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(m_pGeometry);
	}
}


STDMETHODIMP CotEllipse::get_CenterPoint(IotPoint** pVal)
{
	if(!m_pGeometry)
	{
		return E_FAIL;
	}
	GEOMETRY::geom::Coordinate coord =m_pGeometry->GetCenterPoint();

	CoCreateInstance(CLSID_otPoint,NULL,CLSCTX_INPROC_SERVER,__uuidof(IotPoint),(void**)pVal);

	(*pVal)->put_X(coord.x);
	(*pVal)->put_Y(coord.y);
	(*pVal)->put_Z(coord.z);
	(*pVal)->put_M(coord.m);

	return S_OK;
}

STDMETHODIMP CotEllipse::put_CenterPoint(IotPoint* newVal)
{
	if(!m_pGeometry)
	{
		return E_FAIL;
	}
	GEOMETRY::geom::Coordinate coord;
	newVal->get_X(&coord.x);
	newVal->get_Y(&coord.y);

	m_pGeometry->SetCenterPoint(coord);


	return S_OK;
}

STDMETHODIMP CotEllipse::GetAxes(DOUBLE* semiMajor, DOUBLE* semiMinor)
{
	if(!m_pGeometry)
	{
		return E_FAIL;
	}
	m_pGeometry->GetAxes(semiMajor,semiMinor);

	return S_OK;
}

STDMETHODIMP CotEllipse::SetAxes(DOUBLE semiMajor, DOUBLE semiMinor)
{
	if(!m_pGeometry)
	{
		return E_FAIL;
	}
    
	m_pGeometry->SetAxes(semiMajor,semiMinor);
	return S_OK;
}

/*****************************************************************************
* 实现IOriginData接口
******************************************************************************/
STDMETHODIMP CotEllipse::get_OriginData(long * pVal)
{

	*pVal =(long)m_pGeometry;
	return S_OK;
}

STDMETHODIMP CotEllipse::put_OriginData(long  pVal)
{

	if(m_pGeometry && m_bAutoDestroy)
	{
		delete m_pGeometry;
	}

	m_pGeometry =(GEOMETRY::geom::Ellipse*)(pVal);

	return S_OK;
}

STDMETHODIMP CotEllipse::get_AutoDestroy(long * pVal)
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

STDMETHODIMP CotEllipse::put_AutoDestroy(long  pVal)
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

STDMETHODIMP CotEllipse::get_GeometryType( otGeometryType * pVal)
{
	*pVal =OT_GEOM_ELLIPSE;
	return S_OK;
}
STDMETHODIMP CotEllipse::get_PointCount( LONG * pVal)
{
	if(!m_pGeometry)
	{

		return E_FAIL;
	}
	*pVal =m_pGeometry->PointCount();

	return S_OK;
}
STDMETHODIMP CotEllipse::GetEnvelope( IotEnvelope * * envelope)
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
STDMETHODIMP CotEllipse::get_HasZ( VARIANT_BOOL * pVal)
{
	if(!m_pGeometry)
	{
		return E_FAIL;
	}
	*pVal =(m_pGeometry)->HasZ() ? VARIANT_TRUE:VARIANT_FALSE;
	return S_OK;
}
STDMETHODIMP CotEllipse::put_HasZ( VARIANT_BOOL newVal)
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
STDMETHODIMP CotEllipse::get_HasM( VARIANT_BOOL * pVal)
{
	if(!m_pGeometry)
	{
		return E_FAIL;
	}
	*pVal =(m_pGeometry)->HasM() ? VARIANT_TRUE:VARIANT_FALSE;
	return S_OK;
}
STDMETHODIMP CotEllipse::put_HasM( VARIANT_BOOL newVal)
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
STDMETHODIMP CotEllipse::get_IsEmpty( VARIANT_BOOL * pVal)
{
	if(!m_pGeometry)
	{
		return E_FAIL;
	}

	*pVal =m_pGeometry->isEmpty()? VARIANT_TRUE:VARIANT_FALSE;
	return S_OK;
}
STDMETHODIMP CotEllipse::SetEmpty()
{
	if(!m_pGeometry)
	{
		return E_FAIL;
	}
	m_pGeometry->SetEmpty();
	return S_OK;
}
STDMETHODIMP CotEllipse::Clone( IotGeometry * * geometry)
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
STDMETHODIMP CotEllipse::get_IsValid( VARIANT_BOOL * pVal)
{
	if(!m_pGeometry)
	{
		return E_FAIL;
	}
	*pVal =(m_pGeometry->isValid())?VARIANT_TRUE:VARIANT_FALSE;

	return S_OK;
}
STDMETHODIMP CotEllipse::Disjoint( IotGeometry * other,  VARIANT_BOOL * bRet)
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
STDMETHODIMP CotEllipse::Touches( IotGeometry * other,  VARIANT_BOOL * bRet)
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
STDMETHODIMP CotEllipse::Intersects( IotGeometry * other,  VARIANT_BOOL * bRet)
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
STDMETHODIMP CotEllipse::Crosses( IotGeometry * other,  VARIANT_BOOL * bRet)
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
STDMETHODIMP CotEllipse::Within( IotGeometry * other,  VARIANT_BOOL * bRet)
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
STDMETHODIMP CotEllipse::Overlaps( IotGeometry * other,  VARIANT_BOOL * bRet)
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
STDMETHODIMP CotEllipse::Equals( IotGeometry * other,  VARIANT_BOOL * bRet)
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
STDMETHODIMP CotEllipse::Covers( IotGeometry * other,  VARIANT_BOOL * bRet)
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
STDMETHODIMP CotEllipse::ConvexHull( IotGeometry * * retGeometry)
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

STDMETHODIMP CotEllipse::Buffer( DOUBLE distance,  IotGeometry * * retGeometry)
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
STDMETHODIMP CotEllipse::Intersection( IotGeometry * other,  IotGeometry * * retGeometry)
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
STDMETHODIMP CotEllipse::Union( IotGeometry * other,  IotGeometry * * retGeometry)
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
STDMETHODIMP CotEllipse::Difference( IotGeometry * other,  IotGeometry * * retGeometry)
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
STDMETHODIMP CotEllipse::SymDifference( IotGeometry * other,  IotGeometry * * retGeometry)
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
* 实现IotGeometry接口
*
***************************************************************************************/

STDMETHODIMP CotEllipse::Move(DOUBLE dx, DOUBLE dy)
{
	if(!m_pGeometry)
	{
		return E_FAIL;
	}


	m_pGeometry->Move(dx,dy);

	return S_OK;

}

STDMETHODIMP CotEllipse::Scale(IotPoint * Origin,  DOUBLE dx,  DOUBLE dy)
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

STDMETHODIMP CotEllipse::Rotate( IotPoint * Origin,  DOUBLE angle)
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