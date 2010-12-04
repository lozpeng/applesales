//////////////////////////////////////////////////////////////////////
// ��Ȩ(c) 2010-2020, ����ǻ�
// ���ߣ�  9527
// ʱ�䣺  2008/11/27
// ������  ��������
//////////////////////////////////////////////////////////////////////

#ifndef _Display_Header_h
#define _Display_Header_h

#define SetNoColor 0xff000000
#define SetHasColor 0xfe000000
#define CheckNoColor(rgb)		LOBYTE((rgb>>24))
#define IS_WIN30_DIB(lpbi)  ((*(unsigned long*)(lpbi)) == sizeof(BITMAPINFOHEADER))
#define VERSION 0x300		//��ɫ��汾
#define WIDTHBYTES(bits)    (((bits) + 31) / 32 * 4) 

//һ����ʾ�����ͼ����Ŀ
#define  MAX_DISPLAY_SHAPE 10000

/** 
* ��ʾ���
*/
typedef void* DISPLAY_HANDLE;

/** 
* ���ŵ�λ��ʽö��: .
*
* ���ء����ס����ס�����
*/
//enum SYS_UNIT_TYPE
//{
//	otSystem::SYS_UNIT_PIXEL = 0,
//	otSystem::SYS_UNIT_MILLIMETER = 1,
//	otSystem::SYS_UNIT_CENTIMETER = 10,
//	otSystem::SYS_UNIT_DECIMETER = 100,
//	POINT	=200
//};

/** 
* �򵥱ʵ���ʽö��: .
* 
* ʵ�߱ʡ����߱ʡ����߱ʡ�����-���߱ʡ�����-��-��ʡ���
*/
enum SIMLINE_STYLE
{
	SOLID		=	0,
	DASH			=	1,
	DOT			=	2,
	DASHDOT		=	3,
	DASHDOTDOT	=	4,
	NONE	=	5,
	INSIDEFRAME	=	6
};

/** 
* �߼��ʵ���ʽö��: .
* 
* ʵ�߱ʡ����߱ʡ����߱ʡ�����-���߱ʡ�����-��-���߱ʡ��ޡ��û��Զ����߱�
*/
enum EXTLINE_STYLE
{
	EXT_SOLID		=	0,
	EXT_DASH			=	1,
	EXT_DOT			=	2,
	EXT_DASHDOT		=	3,
	EXT_DASHDOTDOT	=	4,
	EXT_NULL			=	5,
	EXT_INSIDEFRAME	=	6,
	EXT_USERSTYLE	=	7,
	EXT_ALTERNATE	=	8
};

/** 
* �߼��ʵĽ������(��ױ���뼸�α��趨)����ױ��ʱ���ʿ������Ϊ1��
*/
enum EXTLINE_COMBIN_TYPE
{
	EXT_COSMETIC		=	0x00000000,
	EXT_GEOMETRIC	=	0x00010000
};

/** 
* �߼��ʵ���ͷö��(���ڼ��α�ʱ����): .
*
* Բͷ����ͷ��ƽͷ
*/
enum EXTLINE_END_CAP
{
	EXT_ENDCAP_ROUND		=	0x00000000,
	EXT_ENDCAP_SQUARE	=	0x00000100,
	EXT_ENDCAP_FLAT		=	0x00000200
};

/** 
* �߼��ʵ�������ö�٣����ڼ��α�ʱ���ã�: .
*
* Բ�ӡ�б�ӡ�ƽ��
*/
enum EXTLINE_JOIN
{
	EXT_JOIN_ROUND	=	0x00000000,
	EXT_JOIN_BEVEL	=	0x00001000,
	EXT_JOIN_MITER	=	0x00002000
};

/** 
* ��ˢ����ʽö��:����ˢ����Ӱˢ: .
*/
enum LOGBRUSH_STYLE
{
	SOLID_BRUSH = 0,
	HATCH_BRUSH	=	2
};

