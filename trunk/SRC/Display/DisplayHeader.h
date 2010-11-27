//////////////////////////////////////////////////////////////////////
// 版权(c) 2010-2020, 天地智绘
// 作者：  9527
// 时间：  2008/11/27
// 描述：  基本定义
//////////////////////////////////////////////////////////////////////

#ifndef _Display_Header_h
#define _Display_Header_h

#define SetNoColor 0xff000000
#define SetHasColor 0xfe000000
#define CheckNoColor(rgb)		LOBYTE((rgb>>24))
#define IS_WIN30_DIB(lpbi)  ((*(unsigned long*)(lpbi)) == sizeof(BITMAPINFOHEADER))
#define VERSION 0x300		//调色板版本
#define WIDTHBYTES(bits)    (((bits) + 31) / 32 * 4) 

//一次显示的最大图形数目
#define  MAX_DISPLAY_SHAPE 10000

/** 
* 显示句柄
*/
typedef void* DISPLAY_HANDLE;

/** 
* 符号单位样式枚举: .
*
* 像素、毫米、厘米、分米
*/
//enum SYS_UNIT_TYPE
//{
//	otSystem::SYS_UNIT_PIXEL = 0,
//	otSystem::SYS_UNIT_MILLIMETER = 1,
//	otSystem::SYS_UNIT_CENTIMETER = 10,
//	otSystem::SYS_UNIT_DECIMETER = 100,
//	OT_POINT	=200
//};

/** 
* 简单笔的样式枚举: .
* 
* 实线笔、虚线笔、点线笔、短线-点线笔、短线-点-点笔、无
*/
enum SIMLINE_STYLE
{
	OT_SOLID		=	0,
	OT_DASH			=	1,
	OT_DOT			=	2,
	OT_DASHDOT		=	3,
	OT_DASHDOTDOT	=	4,
	OT_NULL			=	5,
	OT_INSIDEFRAME	=	6
};

/** 
* 高级笔的样式枚举: .
* 
* 实线笔、虚线笔、点线笔、短线-点线笔、短线-点-点线笔、无、用户自定义线笔
*/
enum EXTLINE_STYLE
{
	OT_EXT_SOLID		=	0,
	OT_EXT_DASH			=	1,
	OT_EXT_DOT			=	2,
	OT_EXT_DASHDOT		=	3,
	OT_EXT_DASHDOTDOT	=	4,
	OT_EXT_NULL			=	5,
	OT_EXT_INSIDEFRAME	=	6,
	OT_EXT_USERSTYLE	=	7,
	OT_EXT_ALTERNATE	=	8
};

/** 
* 高级笔的结合类型(化妆笔与几何笔设定)（化妆笔时，笔宽必须设为1）
*/
enum EXTLINE_COMBIN_TYPE
{
	OT_EXT_COSMETIC		=	0x00000000,
	OT_EXT_GEOMETRIC	=	0x00010000
};

/** 
* 高级笔的线头枚举(仅在几何笔时可用): .
*
* 圆头、方头、平头
*/
enum EXTLINE_END_CAP
{
	OT_EXT_ENDCAP_ROUND		=	0x00000000,
	OT_EXT_ENDCAP_SQUARE	=	0x00000100,
	OT_EXT_ENDCAP_FLAT		=	0x00000200
};

/** 
* 高级笔的线连接枚举（仅在几何笔时可用）: .
*
* 圆接、斜接、平切
*/
enum EXTLINE_JOIN
{
	OT_EXT_JOIN_ROUND	=	0x00000000,
	OT_EXT_JOIN_BEVEL	=	0x00001000,
	OT_EXT_JOIN_MITER	=	0x00002000
};

/** 
* 笔刷的样式枚举:固体刷、阴影刷: .
*/
enum LOGBRUSH_STYLE
{
	OT_BS_SOLID		=	0,
	OT_BS_HATCHED	=	2
};

