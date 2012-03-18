#pragma once

// otMapPpg.h : CotMapPropPage 属性页类的声明。


// CotMapPropPage : 有关实现的信息，请参阅 otMapPpg.cpp。

class CotMapPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CotMapPropPage)
	DECLARE_OLECREATE_EX(CotMapPropPage)

// 构造函数
public:
	CotMapPropPage();

// 对话框数据
	enum { IDD = IDD_PROPPAGE_OTMAPCONTROL };

// 实现
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 消息映射
protected:
	DECLARE_MESSAGE_MAP()
};

