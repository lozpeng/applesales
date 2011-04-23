#include "stdafx.h"
#include "SymbolFactory.h"
#include "AdvLineSymbol.h"
#include "DisOptimize.h"
#include "CDC.h"
#include "DashArray.h"
#include "IArchive.h"
#include "ArrowMarkerSymbol.h"

#pragma warning(disable:4996)
Display::CAdvLineSymbol::CAdvLineSymbol()
{
		m_enumLineCapsType = EXT_ENDCAP_ROUND;			//高级线的线头类型默认为圆形

		m_enumLineJointType = EXT_JOIN_ROUND;			//高级线的线连接类型默认为圆形

		m_LineJointStyle = LJSRound;					

		m_enumExtLineType = EXT_SOLID;					//高级线的样式，默认为实心笔

		m_enumCombinType = EXT_GEOMETRIC;				//高级线的结合类型,默认为几何笔
	
		m_enumLogBrushType = SOLID_BRUSH;					//笔刷设置，默认为实心刷

		m_enumLOGBRUSH_HATCH = HORIZONTAL;			//笔刷线型，默认为水平线

		m_enumArrowMarkerType = NOARROW;					//箭头类型,默认无装饰物

		m_lArrowNum = 2;									//装饰符的数量

		m_bFixRotation = false;							//箭头方向,默认为flase,跟随线形方向

		m_bFlipFirst = false;								//反向装饰符的首个,默认为false

		m_bFlipAll = false;								//反向全部装饰符,默认为false

		m_pArrowMarkerSymbol.reset( new CArrowMarkerSymbol );

		m_hPenHandle = NULL;
		
		Display::ISymbolPtr aimOfSymbol = Display::CSymbolFactory::CreateSymbol(SIMPLE_LINE_SYMBOL);
		aimOfSymbol->SetUnit(this->GetUnit());
		m_pDashGroup = new CDashArray(aimOfSymbol);
		m_pDashGroup->SetDashGroupCount(1);				//初始数组个数为0
		if ( m_enumUnit == SYSTEM::SYS_UNIT_PIXEL )
		{
			m_pDashGroup->AddDash(20.000000f);
		}
		else if ( m_enumUnit == SYSTEM::SYS_UNIT_MILLIMETER )
		{	
			m_pDashGroup->AddDash(10.000000f);
		}
		else if ( m_enumUnit == SYSTEM::SYS_UNIT_CENTIMETER )
		{
			m_pDashGroup->AddDash(1.000000f);
		}
		else if ( m_enumUnit == SYSTEM::SYS_UNIT_DECIMETER )
		{
			m_pDashGroup->AddDash(0.100000f);
		}
		else if ( m_enumUnit == SYSTEM::SYS_UNIT_POINT )
		{
			m_pDashGroup->AddDash(30.000000f);
		}

		m_bDrawFlag = true;

		storeArrowAngle = m_pArrowMarkerSymbol->GetAngle();

		m_lOffsetLineCount = 0;
}

Display::CAdvLineSymbol::CAdvLineSymbol(const Display::CAdvLineSymbol& AdvLineSymbol)
{
	*this = AdvLineSymbol;
}

Display::CAdvLineSymbol& Display::CAdvLineSymbol::operator = (const Display::CAdvLineSymbol & AdvLineSymbol)
{
		this->m_bFixRotation		=		AdvLineSymbol.m_bFixRotation;
		this->m_bFlipAll			=		AdvLineSymbol.m_bFlipAll;
		this->m_bFlipFirst			=		AdvLineSymbol.m_bFlipFirst;
		this->m_enumArrowMarkerType	=		AdvLineSymbol.m_enumArrowMarkerType;
		this->m_enumCombinType		=		AdvLineSymbol.m_enumCombinType;
		this->m_enumExtLineType		=		AdvLineSymbol.m_enumExtLineType;
		this->m_enumLineCapsType	=		AdvLineSymbol.m_enumLineCapsType;
		this->m_enumLineJointType	=		AdvLineSymbol.m_enumLineJointType;
		this->m_LineJointStyle		=		AdvLineSymbol.m_LineJointStyle;
		this->m_enumLOGBRUSH_HATCH	=		AdvLineSymbol.m_enumLOGBRUSH_HATCH;
		this->m_enumLogBrushType	=		AdvLineSymbol.m_enumLogBrushType;
		this->m_lArrowNum			=		AdvLineSymbol.m_lArrowNum;
		this->m_lColor				=		AdvLineSymbol.m_lColor;	
		*this->m_pDashGroup			=		*AdvLineSymbol.m_pDashGroup;
		this->storeArrowAngle		=		AdvLineSymbol.storeArrowAngle;
		*(ILineSymbol*)this			=		*(ILineSymbol*)&AdvLineSymbol;
		this->m_pArrowMarkerSymbol	=		AdvLineSymbol.m_pArrowMarkerSymbol->Clone();
		return *this;
}

