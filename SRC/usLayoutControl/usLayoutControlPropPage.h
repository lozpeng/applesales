#pragma once

// usLayoutControlPropPage.h : CusLayoutControlPropPage 属性页类的声明。


// CusLayoutControlPropPage : 有关实现的信息，请参阅 usLayoutControlPropPage.cpp。

class CusLayoutControlPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CusLayoutControlPropPage)
	DECLARE_OLECREATE_EX(CusLayoutControlPropPage)

// 构造函数
public:
	CusLayoutControlPropPage();

// 对话框数据
	enum { IDD = IDD_PROPPAGE_USLAYOUTCONTROL };

// 实现
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 消息映射
protected:
	DECLARE_MESSAGE_MAP()
};

