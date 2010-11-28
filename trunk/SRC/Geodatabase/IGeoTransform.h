//////////////////////////////////////////////////////////////////////
// 版权(c) 2008-2020, 天地智绘
// 作者：  champion
// 时间：  2008.6
// 描述：  IGeoTransform是坐标转换的接口
//////////////////////////////////////////////////////////////////////

#ifndef  _GEO_TRANSFORM_H_
#define  _GEO_TRANSFORM_H_

#include "SpatialReference.h"

namespace Geodatabase
{


class GEODATABASE_DLL IGeoTransform
{
	
public:
	
    IGeoTransform();

	virtual ~IGeoTransform();


public:

	/**
	* 得到原始坐标系
	*/
	CSpatialReferencePtr GetSourceCS() const;

	/**
	* 得到目标坐标系
	*/
	CSpatialReferencePtr GetTargetCS() const;

	/**
	* 转换点坐标
	* @param nCount 要转换的点数目
    * @param x X坐标数组
    * @param y Y坐标数组
	* @param z Z坐标数组
	*/
	virtual bool Transform( int nCount, double *x, double *y, double *z = NULL ) = 0;


protected:

	//原始坐标系
	CSpatialReferencePtr m_pSrcCS;

    //目标坐标系
	CSpatialReferencePtr m_pTargetCS;



};

typedef  SYSTEM::CSmartPtr<IGeoTransform> IGeoTransformPtr;

}

#endif
