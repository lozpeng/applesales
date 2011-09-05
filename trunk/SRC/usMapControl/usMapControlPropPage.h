#pragma once

// usMapControlPropPage.h : CusMapControlPropPage 属性页类的声明。


// CusMapControlPropPage : 有关实现的信息，请参阅 usMapControlPropPage.cpp。

class CusMapControlPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CusMapControlPropPage)
	DECLARE_OLECREATE_EX(CusMapControlPropPage)

// 构造函数
public:
	CusMapControlPropPage();

// 对话框数据
	enum { IDD = IDD_PROPPAGE_USMAPCONTROL };

// 实现
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 消息映射
protected:
	DECLARE_MESSAGE_MAP()
};

