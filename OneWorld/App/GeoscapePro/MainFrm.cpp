// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "GeoscapePro.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CBCGPFrameWnd)


BEGIN_MESSAGE_MAP(CMainFrame, CBCGPFrameWnd)
	ON_WM_CREATE()
	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_2000, ID_VIEW_APPLOOK_WIN7, OnAppLook)
	//ON_COMMAND_RANGE(ID_VIEW_APPLOOK_2007, ID_VIEW_APPLOOK_VS2010, OnAppLook)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_2000, ID_VIEW_APPLOOK_WIN7, OnUpdateAppLook)
	ON_COMMAND(ID_VIEW_WORKSPACE, OnViewWorkspace)
	ON_UPDATE_COMMAND_UI(ID_VIEW_WORKSPACE, OnUpdateViewWorkspace)
	ON_COMMAND(ID_VIEW_WORKSPACE2, OnViewWorkspace2)
	ON_UPDATE_COMMAND_UI(ID_VIEW_WORKSPACE2, OnUpdateViewWorkspace2)
	ON_COMMAND(ID_VIEW_OUTPUT, OnViewOutput)
	ON_UPDATE_COMMAND_UI(ID_VIEW_OUTPUT, OnUpdateViewOutput)
	ON_REGISTERED_MESSAGE(BCGM_ON_RIBBON_CUSTOMIZE, OnRibbonCustomize)
	ON_COMMAND(ID_TOOLS_OPTIONS, OnToolsOptions)
END_MESSAGE_MAP()

// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{

	//m_nAppLook = theApp.GetInt (_T("ApplicationLook"), ID_VIEW_APPLOOK_VS2005);
	// TODO: add member initialization code here
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CBCGPFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManager2007));
	CBCGPVisualManager2007::SetStyle (CBCGPVisualManager2007::VS2007_LunaBlue);


	if (!CreateRibbonBar ())
	{
		TRACE0("Failed to create ribbon bar\n");
		return -1;      // fail to create
	}


	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: add your status bar panes here:
	m_wndStatusBar.AddElement (new CBCGPRibbonStatusBarPane (
		ID_STATUSBAR_PANE1, _T("Pane 1"), TRUE), _T("Pane 1"));
	m_wndStatusBar.AddExtendedElement (new CBCGPRibbonStatusBarPane (
		ID_STATUSBAR_PANE2, _T("Pane 2"), TRUE), _T("Pane 2"));

	// Load control bar icons:
	CBCGPToolBarImages imagesWorkspace;
	imagesWorkspace.SetImageSize (CSize (16, 16));
	imagesWorkspace.SetTransparentColor (RGB (255, 0, 255));
	imagesWorkspace.Load (IDB_WORKSPACE);
	imagesWorkspace.SmoothResize(globalData.GetRibbonImageScale());
	
	if (!m_wndWorkSpace.Create (_T("解决方案"), this, CRect (0, 0, 200, 200),
		TRUE, ID_VIEW_WORKSPACE,
		WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI))
	{
		TRACE0("Failed to create Workspace bar\n");
		return -1;      // fail to create
	}

	m_wndWorkSpace.SetIcon (imagesWorkspace.ExtractIcon (0), FALSE);

	if (!m_wndWorkSpace2.Create (_T("属性"), this, CRect (0, 0, 200, 200),
		TRUE, ID_VIEW_WORKSPACE2,
		WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI))
	{
		TRACE0("Failed to create Workspace bar 2\n");
		return -1;      // fail to create
	}

	m_wndWorkSpace2.SetIcon (imagesWorkspace.ExtractIcon (1), FALSE);


	//if (!m_wndOutput.Create (_T("查询"), this, CSize (150, 150),
	//	TRUE /* Has gripper */, ID_VIEW_OUTPUT,
	//	WS_CHILD | WS_VISIBLE | CBRS_BOTTOM))
	//{
	//	TRACE0("Failed to create output bar\n");
	//	return -1;      // fail to create
	//}

	m_wndWorkSpace.EnableDocking(CBRS_ALIGN_ANY);
	m_wndWorkSpace2.EnableDocking(CBRS_ALIGN_ANY);
	//m_wndOutput.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	EnableAutoHideBars(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndWorkSpace);
	m_wndWorkSpace2.AttachToTabWnd (&m_wndWorkSpace, BCGP_DM_STANDARD, FALSE, NULL);
	//DockControlBar(&m_wndOutput);

	//OnAppLook (m_nAppLook);

	// VISUAL_MANAGER
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CBCGPFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}


// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CBCGPFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CBCGPFrameWnd::Dump(dc);
}

#endif //_DEBUG


// CMainFrame message handlers





void CMainFrame::OnAppLook(UINT id)
{
	CBCGPDockManager::SetDockMode (BCGP_DT_SMART);

	m_nAppLook = id;

	m_wndRibbonBar.SetScenicLook(FALSE);
	m_wndRibbonBar.EnableMinimizeButton(FALSE);

	CBCGPTabbedControlBar::m_StyleTabWnd = CBCGPTabWnd::STYLE_3D;

	switch (m_nAppLook)
	{
	case ID_VIEW_APPLOOK_2000:
		// enable Office 2000 look:
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManager));
		break;

	case ID_VIEW_APPLOOK_XP:
		// enable Office XP look:
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManagerXP));
		break;

	case ID_VIEW_APPLOOK_WIN_XP:
		// enable Windows XP look (in other OS Office XP look will be used):
		CBCGPWinXPVisualManager::m_b3DTabsXPTheme = TRUE;
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPWinXPVisualManager));
		break;

	case ID_VIEW_APPLOOK_2003:
		// enable Office 2003 look:
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManager2003));
		CBCGPDockManager::SetDockMode (BCGP_DT_SMART);
		break;

	case ID_VIEW_APPLOOK_2007:
	case ID_VIEW_APPLOOK_2007_1:
	case ID_VIEW_APPLOOK_2007_2:
	case ID_VIEW_APPLOOK_2007_3:
		// enable Office 2007 look:
		switch (m_nAppLook)
		{
		case ID_VIEW_APPLOOK_2007:
			CBCGPVisualManager2007::SetStyle (CBCGPVisualManager2007::VS2007_LunaBlue);
			break;

		case ID_VIEW_APPLOOK_2007_1:
			CBCGPVisualManager2007::SetStyle (CBCGPVisualManager2007::VS2007_ObsidianBlack);
			break;

		case ID_VIEW_APPLOOK_2007_2:
			CBCGPVisualManager2007::SetStyle (CBCGPVisualManager2007::VS2007_Silver);
			break;

		case ID_VIEW_APPLOOK_2007_3:
			CBCGPVisualManager2007::SetStyle (CBCGPVisualManager2007::VS2007_Aqua);
			break;
		}

		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManager2007));
		CBCGPDockManager::SetDockMode (BCGP_DT_SMART);
		break;

	case ID_VIEW_APPLOOK_2010_1:
	case ID_VIEW_APPLOOK_2010_2:
	case ID_VIEW_APPLOOK_2010_3:
		// enable Office 2010 look:
		switch (m_nAppLook)
		{
		case ID_VIEW_APPLOOK_2010_1:
			CBCGPVisualManager2010::SetStyle (CBCGPVisualManager2010::VS2010_Blue);
			break;

		case ID_VIEW_APPLOOK_2010_2:
			CBCGPVisualManager2010::SetStyle (CBCGPVisualManager2010::VS2010_Black);
			break;

		case ID_VIEW_APPLOOK_2010_3:
			CBCGPVisualManager2010::SetStyle (CBCGPVisualManager2010::VS2010_Silver);
			break;
		}
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManager2010));
		
		m_wndRibbonBar.SetScenicLook();
		m_wndRibbonBar.EnableMinimizeButton();
		CBCGPDockManager::SetDockMode (BCGP_DT_SMART);
		break;

	case ID_VIEW_APPLOOK_WIN7:
		// enable Windows look:
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManagerScenic));
		
		m_wndRibbonBar.SetScenicLook();
		CBCGPDockManager::SetDockMode (BCGP_DT_SMART);
		break;

	case ID_VIEW_APPLOOK_VS2005:
		// enable VS 2005 look:
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManagerVS2005));
		CBCGPDockManager::SetDockMode (BCGP_DT_SMART);
		break;

	case ID_VIEW_APPLOOK_VS2008:
		// enable VS 2008 look:
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManagerVS2008));
		CBCGPDockManager::SetDockMode (BCGP_DT_SMART);
		break;

	case ID_VIEW_APPLOOK_VS2010:
		// enable VS 2010 look:
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManagerVS2010));
		CBCGPDockManager::SetDockMode (BCGP_DT_SMART);
		break;
	}

	CBCGPDockManager* pDockManager = GetDockManager ();
	if (pDockManager != NULL)
	{
		ASSERT_VALID (pDockManager);
		pDockManager->AdjustBarFrames ();
	}

	CBCGPTabbedControlBar::ResetTabs ();

	RecalcLayout ();
	RedrawWindow (NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME | RDW_ERASE);

	theApp.WriteInt (_T("ApplicationLook"), m_nAppLook);
}

