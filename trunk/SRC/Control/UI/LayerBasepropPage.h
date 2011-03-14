#pragma once


// CLayerBasepropPage 对话框

class CLayerBasepropPage : public CDialog
{
	DECLARE_DYNAMIC(CLayerBasepropPage)

public:
	CLayerBasepropPage(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLayerBasepropPage();

// 对话框数据
	enum { IDD = IDD_LAYERPROP_GENERAL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
