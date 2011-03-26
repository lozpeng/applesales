#pragma once
#include "afxwin.h"
#include "Resource.h"
#include "ILayer.h"
// CRasterPropPage 对话框

class CRasterPropPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CRasterPropPage)

public:
	CRasterPropPage();
	virtual ~CRasterPropPage();

// 对话框数据
	enum { IDD = IDD_RASTER_PROP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CStatic m_wndPropListLocation;
	virtual BOOL OnInitDialog();

	void SetLayer(Carto::ILayer* player);

private:
	Carto::ILayer* m_player;

	CBCGPPropList	m_wndPropList;
};