void CMainFrame::OnUpdateAppLook(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio (m_nAppLook == pCmdUI->m_nID);
}

BOOL CMainFrame::CreateRibbonBar ()
{
	if (!m_wndRibbonBar.Create(this))
	{
		return FALSE;
	}

	// Load panel images:
	m_PanelImages.SetImageSize (CSize (16, 16));
	m_PanelImages.Load (IDB_RIBBON_ICONS);

	// Init main button:
	m_MainButton.SetImage (IDB_RIBBON_MAIN);
	m_MainButton.SetToolTipText (_T("File"));
	m_MainButton.SetText (_T("\nf"));

	m_wndRibbonBar.SetMainButton (&m_MainButton, CSize (45, 45));

	CBCGPRibbonMainPanel* pMainPanel = m_wndRibbonBar.AddMainCategory (
		_T("File"), IDB_RIBBON_FILESMALL, IDB_RIBBON_FILELARGE);

	pMainPanel->Add (new CBCGPRibbonButton (ID_FILE_NEW, _T("&New"), 0, 0));
	pMainPanel->Add (new CBCGPRibbonButton (ID_FILE_OPEN, _T("&Open..."), 1, 1));

	pMainPanel->Add (new CBCGPRibbonButton (ID_FILE_SAVE, _T("&Save"), 2, 2));

	pMainPanel->Add (new CBCGPRibbonButton (ID_FILE_SAVE_AS, _T("Save &As..."), 3, 3));

	CBCGPRibbonButton* pBtnPrint = new CBCGPRibbonButton (ID_FILE_PRINT, _T("&Print"), 4, 4);

	pBtnPrint->AddSubItem (new CBCGPRibbonLabel (_T("Preview and print the document")));
	pBtnPrint->AddSubItem (new CBCGPRibbonButton (ID_FILE_PRINT, _T("&Print"), 4, 4, TRUE));
	pBtnPrint->AddSubItem (new CBCGPRibbonButton (ID_FILE_PRINT_DIRECT, _T("&Quick Print"), 7, 7, TRUE));
	pBtnPrint->AddSubItem (new CBCGPRibbonButton (ID_FILE_PRINT_PREVIEW, _T("Print Pre&view"), 6, 6, TRUE));

	pBtnPrint->SetKeys (_T("p"), _T("w"));

	pMainPanel->Add (pBtnPrint);

	pMainPanel->AddRecentFilesList (_T("Recent Documents"));

	pMainPanel->AddToBottom (new CBCGPRibbonMainPanelButton (ID_TOOLS_OPTIONS, _T("Opt&ions"), 9));
	pMainPanel->AddToBottom (new CBCGPRibbonMainPanelButton (ID_APP_EXIT, _T("E&xit"), 8));

	// Add "Home" category with "Clipboard" panel:
	CBCGPRibbonCategory* pCategory = m_wndRibbonBar.AddCategory (
		_T("工程管理"),
		IDB_RIBBON_HOMESMALL,
		IDB_RIBBON_HOMELARGE);

	// Create "Clipboard" panel:
	CBCGPRibbonPanel* pPanelClipboard = pCategory->AddPanel (
		_T("工程"), 
		m_PanelImages.ExtractIcon (1));

	CBCGPRibbonButton* pOpenPro = new CBCGPRibbonButton (ID_FILE_OPEN, _T("打开"), 0, 0);
	pOpenPro->SetMenu (IDR_PASTE_MENU, TRUE);
	pPanelClipboard->Add (pOpenPro);

	CBCGPRibbonButton* pSavePro = new CBCGPRibbonButton (ID_FILE_SAVE, _T("保存"), 0, 0);
	pSavePro->SetMenu (IDR_PASTE_MENU, TRUE);
	pPanelClipboard->Add (pSavePro);

	CBCGPRibbonButton* pSaveAsPro = new CBCGPRibbonButton (ID_FILE_SAVE_AS, _T("另存为"), 0, 0);
	pSaveAsPro->SetMenu (IDR_PASTE_MENU, TRUE);
	pPanelClipboard->Add (pSaveAsPro);

	CBCGPRibbonButton* pClosePro = new CBCGPRibbonButton (ID_FILE_CLOSE, _T("关闭"), 0, 0);
	pClosePro->SetMenu (IDR_PASTE_MENU, TRUE);
	pPanelClipboard->Add (pClosePro);

	//pPanelClipboard->Add (new CBCGPRibbonButton (ID_FILE_SAVE, _T("保存工程"), 1));
	//pPanelClipboard->Add (new CBCGPRibbonButton (ID_FILE_SAVE_AS, _T("关闭工程"), 2));
	//pPanelClipboard->Add (new CBCGPRibbonButton (ID_FILE_CLOSE, _T("另存为"), 3));
	//pPanelClipboard->Add (new CBCGPRibbonButton (ID_EDIT_CLEAR, _T("Erase\nr"), 3));

	pPanelClipboard->SetKeys (_T("zc"));

	// Create "Window" panel:
	CBCGPRibbonPanel* pPanelWindow = pCategory->AddPanel (
		_T("选择"), 
		m_PanelImages.ExtractIcon (2));

	/*pPanelWindow->Add (new CBCGPRibbonCheckBox (ID_VIEW_WORKSPACE, _T("View 1\n1")));
	pPanelWindow->Add (new CBCGPRibbonCheckBox (ID_VIEW_WORKSPACE2, _T("View 2\n2")));

	pPanelWindow->Add (new CBCGPRibbonCheckBox (ID_VIEW_OUTPUT, _T("Output\no")));*/
	/*pPanelWindow->Add (new CBCGPRibbonButton (ID_FILE_MRU_FILE1, _T("添加路径")));
	pPanelWindow->Add (new CBCGPRibbonButton (10, _T("编辑路径")));
	pPanelWindow->Add (new CBCGPRibbonButton (10, _T("删除路径")));
	pPanelWindow->Add (new CBCGPRibbonButton (10, _T("漫游路径")));
	pPanelWindow->Add (new CBCGPRibbonButton (10, _T("暂停漫游")));
	pPanelWindow->Add (new CBCGPRibbonButton (10, _T("停止漫游")));*/
	CBCGPRibbonButton* pSelect = new CBCGPRibbonButton (ID_FILE_MRU_FILE1, _T("选择"), 0, 0);
	pSelect->SetMenu (IDR_PASTE_MENU, TRUE);
	pPanelWindow->Add (pSelect);

	CBCGPRibbonButton* pPro = new CBCGPRibbonButton (ID_FILE_MRU_FILE1, _T("属性"), 0, 0);
	pPro->SetMenu (IDR_PASTE_MENU, TRUE);
	pPanelWindow->Add (pPro);


	pPanelWindow->SetKeys (_T("zw"));

	// Create "<TODO>" panel:
	CBCGPRibbonPanel* pPanelTODO = pCategory->AddPanel (
		_T("添加"));
	//pPanelTODO->Add (new CBCGPRibbonLabel (_T("TODO: add elements here")));

	//pPanelTODO->SetKeys (_T("zt"));

	//// Add some hidden (non-ribbon) elements:
	//CBCGPRibbonUndoButton* pUndo = new CBCGPRibbonUndoButton (ID_EDIT_UNDO, _T("Undo"), 4);

	//pUndo->AddUndoAction (_T("Undo Item 1"));
	//pUndo->AddUndoAction (_T("Undo Item 2"));
	//pUndo->AddUndoAction (_T("Undo Item 3"));
	//pUndo->AddUndoAction (_T("Undo Item 4"));
	//pUndo->AddUndoAction (_T("Undo Item 5"));

	//pCategory->AddHidden (pUndo);
	CBCGPRibbonButton* pFeature = new CBCGPRibbonButton (ID_FILE_MRU_FILE1, _T("矢量层"), 0, 0);
	pFeature->SetMenu (IDR_PASTE_MENU, TRUE);
	pPanelTODO->Add (pFeature);

	CBCGPRibbonButton* pRaster = new CBCGPRibbonButton (ID_FILE_MRU_FILE1, _T("纹理层"), 0, 0);
	pRaster->SetMenu (IDR_PASTE_MENU, TRUE);
	pPanelTODO->Add (pRaster);

	CBCGPRibbonButton* pDEM = new CBCGPRibbonButton (ID_FILE_MRU_FILE1, _T("DEM层"), 0, 0);
	pDEM->SetMenu (IDR_PASTE_MENU, TRUE);
	pPanelTODO->Add (pDEM);

	CBCGPRibbonButton* pModel = new CBCGPRibbonButton (ID_FILE_MRU_FILE1, _T("模型层"), 0, 0);
	pModel->SetMenu (IDR_PASTE_MENU, TRUE);
	pPanelTODO->Add (pModel);

	// Add "<TODO>" category with "Clipboard" panel:
	CBCGPRibbonCategory* pTODOCategory = m_wndRibbonBar.AddCategory (
		_T("飞行导航"), 
		IDB_RIBBON_HOMESMALL,
		IDB_RIBBON_HOMELARGE);
	CBCGPRibbonPanel* pFly = pTODOCategory->AddPanel (
		_T("飞行模式"));

	CBCGPRibbonButton* pTerrain = new CBCGPRibbonButton (ID_FILE_MRU_FILE1, _T("地形模式"), 0, 0);
	pTerrain->SetMenu (IDR_PASTE_MENU, TRUE);
	pFly->Add (pTerrain);

	CBCGPRibbonButton* pFlight = new CBCGPRibbonButton (ID_FILE_MRU_FILE1, _T("飞行模式"), 0, 0);
	pFlight->SetMenu (IDR_PASTE_MENU, TRUE);
	pFly->Add (pFlight);

	CBCGPRibbonButton* pDrive = new CBCGPRibbonButton (ID_FILE_MRU_FILE1, _T("汽车模型"), 0, 0);
	pDrive->SetMenu (IDR_PASTE_MENU, TRUE);
	pFly->Add (pDrive);

	CBCGPRibbonPanel* pRoute = pTODOCategory->AddPanel (
		_T("路径"));

		CBCGPRibbonButton* pR = new CBCGPRibbonButton (ID_FILE_MRU_FILE1, _T("路径"), 0, 0);
	pR->SetMenu (IDR_PASTE_MENU, TRUE);
	pRoute->Add (pR);

	CBCGPRibbonButton* pEdit = new CBCGPRibbonButton (ID_FILE_MRU_FILE1, _T("编辑"), 0, 0);
	pEdit->SetMenu (IDR_PASTE_MENU, TRUE);
	pRoute->Add (pEdit);
	
	CBCGPRibbonButton* pPlay = new CBCGPRibbonButton (ID_FILE_MRU_FILE1, _T("播放"), 0, 0);
	pPlay->SetMenu (IDR_PASTE_MENU, TRUE);
	pRoute->Add (pPlay);


	CBCGPRibbonCategory* pViewCategory = m_wndRibbonBar.AddCategory (
		_T("视图"), 
		IDB_RIBBON_HOMESMALL,
		IDB_RIBBON_HOMELARGE);

	CBCGPRibbonPanel* pLayout = pViewCategory->AddPanel (
		_T("布局"));

		CBCGPRibbonButton* pNormal = new CBCGPRibbonButton (ID_FILE_MRU_FILE1, _T("常规模式"), 0, 0);
	pNormal->SetMenu (IDR_PASTE_MENU, TRUE);
	pLayout->Add (pNormal);

	CBCGPRibbonButton* pMax = new CBCGPRibbonButton (ID_FILE_MRU_FILE1, _T("最大化"), 0, 0);
	pMax->SetMenu (IDR_PASTE_MENU, TRUE);
	pLayout->Add (pMax);

	CBCGPRibbonButton* pFull = new CBCGPRibbonButton (ID_FILE_MRU_FILE1, _T("全屏"), 0, 0);
	pFull->SetMenu (IDR_PASTE_MENU, TRUE);
	pLayout->Add (pFull);

	CBCGPRibbonPanel* pScreen = pViewCategory->AddPanel (
		_T("屏幕"));

	pScreen->Add (new CBCGPRibbonCheckBox (ID_VIEW_WORKSPACE, _T("飞行控制")));
	pScreen->Add (new CBCGPRibbonCheckBox (ID_VIEW_WORKSPACE, _T("状态栏")));
	pScreen->Add (new CBCGPRibbonCheckBox (ID_VIEW_WORKSPACE, _T("时间控制")));

	CBCGPRibbonPanel* pEnv = pViewCategory->AddPanel (
		_T("环境"));

		pEnv->Add (new CBCGPRibbonCheckBox (ID_VIEW_WORKSPACE, _T("大气")));
	pEnv->Add (new CBCGPRibbonCheckBox (ID_VIEW_WORKSPACE, _T("太阳")));
	

	// Add quick access toolbar commands:
	CBCGPRibbonQATDefaultState qatState;

	qatState.AddCommand (ID_FILE_NEW, FALSE);
	qatState.AddCommand (ID_FILE_OPEN, FALSE);
	qatState.AddCommand (ID_FILE_SAVE);
	qatState.AddCommand (ID_FILE_PRINT_DIRECT);
	qatState.AddCommand (ID_FILE_PRINT_PREVIEW, FALSE);
	qatState.AddCommand (ID_EDIT_UNDO);

	m_wndRibbonBar.SetQuickAccessDefaultState (qatState);

	// Add "Style" button to the right of tabs:
	CBCGPRibbonButton* pStyleButton = new CBCGPRibbonButton (-1, _T("Style\ns"), -1, -1);
	pStyleButton->SetMenu (IDR_THEME_MENU, TRUE /* Right align */);

	m_wndRibbonBar.AddToTabs (pStyleButton);

	// Add "About" button to the right of tabs:
	m_wndRibbonBar.AddToTabs (new CBCGPRibbonButton (ID_APP_ABOUT, _T("\na"), m_PanelImages.ExtractIcon (0)));

	return TRUE;
}

