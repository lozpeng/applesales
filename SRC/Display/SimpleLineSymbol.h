//////////////////////////////////////////////////////////////////////
  // 版权(c) 2010-2020, 天地智绘
  // 作者：  hhzhao
  // 时间：  2008/11/26
  // 描述：  简单线符号类
//////////////////////////////////////////////////////////////////////
#ifndef _CSIMPLELINESYMBOL_H
#define _CSIMPLELINESYMBOL_H

#include "ILineSymbol.h"
#include "DisplayCache.h"

namespace Display{

class DISPLAY_DLL CSimpleLineSymbol : public ILineSymbol
{
public:
	CSimpleLineSymbol();

	CSimpleLineSymbol(const CSimpleLineSymbol& SimpleLineSymbol);

	CSimpleLineSymbol& operator = (const CSimpleLineSymbol& SimpleLineSymbol);

	virtual ~CSimpleLineSymbol();

	// 函数名称   : SetProperties( const char* PropertyName , const _variant_t& PropertyValue )
	// 描述       : 设置属性
	// 返回类型   : virtual void 
	// 参数       : const char* PropertyName   属性名称
	// 参数       : const _variant_t& PropertyValue   属性值
	virtual void SetProperties( const char* PropertyName , const _variant_t& PropertyValue);

	// 函数名称   : GetProperties(const char* PropertyName)
	// 描述       : 得到属性
	// 返回类型   : virtual _variant_t 
	// 参数       : const char* PropertyName   属性名称
	virtual _variant_t GetProperties(const char* PropertyName);			//得到当前符号的属性配置返回引用.如果没有此属性返回0.


	/////子类实例化须实现方法

	// 函数名称   : Draw(void* pObject)
	// 描述       : 绘制
	// 返回类型   : virtual void 
	// 参数       : void* pObject   符号对象
	virtual void Draw(void* pObject);				//实现绘制

	// 函数名称   : GetType()
	// 描述       : 获得类类型
	// 返回类型   : virtual SYMBOL_TYPE 
	virtual SYMBOL_TYPE GetType();					//得到类类型

	// 函数名称   : Zoom(float rate)
	// 描述       : 根据比例进行符号缩放
	// 返回类型   : virtual void 
	// 参数       : float rate
	virtual void Zoom(float rate);

	//类自身方法，可继承给子类，可被子类覆盖

	// 函数名称   : GetLineStyle()
	// 描述       : 得到线样式
	// 返回类型   : SIMLINESTYLE 
	SIMLINE_STYLE GetLineStyle();					//得到线样式

	// 函数名称   : SetLineStyle(SIMLINESTYLE nStyle)
	// 描述       : 设置线样式
	// 返回类型   : void 
	// 参数       : SIMLINESTYLE nStyle
	void SetLineStyle(SIMLINE_STYLE nStyle);

	// 函数名称   : SelectDC(CDC * pDC)
	// 描述       : 装配画布,通过画布初始化符号
	// 返回类型   : virtual void 
	// 参数       : CDC * pDC
	virtual void SelectDC(CDC * pDC);

	// 函数名称   : SetReadyDraw()
	// 描述       : 将selectDC创建所需的绘制句柄装入当前画布，完成绘制前的准备工作
	// 返回类型   : virtual void 
    virtual void SetReadyDraw();

	// 函数名称   : ClearDC()
	// 描述       : 清除画布
	// 返回类型   : virtual void 
	virtual void ClearDC();

protected:
	virtual void OnUnitChanged(SYSTEM::SYS_UNIT_TYPE oldUnit , SYSTEM::SYS_UNIT_TYPE newUnit);
	virtual void OnChangingInSelectDC();

private://类自身所需变量
	SIMLINE_STYLE m_enumLineType;					//线样式枚举

	DISPLAY_HANDLE_NODE* m_hPenHandle;							//笔对象缓存

public:

	// 函数名称   : serialization(otSystem::IArchive &ar)
	// 描述       : 序列化操作
	// 返回类型   : virtual void 
	// 参数       : otSystem::IArchive &ar   档案文件流
    virtual void serialization(SYSTEM::IArchive & ar);
};

typedef SYSTEM::CSmartPtr<CSimpleLineSymbol> CSimpleLineSymbolPtr;
}

#endif //CSIMPLELINESYMBOL_H
