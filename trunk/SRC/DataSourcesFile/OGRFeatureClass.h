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

	//包含记录的数目
	virtual long RowCount() const;

	///////以下为字段的操作方法///////////////////////////////////////////////////
	//添加一条新的字段
	virtual void AddField(Geodatabase::CField *pField) ;

	//删除一个字段
	virtual void DeleteField(long index) ;

	//通过字段名查找字段的序号
	virtual long FindField(const char* name);

	//通过序号得到一个字段的描述
	virtual Geodatabase::CFieldPtr GetField(long index);

	virtual long FieldCount() const;

	virtual std::string  ShapeFieldName();

	///////以下为查询的操作方法///////////////////////////////////////////////////

	//通过查询条件进行查询，返回一个选择集
	virtual Geodatabase::ISelctionSetPtr Select(Geodatabase::CSimpleQuery* query);

	//矩形查询
	virtual Geodatabase::ISelctionSetPtr SelectByRect(const double &xmin,const double &ymin,const double &xmax,const double &ymax);

	//通过查询条件查询，返回一个指针
	virtual Geodatabase::ICursorPtr Query(Geodatabase::CSimpleQuery* query,bool bReadOnly =true);

	virtual Geodatabase::ICursorPtr QueryByExtent(GEOMETRY::geom::Envelope *pEnvelop,Geodatabase::CSimpleQuery *pQuery,bool bReadOnly =true);

	//包含要素的数目
	virtual long FeatureCount() const ;

	//要素的图形类型,为GEOMETRY::geom::GeometryTypeId类型
	virtual long ShapeType() ;

	///////以下为要素的操作方法///////////////////////////////////////////////////
	//在数据类中创建一个空的要素，属性为空
	virtual Geodatabase::CFeaturePtr CreateFeature() ;

	//根据要素ID的获取要素
	virtual Geodatabase::CFeaturePtr GetFeature(long index);

	//根据要素ID获取要素的图形
	virtual GEOMETRY::geom::Geometry* GetFeatureShape(long index);

	//添加一个新要素
	virtual void AddFeature(Geodatabase::CFeature *pFeature);

	//更新一个要素
	virtual void UpdateFeature(Geodatabase::CFeature *pFeature);

	//删除一个要素
	virtual void DeleteFeature(long index) ; 

	///////////投影相关///////////////////////////////////////////////////////////
	virtual std::string GetWkt() const ;

	virtual void SetWkt(const char* strwkt);

	//得到数据集的范围，pEnvelop是返回的范围
	virtual bool GetExtent(GEOMETRY::geom::Envelope *pEnvelop) const ;

	//是否具有M值或Z值
	virtual bool HasM() const ;

	virtual bool HasZ() const ;

public:
	//将OGRFeature转换为CFeature
	bool ConvertFeature(OGRFeature *poFeature,Geodatabase::CFeature **ppFeature);

	//将OGRGeometry转换成Geometry
	static bool OGRGeometry2Geometry(OGRGeometry *poGeometry,GEOMETRY::geom::Geometry **ppGeometry);

	Geodatabase::ICursorPtr SimpleQuery(Geodatabase::CSimpleQuery* query,bool bReadOnly);

	Geodatabase::ICursorPtr SpatialQuery(Geodatabase::CSpatialQuery* query,bool bReadOnly);

	//简单的条件选择
	Geodatabase::ISelctionSetPtr SimpleSelect(Geodatabase::CSimpleQuery* query);

	//空间查询选择
	Geodatabase::ISelctionSetPtr SpatialSelect(Geodatabase::CSpatialQuery* query);

private:
	void Init();
private:

	//数据源
    OGRLayer *m_pOGRLayer;
	//要素图形的类型
	long                m_lshptype;

	//数据的地理范围
	GEOMETRY::geom::Envelope m_envelop;

public:
	virtual void Print();
};


#endif