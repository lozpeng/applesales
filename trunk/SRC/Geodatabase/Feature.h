//////////////////////////////////////////////////////////////////////
// 版权(c) 2008-2020, 天地智绘
// 作者：  champion
// 时间：  2008.5
// 描述：  CFeature类保存了一个矢量要素的图形信息和属性信息
//////////////////////////////////////////////////////////////////////

#ifndef  _GEODATABASE_FEATURE_H_
#define  _GEODATABASE_FEATURE_H_

#include "IRow.h"
#include <string>
#include <vector>
#include <comutil.h>

namespace GEOMETRY
{
	namespace geom
	{
		class Geometry;
	}
}

namespace Geodatabase
{

class IFeatureClass;
class CField;

class GEODATABASE_DLL CFeature: public IRow 
{
public:
	CFeature(IFeatureClass *pFeatureClass,long oid);

	//拷贝构造
	CFeature(const CFeature &other);

	virtual ~CFeature();

public:

	//得到矢量图形
	GEOMETRY::geom::Geometry* GetShape() const {return m_pGeometry;};

	//得到图形的拷贝
	GEOMETRY::geom::Geometry* GetShapeClone() const;

	//设置图形
	void SetShape(GEOMETRY::geom::Geometry* pGeometry);

	//将更改保存回表中
	virtual void Update();
	//在表中删除该记录
	virtual void Delete();
	//将所有的值制空
	virtual void SetEmpty();

	//得到要素的拷贝
	virtual CFeature* Clone();


public:
	GEOMETRY::geom::Geometry*   m_pGeometry;


};

typedef  SYSTEM::CSmartPtr<CFeature> CFeaturePtr;




}




#endif