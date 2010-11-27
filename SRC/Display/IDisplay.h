#ifndef _IDisplay_h
#define _IDisplay_h
//
#include "DisplayTransformation.h"
#include "CDC.h"
#include "ISymbol.h"
#include <boost/signal.hpp>
#include <boost/signals/connection.hpp>


namespace Display
{

	

class ISymbol;

class DISPLAY_DLL IDisplay// : public SYSTEM::CRef 
{
public:
	IDisplay();
	virtual ~IDisplay();

public:

	SYSTEM::CSmartPtr<IDisplay> Clone();

	//设置是否是制图display
	void SetLayoutDisplay(BOOL bLayoutDis);

	BOOL GetBeLayoutDisplay();
	/**
	* 设置画布
	* @param hDC 画布句柄
	* @param lWidth 画布宽度
	* @param lHeight 画布高度
	*/
	virtual	void SetDC(long hDC, long lWidth, long lHeight );

	/**
	* 设置符号
	* @param pSymbol 智能指针，指向符号
	* @return 若设置成功则返回True
	*/
	virtual BOOL SetSymbol(ISymbol* pSymbol);

	/**
	* 绘制
	* @param pGeometry 几何体
	*/
	virtual void Draw(const GEOMETRY::geom::Geometry* pGeometry);
	/**
	* 绘制
	* @param pEnvelope 矩形
	*/
	virtual void Draw(const GEOMETRY::geom::Envelope* pEnvelope);
	/**
	* 绘制文字
	* @param pEnvelope 文字的位置
	* @param strText 文字
	*/
	virtual DIS_RECT Draw(const GEOMETRY::geom::Envelope* pEnvelope,  const std::string strText, BOOL bScaleWithMap , unsigned int dwDTFormat= DT_NOCLIP | DT_NOPREFIX | DT_LEFT | DT_TOP);
	DIS_RECT Draw(const DIS_RECT* rect,  const std::string strText, BOOL bScaleWithMap, unsigned int dwDTFormat);

	void Draw(void* pObject);
	/**
	* 开始绘制
	* @return 
	*/
	virtual BOOL Begin();

	/**
	* 在开始绘制前，先绘制一些其他
	* @param hDC 画布句柄
	*/
	virtual void OnBeginDraw( long hDC );

	/**
	* 结束绘制 
	*/
	virtual void End();

	/**
	* 在结束绘制之前，先绘制一些其他
	* @param hDC 画布句柄
	*/
	virtual void OnEndDraw( long hDC );

	/**
	* 将多个符号设置到栈中
	* @param ISymbolPtr pSymbol
	*/
	int SetSymbolInStack(ISymbol* pSymbol);

	/**
	* 在绘制中（Begin-End）切换栈中符号
	* @param index 符号索引
	*/
	virtual BOOL SelectStackSymbol(int index);

	/**
	* 获得显示转换
	* @return 若获得成功则返回显示转换
	*/
	CDisplayTransformation& GetDisplayTransformation();

	/**
	* 绘制图例
	* @param pSymbol 符号
	* @param rect 绘制区域
	* @param nFlag 判断显示方式（直线或折线）
	*/
	void DrawLegend(ISymbol* pSymbol, DIS_RECT * rect, int nFlag = 0);

	/**
	* 绘制图例
	* @param pSymbol 符号
	* @param lPosx 绘制区域起始位置x
	* @param lPosy 绘制区域起始位置y
	* @param lWidth 绘制区域宽度
	* @param lHeight 绘制区域高度
	* @param nFlag 判断显示方式（直线或折线）
	*/
	void DrawLegend(ISymbol* pSymbol,long lPosx,long lPosy,long lWidth,long lHeight, int nFlag = 0);

	/**
	* 偏移屏幕内容
	* @param offset_x 偏移位置X
	* @param offset_y 偏移位置Y
	*/
	void OffsetScreen(long offset_x,long offset_y);

	/**
	* 设置背景色
	* @param color 颜色值
	*/
	void SetBgColor( COLORREF color);

	/**
	* 获得颜色值
	* @return 返回颜色值
	*/
	COLORREF GetBgColor();

	/**
	* 绘制背景
	*/
	void DrawBackgroud();

	/**
	* 获得绘制DC
	* @return 若获得成功返回CDC
	*/
	CDC* GetDrawDC();

	//设置绘制缓冲区
	void SetDrawBuffer(DRAW_CONTENT content);

	//刷新显示内存
	void RefreshDisplay(long content);

	//重新设置显示缓冲大小
	void CacheBuffer(long lWidth, long lHeight);

	//设置是否正在打印
	void SetPrinting(BOOL bPrint);

	BOOL GetPrinting(){return m_bPrint;};

	//刷新地理要素贴图
	void UpdateGeography();

	boost::signals::connection RegisterUpdateGeography(boost::function<void ()> fun);

protected:
	
	//
	bool bDraw;
	COLORREF m_BgColor;

	//
	CDisplayTransformation m_cDisplayTransformation;
	Display::CDC* m_pDC;	

	//
	ISymbol* m_pSymbol;
	std::vector<ISymbol*> m_stackpSymbol;

	BOOL m_bLayoutDis;

	BOOL m_bPrint;

	
	
};

typedef SYSTEM::CSmartPtr<IDisplay> IDisplayPtr;

}

#endif