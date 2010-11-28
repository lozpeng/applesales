//////////////////////////////////////////////////////////////////////
// ��Ȩ(c) 2008-2020, ����ǻ�
// ���ߣ�  champion
// ʱ�䣺  2008.5
// ������  IFeatureDataset������ʸ������Ŀ¼�Ļ��࣬���ṩ�˷�������ʸ�����ݵĽӿ�
//////////////////////////////////////////////////////////////////////

#ifndef  _IFEATUREDATASET_H_
#define  _IFEATUREDATASET_H_

#include "IFeatureClass.h"
#include "IGeodataObject.h"
#include <string>
#include <map>

namespace Geodatabase
{
class IWorkspace;

class GEODATABASE_DLL IFeatureDataset : public IGeodataObject
{
public:
	IFeatureDataset(IWorkspace *pWorkspace);
	virtual ~IFeatureDataset();

public:

	//�������ݼ�����Ŀ
	virtual long FeatureClassCount() const;

	//ͨ�����ƣ���ʸ��������
	virtual IFeatureClassPtr OpenFeatureClass(const char *name);

	//�õ����������������
	virtual void  GetClassNames(std::vector<std::string> &names);

};

typedef  SYSTEM::CSmartPtr<IFeatureDataset> IFeatureDatasetPtr;
 






}




#endif