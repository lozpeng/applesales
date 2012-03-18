#pragma once

#include "IAction.h"
#include <Map.h>
#include <IDisplay.h>

namespace Carto
{
	class CMap;
}

enum SERIEALIZE_TYPE
{
	SERIEALIZE_NONE = 0x00, //
	SERIEALIZE_MAP = 0x01,  //不带ELEMENT的MAP
	SERIEALIZE_LAYOUT= 0x02,//出图整饰元素 
	SERIEALIZE_MAPELEMENT= 0x03,//地图ELEMNT
	SERIEALIZE_ALL = 0x04		//全部输出
};

class CotMapCtrl : public COleControl
{
	DECLARE_DYNCREATE(CotMapCtrl)

// 构造函数
public:
	CotMapCtrl();

// 重写
public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();

// 实现
protected:
	~CotMapCtrl();

	DECLARE_OLECREATE_EX(CotMapCtrl)    // 类工厂和 guid
	DECLARE_OLETYPELIB(CotMapCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CotMapCtrl)     // 属性页 ID
	DECLARE_OLECTLTYPE(CotMapCtrl)		// 类型名称和杂项状态

// 消息映射
	DECLARE_MESSAGE_MAP()

// 调度映射
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// 事件映射
	DECLARE_EVENT_MAP()



// 调度和事件 ID
public:
	enum {
		dispidStopFlashLayer = 27L,
		dispidFlashLayer = 26L,
		dispidSaveElement = 25L,
		dispidRemoveElement = 24L,
		dispidLoadElementFile = 23L,
		dispidOutputMapToFile = 22L,
		dispidOutputMap = 21L,
		dispidMoveCenterTo = 20L,
		dispidPixelToMap = 19L,
		dispidMapToPixel = 18L,
		dispidMouseIcon = 17,
		dispidMouseType = 16,
		dispidLoadGWF = 15L,
		dispidRefreshScreen = 14L,
		dispidScreenCanvas = 13,
		dispidUpdateContent = 12L,
		dispidAddShpFile = 11L,
		eventidOnMouseMove = 4L,
		eventidOnMouseUp = 3L,
		eventidOnMouseDown = 2L,
		eventidOnDoubleClick = 1L,
		dispidFullExtent = 10,
		dispidViewExtent = 9,
		dispidObject =8,
		dispidMap = 7,
		dispidMoveMap = 6L,
		dispidAddImageFile = 5L,
		dispidAddTmsFile = 4L,
		dispidAction = 3,
		dispidAddFeatureLayer =1L,
		dispidRefresh         =2L,
	};
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

    
public:

	otActionType GetAction(void);

	void SetAction(otActionType newVal);

	//添加矢量图层
	afx_msg void AddFeatureLayer(BSTR filename);

	//打开TMS文件，并添加到Map中
	afx_msg void AddTmsFile(BSTR filename);

	//打开影像文件，并添加到Map中
	VARIANT_BOOL AddImageFile(BSTR filename);

	//刷新地图的所有内容
	afx_msg void Refresh();

	//移动地图
	void MoveMap(DOUBLE dx, DOUBLE dy);

	afx_msg IGeoMap* GetMap(void);

	//得到控件内部的接口
	afx_msg IDispatch* GetObject();


	//得到和设置视图区的地理范围
	IotEnvelope* GetViewExtent(void);
	void SetViewExtent(IotEnvelope* pVal);


	/**
	* 得到整个地图的范围
	*/
	IotEnvelope* GetFullExtent(void);

    //打开shp文件，并添加到Map中
	void AddShpFile(LPCTSTR filename);

	//更新地图的内容
	void UpdateContent(otDrawContent content);

	//得到屏幕Display
	IotCanvas* GetScreenCanvas(void);

	void RefreshScreen();

	//加载工程文件
	void LoadGWF(LPCTSTR filename);

	//设置鼠标光标类型
	otMouseType GetMouseType(void);
	void SetMouseType(otMouseType newVal);

	void SetMouseIcon(LPCTSTR newVal);

	void MapToPixel(DOUBLE mapX, DOUBLE mapY, LONG* X, LONG* Y);

	IotPoint* PixelToMap(LONG x, LONG y);
	void MoveCenterTo(IotPoint* point);

	//绘制屏幕内容到指定DC上
	void OutputMap(LONG hDC);

