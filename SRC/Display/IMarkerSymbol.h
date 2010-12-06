//////////////////////////////////////////////////////////////////////
  // 版权(c) 2010-2020, 天地智绘
  // 作者：  hhzhao
  // 时间：  2008/11/18
  // 描述：  点符号接口类
//////////////////////////////////////////////////////////////////////

#ifndef IMARKER_SYMBOL_H
#define IMARKER_SYMBOL_H

#include "ISymbol.h"
#include "IArchive.h"

namespace Display{
class  CSymbolMask;
class  CComplexMarkerSymbol;

/** @interface */
/** 
 * 点符号接口
 */
class DISPLAY_DLL IMarkerSymbol: virtual public ISymbol
{

friend class CSymbolMask;
friend class CComplexMarkerSymbol;

public:

	IMarkerSymbol();

	virtual ~IMarkerSymbol();

	IMarkerSymbol(const IMarkerSymbol& MarkSymbol);

	IMarkerSymbol& operator = (const IMarkerSymbol& MarkSymbol);

	/**
	* 设置属性
	* @param PropertyName 属性名称
	* @param PropertyValue 属性值
	*/
	virtual void SetProperties(const char* PropertyName , const _variant_t& PropertyValue);
	
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
	virtual void DrawLegend(DIS_RECT *rect,int nFlag);

	/**
	* 根据比例进行符号缩放
	* @param rate 缩放比例
	*/
	virtual void Zoom(float rate);				

	/**
	* 获得各种符号类型
	* @return 若存在则返回符号类型
	*/
	SYMBOL_TYPE GetType();						

   /**
    * 设置点符号的偏移量
	* @param x x偏移量
	* @param y y偏移量
	*/
	virtual void SetOffSet(float x , float y);				

   /**
    *得到点符号的x偏移量
	* @return 返回点符号的x偏移量
	*/
	virtual float GetOffsetX();							

   /**
    * 得到点符号的y偏移量
	* @return 返回点符号的x偏移量
	*/
	virtual float GetOffsetY();			

   /**
    * 设置点符号的弧度
	* @param fAngle 点符号的弧度
	*/
	virtual void SetAngle(float fAngle);				

   /**
    * 得到点符号的弧度
	* @return 返回点符号的弧度
	*/
	virtual float GetAngle();							

   /**
    * 设置符号的尺寸
	* @param marksize 符号的尺寸
	*/
	virtual void SetMarkerSize(float marksize);	

   /**
    * 得到符号的尺寸
	* @return 返回符号的尺寸
	*/
	virtual float GetMarkerSize();				

   /**
    * 设置是否绘制外围轮廓
	* @param bMask 判断是否绘制外围轮廓
	*/
	virtual void SetMaskDrawable(bool bMask);			

   /**
    * 得到是否绘制外围轮廓的设置
	* @return 若返回true，则绘制外围轮廓的设置，否则为false
	*/
	virtual bool GetMaskDrawable();						

   /**
    * 装入外围轮廓指针
	* @param pSymbolMask 外围轮廓指针
	*/
	virtual void SetMask(ISymbolPtr pSymbolMask);		

   /**
    * 得到外围轮廓指针
	* @return 若存在，则返回外围轮廓指针，否则返回为NULL
	*/
	virtual ISymbolPtr GetMask();						

   /**
    * 设置点符号颜色
	* @param lColor 点符号颜色
	*/
	virtual void SetMarkerColor(unsigned long lColor);	

   /**
    * 得到点符号颜色
	* @return 返回点符号的颜色值 
	*/
	virtual unsigned long GetMarkColor();				

   /**
    * 绘制
	* @param pObject 符号对象
	*/
	virtual void Draw(void* pObject);

   /**
    * 序列化操作
	* @param ar 档案文件流
	*/
	virtual void serialization(SYSTEM::IArchive & ar);
	
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
	
	long m_lOffsetX;							/**< 符号的偏移量，默认为0*/

	long m_lOffsetY;

	float m_fAngle;								/**< 符号的角度，默认为0,单位角度数*/

	unsigned long m_lMarkerSize;					/**< 符号大小，默认值且最小值为1*/

	bool m_bMask;								/**< 判断是否绘制外围轮廓，默认false*/

	ISymbolPtr m_pSymbolMask;					/**< 外围轮廓的对象指针*/

	float m_fMarkerSize;							/**< 内部储存符号尺寸,需要序列化*/
	float m_fOffsetX;
	float m_fOffsetY;
};

typedef SYSTEM::CSmartPtr<IMarkerSymbol> IMarkerSymbolPtr;
}
#endif //IMarkerSymbol_H
