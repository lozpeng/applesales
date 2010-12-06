//////////////////////////////////////////////////////////////////////
  // 版权(c) 2010-2020, 天地智绘
  // 作者：  hhzhao
  // 时间：  2008/11/26
  // 描述：  简单面符号类
//////////////////////////////////////////////////////////////////////

#ifndef CSIMPLEFILLSYMBOL_H
#define CSIMPLEFILLSYMBOL_H

////////////////////////////////////////////////////////////////////////////////
//
// 简单面符号
//		： 填充简单颜色，可以绘制边界线
//
////////////////////////////////////////////////////////////////////////////////

#include "IFillSymbol.h"
#include "DisplayCache.h"
#include "CDC.h"
#include "IArchive.h"
namespace Display{
	
class DISPLAY_DLL CSimpleFillSymbol : public IFillSymbol 
{
public:
	CSimpleFillSymbol();															//定义拷贝构造函数

	CSimpleFillSymbol(const CSimpleFillSymbol& toSimpleFillSymbol);

	CSimpleFillSymbol& operator = (const CSimpleFillSymbol& toSimpleFillSymbol);

	~CSimpleFillSymbol();

	// 函数名称   : Draw(void* pObject)
	// 描述       : 实现绘制
	// 返回类型   : virtual void 
	// 参数       : void* pObject
	 virtual void Draw(void* pObject);				  

	 // 函数名称   : GetType()
	 // 描述       : 得到类类型
	 // 返回类型   : virtual SYMBOL_TYPE 
	 virtual SYMBOL_TYPE GetType();

	 // 函数名称   : SelectDC(CDC *pDC)
	 // 描述       : 配置笔，刷，字体等
	 // 返回类型   : virtual void 
	 // 参数       : CDC *pDC   绘制句柄 
	 virtual void SelectDC(Display::CDC * pDC);
	
	 // 函数名称   : SetReadyDraw()
	 // 描述       : 将selectDC创建所需的绘制句柄装入当前画布，完成绘制前的准备工作
	 // 返回类型   : virtual void 
	 virtual void SetReadyDraw();

	 // 函数名称   : ClearDC()
	 // 描述       : 清除画布
	 // 返回类型   : virtual void 
	 virtual void ClearDC();

	 // 函数名称   : Zoom(float rate)
	 // 描述       : 根据比例进行符号缩放
	 // 返回类型   : virtual void 
	 // 参数       : float rate
	 virtual void Zoom(float rate);
protected:
	virtual void OnUnitChanged(SYSTEM::SYS_UNIT_TYPE oldUnit , SYSTEM::SYS_UNIT_TYPE newUnit);
	virtual void OnChangingInSelectDC();
protected:
	DISPLAY_HANDLE_NODE* m_hBrushHandle;											//刷子ID

public:

    virtual void serialization(SYSTEM::IArchive & ar);
};

typedef SYSTEM::CSmartPtr<CSimpleFillSymbol> CSimpleFillSymbolPtr;
}

#endif //CSIMPLEFILLSYMBOL_H
