//////////////////////////////////////////////////////////////////////
// 版权(c) 2010-2020, 天地智绘
// 作者：  hhzhao
// 时间：  2010/11/18
// 描述：  数据层的渲染定义，其它地理数据层（栅格、矢量等层）均由其派生
//////////////////////////////////////////////////////////////////////


#ifndef _TEXTSYMBOL_H
#define _TEXTSYMBOL_H
#include "ISymbol.h"
#include "CDC.h"
//#include "DisplayCache.h"

namespace Display{
	class DISPLAY_DLL CTextSymbol : public ISymbol 
	{
	public:

		CTextSymbol();

		virtual ~CTextSymbol();

		CTextSymbol(const CTextSymbol& toTextSymbol);

		CTextSymbol& operator = (const CTextSymbol& toTextSymbol);

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
		// 函数名称   : SelectDC(CDC *pDC)
		// 描述       : 配置笔，刷，字体等
		// 返回类型   : virtual void 
		// 参数       : CDC *pDC   绘制句柄 
		virtual void SelectDC(Display::CDC * pDC);

		// 函数名称   : SetReadyDraw()
		// 描述       : 将selectDC创建所需的绘制句柄装入当前画布，完成绘制前的准备工作
		// 返回类型   : virtual void 
		virtual void SetReadyDraw();


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
		* 设置文字符号的倾斜度
		* @param fAngle 文字的倾斜度
		*/
		virtual void SetAngle(float fAngle);				

		/**
		* 得到文字符号的倾斜度
		* @return 返回文字符号的倾斜度
		*/
		virtual float GetAngle();							

		/**
		* 设置符号的尺寸
		* @param textsize 符号的尺寸
		*/
		virtual void SetTextSize(float textsize);	

		/**
		* 得到符号的尺寸
		* @return 返回符号的尺寸
		*/
		virtual float GetTextSize();				

		/**
		* 设置文字符号颜色
		* @param lColor 文字符号颜色
		*/
		virtual void SetTextColor(unsigned long lColor);	

		/**
		* 得到文字符号颜色
		* @return 返回文字符号的颜色值 
		*/
		virtual unsigned long GetTextColor();		

		/**
		* 设置文字符号颜色
		* @param font 文字符号颜色
		*/
		virtual void SetTextFont(DIS_FONT font);	

		/**
		* 得到文字符号颜色
		* @return 返回文字符号的颜色值 
		*/
		virtual DIS_FONT GetTextFont();	

		/**
		* 设置文字绘制格式信息
		* @return 
		*/
		void SetDrawFormat(unsigned int dwDTFormat);

		/**
		* 设置文字阅读顺序
		* @param bRightToLeft 文字阅读顺序
		*/
		virtual void SetReadDirection(BOOL bRightToLeft);	

		/**
		* 得到文字阅读顺序
		* @return 返回文字阅读顺序 
		*/
		virtual BOOL GetReadDirection();

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

		/**
		* 绘制图例
		* @param rect 绘制区域
		* @param nFlag 判断标识
		*/
		virtual void DrawLegend( DIS_RECT *rect , int nFlag );

		void SetTextPosType(TEXT_POS_TYPE eType);

		TEXT_POS_TYPE GetTextPosType();


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


		virtual void SetFont();



	protected:////子类须继承属性，可以直接使用

		//////////////////////////////////////////////////////////////////////////
		//DISPLAY_HANDLE_NODE* m_hFontHandle;								//存储字体缓存
		//////////////////////////////////////////////////////////////////////////

		long m_lOffsetX;							/**< 符号的偏移量，默认为0*/

		long m_lOffsetY;

		float m_fAngle;								/**< 符号的角度，默认为0,单位角度数*/

		float m_fTextHeight;					/**< 符号大小，默认值且最小值为1*/

		unsigned int m_dwDTFormat;					/**<绘制信息,默认值为DT_NOCLIP | DT_NOPREFIX | DT_LEFT | DT_TOP*/

		DIS_FONT m_font;							/**< 字体信息*/

		BOOL m_bRightToLeft;						/**< 标志阅读顺序，是否从右至左，默认为FALSE*/

		bool m_bMask;								/**< 判断是否绘制外围轮廓，默认false*/

		TEXT_POS_TYPE m_enumTextPosType;

		ISymbolPtr m_pSymbolMask;					/**< 外围轮廓的对象指针*/

		float m_fTextSize;							/**< 内部储存符号尺寸,需要序列化*/
		float m_fOffsetX;
		float m_fOffsetY;
	
	};
	typedef SYSTEM::CSmartPtr<CTextSymbol> CTextSymbolPtr;
}
#endif

