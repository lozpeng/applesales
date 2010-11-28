//////////////////////////////////////////////////////////////////////
// 版权(c) 2008-2020, 天地智绘
// 作者：  champion
// 时间：  2008.5
// 描述：  地理数据的基类
//////////////////////////////////////////////////////////////////////

#ifndef _IGeodataObject_h
#define _IGeodataObject_h

#include <Geometry/geom/Envelope.h>
#include "IArchive.h"

namespace Geodatabase
{

class IWorkspace;

class GEODATABASE_DLL IGeodataObject 
{
public:
	IGeodataObject(IWorkspace* workspace);
	virtual ~IGeodataObject();

public:

	/**
	* 获取数据对象类型
	* @return 返回数据对象类型
	*/
	GEODATATYPE GetType() const;

	/**
	* 获得名称
	* @return 返回名称
	*/
	std::string Getname() const;

	//得到数据集的范围，pEnvelop是返回的范围
	virtual bool GetExtent(GEOMETRY::geom::Envelope *pEnvelop) const;

	/**
	* 获取数据源
	* @return 返回数据源
	*/
	IWorkspace* GetWorkspace() const;

	/**
	* 序列化数据源相关信息,只存储信息到流
	* @param ar 档案文件流
	*/
	virtual void serialization(SYSTEM::IArchive &ar);

protected:

	//
	std::string m_name;

	//
	GEODATATYPE m_objType;

	//
	IWorkspace* m_pWorkspace;

	//
	GEOMETRY::geom::Envelope m_Envelop;

};

typedef  SYSTEM::CSmartPtr<IGeodataObject> IGeodataObjectPtr;

}

#endif