/** 
* ��ˢ������ö��: .
*
* ˮƽˢ����ֱˢ������������45��ˢ������������45��ˢ��ʮ��ʮ����ˢ��������ˢ
*/
enum LOGBRUSH_HATCH
{
	HORIZONTAL	=	0,	/* ----- */	//Horizontal hatch 
	VERTICAL		=	1,	/* ||||| */	//Vertical hatch 
	FDIAGONAL		=	2,	/* \\\\\ */	//A 45-degree downward, left-to-right hatch 
	BDIAGONAL		=	3,	/* ///// */	//A 45-degree upward, left-to-right hatch 
	CROSS			=	4,	/* +++++ */	//Horizontal and vertical cross-hatch 
	DIAGCROSS		=	5,	/* xxxxx */	//45-degree crosshatch 
};

/** 
* ��ͷ���������ö��: .
* 
* �޷��򡢿�ʼ��������˫�����ͷ
*/
enum ARROW_DIRECTION
{
	NOARROW		=	0,
	ARROWBEGIN	=	1,
	ARROWEND		=	2,
	ARROWBOTH	=	3
};

/** 
* �򵥷��ŵ���ʽ: .
*
* �����ơ������Ρ�Բ�Ρ�ʮ���Ρ�x�Ρ����Ρ��Զ���
*/
enum SIMPLE_MARKER_STYLE
{
	SIMPLE_MARKER_NULL		=	0,
	SIMPLE_MARKER_SQUARE	=	1,
	SIMPLE_MARKER_CIRCLE	=	2,
	SIMPLE_MARKER_CROSS	=	3,
	SIMPLE_MARKER_X		=	4,
	SIMPLE_MARKER_STAR		=	5,
	SIMPLE_MARKER_DIAMOND	=	6,
	SIMPLE_MARKER_CUSTOM   =   7
};

/**
* ����ģʽѡ��.
* 
* ͸������͸��
*/
enum BK_MODE
{
	BK_TRANSPARENT	=	1,
	BK_OPAQUE		=	2
};

/** 
* ��ʾ��������: .
*
* ���֡��㡢�ߡ��桢դ��
*/
typedef enum DISOBJTYPE
{
	Dis_Text,
	Dis_Point,
	Dis_Line,
	Dis_Polygon,
	Dis_ArcPolygon, //���л��εĶ����
	Dis_Rect,
	Dis_Circle,
	Dis_Ellipse,
	Dis_Bezier,
	Dis_EndPoint,
	Dis_Raster,
	Dis_Bound
}DIS_OBJ_TYPE;

/** 
* ��ʾ��������: .
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
* @alias ��ʾר�õĵ㶨�� 
*/
typedef struct DisPoint
{
	
	DIS_OBJ_TYPE type;
	INT_POINT p;

	DisPoint(){type = Dis_Point;}

}DIS_POINT;



/**
* @alias ��ʾר�õ��߶��� 
*/
typedef struct DisLine
{

	DIS_OBJ_TYPE type;
	unsigned long Count;
	INT_POINT ps[2];

	DisLine(){type = Dis_Line;}
}DIS_LINE;


/**
* @alias ��ʾר�õ��涨�� 
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
* @alias ��ʾר�õľ��ζ��� 
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
* @alias ��ʾר�õ�Բ�ζ��� 
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
* @alias ��ʾר�õ���Բ���� 
*/
typedef struct DisEllipse
{
	DIS_OBJ_TYPE type;

	//��Ӿ��ε��ĸ��ǵ�
	long left,right,top,bottom;

	DisEllipse(){type = Dis_Ellipse;};

	long Width() const{return abs(right -left);}

	long Height() const{return abs(bottom-top);}
}DIS_ELLIPSE;



/**
* @alias ��ʾר�õ�Bezier Spline���� 
*/

typedef struct DisBezier
{
	DIS_OBJ_TYPE type;
	unsigned long Count;
	INT_POINT ps[2];

	DisBezier(){type = Dis_Bezier;};


}DIS_BEZIER;

/**
* @alias ��ʾר�û��ζ��� 
*/
struct DIS_SEGMENT
{

