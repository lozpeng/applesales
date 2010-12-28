//////////////////////////////////////////////////////////////////////
// 版权(c) 2008-2020, 天地智绘
// 作者：  champion
// 时间：  2008.6
// 描述：  定义了空间查询的条件
//////////////////////////////////////////////////////////////////////

#ifndef  _GEODATABASE_SPATIALQUERY_H_
#define  _GEODATABASE_SPATIALQUERY_H_

#include "SimpleQuery.h"
#include <Geometry/geom/Geometry.h>
#include <Geometry/geom/GeometryFactory.h>

namespace Geodatabase
{

class  CSpatialQuery: public Geodatabase::CSimpleQuery
{
public:
	CSpatialQuery( ) 
	{ 
		m_pQueryGeometry =NULL;
		m_spatialRel =SpatialRelEnvelopeIntersects;
	}
	virtual ~CSpatialQuery()
	{
		if(m_pQueryGeometry)
		{
			delete m_pQueryGeometry;
			m_pQueryGeometry =NULL;
		}
	}

public:
	//得到查询用的几何图形
	GEOMETRY::geom::Geometry *GetGeometry() const{return m_pQueryGeometry;}

	//设置查询用的几何图形
	void SetGeometry(GEOMETRY::geom::Geometry* pGeometry) {m_pQueryGeometry =pGeometry;}

	//设置查询用的Rect
	void SetGeometry(GEOMETRY::geom::Envelope* pEnvelope) {m_pQueryGeometry =GEOMETRY::geom::GeometryFactory::getDefaultInstance()->toGeometry(pEnvelope);}

	//得到查询的空间关系
	long GetSpatialRel() const{return m_spatialRel;}

	//设置查询的空间关系
	void SetSpatialRel(long spatialrel) {m_spatialRel =(EnumSpatialRel)spatialrel;}


protected:
	GEOMETRY::geom::Geometry *m_pQueryGeometry;

	EnumSpatialRel m_spatialRel;



};






}




#endif