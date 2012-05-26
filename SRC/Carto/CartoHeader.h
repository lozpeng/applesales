//////////////////////////////////////////////////////////////////////
// ��Ȩ(c) 2010-2020, ����ǻ�
// ���ߣ�  hhzhao
// ʱ�䣺  2010/11/20
// ������  ���ֽṹ�Ķ���
//////////////////////////////////////////////////////////////////////
#ifndef _Carto_Header_H
#define _Carto_Header_H
namespace Carto
{
	/**
	*ͼ�����ͣ�ʸ��ͼ�㡢դ��ͼ�㡢TINͼ�㡢��עͼ��
	*/
	enum LAYER_TYPE
	{
		UnknownLayer,
		FeatureLayer,
		RasterLayer,
		TinLayer,
		GraphicLayer

	};

	enum LAYER_POSITION
	{
		LTBottom,
		LTNormal,
		LTTop
	};

	enum SELECT_OPTION
	{
		SELECT_REPLACE,
		SELECT_ADD,
		SELECT_SUBTRACT,
		SELECT_INTERSECT
	};

	/** 
	* ר������
	*/
	enum RENDER_TYPE
	{
		SIMPLERENDER = 0x01,/**< ��ר��*/
		MIXSIMPLERENDER = 0x21,/**< ����ר��*/
		SIZECLASSRENDER = 0x02,
		WIDTHCLASSRENDER = 0x03,
		SIZEGRADERENDER = 0x04,
		UNIQUERENDER = 0x05, //Ψһֵ
		RANGERENDER = 0x06,  //��Χ
		DOTDENSITYRENDER = 0x07,
		PILLARRENDER = 0x08,
		PIERENDER = 0x09,
		TRIANGLERENDER = 0x10,
		CHARTRENDER = 0x11,//ͼ��ר��ͼ
	};

	/** 
	* դ����Ⱦ����
	*/
	enum RASTER_RENDER_TYPE
	{
		RASTER_RGBRENDER = 0x01,/**< RGB��Ⱦ*/
		RASTER_CLASSIFY_COLORRAMP_RENDER=0x02,/**��ɫ�������Ⱦ*/
		RASTER_CUSTOMRENDER = 0x10,/**< �Զ���ר�⣬���ڱ�д��չר��*/
	};

	typedef struct _PIXEL_INFO {

		bool           Valid; 
		double         mp_pHist[256];
		double         Max;
		double         Min;
		double         Avg;
		double         Std;
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