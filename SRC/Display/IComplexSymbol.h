/************************************************************************/
/*作者：张维
描述：复合符号接口
版本号：1.0
创建日期：2007-6-14 下午06:16:45                                                                      */
/************************************************************************/

#pragma once

#include "IArchive.h"
#include "alm.h"
#include "ISerialization.h"
#include "SymbolArray.h"
#include "ISymbol.h"
namespace Display{
	class DISPLAY_DLL IComplexSymbol : virtual public ISymbol/*public SYSTEM::CRef , public SYSTEM::ISerialization */
{
public:
	IComplexSymbol(void);

	~IComplexSymbol(void);

	IComplexSymbol(const IComplexSymbol& ComplexSymbol);

	IComplexSymbol& operator = (const IComplexSymbol& ComplexSymbol);	

   /**
    * 添加符号加入
	* @param Symbol 符号指针
	* @return 若添加成功则返回true，否则为false
	*/
	virtual bool Add(ISymbolPtr Symbol) = 0;							

   /**
    * 设置符号是否可见
	* @param index 符号索引
	* @param visible 是否可见
	*/
	virtual void SetSymbolVisible( int index , bool visible );			

   /**
    * 判断是否可见
	* @param index 符号索引
	* @return 
	*/
	virtual bool IsVisible(int index);									

   /**
    * 删除加入的符号,根据索引号
	* @param index 符号的索引
	*/
	virtual void RemoveSymbol(int index);								

   /**
    * 根据索引号设置是否加锁
	* @param index 索引号
	* @param bool bLock = false 设置	是否加锁，默认false为不加锁
	* @return 
	*/
	virtual void LockSymbol( int index , bool bLock = false);			

   /**
    * 根据索引得到符号指针
	* @param index 索引号
	* @return 若存在，则返回
	*/
	virtual ISymbolPtr GetAt(int index);								

   /**
    * 根据索引号得到符号是否加锁了
	* @param index 索引号
	* @return 若加锁则返回为true，否则为false
	*/
	virtual bool IsLocked(int index);										

   /**
    * 得到加入的符号个数
	* @return 返回加入符号的个数 
	*/
	virtual int GetSize();													

   /**
    * 从第index位置开始插入一个符号
	* @param index 索引号
	* @param symbol 符号
	* @param bVisible 符号是否可见
	* @return 
	*/
	virtual bool Insert( int index , ISymbolPtr symbol , bool bVisible ) = 0; 

   /**
    * 交换符号顺序
	* @param posX X坐标
	* @param posY Y坐标
	* @return 
	*/
	virtual bool ExchangeOrder( int posX , int posY );					

   /**
    * 修改索引号对应的符号
	* @param index 索引号
	* @param symbol 智能指针，指向符号
	* @return 若设置成功则返回true，否则为false
	*/
	virtual bool SetSymbol( int index , ISymbolPtr symbol ) = 0;

	/**
	* 绘制图例
	* @param rect 绘制区域
	* @param nFlag 判断标识
	*/
	virtual void DrawLegend( DIS_RECT * rect , int nFlag );

	/**
	* 清除DC
	*/
	virtual void ClearDC();


	void SetReadyDraw(){};

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

public:

	virtual void serialization(SYSTEM::IArchive &ar);
protected:

	ISymbolArrayPtr  m_arrayGroup;					//初始一个CArray数组,用于储存符号的指针
	SYSTEM::CArray<bool>	m_arrayLock;						//初始一个储存符号是否可设颜色的锁
	SYSTEM::CArray<bool>	m_arrayView;						//初始化符号可见不可见
};
typedef SYSTEM::CSmartPtr<IComplexSymbol> IComplexSymbolPtr;
}