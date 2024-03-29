// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "UAVSoft.h"

#include "MainFrm.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_OTHER_INFO,
	ID_INDICATOR_POS_MAP,
	
};

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CBCGPFrameWnd)


BEGIN_MESSAGE_MAP(CMainFrame, CBCGPFrameWnd)
	ON_WM_CREATE()
	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_2000, ID_VIEW_APPLOOK_WIN7, OnAppLook)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_2000, ID_VIEW_APPLOOK_WIN7, OnUpdateAppLook)
	ON_COMMAND(ID_VIEW_WORKSPACE, OnViewWorkspace)
	ON_UPDATE_COMMAND_UI(ID_VIEW_WORKSPACE, OnUpdateViewWorkspace)
	/*ON_COMMAND(ID_VIEW_WORKSPACE2, OnViewWorkspace2)
	ON_UPDATE_COMMAND_UI(ID_VIEW_WORKSPACE2, OnUpdateViewWorkspace2)
	ON_COMMAND(ID_VIEW_OUTPUT, OnViewOutput)
	ON_UPDATE_COMMAND_UI(ID_VIEW_OUTPUT, OnUpdateViewOutput)*/
	ON_REGISTERED_MESSAGE(BCGM_ON_RIBBON_CUSTOMIZE, OnRibbonCustomize)
	ON_COMMAND(ID_TOOLS_OPTIONS, OnToolsOptions)

	ON_COMMAND(ID_MEASUREBAR, OnToolBox)

	ON_UPDATE_COMMAND_UI(ID_STATUSBAR_PANE1, &CMainFrame::OnUpdatePosMap)
END_MESSAGE_MAP()

// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{

	m_nAppLook = theApp.GetInt (_T("ApplicationLook"), ID_VIEW_APPLOOK_2007);
	// TODO: add member initialization code here
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CBCGPFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	//
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
		ID_STATUSBAR_PANE1, _T(""), TRUE), _T(""));
	m_wndStatusBar.AddSeparator();
	m_wndStatusBar.AddElement (new CBCGPRibbonStatusBarPane (
		ID_STATUSBAR_PANE2, _T(""), TRUE), _T(""));

	// Load control bar icons:
	CBCGPToolBarImages imagesWorkspace;
	imagesWorkspace.SetImageSize (CSize (16, 16));
	imagesWorkspace.SetTransparentColor (RGB (255, 0, 255));
	imagesWorkspace.Load (IDB_WORKSPACE);
	imagesWorkspace.SmoothResize(globalData.GetRibbonImageScale());
	
	if (!m_wndWorkSpace.Create (_T("图层管理"), this, CRect (0, 0, 200, 200),
		TRUE, ID_VIEW_WORKSPACE,
		WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI))
	{
		TRACE0("Failed to create Workspace bar\n");
		return -1;      // fail to create
	}

	m_wndWorkSpace.SetIcon (imagesWorkspace.ExtractIcon (0), FALSE);

	if (!m_wndWorkSpace2.Create (_T("View 2"), this, CRect (0, 0, 200, 200),
		TRUE, ID_VIEW_WORKSPACE2,
		WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI))
	{
		TRACE0("Failed to create Workspace bar 2\n");
		return -1;      // fail to create
	}

	m_wndWorkSpace2.SetIcon (imagesWorkspace.ExtractIcon (1), FALSE);


	if (!m_wndOutput.Create (_T("Output"), this, CSize (150, 150),
		TRUE /* Has gripper */, ID_VIEW_OUTPUT,
		WS_CHILD | WS_VISIBLE | CBRS_BOTTOM))
	{
		TRACE0("Failed to create output bar\n");
		return -1;      // fail to create
	}

	m_wndWorkSpace.EnableDocking(CBRS_ALIGN_ANY);
	m_wndWorkSpace2.EnableDocking(CBRS_ALIGN_ANY);
	m_wndOutput.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	EnableAutoHideBars(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndWorkSpace);
	m_wndWorkSpace2.AttachToTabWnd (&m_wndWorkSpace, BCGP_DM_STANDARD, FALSE, NULL);
	DockControlBar(&m_wndOutput);

	OnAppLook (m_nAppLook);

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

	m_PanelImages.SetImageSize (CSize (24, 24));
	if (!m_PanelImages.Load (IDB_ZOOMBAR))
	{
		TRACE0("Failed to load panel images\n");
		return -1;
	}
	//主菜单
	AddMainCategory();

	//地图浏览
	AddTab_MapControl();

	//标绘量测
	AddTab_Mesure();

	//地理要素提取
	AddTab_GeoInfoExtract();

	//矢量编辑
	AddTab_Editor();

	//制图
	AddTab_Print();

	//系统设置
	AddTab_Setting();

	//-----------------------------------
	// Add quick access toolbar commands:
	//-----------------------------------
	CBCGPRibbonQATDefaultState qatState;
	qatState.AddCommand (ID_MAP_ZOOM_IN);
	qatState.AddCommand (ID_ZOOM_OUT);
	qatState.AddCommand (ID_MAP_PAN);
	qatState.AddCommand (ID_MAP_FULLVIEW);
	qatState.AddCommand (ID_PRE_EXTENT);
	qatState.AddCommand (ID_NEXT_EXTENT);
	m_wndRibbonBar.SetQuickAccessDefaultState (qatState);

	return TRUE;
}