	SEGMENT_TYPE type; //��������
	//������߶Σ�ǰ�������ʾ��㣬�յ�
	//���������߱�ʾ�ĸ����Ƶ�
	//���α�ʾ��ʼ��ֹ��
	INT_POINT    points[4];
	DisRect      bound; //����ǻ��α�ʾ��������Բ��Բ�ı߽����
	short direction; //���η���,0��ʾ˳ʱ�룬1��ʾ��ʱ��
};


/**
* @alias ��ʾר�õĴ��л��ε��涨�� 
*/
typedef struct DisArcPolygon
{
	DIS_OBJ_TYPE type;
	long RingCount;
	long* pRingIndex; //ÿ�����Ļ�����Ŀ
	long SegmentCount;
	DIS_SEGMENT* pSegments;

	DisArcPolygon(){type = Dis_ArcPolygon;};

}DIS_ARCPOLYGON;


/**
* @alias ��ʾר�õı��ζ��� 
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
* @alias ��ʾʹ�õ������������ 
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
* @alias ��ʾ�˲����ڵ㶨��
*/
typedef struct _NODE 
{
	bool bIsLeaf;               // �Ƿ����ӽڵ�
	long nPixelCount;           // ���м�������
	long nRedSum;               // ��ɫ����
	long nGreenSum;             // ��ɫ����
	long nBlueSum;              // ��ɫ����
	struct _NODE* pChild[8];    // ָ��һ���ӽڵ�
	struct _NODE* pNext;        // ��һ���ڵ�

} NODE;

/**
* @alias ��ʾ��ɫ�ṹ
*/
typedef struct _PALENTRY{ 
	unsigned char peRed; 				//��
	unsigned char peGreen; 				//��
	unsigned char peBlue; 				//��
	unsigned char peFlags; 					
} PALENTRY;

/**
* @alias ͼƬ��Ϣ�ṹ
*/
typedef struct _IMAGE_INFO
{
	long lWidth;
	long lHeight;
	long lBitCount;
	void ** vDataColor;
} IMAGE_INFO;

//�������ֶ���
#define CreateDisplayText(DIS_TEXT_obj, txtCount) DIS_TEXT_obj=(DIS_TEXT*)malloc( sizeof(DIS_TEXT) + (txtCount+1) * sizeof(char)); memset(DIS_TEXT_obj , 0 ,sizeof(DIS_TEXT) + (txtCount+1) * sizeof(char)) ; DIS_TEXT_obj->type = Dis_Text; DIS_TEXT_obj->nCharCount = txtCount; DIS_TEXT_obj->cText = (char*)((unsigned char*)DIS_TEXT_obj +sizeof(DIS_TEXT));

//�������ζ���
#define CreateDisplayRect(DIS_RECT_obj) DIS_RECT_obj=(DIS_RECT*)malloc( sizeof(DIS_RECT)); memset(DIS_RECT_obj , 0 ,sizeof(DIS_RECT)) ; DIS_RECT_obj->type = Dis_Rect

//���������
#define CreateDisplayPoint(DIS_POINT_obj) DIS_POINT_obj=(DIS_POINT*)malloc( sizeof(DIS_POINT) ); memset(DIS_POINT_obj , 0 ,sizeof(DIS_POINT)) ; DIS_POINT_obj->type = Dis_Point

// �����߶���
#define CreateDisplayLine(DIS_LINE_obj , ptCount) DIS_LINE_obj = (DIS_LINE  *)malloc( sizeof(DIS_LINE) + ( ptCount - 2 ) * sizeof(INT_POINT) ); \
	memset(DIS_LINE_obj , 0 , sizeof(DIS_LINE) + ( ptCount - 2 ) * sizeof(INT_POINT)) ; DIS_LINE_obj->type = Dis_Line; DIS_LINE_obj->Count = ptCount

// ����Bezier����
#define CreateDisplayBezier(DIS_BEZIER_obj , ptCount) DIS_BEZIER_obj = (DIS_BEZIER  *)malloc( sizeof(DIS_BEZIER) + ( ptCount - 2 ) * sizeof(INT_POINT) ); \
	memset(DIS_BEZIER_obj , 0 , sizeof(DIS_BEZIER) + ( ptCount - 2 ) * sizeof(INT_POINT)) ; DIS_BEZIER_obj->type = Dis_Bezier; DIS_BEZIER_obj->Count = ptCount

