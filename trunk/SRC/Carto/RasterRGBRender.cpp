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
	void CRasterRGBRender::Draw(Display::IDisplayPtr pDisplay, GeodataModel::IRasterDataset *pRaster)
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
}

