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
	//		//��ͼ�ĵ���Χ
	//		GEOMETRY::geom::Envelope viewExtent;
	//		pDisplay->GetDisplayTransformation().GetGeoBound(viewExtent);

	//		//����Դ�ĵ���Χ
	//		GEOMETRY::geom::Envelope dataExtent;
	//		pRaster->GetExtent(&dataExtent);

	//		//�����Ƿ���Ҫ��̬ͶӰ���Ƽ�����������ͼ�ϵ���ʾ��Χ
	//		GEOMETRY::geom::Envelope dataDrawExtent;
	//		
	//			//�жϷ�Χ�Ƿ��ཻ
	//			if(!dataExtent.intersects(viewExtent))
	//				return;

	//			//������ʾ�ĵ���Χ
	//			dataExtent.intersection(viewExtent,dataDrawExtent);

	//			RECT destRect;

	//			//��������ͼ�е�Ŀ�귶Χ
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

