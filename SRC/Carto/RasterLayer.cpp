#include "stdafx.h"
#include "RasterLayer.h"
#include "IRasterDataset.h"
#include "RasterRGBRender.h"

#pragma   comment(lib,  "msimg32")

namespace Carto
{

CRasterLayer::CRasterLayer()
{
	m_layerType = RasterLayer;
	m_blendDc=NULL;

}

CRasterLayer::~CRasterLayer()
{

}

void CRasterLayer::serialization(SYSTEM::IArchive &ar)
{
	ILayer::serialization( ar );

	if( ar.IsRead() )
	{
		m_pRender = IRasterRender::CreateRenderFromStream( ar );
		Geodatabase::IRasterDataset *pRaster =dynamic_cast<Geodatabase::IRasterDataset*>(m_pDataObject.get());
		if(!pRaster)
		{
			return;
		}
		

		
		CRasterRGBRender *pRender =dynamic_cast<CRasterRGBRender*>(m_pRender.get());

		if(pRaster->GetBandCount()>=3)
		{
			pRender->SetRedBandIndex(1);
			pRender->SetGreenBandIndex(2);
			pRender->SetBlueBandIndex(3);
			pRender->SetRGBMode(TRUE);

			//计算用于显示的通道信息

			PIXEL_INFO pi_r;
			if (ExecuteStateByBand(1,pi_r))
				pRender->SetPixelInfo(pi_r,1);

			PIXEL_INFO pi_g;
			if(ExecuteStateByBand(2,pi_g))
				pRender->SetPixelInfo(pi_g,2);

			PIXEL_INFO pi_b;
			if(ExecuteStateByBand(3,pi_b))
				pRender->SetPixelInfo(pi_b,3);

		}
		else
		{
			pRender->SetRedBandIndex(1);
			pRender->SetGreenBandIndex(1);
			pRender->SetBlueBandIndex(1);
			pRender->SetRGBMode(FALSE);

			PIXEL_INFO pi_r;
			if(ExecuteStateByBand(1,pi_r))
			{
				pRender->SetPixelInfo(pi_r,1);
				pRender->SetPixelInfo(pi_r,2);
				pRender->SetPixelInfo(pi_r,3);
			}

		}

	}
	else
	{
		m_pRender->serialization( ar );
	}
}

CRasterLayerPtr CRasterLayer::CreateRasterLayer(Geodatabase::IGeodataObjectPtr pDataObject)
{
	if(!pDataObject)
	{
		return NULL;
	}

	CRasterLayer *player = new  CRasterLayer();

	if( !player->SetData( pDataObject) )
	{
		return NULL;
	}

	return CRasterLayerPtr(player);

}

IRasterRenderPtr CRasterLayer::GetRender() const
{
	return m_pRender;

}

void CRasterLayer::SetRender(IRasterRenderPtr pRender)
{
	assert(pRender !=NULL);

	m_pRender = pRender;

}

bool CRasterLayer::SetData(Geodatabase::IGeodataObjectPtr pDataObject)
{
    
	Geodatabase::IRasterDataset *pRaster =dynamic_cast<Geodatabase::IRasterDataset*>(pDataObject.get());
	if(!pRaster)
	{
		return false;
	}
	m_pDataObject = pDataObject;

	//设置一个默认的RasterRender
    CRasterRGBRender *pRender =new CRasterRGBRender();

	pRender->SetRasterDataSet(dynamic_cast<Geodatabase::IRasterDataset*>(m_pDataObject.get()));


	if(pRaster->GetBandCount()>=3)
	{
		pRender->SetRedBandIndex(1);
		pRender->SetGreenBandIndex(2);
		pRender->SetBlueBandIndex(3);
		pRender->SetRGBMode(TRUE);

		//计算用于显示的通道信息

		PIXEL_INFO pi_r;
		if (ExecuteStateByBand(1,pi_r))
		   pRender->SetPixelInfo(pi_r,1);
  
		PIXEL_INFO pi_g;
		if(ExecuteStateByBand(2,pi_g))
		   pRender->SetPixelInfo(pi_g,2);

		PIXEL_INFO pi_b;
		if(ExecuteStateByBand(3,pi_b))
		   pRender->SetPixelInfo(pi_b,3);

	}
	else
	{
		pRender->SetRedBandIndex(1);
		pRender->SetGreenBandIndex(1);
		pRender->SetBlueBandIndex(1);
		pRender->SetRGBMode(FALSE);

		PIXEL_INFO pi_r;
		if(ExecuteStateByBand(1,pi_r))
		{
			pRender->SetPixelInfo(pi_r,1);
			pRender->SetPixelInfo(pi_r,2);
			pRender->SetPixelInfo(pi_r,3);
		}

	}
    m_pRender.reset(pRender);

    return true;

}

void CRasterLayer::Draw(Display::IDisplayPtr pDisplay, DRAW_CONTENT content)
{
	if (pDisplay == NULL)	
		return;

	//可见性
	if (!m_bVisible)
	{
		return;
	}
	//图层私有缓存设置
	if (m_bCached)
	{
		if (m_sCachedId < 0)
		{
			pDisplay->AddCache(m_sCachedId);
		}
		pDisplay->set_ActiveCache(m_sCachedId);
	}


	//显示比例尺范围
	if (m_bScaleRange)
	{
		double scaleValue = pDisplay->GetDisplayTransformation().GetScale();

		if (scaleValue < m_dScaleMin)
			return;

		if (scaleValue > m_dScaleMax)
			return;
	}

	// 图层绘制
	if ( m_pRender != NULL && content== drawGeography)
	{
		BeforeDraw(pDisplay);
		m_pRender->Draw( pDisplay, dynamic_cast<Geodatabase::IRasterDataset*>(m_pDataObject.get()) );
		AfterDraw(pDisplay);
	}

	
	ILayer::Draw(pDisplay,drawGeography);
}

void  CRasterLayer::BeforeDraw(SYSTEM::CSmartPtr<Display::IDisplay> pDisplay)
{
	if (m_TransparentAlphaValue!=0)
	{
		m_blendDc =::CreateCompatibleDC((HDC)pDisplay->GetDrawDC()->GetSafeHdc());

		RECT viewrect = pDisplay->GetDisplayTransformation().GetViewPosition().GetViewBound().GetRect();

		long lDcWidth = pDisplay->GetDrawDC()->GetDCWidth();
		long lDcHeight = pDisplay->GetDrawDC()->GetDCHeight();

		m_TransBmp =::CreateCompatibleBitmap((HDC)(pDisplay->GetDrawDC())->GetSafeHdc(),lDcWidth,lDcHeight);

		HBITMAP oldbmp =(HBITMAP)::SelectObject(m_blendDc,m_TransBmp);

		//将原来的背景复制
		::BitBlt(m_blendDc,viewrect.left,viewrect.top,lDcWidth,lDcHeight,(HDC)pDisplay->GetDrawDC()->GetSafeHdc(),
			viewrect.left,viewrect.top,SRCCOPY);




	}
}
void CRasterLayer::AfterDraw(Display::IDisplayPtr pDisplay)
{
	if(!m_pRender)
		return;

	if (m_TransparentAlphaValue!=0)
	{


		RECT viewrect = pDisplay->GetDisplayTransformation().GetViewPosition().GetViewBound().GetRect();

		long lDcWidth = pDisplay->GetDrawDC()->GetDCWidth();
		long lDcHeight = pDisplay->GetDrawDC()->GetDCHeight();
		int iTransExtent = int(m_TransparentAlphaValue * 255.0 / 100.0);

		BLENDFUNCTION  bl;
		bl.AlphaFormat = 0 ;
		bl.BlendFlags = 0;
		bl.BlendOp = AC_SRC_OVER;
		bl.SourceConstantAlpha = 255-iTransExtent;

		::AlphaBlend(m_blendDc,viewrect.left,viewrect.top,lDcWidth,lDcHeight,(HDC)pDisplay->GetDrawDC()->GetSafeHdc(),viewrect.left,viewrect.top,lDcWidth,lDcHeight,bl);

		::BitBlt((HDC)pDisplay->GetDrawDC()->GetSafeHdc(),viewrect.left,viewrect.top,lDcWidth,lDcHeight,m_blendDc,
			viewrect.left,viewrect.top,SRCCOPY);

		::DeleteDC( m_blendDc );
		::DeleteObject(m_TransBmp);

	}
}


void CRasterLayer::ClearSelectionSet()
{

}


long CRasterLayer::BandCount()
{
	Geodatabase::IRasterDataset* pDataset =dynamic_cast<Geodatabase::IRasterDataset*>(m_pDataObject.get());
	return pDataset->GetBandCount();
}

bool Carto::CRasterLayer::ExecuteStateByBand(const int nBandIndex,PIXEL_INFO& bandPixInfo)
{
	/*Geodatabase::IRasterDataset* pDataset =dynamic_cast<Geodatabase::IRasterDataset*>(m_pDataObject.get());

	if (!pDataset->GetB(nBandIndex,bandPixInfo.mp_pHist,&bandPixInfo.Max,&bandPixInfo.Min,&bandPixInfo.Avg,&bandPixInfo.Std))
	 return false;

	bandPixInfo.Valid = true;*/

	return true;

}

CLegendInfoPtr CRasterLayer::GetLegendInfo()
{
	if(m_pRender)
	{
		return m_pRender->GetLegendInfo();
	}
	return NULL;
}

}