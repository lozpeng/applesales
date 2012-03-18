#pragma once
#include "otcGeometry.h"

class CInterfaceConvert
{
public:
	CInterfaceConvert(void);
	~CInterfaceConvert(void);

public:

	/**
	* 将IotGeometry转换成Geometry*
	* @param pGeometry IotGeometry接口指针
	*/
	static GEOMETRY::geom::Geometry* ConvertIGeo(IotGeometry *pGeometry);

	/**
	* 将IotGeometry转换成Geometry*
	* @param pGeometry Geometry指针
	* @param pRet 返回的IotGeometry指针
	*/
	static void ConvertGeo(GEOMETRY::geom::Geometry* pGeometry,IotGeometry **pRet,bool bOwn=true);

};