void CMainFrame::AddMainCategory()
{
	m_MainButton.SetImage (IDB_MAIN);
	m_MainButton.SetToolTipText (_T("文件"));
	m_MainButton.SetDescription (_T("单击此处打开、保存地图文件"));
	m_MainButton.SetID (ID_MAIN_BUTTON);

	m_wndRibbonBar.SetMainButton (&m_MainButton, CSize (45, 45));

	CBCGPRibbonMainPanel* pMainPanel = m_wndRibbonBar.AddMainCategory (
		_T("文件"), IDB_FILESMALL, IDB_FILELARGE);

	pMainPanel->Add (new CBCGPRibbonButton (ID_NEWMAPCLASS, _T("新建地图"), 0, 0));
	pMainPanel->Add (new CBCGPRibbonButton (ID_OPENMAPCLASS, _T("打开地图"), 1, 1));
	pMainPanel->Add (new CBCGPRibbonButton (ID_SAVEMAPCLASS, _T("保存地图"), 2, 2));
	//pMainPanel->Add (new CBCGPRibbonButton (ID_SAVEASMAPCLASS, _T("地图另存为..."), 3, 3));
}

//添加地图显示菜单
void CMainFrame::AddTab_MapControl()
{
	CBCGPRibbonCategory* pCategory = m_wndRibbonBar.AddCategory (
		_T("开始"),
		IDB_ZOOMBARSMALL,
		IDB_ZOOMBAR);

	//创建工程管理
	CBCGPRibbonPanel* pPanelProject = pCategory->AddPanel (
		_T("工程"));
	CBCGPRibbonButton* pBtnNewXTD = new CBCGPRibbonButton (ID_NEWMAPCLASS, _T("新建"), 11, 11);
	pPanelProject->Add (pBtnNewXTD);
	CBCGPRibbonButton* pBtnOpenXTD = new CBCGPRibbonButton (ID_OPENMAPCLASS, _T("打开"), 12,12);
	pPanelProject->Add (pBtnOpenXTD);
	CBCGPRibbonButton* pBtnSaveXTD = new CBCGPRibbonButton (ID_SAVEMAPCLASS, _T("保存"), 13,13);
	pPanelProject->Add (pBtnSaveXTD);
	/*CBCGPRibbonButton* pBtnSaveAsXTD = new CBCGPRibbonButton (ID_SAVEASMAPCLASS, _T("另存为"), 14,14);
	pPanelProject->Add (pBtnSaveAsXTD);*/
	//图层
	CBCGPRibbonPanel* pPanelFile = pCategory->AddPanel (_T("文件"));
	CBCGPRibbonComboBox* pDisplayCombo = new CBCGPRibbonComboBox (ID_DUMMY_COMBO, FALSE, 50, "比例尺:");
	pDisplayCombo->EnableDropDownListResize (FALSE);
	pDisplayCombo->AddItem(_T("1:1000"));
	pDisplayCombo->AddItem(_T("1:10000"));
	pDisplayCombo->AddItem(_T("1:50000"));
	pDisplayCombo->AddItem(_T("1:100000"));
	pDisplayCombo->AddItem(_T("1:250000"));
	pDisplayCombo->AddItem(_T("1:500000"));
	pDisplayCombo->AddItem(_T("1:1000000"));
	pPanelFile->Add (pDisplayCombo);
	//加载数据
	CBCGPRibbonButton* pPanelRaster = new CBCGPRibbonButton (ID_OPEN_IMG, _T("栅格数据加载"), 20);
	pPanelFile->Add (pPanelRaster);
	CBCGPRibbonButton* pPanelFeature = new CBCGPRibbonButton (ID_OPEN_Vector, _T("矢量数据加载"), 21);
	pPanelFile->Add (pPanelFeature);

	//创建视图基本操作
	CBCGPRibbonPanel* pPanelMap = pCategory->AddPanel (_T("浏览工具"));
	//--------------------------
	// 放大:
	//--------------------------
	CBCGPRibbonButton* pBtnZoomIn = new CBCGPRibbonButton (ID_MAP_ZOOM_IN, _T("放大"), 0, 0);
	pPanelMap->Add (pBtnZoomIn);
	//--------------------------
	// 缩小:
	//--------------------------
	CBCGPRibbonButton* pBtnZoomOut = new CBCGPRibbonButton (ID_ZOOM_OUT,_T("缩小"), 1, 1);
	pPanelMap->Add (pBtnZoomOut);
	

	CBCGPRibbonButton* pBtnPan = new CBCGPRibbonButton (ID_MAP_PAN, _T("漫游"), 4, 4);
	pPanelMap->Add (pBtnPan);
	//--------------------------
	// 全图:
	//--------------------------
	CBCGPRibbonButton* pBtnOvewView = new CBCGPRibbonButton (ID_MAP_FULLVIEW,_T("全图"), 5, 5);
	pPanelMap->Add (pBtnOvewView);

	//--------------------------
	// 前一视图:
	//--------------------------
	CBCGPRibbonButton* pBtnPreView = new CBCGPRibbonButton (ID_PRE_EXTENT, _T("前视图"), 7, 7);
	pPanelMap->Add (pBtnPreView);


	//--------------------------
	// 后一视图:
	//--------------------------
	CBCGPRibbonButton* pBtnNextView = new CBCGPRibbonButton (ID_NEXT_EXTENT, _T("后视图"), 8, 8);
	pPanelMap->Add (pBtnNextView);

	
	//添加当前图层
	CBCGPRibbonPanel* pPanelTargetLayer = pCategory->AddPanel (_T("增强显示"));
	CBCGPRibbonComboBox* pBtnCurrLayer = new CBCGPRibbonComboBox(ID_CURRLAYER_COMBO,FALSE,60,"目标层:");
	pPanelTargetLayer->Add(pBtnCurrLayer);

	CBCGPRibbonButton* pBtnShowOverView = new CBCGPRibbonButton (ID_ZOOMTO_LYREXTENT, _T("缩放到图层"), 26);
	pPanelTargetLayer->Add (pBtnShowOverView);
	
	pPanelTargetLayer->AddSeparator();

	
	pPanelTargetLayer->Add (new CBCGPRibbonLabel (_T("   调  整:")));
	CBCGPRibbonButton* pBtnBright = new CBCGPRibbonButton (ID_BRIGHT_RESTORE, _T("亮  度:"),29);
	pPanelTargetLayer->Add (pBtnBright);
	CBCGPRibbonButton* pBtnContrast = new CBCGPRibbonButton (ID_CONTRAST_RESTORE, _T("对比度:"), 30);
	pPanelTargetLayer->Add ( pBtnContrast);


	pPanelTargetLayer->Add (new CBCGPRibbonLabel (_T(" ")));
	CBCGPRibbonSlider* pSliderBright = new CBCGPRibbonSlider(ID_BRIGHT_SLIDER);
	pSliderBright->SetRange (0, 100);
	pSliderBright->SetPos (50);
	pPanelTargetLayer->Add(pSliderBright);

	pPanelTargetLayer->SetCenterColumnVert(TRUE);	
	CBCGPRibbonSlider* pSliderContrast = new CBCGPRibbonSlider (ID_CONTRAST_SLIDER);
	pSliderContrast->SetRange (0, 100);
	pSliderContrast->SetPos (50);
	pPanelTargetLayer->Add ( pSliderContrast);

	pPanelTargetLayer->Add (new CBCGPRibbonLabel (_T(" ")));
	CBCGPRibbonEdit* pBtnLE = new CBCGPRibbonEdit (ID_BRIGHT_TEXT, 30, _T(""));
	pBtnLE->EnableSpinButtons (0, 99);
	pBtnLE->SetEditText (_T("50"));
	pPanelTargetLayer->Add (pBtnLE);

	CBCGPRibbonEdit* pBtnDE = new CBCGPRibbonEdit (ID_CONTRAST_TEXT, 30, _T(""));
	pBtnDE->EnableSpinButtons (0, 99);
	pBtnDE->SetEditText (_T("50"));
	pPanelTargetLayer->Add (pBtnDE);


	pPanelTargetLayer->Add (new CBCGPRibbonLabel (_T(" ")));
	CBCGPRibbonButton* pBtnTrans = new CBCGPRibbonButton (ID_TRANSPARENT_RESTORE, _T("透明度:"), 31);
	pPanelTargetLayer->Add ( pBtnTrans);
	pPanelTargetLayer->Add (new CBCGPRibbonLabel (_T(" ")));

	pPanelTargetLayer->Add (new CBCGPRibbonLabel (_T(" ")));
	CBCGPRibbonSlider* pSliderTrans = new CBCGPRibbonSlider (ID_TRANSPARENT_SLIDER);

	pSliderTrans->SetRange (0, 100);
	pSliderTrans->SetPos (0);
	pPanelTargetLayer->Add ( pSliderTrans);
	pPanelTargetLayer->Add (new CBCGPRibbonLabel (_T(" ")));

	pPanelTargetLayer->Add (new CBCGPRibbonLabel (_T(" ")));
	CBCGPRibbonEdit* pBtnTE = new CBCGPRibbonEdit (ID_TRANSPARENT_TEXT, 30, _T(""));
	pBtnTE->EnableSpinButtons (0, 99);
	pBtnTE->SetEditText (_T("0"));
	pPanelTargetLayer->Add (pBtnTE);
	pPanelTargetLayer->Add (new CBCGPRibbonLabel (_T(" ")));

	pPanelTargetLayer->AddSeparator();
	CBCGPRibbonButton* pBtnSwipView = new CBCGPRibbonButton (ID_SWIPE, _T("卷帘"),0,6);
	pPanelTargetLayer->Add ( pBtnSwipView);
	CBCGPRibbonButton* pBtnStretch = new CBCGPRibbonButton (ID_RASLUT_EDIT, _T("闪烁"),1,5);
	pPanelTargetLayer->Add ( pBtnStretch);

	CBCGPRibbonPanel* pPanelShowHide = pCategory->AddPanel (
		_T("显示/隐藏"), m_PanelImages.ExtractIcon (26));
	pPanelShowHide->Add (new CBCGPRibbonCheckBox (ID_VIEW_WORKSPACE, _T("图层管理")));

	CBCGPRibbonPanel* pPanelSystem = pCategory->AddPanel (_T("系统"));
	CBCGPRibbonButton* pBtnSetting = new CBCGPRibbonButton (ID_SETTING,_T("设置"), 3, 22);
	pPanelSystem->Add(pBtnSetting);
	CBCGPRibbonButton* pBtnHelp = new CBCGPRibbonButton (ID_FOR_HELP,_T("帮助"), 1, 26);
	pPanelSystem->Add(pBtnHelp);
	CBCGPRibbonButton* pBtnClose = new CBCGPRibbonButton (ID_FOR_EXIT,_T("退出"), 2, 25);
	pPanelSystem->Add(pBtnClose);
}

