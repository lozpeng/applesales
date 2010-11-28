//////////////////////////////////////////////////////////////////////
// 版权(c) 2008-2020, 天地智绘
// 作者：  champion
// 时间：  2008.5
// 描述：  IFeatureDataset是所有矢量数据目录的基类，它提供了访问其中矢量数据的接口
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

	//包含数据集的数目
	virtual long FeatureClassCount() const;

	//通过名称，打开矢量数据类
	virtual IFeatureClassPtr OpenFeatureClass(const char *name);

	//得到所有数据类的名称
	virtual void  GetClassNames(std::vector<std::string> &names);

};

typedef  SYSTEM::CSmartPtr<IFeatureDataset> IFeatureDatasetPtr;
 






}




#endif