/** 
* 笔刷的线型枚举: .
*
* 水平刷、垂直刷、从左到右向下45度刷、从左到右向上45度刷、十字十字线刷、交叉线刷
*/
enum LOGBRUSH_HATCH
{
	OT_HS_HORIZONTAL	=	0,	/* ----- */	//Horizontal hatch 
	OT_HS_VERTICAL		=	1,	/* ||||| */	//Vertical hatch 
	OT_HS_FDIAGONAL		=	2,	/* \\\\\ */	//A 45-degree downward, left-to-right hatch 
	OT_HS_BDIAGONAL		=	3,	/* ///// */	//A 45-degree upward, left-to-right hatch 
	OT_HS_CROSS			=	4,	/* +++++ */	//Horizontal and vertical cross-hatch 
	OT_HS_DIAGCROSS		=	5	/* xxxxx */	//45-degree crosshatch 
};

/** 
* 箭头方向的类型枚举: .
* 
* 无方向、开始、结束、双方向箭头
*/
enum ARROW_DIRECTION
{
	OT_NOARROW		=	0,
	OT_ARROWBEGIN	=	1,
	OT_ARROWEND		=	2,
	OT_ARROWBOTH	=	3
};

/** 
* 简单符号的样式: .
*
* 不绘制、正方形、圆形、十字形、x形、菱形、自定义
*/
enum SIMPLE_MARKER_STYLE
{
	OT_SIMPLE_MARKER_NULL		=	0,
	OT_SIMPLE_MARKER_SQUARE	=	1,
	OT_SIMPLE_MARKER_CIRCLE	=	2,
	OT_SIMPLE_MARKER_CROSS	=	3,
	OT_SIMPLE_MARKER_X		=	4,
	OT_SIMPLE_MARKER_STAR		=	5,
	OT_SIMPLE_MARKER_DIAMOND	=	6,
	OT_SIMPLE_MARKER_CUSTOM   =   7
};

/**
* 背景模式选择：.
* 
* 透明、不透明
*/
enum BK_MODE
{
	OT_TRANSPARENT	=	1,
	OT_OPAQUE		=	2
};

/** 
* 显示对象类型: .
*
* 文字、点、线、面、栅格
*/
typedef enum DISOBJTYPE
{
	Dis_Text,
	Dis_Point,
	Dis_Line,
	Dis_Polygon,
	Dis_ArcPolygon, //带有弧段的多边形
	Dis_Rect,
	Dis_Circle,
	Dis_Ellipse,
	Dis_Bezier,
	Dis_EndPoint,
	Dis_Raster,
	Dis_Bound
}DIS_OBJ_TYPE;

/** 
* 显示弧段类型: .
*
*/
enum SEGMENT_TYPE
{
    ST_LINE,
	ST_CIRCULARARC,
	ST_ELLIPTICARC,
	ST_BEZIERCURVE
};

typedef struct DrawData
{
	void *pData;
}DRAW_DATA;

typedef struct IntPoint
{
	long x,y;
}INT_POINT;



/**
* @alias 显示专用的点定义 
*/
typedef struct DisPoint
{
	
	DIS_OBJ_TYPE type;
	INT_POINT p;

	DisPoint(){type = Dis_Point;}

}DIS_POINT;



/**
* @alias 显示专用的线定义 
*/
typedef struct DisLine
{

	DIS_OBJ_TYPE type;
	unsigned long Count;
	INT_POINT ps[2];

	DisLine(){type = Dis_Line;}
}DIS_LINE;


/**
* @alias 显示专用的面定义 
*/
typedef struct DisPolygon
{
	DIS_OBJ_TYPE type;
	unsigned long Count;
	unsigned long RingCount[1];

	// INTPOINT 
	INT_POINT* GetPointAdr()
	{
		return (INT_POINT*)(((unsigned char*)this) + sizeof(long)*(Count+1) + sizeof(DIS_OBJ_TYPE) );
	}

	DisPolygon(){type = Dis_Polygon;};

}DIS_POLYGON;

typedef struct DisBound
{
	DIS_OBJ_TYPE type;


	double left,right,top,bottom;


	DisBound(){type = Dis_Bound;};

	double Height(){return abs(bottom-top);}
	double Width(){return abs(right-left);}

	RECT GetRect()
	{
		RECT rect;
		rect.left = (long)(left+0.5);
		rect.right = (long)(right+0.5);
		rect.top = (long)(top+0.5);
		rect.bottom = (long)(bottom+0.5);

		return rect;
	}

}DIS_BOUND;