LRESULT CMainFrame::OnRibbonCustomize (WPARAM wp, LPARAM lp)
{
	ShowOptions (0);
	return 1;
}

void CMainFrame::OnToolsOptions()
{
	ShowOptions (0);
}

void CMainFrame::ShowOptions (int nPage)
{
	// Create "Customize" page:
	CBCGPRibbonCustomizePage pageCustomize (&m_wndRibbonBar);

	// Add "popular" items:
	CList<UINT, UINT> lstPopular;

	lstPopular.AddTail (ID_FILE_NEW);
	lstPopular.AddTail (ID_FILE_OPEN);
	lstPopular.AddTail (ID_FILE_SAVE);
	lstPopular.AddTail (ID_FILE_PRINT_PREVIEW);
	lstPopular.AddTail (ID_FILE_PRINT_DIRECT);
	lstPopular.AddTail (ID_EDIT_UNDO);

	pageCustomize.AddCustomCategory (_T("Popular Commands"), lstPopular);

	// Add hidden commands:
	CList<UINT,UINT> lstHidden;
	m_wndRibbonBar.GetItemIDsList (lstHidden, TRUE);

	pageCustomize.AddCustomCategory (_T("Commands not in the Ribbon"), lstHidden);

	// Add all commands:
	CList<UINT,UINT> lstAll;
	m_wndRibbonBar.GetItemIDsList (lstAll);

	pageCustomize.AddCustomCategory (_T("All Commands"), lstAll);

	// Create property sheet:
	CBCGPPropertySheet propSheet (_T("Options"), this, nPage);
	propSheet.m_psh.dwFlags |= PSH_NOAPPLYNOW;

	propSheet.SetLook (CBCGPPropertySheet::PropSheetLook_List, 124 /* List width */);

	propSheet.AddPage (&pageCustomize);

	// TODO: add your option pages here:
	// COptionsPage1 pageOptions1;
	// propSheet.AddPage (&pageOptions1);
	//
	// COptionsPage1 pageOptions2;
	// propSheet.AddPage (&pageOptions2);

	if (propSheet.DoModal() != IDOK)
	{
		return;
	}
}

