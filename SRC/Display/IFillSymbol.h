//////////////////////////////////////////////////////////////////////
  // 版权(c) 2010-2020, 天地智绘
  // 作者：  hhzhao
  // 时间：  2008/11/19
  // 描述：  面符号接口类
//////////////////////////////////////////////////////////////////////

#ifndef IFILLSYMBOL_H
#define IFILLSYMBOL_H
#include "ISymbol.h"
#include "ILineSymbol.h"


namespace Display{

/** @interface */
/** 
*面符号接口
*/
class DISPLAY_DLL IFillSymbol : virtual public ISymbol 
{
public:
	IFillSymbol();

	virtual ~IFillSymbol();

	IFillSymbol(const IFillSymbol& FillSymbol);

	IFillSymbol& operator = (const IFillSymbol& FillSymbol);

	/**
	* 获得各种符号类型
	* @return 若存在则返回符号类型
	*/
	virtual SYMBOL_TYPE GetType();												

	/**
	* 根据比例进行符号缩放
	* @param rate 缩放比例
	*/
	virtual void Zoom(float rate);												

   /**
    * 设置边界线的颜色
	* @param lColor 边界线颜色值
	*/
	virtual void SetOutLineColor(unsigned long lColor);									//设置线的颜色

   /**
    * 获得边界线的颜色
	* @return 返回边界线颜色值
	*/
	virtual unsigned long GetOutLineColor();											//得到线的颜色

   /**
    * 设置填充颜色
	* @param lColor 颜色值
	*/
	virtual void SetFillColor(unsigned long lColor);									//设置填充颜色

   /**
    * 得到填充颜色
	* @return 返回填充色
	*/
	virtual unsigned long GetFillColor();												//得到填充颜色
	
	/**
	* 设置是否绘制填充区
	* @param bFill 判断是否绘制填充区
	*/
	virtual void SetDrawFill(bool bFill);												

	/**
	* 得到是否绘制填充区
	* @return 若绘制填充区则返回true，否则返回false
	*/
	virtual bool GetDrawFill();	
   /**
    * 设置边界线的宽度
	* @param size 边界线的宽度
	*/
	virtual void SetOutLineWidth(float size);											//设置线的宽度

   /**
    * 得到线的宽度
	* @return 返回线的宽度
	*/
	virtual float  GetOutLineWidth();													//得到线的宽度

   /**
    * 设置边界线指针
	* @param mOutLine 边界线符号指针
	*/
	virtual void SetOutLineSymbol(ILineSymbolPtr mOutLine);								    //设置线指针

   /**
    * 获得边界线的指针
	* @return 返回边界线符号指针
	*/
	ILineSymbolPtr GetOutLineSymbol();

   /**
    * 设置是否绘制边界线
	* @param bline 判断是否绘制边界线
	*/
	virtual void SetDrawOutLine(bool bline);												

   /**
    * 得到是否绘制线
	* @return 若绘制线则返回true，否则返回false
	*/
	virtual bool GetDrawOutLine();	

	
	
	/**
	* 设置属性
	* @param PropertyName 属性名称
	* @param PropertyValue 属性值
	*/
	virtual void SetProperties( const char* PropertyName , const _variant_t& PropertyValue);

	/**
	* 获得属性值
	* @param PropertyName 属性名称
	*/
	virtual _variant_t GetProperties(const char* PropertyName);					

	/**
	* 绘制图例
	* @param rect 绘制区域
	* @param nFlag 判断标识
	*/
	virtual void DrawLegend( DIS_RECT * rect , int nFlag );						

	/**
	* 绘制
	* @param pObject 符号对象
	* @return 
	*/
	virtual void Draw(void* pObject);

	/**
	* 清除DC
	*/
	virtual void ClearDC();
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

	bool m_bOutLine;															/**< 是否绘制边界线*/

	unsigned long m_lRgnID;														/**< Rgn ID 有问题*/

	ILineSymbolPtr m_OutLineSymbol;													/**< 线对象指针*/

protected:

	void DrawOutLine(DIS_POLYGON *pDIS_POLYGON);									    /**< 画线*/

	void DrawOutLine(DIS_RECT *pDIS_RECT);

	void DrawOutLine(DIS_CIRCLE *pCircle);

	void DrawOutLine(DIS_ELLIPSE *pEllipse);

	void DrawOutLine(DIS_ARCPOLYGON *pPolygon);

	int GetSquare(DIS_RECT * rc );													/**< 得到外接正方形*/
public:

	/**
	* 序列化操作
	* @param ar 档案文件流
	*/
    virtual void serialization(SYSTEM::IArchive & ar);
};

typedef SYSTEM::CSmartPtr<IFillSymbol> IFillSymbolPtr;
}
#endif //IFILLSYMBOL_H