/**
* @alias 显示专用的矩形定义 
*/
typedef struct DisRect
{
	DIS_OBJ_TYPE type;


	long left,right,top,bottom;


	DisRect(){type = Dis_Rect;};
	DisRect(RECT rct)
	{
		type = Dis_Rect;
		left = rct.left;
		right = rct.right;
		top = rct.top;
		bottom = rct.bottom;
	}

	long Height(){return abs(bottom-top);}
	long Width(){return abs(right-left);}

}DIS_RECT;



/**
* @alias 显示专用的圆形定义 
*/
typedef struct DisCircle
{
	DIS_OBJ_TYPE type;

	INT_POINT center;
	long   Radio;
	DisCircle()
	{
		type = Dis_Circle;
		Radio = 0;
	}
}DIS_CIRCLE,DIS_SIMPLE_MARKER;


/**
* @alias 显示专用的椭圆定义 
*/
typedef struct DisEllipse
{
	DIS_OBJ_TYPE type;

	//外接矩形的四个角点
	long left,right,top,bottom;

	DisEllipse(){type = Dis_Ellipse;};

	long Width() const{return abs(right -left);}

	long Height() const{return abs(bottom-top);}
}DIS_ELLIPSE;



/**
* @alias 显示专用的Bezier Spline定义 
*/

typedef struct DisBezier
{
	DIS_OBJ_TYPE type;
	unsigned long Count;
	INT_POINT ps[2];

	DisBezier(){type = Dis_Bezier;};


}DIS_BEZIER;

/**
* @alias 显示专用弧段定义 
*/
struct DIS_SEGMENT
{

	SEGMENT_TYPE type; //弧段类型
	//如果是线段，前两个点表示起点，终点
	//贝塞尔曲线表示四个控制点
	//弧段表示起始终止点
	INT_POINT    points[4];
	DisRect      bound; //如果是弧段表示它所在椭圆或圆的边界矩形
	short direction; //弧段方向,0表示顺时针，1表示逆时针
};


/**
* @alias 显示专用的带有弧段的面定义 
*/
typedef struct DisArcPolygon
{
	DIS_OBJ_TYPE type;
	long RingCount;
	long* pRingIndex; //每个环的弧段数目
	long SegmentCount;
	DIS_SEGMENT* pSegments;

	DisArcPolygon(){type = Dis_ArcPolygon;};

}DIS_ARCPOLYGON;


/**
* @alias 显示专用的饼形定义 
*/
typedef struct DisEndPoint
{
	DIS_OBJ_TYPE type;

	float xRadial1;
	float yRadial1;
	float xRadial2;
	float yRadial2;
	
	DisEndPoint(){type = Dis_EndPoint;};

}DIS_ENDPOINT;




/**
* @alias 显示使用的字体参数定义 
*/
typedef struct DisFont
{
	float lfHeight; 
	float lfWidth; 
	long lfEscapement; 
	long lfOrientation; 
	long lfWeight; 
	unsigned char lfItalic; 
	unsigned char lfUnderline; 
	unsigned char lfStrikeOut; 
	/*unsigned char*/int lfCharSet; 
	unsigned char lfOutPrecision; 
	unsigned char lfClipPrecision; 
	unsigned char lfQuality; 
	unsigned char lfPitchAndFamily; 
	char lfFaceName[32];
}DIS_FONT;

typedef struct DisText
{
	DIS_OBJ_TYPE type;
	DIS_RECT textPos;
	int nCharCount;
	char* cText;

	DisText(){type = Dis_Text;};
}DIS_TEXT;

/**
* @alias 显示八叉树节点定义
*/
typedef struct _NODE 
{
	bool bIsLeaf;               // 是否有子节点
	long nPixelCount;           // 共有几个像素
	long nRedSum;               // 红色总数
	long nGreenSum;             // 绿色总数
	long nBlueSum;              // 蓝色总数
	struct _NODE* pChild[8];    // 指向一个子节点
	struct _NODE* pNext;        // 下一个节点

} NODE;

