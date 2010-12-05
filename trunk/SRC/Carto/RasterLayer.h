#ifndef _RasterLayer_h
#define _RasterLayer_h

#include "IRasterRender.h"
#include "Map.h"

namespace Carto
{

class CARTO_DLL CRasterLayer : public ILayer
{
public:

	CRasterLayer();

	virtual ~CRasterLayer();

	/**
	* 序列化操作
	* @param SYSTEM::IArchive &ar 文档流
	*/
	virtual void serialization(SYSTEM::IArchive &ar);

	static SYSTEM::CSmartPtr<CRasterLayer> CreateRasterLayer(Geodatabase::IGeodataObjectPtr pDataObject);

    virtual bool SetData(Geodatabase::IGeodataObjectPtr pDataObject);

	virtual void Draw(Display::IDisplayPtr pDisplay,DRAW_CONTENT content);

	virtual void AfterDraw(SYSTEM::CSmartPtr<Display::IDisplay> pDisplay);

	virtual void ClearSelectionSet();

	/**
	* 得到波段数目
	* @return  数据源的波段数
	*/
	long BandCount();

    IRasterRenderPtr GetRender() const;

	void SetRender(IRasterRenderPtr pRender);

	/**
	* 统计指定通道的信息，填充PIXEL_INFO结构 
	*/
	bool ExecuteStateByBand(const int nBandIndex,PIXEL_INFO& bandPixInfo);

	CLegendInfoPtr GetLegendInfo();





protected:

	IRasterRenderPtr m_pRender;

};

typedef SYSTEM::CSmartPtr<CRasterLayer> CRasterLayerPtr;

};

#endif