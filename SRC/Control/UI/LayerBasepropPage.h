#pragma once
#include "resource.h"
#include "ILayer.h"
// CLayerBasepropPage 对话框

class CLayerBasepropPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CLayerBasepropPage)

public:
	CLayerBasepropPage();
	virtual ~CLayerBasepropPage();

// 对话框数据
	enum { IDD = IDD_LAYERPROP_GENERAL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	void SetLayer(Carto::ILayer* player);

    void GetDataSource();
public:
	virtual BOOL OnInitDialog();

private:
	Carto::ILayer* m_player;
	CString m_layername;
	CString m_strSource;
	double m_top;
	double m_left;
	double m_right;
	double m_bottom;
};