//��������ζ���
#define CreateDisplayPolygon( DIS_POLYGON_obj , RingCount , ptCount ) \
	DIS_POLYGON_obj = (DIS_POLYGON*)malloc( sizeof(DIS_POLYGON) + sizeof(unsigned long) * (RingCount - 1) + sizeof(INT_POINT) * ptCount ); \
	memset(DIS_POLYGON_obj , 0 , sizeof(DIS_POLYGON) + sizeof(unsigned long) * (RingCount - 1) + sizeof(INT_POINT) * ptCount) ; DIS_POLYGON_obj->type = Dis_Polygon ; DIS_POLYGON_obj->Count = RingCount ; 

//�������ζ���ζ���
#define CreateDisplayArcPolygon( DIS_ARCPOLYGON_obj , RingNum , SegmentNum ) \
	DIS_ARCPOLYGON_obj = (DIS_ARCPOLYGON*)malloc( sizeof(DIS_ARCPOLYGON) + sizeof(long) *RingNum + sizeof(DIS_SEGMENT) * SegmentNum ); \
	memset(DIS_ARCPOLYGON_obj , 0 , sizeof(DIS_ARCPOLYGON) +sizeof(long) *RingNum + sizeof(DIS_SEGMENT) * SegmentNum) ; \
	DIS_ARCPOLYGON_obj->type = Dis_ArcPolygon ; DIS_ARCPOLYGON_obj->RingCount = RingNum; DIS_ARCPOLYGON_obj->SegmentCount = SegmentNum ; \
    DIS_ARCPOLYGON_obj->pRingIndex =(long*)(((unsigned char*)DIS_ARCPOLYGON_obj) + sizeof(DIS_ARCPOLYGON) );\
    DIS_ARCPOLYGON_obj->pSegments =(DIS_SEGMENT*)(((unsigned char*)DIS_ARCPOLYGON_obj) + sizeof(DIS_ARCPOLYGON)+ sizeof(long) *RingNum);


//����Բ�ζ���
#define CreateDisplayCircle(DIS_CIRCLE_obj) DIS_CIRCLE_obj=(DIS_CIRCLE*)malloc( sizeof(DIS_CIRCLE)); memset(DIS_CIRCLE_obj , 0 ,sizeof(DIS_CIRCLE)) ; DIS_CIRCLE_obj->type = Dis_Circle;

//������Բ�ζ���
#define CreateDisplayEllipse(DIS_ELLIPSE_obj) DIS_ELLIPSE_obj=(DIS_ELLIPSE*)malloc( sizeof(DIS_ELLIPSE)); memset(DIS_ELLIPSE_obj , 0 ,sizeof(DIS_ELLIPSE)) ; DIS_ELLIPSE_obj->type = Dis_Ellipse;

//����Bound����
#define CreateDisplayBound(DIS_BOUND_obj) DIS_BOUND_obj = (DIS_BOUND*)malloc( sizeof(DIS_BOUND)); memset(DIS_BOUND_obj , 0 ,sizeof(DIS_BOUND)) ; DIS_BOUND_obj->type = Dis_Bound;
// �ͷ���ʾ����
#define FreeDisplayObj(DIS_obj) free(DIS_obj)