Display::CAdvLineSymbol::~CAdvLineSymbol()
{
	if ( m_pDashGroup != NULL)
	{
		delete m_pDashGroup;
	}
}
//线设置部分
void Display::CAdvLineSymbol::SetLineCapsType(EXTLINE_END_CAP enumLineCapsType)
{	
		m_enumLineCapsType = enumLineCapsType;
}

EXTLINE_END_CAP Display::CAdvLineSymbol::GetLineCapsType()
{
	return m_enumLineCapsType;
}

void Display::CAdvLineSymbol::SetLineJointType(EXTLINE_JOIN enumLineJointType)
{
		m_enumLineJointType = enumLineJointType;
		if ( enumLineJointType == EXT_JOIN_ROUND )
			m_LineJointStyle = LJSRound;
		else if ( enumLineJointType == EXT_JOIN_MITER )
			m_LineJointStyle = LJSMiter;
		else if ( enumLineJointType == EXT_JOIN_BEVEL )
			m_LineJointStyle = LJSBevel;
}

EXTLINE_JOIN Display::CAdvLineSymbol::GetLineJointType()
{
	return m_enumLineJointType;
}

void Display::CAdvLineSymbol::SetExtLineStyle(EXTLINE_STYLE enumLineExtStyle)
{
		m_enumExtLineType = enumLineExtStyle;
}

EXTLINE_STYLE Display::CAdvLineSymbol::GetExtLineStyle()
{
	return m_enumExtLineType;
}

/////刷子部分
void Display::CAdvLineSymbol::SetLogBrushStyle(LOGBRUSH_STYLE enumLogBrush)
{
		m_enumLogBrushType = enumLogBrush;
}

LOGBRUSH_STYLE Display::CAdvLineSymbol::GetLogBrushStyle()
{
	return m_enumLogBrushType;
}

void Display::CAdvLineSymbol::SetLogBrushHatch(LOGBRUSH_HATCH enumLOGBRUSH_HATCH)
{
		m_enumLOGBRUSH_HATCH = enumLOGBRUSH_HATCH;
}

LOGBRUSH_HATCH Display::CAdvLineSymbol::GetLogBrushHatch()
{
	return m_enumLOGBRUSH_HATCH;
}
//////装饰符号部分
void Display::CAdvLineSymbol::SetArrowMarkerType(ARROW_DIRECTION enumArrowMarkerType)
{
		m_enumArrowMarkerType = enumArrowMarkerType;
}

ARROW_DIRECTION Display::CAdvLineSymbol::GetArrowMarkerType()
{
	return m_enumArrowMarkerType;
}

void Display::CAdvLineSymbol::SetArrowNum(long lArrowNum)
{

		if( lArrowNum < 0 )
		{
			return;
		}
		m_lArrowNum = lArrowNum;
}

long Display::CAdvLineSymbol::GetArrowNum()
{
	return m_lArrowNum;
}

void Display::CAdvLineSymbol::SetFixRotation(bool bFixRotation)
{
		m_bFixRotation = bFixRotation;
}

bool Display::CAdvLineSymbol::GetFixRotation()
{
	return m_bFixRotation;
}

