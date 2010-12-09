//////////////////////////////////////////////////////////////////////
// ��Ȩ(c) 2010-2020, ����ǻ�
// ���ߣ�  hhzhao
// ʱ�䣺  2009/3/12
// ������  element�����������漰��ö�١���ȶ���
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
	EU_PIXEL = 0,//����
	EU_MILLIMETER = 1,//����
	EU_CENTIMETER = 10,//����
	EU_DECIMETER = 100,//����
};
enum ELEMENT_TYPE
{
	ET_ELEMENT_NONE = 0x01,		//��
	
	ET_MAP_FRAME_ELEMENT = 0x02,//��ͼͼԪ
	ET_GROUP_ELEMENT = 0x04,	//����ͼԪ

	ET_POINTELEMENT = 0x10,		//��
	ET_LINEELEMENT = 0x20,		//��
	ET_FILLELEMENT = 0x40,		//��
	ET_TEXT_ELEMENT = 0x80,		//����
	ET_MAP_SURROUND_ELEMENT = 0x0100,	//��ͼ����ͼԪ
	ET_EXTELEMENT = 0x0200,				//��չELEMENT

	//��
	ET_SIMPLE_POINT_ELEMENT = 0x11,		//�򵥵�
	
	//��
	ET_POLYLINE_ELEMENT = 0x21,			//����
	ET_CURVE_ELEMENT = 0x22,			//����
	ET_BEZIERCURVE_ELEMENT = 0x23,		//��������

	//��
	ET_FILL_RECTANGLE_ELEMENT = 0x41,	//����
	ET_FILL_POLYGON_ELEMENT = 0x42,		//�����
	ET_FILL_CIRCLE_ELEMENT = 0x43,		//Բ
	ET_FILL_ELLIPSE_ELEMENT = 0x44,		//��Բ
	
	//����
	ET_SIMPLE_TEXT_ELEMENT  = 0x81,		//����ͼԪ
	ET_CALLOUT_TEXT_ELEMENT = 0x82,		//callout text
	ET_PARAGRAPH_TEXT_ELEMENT = 0x83,	//������Ρ����Ρ�Բ����������

	//��ͼ����ͼԪ
	ET_MARKER_NORTH_ARROW = 0x0101,		//ָ����
	ET_ALTERNATING_SCALEBAR = 0x0102,	//���������
	ET_SCALELINE = 0x0103,				//���߱�����
	ET_LEGEND = 0x0104,					//ͼ��
	ET_MAP_TITLE = 0x0105,				//����
	ET_RELATIONDISTRICT_TABLE= 0x0106,	//�ӱ߱�
	ET_NEAT_LINE = 0x107,				//neatline
	ET_MAP_SURROUND_ELEMENT_END = 0x0199,//

	//��չͼԪ
	ET_EXT_PICTURE_ELEMENT = 0x0201		//ͼƬͼԪ

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
	EWHR_FIX_RATIO,		//�̶���߱�
	EWHR_FREE_RATIO		//���̶���߱�
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
	LDS_LABEL_LEGEND = 0,//��ǩͼ��
	LDS_LEGEND_LABEL = 1 //ͼ����ǩ
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
//��ע��Ա����ߵķ�λ
enum UnitPosition
{
	UP_AFTER_BAR,		//������֮��
	UP_BEFORE_BAR,		//������֮ǰ
	UP_ABOVE_BAR,		//������֮��
	UP_BELOW_BAR,		//������֮��
	UP_AFTER_LABELS	,	//���̶ֿ�֮��
	UP_BEFORE_LABELS	//���̶ֿ�֮ǰ	
};

//�̶���Ա����ߵķ�λ
enum NumPosition
{
	NP_ABOVE_BAR,		//������֮��
	NP_BELOW_BAR,		//������֮��
	NP_CENTER_BAR		//��������
};


//�̶���Ա����ߵķ�λ
enum MarkPosition
{
	MP_ABOVE_BAR,		//������֮��
	MP_BELOW_BAR,		//������֮��
	MP_CENTER_BAR		//�����ߴ��м�ᴩ
};


//����label�Ĺ���
enum LabelFrequency
{
	LF_NONE,	//��
	LF_ONE,		//�м��
	LF_MAIN_DIVISION,	//��Ҫ���ֶ�
	LF_ALL_DIVISIONS,	//���зֶ�
	LF_DIVISIONS_FIRST_MIDPOINT,	//���зֶΣ��Լ���һ�ֶε��е�
	LF_DIVISIONS_FIRST_SUBDIVISION	//���зֶΣ��Լ���һ���ӷֶ�
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

//ѡ����handle����
enum HANDLE_TYPE
{
	HT_NONE,	//��handle
	HT_ONE,		//һ��handle��calloutʱʹ�ã�
	HT_FOUR,	//�ĸ�handle
	HT_EIGHT	//�˸�handle
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
	long lPartIndex; //��־geometry�еĵڼ���
	long lHitLocation;//��־���е�״̬

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
#define CREATEEXTSYMBOL "�ı�����"
#define TEXTLENGTH      "TextLength"
#define TEXTSIZE        "TextSize"
#define TEXTSTRING      "TextString"
#define TEXTWIDTH       "TextWidth"
#define TEXTBOLD        "TextBold"
#define STRINGWIDTH     "StringWidth"

#endif