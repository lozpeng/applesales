//////////////////////////////////////////////////////////////////////
  // 版权(c) 2010-2020, 天地智绘
  // 作者：  hhzhao
  // 时间：  2008/11/18
  // 描述：  线符号接口类
//////////////////////////////////////////////////////////////////////

#ifndef ILINESYMBOL_H
#define ILINESYMBOL_H

#include "ISymbol.h"

namespace Display{

/** @interface */
/** 
 *线符号接口
 */
class DISPLAY_DLL ILineSymbol : virtual public ISymbol 
{
public:
	ILineSymbol();

	virtual ~ILineSymbol();

	ILineSymbol(const ILineSymbol& toLineSymbol);

	ILineSymbol& operator = (const ILineSymbol& toLineSymbol);

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
    * 设置线宽
	* @param nWidth 线宽
	* @return 
	*/
	virtual void SetLineWidth(float nWidth);				

   /**
    * 得到线宽
	* @return 返回线宽 
	*/
	virtual float GetLineWidth();							

   /**
    * 设置线符号颜色
	* @param lColor 线符号的颜色值
	*/
	virtual void SetLineColor(unsigned long lColor);				

   /**
    * 得到线符号颜色
	* @return 返回线符号颜色值
	*/
	virtual unsigned long GetLineColor();							

   /**
    * 设置线符号的偏移量
	* @param float x
	* @param float y
	* @return 
	*/
	virtual void SetOffset(float x , float y);							

   /**
    * 得到线符号的x偏移量
	* @return 返回线符号的x偏移量 
	*/
	virtual float GetOffsetX();										

   /**
    * 得到线符号的y偏移量
	* @return 返回线符号的y偏移量
	*/
	virtual float GetOffsetY();										

	/**
	* 绘制图例
	* @param rect 绘制区域
	* @param nFlag 判断标识
	*/
	virtual void DrawLegend( DIS_RECT * rect,int nFlag );				

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
protected:////子类须继承属性，可以直接使用

	unsigned long  m_lLineWidth;									/**< 线宽*/

	long m_lOffsetX;

	long m_lOffsetY;
	
	float m_fLineWidth;
	float m_fOffsetX;
	float m_fOffsetY;
public:

   /**
    * 序列化操作
	* @param ar 档案文件流
	*/
	virtual void serialization(SYSTEM::IArchive & ar);
};

typedef SYSTEM::CSmartPtr<ILineSymbol> ILineSymbolPtr;

}

#endif //ILINESYMBOL_H