void Display::CAdvLineSymbol::SetFlipFirst(bool bFlipFirst)
{
		m_bFlipFirst = bFlipFirst;
}

bool Display::CAdvLineSymbol::GetFlipFirst()
{
	return m_bFlipFirst;
}

void Display::CAdvLineSymbol::SetFlipAll(bool bFlipAll)
{
		m_bFlipAll = bFlipAll;
}

bool Display::CAdvLineSymbol::GetFlipAll()
{
	return m_bFlipAll;
}

void Display::CAdvLineSymbol::SetArrowMarkerSymbol(IMarkerSymbolPtr pArrowMarkSymbol)
{

		if( !pArrowMarkSymbol )
		{
			return;
		}
		m_pArrowMarkerSymbol = pArrowMarkSymbol;
		storeArrowAngle = m_pArrowMarkerSymbol->GetAngle();

}

Display::IMarkerSymbolPtr Display::CAdvLineSymbol::GetArrowMarkerSymbol()
{
	return m_pArrowMarkerSymbol;
}

//
SYMBOL_TYPE	Display::CAdvLineSymbol::GetType()
{
	return ADV_LINE_SYMBOL;
}

void Display::CAdvLineSymbol::SelectDC(Display::CDC * pDC)
{
		ISymbol::SelectDC( pDC );

		LINE_STYLE ls;									//设置画笔
		memset( &ls , 0 , sizeof(ls) );
		ls.bExt = true;
		if ( m_enumExtLineType == EXT_USERSTYLE )
		{
			if ( m_pDashGroup->GetDashGroupCount() > 0 )
			{
				if ( m_pDashGroup->GetDashSize() > 0 )
				{
					ls.dwStyleCount = m_pDashGroup->GetDashGroupCount();
					ls.lpStyle = m_pDashGroup->GetData();
					if (ls.dwStyleCount > 16)
					{
						ls.dwStyleCount = 16;
					}
				}
				else
				{
					return;
				}
			}
			else
			{
				return;
			}
		}

		ls.eExtStyle = (EXTLINE_STYLE)((int)m_enumLineCapsType | (int)m_enumLineJointType | (int)m_enumExtLineType | (int)m_enumCombinType);

		ls.lbStyle = m_enumLogBrushType;
		if (m_enumCombinType == EXT_COSMETIC)
		{
			ls.lbStyle = BS_SOLID;
		}
		ls.lbHatch = m_enumLOGBRUSH_HATCH;

		ls.lColor = m_lColor;
		if ( m_lLineWidth == 0 || m_enumCombinType == EXT_COSMETIC)
		{
			ls.lWidth = 1;
		}
		else
		{
			ls.lWidth = m_lLineWidth;
		}

		DISPLAY_HANDLE hPen = m_pDC->CreatePen(ls);
		m_hPenHandle = CDisplayCache::AddToDisplayCache( hPen , m_pDC );
		if ( m_enumArrowMarkerType != NOARROW )							//判断是否加入箭头装饰符部分代码
		{				
			if  ( m_pArrowMarkerSymbol.get() != NULL )
			{
				m_pArrowMarkerSymbol->SelectDC(pDC);
			}	
			else
			{
				return;
			}
		}
}

void Display::CAdvLineSymbol::SetReadyDraw()
{
	CDisplayCache::UseCache( m_hPenHandle , this );
}

