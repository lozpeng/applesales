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
	* ���л�����
	* @param SYSTEM::IArchive &ar �ĵ���
	*/
	virtual void serialization(SYSTEM::IArchive &ar);

	static SYSTEM::CSmartPtr<CRasterLayer> CreateRasterLayer(Geodatabase::IGeodataObjectPtr pDataObject);

    virtual bool SetData(Geodatabase::IGeodataObjectPtr pDataObject);

	virtual void Draw(Display::IDisplayPtr pDisplay,DRAW_CONTENT content);

	virtual void AfterDraw(SYSTEM::CSmartPtr<Display::IDisplay> pDisplay);

	virtual void ClearSelectionSet();

	/**
	* �õ�������Ŀ
	* @return  ����Դ�Ĳ�����
	*/
	long BandCount();

    IRasterRenderPtr GetRender() const;

	void SetRender(IRasterRenderPtr pRender);

	/**
	* ͳ��ָ��ͨ������Ϣ�����PIXEL_INFO�ṹ 
	*/
	bool ExecuteStateByBand(const int nBandIndex,PIXEL_INFO& bandPixInfo);

	CLegendInfoPtr GetLegendInfo();





protected:

	IRasterRenderPtr m_pRender;

};

typedef SYSTEM::CSmartPtr<CRasterLayer> CRasterLayerPtr;

};

#endif