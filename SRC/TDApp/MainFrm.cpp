// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "TDApp.h"

#include "MainFrm.h"
#include "imgprocessUI/ImageProcessTool.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CBCGPFrameWnd)

const int  iMaxUserToolbars		= 10;
const UINT uiFirstUserToolBarId	= AFX_IDW_CONTROLBAR_FIRST + 40;
const UINT uiLastUserToolBarId	= uiFirstUserToolBarId + iMaxUserToolbars - 1;

BEGIN_MESSAGE_MAP(CMainFrame, CBCGPFrameWnd)
	ON_WM_CREATE()
	// Global help commands
	ON_COMMAND(ID_HELP_FINDER, CBCGPFrameWnd::OnHelpFinder)
	ON_COMMAND(ID_HELP, CBCGPFrameWnd::OnHelp)
	ON_COMMAND(ID_CONTEXT_HELP, CBCGPFrameWnd::OnContextHelp)
	ON_COMMAND(ID_DEFAULT_HELP, CBCGPFrameWnd::OnHelpFinder)
	ON_WM_CLOSE()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{

	m_nAppLook = theApp.GetInt (_T("ApplicationLook"), ID_VIEW_APPLOOK_WIN7);
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
		TRACE0("创建工具条错误\n");
		return -1;      // fail to create
	};

	if (!m_wndWorkSpace.Create (_T("图层管理"), this, CRect (0, 0, 200, 200),
		TRUE, ID_VIEW_WORKSPACE,
		WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI))
	{
		TRACE0("Failed to create Workspace bar\n");
		return -1;      // fail to create
	}

	m_wndWorkSpace.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndWorkSpace);

	// VISUAL_MANAGER
	return 0;
}
BOOL CMainFrame::CreateRibbonBar()
{
	if (!m_wndRibbonBar.Create (this))
	{
		return -1;      // fail to create
	}
	//-------------------
	// Load panel images:
	//-------------------
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
	//影像分析
	AddTab_ImageAnalyse();
	//变化发现
	AddTab_ChangeDetect();
	//地理要素提取
	AddTab_GeoInfoExtract();
	//矢量编辑
	AddTab_Editor();
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
	m_MainButton.SetImage (IDB_MIAN);
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
	//--------------------------
	// 点放大:
	//--------------------------
	//CBCGPRibbonButton* pBtnPZoomIn = new CBCGPRibbonButton (ID_FIXEDZOOM_IN, _T("点放大"), 2, 2);
	//pPanelMap->Add (pBtnPZoomIn);
	////--------------------------
	//// 点缩小:
	////--------------------------
	//CBCGPRibbonButton* pBtnPZoomOut = new CBCGPRibbonButton (ID_FIXEDZOOM_OUT, _T("点缩小"), 3, 3);
	//pPanelMap->Add (pBtnPZoomOut);
	//--------------------------
	// 漫游:
	//--------------------------

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

	//

	//CBCGPRibbonPanel* pPanelLabel = pCategory->AddPanel (_T("标绘工具"));
	////--------------------------
	//// 选择:
	////--------------------------
	//CBCGPRibbonButton* pBtnSelected = new CBCGPRibbonButton(ID_DRAW_SELECT, _T("选择"), -1, 0);
	//pPanelLabel->Add (pBtnSelected);
	////--------------------------
	//// 矢量要素:
	////--------------------------
	//CBCGPRibbonButton* pBtnRect = new CBCGPRibbonButton (ID_DRAW_RECT, _T("矩形"), -1, 1);
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
	//CBCGPRibbonButton* pBtnPoint = new CBCGPRibbonButton(ID_DRAW_MARKER, _T("点"), -1, 8);
	//pPanelLabel->Add (pBtnPoint);

	////--------------------------
	//// 文本标绘:
	////--------------------------
	//CBCGPRibbonButton* pBtnText = new CBCGPRibbonButton(ID_DRAW_TEXT, _T("文本"), -1, 9);
	//pPanelLabel->Add (pBtnText);

	//////--------------------------
	////// 插入图片:
	//////--------------------------
	//CBCGPRibbonButton* pBtnPic = new CBCGPRibbonButton(ID_DRAW_CURVE, _T("曲线"), -1, 11);
	//pPanelLabel->Add (pBtnPic); 

	////--------------------------
	////添加旋转选择要素工具
	////--------------------------
	//CBCGPRibbonButton* pBtnRotationElement = new CBCGPRibbonButton(ID_DRAW_HANDLINE, _T("手绘"), -1, 5);
	//pPanelLabel->Add (pBtnRotationElement);
	//
	////--------------------------
	////添加编辑选择要素工具要素工具
	////--------------------------
	//CBCGPRibbonButton* pBtnEditNodeElement = new CBCGPRibbonButton(ID_DRAW_EDITOR, _T("编辑结点"), -1, 5);
	//pPanelLabel->Add (pBtnEditNodeElement);

	////--------------------------
	////将标绘要素保存为shp
	////--------------------------
	//CBCGPRibbonButton* pBtnElementSaveAs = new CBCGPRibbonButton(ID_DRAW_SAVEAS, _T("导出"), -1, 17);
	//pPanelLabel->Add (pBtnElementSaveAs);

	CBCGPRibbonPanel* pPanelSystem = pCategory->AddPanel (_T("系统"));
	CBCGPRibbonButton* pBtnSetting = new CBCGPRibbonButton (ID_SETTING,_T("设置"), 3, 22);
	pPanelSystem->Add(pBtnSetting);
	CBCGPRibbonButton* pBtnHelp = new CBCGPRibbonButton (ID_FOR_HELP,_T("帮助"), 1, 26);
	pPanelSystem->Add(pBtnHelp);
	CBCGPRibbonButton* pBtnClose = new CBCGPRibbonButton (ID_FOR_EXIT,_T("退出"), 2, 25);
	pPanelSystem->Add(pBtnClose);
}

