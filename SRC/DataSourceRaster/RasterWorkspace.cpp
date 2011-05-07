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
		return NULL;
	}

	CDSRasterDataset *pDataset =new CDSRasterDataset(this,m_pDataset,ReadOnly,name);

	return IRasterDatasetPtr(pDataset);
}

bool CRasterWorkspace::CreateRasterDataset(const char *name,RasFileInfo *fileInfo)
{

	GDALDataType datatype;
	BANDDATATYPE ldatatype=(BANDDATATYPE)fileInfo->lDataType;
	if(BDT_BYTE==ldatatype)
	{
		datatype=GDT_Byte;
	}
	else if(BDT_USHORT==ldatatype)
	{
		datatype=GDT_UInt16;
	}
	else if(BDT_SHORT==ldatatype)
	{
		datatype=GDT_Int16;
	}
	else if(BDT_FLOAT==ldatatype)
	{
		datatype=GDT_Float32;
	}
	else if(BDT_DOUBLE==ldatatype)
	{
		datatype=GDT_Float64;
	}
	//获取文件名后缀
	string ext =name;

	ext =ext.substr(ext.rfind('.')+1,ext.size()-ext.rfind('.')-1);

	GDALDriver *poDriver=NULL;
	if(stricmp(ext.c_str(),"tif")==0 || stricmp(ext.c_str(),"tiff")==0)
	{
		poDriver =GetGDALDriverManager()->GetDriverByName("GTiff");
	}
	else if(stricmp(ext.c_str(),"jpg")==0)
	{
		poDriver =GetGDALDriverManager()->GetDriverByName("JPEG");
	}
	else if(stricmp(ext.c_str(),"bmp")==0)
	{
		poDriver =GetGDALDriverManager()->GetDriverByName("BMP");
	}
	if(!poDriver)
	{
		return false;
	}
	
	GDALDataset *poDstDS=0;
	poDstDS=poDriver->Create(name,fileInfo->lWidth,fileInfo->lHeight,fileInfo->lChannelNum,datatype,0);

	if(poDstDS ==NULL)
	{
		return false;
	}
	delete poDstDS;
	return true;

}
