//////////////////////////////////////////////////////////////////////
// ��Ȩ(c) 2008-2020, ����ǻ�
// ���ߣ�  champion
// ʱ�䣺  2008.6
// ������  ʸ��Ҫ�ص�ѡ��
//////////////////////////////////////////////////////////////////////

#ifndef  _IFEATURE_SELECTION_H_
#define  _IFEATURE_SELECTION_H_

#include "SelectionSet.h"
#include <geometry/geom/Geometry.h>

namespace Geodatabase
{

class IFeatureClass;


class GEODATABASE_DLL IFeatureSelection : public CSelctionSet
{
public:
	IFeatureSelection(IFeatureClass *pFeatureClass);

	virtual ~IFeatureSelection();
public:

	//�õ���һ��Ҫ�ص�ͼ�Σ������ڲ���ͼ��ָ��
	virtual const GEOMETRY::geom::Geometry* NextShape();

protected:
    
	SYSTEM::CSmartPtr<GEOMETRY::geom::Geometry> m_pShape;


};

typedef  SYSTEM::CSmartPtr<IFeatureSelection> IFeatureSelectionPtr;


}


#endif
