#pragma once

#include "MapTree.h"
// otMapTreeCtrl.h : CotMapTreeCtrl ActiveX 控件类的声明。


// CotMapTreeCtrl : 有关实现的信息，请参阅 otMapTreeCtrl.cpp。

class CotMapTreeCtrl : public COleControl
{
	DECLARE_DYNCREATE(CotMapTreeCtrl)

// 构造函数
public:
	CotMapTreeCtrl();

// 重写
public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();

// 实现
protected:
	~CotMapTreeCtrl();

	DECLARE_OLECREATE_EX(CotMapTreeCtrl)    // 类工厂和 guid
	DECLARE_OLETYPELIB(CotMapTreeCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CotMapTreeCtrl)     // 属性页 ID
	DECLARE_OLECTLTYPE(CotMapTreeCtrl)		// 类型名称和杂项状态

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
		eventidOnMouseMove = 4L,
		eventidOnMouseUp = 3L,
		eventidOnMouseDown = 2L,
		eventidOnDoubleClick = 1L,
		dispidShowPopMenu =4L,
		dispidHasLine = 3L,
		dispidUpdate = 2L,
		dispidSetFriendControl = 1L
	};

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);


protected:
	void SetFriendControl(IDispatch* MapControl);

	void Update(void);

	VARIANT_BOOL GetHasLine(void);

	void SetHasLine(VARIANT_BOOL newVal);

	VARIANT_BOOL GetShowPopMenu(void);

	void SetShowPopMenu(VARIANT_BOOL newVal);

public:
	/**
	* 触发鼠标双击事件
	* @param button 表示按下的是鼠标哪个键,0代表没有按键，1代表左键，2代表右键,3代表滚轮
	* @param flag 标记值，保留,用于记录键盘一些特殊键的情况
	* @param X 鼠标点的X坐标，客户区坐标系
	* @param Y 鼠标点的Y坐标，客户区坐标系
	* 
	*/
	void FireDoubleClick(LONG button, LONG flag, LONG x, LONG y);


	/**
	* 触发鼠标单击事件
	* @param button 表示按下的是鼠标哪个键,1代表左键，2代表右键,3代表滚轮
	* @param flag 标记值，保留,用于记录键盘一些特殊键的情况
	* @param X 鼠标点的X坐标，客户区坐标系
	* @param Y 鼠标点的Y坐标，客户区坐标系
	* 
	*/
	void FireMouseDown(LONG button, LONG flag, LONG x, LONG y);

	/**
	* 触发鼠标抬起事件
	* @param button 表示按下的是鼠标哪个键,1代表左键，2代表右键,3代表滚轮
	* @param flag 标记值，保留,用于记录键盘一些特殊键的情况
	* @param X 鼠标点的X坐标，客户区坐标系
	* @param Y 鼠标点的Y坐标，客户区坐标系
	* 
	*/
	void FireMouseUp(LONG button, LONG flag, LONG x, LONG y);


	void FireMouseMove(LONG button, LONG flag, LONG x, LONG y);


public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);

private:
	CMapTree m_wndTree;

	//控件指针
	_DotMapControl *m_pMapControl;

	//树的样式是否带虚线
	BOOL  m_hasLine;
};

