//////////////////////////////////////////////////////////////////////
  // 版权(c) 2010-2020, 天地智绘
  // 作者：  hhzhao
  // 时间：  2009/11/23
  // 描述：  shapefileFeatureclass  shapefile要素集类
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

	virtual void serialization(SYSTEM::IArchive &ar);
public:
	
    long GetTotalNum();

	//初始化，读取一些基本信息
	void Init();

	//读取投影信息
	bool ReadPrj();

	void GetFeatureValue(long &index,Geodatabase::CFeaturePtr &pFeature,bool &bhasShape,std::vector<long> &fieldsIndex);

	Geodatabase::ICursorPtr SimpleQuery(Geodatabase::CSimpleQuery* query,bool bReadOnly);

	Geodatabase::ICursorPtr SpatialQuery(Geodatabase::CSpatialQuery* query,bool bReadOnly);

	//简单的条件选择
	Geodatabase::ISelctionSetPtr SimpleSelect(Geodatabase::CSimpleQuery* query);

	//空间查询选择
	Geodatabase::ISelctionSetPtr SpatialSelect(Geodatabase::CSpatialQuery* query);
private:
	Geodatabase::CFeature *ShpReadFeature(long index);

	GEOMETRY::geom::Geometry* ReadShape(long index);

	//建立空间索引
	void BuildSpatialIndex();

private:
    SHPHandle m_shpHandle;
	DBFHandle m_dbfHandle;
	//文件是否是只读方式打开
	bool      m_Readonly;

	//投影
	std::string m_wkt;

	std::vector<Geodatabase::CFieldPtr> m_allFields;

    long  m_lshptype;

	//空间索引的指针
	FILE *m_IndexTree;


 
};


#endif