/**
* @alias ���ʲ�������
*/
typedef struct LineStyle
{
	unsigned long lColor;	/** ��ͨ�ʣ���Ҫ�˲���������ɫ����չ��ʱ���˲�������LOGBRUSH�ṹ��lbcolor������Ĭ�Ϻ�ɫ*/
	unsigned long lWidth;	/** ��ͨ������չ�ʶ���Ҫ�˲������ÿ�ȡ�Ĭ��Ϊ1*/
	bool bExt;				/** �ж������Ĳ�����������ͨ�ʻ�����չ�ʣ�Ĭ��Ϊ��ͨ��*/
	SIMLINE_STYLE eStyle;	/** ��ͨ��ʱ����Ҫ�Ĳ�������ʽ*/
	EXTLINE_STYLE eExtStyle;/** ��չ��ʱ����Ҫ�Ĳ�������ʽ���*/
	long lbHatch;			/** ��չ��ʱ����Ҫ�Ļ�����ʽ������ʮ���ߣ�б45���ߡ�Ĭ��ˮƽ��*/ 
	long lbStyle;			//��չ��ʱ����Ҫ�ı�ˢ��ʽ��Ĭ�Ϲ���ˢ
	unsigned long dwStyleCount;	/** ��չ��ʱ��������Ҫ�������ۺ���ʽ����ĸ�����Ĭ��Ϊ0*/
	unsigned long *lpStyle;	/** �������ۺ���ʽ���飬Ĭ��Ϊ0*/

}LINE_STYLE;

/**
* @alias ��ɫ����ɫ����
*/
typedef struct ImageColor
{
	unsigned long ulDataLens;	/** ���ݳ���*/
	unsigned long ulData[1];	/** ʵ������*/

} IMAGE_COLOR;


/**
* @alias ��ˢ��������
*/
typedef struct BrushStyle
{
	COLORREF lColor;	/** ��ˢ��ɫĬ��Ϊ��ɫ*/
	LOGBRUSH_STYLE Style;
	LOGBRUSH_HATCH Hatch;

}BRUSH_STYLE;

/** 
* ��������
*/
typedef enum SymbolType
{

	NONE_SYMBOL = 0x01, //�շ���
	MARKER_SYMBOL = 0x10,
	LINE_SYMBOL = 0x20,
	FILL_SYMBOL = 0x40,
	EXT_SYMBOL = 0x80, 
	COMPLEX_SYMBOL = 0x0100,
	TEXT_SYMBOL = 0x0200,//���ַ���



	SIMPLE_MARKER_SYMBOL = 0x11,	
	CHAR_MARKER_SYMBOL   = 0x12,
	ARROW_MARKER_SYMBOL  = 0x13,
	PIC_MARKER_SYMBOL    = 0x14,

	SIMPLE_LINE_SYMBOL = 0x21,
	ADV_LINE_SYMBOL	  = 0x22,
	MARKER_LINE_SYMBOL	  = 0x23,
	HASH_LINE_SYMBOL   = 0x24,		
	PIC_LINE_SYMBOL    = 0x25,


	SIMPLE_FILL_SYMBOL = 0x41,
	MARKER_FILL_SYMBOL	  = 0x42,
	LINE_FILL_SYMBOL   = 0x43,
	PIC_FILL_SYMBOL    =	0x44,
	GRADIENT_FILL_SYMBOL    =	0x45,
	
	COMPLEX_MARKER_SYMBOL= COMPLEX_SYMBOL | MARKER_SYMBOL,
	COMPLEX_LINE_SYMBOL= COMPLEX_SYMBOL | LINE_SYMBOL,
	COMPLEX_FILL_SYMBOL=	COMPLEX_SYMBOL | FILL_SYMBOL,

	EXT_MARKER_SYMBOL	  = EXT_SYMBOL | MARKER_SYMBOL,
	EXT_LINE_SYMBOL	  = EXT_SYMBOL | LINE_SYMBOL,
	EXT_FILL_SYMBOL	  = EXT_SYMBOL | FILL_SYMBOL,
	EXT_ALL_SYMBOL	  = 0xf0,

	RASTER_SYMBOL	  = 0x1000,
	PICRASTER_SYMBOL	  = 0x1001,
	COLORBOXRASTER_SYMBOL=0x1002,
	BANDRASTER_SYMBOL	=0x1003,
	FAKECOLOR_RASTER_SYMBOL = 0x1004,
	DEM_REFLACTION_SYMBOL = 0x1005
}SYMBOL_TYPE;

