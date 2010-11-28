//////////////////////////////////////////////////////////////////////
// 版权(c) 2008-2020, 天地智绘
// 作者：  champion
// 时间：  2008.6
// 描述：  地理参考系类的定义
//////////////////////////////////////////////////////////////////////

#ifndef  _SPATIAL_REFERENCE_H_
#define  _SPATIAL_REFERENCE_H_

#include "SystemUnit.h"

namespace Geodatabase
{


class GEODATABASE_DLL CSpatialReference
{
	friend class CSpatialReference;
public:
    CSpatialReference();
	CSpatialReference(const char *wkt);
	CSpatialReference(const CSpatialReference& other);
    
	virtual ~CSpatialReference();

	CSpatialReference &operator=(const CSpatialReference& other);

public:
    
	/**
	* 获得对象的拷贝
	*/
	CSpatialReference* Clone() const;

	/**
	* 导入Wkt字符串
	* @param wkt 表示坐标参考系的字符串
	*/
	bool ImportFromWkt(const char *wkt);

	/**
	* 导入ESRI投影定义字符串
	* @param wkt 表示坐标参考系的字符串
	*/
	bool ImportFromESRI(const char *wkt);

	/**
	* 导出Wkt字符串
	*/
	std::string ExportToWkt() const;

	/**
	* 是否地理坐标系
	*/
	bool IsGeographic() const;

	/**
	* 是否投影坐标系
	*/
	bool IsProjected() const;

	/**
	* 两个参考系是否相同
	*/
    bool IsSame(const CSpatialReference* pOther) const;

	/**
	* 得到地理参考系名称
	*/
	std::string GetGeogName() const;

	/**
	* 得到投影名称
	*/
	std::string GetProjName() const;

    //得到大地坐标系单位
	SYSTEM::SYS_UNIT_TYPE GetLinearUnits() const;

	//得到经纬度坐标单位
	SYSTEM::SYS_UNIT_TYPE GetAngularUnits() const;


	/**
	* 得到内部指针
	*/
	void* GetHandle() const;


private:

	//将内部指针清空
	void Clear();

private:
	//保存GDAL的OGRSpatialReference指针
	void *m_Handle;

};

typedef  SYSTEM::CSmartPtr<CSpatialReference> CSpatialReferencePtr;

}

#endif