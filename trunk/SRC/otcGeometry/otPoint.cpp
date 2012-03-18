// otPoint.cpp : CotPoint 的实现

#include "stdafx.h"
#include "otPoint.h"
#include <geometry/geom/GeometryFactory.h>
#include <Geometry/geom/Point.h>
#include "InterfaceConvert.h"
// CotPoint



CotPoint::CotPoint()
{
	m_x =m_y =m_z =m_m =0.0;
	m_bm =m_bz =false;
}

STDMETHODIMP CotPoint::get_X(DOUBLE* pVal)
{
	// TODO: 在此添加实现代码
    
    *pVal =m_x;
	return S_OK;
}

STDMETHODIMP CotPoint::put_X(DOUBLE newVal)
{
	// TODO: 在此添加实现代码
    
	m_x =newVal;
		 
	return S_OK;
}

STDMETHODIMP CotPoint::get_Y(DOUBLE* pVal)
{
	// TODO: 在此添加实现代码
    
	*pVal =m_y;
	return S_OK;
}

STDMETHODIMP CotPoint::put_Y(DOUBLE newVal)
{
	// TODO: 在此添加实现代码
    m_y =newVal;
	return S_OK;
}

STDMETHODIMP CotPoint::get_Z(DOUBLE* pVal)
{
	// TODO: 在此添加实现代码
    *pVal =m_z;
	return S_OK;
}

STDMETHODIMP CotPoint::put_Z(DOUBLE newVal)
{
	// TODO: 在此添加实现代码
   
    m_z =newVal;

	return S_OK;
}

STDMETHODIMP CotPoint::get_M(DOUBLE* pVal)
{
	// TODO: 在此添加实现代码

	*pVal =m_m;
	return S_OK;
}

STDMETHODIMP CotPoint::put_M(DOUBLE newVal)
{
	// TODO: 在此添加实现代码

	m_m =newVal;
	return S_OK;
}
/***************************************************************************************
* 实现IotGeometry接口
*
***************************************************************************************/

