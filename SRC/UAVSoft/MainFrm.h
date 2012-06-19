// MainFrm.h : interface of the CMainFrame class
//


#pragma once
#include "WorkSpaceBar.h"
#include "WorkSpaceBar2.h"
#include "OutputBar.h"

class CMainFrame : public CBCGPFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	
// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnAppLook(UINT id);
	afx_msg void OnUpdateAppLook(CCmdUI* pCmdUI);
	afx_msg LRESULT OnRibbonCustomize (WPARAM wp, LPARAM lp);
	afx_msg void OnToolsOptions();
	afx_msg void OnViewWorkspace();
	afx_msg void OnUpdateViewWorkspace(CCmdUI* pCmdUI);
	/*afx_msg void OnViewWorkspace2();
	afx_msg void OnUpdateViewWorkspace2(CCmdUI* pCmdUI);*/
	/*afx_msg void OnViewOutput();
	afx_msg void OnUpdateViewOutput(CCmdUI* pCmdUI);*/
	DECLARE_MESSAGE_MAP()

	BOOL CreateRibbonBar ();
	void ShowOptions (int nPage);

	afx_msg void OnUpdatePosMap(CCmdUI *pCmdUI);

public:
    Framework::IMaptreeCtrl* GetTOC();

	void		AddMainCategory();
	void		AddTab_MapControl();
	void		AddTab_Mesure();
	//编辑模块
	void		AddTab_Editor();
	//地理要素提取
	void        AddTab_GeoInfoExtract();
	//制图
	void        AddTab_Print();

	void        UpdateStatusInfo(CString info);

public:

	CBCGPRibbonStatusBar	m_wndStatusBar;
	CBCGPRibbonBar			m_wndRibbonBar;
	CBCGPRibbonMainButton	m_MainButton;
	CBCGPToolBarImages		m_PanelImages;
	CBCGPMenuBar			m_wndMenuBar;
	CBCGPToolBar			m_wndToolBar;
	CWorkSpaceBar			m_wndWorkSpace;
	CWorkSpaceBar2			m_wndWorkSpace2;
	COutputBar				m_wndOutput;
	UINT	m_nAppLook;
};


