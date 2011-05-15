/* Generated by Together */
/*作者：张维
描述：复合线符号类
版本号：1.0
创建日期：2007-5-8 下午05:30:50
*/

#ifndef CCOMPLEXLINESYMBOL_H
#define CCOMPLEXLINESYMBOL_H
#include "ILineSymbol.h"
#include "IMarkerSymbol.h"
#include "CDC.h"
#include "IArchive.h"
#include "alm.h"
#include "IComplexSymbol.h"

namespace Display{
class DISPLAY_DLL CComplexLineSymbol : public ILineSymbol , public IComplexSymbol
{
public:
//	using ILineSymbol::AddRef;
//	using ILineSymbol::Release;
	using ILineSymbol::m_lColor;
	using ILineSymbol::m_pDC;
	using ILineSymbol::SetProperties;
	using ILineSymbol::GetProperties;

	CComplexLineSymbol();
	virtual ~CComplexLineSymbol();

	CComplexLineSymbol(const CComplexLineSymbol& ComplexLineSymbol);

	//重载"="
	CComplexLineSymbol& operator = (const CComplexLineSymbol& ComplexLineSymbol);

	/////子类实例化须实现方法

	// 函数名称   : Draw(void* pObject)
	// 描述       : 实现绘制
	// 返回类型   : virtual void 
	// 参数       : void* pObject
	virtual void Draw(void* pObject);						//实现绘制

	// 函数名称   : GetType()
	// 描述       : 得到类类型
	// 返回类型   : virtual SYMBOL_TYPE 
	virtual SYMBOL_TYPE GetType();							//得到类类型

	// 函数名称   : SelectDC(CDC *pDC)
	// 描述       : 配置笔，刷，字体等
	// 返回类型   : virtual void 
	// 参数       : CDC *pDC   绘制句柄 
	virtual void SelectDC(CDC *pDC);						//配置笔，刷，字体等

	// 函数名称   : Zoom(float rate)
	// 描述       : 根据比例进行符号缩放
	// 返回类型   : virtual void 
	// 参数       : float rate
	virtual void Zoom(float rate);

	// 函数名称   : GetLineWidth()
	// 描述       : 获得线宽
	// 返回类型   : virtual unsigned long
	virtual float GetLineWidth();							//得到线宽

	//重载父类的方法

	// 函数名称   : SetLineWidth(double nWidth)
	// 描述       : 设置线宽
	// 返回类型   : virtual void 
	// 参数       : double nWidth
	virtual void SetLineWidth(float nWidth);				//设置线宽

	// 函数名称   : SetLineColor
	// 描述       : 设置线符号颜色
	// 返回类型   : virtual void 
	// 参数       : unsigned long lColor
	virtual void SetLineColor(unsigned long lColor);		//设置线符号颜色

	// 函数名称   : SetOffset
	// 描述       : 设置线符号的偏移量
	// 返回类型   : virtual void 
	// 参数       : long x
	// 参数       : long y
	virtual void SetOffset(float x , float y);					//设置线符号的偏移量

	// 函数名称   : DrawLegend( DIS_RECT * rect , int nFlag )
	// 描述       : 绘制图例
	// 返回类型   : virtual void 
	// 参数       : DIS_RECT * rect    绘制区域
	// 参数       : int nFlag   判断显示方式（直线或折线）
	virtual void DrawLegend( DIS_RECT * rect , int nFlag );

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
	virtual _variant_t GetProperties(const char* PropertyName );

	/////实现父类虚函数

	// 函数名称   : Add(ISymbolPtr symbol)
	// 描述       : 添加符号加入
	// 返回类型   : virtual bool 
	// 参数       : ISymbolPtr symbol   
	virtual bool Add(ISymbolPtr symbol);			//添加符号加入

	// 函数名称   : Insert( int index , ISymbolPtr symbol , bool state )
	// 描述       : 从索引位置开始插入一个符号，并设置显示状态
	// 返回类型   : virtual bool 
	// 参数       : int index   索引
	// 参数       : ISymbolPtr symbol   智能指针，指向符号
	// 参数       : bool state   判断是否可见
	virtual bool Insert( int index , ISymbolPtr symbol , bool state ); 

	// 函数名称   : SetSymbol( int index , ISymbolPtr symbol )
	// 描述       : 设置索引对应的符号
	// 返回类型   : virtual bool 
	// 参数       : int index
	// 参数       : ISymbolPtr symbol
	virtual bool SetSymbol( int index , ISymbolPtr symbol );

	virtual void ClearDC();
public:
	
	// 函数名称   : serialization(SYSTEM::IArchive &ar)
	// 描述       : 序列化操作
	// 返回类型   : virtual void 
	// 参数       : SYSTEM::IArchive &ar   档案文件流
	virtual void serialization(SYSTEM::IArchive & ar);
protected:
	virtual void OnUnitChanged(SYSTEM::SYS_UNIT_TYPE oldUnit , SYSTEM::SYS_UNIT_TYPE newUnit);
	virtual void OnChangingInSelectDC();

private:
	
};
typedef SYSTEM::CSmartPtr<CComplexLineSymbol> IComplexLineSymbolPtr;
}
#endif //CTOCOMPLEXLINESYMBOL_H
