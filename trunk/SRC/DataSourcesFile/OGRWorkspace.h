#ifndef _OGR_WORKSPACE_H_
#define _OGR_WORKSPACE_H_


#include "IWorkspaceFactory.h"
#include "IWorkspace.h"
#include "FeatureEditCache.h"
#include "ogrsf_frmts.h"

class COGRWorkspaceFactory;

/********************************************************************************
* COGRWorkspace相当于OGR中的 OGRDataSource,它其中包含了一个或多个FeatureClass,不
* 包含数据集
*
*********************************************************************************/
class DSFile_DLL COGRWorkspace: public Geodatabase::IWorkspace
{
	friend class COGRWorkspaceFactory;
protected:
	COGRWorkspace(COGRWorkspaceFactory *pFactory,OGRDataSource *pSrc);
public:
	virtual ~COGRWorkspace();
public:
	//包含数据集的数目
	//virtual long DatasetCount(Geodatabase::DatasetType type) const;

	//得到某类数据集的所有名称
	//virtual void GetDatasetNames(Geodatabase::DatasetType type,std::vector<std::string> &names) const;


	void UpdateFeature(Geodatabase::IFeatureClass *pFeatureClass,Geodatabase::CFeaturePtr pFeature);

	//通过名称，打开矢量数据类
	virtual Geodatabase::IFeatureClassPtr  OpenFeatureClass(const char *name);

private:
    
	//OGR中的数据源
    OGRDataSource *m_pDataSrc; 

};







#endif