/** 
* ��������
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
* ������ʽ:����롢�Ҷ��롢���Ķ���
*/
typedef enum AlignType
{
	ATLeft	 = 1,
	ATRight  = 2,
	ATCenter = 3

}ALIGN_TYPE;

/** 
* ��������
*/
typedef enum ObjType
{
	OTNormal = 1,	/**��������ƶ���*/
	OTCurve	 = 2,	/** �����*/
	OTRect	 = 3	,	/** ����*/
	OTEllipse = 4,	/** ��Բ*/
	OTRoundRect	= 5,/** Բ�Ǿ���*/
	OTArcCW	 = 6,	/** ˳ʱ����Բ��*/
	OTArcCCW = 7,	/** ��ʱ����Բ��*/
	OTChord	 = 8,	/** ����*/
	OTPie	 = 9,	/** ����*/
	OTPath	 = 10,	/** ·��������֮���������ģ��������Ĳ����������Զ�����������������*/
	OTMultiObject = 11	/** ������״���Դ��벿�ֲ����κδ���*/

}OBB_TYPE;

//CtoTextSymbol����ʽ���趨
#define DT_TOP						0x00000000
#define DT_LEFT						0x00000000
#define DT_CENTER					0x00000001
#define DT_RIGHT						0x00000002
#define DT_VCENTER					0x00000004
#define DT_BOTTOM					0x00000008
#define DT_WORDBREAK					0x00000010
#define DT_SINGLELINE				0x00000020
#define DT_EXPANDTABS				0x00000040
#define DT_TABSTOP					0x00000080
#define DT_NOCLIP					0x00000100
#define DT_EXTERNALLEADING			0x00000200
#define DT_CALCRECT					0x00000400
#define DT_NOPREFIX					0x00000800
#define DT_INTERNAL					0x00001000
#define DT_EDITCONTROL				0x00002000
#define DT_PATH_ELLIPSIS				0x00004000
#define DT_END_ELLIPSIS				0x00008000
#define DT_MODIFYSTRING				0x00010000
#define DT_RTLREADING				0x00020000
#define DT_WORD_ELLIPSIS				0x00040000
#define DT_NOFULLWIDTHCHARBREAK		0x00080000
#define DT_HIDEPREFIX				0x00100000
#define DT_PREFIXONLY				0x00200000

//�ı������λ��
typedef enum TextPosType{
	TXTPOS_LEFTTOP		=	0,
	TXTPOS_CENTERTOP		=	1,
	TXTPOS_RIGHTTOP		=	2,
	TXTPOS_LEFTCENTER	=	3,
	TXTPOS_CENTER		=	4,
	TXTPOS_RIGHTCENTER	=	5,
	TXTPOS_LEFTBOTTOM	=	6,
	TXTPOS_CENTERBOTTOM	=	7,
	TXTPOS_RIGHTBOTTOM	=	8
}TEXT_POS_TYPE;

typedef enum TextFillType
{
	FILL_NULL=0,
	FILL_RECT=1,
	FILL_RECT_ROUND=2,
	FILL_RECT_SHARP=3,
	FILL_RECT_ROUND_SHARP=4
}TEXT_FILL_TYPE;

typedef enum TextMarkType
{
	MARK_NULL=0,
	MARK_DRAW=1
}TEXT_MARK_TYPE;

typedef enum TextLineType
{
	LINE_NULL=0,
	LINE_LEFT=1,
	LINE_TOP=2,
	LINE_RIGHT=3,
	LINE_BOTTOM=4,
	LINE_BOTH_V=5,//����2��
	LINE_BOTH_H=6	//ˮƽ2��
}TEXT_LINE_TYPE;
/**
* ��������
*/
typedef enum DrawContent
{
	//����ʾ
	drawNone = 0x00,
	//��ʾʸ��Ҫ�ء�դ��
	drawGeography = 0x01,
	//��ʾѡ��
	drawGeoSelection = 0x02,
	//��ʾͼԪ
	drawElement = 0x04,
	//��ʱ�༭
	drawEdit = 0x08,
	//��ʱ����
	drawTempObj = 0x10,
	//ȫ����ʾ
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