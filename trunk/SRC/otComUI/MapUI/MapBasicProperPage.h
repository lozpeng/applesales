#pragma once

#include "resource.h"
#include "Map.h"
// CMapBasicProperPage 对话框

class CMapBasicProperPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CMapBasicProperPage)

public:
	CMapBasicProperPage();
	virtual ~CMapBasicProperPage();

	void SetMap(Carto::CMapPtr pMap);

	BOOL OnInitDialog();

	BOOL  OnApply();


// 对话框数据
	enum { IDD = IDD_PAGE_MAP_BASIC_PROPER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

private:
	CComboBox m_cmbRefScale;

public:
	double m_dbRefScale;
	double m_customScale;

private:
	Carto::CMapPtr m_pMap;
public:
	afx_msg void OnCbnSelchangeComboRefScale();
};
