#include "stdafx.h"
#include "OGRFeatureClass.h"
#include "OGRWorkspace.h"
#include "OGRWorkspaceFactory.h"
#include "OGRFeatureCursor.h"
#include "Feature.h"
#include "SelectionSet.h"
#include "SpatialQuery.h"
#include  <Geometry/geom/Geometry.h>
#include <Geometry/geom/GeometryFactory.h>
#include <Geometry/geom/Coordinate.h>
#include <Geometry/geom/CoordinateArraySequenceFactory.h>
#include <Geometry/geom/CoordinateSequence.h>
#include <Geometry/geom/MultiLineString.h>
#include <Geometry/geom/Polygon.h>
#include <Geometry/geom/LinearRing.h>
#include <Geometry/geom/MultiPolygon.h>

using namespace Geodatabase;
using namespace std;
using namespace GEOMETRY::geom;

COGRFeatureClass::COGRFeatureClass(COGRWorkspace *pWorkspace,OGRLayer *pOGRLayer)
:IFeatureClass(pWorkspace,NULL)
{
	m_pOGRLayer =pOGRLayer;
	m_lshptype =-1;

	Init();

}

COGRFeatureClass::~COGRFeatureClass()
{



}

void COGRFeatureClass::Init()
{
	if(!m_pOGRLayer)
	{
		return;
	}

	//获得数据的地理范围
	OGREnvelope  extent;
	m_pOGRLayer->GetExtent(&extent);
	m_envelop.init(extent.MinX,extent.MaxX,extent.MinY,extent.MaxY);

}

//要素的数目
long COGRFeatureClass::RowCount() const
{
	return FeatureCount();
}

long COGRFeatureClass::FeatureCount() const
{
	m_pOGRLayer->SetSpatialFilter(NULL);
	m_pOGRLayer->SetAttributeFilter(NULL);
	return m_pOGRLayer->GetFeatureCount();
}



/************************************************************************************************
* 以下为要素的操作方法
*
*************************************************************************************************/


//获得图形的类型
long COGRFeatureClass::ShapeType() 
{
	if(m_lshptype!=-1)
	{
		return m_lshptype;
	}

	OGRwkbGeometryType type =m_pOGRLayer->GetLayerDefn()->GetGeomType();

	switch(type)
	{
	case wkbPoint:
	case wkbPoint25D:
		m_lshptype =(long)GEOS_POINT; 
		break;

	case wkbLineString:
	case wkbLineString25D:
		m_lshptype = (long)GEOS_LINESTRING; 
		break;

	case wkbMultiPoint:
	case wkbMultiPoint25D:
		m_lshptype = (long)GEOS_MULTIPOINT; 
		break;

	case wkbMultiLineString:
	case wkbMultiLineString25D:
		m_lshptype = (long)GEOS_MULTILINESTRING; 
		break;

	case wkbPolygon:
	case wkbMultiPolygon:
	case wkbPolygon25D:
	case wkbMultiPolygon25D:
		m_lshptype = (long)GEOS_POLYGON; 
		break;
	case wkbGeometryCollection:
	case wkbGeometryCollection25D:
		m_lshptype =(long)GEOS_GEOMETRYCOLLECTION;
		break;


	default:
		m_lshptype =GEOM_NULL;
		break;
	}

	return m_lshptype;
}

//产生一个空的要素,并将要素加入到数据集中
CFeaturePtr COGRFeatureClass::CreateFeature()
{


	return CFeaturePtr();



}

CFeaturePtr COGRFeatureClass::GetFeature(long index)
{
	long ltotal =FeatureCount();

	//id是否有效
	if(index<1 || index>ltotal)
	{
		return CFeaturePtr();
	}


	OGRFeature *poFeature =m_pOGRLayer->GetFeature(index);
	if(!poFeature)
	{
		return CFeaturePtr();
	}
	CFeature *pFeature =NULL;
	if(!ConvertFeature(poFeature,&pFeature))
	{
		OGRFeature::DestroyFeature(poFeature);
		return CFeaturePtr();
	}

	OGRFeature::DestroyFeature(poFeature);
	return CFeaturePtr(pFeature);

}
#include <iostream>
using namespace std;

