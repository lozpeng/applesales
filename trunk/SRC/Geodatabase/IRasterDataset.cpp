#include "stdafx.h"
#include "IRasterDataset.h"
#include "IWorkspace.h"
#include "IRasterCatalog.h"

namespace Geodatabase{


IRasterDataset::IRasterDataset(IWorkspace *pWorkspace,IRasterCatalog *pRasterCatalog):IGeodataObject(pWorkspace)
{
	m_objType =GDT_RASTERDATASET;
	m_pRasterCatalog =pRasterCatalog;

}

IRasterDataset::~IRasterDataset()
{

}



bool IRasterDataset::IsWritable()
{
	return false;
}


long IRasterDataset::GetBandCount()
{
	return 0;
}

bool IRasterDataset::GetSize(long *plWidth, long *plHeight)
{
	return false;
}

bool IRasterDataset::GetCellSize (double *pdblSizeX, double *pdblSizeY)
{
	return false;
}

BANDDATATYPE IRasterDataset::GetBandDataType(long lChannelIndex)
{
	return BDT_UNKNOWN;
}


bool IRasterDataset::GetBandMinMaxValue(long lChannelIndex, double *pvMaxValue, double *pvMinValue)
{
	return false;
}



/*@*****************************坐标转换，投影相关接口*****************************************@*/


bool IRasterDataset::SetCoordinateExtent(const GEOMETRY::geom::Envelope &extent)
{
	return false;
}


bool IRasterDataset::WorldToPixel (double dblX, double dblY, long *plCol,long *plRow)
{
	return false;
}


bool IRasterDataset::PixelToWorld ( long lCol,long lRow, double *pdblX, double *pdblY)
{
	return false;

}


std::string IRasterDataset::GetProjection()
{
	return "";
}


bool IRasterDataset::SetProjection(const char *pszWKT)
{
	return false;
}


/*@*****************************数据读取相关接口********************************************@*/

bool    IRasterDataset::GetPixel(long lChannelIndex,long lCol, long lRow,  void *pvValue)
{
	return false;
}

bool	IRasterDataset::SetPixel(long lChannelIndex,long lCol,  long lRow, void *pvValue)
{
	return false;
}

bool IRasterDataset::DataReadBandNormalize(long lBandlIndex, long lCol, long lRow, long lWidth, long lHeight, long lBuffSizeX, long lBuffSizeY, unsigned char *pbBuffer,double& minValue,double& maxValue)
{
	return false;
}

bool IRasterDataset::DataReadBand(long lBandlIndex, long lCol, long lRow, long lWidth, long lHeight, long lBuffSizeX, long lBuffSizeY, void *pvBuffer)
{
	return false;
}

bool IRasterDataset::DataWriteBand(long lBandlIndex, long lCol, long lRow, long lWidth, long lHeight, void *pvBuffer)
{
	return false;
}




/*@*****************************金字塔操作相关接口********************************************@*/

bool	IRasterDataset::HasPyramid()
{
	return false;
}

//建立金字塔
bool IRasterDataset::BuildPyramid(double dResample,SYSTEM::IProgress*)
{
	return false;
}

bool IRasterDataset::DataReadPyramidBand(long lLevel, long lBandlIndex, long lCol, long lRow, long lWidth, long lHeight,long lBuffSizeX, long lBuffSizeY, void *pvBuffer)
{
	return false;
}


bool IRasterDataset::GetPyramidSize( long lLevel, long *lWidth, long *lHeight)
{
	return false;
}

bool IRasterDataset::GetPyramidCellSize(long lLevel, double *pdCellX, double *pdCellY)
{
	return false;
}

bool IRasterDataset::GetPyramidLevelNum(long *lLevelNum)
{
	return false;
}

bool IRasterDataset::ReadPyramidNormal(long lLevel,long lBandlIndex, long lCol, long lRow, long lWidth, long lHeight, long lBuffSizeX, long lBuffSizeY, unsigned char *pbBuffer)
{
	return false;
}


} //namespace Geodatabase