#include "StdAfx.h"
#include "RasterRGBRender.h"

namespace Carto
{
	CRasterRGBRender::CRasterRGBRender(void)
	{
	}
	CRasterRGBRender::~CRasterRGBRender(void)
	{
	}
	void CRasterRGBRender::Draw(Display::IDisplayPtr pDisplay, Geodatabase::IRasterDataset *pRaster)
	{
	//	if(!pRaster)
	//	{
	//		return;
	//	}

	//	m_pDisplay = pDisplay;

	//	m_pRasterDataset =pRaster;

	//	if (!m_bLocked)
	//	{
	//		//视图的地理范围
	//		GEOMETRY::geom::Envelope viewExtent;
	//		pDisplay->GetDisplayTransformation().GetGeoBound(viewExtent);

	//		//数据源的地理范围
	//		GEOMETRY::geom::Envelope dataExtent;
	//		pRaster->GetExtent(&dataExtent);

	//		//根据是否需要动态投影绘制计算数据在视图上的显示范围
	//		GEOMETRY::geom::Envelope dataDrawExtent;
	//		
	//			//判断范围是否相交
	//			if(!dataExtent.intersects(viewExtent))
	//				return;

	//			//数据显示的地理范围
	//			dataExtent.intersection(viewExtent,dataDrawExtent);

	//			RECT destRect;

	//			//计算在视图中的目标范围
	//			pDisplay->GetDisplayTransformation().ConvertGeoToDisplay(dataDrawExtent.getMinX(),dataDrawExtent.getMinY(),destRect.left,destRect.bottom);
	//			pDisplay->GetDisplayTransformation().ConvertGeoToDisplay(dataDrawExtent.getMaxX(),dataDrawExtent.getMaxY(),destRect.right,destRect.top);

	//			if(destRect.bottom ==destRect.top || destRect.left ==destRect.right)
	//				return;
	//			m_destRect = destRect;

	//			m_DrawDataEnv = dataDrawExtent;

	//			ReadDrawData(dataDrawExtent);

	//	}
	//	DibDraw();
	}
	bool CRasterRGBRender::UpdateBandPixelInfo(unsigned short RGBType)
{
	if(!m_pRasterDataset)
		return false;

	/*if (!m_pRasterDataset->GetChannelStatisInfo(m_ShowBandIndex[RGBType-1],m_PixelInfo[RGBType-1].mp_pHist,&m_PixelInfo[RGBType-1].Max,&m_PixelInfo[RGBType-1].Min,&m_PixelInfo[RGBType-1].Avg,&m_PixelInfo[RGBType-1].Std))
	{
		m_PixelInfo[RGBType-1].Valid = false;
		return false;
	}	

	m_PixelInfo[RGBType-1].Valid = true;*/
	return true;
}
	void CRasterRGBRender::SetPixelInfo(const PIXEL_INFO &pi, unsigned short RGBType)
{
   assert(RGBType>=1 && RGBType <= 3);

	RGBType--;

	m_PixelInfo[RGBType] = pi;
}

}