void COGRFeatureClass::Print()
{
	FILE * fp = NULL; 
	char  *p ="C:\\temp.txt" ; 
	fp = fopen( p, "a+" ); 
	//fprintf( fp, "d" ); 
	fprintf( fp, "\n" ); 

	OGRFeature *poFeature =NULL;
	while(true)
	{
		poFeature =m_pOGRLayer->GetNextFeature();

		if(!poFeature)
		{
			break;
		}

		char buf[100]; 

		fprintf( fp, "\n"); 
		sprintf(buf,"%d,",poFeature->GetFID());
		fprintf( fp, buf); 
		fprintf( fp, ","); 
		//printf("\n");

		//设置属性
		int fieldnum =poFeature->GetFieldCount();
		OGRFieldType type;
		for(int i=0;i<fieldnum;i++)
		{
			const char *fieldName = poFeature->GetFieldDefnRef(i)->GetNameRef();
			
			fprintf( fp, fieldName); 
			fprintf( fp, "=");
			type =poFeature->GetFieldDefnRef(i)->GetType();

			const char* szVal = poFeature->GetFieldAsString(i);
			fprintf( fp, szVal); 
			fprintf( fp, ","); 
		}
	}
	fclose(fp); 

}
bool COGRFeatureClass::ConvertFeature(OGRFeature *poFeature,Geodatabase::CFeature **ppFeature)
{
	CFeature *pFeature =new CFeature(this,poFeature->GetFID());
	Geometry *pGeometry =NULL;
	//设置图形
	if(!OGRGeometry2Geometry(poFeature->GetGeometryRef(),&pGeometry))
	{
		delete pFeature;
		return false;
	}
	pFeature->SetShape(pGeometry);


	//设置属性
	int fieldnum =poFeature->GetFieldCount();
	OGRFieldType type;
	for(int i=0;i<fieldnum;i++)
	{
		type =poFeature->GetFieldDefnRef(i)->GetType();
		switch(type)
		{
		case OFTInteger:
			{
				pFeature->m_values[i].vtype =FieldValue::VT_INT;
				pFeature->m_values[i].m_Var.iVal =poFeature->GetFieldAsInteger(i);
				printf("%d,",poFeature->GetFieldAsInteger(i));
				break;
			}
		case OFTReal:
			{
				pFeature->m_values[i].vtype =FieldValue::VT_DOUBLE;
				pFeature->m_values[i].m_Var.dVal =poFeature->GetFieldAsDouble(i);
				printf("%f,",poFeature->GetFieldAsDouble(i));

				break;
			}

		case OFTString:
			{
				pFeature->m_values[i].SetString(poFeature->GetFieldAsString(i));
				const char* szVal = poFeature->GetFieldAsString(i);
				printf(szVal);
				printf(",");
				break;
			} 
		case OFTStringList:
			{
				char **stringList = poFeature->GetFieldAsStringList(i);
				const char* szVal = poFeature->GetFieldAsString(i);
				printf(szVal);
				printf(",");
				break;
			}
		case OFTIntegerList:
			{
				int nList = 0;
				const int *pList = poFeature->GetFieldAsIntegerList(i,&nList);
				for(int i = 0;i< nList ;i++)
				{
					printf("%d,",pList[i]);
				}
				const char* szVal = poFeature->GetFieldAsString(i);
				printf(szVal);
				printf(",");
				break;
			}
		default:
			break;
		}
	}


	*ppFeature =pFeature;
	return true;


}

