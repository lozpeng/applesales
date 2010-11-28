//////////////////////////////////////////////////////////////////////
// 版权(c) 2008-2020, 天地智绘
// 作者：  champion
// 时间：  2008.6
// 描述：  矢量表的指针的基类
//////////////////////////////////////////////////////////////////////


#ifndef  _IFEATURECURSOR_H_
#define  _IFEATURECURSOR_H_

#include "ICursor.h"
#include "Feature.h"


namespace Geodatabase
{

class IFeatureClass;

class GEODATABASE_DLL IFeatureCursor: public ICursor 
{
public:
	IFeatureCursor(IFeatureClass *pFeatureClass);
	virtual ~IFeatureCursor();

public:
    
    virtual CFeaturePtr NextFeature() =0;

	virtual IRowPtr NextRow();


};

typedef  SYSTEM::CSmartPtr<IFeatureCursor> IFeatureCursorPtr;




}




#endif