//////////////////////////////////////////////////////////////////////
// 版权(c) 2008-2020, 天地智绘
// 作者：  champion
// 时间：  2008.6
// 描述：  投影转换的定义
//////////////////////////////////////////////////////////////////////

#ifndef  _PROJ_TRANSFORM_H_
#define  _PROJ_TRANSFORM_H_

#include "IGeoTransform.h"

namespace Geodatabase
{


class GEODATABASE_DLL CProjTransform :public IGeoTransform
{

public:

	CProjTransform();

	CProjTransform(CSpatialReferencePtr pSrcCS,CSpatialReferencePtr pTargetCS);

	virtual ~CProjTransform();


public:

	void Init(CSpatialReferencePtr pSrcCS,CSpatialReferencePtr pTargetCS);

	/**
	* 转换点坐标
	* @param nCount 要转换的点数目
	* @param x X坐标数组
	* @param y Y坐标数组
	* @param z Z坐标数组
	*/
	 bool Transform( int nCount, double *x, double *y, double *z = NULL );

private:
	void Clear();
private:

	//保存OGRProj4CT的坐标
	void *m_handle;

};

typedef  SYSTEM::CSmartPtr<CProjTransform> CProjTransformPtr;

}

#endif