void CMainFrame::AddTab_ImageAnalyse()
{
	CBCGPRibbonCategory* pCategory = m_wndRibbonBar.AddCategory (
		_T("影像增强"),
		IDB_FILESMALL,
		IDB_FILELARGE);

	//添加当前图层
	CBCGPRibbonPanel* pPanelTargetLayer = pCategory->AddPanel (_T("显示"));
	CBCGPRibbonComboBox* pBtnCurrLayer = new CBCGPRibbonComboBox(ID_CURRLAYER_COMBO,FALSE,80,"目标层:");
	pPanelTargetLayer->Add(pBtnCurrLayer);
	CBCGPRibbonButton* pBtnShowOverView = new CBCGPRibbonButton (ID_ZOOMTO_LYREXTENT, _T("缩放到图层范围"), 1);
	pPanelTargetLayer->Add (pBtnShowOverView);
	CBCGPRibbonButton* pBtnHideOverView = new CBCGPRibbonButton (ID_ZOOMTO_LYRRESOLUTION, _T("1:1显示"), 0);
	pPanelTargetLayer->Add (pBtnHideOverView);
	pPanelTargetLayer->AddSeparator();

	
	pPanelTargetLayer->Add (new CBCGPRibbonLabel (_T("   调  整:")));
	CBCGPRibbonButton* pBtnBright = new CBCGPRibbonButton (ID_BRIGHT_RESTORE, _T("亮  度:"),3);
	pPanelTargetLayer->Add (pBtnBright);
	CBCGPRibbonButton* pBtnContrast = new CBCGPRibbonButton (ID_CONTRAST_RESTORE, _T("对比度:"), 4);
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
	CBCGPRibbonButton* pBtnTrans = new CBCGPRibbonButton (ID_TRANSPARENT_RESTORE, _T("透明度:"), 5);
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
	CBCGPRibbonButton* pBtnSwipView = new CBCGPRibbonButton (ID_SWIPE, _T("卷帘"),0,3);
	pPanelTargetLayer->Add ( pBtnSwipView);
	CBCGPRibbonButton* pBtnStretch = new CBCGPRibbonButton (ID_RASLUT_EDIT, _T("闪烁"),1,4);
	pPanelTargetLayer->Add ( pBtnStretch);
}