void CMainFrame::AddTab_Setting()
{


	CBCGPRibbonCategory* pCategory = m_wndRibbonBar.AddCategory (
		_T("系统设置"),
		IDB_FILELARGE,
		IDB_DRAWMESURE);


	//CBCGPRibbonPanel* pPanelLabel = pCategory->AddPanel (_T("标绘工具"));
	////--------------------------
	//// 选择:
	////--------------------------
	//CBCGPRibbonButton* pBtnSelected = new CBCGPRibbonButton(ID_DRAW_SELECT, _T("选择"), -1, 2);
	//pPanelLabel->Add (pBtnSelected);

	////--------------------------
	//// 删除全部:
	////--------------------------
	//CBCGPRibbonButton* pBtnDelAll = new CBCGPRibbonButton(ID_DEL_ALL, _T("删除全部"), -1, 14);
	//pPanelLabel->Add (pBtnDelAll);

	////--------------------------
	//// 矢量要素:
	////--------------------------
	//CBCGPRibbonButton* pBtnRect = new CBCGPRibbonButton (ID_DRAW_RECT, _T("矩形"), -1, 3);
	//pPanelLabel->Add (pBtnRect);
	////--------------------------
	//// 矢量要素:
	////--------------------------
	//CBCGPRibbonButton* pBtnPolygon = new CBCGPRibbonButton(ID_DRAW_POLYGON, _T("多边形"), -1, 4);
	//pPanelLabel->Add (pBtnPolygon);		
	////--------------------------
	////添加标绘线工具
	////--------------------------
	//CBCGPRibbonButton* pBtnPolyline = new CBCGPRibbonButton(ID_DRAW_POLYLINE, _T("多段线"), -1, 5);
	//pPanelLabel->Add (pBtnPolyline);	
	//// 点标绘:
	////--------------------------
	//CBCGPRibbonButton* pBtnPoint = new CBCGPRibbonButton(ID_DRAW_MARKER, _T("点"), -1, 6);
	//pPanelLabel->Add (pBtnPoint);

	////--------------------------
	////添加编辑选择要素工具要素工具
	////--------------------------
	//CBCGPRibbonButton* pBtnEditNodeElement = new CBCGPRibbonButton(ID_DRAW_EDITOR, _T("编辑结点"), -1, 7);
	//pPanelLabel->Add (pBtnEditNodeElement);

	////--------------------------
	////将标绘要素保存为shp
	////--------------------------
	//CBCGPRibbonButton* pBtnElementSaveAs = new CBCGPRibbonButton(ID_DRAW_SAVEAS, _T("导出"), -1, 8);
	//pPanelLabel->Add (pBtnElementSaveAs);


	//量测工具	
	CBCGPRibbonPanel* pPanelMeasure = pCategory->AddPanel (_T("量测工具"));
	//--------------------------
	// 线量测:
	//--------------------------
	//CBCGPRibbonButton* pBtnLineMeasure = new CBCGPRibbonButton(ID_LINE_MEASURE, _T("距离量测"), -1, 15);
	//pPanelMeasure->Add (pBtnLineMeasure);

	////--------------------------
	//// 面量测:
	////--------------------------
	//CBCGPRibbonButton* pBtnAreaMeasure = new CBCGPRibbonButton(ID_AREA_MEASURE, _T("面积量测"), -1, 16);
	//pPanelMeasure->Add (pBtnAreaMeasure);

	pPanelMeasure->Add (new CBCGPRibbonLabel (_T(" 单 位:")));
	CBCGPRibbonComboBox* pBtnUnit= new CBCGPRibbonComboBox(ID_COMBOX_UNITTYPE,FALSE,50,"");
	pPanelMeasure->Add(pBtnUnit);

	pBtnUnit->AddItem("米");
	pBtnUnit->AddItem("千米");
	if(pBtnUnit->GetCount() > 0)
		pBtnUnit->SelectItem(0);

	//半自动提取
	CBCGPRibbonPanel* pPanelHalfAuto = pCategory->AddPanel (_T("半自动提取工具"));

	//添加当前图层
	//CBCGPRibbonButtonsGroup* pMagicGroup = new CBCGPRibbonButtonsGroup;

	CBCGPRibbonComboBox* pBtnCurrLayer = new CBCGPRibbonComboBox(ID_MAGICSTICK_LAYER,FALSE,85,"目标图层:");
	pPanelHalfAuto->Add(pBtnCurrLayer);
	CBCGPRibbonEdit *pEditButton =new CBCGPRibbonEdit(ID_MAGICSTICK_TOL,100,"像素阈值:");
	pEditButton->SetEditText("20");
	pPanelHalfAuto->Add(pEditButton);

	//--------------------------
	// 魔术棒
	//--------------------------
	//CBCGPRibbonButton* pBtnMagic = new CBCGPRibbonButton (ID_MAGIC_STICK, _T("魔术棒提取"), 10, 10);

	//pPanelHalfAuto->Add (pBtnMagic);

	//// 删除上次魔术棒提取结果
	////--------------------------
	//CBCGPRibbonButton* pBtnRemoveMagic = new CBCGPRibbonButton (ID_REMOVELASTMAGIC, _T("取消上次操作"), 12, 12);

	//pPanelHalfAuto->Add (pBtnRemoveMagic);

	pPanelHalfAuto->AddSeparator();
}
void CMainFrame::AddTab_Mesure()
{
	
	//标绘工具栏
	UINT uiToolbarHotID = 0;

	if (!m_wndMarkBar.Create (_T("工具箱"), this, CRect (0, 0, 20, 500),
		TRUE, 
		ID_MEASUREBAR,
		WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT | CBRS_FLOAT_MULTI))
	{
		TRACE0("Failed to create ToolBox Bar\n");
		return ;		// fail to create
	}
	m_wndMarkBar.AddToolsPage(_T("标绘工具"), IDB_BITMAP_MARK, 20, 
		_T("选择\n全部删除\n矩形\n多边形\n折线\n点\n节点\n导出"));

	m_wndMarkBar.GetPage (0)->SetMode (CBCGPToolBoxPage::ToolBoxPageMode_Default);

	m_wndMarkBar.AddToolsPage(_T("量测工具"), IDB_MESURE, 20, 
		_T("线量测\n面量测"));

	m_wndMarkBar.GetPage (1)->SetMode (CBCGPToolBoxPage::ToolBoxPageMode_Default);

	m_wndMarkBar.AddToolsPage(_T("提取工具"), IDB_BITMAP_MAGIC, 20, 
		_T("魔术棒提取\n取消上次操作"));


	m_wndMarkBar.AddToolsPage(_T("影像分类"), IDB_BITMAP_IMGPRO, 20, 
		_T("ROI提取\nROI分类\n分类结果编码\n分类矢量化"));

	//标准工具栏IDB_BITMAP_IMGPRO
	//uiToolbarHotID =  0;
	//if (!m_wndStandBar.Create(this,
	//	WS_CHILD|WS_VISIBLE|CBRS_TOP|CBRS_TOOLTIPS|CBRS_FLYBY|CBRS_HIDE_INPLACE|CBRS_SIZE_DYNAMIC|
	//	CBRS_GRIPPER | CBRS_BORDER_3D,ID_MEASUREBAR) ||
	//	!m_wndStandBar.LoadToolBar(IDR_MARKBAR, 0, 0, FALSE, 0, 0, uiToolbarHotID))
	//{
	//	TRACE0("Failed to create toolbar\n");
	//	return ;      // fail to create
	//}
	////
	//CBCGPToolbarComboBoxButton  comboButton(ID_DUMMY_COMBO, 
	//	CImageHash::GetImageOfCommand (ID_DUMMY_COMBO, FALSE),
	//	CBS_DROPDOWNLIST);
	//m_wndStandBar.ReplaceButton (ID_DUMMY_COMBO, comboButton, TRUE);

	////CBCGPBaseControlBar* pControlbar = new CBCGPBaseControlBar();
	//
	//m_wndMarkBar.AddControlBar(&m_wndStandBar);
	m_wndMarkBar.SetWindowText (_T("工具箱"));
	m_wndMarkBar.EnableDocking(CBRS_ALIGN_ANY);

	// 此处控制工具箱的大小位置
	CRect viewRect,dockRect;
	this->GetClientRect(&viewRect);
	dockRect.left=viewRect.right-100;
	dockRect.right=dockRect.left+110;
	dockRect.top=viewRect.top+200;
	dockRect.bottom=dockRect.top+350;
	dockRect.NormalizeRect();
	m_wndMarkBar.FloatControlBar(dockRect);
	m_wndMarkBar.ShowControlBar(FALSE, TRUE, TRUE);


	
}

