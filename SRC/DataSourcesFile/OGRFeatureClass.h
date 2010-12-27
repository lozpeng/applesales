#ifndef _OGR_FEATURECLASS_H_
#define _OGR_FEATURECLASS_H_

#include "IFeatureClass.h"
#include "OGRWorkspace.h"
#include "SpatialQuery.h"
#include <Geometry/geom/Envelope.h>

namespace GEOMETRY
{
	namespace geom
	{
		class Geometry;
	}
}
class  COGRFeatureClass: public Geodatabase::IFeatureClass
{
	friend class COGRWorkspace;
protected:
	COGRFeatureClass(COGRWorkspace *pWorkspace,OGRLayer *pOGRLayer);
public:
	virtual ~COGRFeatureClass();

public:

	//������¼����Ŀ
	virtual long RowCount() const;

	///////����Ϊ�ֶεĲ�������///////////////////////////////////////////////////
	//���һ���µ��ֶ�
	virtual void AddField(Geodatabase::CField *pField) ;

	//ɾ��һ���ֶ�
	virtual void DeleteField(long index) ;

	//ͨ���ֶ��������ֶε����
	virtual long FindField(const char* name);

	//ͨ����ŵõ�һ���ֶε�����
	virtual Geodatabase::CFieldPtr GetField(long index);

	virtual long FieldCount() const;

	virtual std::string  ShapeFieldName();

	///////����Ϊ��ѯ�Ĳ�������///////////////////////////////////////////////////

	//ͨ����ѯ�������в�ѯ������һ��ѡ��
	virtual Geodatabase::ISelctionSetPtr Select(Geodatabase::CSimpleQuery* query);

	//���β�ѯ
	virtual Geodatabase::ISelctionSetPtr SelectByRect(const double &xmin,const double &ymin,const double &xmax,const double &ymax);

	//ͨ����ѯ������ѯ������һ��ָ��
	virtual Geodatabase::ICursorPtr Query(Geodatabase::CSimpleQuery* query,bool bReadOnly =true);

	virtual Geodatabase::ICursorPtr QueryByExtent(GEOMETRY::geom::Envelope *pEnvelop,Geodatabase::CSimpleQuery *pQuery,bool bReadOnly =true);

	//����Ҫ�ص���Ŀ
	virtual long FeatureCount() const ;

	//Ҫ�ص�ͼ������,ΪGEOMETRY::geom::GeometryTypeId����
	virtual long ShapeType() ;

	///////����ΪҪ�صĲ�������///////////////////////////////////////////////////
	//���������д���һ���յ�Ҫ�أ�����Ϊ��
	virtual Geodatabase::CFeaturePtr CreateFeature() ;

	//����Ҫ��ID�Ļ�ȡҪ��
	virtual Geodatabase::CFeaturePtr GetFeature(long index);

	//����Ҫ��ID��ȡҪ�ص�ͼ��
	virtual GEOMETRY::geom::Geometry* GetFeatureShape(long index);

	//���һ����Ҫ��
	virtual void AddFeature(Geodatabase::CFeature *pFeature);

	//����һ��Ҫ��
	virtual void UpdateFeature(Geodatabase::CFeature *pFeature);

	//ɾ��һ��Ҫ��
	virtual void DeleteFeature(long index) ; 

	///////////ͶӰ���///////////////////////////////////////////////////////////
	virtual std::string GetWkt() const ;

	virtual void SetWkt(const char* strwkt);

	//�õ����ݼ��ķ�Χ��pEnvelop�Ƿ��صķ�Χ
	virtual bool GetExtent(GEOMETRY::geom::Envelope *pEnvelop) const ;

	//�Ƿ����Mֵ��Zֵ
	virtual bool HasM() const ;

	virtual bool HasZ() const ;

public:
	//��OGRFeatureת��ΪCFeature
	bool ConvertFeature(OGRFeature *poFeature,Geodatabase::CFeature **ppFeature);

	//��OGRGeometryת����Geometry
	static bool OGRGeometry2Geometry(OGRGeometry *poGeometry,GEOMETRY::geom::Geometry **ppGeometry);

	Geodatabase::ICursorPtr SimpleQuery(Geodatabase::CSimpleQuery* query,bool bReadOnly);

	Geodatabase::ICursorPtr SpatialQuery(Geodatabase::CSpatialQuery* query,bool bReadOnly);

	//�򵥵�����ѡ��
	Geodatabase::ISelctionSetPtr SimpleSelect(Geodatabase::CSimpleQuery* query);

	//�ռ��ѯѡ��
	Geodatabase::ISelctionSetPtr SpatialSelect(Geodatabase::CSpatialQuery* query);

private:
	void Init();
private:

	//����Դ
    OGRLayer *m_pOGRLayer;
	//Ҫ��ͼ�ε�����
	long                m_lshptype;

	//���ݵĵ���Χ
	GEOMETRY::geom::Envelope m_envelop;

public:
	virtual void Print();
};


#endif