/**
* @alias 显示颜色结构
*/
typedef struct _PALENTRY{ 
	unsigned char peRed; 				//红
	unsigned char peGreen; 				//绿
	unsigned char peBlue; 				//蓝
	unsigned char peFlags; 					
} PALENTRY;

/**
* @alias 图片信息结构
*/
typedef struct _IMAGE_INFO
{
	long lWidth;
	long lHeight;
	long lBitCount;
	void ** vDataColor;
} IMAGE_INFO;

//创建文字对象
#define CreateDisplayText(DIS_TEXT_obj, txtCount) DIS_TEXT_obj=(DIS_TEXT*)malloc( sizeof(DIS_TEXT) + (txtCount+1) * sizeof(char)); memset(DIS_TEXT_obj , 0 ,sizeof(DIS_TEXT) + (txtCount+1) * sizeof(char)) ; DIS_TEXT_obj->type = Dis_Text; DIS_TEXT_obj->nCharCount = txtCount; DIS_TEXT_obj->cText = (char*)((unsigned char*)DIS_TEXT_obj +sizeof(DIS_TEXT));

//创建矩形对象
#define CreateDisplayRect(DIS_RECT_obj) DIS_RECT_obj=(DIS_RECT*)malloc( sizeof(DIS_RECT)); memset(DIS_RECT_obj , 0 ,sizeof(DIS_RECT)) ; DIS_RECT_obj->type = Dis_Rect

//创建点对象
#define CreateDisplayPoint(DIS_POINT_obj) DIS_POINT_obj=(DIS_POINT*)malloc( sizeof(DIS_POINT) ); memset(DIS_POINT_obj , 0 ,sizeof(DIS_POINT)) ; DIS_POINT_obj->type = Dis_Point

// 创建线对象
#define CreateDisplayLine(DIS_LINE_obj , ptCount) DIS_LINE_obj = (DIS_LINE  *)malloc( sizeof(DIS_LINE) + ( ptCount - 2 ) * sizeof(INT_POINT) ); \
	memset(DIS_LINE_obj , 0 , sizeof(DIS_LINE) + ( ptCount - 2 ) * sizeof(INT_POINT)) ; DIS_LINE_obj->type = Dis_Line; DIS_LINE_obj->Count = ptCount

// 创建Bezier对象
#define CreateDisplayBezier(DIS_BEZIER_obj , ptCount) DIS_BEZIER_obj = (DIS_BEZIER  *)malloc( sizeof(DIS_BEZIER) + ( ptCount - 2 ) * sizeof(INT_POINT) ); \
	memset(DIS_BEZIER_obj , 0 , sizeof(DIS_BEZIER) + ( ptCount - 2 ) * sizeof(INT_POINT)) ; DIS_BEZIER_obj->type = Dis_Bezier; DIS_BEZIER_obj->Count = ptCount

//创建多边形对象
#define CreateDisplayPolygon( DIS_POLYGON_obj , RingCount , ptCount ) \
	DIS_POLYGON_obj = (DIS_POLYGON*)malloc( sizeof(DIS_POLYGON) + sizeof(unsigned long) * (RingCount - 1) + sizeof(INT_POINT) * ptCount ); \
	memset(DIS_POLYGON_obj , 0 , sizeof(DIS_POLYGON) + sizeof(unsigned long) * (RingCount - 1) + sizeof(INT_POINT) * ptCount) ; DIS_POLYGON_obj->type = Dis_Polygon ; DIS_POLYGON_obj->Count = RingCount ; 