void CMainFrame::AddTab_Editor()
{
	CBCGPRibbonCategory* pCategory = m_wndRibbonBar.AddCategory (
		_T("提取结果编辑"),
		IDB_FILESMALL,
		IDB_EDITORLARGE);



	//创建编辑基本操作
	CBCGPRibbonPanel* pPanelEditor = pCategory->AddPanel (_T("编辑工具"));
	//添加当前图层
	pPanelEditor->Add (new CBCGPRibbonLabel (_T("编辑目标层：")));
	CBCGPRibbonComboBox* pBtnCurrLayer = new CBCGPRibbonComboBox(ID_CURRLAYER_COMBO_VECTOR,FALSE,100,"");

	pPanelEditor->Add(pBtnCurrLayer);
	CBCGPRibbonButton* pBtnShowOverView = new CBCGPRibbonButton (ID_ZOOMTO_LYREXTENT, _T("缩放到图层"), 1);
	pPanelEditor->Add (pBtnShowOverView);

	pPanelEditor->AddSeparator();
	//--------------------------
	// 开始编辑:
	//--------------------------
	CBCGPRibbonButton* pBtnEditStart = new CBCGPRibbonButton (ID_EDITOR_START, _T("开始编辑"), 0, 0);
	pPanelEditor->Add (pBtnEditStart);
	//--------------------------
	// 绘制:
	//--------------------------
	CBCGPRibbonButton* pBtnEditSketch = new CBCGPRibbonButton (ID_EDITOR_SKETCH,_T("绘制"), 1, 1);
	pPanelEditor->Add (pBtnEditSketch);
	//--------------------------
	// 编辑:
	//--------------------------
	CBCGPRibbonButton* pBtnEdit = new CBCGPRibbonButton (ID_EDITOR_EDIT, _T("编辑"), 2, 2);
	pPanelEditor->Add (pBtnEdit);
	//--------------------------
	// 撤销:
	//--------------------------

	CBCGPRibbonButton* pBtnEditUndo = new CBCGPRibbonButton (ID_EDITOR_UNDO, _T("撤销"), 3, 3);
	pPanelEditor->Add (pBtnEditUndo);
	//--------------------------
	// 重复:
	//--------------------------
	CBCGPRibbonButton* pBtnEditRedo = new CBCGPRibbonButton (ID_EDITOR_REDO, _T("重复"), 4, 4);
	pPanelEditor->Add (pBtnEditRedo);

	//--------------------------
	// 结束编辑:
	//--------------------------
	CBCGPRibbonButton* pBtnEditEnd = new CBCGPRibbonButton (ID_EDITOR_END,_T("结束编辑"), 5, 5);
	pPanelEditor->Add (pBtnEditEnd);

	//--------------------------
	// 保存:
	//--------------------------
	CBCGPRibbonButton* pBtnEditSave = new CBCGPRibbonButton (ID_EDITOR_SAVE, _T("保存"), 6, 6);
	pPanelEditor->Add (pBtnEditSave);
	//--------------------------
	// 删除:
	//--------------------------
	CBCGPRibbonButton* pBtnEditDel = new CBCGPRibbonButton (ID_DELETE_FEATURES, _T("删除"), 7, 7);
	pPanelEditor->Add (pBtnEditDel);
	////--------------------------
	//// 合并要素:
	////--------------------------
	//CBCGPRibbonButton* pBtnEditUnion = new CBCGPRibbonButton (ID_UNION_FEATURES, _T("合并要素"), 8, 8);
	//pPanelEditor->Add (pBtnEditUnion);

	//--------------------------
	// 要素属性编辑:
	//--------------------------
	CBCGPRibbonButton* pBtnAtiEdit = new CBCGPRibbonButton (ID_ATTRIBUTE_EDIT, _T("属性编辑"), 9, 9);
	pPanelEditor->Add (pBtnAtiEdit);


	//--------------------------
	// 要素信息:
	//--------------------------
	CBCGPRibbonButton* pBtnFeatureInfo = new CBCGPRibbonButton (ID_FEATURES_INFO, _T("要素信息"), 10, 10);
	pPanelEditor->Add (pBtnFeatureInfo);

	//--------------------------
	// 要素选择:
	//--------------------------
	CBCGPRibbonButton* pBtnFeatureSelect = new CBCGPRibbonButton (ID_SELECTFEATURE, _T("要素选择"), 11, 11);
	pPanelEditor->Add (pBtnFeatureSelect);

	

}

