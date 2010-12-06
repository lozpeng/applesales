//////////////////////////////////////////////////////////////////////
  // 版权(c) 2010-2020, 天地智绘
  // 作者：  hhzhao
  // 时间：  2008/11/26
  // 描述：  简单点符号类

// 简单点符号
//		： 可以绘制可设置颜色的五个简单形状
//			1为正方形，
//			2为圆形，
//			3为十字形，
//			4为x形，
//			5为菱形，
//			6为自定义，需要设置绘制函数
//////////////////////////////////////////////////////////////////////

#ifndef _CSIMPLEMARKERSYMBOL_H
#define _CSIMPLEMARKERSYMBOL_H

#include "DisplayCache.h"


#include "IMarkerSymbol.h"
#include "CDC.h"
#include "IArchive.h"

namespace Display{

	typedef void ( __stdcall *DRAWSTYLE_FUNC )( Display::CDC* , const DIS_POINT* , unsigned long , long , long );

class DISPLAY_DLL CSimpleMarkerSymbol : public IMarkerSymbol
{
public:
	CSimpleMarkerSymbol();

	CSimpleMarkerSymbol( const CSimpleMarkerSymbol& SimpleMarkSymbol );

	CSimpleMarkerSymbol& operator = ( const CSimpleMarkerSymbol& SimpleMarkSymbol );

	virtual ~CSimpleMarkerSymbol();

	// 函数名称   : SetProperties( const char* PropertyName , const _variant_t& PropertyValue )
	// 描述       : 设置属性
	// 返回类型   : virtual void 
	// 参数       : const char* PropertyName   属性名称
	// 参数       : const _variant_t& PropertyValue   属性值
	virtual void SetProperties( const char* PropertyName , const _variant_t& PropertyValue );

	// 函数名称   : GetProperties(const char* PropertyName)
	// 描述       : 得到属性
	// 返回类型   : virtual _variant_t 
	// 参数       : const char* PropertyName   属性名称
	virtual _variant_t GetProperties( const char* PropertyName );

	// 函数名称   : Draw(void* pObject)
	// 描述       : 绘制
	// 返回类型   : virtual void 
	// 参数       : void* pObject   符号对象
	virtual void Draw( void* pObject );

	// 函数名称   : GetType()
	// 描述       : 得到符号类型，返回简单点符号，供父类使用
	// 返回类型   : virtual SYMBOL_TYPE    符号类型 
	virtual SYMBOL_TYPE GetType();

	// 函数名称   : Zoom(float rate)
	// 描述       : 根据比例进行符号缩放
	// 返回类型   : virtual void 
	// 参数       : float rate
	virtual void Zoom( float rate );

	/*
		设置所要显示的符号，共有五种：
			1为正方形，
			2为圆形，
			3为十字形，
			4为x形，
			5为菱形，
			6为自定义，需要设置绘制函数
			默认为0不绘制
	*/

	// 函数名称   : SetMarkerType( SIMPLE_MARKER_STYLE enumType , DRAWSTYLE_FUNC Func = NULL)
	// 描述       : 设置所要显示的符号
	// 返回类型   : void 
	// 参数       : SIMPLE_MARKER_STYLE enumType   枚举点符号类型
	// 参数       : DRAWSTYLE_FUNC Func = NULL
	void SetMarkerType( SIMPLE_MARKER_STYLE enumType , DRAWSTYLE_FUNC Func = NULL);		
			
	// 函数名称   : GetMarkerType()
	// 描述       : 得到索引
	// 返回类型   : SIMPLE_MARKER_STYLE 
	SIMPLE_MARKER_STYLE GetMarkerType();									//得到索引

	// 函数名称   : SetOutLineWidth( unsigned long width )
	// 描述       : 设置边界线的宽度
	// 返回类型   : void 
	// 参数       : unsigned long width
	void SetOutLineWidth( float width );					//设置OutLine的宽度

	// 函数名称   : GetOutLineWidth
	// 描述       : 获得边界线的宽度
	// 返回类型   : unsigned long 
	float GetOutLineWidth();								//得到OutLine的宽度

	// 函数名称   : SetOutLineColor( unsigned long lColor )
	// 描述       : 设置边界线的颜色
	// 返回类型   : void 
	// 参数       : unsigned long lColor
	void SetOutLineColor( unsigned long lColor );					//设置轮廓线的颜色

	// 函数名称   : GetOutLineColor()
	// 描述       : 得到边界线的颜色
	// 返回类型   : unsigned long 
	unsigned long GetOutLineColor();								//得到轮廓线的颜色

	// 函数名称   : SetOutLineFlag( bool bOutLine )
	// 描述       : 设置是否绘制边界线
	// 返回类型   : void 
	// 参数       : bool bOutLine   判读是否绘制边界线
	void SetOutLineFlag( bool bOutLine );							//设置是否绘制轮廓线

	// 函数名称   : GetOutLineFlag()
	// 描述       : 得到是否绘制边界线设置
	// 返回类型   : bool 
	bool GetOutLineFlag();											//得到是否绘制轮廓线设置
	
	// 函数名称   : SetCustomDrawFunction()
	// 描述       : 设置自定义函数
	// 返回类型   : void 
	void SetCustomDrawFunction();								    // 设置自定义函数
public:

	// 函数名称   : SelectDC(Display::CDC *pDC)
	// 描述       : 装配画布,通过画布初始化符号
	// 返回类型   : virtual void 
	// 参数       : Display::CDC *pDC
    virtual void SelectDC( CDC * pDC );

	// 函数名称   : SetReadyDraw()
	// 描述       : 将selectDC创建所需的绘制句柄装入当前画布，完成绘制前的准备工作
	// 返回类型   : virtual void 
	virtual void SetReadyDraw();

	// 函数名称   : ClearDC
	// 描述       : 清除画布
	// 返回类型   : virtual void 
	virtual void ClearDC();

	// 函数名称   : serialization(otSystem::IArchive &ar)
	// 描述       : 序列化操作
	// 返回类型   : virtual void 
	// 参数       : otSystem::IArchive &ar   档案文件流
    virtual void serialization( SYSTEM::IArchive & ar );
protected:
	virtual void OnUnitChanged(SYSTEM::SYS_UNIT_TYPE oldUnit , SYSTEM::SYS_UNIT_TYPE newUnit);
	virtual void OnChangingInSelectDC();
private:

	unsigned long m_lOutLineWidth;									//outline的宽度
	float m_fOutLineWidth;

	SIMPLE_MARKER_STYLE m_enumMarkType;									//简单符号类型

	unsigned long m_lOutLineColor;									//点符号的边框线颜色

	bool m_bOutLine;												//是否绘制边框线


	///////////////////////

	DISPLAY_HANDLE_NODE* m_hPenHandle;								//存储笔缓存

	DISPLAY_HANDLE_NODE* m_hBrushHandle;							//存储刷子缓存

	//////////////////////

	DRAWSTYLE_FUNC m_StyleFunc;
};

typedef SYSTEM::CSmartPtr<CSimpleMarkerSymbol> CSimpleMarkerSymbolPtr;
}
#endif //CSIMPLEMARKSYMBOL_H
