#include "stdafx.h"
#include "IFeatureDataset.h"

namespace Geodatabase{


IFeatureDataset::IFeatureDataset(IWorkspace *pWorkspace) : IGeodataObject(pWorkspace)
{
	m_objType = GDT_FEATUREDATASET;
}

IFeatureDataset::~IFeatureDataset()
{

}

long IFeatureDataset::FeatureClassCount() const
{
	return 1;
}

IFeatureClassPtr  IFeatureDataset::OpenFeatureClass(const char *name)
{
	return IFeatureClassPtr();
}

void IFeatureDataset::GetClassNames(std::vector<std::string> &names)
{

}

} //namespace Geodatabase