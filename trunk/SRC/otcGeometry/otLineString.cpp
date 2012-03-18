// otLineString.cpp : CotLineString 的实现

#include "stdafx.h"
#include "otLineString.h"
#include "InterfaceConvert.h"

// CotLineString
CotLineString::CotLineString()
{
	m_pGeometry =GEOMETRY::geom::GeometryFactory::getDefaultInstance()->createLineString();
	m_bAutoDestroy =true;
}

CotLineString::~CotLineString()
{
	if(m_bAutoDestroy && m_pGeometry)
	{
		GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(m_pGeometry);
	}
}


/***************************************************************************************
* 实现IotLineString接口
*
***************************************************************************************/
STDMETHODIMP CotLineString::IsClosed(VARIANT_BOOL* bRet)
{
	if(!m_pGeometry)
	{
		return E_FAIL;
	}
	*bRet =m_pGeometry->isClosed()? VARIANT_TRUE:VARIANT_FALSE;
    
	return S_OK;
}

STDMETHODIMP CotLineString::get_Length(DOUBLE* pVal)
{
	if(!m_pGeometry)
	{
		return E_FAIL;
	}
	*pVal =m_pGeometry->getLength();

	return S_OK;
}

STDMETHODIMP CotLineString::get_StartPoint(IotPoint** pVal)
{
	if(!m_pGeometry)
	{
		*pVal =NULL;
		return E_FAIL;
	}

	if(m_pGeometry->isEmpty())
	{
		*pVal =NULL;
		return E_FAIL;
	}

	GEOMETRY::geom::Coordinate coord =m_pGeometry->GetPoint(0);

	CoCreateInstance(CLSID_otPoint,NULL,CLSCTX_INPROC_SERVER,__uuidof(IotPoint),(void**)pVal);

	(*pVal)->put_X(coord.x);
	(*pVal)->put_Y(coord.y);
	(*pVal)->put_Z(coord.z);
	(*pVal)->put_M(coord.m);


	return S_OK;
}

STDMETHODIMP CotLineString::put_StartPoint(IotPoint* newVal)
{
	
	if(!m_pGeometry)
	{
		
		return E_FAIL;
	}

	if(m_pGeometry->isEmpty())
	{
		
		return E_FAIL;
	}
    GEOMETRY::geom::Coordinate coord;

	newVal->get_X(&coord.x);
	newVal->get_Y(&coord.y);
	newVal->get_Z(&coord.z);
	newVal->get_M(&coord.m);

	//替换第一个点
	m_pGeometry->ReplacePoint(0,coord);

	return S_OK;
}

STDMETHODIMP CotLineString::get_EndPoint(IotPoint** pVal)
{
	if(!m_pGeometry)
	{
		*pVal =NULL;
		return E_FAIL;
	}

	if(m_pGeometry->isEmpty())
	{
		*pVal =NULL;
		return E_FAIL;
	}
	GEOMETRY::geom::Coordinate coord =m_pGeometry->GetPoint(m_pGeometry->PointCount()-1);

	CoCreateInstance(CLSID_otPoint,NULL,CLSCTX_INPROC_SERVER,__uuidof(IotPoint),(void**)pVal);

	(*pVal)->put_X(coord.x);
	(*pVal)->put_Y(coord.y);
	(*pVal)->put_Z(coord.z);
	(*pVal)->put_M(coord.m);

	return S_OK;
}

STDMETHODIMP CotLineString::put_EndPoint(IotPoint* newVal)
{
	if(!m_pGeometry)
	{

		return E_FAIL;
	}

	if(m_pGeometry->isEmpty())
	{

		return E_FAIL;
	}
	GEOMETRY::geom::Coordinate coord;

	newVal->get_X(&coord.x);
	newVal->get_Y(&coord.y);
	newVal->get_Z(&coord.z);
	newVal->get_M(&coord.m);

	//替换最后一个点
	m_pGeometry->ReplacePoint(m_pGeometry->PointCount()-1,coord);

	return S_OK;
}

/*****************************************************************************
* 实现IOriginData接口
******************************************************************************/
STDMETHODIMP CotLineString::get_OriginData(long * pVal)
{

	*pVal =(long)m_pGeometry;
	return S_OK;
}

STDMETHODIMP CotLineString::put_OriginData(long  pVal)
{

	if(m_pGeometry && m_bAutoDestroy)
	{
		delete m_pGeometry;
	}

	m_pGeometry =(GEOMETRY::geom::LineString*)(pVal);

	return S_OK;
}