void Display::CAdvLineSymbol::Draw(void* pObject)
{
		if( CheckNoColor(m_lColor))
			return;

		long *pMarkGroup=NULL;
		if(((DIS_LINE *)pObject)->type == Dis_Line)
		{
			DIS_LINE *pDIS_LINE = (DIS_LINE*)pObject;
			
			if(pDIS_LINE == NULL)
				return;

			

			m_lOffsetLineCount = CDisOptimize::OffsetLine( pDIS_LINE->Count , &(pDIS_LINE->ps[0].x) , m_lOffsetX , m_lOffsetY , m_LineJointStyle , &pMarkGroup );
			if (m_lOffsetLineCount > 1)	
			{
				m_pDC->DrawPolyLines( *pMarkGroup , m_lOffsetLineCount );
			}
			else
			{
				pMarkGroup = NULL;
				return;
			}

		}
		else if(((DIS_BEZIER *)pObject)->type == Dis_Bezier)
		{
			DIS_BEZIER  *pDIS_BEZIER = (DIS_BEZIER *)pObject;

			m_lOffsetLineCount = CDisOptimize::OffsetLine( pDIS_BEZIER->Count , &(pDIS_BEZIER->ps[0].x) , m_lOffsetX , m_lOffsetY , m_LineJointStyle , &pMarkGroup );
			
			if (m_lOffsetLineCount > 1)	
			{
				m_pDC->DrawPolyBezier( *pMarkGroup , m_lOffsetLineCount );
			}
			else
			{
				pMarkGroup = NULL;
				return;
			}
		}
		
		//实现绘制	
		if ( m_enumArrowMarkerType != NOARROW )	
		{
			if (pMarkGroup != NULL)
				DrawArrow(pMarkGroup);
		}

		CDisOptimize::free_Group(&pMarkGroup);

}
void Display::CAdvLineSymbol::SetDashGroup(Display::CDashArray &DashArray)
{

		*m_pDashGroup = DashArray;
		if ( m_pDashGroup->GetDashSize() && m_pDashGroup->GetDashGroupCount() > 0 )
			m_bDrawFlag = true;
		else
			m_bDrawFlag = false;
}

Display::CDashArray& Display::CAdvLineSymbol::GetDashGroup()
{
	return *m_pDashGroup;
}

