#include "stdafx.h"
#include "OGRWorkspaceFactory.h"
#include "OGRWorkspace.h"
#include "OGRFeatureClass.h"
#include <Geometry/geom/Geometry.h>

using namespace Geodatabase;
using namespace GEOMETRY::geom;
using namespace std;


COGRWorkspace::COGRWorkspace(COGRWorkspaceFactory *pFactory,OGRDataSource *pSrc):IWorkspace(pFactory)
{
	m_type =WT_FileSystem;

    m_pDataSrc =pSrc;
}

COGRWorkspace::~COGRWorkspace()
{
    if(m_pDataSrc)
	{
		//释放数据源
		OGRDataSource::DestroyDataSource( m_pDataSrc );

	}
}

//
//long COGRWorkspace::DatasetCount(Geodatabase::otDatasetType type) const
//{
//	//if(!m_pDataSrc)
//	//{
//	//	return 0;
//	//}
//	//if(type==DT_FeatureClass)
//	//{
// //      
//	//	return m_pDataSrc->GetLayerCount();
//	//}
//	//else
//	//{
// //      return 0;
//	//}
//	//
//	return 0;
//}

//void COGRWorkspace::GetDatasetNames(Geodatabase::otDatasetType type, std::vector<std::string> &names) const
//{
//
//}

IFeatureClassPtr COGRWorkspace::OpenFeatureClass(const char *name)
{
	
	if(!m_pDataSrc)
	{
		return IFeatureClassPtr();
	}
    OGRLayer *pLayer =m_pDataSrc->GetLayerByName(name);
	if(!pLayer)
	{
		return IFeatureClassPtr();
	}
	COGRFeatureClass *pFeatureClass =new COGRFeatureClass(this,pLayer);
	pFeatureClass->m_name =name;

	return IFeatureClassPtr(pFeatureClass);

}

//在指定数据集的编辑缓存中添加一个新的要素
void COGRWorkspace::UpdateFeature(Geodatabase::IFeatureClass *pFeatureClass,Geodatabase::CFeaturePtr pFeature)
{
	if(!m_pDataSrc)
	{
		return ;
	}


}
