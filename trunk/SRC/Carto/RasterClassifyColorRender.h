#ifndef _RASTER_CLASSIFY_COLOR_RENDER_H_
#define _RASTER_CLASSIFY_COLOR_RENDER_H_
#include "IRasterRender.h"
#include "CartoHeader.h"
#include "IRasterDataset.h"
#include "IColorRamp.h"
#include <list>
using std::list;


namespace Carto
{

class CARTO_DLL CRasterClassifyColorRender : public IRasterRender
{
public:
	CRasterClassifyColorRender();
	virtual ~CRasterClassifyColorRender();
public:

	virtual void Draw( Display::IDisplayPtr pDisplay,Geodatabase::IRasterDataset* pRaster);

	/**
	* 对当前专题进行序列化操作
	* @param ar 文档流
	*/
	virtual void serialization(SYSTEM::IArchive &ar);

	int getBreak(){return m_nBreak;}

	void setBreak(int nbreak){m_nBreak=nbreak;}

	Display::IColorRampPtr getColorRamp(){return m_pColorRamp;}

	void setColorRamp(Display::IColorRampPtr pColorRamp);

private:

	template<class DataType>
	void ReadDrawData(GEOMETRY::geom::Envelope dataDrawExtent/*,DataType nulldata*/);

	bool DibDraw();


private:
	//分段数目
	int m_nBreak;
	Display::IColorRampPtr m_pColorRamp;

	std::vector<Display::RGBColor> m_colorgroup;

	Display::IDisplayPtr m_pDisplay;

	//屏幕绘制范围
	RECT			m_destRect;
	//数据显示的地理范围
	GEOMETRY::geom::Envelope m_DrawDataEnv;

	//用于读取显示的图像采样宽
	long			mp_lResampleWidth;

	//用于读取显示的图像采样高
	long			mp_lResampleHeight;

	//当前采样比
	double			mp_dblResampleRatio;

	//采样数据尺寸
	long			mp_lResampleBufferSize;

	unsigned char	*mp_pucBufSrc[3];

};


}

#endif