void Display::CAdvLineSymbol::DrawArrow(void* pObject)
{
		if ( m_enumArrowMarkerType == NOARROW )
		{
			return;
		}
		else if ( m_enumArrowMarkerType == ARROWBOTH )
		{
			//起点
			DIS_POINT point1,point2;
			point1.type = Dis_Point;
			point2.type = Dis_Point;

			INT_POINT *temppoint1 = (INT_POINT*)pObject;
			point1.p.x = temppoint1->x;
			point1.p.y = temppoint1->y;

			INT_POINT *temppoint2 = ( ((INT_POINT*)pObject) + 1 );
			point2.p.x = temppoint2->x;
			point2.p.y = temppoint2->y;

			if ( m_pArrowMarkerSymbol->GetType() == COMPLEX_MARKER_SYMBOL )
			{
				m_pArrowMarkerSymbol->SetAngle(0);
				m_pArrowMarkerSymbol->SetAngle( _2PI - atan2((float)( point1.p.y - point2.p.y ) , (float)( point1.p.x - point2.p.x )));
			}
			else
			{
				m_pArrowMarkerSymbol->SetAngle( _2PI - ( storeArrowAngle + atan2((float)( point1.p.y - point2.p.y ) , (float)( point1.p.x - point2.p.x ))));
			}

			m_pArrowMarkerSymbol->SetReadyDraw();
			m_pArrowMarkerSymbol->Draw(&point1);


			//终点
			DIS_POINT point3,point4;
			point3.type = Dis_Point;
			point4.type = Dis_Point;

			INT_POINT *temppoint3 = (((INT_POINT*)pObject) + m_lOffsetLineCount - 2 );
			point3.p.x = temppoint3->x;
			point3.p.y = temppoint3->y;

			INT_POINT *temppoint4 = (((INT_POINT*)pObject) + m_lOffsetLineCount - 1 );
			point4.p.x=temppoint4->x;
			point4.p.y=temppoint4->y;

			if ( m_pArrowMarkerSymbol->GetType() == COMPLEX_MARKER_SYMBOL )
			{
				m_pArrowMarkerSymbol->SetAngle(0);
				m_pArrowMarkerSymbol->SetAngle( _2PI - atan2((float)( point4.p.y - point3.p.y ) , (float)( point4.p.x - point3.p.x )));
			}
			else
			{
				m_pArrowMarkerSymbol->SetAngle( _2PI - ( storeArrowAngle + atan2((float)( point4.p.y - point3.p.y ) , (float)( point4.p.x - point3.p.x ))));
			}
			//			m_pArrowMarkerSymbol->SetReadyDraw();			//上面已经调用，不必重复调用
			m_pArrowMarkerSymbol->Draw(&point4);
			this->SetReadyDraw();
		}
		else if(m_enumArrowMarkerType==ARROWBEGIN)
		{
			//起点
			DIS_POINT point1,point2;
			point1.type = Dis_Point;
			point2.type = Dis_Point;

			INT_POINT *temppoint1 = (INT_POINT*)pObject;
			point1.p.x = temppoint1->x;
			point1.p.y = temppoint1->y;

			INT_POINT *temppoint2 = (((INT_POINT*)pObject) + 1);
			point2.p.x = temppoint2->x;
			point2.p.y = temppoint2->y;

			if ( m_pArrowMarkerSymbol->GetType() == COMPLEX_MARKER_SYMBOL )
			{
				m_pArrowMarkerSymbol->SetAngle(0);
				m_pArrowMarkerSymbol->SetAngle( _2PI - atan2((float)(point1.p.y - point2.p.y) , (float)(point1.p.x - point2.p.x)));
			}
			else
			{
				m_pArrowMarkerSymbol->SetAngle( _2PI - (storeArrowAngle + atan2((float)(point1.p.y - point2.p.y) , (float)(point1.p.x - point2.p.x))));
			}
			m_pArrowMarkerSymbol->SetReadyDraw();
			m_pArrowMarkerSymbol->Draw(&point1);
			this->SetReadyDraw();
		}
		else if(m_enumArrowMarkerType==ARROWEND)
		{
			//终点
			DIS_POINT point3,point4;
			point3.type = Dis_Point;
			point4.type = Dis_Point;

			INT_POINT *temppoint3 = (((INT_POINT*)pObject) + m_lOffsetLineCount - 2);
			point3.p.x = temppoint3->x;
			point3.p.y = temppoint3->y;

			INT_POINT *temppoint4 = (((INT_POINT*)pObject) + m_lOffsetLineCount - 1);
			point4.p.x = temppoint4->x;
			point4.p.y = temppoint4->y;

			if ( m_pArrowMarkerSymbol->GetType() == COMPLEX_MARKER_SYMBOL )
			{
				m_pArrowMarkerSymbol->SetAngle(0);
				m_pArrowMarkerSymbol->SetAngle( _2PI - atan2((float)(point4.p.y - point3.p.y) , (float)(point4.p.x - point3.p.x)));
			}
			else
			{
				m_pArrowMarkerSymbol->SetAngle( _2PI - (storeArrowAngle + atan2((float)(point4.p.y - point3.p.y) , (float)(point4.p.x - point3.p.x))));
			}
			m_pArrowMarkerSymbol->SetReadyDraw();		
			m_pArrowMarkerSymbol->Draw(&point4);
			this->SetReadyDraw();
		}
		if ( m_pArrowMarkerSymbol->GetType() == COMPLEX_MARKER_SYMBOL )
		{
			m_pArrowMarkerSymbol->SetAngle(0);
		}
		else
		{
			m_pArrowMarkerSymbol->SetAngle(storeArrowAngle);
		}
}

