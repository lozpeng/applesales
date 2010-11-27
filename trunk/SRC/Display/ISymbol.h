#ifndef _ISymbol_h
#define _ISymbol_h

#include "ISerialization.h"
#include "SmartPtr.h"
#include "SystemUnit.h"

namespace Display
{
	class CDC;
	class DISPLAY_DLL ISymbol: public SYSTEM::ISerialization
	{

	public:
		ISymbol();
		ISymbol(const ISymbol& Symbol);
		virtual ~ISymbol();
	public:
	/**
	* 根据比例进行符号缩放
	* @param rate 缩放比例
	*/
	virtual void Zoom(float rate);

	/**
	* 绘制，抽象方法，子类须实现
	* @param pObject 
	*/
	virtual void Draw(void* pObject) = 0;

	/**
	* 获得各种符号类型
	* @return 若存在则返回符号类型
	*/
	virtual SYMBOL_TYPE GetType() = 0;

	/**
	* 装配画布,通过画布初始化符号
	* @param pDC 画布
	*/
	virtual void SelectDC(Display::CDC *pDC)=0;

	/**
	* 将selectDC创建所需的绘制句柄装入当前画布，完成绘制前的准备工作
	*/
	virtual void SetReadyDraw()=0;

	/**
	* 清除画布
	*/
	virtual void ClearDC();

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
	virtual void DrawLegend( DIS_RECT *rect , int nFlag )=0;

	/**
	* 得到ID号 
	* @return 返回ID号
	*/
	long GetID();

	/**
	* 设置ID号
	* @param lID 符号标识
	*/
	void SetID(long lID);

	/**
	* 得到符号卷标
	* @return 获得符号卷标
	*/
	std::string GetLabel();

	/**
	* 设置符号卷标
	* @param strLabel 符号卷标
	*/
	void SetLabel(const char* strLabel);

	/** 
	* 复制一个符号
	* @return 若复制成功则返回一个符号
	*/
	SYSTEM::CSmartPtr<ISymbol> Clone();

	/**
	* 获得颜色值
	* @return 返回颜色值
	*/
	COLORREF GetColor();

	/**
	* 设置颜色值
	* @param color 颜色值
	*/
	void SetColor( COLORREF color );

	/**
	* 获得符号单位
	* @return 返回符号单位
	*/
	SYSTEM::SYS_UNIT_TYPE GetUnit();

	/**
	* 设置符号单位
	* @param SYS_UNIT_TYPE 符号单位
	*/
	void SetUnit(SYSTEM::SYS_UNIT_TYPE  unitType);

	/**
	* 外部调用，传进一个原始值，获得目标单位对应的值
	* @param valUnit
	* @param aimUnit
	* @param float val
	*/
	float UnitChangeTo(SYSTEM::SYS_UNIT_TYPE valUnit , SYSTEM::SYS_UNIT_TYPE aimUnit , float val);

	/**
	* 在SelectDC中调用，将float值转化为long型值
	* @param Unit 单位
	* @param Val
	*/
	long UnitChange( SYSTEM::SYS_UNIT_TYPE Unit , float Val );

	/**
	* 序列化操作
	* @param ar 文档流
	*/
	virtual void serialization(SYSTEM::IArchive &ar)=0;

	CDC* GetDC(){return m_pDC;};

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

	/**
	* 获得像素和毫米之间的比例
	* @return 返回像素和毫米之间的比例
	*/
	float GetRateOfPixelAndMM();
	protected:
		Display::CDC*	m_pDC;

		long m_lID;

		std::string m_strLabel;

		COLORREF m_lColor;

		SYSTEM::SYS_UNIT_TYPE m_enumUnit;	

	};
	typedef SYSTEM::CSmartPtr<ISymbol> ISymbolPtr;
}
#endif