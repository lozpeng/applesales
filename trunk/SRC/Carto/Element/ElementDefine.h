//////////////////////////////////////////////////////////////////////
// 版权(c) 2010-2020, 天地智绘
// 作者：  hhzhao
// 时间：  2009/3/12
// 描述：  element对象类中所涉及的枚举、宏等定义
//////////////////////////////////////////////////////////////////////


#ifndef _ELEMENT_DEFINE
#define	_ELEMENT_DEFINE

#define PI 3.1415926
namespace Element{


enum DRAW_SCALEBAR_STYLE
{
	DSS_SIMPLE,
	DSS_SYMBOL,
};
enum ELEMENT_UNIT
{
	EU_PIXEL = 0,//像素
	EU_MILLIMETER = 1,//毫米
	EU_CENTIMETER = 10,//厘米
	EU_DECIMETER = 100,//分米
};
enum ELEMENT_TYPE
{
	ET_ELEMENT_NONE = 0x01,		//空
	
	ET_MAP_FRAME_ELEMENT = 0x02,//地图图元
	ET_GROUP_ELEMENT = 0x04,	//成组图元

	ET_POINTELEMENT = 0x10,		//点
	ET_LINEELEMENT = 0x20,		//线
	ET_FILLELEMENT = 0x40,		//面
	ET_TEXT_ELEMENT = 0x80,		//文字
	ET_MAP_SURROUND_ELEMENT = 0x0100,	//地图附属图元
	ET_EXTELEMENT = 0x0200,				//扩展ELEMENT

	//点
	ET_SIMPLE_POINT_ELEMENT = 0x11,		//简单点
	
	//线
	ET_POLYLINE_ELEMENT = 0x21,			//折线
	ET_CURVE_ELEMENT = 0x22,			//曲线
	ET_BEZIERCURVE_ELEMENT = 0x23,		//贝氏曲线

	//面
	ET_FILL_RECTANGLE_ELEMENT = 0x41,	//矩形
	ET_FILL_POLYGON_ELEMENT = 0x42,		//多边形
	ET_FILL_CIRCLE_ELEMENT = 0x43,		//圆
	ET_FILL_ELLIPSE_ELEMENT = 0x44,		//椭圆
	
	//文字
	ET_SIMPLE_TEXT_ELEMENT  = 0x81,		//简单字图元
	ET_CALLOUT_TEXT_ELEMENT = 0x82,		//callout text
	ET_PARAGRAPH_TEXT_ELEMENT = 0x83,	//带多边形、矩形、圆等外框的文字

	//地图附属图元
	ET_MARKER_NORTH_ARROW = 0x0101,		//指北针
	ET_ALTERNATING_SCALEBAR = 0x0102,	//交替比例尺
	ET_SCALELINE = 0x0103,				//单线比例尺
	ET_LEGEND = 0x0104,					//图例
	ET_MAP_TITLE = 0x0105,				//标题
	ET_RELATIONDISTRICT_TABLE= 0x0106,	//接边表
	ET_NEAT_LINE = 0x107,				//neatline
	ET_MAP_SURROUND_ELEMENT_END = 0x0199,//

	//扩展图元
	ET_EXT_PICTURE_ELEMENT = 0x0201		//图片图元

};

enum ELEMENT_ANCHOR_POS
{
	EAP_LEFT_TOP,
	EAP_CENTER_TOP,
	EAP_RIGHT_TOP,
	EAP_LEFT_CENTER,
	EAP_CENTER_CENTER,
	EAP_RIGHT_CENTER,
	EAP_LEFT_BOTTOM,
	EAP_CENTER_BOTTOM,
	EAP_RIGHT_BOTTOM
};

enum ELEMENT_WIDTH_HEIGHT_RATIO
{
	EWHR_FIX_RATIO,		//固定宽高比
	EWHR_FREE_RATIO		//不固定宽高比
};

enum SCALEBAR_UNIT
{
	SU_MILLIMETER,
	SU_CENTIMETER,
	SU_DECIMETER,
	SU_METER,
	SU_KILOMETRES
};
enum LEGEND_DRAW_STYLE
{
	LDS_LABEL_LEGEND = 0,//标签图例
	LDS_LEGEND_LABEL = 1 //图例标签
};

enum TITLE_DRAW_STYLE
{
	TDS_LEFT,
	TDS_CENTER,
	TDS_RIGHT	
};
enum DRAW_STYLE
{
	DS_NULL,

	DS_BORDER,

	DS_BACKGROUND,

	DS_SHADOW,

