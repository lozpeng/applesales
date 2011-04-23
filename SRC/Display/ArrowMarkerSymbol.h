#pragma once

#include "CDC.h"
#include "IMarkerSymbol.h"
#include "IArchive.h"
#include "DisplayCache.h"

namespace Display{

class DISPLAY_DLL CArrowMarkerSymbol : public IMarkerSymbol
{
public:
	CArrowMarkerSymbol();

	CArrowMarkerSymbol(const CArrowMarkerSymbol& toArrowMarkerSymbol);

	CArrowMarkerSymbol& operator = (const CArrowMarkerSymbol& toArrowMarkerSymbol);

	virtual~CArrowMarkerSymbol();

	virtual void ClearDC();

	virtual void SetProperties(const char* PropertyName , const _variant_t& PropertyValue);

	virtual _variant_t GetProperties(const char* PropertyName);			//得到当前符号的属性配置返回引用.如果没有此属性返回0.


	/////子类实例化实现
	virtual void Draw(void* pObject);		//实现绘制

	virtual SYMBOL_TYPE GetType();			//得到类类型

	virtual void Zoom(float rate);

	//类自身方法，可继承给子类，可被子类覆盖
	void SetRate(float fRate);		//设置符号横向长度

	float GetRate();				//得到符号横向长度	

    virtual void SelectDC(Display::CDC * pDC);

    virtual void SetReadyDraw();

    virtual void serialization(SYSTEM::IArchive & ar);			
protected:
	virtual void OnUnitChanged(SYSTEM::SYS_UNIT_TYPE oldUnit , SYSTEM::SYS_UNIT_TYPE newUnit);
	virtual void OnChangingInSelectDC();
private://类自身所需变量
	float m_fRate;							//储存长宽比例

	unsigned long m_lWidth;					//宽度,内部调用


	DISPLAY_HANDLE_NODE* m_hPenHandle;	
	DISPLAY_HANDLE_NODE* m_hBrushHandle;

	unsigned long m_lInsideReviseX;			//内部x方向校正,使传入的绘制点为符号的中心点
	
	long DIS_POINTs[6];						//储存箭头的3个顶点
};

typedef SYSTEM::CSmartPtr<CArrowMarkerSymbol> CArrowMarkerSymbolPtr;

}