STDMETHODIMP CotLineString::get_AutoDestroy(long * pVal)
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

STDMETHODIMP CotLineString::put_AutoDestroy(long  pVal)
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

STDMETHODIMP CotLineString::get_GeometryType( otGeometryType * pVal)
{
	*pVal =OT_GEOM_LINESTRING;
	return S_OK;
}
STDMETHODIMP CotLineString::get_PointCount( LONG * pVal)
{
	if(!m_pGeometry)
	{

		return E_FAIL;
	}
	*pVal =m_pGeometry->PointCount();

	return S_OK;
}
STDMETHODIMP CotLineString::GetEnvelope( IotEnvelope * * envelope)
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
STDMETHODIMP CotLineString::get_HasZ( VARIANT_BOOL * pVal)
{
	if(!m_pGeometry)
	{
		return E_FAIL;
	}
	*pVal =(m_pGeometry)->HasZ() ? VARIANT_TRUE:VARIANT_FALSE;
	return S_OK;
}
STDMETHODIMP CotLineString::put_HasZ( VARIANT_BOOL newVal)
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
STDMETHODIMP CotLineString::get_HasM( VARIANT_BOOL * pVal)
{
	if(!m_pGeometry)
	{
		return E_FAIL;
	}
	*pVal =(m_pGeometry)->HasM() ? VARIANT_TRUE:VARIANT_FALSE;
	return S_OK;
}
STDMETHODIMP CotLineString::put_HasM( VARIANT_BOOL newVal)
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
STDMETHODIMP CotLineString::get_IsEmpty( VARIANT_BOOL * pVal)
{
	if(!m_pGeometry)
	{
		return E_FAIL;
	}

    *pVal =m_pGeometry->isEmpty()? VARIANT_TRUE:VARIANT_FALSE;
	return S_OK;
}
STDMETHODIMP CotLineString::SetEmpty()
{
	if(!m_pGeometry)
	{
		return E_FAIL;
	}
	m_pGeometry->SetEmpty();
	return S_OK;
}
STDMETHODIMP CotLineString::Clone( IotGeometry * * geometry)
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
STDMETHODIMP CotLineString::get_IsValid( VARIANT_BOOL * pVal)
{
	if(!m_pGeometry)
	{
		return E_FAIL;
	}
	*pVal =(m_pGeometry->isValid())?VARIANT_TRUE:VARIANT_FALSE;

	return S_OK;
}
STDMETHODIMP CotLineString::Disjoint( IotGeometry * other,  VARIANT_BOOL * bRet)
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
STDMETHODIMP CotLineString::Touches( IotGeometry * other,  VARIANT_BOOL * bRet)
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
STDMETHODIMP CotLineString::Intersects( IotGeometry * other,  VARIANT_BOOL * bRet)
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
STDMETHODIMP CotLineString::Crosses( IotGeometry * other,  VARIANT_BOOL * bRet)
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
STDMETHODIMP CotLineString::Within( IotGeometry * other,  VARIANT_BOOL * bRet)
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
STDMETHODIMP CotLineString::Overlaps( IotGeometry * other,  VARIANT_BOOL * bRet)
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
STDMETHODIMP CotLineString::Equals( IotGeometry * other,  VARIANT_BOOL * bRet)
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
STDMETHODIMP CotLineString::Covers( IotGeometry * other,  VARIANT_BOOL * bRet)
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
STDMETHODIMP CotLineString::ConvexHull( IotGeometry * * retGeometry)
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

STDMETHODIMP CotLineString::Buffer( DOUBLE distance,  IotGeometry * * retGeometry)
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
STDMETHODIMP CotLineString::Intersection( IotGeometry * other,  IotGeometry * * retGeometry)
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
STDMETHODIMP CotLineString::Union( IotGeometry * other,  IotGeometry * * retGeometry)
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
STDMETHODIMP CotLineString::Difference( IotGeometry * other,  IotGeometry * * retGeometry)
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
STDMETHODIMP CotLineString::SymDifference( IotGeometry * other,  IotGeometry * * retGeometry)
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
* 实现IotPointCollection接口
*
***************************************************************************************/

