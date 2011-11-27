#include <owPlugins/ds_feature_ogr/OGRFeature.h>
#include "ogrsf_frmts.h"

using namespace owPlugins;

OGRGSFeature::OGRGSFeature(OGRFeature* ogr_feature)
{
	_ogr_feature = ogr_feature;

	_id = _ogr_feature->GetFID();

	//
	convertFeature();
}

OGRGSFeature::~OGRGSFeature()
{

}

/** 获得矢量记录id号*/
const FeatureOID& OGRGSFeature::getOID() const
{
	return _id;
}

/** 获取矢量图形*/
const GeoShapeList& OGRGSFeature::getShapes() const
{
	return _shapelist;
}

/** 获取矢量图形*/
GeoShapeList& OGRGSFeature::getShapes()
{
	return _shapelist;
}

bool OGRGSFeature::convertFeature()
{
	//
	OGRGeometry* poGeometry = _ogr_feature->GetGeometryRef();

	if(!poGeometry)
		return false;

	//矢量图形转换
	convertShape(poGeometry, _shapelist);

	//属性字段转换
	convertAttribute();

	return true;

}

bool OGRGSFeature::convertAttribute()
{
	//设置属性
	int fieldnum =_ogr_feature->GetFieldCount();

	OGRFieldType type;

	for(int i=0;i<fieldnum;i++)
	{
		type =_ogr_feature->GetFieldDefnRef(i)->GetType();
		switch(type)
		{
		case OFTInteger:
			{
				std::string key =_ogr_feature->GetFieldDefnRef(i)->GetNameRef();
				int val =_ogr_feature->GetFieldAsInteger(i);
				setAttribute(key,val);
				break;
			}
		case OFTReal:
			{
				std::string key =_ogr_feature->GetFieldDefnRef(i)->GetNameRef();
				double val =_ogr_feature->GetFieldAsDouble(i);
				setAttribute(key,val);
				break;
			}

		case OFTString:
			{
				std::string key =_ogr_feature->GetFieldDefnRef(i)->GetNameRef();
				std::string val = _ogr_feature->GetFieldAsString(i);
				setAttribute(key,val);
				break;

			} 
		default:
			{
				std::string key =_ogr_feature->GetFieldDefnRef(i)->GetNameRef();
				std::string val = _ogr_feature->GetFieldAsString(i);
				setAttribute(key,val);
				break;
			}
			break;
		}
	}	

	return true;
}


