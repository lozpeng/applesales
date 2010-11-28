#include "stdafx.h"
#include "IFeatureClass.h"
#include "IFeatureDataset.h"
#include "Feature.h"

namespace Geodatabase{


IFeatureClass::IFeatureClass(IWorkspace *pWorkspace,IFeatureDataset *pDataset) 
                :ITable(pWorkspace)
{
	m_pDataset =pDataset;
	m_objType = GDT_FEATURECLASS;
}

IFeatureClass::~IFeatureClass()
{

}

IRowPtr IFeatureClass::CreateRow()
{
	return CreateFeature();
}

IRowPtr IFeatureClass::GetRow(long index)
{
	return GetFeature(index);
}

void IFeatureClass::AddRow(Geodatabase::IRow* pRow)
{
    if(!pRow)
	{
		return;
	}
    
	CFeature *pFeature =dynamic_cast<CFeature*>(pRow);

	if(pFeature)
	{
		AddFeature(pFeature);
	}
	
}

void IFeatureClass::UpdateRow(Geodatabase::IRow* pRow)
{
	if(!pRow)
	{
		return;
	}
	CFeature *pFeature =dynamic_cast<CFeature*>(pRow);

	if(pFeature)
	{
		UpdateFeature(pFeature);
	}
}

void IFeatureClass::DeleteRow(long index)
{

	DeleteFeature(index);

}



} //namespace Geodatabase