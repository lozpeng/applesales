#ifndef _RasterRGBRender_H_
#define _RasterRGBRender_H_
#pragma once
#include "irasterrender.h"
#include "IRasterRender.h"
#include "CartoHeader.h"
#include "IRasterDataset.h"

#include <list>
using std::list;

enum COLORTYPE {COLNONE,FULL,RED,GREEN,BLUE,YELLOW,CYAN,MAGENTA};

namespace Carto
{
	class CImageProFunction;

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
		virtual void Draw( Display::IDisplayPtr pDisplay,Geodatabase::IRasterDataset* pRaster);
		/** 
		* 准备用于绘制的数据
		* @param envelop 读取的数据块地理范围
		*/
		void ReadDrawData(GEOMETRY::geom::Envelope dataDrawExtent);
	private:

		/**
		* 读出数据LUT并根据LUT显示数据
		*/
		BOOL DibDraw();
	public:
		/**
		* 获得显示红色波段的序号
		* @return long
		*/
		long GetRedBandIndex() const {return m_ShowBandIndex[0];};

		/**
		* 设置显示红色波段的序号
		* @param lindex 波段序号
		*/
		void SetRedBandIndex(long lindex){m_ShowBandIndex[0] =lindex;UpdateBandPixelInfo(1);};

		/**
		* 获得显示绿色波段的序号
		* @return long
		*/
		long GetGreenBandIndex() const {return m_ShowBandIndex[1];};

		/**
		* 设置显示绿色波段的序号
		* @param lindex 波段序号
		*/
		void SetGreenBandIndex(long lindex) {m_ShowBandIndex[1] =lindex;UpdateBandPixelInfo(2);};

		/**
		* 获得显示蓝色波段的序号
		* @return long
		*/
		long GetBlueBandIndex() const {return m_ShowBandIndex[2];};

		/**
		* 设置显示蓝色波段的序号
		* @param lindex 波段序号
		*/
		void SetBlueBandIndex(long lindex) {m_ShowBandIndex[2] =lindex;UpdateBandPixelInfo(3);};

		/**
		* 设置彩色或灰度显示状态
		*/
		void SetRGBMode(BOOL bRGB) {m_bRGB = bRGB;};

		/**
		* 获得彩色或灰度显示状态，TRUE为真彩色显示，FALSE为灰度显示
		*/
		BOOL GetRGBMode() {return m_bRGB;};
		/** 
		* 在通道组合改变后更新通道统计信息结构
		*/
		bool UpdateBandPixelInfo(unsigned short RGBType /*R - 1,G - 2,B - 3 */);
		/** 
		* 设置某一显示通道的统计信息
		* @param pi 统计信息结构体
		* @param RGBType 指定R G B
		*/
		void SetPixelInfo(const PIXEL_INFO &pi, unsigned short RGBType/*R - 1 , G - 2 , B - 3 */ );
	public:
		/** 
		* 获得当前render的栅格数据源指定波段的LUT表
		*/
		BOOL GetBandLUT (long lChannelIndex, BYTE *pbLUT,long *plNumNodes = NULL,GEOMETRY::geom::Coordinate* pstNodes = NULL);

		/** 
		* 设置当前render的栅格数据源指定波段的LUT表
		*/
		BOOL SetBandLUT (long lChannelIndex, BYTE *pbLUT,long lNumNodes = 0,GEOMETRY::geom::Coordinate* pstNodes = NULL);
	private:
		/**
		* 获取打开的图像一个通道的 LUT 信息
		* @参数lChannelIndex: 波段号
		* @参数pbLUT:   LUT值
		* @参数plNodesCount: 节点的数目
		* @参数pstPts:  节点的坐标
		* @return 成功返回true,失败返回false
		*/
		virtual	bool	GetChannelLUT(long lChannelIndex, BYTE *pbLUT, long *plNodesCount = NULL, GEOMETRY::geom::Coordinate* pstPts = NULL);
		/* 设置打开的图像一个通道的 LUT 信息
		* @参数lChannelIndex: 波段号
		* @参数pbLUT:   LUT值
		* @参数plNodesCount: 节点的数目
		* @参数pstPts:  节点的坐标
		* @return 成功返回true,失败返回false
		*/
		virtual	bool	SetChannelLUT(long lChannelIndex, BYTE *pbLUT, long lNodesCount = 0, GEOMETRY::geom::Coordinate* pstPts = NULL);
		void			ApplyImageProFunction(long lBufLen,unsigned char* pChannel1, unsigned char* pChannel2, unsigned char* pChannel3);
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

		list<CImageProFunction*> mg_lstProFun;

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
