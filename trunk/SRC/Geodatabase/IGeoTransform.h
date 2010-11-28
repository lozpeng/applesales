//////////////////////////////////////////////////////////////////////
// ��Ȩ(c) 2008-2020, ����ǻ�
// ���ߣ�  champion
// ʱ�䣺  2008.6
// ������  IGeoTransform������ת���Ľӿ�
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
	* �õ�ԭʼ����ϵ
	*/
	CSpatialReferencePtr GetSourceCS() const;

	/**
	* �õ�Ŀ������ϵ
	*/
	CSpatialReferencePtr GetTargetCS() const;

	/**
	* ת��������
	* @param nCount Ҫת���ĵ���Ŀ
    * @param x X��������
    * @param y Y��������
	* @param z Z��������
	*/
	virtual bool Transform( int nCount, double *x, double *y, double *z = NULL ) = 0;


protected:

	//ԭʼ����ϵ
	CSpatialReferencePtr m_pSrcCS;

    //Ŀ������ϵ
	CSpatialReferencePtr m_pTargetCS;



};

typedef  SYSTEM::CSmartPtr<IGeoTransform> IGeoTransformPtr;

}

#endif