bool COGRFeatureClass::OGRGeometry2Geometry(OGRGeometry *poGeometry,GEOMETRY::geom::Geometry **ppGeometry)
{

	typedef vector<GEOMETRY::geom::Coordinate> CoordVect;

	if(!poGeometry || !ppGeometry)
	{
		return false;
	}
	Geometry *pGeometry =NULL;

	bool bhasZ =false;

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
			OGRPoint *pPoint =dynamic_cast<OGRPoint*>(poGeometry);
			if(!pPoint)
			{
				return false;
			}

			Coordinate coord(pPoint->getX(),pPoint->getY(),pPoint->getZ());


			pGeometry =(Geometry*)GeometryFactory::getDefaultInstance()->createPoint(coord);
			break;
		}
	case wkbLineString:
	case wkbLineString25D:
		{

			OGRLineString *pLine =dynamic_cast<OGRLineString*>(poGeometry);
			if(!pLine)
			{
				return false;
			}

			long lptnum =pLine->getNumPoints();
			Coordinate coord;

			CoordVect *pcoords =new CoordVect(lptnum);


			for(long i=0;i<lptnum;i++)
			{

				coord.x =pLine->getX(i);
				coord.y =pLine->getY(i);
				coord.z =pLine->getZ(i);


				(*pcoords)[i] =coord;
			}

			CoordinateSequence *coords = GeometryFactory::getDefaultInstance()->getCoordinateSequenceFactory()->create(pcoords);
			pGeometry =(Geometry*)GeometryFactory::getDefaultInstance()->createLineString(coords);
			break;
		}
	case wkbMultiPoint:
	case wkbMultiPoint25D:
		{

			Coordinate coord;
			OGRMultiPoint *pPoints =dynamic_cast<OGRMultiPoint*>(poGeometry);
			if(!pPoints)
			{
				return false;
			}
			long lptnum =pPoints->getNumGeometries();
			CoordVect *pcoords =new CoordVect(lptnum);

			OGRPoint *pPoint =NULL;
			for(long i=0;i<lptnum;i++)
			{
				pPoint =(OGRPoint*)pPoints->getGeometryRef(i);
				coord.x =pPoint->getX();
				coord.y =pPoint->getY();
				coord.z =pPoint->getZ();

				(*pcoords)[i] =coord;
			}
			CoordinateSequence *coords = GeometryFactory::getDefaultInstance()->getCoordinateSequenceFactory()->create(pcoords);

			pGeometry =(Geometry*)GeometryFactory::getDefaultInstance()->createMultiPoint(*coords);

			delete coords;
			break;
		}

	case wkbMultiLineString:
	case wkbMultiLineString25D:
		{

			OGRMultiLineString *pMultiLine =dynamic_cast<OGRMultiLineString*>(poGeometry);
			if(!pMultiLine)
			{
				return false;
			}

			long lptnum,lNumParts;
			lNumParts =pMultiLine->getNumGeometries();


			//建立一个空的多线要素
			pGeometry =(Geometry*)GeometryFactory::getDefaultInstance()->createMultiLineString();

			Coordinate coord;
			CoordVect *pcoords =NULL;
			OGRLineString *pLine =NULL;
			OGRPoint *pPoint =NULL;
			long i,j;
			for( i=0;i<lNumParts;i++)
			{

				pLine =(OGRLineString*)pMultiLine->getGeometryRef(i);
				lptnum =pLine->getNumPoints();
				pcoords =new CoordVect(lptnum);

				for(j=0;j<lptnum;j++)
				{
					coord.x =pLine->getX(j);
					coord.y =pLine->getY(j);
					coord.z =pLine->getZ(j);

					(*pcoords)[j] =coord;
				}

				CoordinateSequence *coords = GeometryFactory::getDefaultInstance()->getCoordinateSequenceFactory()->create(pcoords);
				LineString *pline = GeometryFactory::getDefaultInstance()->createLineString(coords);

				((MultiLineString*)pGeometry)->AddGeometry((Geometry*)pline);

			}
			break;
		}

	case wkbPolygon:
	case wkbPolygon25D:
		{
			OGRPolygon *pPolygon =dynamic_cast<OGRPolygon*>(poGeometry);
			if(!pPolygon)
			{
				return false;
			}
			long lptnum,lNumParts;

			OGRLinearRing *pLineRing=NULL;

			//建立一个空的多边形要素
			pGeometry =(Geometry*)GeometryFactory::getDefaultInstance()->createPolygon();

			Coordinate coord;
			CoordVect *pcoords =NULL;

			//首先获得外环
			pLineRing =pPolygon->getExteriorRing();

			lptnum =pLineRing->getNumPoints();
			pcoords =new CoordVect(lptnum);
			long i,j;

			for(j=0;j<lptnum;j++)
			{
				coord.x =pLineRing->getX(j);
				coord.y =pLineRing->getY(j);
				coord.z =pLineRing->getZ(j);

				(*pcoords)[j] =coord;
			}
			CoordinateSequence *coords = GeometryFactory::getDefaultInstance()->getCoordinateSequenceFactory()->create(pcoords);
			LinearRing *pring = GeometryFactory::getDefaultInstance()->createLinearRing(coords);

			((GEOMETRY::geom::Polygon*)pGeometry)->AddGeometry((Geometry*)pring);

			//获得内环的数目
			lNumParts =pPolygon->getNumInteriorRings();


			for( i=0;i<lNumParts;i++)
			{
				pLineRing =pPolygon->getInteriorRing(i);

				lptnum =pLineRing->getNumPoints();
				pcoords =new CoordVect(lptnum);

				for(j=0;j<lptnum;j++)
				{
					coord.x =pLineRing->getX(j);
					coord.y =pLineRing->getY(j);
					coord.z =pLineRing->getZ(j);

					(*pcoords)[j] =coord;
				}
				coords = GeometryFactory::getDefaultInstance()->getCoordinateSequenceFactory()->create(pcoords);
				pring = GeometryFactory::getDefaultInstance()->createLinearRing(coords);

				((GEOMETRY::geom::Polygon*)pGeometry)->AddGeometry((Geometry*)pring);

			}  
			break;
		}
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
			pGeometry =(Geometry*)GeometryFactory::getDefaultInstance()->createMultiPolygon();
			Geometry *pGeo =NULL;
			for(long i=0;i<lnum;i++)
			{
				pg =pMultiPolygon->getGeometryRef(i);
				if(!OGRGeometry2Geometry(pg,&pGeo))
				{
					return false;
				}
				((GEOMETRY::geom::MultiPolygon*)pGeometry)->AddGeometry(pGeo);

			}


			break;
		}
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
			pGeometry =(Geometry*)GeometryFactory::getDefaultInstance()->createGeometryCollection();
			Geometry *pGeo =NULL;
			for(long i=0;i<lnum;i++)
			{
				pg =pCollection->getGeometryRef(i);
				if(!OGRGeometry2Geometry(pg,&pGeo))
				{
					return false;
				}
				((GEOMETRY::geom::GeometryCollection*)pGeometry)->AddGeometry(pGeo);

			}
			break;
		}
	default:
		break;

	}



	if(pGeometry==NULL)
	{
		return false;
	}

	pGeometry->SetbZ(bhasZ);
	pGeometry->SetbM(false);
	*ppGeometry =pGeometry;
	return true;
}

