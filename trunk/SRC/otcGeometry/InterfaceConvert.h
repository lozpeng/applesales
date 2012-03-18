#pragma once
#include "otcGeometry.h"

class CInterfaceConvert
{
public:
	CInterfaceConvert(void);
	~CInterfaceConvert(void);

public:

	/**
	* ��IotGeometryת����Geometry*
	* @param pGeometry IotGeometry�ӿ�ָ��
	*/
	static GEOMETRY::geom::Geometry* ConvertIGeo(IotGeometry *pGeometry);

	/**
	* ��IotGeometryת����Geometry*
	* @param pGeometry Geometryָ��
	* @param pRet ���ص�IotGeometryָ��
	*/
	static void ConvertGeo(GEOMETRY::geom::Geometry* pGeometry,IotGeometry **pRet,bool bOwn=true);

};