void CMainFrame::AddTab_GeoInfoExtract()
{
	CBCGPRibbonCategory* pCategory = m_wndRibbonBar.AddCategory (
		_T("环境污染事故分析"),
		IDB_POL_LARGE,
		IDB_POL_LARGE);

	//CBCGPRibbonPanel* pPanelEdge = pCategory->AddPanel (_T("图像边缘提取"));
	////--------------------------
	//// 边缘增强
	////--------------------------
	//CBCGPRibbonButton* pBtnEdgeEnhance = new CBCGPRibbonButton(ID_EDGE_ENHANCE, _T("图像边缘增强"), -1, 0);
	//pPanelEdge->Add (pBtnEdgeEnhance);

	////--------------------------
	//// 边缘提取
	////--------------------------
	//CBCGPRibbonButton* pBtnEdgeExtract = new CBCGPRibbonButton(ID_EDGE_EXTRACT, _T("图像边缘提取"), -1, 1);
	//pPanelEdge->Add (pBtnEdgeExtract);

	CBCGPRibbonPanel* pPanelPOL = pCategory->AddPanel (_T("污染体气识别"));

	//--------------------------
	// 气体污染数据插值
	//--------------------------
	CBCGPRibbonButton* pBtnGasDataInsert = new CBCGPRibbonButton(ID_GAS_DATAINSERT, _T("气体污染数据插值"), 8, 8);
	pPanelPOL->Add (pBtnGasDataInsert);


	CBCGPRibbonPanel* pPanelWater = pCategory->AddPanel (_T("水源地污染识别"));
	//--------------------------
	// 高精度水华识别
	//--------------------------
	CBCGPRibbonButton* pBtnHighWPL = new CBCGPRibbonButton(ID_HIGH_WATERPOL, _T("高精度水华识别"), 4, 4);
	pPanelWater->Add (pBtnHighWPL);


	CBCGPRibbonPanel* pPanelOil = pCategory->AddPanel (_T("溢油污染识别"));

	//--------------------------
	// 溢油边缘检测
	//--------------------------
	CBCGPRibbonButton* pBtnOilEdge = new CBCGPRibbonButton(ID_OIL_EDGE, _T("溢油边缘检测"), 7, 7);
	pPanelOil->Add (pBtnOilEdge);

	CBCGPRibbonPanel* pPanelDamage = pCategory->AddPanel (_T("垮塌事故识别"));

	//--------------------------
	// 垮塌事故识别
	//--------------------------
	CBCGPRibbonButton* pBtnBuildDamage = new CBCGPRibbonButton(ID_BUILD_DAMAGE, _T("垮塌事故识别"), 6, 6);
	pPanelDamage->Add (pBtnBuildDamage);


	return;


	//--------------------------
	// 自适应水华识别
	//--------------------------
	CBCGPRibbonButton* pBtnAdaptWPL = new CBCGPRibbonButton(ID_CLASSIFY_FUZZYKMEAN, _T("自适应水华识别"), 5, 5);
	pPanelPOL->Add (pBtnAdaptWPL);



	//--------------------------
	// 浓度影像生成
	//--------------------------
	CBCGPRibbonButton* pBtnGasCreateImage = new CBCGPRibbonButton(ID_GAS_CREATEIMAGE, _T("浓度影像生成"), 9, 9);
	pPanelPOL->Add (pBtnGasCreateImage);




	CBCGPRibbonPanel* pPanelClasses = pCategory->AddPanel (_T("影像分类"));
	//--------------------------
	// ROI提取
	//--------------------------
	CBCGPRibbonButton* pBtnRoiDlg = new CBCGPRibbonButton(IDC_CREATE_ROI_DIALOG, _T("ROI提取"), -1, 2);
	pPanelClasses->Add (pBtnRoiDlg);

	CBCGPRibbonButton* pBtnSuperCls = new CBCGPRibbonButton(IDC_SUPER_CLASS_DIALOG, _T("ROI监督分类"), -1, 2);
	pPanelClasses->Add (pBtnSuperCls);
    
	CBCGPRibbonPanel* pPanelAfterClasses = pCategory->AddPanel (_T("分类后处理"));
	//--------------------------
	// 分类结果编号命名
	//--------------------------
	CBCGPRibbonButton* pBtnClassRename = new CBCGPRibbonButton(ID_CLASSES_RENAME, _T("分类结果编号命名"), -1, 2);
	pPanelAfterClasses->Add (pBtnClassRename);

	//--------------------------
	// 子类合并
	//--------------------------
	CBCGPRibbonButton* pBtnClassMerge = new CBCGPRibbonButton(ID_CLASSES_MERGE, _T("分类矢量化"), -1, 3);
	pPanelAfterClasses->Add (pBtnClassMerge);

	
}