//创建弧段多边形对象
#define CreateDisplayArcPolygon( DIS_ARCPOLYGON_obj , RingNum , SegmentNum ) \
	DIS_ARCPOLYGON_obj = (DIS_ARCPOLYGON*)malloc( sizeof(DIS_ARCPOLYGON) + sizeof(long) *RingNum + sizeof(DIS_SEGMENT) * SegmentNum ); \
	memset(DIS_ARCPOLYGON_obj , 0 , sizeof(DIS_ARCPOLYGON) +sizeof(long) *RingNum + sizeof(DIS_SEGMENT) * SegmentNum) ; \
	DIS_ARCPOLYGON_obj->type = Dis_ArcPolygon ; DIS_ARCPOLYGON_obj->RingCount = RingNum; DIS_ARCPOLYGON_obj->SegmentCount = SegmentNum ; \
    DIS_ARCPOLYGON_obj->pRingIndex =(long*)(((unsigned char*)DIS_ARCPOLYGON_obj) + sizeof(DIS_ARCPOLYGON) );\
    DIS_ARCPOLYGON_obj->pSegments =(DIS_SEGMENT*)(((unsigned char*)DIS_ARCPOLYGON_obj) + sizeof(DIS_ARCPOLYGON)+ sizeof(long) *RingNum);


//创建圆形对象
#define CreateDisplayCircle(DIS_CIRCLE_obj) DIS_CIRCLE_obj=(DIS_CIRCLE*)malloc( sizeof(DIS_CIRCLE)); memset(DIS_CIRCLE_obj , 0 ,sizeof(DIS_CIRCLE)) ; DIS_CIRCLE_obj->type = Dis_Circle;

//创建椭圆形对象
#define CreateDisplayEllipse(DIS_ELLIPSE_obj) DIS_ELLIPSE_obj=(DIS_ELLIPSE*)malloc( sizeof(DIS_ELLIPSE)); memset(DIS_ELLIPSE_obj , 0 ,sizeof(DIS_ELLIPSE)) ; DIS_ELLIPSE_obj->type = Dis_Ellipse;

//创建Bound对象
#define CreateDisplayBound(DIS_BOUND_obj) DIS_BOUND_obj = (DIS_BOUND*)malloc( sizeof(DIS_BOUND)); memset(DIS_BOUND_obj , 0 ,sizeof(DIS_BOUND)) ; DIS_BOUND_obj->type = Dis_Bound;
// 释放显示对象
#define FreeDisplayObj(DIS_obj) free(DIS_obj)

/**
* @alias 画笔参数定义
*/
typedef struct LineStyle
{
	unsigned long lColor;	/** 普通笔，需要此参数设置颜色；扩展笔时，此参数附给LOGBRUSH结构的lbcolor参数，默认红色*/
	unsigned long lWidth;	/** 普通笔与扩展笔都需要此参数设置宽度。默认为1*/
	bool bExt;				/** 判断所传的参数适用于普通笔还是扩展笔，默认为普通笔*/
	SIMLINE_STYLE eStyle;	/** 普通笔时，需要的参数笔样式*/
	EXTLINE_STYLE eExtStyle;/** 扩展笔时，需要的参数笔样式组合*/
	long lbHatch;			/** 扩展笔时，需要的绘线样式，例如十字线，斜45度线。默认水平线*/ 
	long lbStyle;			//扩展笔时，需要的笔刷样式，默认固体刷
	unsigned long dwStyleCount;	/** 扩展笔时，根据需要设置破折号样式数组的个数，默认为0*/
	unsigned long *lpStyle;	/** 设置破折号样式数组，默认为0*/

}LINE_STYLE;

/**
* @alias 调色板颜色定义
*/
typedef struct ImageColor
{
	unsigned long ulDataLens;	/** 数据长度*/
	unsigned long ulData[1];	/** 实际数据*/

} IMAGE_COLOR;


/**
* @alias 画刷参数定义
*/
typedef struct BrushStyle
{
	COLORREF lColor;	/** 画刷颜色默认为红色*/
	LOGBRUSH_STYLE Style;
	LOGBRUSH_HATCH Hatch;

}BRUSH_STYLE;

