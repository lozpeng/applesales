#pragma once
#include "InternalControl.h"
// usMapControlCtrl.h : CusMapCtrl ActiveX 控件类的声明。


// CusMapCtrl : 有关实现的信息，请参阅 usMapControlCtrl.cpp。

class CusMapCtrl : public COleControl
{
	DECLARE_DYNCREATE(CusMapCtrl)

// 构造函数
public:
	CusMapCtrl();

// 重写
public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();

// 实现
protected:
	~CusMapCtrl();

	DECLARE_OLECREATE_EX(CusMapCtrl)    // 类工厂和 guid
	DECLARE_OLETYPELIB(CusMapCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CusMapCtrl)     // 属性页 ID
	DECLARE_OLECTLTYPE(CusMapCtrl)		// 类型名称和杂项状态

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
		dispidRefresh = 2L,
		dispidAddShpfile = 1L

	};
protected:
	

private:
	CInternalControl m_MapControl;
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
protected:
	void AddShpfile(LPCTSTR filename);
	void Refresh(void);
};

