#pragma once

// usLayoutControlCtrl.h : CusLayoutCtrl ActiveX 控件类的声明。


// CusLayoutCtrl : 有关实现的信息，请参阅 usLayoutControlCtrl.cpp。

class CusLayoutCtrl : public COleControl
{
	DECLARE_DYNCREATE(CusLayoutCtrl)

// 构造函数
public:
	CusLayoutCtrl();

// 重写
public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();

// 实现
protected:
	~CusLayoutCtrl();

	DECLARE_OLECREATE_EX(CusLayoutCtrl)    // 类工厂和 guid
	DECLARE_OLETYPELIB(CusLayoutCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CusLayoutCtrl)     // 属性页 ID
	DECLARE_OLECTLTYPE(CusLayoutCtrl)		// 类型名称和杂项状态

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
	};
};