void CMainFrame::AddTab_Editor()
{
	CBCGPRibbonCategory* pCategory = m_wndRibbonBar.AddCategory (
		_T("矢量编辑"),
		IDB_EDITORSMALL,
		IDB_EDITORLARGE);

		


	//创建编辑基本操作
	CBCGPRibbonPanel* pPanelEditor = pCategory->AddPanel (_T("编辑工具"));
	//添加当前图层
	pPanelEditor->Add (new CBCGPRibbonLabel (_T("编辑目标层：")));
	CBCGPRibbonComboBox* pBtnCurrLayer = new CBCGPRibbonComboBox(ID_CURRLAYER_COMBO_VECTOR,FALSE,100,"");

	pPanelEditor->Add(pBtnCurrLayer);
	CBCGPRibbonButton* pBtnShowOverView = new CBCGPRibbonButton (ID_ZOOMTO_LYREXTENT, _T("缩放到图层范围"), 1);
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
	//--------------------------
	// 合并要素:
	//--------------------------
	CBCGPRibbonButton* pBtnEditUnion = new CBCGPRibbonButton (ID_UNION_FEATURES, _T("合并要素"), 8, 8);
	pPanelEditor->Add (pBtnEditUnion);

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

	//--------------------------
	// 增量导入:
	//--------------------------
	CBCGPRibbonButton* pBtnIncrementalImport = new CBCGPRibbonButton (ID_IncrementalImport, _T("增量导入"), 12, 12);
	pPanelEditor->Add (pBtnIncrementalImport);

}