#define SETPROP(inVal,Val,inName,Name,VT) if( stricmp(inName,Name) == 0 ) { Val = (VT)inVal;return; }
#define SETPROP2(Val,Name,VT) SETPROP( PropertyValue , Val , PropertyName , Name , VT )
#define SETPROPEX(inVal,Val,inName,Name,VT,VT2) if( stricmp(inName,Name) == 0 ) { Val = (VT2)((VT)inVal);return; }
#define SETPROPEX2(Val,Name,VT,VT2) SETPROPEX( PropertyValue , Val , PropertyName , Name , VT , VT2)
void Display::CAdvLineSymbol::SetProperties(const char* PropertyName,const _variant_t& PropertyValue)
{

		SETPROPEX2( m_enumLineCapsType , "EXTLINE_END_CAP" , long , EXTLINE_END_CAP );
		SETPROPEX2( m_enumLineJointType , "EXTLINE_JOIN" , long , EXTLINE_JOIN );
		SETPROPEX2( m_enumExtLineType , "EXTLINE_STYLE" , long , EXTLINE_STYLE );
		SETPROPEX2( m_enumCombinType , "EXTLINE_COMBIN_TYPE" , long , EXTLINE_COMBIN_TYPE );
		SETPROPEX2( m_enumLogBrushType , "LOGBRUSH_STYLE" , long , LOGBRUSH_STYLE );
		SETPROPEX2( m_enumLOGBRUSH_HATCH , "LOGBRUSH_HATCH" , long , LOGBRUSH_HATCH );
		SETPROPEX2( m_enumArrowMarkerType , "ARROW_DIRECTION" , long , ARROW_DIRECTION );
		SETPROP2( m_lArrowNum , "ARROWNUM" , long );
		SETPROP2( m_bFixRotation , "FIXROTATABLE" , bool );
		SETPROP2( m_bFlipFirst , "FLIPFIRSTABLE" , bool );
		SETPROP2( m_bFlipAll , "FLIPALLABLE" , bool );
		
		if( stricmp("DASHGROUP",PropertyName) == 0 )
		{ 
			*m_pDashGroup = *((CDashArray*)(void*)(long)PropertyValue);
			return; 
		}
		
		if( stricmp( PropertyName , "ARROWSYMBOL" ) == 0 ) 
		{
			if( PropertyValue.vt == VT_BSTR )
			{
				SYSTEM::CStringArchive ar;
				ar.ImportVariant( PropertyValue);
				ar.SetReadState();
				/*m_OutLineSymbol->serialization( ar );*/
				m_pArrowMarkerSymbol = Display::CSymbolFactory::CreateSymbolFromStream(ar);			//本想判断一下返回的符号是否是线符号。暂时不作判断了咧
				return;
			}
			else
			{
				SYSTEM::CBinArchive ar;
				ar.ImportVariant( PropertyValue);
				ar.SetReadState();
				/*m_OutLineSymbol->serialization( ar );*/
				m_pArrowMarkerSymbol = Display::CSymbolFactory::CreateSymbolFromStream(ar);
				return;
			}
		}

		return ILineSymbol::SetProperties( PropertyName , PropertyValue );

}

#define GETPROP(inName,Name,Val,T) if( stricmp(inName,Name) == 0 ) { vt = (T)Val;return vt; }
#define GETPROP2(Name,Val,T) GETPROP(PropertyName , Name , Val , T )
_variant_t Display::CAdvLineSymbol::GetProperties(const char* PropertyName)
{

	_variant_t vt;

	long t = m_enumLineCapsType;
	GETPROP2("EXTLINE_END_CAP", t , _variant_t );

	t = m_enumLineJointType;
	GETPROP2("EXTLINE_JOIN", t , _variant_t );

	t = m_enumExtLineType;
	GETPROP2("EXTLINE_STYLE", t , _variant_t );

	t = m_enumCombinType;
	GETPROP2("EXTLINE_COMBIN_TYPE", t , _variant_t );

	t = m_enumLogBrushType;
	GETPROP2("LOGBRUSH_STYLE", t , _variant_t );

	t = m_enumLOGBRUSH_HATCH;
	GETPROP2("LOGBRUSH_HATCH", t , _variant_t );

	t = m_enumArrowMarkerType;
	GETPROP2("ARROW_DIRECTION", t , _variant_t );

	GETPROP2("ARROWNUM" , m_lArrowNum , _variant_t );
	GETPROP2("FIXROTATABLE" , m_bFixRotation , _variant_t );
	GETPROP2("FLIPFIRSTABLE" , m_bFlipFirst , _variant_t );
	GETPROP2("FLIPALLABLE" , m_bFlipAll , _variant_t );

	if( stricmp("DASHGROUP",PropertyName) == 0 ) 
	{ 
		return (long)m_pDashGroup;
	}

	if( stricmp(PropertyName, "ArrowSymbol" ) == 0 )
	{
		SYSTEM::CBinArchive ar;
		ar.SetWriteState();
		m_pArrowMarkerSymbol->serialization( ar );
		return ar.ExportToVariant();
	}

	return ILineSymbol::GetProperties(PropertyName);

}
void Display::CAdvLineSymbol::Zoom(float rate)
{

		ILineSymbol::Zoom(rate);
		
		if (m_pArrowMarkerSymbol)
		{
			m_pArrowMarkerSymbol->Zoom(rate);
		}

		//变换破折号数组的间距
		for( unsigned long i = 0 ; i < m_pDashGroup->GetDashGroupCount() ; ++i )
		{
			float tempData = m_pDashGroup->GetDash(i);
			m_pDashGroup->SetDash(tempData * rate , i);
		}
}

