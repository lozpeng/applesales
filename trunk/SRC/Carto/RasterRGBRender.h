#ifndef _RasterRGBRender_H_
#define _RasterRGBRender_H_
#pragma once
#include "irasterrender.h"
#include "IRasterRender.h"
#include "CartoHeader.h"

#include <list>
using std::list;

namespace Carto
{
	class CARTO_DLL CRasterRGBRender : public IRasterRender
	{
	public:
		CRasterRGBRender(void);
		~CRasterRGBRender(void);
	public:
		/**
	* 对选中的记录集进行绘制
	* @param pDisplay 智能指针，指向显示接口
	* @param pRaster 栅格数据源
	*/
	virtual void Draw( Display::IDisplayPtr pDisplay,GeodataModel::IRasterDataset* pRaster);
	protected:

		Display::IDisplayPtr m_pDisplay;

		//RGB波段的序号
		long m_ShowBandIndex[3];

		//表示RGB或灰度显示
		BOOL m_bRGB;

		//当前最近一次的处理的增强算法
		long				mg_lProcessMethod;

		COLORREF			mg_crStart;//渐进色的起始色

		COLORREF			mg_crEnd;//渐进色的起始色

		BOOL				mg_bStretched;//是否为渐进色 

		//R G B调色板

		BYTE				mg_byRed[256];

		BYTE				mg_byGreen[256];

		BYTE				mg_byBlue[256];


		//透明显示
		BOOL   m_bBackTrans;

		//透明色
		COLORREF  m_transColor;	

		unsigned short				m_usBrightness;		//亮度调整值0~100
		unsigned short				m_usContrastness;	//对比度调整值0~100

		//直方图调整时的尺度
		float m_fStandardDeviationScale;

		PIXEL_INFO m_PixelInfo[3];

		//对应显示区原始采样数据
		unsigned char	*mp_pucBufSrc[3];

		//对应显示区原始采样数据经过处理列表处理后得到的数据
		unsigned char	*mp_pucBufPro[3];	

		//数据显示的地理范围
		GEOMETRY::geom::Envelope m_DrawDataEnv;

		//当前采样比
		double			mp_dblResampleRatio;	

		//用于读取显示的图像采样宽
		long			mp_lResampleWidth;

		//用于读取显示的图像采样高
		long			mp_lResampleHeight;

		//采样数据尺寸
		long          mp_lResampleBufferSize;

		//屏幕绘制范围
		RECT m_destRect;


		bool m_bLocked;
	};
	typedef SYSTEM::CSmartPtr<CRasterRGBRender> CRasterRGBRenderPtr;
}
#endif //_RasterRGBRender_H_
