#include "stdafx.h"
#include "IRasterCatalog.h"
#include "IWorkspace.h"
#include "IRasterDataset.h"

namespace Geodatabase{


IRasterCatalog::IRasterCatalog(IWorkspace *pWorkspace):IGeodataObject(pWorkspace)
{
    m_objType =GDT_RASTERCATALOG;	
}

IRasterCatalog::~IRasterCatalog()
{

}

long IRasterCatalog::RasterDatasetCount() const
{
	return 0;
}

void IRasterCatalog::GetDatasetNames(std::vector<std::string> &names)
{

}

IRasterDatasetPtr IRasterCatalog::OpenRasterDataset(const char *name, bool ReadOnly)
{
	return NULL;
}


} //namespace Geodatabase