//////////////////////////////////////////////////////////////////////
// ��Ȩ(c) 2008-2020, ����ǻ�
// ���ߣ�  champion
// ʱ�䣺  2008.6
// ������  ʸ�����ָ��Ļ���
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