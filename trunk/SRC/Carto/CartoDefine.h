//////////////////////////////////////////////////////////////////////
  // 版权(c) 2010-2020, 天地智绘
  // 作者：  hhzhao
  // 时间：  2010/11/18
  // 描述：  carto库的基础定义，包括导出宏、工程连接的基础头文件等
//////////////////////////////////////////////////////////////////////


#ifndef Carto_Define_H
#define Carto_Define_H

#if defined  CARTO_EXPORTS
#define CARTO_DLL __declspec(dllexport)
#else
#define CARTO_DLL __declspec(dllimport)
#pragma comment(lib,"Carto.lib")
#pragma message("Automatically linking with Carto.dll")

#endif


//carto 各种结构的定义
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
		OT_SIMPLERENDER = 0x01,/**< 简单专题*/
		OT_MIXSIMPLERENDER = 0x21,/**< 复合专题*/
		OT_SIZECLASSRENDER = 0x02,
		OT_WIDTHCLASSRENDER = 0x03,
		OT_SIZEGRADERENDER = 0x04,
		OT_UNIQUERENDER = 0x05, //唯一值
		OT_RANGERENDER = 0x06,  //范围
		OT_DOTDENSITYRENDER = 0x07,
		OT_PILLARRENDER = 0x08,
		OT_PIERENDER = 0x09,
		OT_TRIANGLERENDER = 0x10,
		OT_CHARTRENDER = 0x11,//图表专题图
		OT_CUSTOMRENDER = 0x12,/**< 自定义专题，用于编写扩展专题*/
	};

	/** 
	* 栅格渲染类型
	*/
	enum RASTER_RENDER_TYPE
	{
		OT_RASTER_RGBRENDER = 0x01,/**< RGB渲染*/

		OT_RASTER_CUSTOMRENDER = 0x10,/**< 自定义专题，用于编写扩展专题*/
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