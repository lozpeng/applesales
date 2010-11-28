//////////////////////////////////////////////////////////////////////
// 版权(c) 2008-2020, 天地智绘
// 作者：  champion
// 时间：  2008.6
// 描述：  矢量要素的选择集
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

	//得到下一个要素的图形，返回内部的图形指针
	virtual const GEOMETRY::geom::Geometry* NextShape();

protected:
    
	SYSTEM::CSmartPtr<GEOMETRY::geom::Geometry> m_pShape;


};

typedef  SYSTEM::CSmartPtr<IFeatureSelection> IFeatureSelectionPtr;


}


#endif
