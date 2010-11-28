#include "stdafx.h"
#include "RasterWorkspace.h"
#include "RasterWSFactory.h"
#include "DSRasterDataset.h"
#include "gdal_priv.h"

using namespace Geodatabase;
using namespace std;


CRasterWorkspace::CRasterWorkspace(CRasterWSFactory *pFactory):IWorkspace(pFactory)
{
	m_type =WT_FileSystem;

}

CRasterWorkspace::~CRasterWorkspace()
{

}



/*****************************************************************************************************
*  以下为打开栅格数据相关的操作
*
*******************************************************************************************************/

IRasterDatasetPtr CRasterWorkspace::OpenRasterDataset(const char *name, bool ReadOnly)
{

	GDALDataset* m_pDataset =NULL;
	if(ReadOnly)
	{
		m_pDataset=(GDALDataset*)GDALOpen(name,GA_ReadOnly);
	}
	else
	{
		m_pDataset=(GDALDataset*)GDALOpen(name,GA_Update);
	}

	if(NULL==m_pDataset)
	{
		return false;
	}

	CDSRasterDataset *pDataset =new CDSRasterDataset(this,m_pDataset,ReadOnly,name);

	return IRasterDatasetPtr(pDataset);
}

bool CRasterWorkspace::CreateRasterDataset(const char *name,RasFileInfo *fileInfo)
{


	return false;



}
