//////////////////////////////////////////////////////////////////////
// ��Ȩ(c) 2008-2020, ����ǻ�
// ���ߣ�  champion
// ʱ�䣺  2008.6
// ������  ͶӰת���Ķ���
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
	* ת��������
	* @param nCount Ҫת���ĵ���Ŀ
	* @param x X��������
	* @param y Y��������
	* @param z Z��������
	*/
	 bool Transform( int nCount, double *x, double *y, double *z = NULL );

private:
	void Clear();
private:

	//����OGRProj4CT������
	void *m_handle;

};

typedef  SYSTEM::CSmartPtr<CProjTransform> CProjTransformPtr;

}

#endif
