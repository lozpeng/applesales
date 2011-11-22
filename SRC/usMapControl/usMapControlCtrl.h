#pragma once
#include "InternalControl.h"
#include "ICommand.h"
#include "ITool.h"


// CusMapCtrl : 有关实现的信息，请参阅 usMapControlCtrl.cpp。

class CusMapCtrl : public COleControl,public Framework::IMapCtrl
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
		dispidCurTool = 3,
		dispidRefresh = 2L,
		dispidAddShpfile = 1L

	};
protected:
	


public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
protected:
	void AddShpfile(LPCTSTR filename);
	void Refresh(void);

private:
	Framework::ITool* GetTool(usToolType tooltype);

private:
	//当前工具
	Framework::ITool* m_pCurTool;

	usToolType m_Tooltype;
protected:
	usToolType GetCurTool(void);
	void SetCurTool(usToolType newVal);
};

