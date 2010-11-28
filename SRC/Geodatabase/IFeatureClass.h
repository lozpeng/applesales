//////////////////////////////////////////////////////////////////////
// 版权(c) 2008-2020, 天地智绘
// 作者：  champion
// 时间：  2008.5
// 描述：  矢量数据集的基类
//////////////////////////////////////////////////////////////////////

#ifndef  _IFEATURECLASS_H_
#define  _IFEATURECLASS_H_

#include "ITable.h"
#include "Feature.h"
#include "SystemUnit.h"
#include <string>
namespace GEOMETRY
{
	namespace geom
	{
		class Geometry;
		class Envelope;
	}
}
namespace Geodatabase
{

class IFeatureDataset;

/** 
 * 矢量数据集的定义
 */
 struct FeatureClassDef
 {
	 FeatureClassDef( ):minx(0.0),miny(0.0),maxx(0.0),maxy(0.0),scale(10000),hasz(false),hasm(false){}
	 

	 double minx;
	 double miny;
	 double maxx;
	 double maxy;                        /** 数据源地理外矩*/
	 std::string wkt;                    //投影字符串
	 std::string description;            //数据描述
	 long        scale;                   //比例尺
	 long        lshptype;                //图形的类别,为Geometry中的类别
	 bool      hasz;                     //是否具有z值
	 bool      hasm;                     //是否具有m值
	 std::vector<CFieldPtr> FieldsDef;   //字段描述

 };

class GEODATABASE_DLL IFeatureClass :public ITable
{
public:
	IFeatureClass(IWorkspace *pWorkspace,IFeatureDataset *pDataset);
	virtual ~IFeatureClass();

public:

	IFeatureDataset *FeatureDataset() const{return m_pDataset;}

	//包含要素的数目
	virtual long FeatureCount() const =0;

	//要素的图形类型,为GEOMETRY::geom::GeometryTypeId类型
	virtual long ShapeType() =0;

	//图形数据字段的名称
	virtual std::string  ShapeFieldName() =0;

	///////以下为要素的操作方法///////////////////////////////////////////////////
	//在数据类中创建一个空的要素，属性为空
	virtual CFeaturePtr CreateFeature() =0;

	//根据要素ID的获取要素,序号从1开始
	virtual CFeaturePtr GetFeature(long index)=0;

	//根据要素ID获取要素的图形
	virtual GEOMETRY::geom::Geometry* GetFeatureShape(long index) =0;

	//添加一个新要素
	virtual void AddFeature(CFeature* pFeature) =0;

	//更新一个要素
	virtual void UpdateFeature(CFeature* pFeature) =0;

	//删除一个要素
	virtual void DeleteFeature(long index) =0; 
	///////以下为查询的操作方法///////////////////////////////////////////////////

	//矩形查询
	virtual ISelctionSetPtr SelectByRect(const double &xmin,const double &ymin, const double &xmax,const double &ymax) =0;

	//通过范围来查询，返回一个指针
	virtual ICursorPtr QueryByExtent(GEOMETRY::geom::Envelope *pEnvelop,CSimpleQuery *pQuery,bool bReadOnly =true) =0;
	///////////投影相关///////////////////////////////////////////////////////////
	virtual std::string GetWkt() const =0;

	virtual void SetWkt(const char* strwkt) =0;

	//是否具有M值或Z值
	virtual bool HasM() const =0;

	virtual bool HasZ() const =0;

protected:
	//////////////以下为实现的ITable的接口///////////////////////////////////
	//在表中创建一个空的记录，属性为空
	virtual IRowPtr CreateRow();

	//根据记录ID获取记录
	virtual IRowPtr GetRow(long index);

	//添加一条新的记录
	virtual void AddRow(IRow* pRow);

	//更新一条记录
	virtual void UpdateRow(IRow* pRow);

	//删除一条记录
	virtual void DeleteRow(long index); 


public:
	IFeatureDataset   *m_pDataset;



};

typedef  SYSTEM::CSmartPtr<IFeatureClass> IFeatureClassPtr;




}




#endif