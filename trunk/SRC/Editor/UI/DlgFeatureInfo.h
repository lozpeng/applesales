#pragma once
#include "Map.h"
#include "FeatureLayer.h"
#include "resource.h"
#include "IMapCtrl.h"
class CDlgFeatureInfo : public CDialog
{
	DECLARE_DYNAMIC(CDlgFeatureInfo)

public:
	CDlgFeatureInfo(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgFeatureInfo();

// 对话框数据
	enum { IDD = IDD_FEATURE_INFOMATION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnTvnSelchangedTreeFeatures(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL OnInitDialog();

	void SetMap(Carto::CMap* pMap);

	//刷新显示
	void Refresh();

	BOOL Create();

public:
	CTreeCtrl m_Features;
	CListCtrl m_FeatureInfo;

	Carto::CMap *m_pMap;

	std::vector<Carto::IFeatureLayerPtr> m_layers;
	
	afx_msg void OnClose();


	Framework::IMapCtrl *m_pMapCtrl;
};