void CMainFrame::OnViewWorkspace() 
{
	ShowControlBar (&m_wndWorkSpace,
					!(m_wndWorkSpace.IsVisible ()),
					FALSE, TRUE);
	RecalcLayout ();
}

void CMainFrame::OnUpdateViewWorkspace(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck (m_wndWorkSpace.IsVisible ());
	pCmdUI->Enable (!GetDockManager ()->IsPrintPreviewValid ());
}

void CMainFrame::OnViewWorkspace2() 
{
	ShowControlBar (&m_wndWorkSpace2,
					!(m_wndWorkSpace2.IsVisible ()),
					FALSE, TRUE);
	RecalcLayout ();
}

void CMainFrame::OnUpdateViewWorkspace2(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck (m_wndWorkSpace2.IsVisible ());
	pCmdUI->Enable (!GetDockManager ()->IsPrintPreviewValid ());
}

 // WORKSPACEBAR
void CMainFrame::OnViewOutput() 
{
	ShowControlBar (&m_wndOutput,
					!(m_wndOutput.IsVisible ()),
					FALSE, TRUE);
	RecalcLayout ();
}

void CMainFrame::OnUpdateViewOutput(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck (m_wndOutput.IsVisible ());
	pCmdUI->Enable (!GetDockManager ()->IsPrintPreviewValid ());
}
Framework::ITocCtrl* CMainFrame::GetTOC()
{
	return &m_wndWorkSpace.m_wndTree;
}
 // OUTPUTBAR
 // RIBBON_APP
