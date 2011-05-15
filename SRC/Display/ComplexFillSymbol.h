#ifndef CCOMPLEXFILLSYMBOL_H
#define CCOMPLEXFILLSYMBOL_H
#include "IFillSymbol.h"
#include "CDC.h"
#include "IArchive.h"
#include "alm.h"
#include "IComplexSymbol.h"

namespace Display{
class DISPLAY_DLL CComplexFillSymbol : public IFillSymbol , public IComplexSymbol
{
public:
//	using IFillSymbol::AddRef;
//	using IFillSymbol::Release;
	using IFillSymbol::m_lColor;
	using IFillSymbol::m_pDC;


	CComplexFillSymbol();

	CComplexFillSymbol(const CComplexFillSymbol& ComplexFillSymbol);

	//重载"="
	CComplexFillSymbol& operator = (const CComplexFillSymbol& ComplexFillSymbol);

	virtual ~CComplexFillSymbol();

	/////子类实例化须实现方法
	virtual void Draw(void* pObject);							//实现绘制

	virtual SYMBOL_TYPE GetType();								//得到类类型

	void SetOutLineColor(unsigned long lColor);					//设置线的颜色

	void SetFillColor(unsigned long lColor);					//设置填充颜色

	void SetOutLineWidth(unsigned long size);					//设置线的宽度

	void SetOutLine(ILineSymbolPtr mOutLine);			    	//设置线指针

	void SetbOutLine(bool bline);								//设置是否绘制线

	virtual void SelectDC(CDC *pDC);							//装配画布，抽象方法，子类须实现

	virtual void Zoom(float rate);

	virtual void DrawLegend( DIS_RECT * rect , int nFlag );

	virtual void SetProperties( const char* PropertyName , const _variant_t& PropertyValue);

	virtual _variant_t GetProperties(const char* PropertyName);
	
	//实现父类虚函数
	virtual bool Add(ISymbolPtr symbol);

	virtual bool Insert( int index , ISymbolPtr symbol , bool state );

	virtual bool SetSymbol( int index , ISymbolPtr symbol );

	virtual void ClearDC();

public:
	  virtual void serialization(SYSTEM::IArchive & ar);
protected:
	virtual void OnUnitChanged(SYSTEM::SYS_UNIT_TYPE oldUnit , SYSTEM::SYS_UNIT_TYPE newUnit);
	virtual void OnChangingInSelectDC();
private:
	
};
typedef SYSTEM::CSmartPtr<CComplexFillSymbol> IComplexFillSymbolPtr;
}
#endif 