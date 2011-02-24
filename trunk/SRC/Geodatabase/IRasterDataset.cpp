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



/*@*****************************����ת����ͶӰ��ؽӿ�*****************************************@*/


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


/*@*****************************���ݶ�ȡ��ؽӿ�********************************************@*/

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




/*@*****************************������������ؽӿ�********************************************@*/

bool	IRasterDataset::HasPyramid()
{
	return false;
}

//����������
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