	DS_BORDER_BACKGROUND,

	DS_BORDER_SHADOW,

	DS_BACKGROUND_SHADOW,

	DS_ALL

};

enum ELEMENT_DRAW_MODE
{
	EDM_NORMAL,
	EDM_DRAFT,
	EDM_PRINT,
};

enum ELEMENT_EDIT_MODE
{
	EEM_NO_EDIT,
	EEM_ONDRAW,	
	EEM_SELECT,
	EEM_EDIT_VERTIX,
	EEM_MOVE

};

/////scalebar/////////////////////////////////////////////////////////////////////
//标注相对比例尺的方位
enum UnitPosition
{
	UP_AFTER_BAR,		//比例尺之后
	UP_BEFORE_BAR,		//比例尺之前
	UP_ABOVE_BAR,		//比例尺之上
	UP_BELOW_BAR,		//比例尺之下
	UP_AFTER_LABELS	,	//数字刻度之后
	UP_BEFORE_LABELS	//数字刻度之前	
};

//刻度相对比例尺的方位
enum NumPosition
{
	NP_ABOVE_BAR,		//比例尺之上
	NP_BELOW_BAR,		//比例尺之下
	NP_CENTER_BAR		//比例尺中
};


//刻度相对比例尺的方位
enum MarkPosition
{
	MP_ABOVE_BAR,		//比例尺之上
	MP_BELOW_BAR,		//比例尺之下
	MP_CENTER_BAR		//比例尺从中间横穿
};


//绘制label的规则
enum LabelFrequency
{
	LF_NONE,	//无
	LF_ONE,		//中间点
	LF_MAIN_DIVISION,	//主要主分段
	LF_ALL_DIVISIONS,	//所有分段
	LF_DIVISIONS_FIRST_MIDPOINT,	//所有分段，以及第一分段的中点
	LF_DIVISIONS_FIRST_SUBDIVISION	//所有分段，以及第一个子分段
};



////legend item//////////////////////////////////////////////////////////////////////
enum LegendItemStyle
{
	LIS_H_SYM_DES,
	LIS_H_SYM_LAYERNAME
};


enum LegendItemArrangement
{
	LIA_PatchLabelDescription,
	LIA_PatchDescricptionLabel,
	LIA_LabelPatchDescription,
	LIA_LabelDescriptionPatch,
	LIA_DescriptionPatchLabel,
	LIA_DescriptionLabelPatch
};

//选择框的handle类型
enum HANDLE_TYPE
{
	HT_NONE,	//无handle
	HT_ONE,		//一个handle（callout时使用）
	HT_FOUR,	//四个handle
	HT_EIGHT	//八个handle
};

enum HIT_HANDLE
{
	HH_HIT_NONE,
	HH_HIT_INTERIOR,
	HH_HIT_MINX_MINY,
	HH_HIT_MIDX_MINY,
	HH_HIT_MAXX_MINY,
	HH_HIT_MAXX_MIDY,
	HH_HIT_MAXX_MAXY,
	HH_HIT_MIDX_MAXY,
	HH_HIT_MINX_MAXY,
	HH_HIT_MINX_MIDY,
	HH_HIT_ONE
};

enum HIT_MODE
{
	HH_HIT_GEOMETRY,
	HH_HIT_HANDLE,
	HH_HIT_VERTIX,
};

typedef struct HitTestResult
{
	long lPartIndex; //标志geometry中的第几个
	long lHitLocation;//标志击中的状态

	HitTestResult(){lPartIndex =0; lHitLocation = -1; };

}HIT_TEST_RES;

typedef enum OP_TYPE
{
	OPT_ADD,
	OPT_REMOVE,
	OPT_EDIT_PROPERTY,
	OPT_GROUP,
	OPT_UNGROUP,
	OPT_MOVE_UP,
	OPT_MOVE_DOWN,
	OPT_MOVE_TOP,
	OPT_MOVE_BOTTOM

};

typedef struct PageInfo
{
	BOOL bStandardPage;
	std::string name;
	double width;
	double height;

	PageInfo(){bStandardPage = TRUE;name = ""; width = 0; height = 0;};

}PAGE_INFO;


}
#define CREATEEXTSYMBOL "文本符号"
#define TEXTLENGTH      "TextLength"
#define TEXTSIZE        "TextSize"
#define TEXTSTRING      "TextString"
#define TEXTWIDTH       "TextWidth"
#define TEXTBOLD        "TextBold"
#define STRINGWIDTH     "StringWidth"

#endif