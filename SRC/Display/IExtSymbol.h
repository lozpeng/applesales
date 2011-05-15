#ifndef IEXTSYMBOL_H
#define IEXTSYMBOL_H
#include "ISymbol.h"
#include "alm.h"
#include "DisplayCache.h"
#include "ICursor.h"
#include "PropRecordIndexGroup.h"
namespace Display{
	/**扩展符号
	*/
class DISPLAY_DLL IExtSymbol : public Display::ISymbol
{
public:
	IExtSymbol(void);
	virtual ~IExtSymbol(void);

	IExtSymbol(const IExtSymbol& extSymbol);

	IExtSymbol& operator = (const IExtSymbol& extSymbol);

   /**
    * 验证属性流的有效性
	* @param recordset 记录集
	* @param &exchangInfo
	* @return 若属性流有效则返回True
	*/
	virtual bool ValidatePropValueAndGetInfo(Geodatabase::ICursorPtr pCursor , CPropRecordIndexGroup &exchangInfo) = 0;

   /**
    * 将属性流分配给符号属性
	* @param propValueStream 属性流
	*/
	//virtual b SetPropValue(void *propValueStream) = 0;取消使用，由具体扩展符号自行处理数据装入，因为draw 方法中无法约束是否使用此方法

   /**
    * 得到扩展符号的描述
	* @return 返回扩展符号的描述
	*/
	virtual const std::string GetDescription();

   /**
    * 获得符号名称
	* @return 返回符号的名称
	*/
	virtual const std::string GetSymbolName();

   /**
    * 装配画布,通过画布初始化符号
	* @param pDC 绘制图形的画布 
	*/
	virtual void SelectDC(Display::CDC *pDC);

   /**
    * 清除画布
	*/
	virtual void ClearDC();

   /**
    * 序列化操作
	* @param ar 文档流
	*/
	virtual void serialization(SYSTEM::IArchive & ar);

   /**
    * 设置属性
	* @param PropertyName 属性名称
	* @param PropertyValue 属性值
	*/
	virtual void SetProperties(const char* PropertyName , const _variant_t& PropertyValue);
	/**
	* 根据属性名称获得属性值
	* @param PropertyName 属性名称
	* @return 返回属性值
	*/
	virtual _variant_t GetProperties(const char* PropertyName);	

   /**
    * 根据比例进行符号缩放
	* @param rate 比例
	*/
	virtual void Zoom(float rate);
protected:

   /**
    * 实现新旧单位之间的转换
	* @param oldUnit 新单位
	* @param newUnit 旧单位
	*/
	virtual void OnUnitChanged(SYSTEM::SYS_UNIT_TYPE oldUnit , SYSTEM::SYS_UNIT_TYPE newUnit);

   /**
    * 在SelectDC中调用，改变符号单位，将float值转化为long型值，浮点型数据转成屏幕像素数据
	*/
	virtual void OnChangingInSelectDC();
protected:
	/** 
	 * 符号描述
	 */
	std::string m_sDescription;
	/** 
	 * 符号名称
	 */
	std::string m_sSymbolName;	
};

typedef SYSTEM::CSmartPtr<IExtSymbol> IExtSymbolPtr;
}
#endif