bool OGRGSFeature::convertShape(OGRGeometry *poGeometry, GeoShapeList& geoshapes)
{

	bool bhasZ =false;
	int i,j;

	//判断图形是否含有Z值
	if(poGeometry->getCoordinateDimension()==3)
	{
		bhasZ =true;
	}

	OGRwkbGeometryType lShapeType =poGeometry->getGeometryType();
	switch(lShapeType)
	{
	case wkbPoint:
	case wkbPoint25D:
		{
			GeoShape geo_shape(GeoShape::TYPE_POINT);
			GeoPointList point_list;
			GeoPoint pt;

			OGRPoint *pPoint =dynamic_cast<OGRPoint*>(poGeometry);
			if(!pPoint)
			{
				return false;
			}
			
			pt._v[0] = pPoint->getX();
			pt._v[1] = pPoint->getY();
			pt._v[2] = pPoint->getZ();

			//
			point_list.push_back(pt);

			//
			geo_shape.addPart(point_list);

			//
			geoshapes.push_back(geo_shape);
		}
		break;
	case wkbLineString:
	case wkbLineString25D:
		{
			GeoShape geo_shape(GeoShape::TYPE_LINE);
			GeoPointList point_list;
			GeoPoint pt;

			OGRLineString *pLine =dynamic_cast<OGRLineString*>(poGeometry);
			if(!pLine)
			{
				return false;
			}

			long lptnum =pLine->getNumPoints();

			for(long i=0;i<lptnum;i++)
			{
				pt._v[0] = pLine->getX(i);
				pt._v[1] = pLine->getY(i);
				pt._v[2] = pLine->getZ(i);

				//
				point_list.push_back(pt);
			}

			//
			geo_shape.addPart(point_list);

			//
			geoshapes.push_back(geo_shape);
		}
		break;
	case wkbMultiPoint:
	case wkbMultiPoint25D:
		{
			GeoShape geo_shape(GeoShape::TYPE_POINT);
			GeoPointList point_list;
			GeoPoint pt;

			OGRMultiPoint *pPoints =dynamic_cast<OGRMultiPoint*>(poGeometry);
			if(!pPoints)
			{
				return false;
			}

			long lptnum =pPoints->getNumGeometries();
			OGRPoint *pPoint =NULL;

			for(long i=0;i<lptnum;i++)
			{
				pPoint =(OGRPoint*)pPoints->getGeometryRef(i);

				pt._v[0] = pPoint->getX();
				pt._v[1] = pPoint->getY();
				pt._v[2] = pPoint->getZ();

				point_list.push_back(pt);
			}

			//
			geo_shape.addPart(point_list);

			//
			geoshapes.push_back(geo_shape);

		}
		break;
	case wkbMultiLineString:
	case wkbMultiLineString25D:
		{
			GeoShape geo_shape(GeoShape::TYPE_LINE);
			GeoPointList point_list;
			GeoPoint pt;

			//
			OGRMultiLineString *pMultiLine =dynamic_cast<OGRMultiLineString*>(poGeometry);
			if(!pMultiLine)
			{
				return false;
			}

			long lptnum,lNumParts;
			OGRLineString* pLine;

			lNumParts =pMultiLine->getNumGeometries();

			for( i=0;i<lNumParts;i++)
			{

				pLine =(OGRLineString*)pMultiLine->getGeometryRef(i);
				lptnum =pLine->getNumPoints();
				point_list.clear();

				for(j=0;j<lptnum;j++)
				{
					pt._v[0] =pLine->getX(j);
					pt._v[1] =pLine->getY(j);
					pt._v[2] =pLine->getZ(j);

					point_list.push_back(pt);
				}

				geo_shape.addPart(point_list);
			}
			geoshapes.push_back(geo_shape);
		}
		break;
	case wkbPolygon:
	case wkbPolygon25D:
		{
			GeoShape geo_shape(GeoShape::TYPE_POLYGON);
			GeoPointList point_list;
			GeoPoint pt;

			OGRPolygon *pPolygon =dynamic_cast<OGRPolygon*>(poGeometry);
			if(!pPolygon)
			{
				return false;
			}

			long i,j;
			long lptnum,lNumParts;
			OGRLinearRing *pLineRing=NULL;

			//外环
			pLineRing =pPolygon->getExteriorRing();
			lptnum =pLineRing->getNumPoints();

			for(j=0;j<lptnum;j++)
			{
				pt._v[0] =pLineRing->getX(j);
				pt._v[1] =pLineRing->getY(j);
				pt._v[2] =pLineRing->getZ(j);

				point_list.push_back(pt);
			}

			geo_shape.addPart(point_list);

			//interior ring
			lNumParts =pPolygon->getNumInteriorRings();

			for( i=0;i<lNumParts;i++)
			{
				pLineRing =pPolygon->getInteriorRing(i);
				lptnum =pLineRing->getNumPoints();
				point_list.clear();


				for(j=0;j<lptnum;j++)
				{
					pt._v[0] =pLineRing->getX(j);
					pt._v[1] =pLineRing->getY(j);
					pt._v[2] =pLineRing->getZ(j);

					point_list.push_back(pt);
				}

				geo_shape.addPart(point_list);

			}  

			geoshapes.push_back(geo_shape);
		}
		break;
	case wkbMultiPolygon:
	case wkbMultiPolygon25D:
		{
			OGRMultiPolygon *pMultiPolygon =dynamic_cast<OGRMultiPolygon*>(poGeometry);
			if(!pMultiPolygon)
			{
				return false;
			}
			long lnum =pMultiPolygon->getNumGeometries();
			OGRGeometry *pg =NULL;
	
			for(long i=0;i<lnum;i++)
			{
				pg =pMultiPolygon->getGeometryRef(i);
				if(!convertShape(pg,geoshapes))
				{
					return false;
				}
			}
		}
		break;
	case wkbGeometryCollection:
	case wkbGeometryCollection25D:
		{
			OGRGeometryCollection *pCollection =dynamic_cast<OGRGeometryCollection*>(poGeometry);
			if(!pCollection)
			{
				return false;
			}

			long lnum =pCollection->getNumGeometries();
			OGRGeometry *pg =NULL;

			for(long i=0;i<lnum;i++)
			{
				pg =pCollection->getGeometryRef(i);
				if(!convertShape(pg,geoshapes))
				{
					return false;
				}
			}
		}
		break;
	default:
		break;

	}

	return true;
}
