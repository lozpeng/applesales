#pragma once
#include "workflowWizardInclude.h"

#include "MapControl.h"
#include "afxwin.h"
#include <map>
#include <string>

// CDistillStep1 对话框

class CDistillStep1 : public CResizablePage,
   public TreePropSheet::CWhiteBackgroundProvider
{
	DECLARE_DYNAMIC(CDistillStep1)

public:
	CDistillStep1(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDistillStep1();

// 对话框数据
	enum { IDD = IDD_DISTILL_STEP1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonPolygon();
public:
	void	SetMapControl(Control::CMapControl* pMapControl){m_pMapControl = pMapControl;};
protected:
	Control::CMapControl*			     m_pMapControl;
	std::map<int, Carto::ILayerPtr>      m_mapIndexLyrs;
public:
	CComboBox m_ctlComboLyr;
	virtual BOOL OnInitDialog();
	int DoWork();
};