Geometry* COGRFeatureClass::GetFeatureShape(long index)
{

	long ltotal =FeatureCount();

	//id是否有效
	if(index<1 || index>ltotal)
	{
		return NULL;
	}


	OGRFeature *poFeature =m_pOGRLayer->GetFeature(index);
	if(!poFeature)
	{
		return NULL;
	}
	Geometry *pGeometry =NULL;
	OGRGeometry2Geometry(poFeature->GetGeometryRef(),&pGeometry);

	OGRFeature::DestroyFeature(poFeature);

	return pGeometry;
}

//添加一个新的要素
void COGRFeatureClass::AddFeature(Geodatabase::CFeature *pFeature)
{

}
//更新一个要素
void COGRFeatureClass::UpdateFeature(Geodatabase::CFeature *pFeature)
{
	//test s57


	//COGRWorkspace *pWorkspace =dynamic_cast<COGRWorkspace*>(m_pWorkspace);
	//是否在进行编辑
	//if(pWorkspace->IsEditing())
	//{ 
	//	if(!pWorkspace->ExistEditCache(m_name))
	//	{
	//		pWorkspace->BuildEditCache(this);
	//	}

	//	CFeatureEditCache *pCache =pWorkspace->FindEditCache(m_name);


	//产生一个要素的拷贝
	//CFeature *pcopyFeature =new CFeature(*pFeature);
	//pcopyFeature->SetShape(pFeature->GetShapeClone());

	//pWorkspace->UpdateFeature(this,CFeaturePtr(pcopyFeature));
	//}

}
//删除要素
void COGRFeatureClass::DeleteFeature(long index)
{

}

