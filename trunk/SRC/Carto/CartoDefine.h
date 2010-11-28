//////////////////////////////////////////////////////////////////////
  // ��Ȩ(c) 2010-2020, ����ǻ�
  // ���ߣ�  hhzhao
  // ʱ�䣺  2010/11/18
  // ������  carto��Ļ������壬���������ꡢ�������ӵĻ���ͷ�ļ���
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


//carto ���ֽṹ�Ķ���
namespace Carto
{
	/**
	*ͼ�����ͣ�ʸ��ͼ�㡢դ��ͼ�㡢TINͼ�㡢��עͼ��
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
	* ר������
	*/
	enum RENDER_TYPE
	{
		OT_SIMPLERENDER = 0x01,/**< ��ר��*/
		OT_MIXSIMPLERENDER = 0x21,/**< ����ר��*/
		OT_SIZECLASSRENDER = 0x02,
		OT_WIDTHCLASSRENDER = 0x03,
		OT_SIZEGRADERENDER = 0x04,
		OT_UNIQUERENDER = 0x05, //Ψһֵ
		OT_RANGERENDER = 0x06,  //��Χ
		OT_DOTDENSITYRENDER = 0x07,
		OT_PILLARRENDER = 0x08,
		OT_PIERENDER = 0x09,
		OT_TRIANGLERENDER = 0x10,
		OT_CHARTRENDER = 0x11,//ͼ��ר��ͼ
		OT_CUSTOMRENDER = 0x12,/**< �Զ���ר�⣬���ڱ�д��չר��*/
	};

	/** 
	* դ����Ⱦ����
	*/
	enum RASTER_RENDER_TYPE
	{
		OT_RASTER_RGBRENDER = 0x01,/**< RGB��Ⱦ*/

		OT_RASTER_CUSTOMRENDER = 0x10,/**< �Զ���ר�⣬���ڱ�д��չר��*/
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