void CMainFrame::AddTab_Print()
{
	CBCGPRibbonCategory* pCategory = m_wndRibbonBar.AddCategory (
		_T("制图输出"),
		IDB_FILELARGE,
		IDB_LAYOUT);



	//创建编辑基本操作
	CBCGPRibbonPanel* pPanelPageLayout = pCategory->AddPanel (_T("制图浏览工具"));
	//--------------------------
	// 放大:
	//--------------------------
	CBCGPRibbonButton* pBtnZoomIn = new CBCGPRibbonButton (ID_LAYOUT_ZOOM_IN, _T("放大"), 0, 0);
	pPanelPageLayout->Add (pBtnZoomIn);
	//--------------------------
	// 缩小:
	//--------------------------
	CBCGPRibbonButton* pBtnZoomOut = new CBCGPRibbonButton (ID_LAYOUT_ZOOM_OUT,_T("缩小"), 1, 1);
	pPanelPageLayout->Add (pBtnZoomOut);


	CBCGPRibbonButton* pBtnPan = new CBCGPRibbonButton (ID_LAYOUT_PAN, _T("漫游"), 2, 2);
	pPanelPageLayout->Add (pBtnPan);
	//--------------------------
	// 全图:
	//--------------------------
	CBCGPRibbonButton* pBtnOvewView = new CBCGPRibbonButton (ID_LAYOUT_FULLVIEW,_T("全图"), 3, 3);
	pPanelPageLayout->Add (pBtnOvewView);
	//--------------------------
	// 1:1:
	//--------------------------
	CBCGPRibbonButton* pBtnActualSize = new CBCGPRibbonButton (ID_LAYOUT_ACTUALSIZE,_T("1:1"), 4, 4);
	pPanelPageLayout->Add (pBtnActualSize);



	//地图整饰
	CBCGPRibbonPanel* pPanelMapSurround = pCategory->AddPanel (_T("地图整饰工具"));
	//--------------------------
	// 选择制图要素:
	//--------------------------
	CBCGPRibbonButton* pBtnSelectFrameElement= new CBCGPRibbonButton (ID_SELECT_FRAME_ELEMENT, _T("选择要素"), 5, 5);
	pPanelMapSurround->Add (pBtnSelectFrameElement);
	//--------------------------
	// 图名:
	//--------------------------
	CBCGPRibbonButton* pBtnDrawMapTitle = new CBCGPRibbonButton (ID_DRAW_MAP_TITLE,_T("图名"), 9,9);
	pPanelMapSurround->Add (pBtnDrawMapTitle);
	//--------------------------
	// 指北针:
	//--------------------------
	CBCGPRibbonButton* pBtnDrawNorthArrow= new CBCGPRibbonButton (ID_DRAW_NORTH_ARROW,_T("指北针"), 7, 7);
	pPanelMapSurround->Add (pBtnDrawNorthArrow);


	CBCGPRibbonButton* pBtnDrawScaleBar = new CBCGPRibbonButton (ID_DRAW_SCALEBAR, _T("比例尺"), 8, 8);
	pPanelMapSurround->Add (pBtnDrawScaleBar);
	//--------------------------
	// 图例:
	//--------------------------
	CBCGPRibbonButton* pBtnDrawLegend= new CBCGPRibbonButton (ID_DRAW_LEGEND,_T("图例"), 6, 6);
	pPanelMapSurround->Add (pBtnDrawLegend);

	//--------------------------
	// 加载模板:
	//--------------------------
	CBCGPRibbonButton* pBtnLoadTMP= new CBCGPRibbonButton (ID_LOAD_TEMP,_T("更改模板"), 17, 17);
	pPanelMapSurround->Add (pBtnLoadTMP);

	//--------------------------
	// 保存模板:
	//--------------------------
	CBCGPRibbonButton* pBtnSaveTMP= new CBCGPRibbonButton (ID_SAVE_TEMP,_T("保存模板"), 18, 18);
	pPanelMapSurround->Add (pBtnSaveTMP);
//--------------------------
	// 导出到影像文件输出设置:
	//--------------------------ID_LAYOUT_PRINT_TO_IMAGE
	CBCGPRibbonButton* pBtnExportImg= new CBCGPRibbonButton (ID_LAYOUT_PRINT_TO_IMAGE,_T("导出到影像文件"), 19, 19);
	pPanelMapSurround->Add (pBtnExportImg);
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

//void CMainFrame::OnViewWorkspace2() 
//{
//	ShowControlBar (&m_wndWorkSpace2,
//					!(m_wndWorkSpace2.IsVisible ()),
//					FALSE, TRUE);
//	RecalcLayout ();
//}
//
//void CMainFrame::OnUpdateViewWorkspace2(CCmdUI* pCmdUI) 
//{
//	pCmdUI->SetCheck (m_wndWorkSpace2.IsVisible ());
//	pCmdUI->Enable (!GetDockManager ()->IsPrintPreviewValid ());
//}

 // WORKSPACEBAR
//void CMainFrame::OnViewOutput() 
//{
//	ShowControlBar (&m_wndOutput,
//					!(m_wndOutput.IsVisible ()),
//					FALSE, TRUE);
//	RecalcLayout ();
//}
//
//void CMainFrame::OnUpdateViewOutput(CCmdUI* pCmdUI) 
//{
//	pCmdUI->SetCheck (m_wndOutput.IsVisible ());
//	pCmdUI->Enable (!GetDockManager ()->IsPrintPreviewValid ());
//}
 // OUTPUTBAR
 // RIBBON_APP


Framework::IMaptreeCtrl* CMainFrame::GetTOC()
{
	return &m_wndWorkSpace.m_wndTree;
}

void CMainFrame::OnUpdatePosMap(CCmdUI *pCmdUI)
{
	CView* pActiveView = GetActiveView();
	if(!pActiveView->IsKindOf(RUNTIME_CLASS(CUAVSoftView)))
		return;

	CUAVSoftView* pView = (CUAVSoftView*)pActiveView;

	CBCGPRibbonStatusBarPane *pPanel=(CBCGPRibbonStatusBarPane*)m_wndStatusBar.FindByID(ID_STATUSBAR_PANE1);
	//pPanel->SetRect()

	if(pPanel==NULL)
	{
		return;
	}
	
	POINT disPos;
	GetCursorPos(&disPos);
	pView->m_MapCtrl.ScreenToClient(&disPos);

	double mapX, mapY;
	Carto::CMapPtr pActiveMap = pView->m_MapCtrl.GetMap();
	pActiveMap->GetDisplay()->GetDisplayTransformation().ConvertDisplayToGeo(disPos.x, disPos.y, mapX, mapY);

	CString msg;
	msg.Format("X:%f  ,Y:%f",  mapX, mapY);
	pPanel->SetText(msg);
	//pCmdUI->SetText(msg);
	m_wndStatusBar.RecalcLayout ();
	m_wndStatusBar.RedrawWindow ();




}

void CMainFrame::UpdateStatusInfo(CString info)
{
	CBCGPRibbonStatusBarPane *pPanel=(CBCGPRibbonStatusBarPane*)m_wndStatusBar.FindByID(ID_STATUSBAR_PANE2);
	//pPanel->SetRect()

	if(pPanel==NULL)
	{
		return;
	}
	pPanel->SetText(info);
	
	m_wndStatusBar.RecalcLayout ();
	m_wndStatusBar.RedrawWindow ();
}

CUAVSoftView*  CMainFrame::GetActiveMapView()
{
	CUAVSoftDoc * pDoc = (CUAVSoftDoc *)GetActiveDocument();
	if(!pDoc)
		return NULL;

	POSITION pos = pDoc->GetFirstViewPosition();
	CUAVSoftView* pMapView;
	pMapView = (CUAVSoftView*)pDoc->GetNextView(pos);

	return pMapView;
}
//标绘符号工具
void CMainFrame::OnToolBox()
{
	CUAVSoftView* pView=this->GetActiveMapView();
	int nPage = -1;
	int nTool = -1;
	nTool=m_wndMarkBar.GetLastClickedTool (nPage);

	//标绘
	if(nPage == 0)
	{
		switch(nTool)
		{
		case 0:
			pView->OnDrawSelect();
			break;
		case 1:
			pView->OnDelAll();
			break;
		case 2:
			pView->OnDrawRect();
			break;
		case 3:
			pView->OnDrawPolygon();
			break;
		case 4:
			pView->OnDrawPolyline();
			break;
		case 5:
			pView->OnDrawMarker();
			break;
		case 6:
			pView->OnEditElement();
			break;
		case 7:
			pView->OnDrawSaveAs();
			break;
		default:
			;

		}
	}
	else if(nPage == 1)
	{
		switch(nTool)
		{
		case 0:
			pView->OnLineMeasure();
			break;
		case 1:
			pView->OnAreaMeasure();
			break;
		}
	}
	else if(nPage == 2)
	{
		switch(nTool)
		{
		case 0:
			pView->OnMagicStick();
			break;
		case 1:
			pView->OnDeleteLastMagic();
			break;
		}
	}
	else if(nPage == 3)
	{
		switch(nTool)
		{
		case 0:
			pView->OnRoiDlg();
			break;
		case 1:
			pView->OnSuperClsDlg();
			break;
		case 2:
			pView->OnModifyClassinfo();
			break;
		case 3:
			pView->OnClassVector();
			break;
		}
	}
}