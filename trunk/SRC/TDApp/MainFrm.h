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
protected:
	CSplitterWnd m_wndSplitter;
public:

// Operations
public:

// Overrides
public:
	//virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CBCGPStatusBar			m_wndStatusBar;
	CBCGPMenuBar			m_wndMenuBar;
	CBCGPToolBar			m_wndToolBar;
	CWorkSpaceBar			m_wndWorkSpace;
	CWorkSpaceBar2			m_wndWorkSpace2;
	COutputBar				m_wndOutput;

	//浏览工具
	CBCGPToolBar            m_ExplorerToolBar;

	//标绘工具
	CBCGPToolBar            m_DrawingToolBar;

	CBCGPToolBarImages	m_UserImages;
// Generated message map functions
public:
	BOOL		CreateRibbonBar();
	void		AddMainCategory();
	void		AddTab_MapControl();
	void		AddTab_ImageAnalyse();
	void		AddTab_Editor();
	//变化发现模块
	void        AddTab_ChangeDetect();
	//地理要素提取
	void        AddTab_GeoInfoExtract();

	Framework::IMaptreeCtrl* GetTOC();

	CBCGPRibbonBar						m_wndRibbonBar;	// Ribbon control bar
	CBCGPRibbonMainButton				m_MainButton;	// Ribbon main button
	CBCGPToolBarImages					m_PanelImages;	// Ribbon panel images
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()


	UINT	m_nAppLook;
public:
	afx_msg void OnClose();
};


