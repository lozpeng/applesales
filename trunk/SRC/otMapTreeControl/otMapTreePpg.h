#pragma once

// otMapTreePpg.h : CotMapTreePropPage 属性页类的声明。


// CotMapTreePropPage : 有关实现的信息，请参阅 otMapTreePpg.cpp。

class CotMapTreePropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CotMapTreePropPage)
	DECLARE_OLECREATE_EX(CotMapTreePropPage)

// 构造函数
public:
	CotMapTreePropPage();

// 对话框数据
	enum { IDD = IDD_PROPPAGE_OTMAPTREECONTROL };

// 实现
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 消息映射
protected:
	DECLARE_MESSAGE_MAP()
};

