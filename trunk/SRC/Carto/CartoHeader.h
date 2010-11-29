//////////////////////////////////////////////////////////////////////
// 版权(c) 2010-2020, 天地智绘
// 作者：  hhzhao
// 时间：  2010/11/20
// 描述：  各种结构的定义
//////////////////////////////////////////////////////////////////////
#ifndef _Carto_Header_H
#define _Carto_Header_H
namespace Carto
{
	/**
	*图层类型：矢量图层、栅格图层、TIN图层、标注图层
	*/
	enum LAYER_TYPE
	{
		eUnknown,
		eFeatureLayer,
		eRasterLayer,
		eTinLayer,
		eGraphicLayer

	};

	enum LAYER_POSITION
	{
		TBottom,
		TNormal,
		TTop
	};

	enum SELECT_OPTION
	{
		TSELECT_REPLACE,
		TSELECT_ADD,
		TSELECT_SUBTRACT,
		TSELECT_INTERSECT
	};

	/** 
	* 专题类型
	*/
	enum RENDER_TYPE
	{
		SIMPLERENDER = 0x01,/**< 简单专题*/
		MIXSIMPLERENDER = 0x21,/**< 复合专题*/
		SIZECLASSRENDER = 0x02,
		WIDTHCLASSRENDER = 0x03,
		SIZEGRADERENDER = 0x04,
		UNIQUERENDER = 0x05, //唯一值
		RANGERENDER = 0x06,  //范围
		DOTDENSITYRENDER = 0x07,
		PILLARRENDER = 0x08,
		PIERENDER = 0x09,
		TRIANGLERENDER = 0x10,
		CHARTRENDER = 0x11,//图表专题图
		CUSTOMRENDER = 0x12,/**< 自定义专题，用于编写扩展专题*/
	};

	/** 
	* 栅格渲染类型
	*/
	enum RASTER_RENDER_TYPE
	{
		RASTER_RGBRENDER = 0x01,/**< RGB渲染*/
		RASTER_CUSTOMRENDER = 0x10,/**< 自定义专题，用于编写扩展专题*/
	};

	typedef struct _PIXEL_INFO {

		bool           Valid; 
		float         mp_pHist[256];
		float         Max;
		float         Min;
		float         Avg;
		float         Std;
		_PIXEL_INFO()
		{
			Valid = false;
		};
	}PIXEL_INFO;

	typedef struct _BANDLUTBOX
	{
		long         lEnhanceType;
		BYTE		  values[3][256];
	}BANDLUTBOX;

	enum MAP_EXTENT_MODE
	{
		EEM_AUTO,
		EEM_FIX_SCALE,	
		EEM_FIX_EXTENT
	};
}

#endif