/** 
* 符号类型
*/
typedef enum SymbolType
{

	OT_NONE_SYMBOL = 0x01, //空符号
	OT_MARKER_SYMBOL = 0x10,
	OT_LINE_SYMBOL = 0x20,
	OT_FILL_SYMBOL = 0x40,
	OT_EXT_SYMBOL = 0x80, 
	OT_COMPLEX_SYMBOL = 0x0100,
	OT_TEXT_SYMBOL = 0x0200,//文字符号



	OT_SIMPLE_MARKER_SYMBOL = 0x11,	
	OT_CHAR_MARKER_SYMBOL   = 0x12,
	OT_ARROW_MARKER_SYMBOL  = 0x13,
	OT_PIC_MARKER_SYMBOL    = 0x14,

	OT_SIMPLE_LINE_SYMBOL = 0x21,
	OT_ADV_LINE_SYMBOL	  = 0x22,
	OT_MARKER_LINE_SYMBOL	  = 0x23,
	OT_HASH_LINE_SYMBOL   = 0x24,		
	OT_PIC_LINE_SYMBOL    = 0x25,


	OT_SIMPLE_FILL_SYMBOL = 0x41,
	OT_MARKER_FILL_SYMBOL	  = 0x42,
	OT_LINE_FILL_SYMBOL   = 0x43,
	OT_PIC_FILL_SYMBOL    =	0x44,
	OT_GRADIENT_FILL_SYMBOL    =	0x45,
	
	OT_COMPLEX_MARKER_SYMBOL= OT_COMPLEX_SYMBOL | OT_MARKER_SYMBOL,
	OT_COMPLEX_LINE_SYMBOL= OT_COMPLEX_SYMBOL | OT_LINE_SYMBOL,
	OT_COMPLEX_FILL_SYMBOL=	OT_COMPLEX_SYMBOL | OT_FILL_SYMBOL,

	OT_EXT_MARKER_SYMBOL	  = OT_EXT_SYMBOL | OT_MARKER_SYMBOL,
	OT_EXT_LINE_SYMBOL	  = OT_EXT_SYMBOL | OT_LINE_SYMBOL,
	OT_EXT_FILL_SYMBOL	  = OT_EXT_SYMBOL | OT_FILL_SYMBOL,
	OT_EXT_ALL_SYMBOL	  = 0xf0,

	OT_RASTER_SYMBOL	  = 0x1000,
	OT_PICRASTER_SYMBOL	  = 0x1001,
	OT_COLORBOXRASTER_SYMBOL=0x1002,
	OT_BANDRASTER_SYMBOL	=0x1003,
	OT_FAKECOLOR_RASTER_SYMBOL = 0x1004,
	OT_DEM_REFLACTION_SYMBOL = 0x1005
}SYMBOL_TYPE;

/** 
* 符号类型
*/
typedef enum GradientType
{
	Gradient_Linear = 1,
	Gradient_Rectanglar = 2,
	Gradient_Circlar = 3
}GRANDIENT_FILL_TYPE;

typedef enum LineJointStyle
{
	LJSMiter  = 1,
	LJSRound  = 2,
	LJSBevel  = 3

}LINE_POINT_STYLE;

/** 
* 对齐样式:左对齐、右对齐、中心对齐
*/
typedef enum AlignType
{
	ATLeft	 = 1,
	ATRight  = 2,
	ATCenter = 3

}ALIGN_TYPE;

/** 
* 对象类型
*/
typedef enum ObjType
{
	OTNormal = 1,	/**　规则绘制对象*/
	OTCurve	 = 2,	/** 拟和线*/
	OTRect	 = 3	,	/** 矩形*/
	OTEllipse = 4,	/** 椭圆*/
	OTRoundRect	= 5,/** 圆角矩形*/
	OTArcCW	 = 6,	/** 顺时针椭圆弧*/
	OTArcCCW = 7,	/** 逆时针椭圆弧*/
	OTChord	 = 8,	/** 弓形*/
	OTPie	 = 9,	/** 扇形*/
	OTPath	 = 10,	/** 路径，部分之间是连续的，如果传入的不连续，会自动把数据连接起来。*/
	OTMultiObject = 11	/** 复合形状，对传入部分不做任何处理*/

}OBB_TYPE;

