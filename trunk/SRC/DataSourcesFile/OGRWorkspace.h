#ifndef _OGR_WORKSPACE_H_
#define _OGR_WORKSPACE_H_


#include "IWorkspaceFactory.h"
#include "IWorkspace.h"
#include "FeatureEditCache.h"
#include "ogrsf_frmts.h"

class COGRWorkspaceFactory;

/********************************************************************************
* COGRWorkspace�൱��OGR�е� OGRDataSource,�����а�����һ������FeatureClass,��
* �������ݼ�
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
	//�������ݼ�����Ŀ
	//virtual long DatasetCount(Geodatabase::DatasetType type) const;

	//�õ�ĳ�����ݼ�����������
	//virtual void GetDatasetNames(Geodatabase::DatasetType type,std::vector<std::string> &names) const;


	void UpdateFeature(Geodatabase::IFeatureClass *pFeatureClass,Geodatabase::CFeaturePtr pFeature);

	//ͨ�����ƣ���ʸ��������
	virtual Geodatabase::IFeatureClassPtr  OpenFeatureClass(const char *name);

private:
    
	//OGR�е�����Դ
    OGRDataSource *m_pDataSrc; 

};







#endif