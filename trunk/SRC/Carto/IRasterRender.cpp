#include "stdafx.h"
#include "IRasterRender.h"
#include "CartoHeader.h"
#include "RasterRGBRender.h"
#include "RasterClassifyColorRender.h"
namespace Carto
{

IRasterRender::IRasterRender()
{
    m_pRasterDataset =NULL;
	m_extRenderName = "";
}
IRasterRender::~IRasterRender()
{

}

void IRasterRender::serialization(SYSTEM::IArchive &ar)
{
	SYSTEM::ISerialization::serialization( ar );
	int type;

	if(ar.IsRead() )
	{
		ar & type;

		m_type = (RASTER_RENDER_TYPE)type;
	}
	else
	{
		type = (int)m_type;
		ar & type;
	}
}

SYSTEM::CSmartPtr<IRasterRender> IRasterRender::CreateRender(Carto::RASTER_RENDER_TYPE type, std::string RenderExtName )
{
	switch(type)
	{
	case RASTER_RGBRENDER:
		return IRasterRenderPtr( new CRasterRGBRender() );
	case RASTER_CLASSIFY_COLORRAMP_RENDER:
        return IRasterRenderPtr( new CRasterClassifyColorRender());
	case RASTER_CUSTOMRENDER: 
		return NULL;
	default:
		return NULL;
	}
}

SYSTEM::CSmartPtr<IRasterRender> IRasterRender::CreateRenderFromStream(SYSTEM::IArchive &ar)
{
	
	int startpos = ar.GetCurrentPos();
	int type;
	ar & type;

	std::string extRenderName = "";

	if (type == RASTER_CUSTOMRENDER)
	{
		ar & extRenderName;
	}

	IRasterRenderPtr pRender = CreateRender( (RASTER_RENDER_TYPE)type, extRenderName);

	ar.GetCurrentPos() = startpos; 

	if (pRender != NULL)
		pRender->serialization( ar );

	return pRender;
}

void IRasterRender::ApplyEnhanceDraw(const int nEnhanceMode)
{
	return;
}

void IRasterRender::ApplyPaletteDraw(BYTE *pbRed, BYTE *pbGreen, BYTE *pbBlue)
{
	return;
}


CLegendInfoPtr IRasterRender::GetLegendInfo()
{
	return NULL;
}

void IRasterRender::SetRasterDataSet(Geodatabase::IRasterDataset* pDataSet)
{
	m_pRasterDataset = pDataSet;
}

} //namespace Carto