//CtoTextSymbol的样式宏设定
#define OT_DT_TOP						0x00000000
#define OT_DT_LEFT						0x00000000
#define OT_DT_CENTER					0x00000001
#define OT_DT_RIGHT						0x00000002
#define OT_DT_VCENTER					0x00000004
#define OT_DT_BOTTOM					0x00000008
#define OT_DT_WORDBREAK					0x00000010
#define OT_DT_SINGLELINE				0x00000020
#define OT_DT_EXPANDTABS				0x00000040
#define OT_DT_TABSTOP					0x00000080
#define OT_DT_NOCLIP					0x00000100
#define OT_DT_EXTERNALLEADING			0x00000200
#define OT_DT_CALCRECT					0x00000400
#define OT_DT_NOPREFIX					0x00000800
#define OT_DT_INTERNAL					0x00001000
#define OT_DT_EDITCONTROL				0x00002000
#define OT_DT_PATH_ELLIPSIS				0x00004000
#define OT_DT_END_ELLIPSIS				0x00008000
#define OT_DT_MODIFYSTRING				0x00010000
#define OT_DT_RTLREADING				0x00020000
#define OT_DT_WORD_ELLIPSIS				0x00040000
#define OT_DT_NOFULLWIDTHCHARBREAK		0x00080000
#define OT_DT_HIDEPREFIX				0x00100000
#define OT_DT_PREFIXONLY				0x00200000

//文本串输出位置
typedef enum TextPosType{
	OT_TXTPOS_LEFTTOP		=	0,
	OT_TXTPOS_CENTERTOP		=	1,
	OT_TXTPOS_RIGHTTOP		=	2,
	OT_TXTPOS_LEFTCENTER	=	3,
	OT_TXTPOS_CENTER		=	4,
	OT_TXTPOS_RIGHTCENTER	=	5,
	OT_TXTPOS_LEFTBOTTOM	=	6,
	OT_TXTPOS_CENTERBOTTOM	=	7,
	OT_TXTPOS_RIGHTBOTTOM	=	8
}TEXT_POS_TYPE;

typedef enum TextFillType
{
	OT_FILL_NULL=0,
	OT_FILL_RECT=1,
	OT_FILL_RECT_ROUND=2,
	OT_FILL_RECT_SHARP=3,
	OT_FILL_RECT_ROUND_SHARP=4
}TEXT_FILL_TYPE;

typedef enum TextMarkType
{
	OT_MARK_NULL=0,
	OT_MARK_DRAW=1
}TEXT_MARK_TYPE;

typedef enum TextLineType
{
	OT_LINE_NULL=0,
	OT_LINE_LEFT=1,
	OT_LINE_TOP=2,
	OT_LINE_RIGHT=3,
	OT_LINE_BOTTOM=4,
	OT_LINE_BOTH_V=5,//纵向2个
	OT_LINE_BOTH_H=6	//水平2个
}TEXT_LINE_TYPE;
/**
* 绘制内容
*/
typedef enum DrawContent
{
	//不显示
	drawNone = 0x00,
	//显示矢量要素、栅格
	drawGeography = 0x01,
	//显示选择
	drawGeoSelection = 0x02,
	//显示图元
	drawElement = 0x04,
	//临时编辑
	drawEdit = 0x08,
	//临时对象
	drawTempObj = 0x10,
	//全部显示
	drawAll = 0x1F

}DRAW_CONTENT;


enum LineSymbolLegendStyle
{
	LSLS_HORIZONTAL,
	LSLS_FLOWINGWATER,
	LSLS_INCLINE,
	LSLS_DECLINE,
	LSLS_ZIGZAG,
	LSLS_SCURVE,
	LSLS_CHEVRONDOWN,
	LSLS_CHEVRONUP,
	LSLS_ARC
};

enum FillSymbolLegendStyle
{
	FSLS_RECT,
	FSLS_ROUNDRECT,
	FSLS_ELIIPSE,
	FSLS_DIAMOND,
	FSLS_PARK,
	FSLS_URBANIZEDAREA,
	FSLS_WATERBODY,
	FSLS_NATUALAREA
};

enum MarkerSymbolLegendStyle
{
	MSLS_SIMPLE
};

static void RectExpandToInclude(DIS_RECT& rect, DIS_RECT other)
{
	rect.left = other.left<rect.left ? other.left:rect.left;

	rect.right = other.right>rect.right ? other.right:rect.right;

	rect.top = other.top<rect.top ? other.top:rect.top;

	rect.bottom = other.bottom>rect.bottom ? other.bottom:rect.bottom;
}

#endif //_Display_Header_h