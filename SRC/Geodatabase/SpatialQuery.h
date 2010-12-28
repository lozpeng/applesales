//////////////////////////////////////////////////////////////////////
// ��Ȩ(c) 2008-2020, ����ǻ�
// ���ߣ�  champion
// ʱ�䣺  2008.6
// ������  �����˿ռ��ѯ������
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
	//�õ���ѯ�õļ���ͼ��
	GEOMETRY::geom::Geometry *GetGeometry() const{return m_pQueryGeometry;}

	//���ò�ѯ�õļ���ͼ��
	void SetGeometry(GEOMETRY::geom::Geometry* pGeometry) {m_pQueryGeometry =pGeometry;}

	//���ò�ѯ�õ�Rect
	void SetGeometry(GEOMETRY::geom::Envelope* pEnvelope) {m_pQueryGeometry =GEOMETRY::geom::GeometryFactory::getDefaultInstance()->toGeometry(pEnvelope);}

	//�õ���ѯ�Ŀռ��ϵ
	long GetSpatialRel() const{return m_spatialRel;}

	//���ò�ѯ�Ŀռ��ϵ
	void SetSpatialRel(long spatialrel) {m_spatialRel =(EnumSpatialRel)spatialrel;}


protected:
	GEOMETRY::geom::Geometry *m_pQueryGeometry;

	EnumSpatialRel m_spatialRel;



};






}




#endif