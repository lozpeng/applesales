#include "StdAfx.h"
#include "InterfaceConvert.h"
#include <geometry/geom/BezierCurve.h>

CInterfaceConvert::CInterfaceConvert(void)
{
}

CInterfaceConvert::~CInterfaceConvert(void)
{
}

GEOMETRY::geom::Geometry* CInterfaceConvert::ConvertIGeo(IotGeometry *pGeometry)
{
	if(!pGeometry)
	{
		return NULL;
	}
	otGeometryType type;
	pGeometry->get_GeometryType(&type);

	GEOMETRY::geom::Geometry *pg =NULL;
	switch(type)
	{
	case OT_GEOM_POINT:
		{
			//点图形则创建一个新的点对象
			GEOMETRY::geom::Coordinate coord;
			IotPoint* pPt;
			pGeometry->QueryInterface(__uuidof(IotPoint),(void**)&pPt);
			pPt->get_X(&coord.x);
			pPt->get_Y(&coord.y);
			pPt->get_Z(&coord.z);
			pPt->get_M(&coord.m);

			pPt->Release();
			GEOMETRY::geom::Point *pt =GEOMETRY::geom::GeometryFactory::getDefaultInstance()->createPoint(coord);
			pg =dynamic_cast<GEOMETRY::geom::Geometry*>(pt);
			break;
		}
	case OT_GEOM_LINESTRING:
		{
           IOriginDataPtr pData;

           pGeometry->QueryInterface(__uuidof(IOriginData),(void**)&pData);

		   long ldata;
		   pData->get_OriginData(&ldata);
		   GEOMETRY::geom::LineString *pLine =(GEOMETRY::geom::LineString*)ldata;
		   
           pg =dynamic_cast<GEOMETRY::geom::Geometry*>(pLine);
		   break;
		}
	case OT_GEOM_LINERING:
		{
			IOriginDataPtr pData;

			pGeometry->QueryInterface(__uuidof(IOriginData),(void**)&pData);

			long ldata;
			pData->get_OriginData(&ldata);
			GEOMETRY::geom::LinearRing *pLine =(GEOMETRY::geom::LinearRing*)ldata;

			pg =dynamic_cast<GEOMETRY::geom::Geometry*>(pLine);
			break;
		}
	case OT_GEOM_MULTIPOINT:
		{
			IOriginDataPtr pData;

			pGeometry->QueryInterface(__uuidof(IOriginData),(void**)&pData);

			long ldata;
			pData->get_OriginData(&ldata);
			GEOMETRY::geom::MultiPoint *pt =(GEOMETRY::geom::MultiPoint*)ldata;

			pg =dynamic_cast<GEOMETRY::geom::Geometry*>(pt);
			break;
		}
	case OT_GEOM_MULTILINESTRING:
		{
			IOriginDataPtr pData;

			pGeometry->QueryInterface(__uuidof(IOriginData),(void**)&pData);

			long ldata;
			pData->get_OriginData(&ldata);
			GEOMETRY::geom::MultiLineString *pt =(GEOMETRY::geom::MultiLineString*)ldata;

			pg =dynamic_cast<GEOMETRY::geom::Geometry*>(pt);
			break;
		}
	case OT_GEOM_POLYGON:
		{
			IOriginDataPtr pData;

			pGeometry->QueryInterface(__uuidof(IOriginData),(void**)&pData);

			long ldata;
			pData->get_OriginData(&ldata);
			GEOMETRY::geom::Polygon *pt =(GEOMETRY::geom::Polygon*)ldata;

			pg =dynamic_cast<GEOMETRY::geom::Geometry*>(pt);
			break;
		}
	case OT_GEOM_MULTIPOLYGON:
		{
			IOriginDataPtr pData;

			pGeometry->QueryInterface(__uuidof(IOriginData),(void**)&pData);

			long ldata;
			pData->get_OriginData(&ldata);
			GEOMETRY::geom::MultiPolygon *pt =(GEOMETRY::geom::MultiPolygon*)ldata;

			pg =dynamic_cast<GEOMETRY::geom::Geometry*>(pt);
			break;
		}
	case OT_GEOM_CIRCLE:
		{

			IOriginDataPtr pData;

			pGeometry->QueryInterface(__uuidof(IOriginData),(void**)&pData);

			long ldata;
			pData->get_OriginData(&ldata);
			GEOMETRY::geom::Circle *pt =(GEOMETRY::geom::Circle*)ldata;

			pg =dynamic_cast<GEOMETRY::geom::Geometry*>(pt);
			break;
		}
	case OT_GEOM_ELLIPSE:
		{

			IOriginDataPtr pData;

			pGeometry->QueryInterface(__uuidof(IOriginData),(void**)&pData);

			long ldata;
			pData->get_OriginData(&ldata);
			GEOMETRY::geom::Ellipse *pt =(GEOMETRY::geom::Ellipse*)ldata;

			pg =dynamic_cast<GEOMETRY::geom::Geometry*>(pt);
			break;
		}
	case OT_GEOM_BEZIERSPLINE:
		{
			IOriginDataPtr pData;

			pGeometry->QueryInterface(__uuidof(IOriginData),(void**)&pData);

			long ldata;
			pData->get_OriginData(&ldata);
			GEOMETRY::geom::BezierSpline *pt =(GEOMETRY::geom::BezierSpline*)ldata;

			pg =dynamic_cast<GEOMETRY::geom::Geometry*>(pt);
			break;
		}
	case OT_GEOM_LINE:
		{
			IOriginDataPtr pData;

			pGeometry->QueryInterface(__uuidof(IOriginData),(void**)&pData);

			long ldata;
			pData->get_OriginData(&ldata);
			GEOMETRY::geom::Line *pt =(GEOMETRY::geom::Line*)ldata;

			pg =dynamic_cast<GEOMETRY::geom::Geometry*>(pt);
			break;
		}
	case OT_GEOM_BEZIERCURVE:
		{
			IOriginDataPtr pData;

			pGeometry->QueryInterface(__uuidof(IOriginData),(void**)&pData);

			long ldata;
			pData->get_OriginData(&ldata);
			GEOMETRY::geom::BezierCurve *pt =(GEOMETRY::geom::BezierCurve*)ldata;

			pg =dynamic_cast<GEOMETRY::geom::Geometry*>(pt);
			break;
		}
	default:
		break;
	}

	return pg;
}