/************************************************************************************************
* 以下为字段的操作方法
*************************************************************************************************/

//增加一个字段
void COGRFeatureClass::AddField(Geodatabase::CField *pField)
{

}

//删除一个字段
void COGRFeatureClass::DeleteField(long index)
{

}

long COGRFeatureClass::FieldCount() const
{

	return m_pOGRLayer->GetLayerDefn()->GetFieldCount();
}
//通过字段名查找字段的序号
long COGRFeatureClass::FindField(const char *name)
{
	return (m_pOGRLayer->GetLayerDefn()->GetFieldIndex(name)+1);
}

CFieldPtr COGRFeatureClass::GetField(long index)
{
	long lcount =FieldCount();

	if(index<=0 || index>lcount)
	{
		return CFieldPtr();
	}
	OGRFieldDefn *pFieldDef =m_pOGRLayer->GetLayerDefn()->GetFieldDefn(index-1);
	if(!pFieldDef)
	{
		return CFieldPtr();
	}

	CField *pField =new CField();

	//获得字段名称
	pField->SetName(pFieldDef->GetNameRef());

	//获得字段类型
	OGRFieldType ftype =pFieldDef->GetType();
	switch(ftype)
	{


	case OFTInteger:
		{
			pField->SetType(FTYPE_LONG);
			break;
		}
	case OFTReal:
		{
			pField->SetType(FTYPE_DOUBLE);
			break;
		}

	case OFTString:
		{
			pField->SetType(FTYPE_STRING);
			break;

		}
	case OFTDate :
		{
			pField->SetType(FTYPE_DATE);
			break;
		}
	case OFTTime:
	case OFTDateTime:
		{
			pField->SetType(FTYPE_TIME);
			break;
		}
	case OFTBinary:
		{
			pField->SetType(FTYPE_BLOB);
			break;
		}
	default:
		pField->SetType(FTYPE_UNKNOWN);
		break;
	}
	//获得字段长度
	pField->SetLength(pFieldDef->GetWidth());

	//获得小数位数
	pField->SetPrecision(pFieldDef->GetPrecision());

	return CFieldPtr(pField);
}

string COGRFeatureClass::ShapeFieldName()
{
	//该几何字段是一个虚拟字段，并没有存在于数据表中
	return "OGR_GEOM";
}


/************************************************************************************************
* 以下为查询选择操作方法
*************************************************************************************************/

ISelctionSetPtr COGRFeatureClass::Select(Geodatabase::CSimpleQuery *query)
{

	CSpatialQuery *pspatialQuery =dynamic_cast<CSpatialQuery*>(query);
	if(pspatialQuery)
	{
		return SpatialSelect(pspatialQuery);
	}
	else
	{
		return SimpleSelect(query);
	}
}

ISelctionSetPtr COGRFeatureClass::SelectByRect(const double &xmin,const double &ymin, const double &xmax,const double &ymax)
{


	return ISelctionSetPtr();
}

ICursorPtr COGRFeatureClass::Query(CSimpleQuery *query, bool bReadOnly)
{
	CSpatialQuery *pspatialQuery =dynamic_cast<CSpatialQuery*>(query);
	if(pspatialQuery)
	{
		return SpatialQuery(pspatialQuery,bReadOnly);
	}
	else
	{
		return SimpleQuery(query,bReadOnly);
	}

}