	//绘制屏幕内容到文件
	VARIANT_BOOL OutputMapToFile(LPCTSTR filename, otOutputFileType filetype);

	//加载图元文件
	void LoadElementFile(LPCTSTR filename);

	//删除图元
	void RemoveElement(void);

public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();

public:

	

	//移动地图内容
	 void OffsetClient(long offset_x, long offset_y);

	 //设置光标
	 void SetCursorType(long lCursorType) { m_lCursorType=lCursorType;}	

public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
protected:
	

private:
	//
	IGeoMapPtr m_potGeoMap;
	//内部存储的地图对象
	Carto::CMapPtr m_pGeomap;

	//唯一的otGeomap指针
	IGeoMap *m_pMapInterface;

	//客户区DC
	HDC m_hClientDC;
	//绘制的内存DC
	HDC m_hMemDC;

	//当前的动作
	IAction *m_pCurAction;

	otActionType m_ActionType;

	//控件的背景色
	COLORREF m_BgColor;

	//控件窗口大小
	long m_lSizeX;
	long m_lSizeY;

	long m_lCursorType;

	//边框的大小
	int m_nBorderSize;

	//屏幕Display
	Display::IDisplayPtr m_pScreenDisplay;

	double m_dblScale;
	bool m_bTimer;
	GEOMETRY::geom::Envelope m_srcEnvelop; //记录内存DC的地理范围
	double   m_srcScale;
	bool m_bMouseWheel;

    //鼠标光标类型
    otMouseType   m_mouseType;

	//自定义鼠标光标
	HCURSOR       m_CustomCursor;
    

	int m_FlashLayerId;
    
protected:


	/**
	* 触发鼠标双击事件
	* @param button 表示按下的是鼠标哪个键,0代表没有按键，1代表左键，2代表右键,3代表滚轮
	* @param flag 标记值，保留,用于记录键盘一些特殊键的情况
	* @param X 鼠标点的X坐标，客户区坐标系
	* @param Y 鼠标点的Y坐标，客户区坐标系
	* @param MapX 鼠标点的X坐标，地图坐标系
	* @param MapY 鼠标点的Y坐标，地图坐标系
	* 
	*/
	void FireDoubleClick(LONG button, LONG flag, LONG X, LONG Y, DOUBLE MapX, DOUBLE MapY);

	
	/**
	* 触发鼠标单击事件
	* @param button 表示按下的是鼠标哪个键,1代表左键，2代表右键,3代表滚轮
	* @param flag 标记值，保留,用于记录键盘一些特殊键的情况
	* @param X 鼠标点的X坐标，客户区坐标系
	* @param Y 鼠标点的Y坐标，客户区坐标系
	* @param MapX 鼠标点的X坐标，地图坐标系
	* @param MapY 鼠标点的Y坐标，地图坐标系
	* 
	*/
	void FireMouseDown(LONG button, LONG flag, LONG x, LONG y, DOUBLE mapX, DOUBLE mapY);
	
	/**
	* 触发鼠标抬起事件
	* @param button 表示按下的是鼠标哪个键,1代表左键，2代表右键,3代表滚轮
	* @param flag 标记值，保留,用于记录键盘一些特殊键的情况
	* @param X 鼠标点的X坐标，客户区坐标系
	* @param Y 鼠标点的Y坐标，客户区坐标系
	* @param MapX 鼠标点的X坐标，地图坐标系
	* @param MapY 鼠标点的Y坐标，地图坐标系
	* 
	*/
	void FireMouseUp(LONG button, LONG flag, LONG x, LONG y, DOUBLE mapX, DOUBLE mapY);


	void FireMouseMove(LONG button, LONG flag, LONG x, LONG y, DOUBLE mapX, DOUBLE mapY);

private:
	void serialization(SYSTEM::IArchive &ar,SERIEALIZE_TYPE sType);
	
	//计算要贴的图在memDC上的位置
	void CalSrcRect(GEOMETRY::geom::Envelope extent,CRect &rect);
	//计算贴图在view中的位置
	void CalDestRect(GEOMETRY::geom::Envelope srcExtent,GEOMETRY::geom::Envelope destExtent,CRect &rect);

protected:
	void SaveElement(LPCTSTR filename);
	public:
	void FlashLayer(LONG layerID, LONG millisecond);
	void StopFlashLayer(void);
};