void CInterfaceConvert::ConvertGeo(GEOMETRY::geom::Geometry *pGeometry, IotGeometry **pRet, bool bOwn)
{
	if(!pGeometry)
	{
		*pRet =NULL;
		return;
	}
	GEOMETRY::geom::GeometryTypeId type =pGeometry->getGeometryTypeId();

	switch(type)
	{
	case GEOMETRY::geom::GEOS_POINT:
		{

			GEOMETRY::geom::Coordinate coord =pGeometry->GetPoint(0);

			IotPoint *pPt;

			CoCreateInstance(CLSID_otPoint,NULL,CLSCTX_INPROC_SERVER,__uuidof(IotPoint),(void**)&pPt);

			pPt->put_X(coord.x);
			pPt->put_Y(coord.y);
			pPt->put_Z(coord.z);
			pPt->put_M(coord.m);

			pPt->QueryInterface(__uuidof(IotGeometry),(void**)pRet);

			//设置是否包含Z,M
			(*pRet)->put_HasM(pGeometry->HasM()?VARIANT_TRUE:VARIANT_FALSE);
			(*pRet)->put_HasZ(pGeometry->HasZ()?VARIANT_TRUE:VARIANT_FALSE);	

			pPt->Release();

			if(bOwn)
			{
				//销毁点对象
				delete pGeometry;

			}

			
			break;
		}
	case GEOMETRY::geom::GEOS_LINESTRING:
		{

            IOriginDataPtr pData;
            CoCreateInstance(CLSID_otLineString,NULL,CLSCTX_INPROC_SERVER,__uuidof(IOriginData),(void**)&pData);

			GEOMETRY::geom::LineString *pg =dynamic_cast<GEOMETRY::geom::LineString*>(pGeometry);
			pData->put_OriginData(long(pg));
			pData->put_AutoDestroy(bOwn?TRUE:FALSE);

			pData->QueryInterface(__uuidof(IotGeometry),(void**)pRet);
			break;
		}
	case GEOMETRY::geom::GEOS_LINEARRING:
		{
			IOriginDataPtr pData;
			CoCreateInstance(CLSID_otLineRing,NULL,CLSCTX_INPROC_SERVER,__uuidof(IOriginData),(void**)&pData);

			GEOMETRY::geom::LinearRing *pg =dynamic_cast<GEOMETRY::geom::LinearRing*>(pGeometry);
			pData->put_OriginData(long(pg));
			pData->put_AutoDestroy(bOwn?TRUE:FALSE);

			pData->QueryInterface(__uuidof(IotGeometry),(void**)pRet);
			break;
		}
	case GEOMETRY::geom::GEOS_MULTIPOINT:
		{
			IOriginDataPtr pData;
			CoCreateInstance(CLSID_otMultiPoint,NULL,CLSCTX_INPROC_SERVER,__uuidof(IOriginData),(void**)&pData);

			GEOMETRY::geom::MultiPoint *pg =dynamic_cast<GEOMETRY::geom::MultiPoint*>(pGeometry);
			pData->put_OriginData(long(pg));
			pData->put_AutoDestroy(bOwn?TRUE:FALSE);

			pData->QueryInterface(__uuidof(IotGeometry),(void**)pRet);
			break;
		}
	case GEOMETRY::geom::GEOS_MULTILINESTRING:
		{
			IOriginDataPtr pData;
			CoCreateInstance(CLSID_otMultiLineString,NULL,CLSCTX_INPROC_SERVER,__uuidof(IOriginData),(void**)&pData);

			GEOMETRY::geom::MultiLineString *pg =dynamic_cast<GEOMETRY::geom::MultiLineString*>(pGeometry);
			pData->put_OriginData(long(pg));
			pData->put_AutoDestroy(bOwn?TRUE:FALSE);

			pData->QueryInterface(__uuidof(IotGeometry),(void**)pRet);
			break;
		}
	case GEOMETRY::geom::GEOS_POLYGON:
		{
			IOriginDataPtr pData;
			CoCreateInstance(CLSID_otPolygon,NULL,CLSCTX_INPROC_SERVER,__uuidof(IOriginData),(void**)&pData);

			GEOMETRY::geom::Polygon *pg =dynamic_cast<GEOMETRY::geom::Polygon*>(pGeometry);
			pData->put_OriginData(long(pg));
			pData->put_AutoDestroy(bOwn?TRUE:FALSE);

			pData->QueryInterface(__uuidof(IotGeometry),(void**)pRet);
			break;
		}
	case GEOMETRY::geom::GEOS_MULTIPOLYGON:
		{
			IOriginDataPtr pData;
			CoCreateInstance(CLSID_otMultiPolygon,NULL,CLSCTX_INPROC_SERVER,__uuidof(IOriginData),(void**)&pData);

			GEOMETRY::geom::MultiPolygon *pg =dynamic_cast<GEOMETRY::geom::MultiPolygon*>(pGeometry);
			pData->put_OriginData(long(pg));
			pData->put_AutoDestroy(bOwn?TRUE:FALSE);

			pData->QueryInterface(__uuidof(IotGeometry),(void**)pRet);
			break;
		}
	case GEOMETRY::geom::GEOM_CIRCLE:
		{
			IOriginDataPtr pData;
			CoCreateInstance(CLSID_otCircle,NULL,CLSCTX_INPROC_SERVER,__uuidof(IOriginData),(void**)&pData);

			GEOMETRY::geom::Circle *pg =dynamic_cast<GEOMETRY::geom::Circle*>(pGeometry);
			pData->put_OriginData(long(pg));
			pData->put_AutoDestroy(bOwn?TRUE:FALSE);

			pData->QueryInterface(__uuidof(IotGeometry),(void**)pRet);
			break;
		}
	case GEOMETRY::geom::GEOM_ELLIPSE:
		{
			IOriginDataPtr pData;
			CoCreateInstance(CLSID_otEllipse,NULL,CLSCTX_INPROC_SERVER,__uuidof(IOriginData),(void**)&pData);

			GEOMETRY::geom::Ellipse *pg =dynamic_cast<GEOMETRY::geom::Ellipse*>(pGeometry);
			pData->put_OriginData(long(pg));
			pData->put_AutoDestroy(bOwn?TRUE:FALSE);

			pData->QueryInterface(__uuidof(IotGeometry),(void**)pRet);
			break;
		}
	case GEOMETRY::geom::GEOM_BEZIERSPLINE:
		{
			IOriginDataPtr pData;
			CoCreateInstance(CLSID_otBezierSpline,NULL,CLSCTX_INPROC_SERVER,__uuidof(IOriginData),(void**)&pData);

			GEOMETRY::geom::BezierSpline *pg =dynamic_cast<GEOMETRY::geom::BezierSpline*>(pGeometry);
			pData->put_OriginData(long(pg));
			pData->put_AutoDestroy(bOwn?TRUE:FALSE);

			pData->QueryInterface(__uuidof(IotGeometry),(void**)pRet);
			break;
		}
	case GEOMETRY::geom::GEOM_LINE:
		{
			IOriginDataPtr pData;
			CoCreateInstance(CLSID_otLine,NULL,CLSCTX_INPROC_SERVER,__uuidof(IOriginData),(void**)&pData);

			GEOMETRY::geom::Line *pg =dynamic_cast<GEOMETRY::geom::Line*>(pGeometry);
			pData->put_OriginData(long(pg));
			pData->put_AutoDestroy(bOwn?TRUE:FALSE);

			pData->QueryInterface(__uuidof(IotGeometry),(void**)pRet);
			break;
		}
	case GEOMETRY::geom::GEOM_BEZIERCURVE:
		{
			IOriginDataPtr pData;
			CoCreateInstance(CLSID_otBezierCurve,NULL,CLSCTX_INPROC_SERVER,__uuidof(IOriginData),(void**)&pData);

			GEOMETRY::geom::BezierCurve *pg =dynamic_cast<GEOMETRY::geom::BezierCurve*>(pGeometry);
			pData->put_OriginData(long(pg));
			pData->put_AutoDestroy(bOwn?TRUE:FALSE);

			pData->QueryInterface(__uuidof(IotGeometry),(void**)pRet);
			break;
		}


	default:
		*pRet =NULL;
		break;
	}


}