void Display::CAdvLineSymbol::serialization(SYSTEM::IArchive & ar)
{ 
	ILineSymbol::serialization(ar); 
	//序列化父类的属性
	ar & m_lArrowNum;	
	ar & m_bFixRotation;
	ar & m_bFlipFirst;
	ar & m_bFlipAll;
	ar & m_bDrawFlag;
	m_pDashGroup->serialization( ar );
	//序列化自己的属性
	if( ar.IsSave() )
	{
		int i;
		i=m_enumLineCapsType;
		ar & i;
		i=m_enumLineJointType;
		ar & i;
		i=m_enumExtLineType;
		ar & (i);
		i=m_enumCombinType;
		ar & (i);
		i=m_enumLogBrushType;
		ar & (i);
		i=m_enumLOGBRUSH_HATCH;
		ar & (i);
		i=m_enumArrowMarkerType;
		ar & (i);

		int  type=m_pArrowMarkerSymbol->GetType();
		ar & (type);
		m_pArrowMarkerSymbol->serialization( ar );
	}
	else
	{
		int i;	
		ar & (i);
		m_enumLineCapsType=(EXTLINE_END_CAP)i;
		ar & (i);
		m_enumLineJointType=(EXTLINE_JOIN)i;
		ar & (i);
		m_enumExtLineType=(EXTLINE_STYLE)i;
		ar & (i);
		m_enumCombinType=(EXTLINE_COMBIN_TYPE)i;
		ar & (i);
		m_enumLogBrushType=(LOGBRUSH_STYLE)i;
		ar & (i);
		m_enumLOGBRUSH_HATCH=(LOGBRUSH_HATCH)i;
		ar & (i);
		m_enumArrowMarkerType=(ARROW_DIRECTION)i;

		int type;
		ar & (type);
		m_pArrowMarkerSymbol = CSymbolFactory::CreateSymbol( (SYMBOL_TYPE)type );
		m_pArrowMarkerSymbol->serialization( ar );
	}	
}

void Display::CAdvLineSymbol::ClearDC()
{
	if( m_hPenHandle != NULL )
	{
		CDisplayCache::ReleaseCache( m_hPenHandle );
		m_hPenHandle = NULL;
	}
	if ( m_pArrowMarkerSymbol != NULL )
	{
		m_pArrowMarkerSymbol->ClearDC();
	}
	ILineSymbol::ClearDC();
}

void Display::CAdvLineSymbol::OnUnitChanged(SYSTEM::SYS_UNIT_TYPE oldUnit , SYSTEM::SYS_UNIT_TYPE newUnit)
{
	ILineSymbol::OnUnitChanged(oldUnit , newUnit);
	/*if ( m_pArrowMarkerSymbol != NULL )
	{
		m_pArrowMarkerSymbol->SetUnit(newUnit);
	}*/
}

void Display::CAdvLineSymbol::OnChangingInSelectDC()
{
	ILineSymbol::OnChangingInSelectDC();
}

void Display::CAdvLineSymbol::SetLineCombinType(EXTLINE_COMBIN_TYPE enumCombinType)
{
	m_enumCombinType = enumCombinType;
}

EXTLINE_COMBIN_TYPE Display::CAdvLineSymbol::GetLineCombinType()
{
	return m_enumCombinType;
}