STDMETHODIMP CotPoint::get_GeometryType( otGeometryType * pVal)
{
	*pVal =OT_GEOM_POINT;
	return S_OK;
}
STDMETHODIMP CotPoint::get_PointCount( LONG * pVal)
{
	*pVal =1;
	return S_OK;
}
STDMETHODIMP CotPoint::GetEnvelope( IotEnvelope * * envelope)
{
	
	CoCreateInstance(CLSID_otEnvelope,NULL,CLSCTX_INPROC_SERVER,__uuidof(IotEnvelope),(void**)envelope);
    
	(*envelope)->put_MinX(m_x);
	(*envelope)->put_MinY(m_y);
	(*envelope)->put_MaxX(m_x);
	(*envelope)->put_MaxY(m_y);


	return S_OK;
}
STDMETHODIMP CotPoint::get_HasZ( VARIANT_BOOL * pVal)
{
	*pVal =m_bz ? VARIANT_TRUE:VARIANT_FALSE;
	return S_OK;
}
STDMETHODIMP CotPoint::put_HasZ( VARIANT_BOOL newVal)
{
	if(newVal ==VARIANT_FALSE)
	{
		m_bz =false;
	}
	else
	{
		m_bz =true;
	}
	return S_OK;
}
STDMETHODIMP CotPoint::get_HasM( VARIANT_BOOL * pVal)
{
	*pVal =m_bm ? VARIANT_TRUE:VARIANT_FALSE;
	return S_OK;
}
STDMETHODIMP CotPoint::put_HasM( VARIANT_BOOL newVal)
{
	if(newVal ==VARIANT_FALSE)
	{
		m_bm =false;
	}
	else
	{
		m_bm =true;
	}
	return S_OK;
}
STDMETHODIMP CotPoint::get_IsEmpty( VARIANT_BOOL * pVal)
{
	*pVal =VARIANT_FALSE;

	return S_OK;
}
STDMETHODIMP CotPoint::SetEmpty()
{
    m_x =m_y =m_z =m_m =0.0;	
	return S_OK;
}
STDMETHODIMP CotPoint::Clone( IotGeometry * * geometry)
{
	IotPoint *pPt;
	CoCreateInstance(CLSID_otPoint,NULL,CLSCTX_INPROC_SERVER,__uuidof(IotPoint),(void**)&pPt);

	pPt->put_X(m_x);
	pPt->put_Y(m_y);
	pPt->put_Z(m_z);
	pPt->put_M(m_m);

	pPt->QueryInterface(__uuidof(IotGeometry),(void**)geometry);

	//设置是否包含Z,M
	(*geometry)->put_HasM(m_bm?VARIANT_TRUE:VARIANT_FALSE);
	(*geometry)->put_HasZ(m_bz?VARIANT_TRUE:VARIANT_FALSE);

	pPt->Release();
	

	return S_OK;
}
STDMETHODIMP CotPoint::get_IsValid( VARIANT_BOOL * pVal)
{
	*pVal =VARIANT_TRUE;

	return S_OK;
}
STDMETHODIMP CotPoint::Disjoint( IotGeometry * other,  VARIANT_BOOL * bRet)
{
	otGeometryType type;
	other->get_GeometryType(&type);

	if(type ==OT_GEOM_POINT)
	{
		
        //构造两个点对象
		GEOMETRY::geom::Coordinate coord;
		coord.x =m_x;
		coord.y =m_y;

		GEOMETRY::geom::Point *pt1 =GEOMETRY::geom::GeometryFactory::getDefaultInstance()->createPoint(coord);

		IotPointPtr pPt;
		other->QueryInterface(__uuidof(IotPoint),(void**)&pPt);
		pPt->get_X(&coord.x);
		pPt->get_Y(&coord.y);

		GEOMETRY::geom::Point *pt2 =GEOMETRY::geom::GeometryFactory::getDefaultInstance()->createPoint(coord);

		*bRet =(pt1->disjoint(pt2))?VARIANT_TRUE:VARIANT_FALSE;

        GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(pt1);
		GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(pt2);

	    
		
	}
	else
	{

	}
	return S_OK;
}
STDMETHODIMP CotPoint::Touches( IotGeometry * other,  VARIANT_BOOL * bRet)
{
	otGeometryType type;
	other->get_GeometryType(&type);

	if(type ==OT_GEOM_POINT)
	{

		//构造两个点对象
		GEOMETRY::geom::Coordinate coord;
		coord.x =m_x;
		coord.y =m_y;

		GEOMETRY::geom::Point *pt1 =GEOMETRY::geom::GeometryFactory::getDefaultInstance()->createPoint(coord);

		IotPointPtr pPt;
		other->QueryInterface(__uuidof(IotPoint),(void**)&pPt);
		pPt->get_X(&coord.x);
		pPt->get_Y(&coord.y);

		GEOMETRY::geom::Point *pt2 =GEOMETRY::geom::GeometryFactory::getDefaultInstance()->createPoint(coord);

		*bRet =(pt1->touches(pt2))?VARIANT_TRUE:VARIANT_FALSE;

		GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(pt1);
		GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(pt2);



	}
	else
	{

	}
	return S_OK;
}
STDMETHODIMP CotPoint::Intersects( IotGeometry * other,  VARIANT_BOOL * bRet)
{
	otGeometryType type;
	other->get_GeometryType(&type);

	if(type ==OT_GEOM_POINT)
	{

		//构造两个点对象
		GEOMETRY::geom::Coordinate coord;
		coord.x =m_x;
		coord.y =m_y;

		GEOMETRY::geom::Point *pt1 =GEOMETRY::geom::GeometryFactory::getDefaultInstance()->createPoint(coord);

		IotPointPtr pPt;
		other->QueryInterface(__uuidof(IotPoint),(void**)&pPt);
		pPt->get_X(&coord.x);
		pPt->get_Y(&coord.y);

		GEOMETRY::geom::Point *pt2 =GEOMETRY::geom::GeometryFactory::getDefaultInstance()->createPoint(coord);

		*bRet =(pt1->intersects(pt2))?VARIANT_TRUE:VARIANT_FALSE;

		GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(pt1);
		GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(pt2);



	}
	else
	{

	}
	
	return S_OK;
}
STDMETHODIMP CotPoint::Crosses( IotGeometry * other,  VARIANT_BOOL * bRet)
{
	otGeometryType type;
	other->get_GeometryType(&type);

	if(type ==OT_GEOM_POINT)
	{

		//构造两个点对象
		GEOMETRY::geom::Coordinate coord;
		coord.x =m_x;
		coord.y =m_y;

		GEOMETRY::geom::Point *pt1 =GEOMETRY::geom::GeometryFactory::getDefaultInstance()->createPoint(coord);

		IotPointPtr pPt;
		other->QueryInterface(__uuidof(IotPoint),(void**)&pPt);
		pPt->get_X(&coord.x);
		pPt->get_Y(&coord.y);

		GEOMETRY::geom::Point *pt2 =GEOMETRY::geom::GeometryFactory::getDefaultInstance()->createPoint(coord);

		*bRet =(pt1->crosses(pt2))?VARIANT_TRUE:VARIANT_FALSE;

		GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(pt1);
		GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(pt2);



	}
	else
	{

	}
	return S_OK;
}
STDMETHODIMP CotPoint::Within( IotGeometry * other,  VARIANT_BOOL * bRet)
{
	otGeometryType type;
	other->get_GeometryType(&type);

	if(type ==OT_GEOM_POINT)
	{

		//构造两个点对象
		GEOMETRY::geom::Coordinate coord;
		coord.x =m_x;
		coord.y =m_y;

		GEOMETRY::geom::Point *pt1 =GEOMETRY::geom::GeometryFactory::getDefaultInstance()->createPoint(coord);

		IotPointPtr pPt;
		other->QueryInterface(__uuidof(IotPoint),(void**)&pPt);
		pPt->get_X(&coord.x);
		pPt->get_Y(&coord.y);

		GEOMETRY::geom::Point *pt2 =GEOMETRY::geom::GeometryFactory::getDefaultInstance()->createPoint(coord);

		*bRet =(pt1->within(pt2))?VARIANT_TRUE:VARIANT_FALSE;

		GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(pt1);
		GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(pt2);



	}
	else
	{
		GEOMETRY::geom::Coordinate coord;
		coord.x =m_x;
		coord.y =m_y;

		GEOMETRY::geom::Point *pt1 =GEOMETRY::geom::GeometryFactory::getDefaultInstance()->createPoint(coord);
		GEOMETRY::geom::Geometry *pg =CInterfaceConvert::ConvertIGeo(other);

		if(!pg)
		{
			*bRet =VARIANT_FALSE;

		}
		else
		{
            *bRet =(pt1->within(pg))?VARIANT_TRUE:VARIANT_FALSE;
		}

		GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(pt1);
		
	}
	return S_OK;
}
STDMETHODIMP CotPoint::Overlaps( IotGeometry * other,  VARIANT_BOOL * bRet)
{
	otGeometryType type;
	other->get_GeometryType(&type);

	if(type ==OT_GEOM_POINT)
	{

		//构造两个点对象
		GEOMETRY::geom::Coordinate coord;
		coord.x =m_x;
		coord.y =m_y;

		GEOMETRY::geom::Point *pt1 =GEOMETRY::geom::GeometryFactory::getDefaultInstance()->createPoint(coord);

		IotPointPtr pPt;
		other->QueryInterface(__uuidof(IotPoint),(void**)&pPt);
		pPt->get_X(&coord.x);
		pPt->get_Y(&coord.y);

		GEOMETRY::geom::Point *pt2 =GEOMETRY::geom::GeometryFactory::getDefaultInstance()->createPoint(coord);

		*bRet =(pt1->overlaps(pt2))?VARIANT_TRUE:VARIANT_FALSE;

		GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(pt1);
		GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(pt2);



	}
	else
	{

	}
	return S_OK;
}
STDMETHODIMP CotPoint::Equals( IotGeometry * other,  VARIANT_BOOL * bRet)
{
	otGeometryType type;
	other->get_GeometryType(&type);

	if(type ==OT_GEOM_POINT)
	{

		//构造两个点对象
		GEOMETRY::geom::Coordinate coord;
		coord.x =m_x;
		coord.y =m_y;

		GEOMETRY::geom::Point *pt1 =GEOMETRY::geom::GeometryFactory::getDefaultInstance()->createPoint(coord);

		IotPointPtr pPt;
		other->QueryInterface(__uuidof(IotPoint),(void**)&pPt);
		pPt->get_X(&coord.x);
		pPt->get_Y(&coord.y);

		GEOMETRY::geom::Point *pt2 =GEOMETRY::geom::GeometryFactory::getDefaultInstance()->createPoint(coord);

		*bRet =(pt1->equals(pt2))?VARIANT_TRUE:VARIANT_FALSE;

		GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(pt1);
		GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(pt2);



	}
	else
	{

	}
	return S_OK;
}
STDMETHODIMP CotPoint::Covers( IotGeometry * other,  VARIANT_BOOL * bRet)
{
	otGeometryType type;
	other->get_GeometryType(&type);

	if(type ==OT_GEOM_POINT)
	{

		//构造两个点对象
		GEOMETRY::geom::Coordinate coord;
		coord.x =m_x;
		coord.y =m_y;

		GEOMETRY::geom::Point *pt1 =GEOMETRY::geom::GeometryFactory::getDefaultInstance()->createPoint(coord);

		IotPointPtr pPt;
		other->QueryInterface(__uuidof(IotPoint),(void**)&pPt);
		pPt->get_X(&coord.x);
		pPt->get_Y(&coord.y);

		GEOMETRY::geom::Point *pt2 =GEOMETRY::geom::GeometryFactory::getDefaultInstance()->createPoint(coord);

		*bRet =(pt1->covers(pt2))?VARIANT_TRUE:VARIANT_FALSE;

		GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(pt1);
		GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(pt2);



	}
	else
	{

	}
	return S_OK;
}
STDMETHODIMP CotPoint::ConvexHull( IotGeometry * * retGeometry)
{
	
	return S_OK;
}
STDMETHODIMP CotPoint::Buffer( DOUBLE distance,  IotGeometry * * retGeometry)
{

	GEOMETRY::geom::Coordinate coord;
	coord.x =m_x;
	coord.y =m_y;

	GEOMETRY::geom::Point *pt1 =GEOMETRY::geom::GeometryFactory::getDefaultInstance()->createPoint(coord);
	GEOMETRY::geom::Geometry *pg =pt1->buffer(distance);

	GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(pt1);
	if(!pg)
	{
		*retGeometry =NULL;
		return S_OK;
	}
	CInterfaceConvert::ConvertGeo(pg,retGeometry);
	return S_OK;
}
STDMETHODIMP CotPoint::Intersection( IotGeometry * other,  IotGeometry * * retGeometry)
{
	
	return S_OK;
}
STDMETHODIMP CotPoint::Union( IotGeometry * other,  IotGeometry * * retGeometry)
{
	
	return S_OK;
}
STDMETHODIMP CotPoint::Difference( IotGeometry * other,  IotGeometry * * retGeometry)
{
	
	return S_OK;
}
STDMETHODIMP CotPoint::SymDifference( IotGeometry * other,  IotGeometry * * retGeometry)
{
	
	return S_OK;
}