//简单的条件查询
ICursorPtr COGRFeatureClass::SimpleQuery(Geodatabase::CSimpleQuery* query,bool bReadOnly)
{

	m_pOGRLayer->SetSpatialFilter(NULL);
	if(query->GetWhereString().empty())
	{
		m_pOGRLayer->SetAttributeFilter(NULL);
	} 
	else
	{
		m_pOGRLayer->SetAttributeFilter(query->GetWhereString().c_str());
	}

	m_pOGRLayer->ResetReading();
	COGRFeatureCursor *pCursor =new COGRFeatureCursor(this,query->GetFields().c_str());


	OGRFeature *pFeature =NULL;
	while(true)
	{
		pFeature =m_pOGRLayer->GetNextFeature();
		if(!pFeature)
		{
			break;
		}
		pCursor->m_Features.push_back(pFeature);
	}


	return ICursorPtr(pCursor);

}



ICursorPtr COGRFeatureClass::SpatialQuery(Geodatabase::CSpatialQuery* query,bool bReadOnly)
{
	return ICursorPtr();
}
ICursorPtr COGRFeatureClass::QueryByExtent(GEOMETRY::geom::Envelope *pEnvelop,CSimpleQuery *pQuery, bool bReadOnly)
{

	COGRFeatureCursor *pCursor =new COGRFeatureCursor(this,pQuery->GetFields().c_str());

	m_pOGRLayer->SetAttributeFilter(NULL);
	m_pOGRLayer->SetSpatialFilterRect(pEnvelop->getMinX(),pEnvelop->getMinY(),pEnvelop->getMaxX(),pEnvelop->getMaxY());

	m_pOGRLayer->ResetReading();
	OGRFeature *pFeature =NULL;
	while(true)
	{
		pFeature =m_pOGRLayer->GetNextFeature();
		if(!pFeature)
		{
			break;
		}
		pCursor->m_Features.push_back(pFeature);
	}


	return ICursorPtr(pCursor);

}

//简单的条件选择
ISelctionSetPtr COGRFeatureClass::SimpleSelect(Geodatabase::CSimpleQuery* query)
{


	return ISelctionSetPtr();
}

//空间查询选择
ISelctionSetPtr COGRFeatureClass::SpatialSelect(Geodatabase::CSpatialQuery *query)
{


	return ISelctionSetPtr();
}



/************************************************************************************************
* 以下为投影和M,Z值操作方法
*************************************************************************************************/

//获得投影字符串
std::string COGRFeatureClass::GetWkt() const
{
	OGRSpatialReference *pSf = m_pOGRLayer->GetSpatialRef();
	if(!pSf)
	{
		return std::string();
	}

	char *cwkt =NULL;
	string wkt;
	if(pSf->exportToWkt(&cwkt)==OGRERR_NONE)
	{
		wkt =cwkt;
		OGRFree(cwkt);
	}
	return wkt;

}

//设置投影字符串
void COGRFeatureClass::SetWkt(const char *strwkt)
{
	//m_pOGRLayer->GetSpatialRef()->SetProjection();
}

bool COGRFeatureClass::HasZ() const
{

	OGRwkbGeometryType type =m_pOGRLayer->GetLayerDefn()->GetGeomType();

	//通过图形的类型判断是否有Z值
	switch(type)
	{
	case wkbPoint25D:
	case wkbLineString25D:
	case wkbMultiPoint25D:
	case wkbMultiLineString25D:
	case wkbPolygon25D:
	case wkbMultiPolygon25D:
	case wkbGeometryCollection25D:
		return true;
		break;

	default:
		return false;
		break;
	}
	return false;
}

bool COGRFeatureClass::HasM() const
{

	return false;
}

bool COGRFeatureClass::GetExtent(GEOMETRY::geom::Envelope *pEnvelop) const
{

	if(!pEnvelop)
	{
		return false;
	}


	*pEnvelop =m_envelop;

	return true;
}