void CMainFrame::AddTab_GeoInfoExtract()
{
	CBCGPRibbonCategory* pCategory = m_wndRibbonBar.AddCategory (
		_T("地理要素提取"),
		IDB_FILELARGE,
		IDB_ChangeDetect);




	CBCGPRibbonPanel* pPanelLabel = pCategory->AddPanel (_T("手动提取工具"));
	//--------------------------
	// 选择:
	//--------------------------
	CBCGPRibbonButton* pBtnSelected = new CBCGPRibbonButton(ID_DRAW_SELECT, _T("选择"), -1, 2);
	pPanelLabel->Add (pBtnSelected);

	//--------------------------
	// 删除全部:
	//--------------------------
	CBCGPRibbonButton* pBtnDelAll = new CBCGPRibbonButton(ID_DEL_ALL, _T("删除全部"), -1, 14);
	pPanelLabel->Add (pBtnDelAll);

	//--------------------------
	// 矢量要素:
	//--------------------------
	CBCGPRibbonButton* pBtnRect = new CBCGPRibbonButton (ID_DRAW_RECT, _T("矩形"), -1, 3);
	pPanelLabel->Add (pBtnRect);
	//--------------------------
	// 矢量要素:
	//--------------------------
	CBCGPRibbonButton* pBtnPolygon = new CBCGPRibbonButton(ID_DRAW_POLYGON, _T("多边形"), -1, 4);
	pPanelLabel->Add (pBtnPolygon);		
	//--------------------------
	//添加标绘线工具
	//--------------------------
	CBCGPRibbonButton* pBtnPolyline = new CBCGPRibbonButton(ID_DRAW_POLYLINE, _T("多段线"), -1, 5);
	pPanelLabel->Add (pBtnPolyline);	
	// 点标绘:
	//--------------------------
	CBCGPRibbonButton* pBtnPoint = new CBCGPRibbonButton(ID_DRAW_MARKER, _T("点"), -1, 6);
	pPanelLabel->Add (pBtnPoint);

	//--------------------------
	//添加编辑选择要素工具要素工具
	//--------------------------
	CBCGPRibbonButton* pBtnEditNodeElement = new CBCGPRibbonButton(ID_DRAW_EDITOR, _T("编辑结点"), -1, 7);
	pPanelLabel->Add (pBtnEditNodeElement);

	//--------------------------
	//将标绘要素保存为shp
	//--------------------------
	CBCGPRibbonButton* pBtnElementSaveAs = new CBCGPRibbonButton(ID_DRAW_SAVEAS, _T("导出"), -1, 8);
	pPanelLabel->Add (pBtnElementSaveAs);
	//--------------------------
	//将标绘要素保存为shp
	//--------------------------
	CBCGPRibbonButton* pBtnElementExport = new CBCGPRibbonButton(ID_DRAW_Export, _T("增量导出"), -1, 8);
	pPanelLabel->Add (pBtnElementExport);

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
	CBCGPRibbonButton* pBtnMagic = new CBCGPRibbonButton (ID_MAGIC_STICK, _T("魔术棒提取"), 10, 10);

    pPanelHalfAuto->Add (pBtnMagic);

	// 删除上次魔术棒提取结果
	//--------------------------
	CBCGPRibbonButton* pBtnRemoveMagic = new CBCGPRibbonButton (ID_REMOVELASTMAGIC, _T("取消上次操作"), 12, 12);

	pPanelHalfAuto->Add (pBtnRemoveMagic);

	pPanelHalfAuto->AddSeparator();
	
	
	//--------------------------
	// 边缘提取
	//--------------------------
	CBCGPRibbonButton* pBtnEdge = new CBCGPRibbonButton (ID_EDGE_EXTRACT,_T("边界跟踪提取"), 0, 0);
	pPanelHalfAuto->Add (pBtnEdge);

	//水体自动提取
	CBCGPRibbonPanel* pPanelAuto = pCategory->AddPanel (_T("自动提取"));
	//--------------------------
	// 水体自动
	//--------------------------
	CBCGPRibbonButton* pBtnWater = new CBCGPRibbonButton (ID_WATER_EXTRACT, _T("水体自动提取"), 11, 11);
	pPanelAuto->Add (pBtnWater);

	//蓝牙
	//CBCGPRibbonPanel* pPanelBlueTooth = pCategory->AddPanel (_T("文件发送"));
	//--------------------------
	// 蓝牙传送
	//--------------------------
	/*CBCGPRibbonButton* pBtnBlue = new CBCGPRibbonButton (ID_SEND_BLUEFILE, _T("蓝牙传送"), 13, 13);
	pPanelBlueTooth->Add (pBtnBlue);*/
}

void CMainFrame::AddTab_ChangeDetect()
{
	CBCGPRibbonCategory* pCategory = m_wndRibbonBar.AddCategory (
		_T("变化检测"),
		IDB_FILELARGE,
		IDB_ChangeDetect);


	CBCGPRibbonPanel* pPanel = pCategory->AddPanel (_T("变化发现工具"));
	//--------------------------
	// 变化检测
	//--------------------------
	CBCGPRibbonButton* pBtnChange = new CBCGPRibbonButton (ID_CHANGE_DETECT, _T("变化发现"), 1, 1);
	pPanel->Add (pBtnChange);
	//--------------------------
	// 变化标识
	//--------------------------
	/*CBCGPRibbonButton* pBtnChangeRender = new CBCGPRibbonButton (ID_CHANGE_RENDER,_T("提取样本"), 9, 9);
	pPanel->Add (pBtnChangeRender);*/


	//--------------------------
	// 变化结果导出
	//--------------------------
	CBCGPRibbonButton* pBtnChangeExport = new CBCGPRibbonButton (ID_CHANGE_SETSYMBOL,_T("变化标识"), -1, 8);
	pPanel->Add (pBtnChangeExport);
	

  
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CBCGPFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

Framework::IMaptreeCtrl* CMainFrame::GetTOC()
{
	return &m_wndWorkSpace.m_wndTree;
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
void CMainFrame::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	Control::CImageProcessTool::ReleaseSheets();
	CBCGPFrameWnd::OnClose();
}