STDMETHODIMP CotLineString::get_Point(LONG index, IotPoint **pVal)
{

	if(!m_pGeometry)
	{
		return E_FAIL;
	}
	GEOMETRY::geom::Coordinate coord =m_pGeometry->GetPoint(index);

	CoCreateInstance(CLSID_otPoint,NULL,CLSCTX_INPROC_SERVER,__uuidof(IotPoint),(void**)pVal);

	(*pVal)->put_X(coord.x);
	(*pVal)->put_Y(coord.y);
	(*pVal)->put_Z(coord.z);
	(*pVal)->put_M(coord.m);

    return S_OK;
}

STDMETHODIMP CotLineString::get_PointNum(LONG *pVal)
{
	if(!m_pGeometry)
	{

		return E_FAIL;
	}
	*pVal =m_pGeometry->PointCount();

   return S_OK;
}

STDMETHODIMP CotLineString::InsertPoint(LONG index, IotPoint *point)
{
	if(!m_pGeometry)
	{

		return E_FAIL;
	}
	GEOMETRY::geom::Coordinate coord;
	point->get_X(&coord.x);
	point->get_Y(&coord.y);
	point->get_Z(&coord.z);
	point->get_M(&coord.m);

	m_pGeometry->InsertPoint(index,coord);

	return S_OK;
}

STDMETHODIMP CotLineString::RemovePoint(LONG index)
{
	if(!m_pGeometry)
	{

		return E_FAIL;
	}
	m_pGeometry->RemovePoint(index);
	return S_OK;
}

STDMETHODIMP CotLineString::ReplacePoint(LONG index, IotPoint *point)
{
	if(!m_pGeometry)
	{

		return E_FAIL;
	}
	GEOMETRY::geom::Coordinate coord;
	point->get_X(&coord.x);
	point->get_Y(&coord.y);
	point->get_Z(&coord.z);
	point->get_M(&coord.m);

	m_pGeometry->ReplacePoint(index,coord);
	return S_OK;
}

STDMETHODIMP CotLineString::AddPoint(IotPoint *point)
{
	if(!m_pGeometry)
	{

		return E_FAIL;
	}
	GEOMETRY::geom::Coordinate coord;
	point->get_X(&coord.x);
	point->get_Y(&coord.y);
	point->get_Z(&coord.z);
	point->get_M(&coord.m);

	m_pGeometry->AddPoint(coord);
	return S_OK;
}

/***************************************************************************************
* 实现IotGeometry接口
*
***************************************************************************************/

STDMETHODIMP CotLineString::Move(DOUBLE dx, DOUBLE dy)
{
	if(!m_pGeometry)
	{
		return E_FAIL;
	}


	m_pGeometry->Move(dx,dy);

	return S_OK;

}

STDMETHODIMP CotLineString::Scale(IotPoint * Origin,  DOUBLE dx,  DOUBLE dy)
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

STDMETHODIMP CotLineString::Rotate( IotPoint * Origin,  DOUBLE angle)
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



/***************************************************************************************
* 实现IotSegmentCollection接口
*
***************************************************************************************/

STDMETHODIMP CotLineString::get_SegmentCount( LONG * pVal)
{
	if(!m_pGeometry)
	{
		return E_FAIL;
	}
	*pVal =m_pGeometry->SegmentCount();

	return S_OK;

}

STDMETHODIMP CotLineString::AddSegment(IotSegment * segment)
{
	if(!m_pGeometry)
	{
		return E_FAIL;
	}
	if(!segment)
	{
		return S_OK;
	}
    
	//抽取Segment指针
	IotGeometry *pGeo =NULL;
	segment->QueryInterface(__uuidof(IotGeometry),(void**)&pGeo);

	GEOMETRY::geom::Geometry* pg =CInterfaceConvert::ConvertIGeo(pGeo);

	m_pGeometry->AddSegment((GEOMETRY::geom::ISegment*)(pg->clone()));

	pGeo->Release();

	return S_OK;
}

STDMETHODIMP CotLineString::GetSegment(LONG index,  IotSegment * * ret)
{
	if(!m_pGeometry)
	{
		return E_FAIL;
	}
	GEOMETRY::geom::Geometry *pg =m_pGeometry->GetSegment(index);

	if(!pg)
	{
		*ret =NULL;
		return S_OK;
	}
	pg =pg->clone();
	IotGeometry *pGeo =NULL;
	CInterfaceConvert::ConvertGeo(pg,&pGeo);

	if(!pGeo)
	{
		*ret =NULL;
		return S_OK;
	}

	pGeo->QueryInterface(__uuidof(IotSegment),(void**)ret);

	pGeo->Release();

	return S_OK;
}