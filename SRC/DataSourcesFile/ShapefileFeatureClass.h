//////////////////////////////////////////////////////////////////////
  // ��Ȩ(c) 2010-2020, ����ǻ�
  // ���ߣ�  hhzhao
  // ʱ�䣺  2009/11/23
  // ������  shapefileFeatureclass  shapefileҪ�ؼ���
//////////////////////////////////////////////////////////////////////

#ifndef _SHP_FEATURECLASS_H_
#define _SHP_FEATURECLASS_H_

#include "DSFileDefine.h"
#include "ShapefileWorkspace.h"
#include "IFeatureClass.h"
#include "SpatialQuery.h"
#include "shapefil.h"

namespace GEOMETRY
{
	namespace geom
	{
		class Geometry;
	}
}
class  CShapefileFeatureClass: public Geodatabase::IFeatureClass
{
	friend class CShapefileWorkspace;
protected:
	CShapefileFeatureClass(CShapefileWorkspace *pWorkspace,SHPHandle hShp,DBFHandle hDbf,const char *name,bool ReadOnly);
public:
	virtual ~CShapefileFeatureClass();

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

	virtual void serialization(SYSTEM::IArchive &ar);
public:
	
    long GetTotalNum();

	//��ʼ������ȡһЩ������Ϣ
	void Init();

	//��ȡͶӰ��Ϣ
	bool ReadPrj();

	void GetFeatureValue(long &index,Geodatabase::CFeaturePtr &pFeature,bool &bhasShape,std::vector<long> &fieldsIndex);

	Geodatabase::ICursorPtr SimpleQuery(Geodatabase::CSimpleQuery* query,bool bReadOnly);

	Geodatabase::ICursorPtr SpatialQuery(Geodatabase::CSpatialQuery* query,bool bReadOnly);

	//�򵥵�����ѡ��
	Geodatabase::ISelctionSetPtr SimpleSelect(Geodatabase::CSimpleQuery* query);

	//�ռ��ѯѡ��
	Geodatabase::ISelctionSetPtr SpatialSelect(Geodatabase::CSpatialQuery* query);
private:
	Geodatabase::CFeature *ShpReadFeature(long index);

	GEOMETRY::geom::Geometry* ReadShape(long index);

	//�����ռ�����
	void BuildSpatialIndex();

private:
    SHPHandle m_shpHandle;
	DBFHandle m_dbfHandle;
	//�ļ��Ƿ���ֻ����ʽ��
	bool      m_Readonly;

	//ͶӰ
	std::string m_wkt;

	std::vector<Geodatabase::CFieldPtr> m_allFields;

    long  m_lshptype;

	//�ռ�������ָ��
	FILE *m_IndexTree;


 
};


#endif