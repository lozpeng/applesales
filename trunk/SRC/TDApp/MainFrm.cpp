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
		TRACE0("��������������\n");
		return -1;      // fail to create
	};

	if (!m_wndWorkSpace.Create (_T("ͼ�����"), this, CRect (0, 0, 200, 200),
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
	//���˵�
	AddMainCategory();
	//��ͼ���
	AddTab_MapControl();
	//Ӱ�����
	AddTab_ImageAnalyse();
	//�仯����
	AddTab_ChangeDetect();
	//����Ҫ����ȡ
	AddTab_GeoInfoExtract();
	//ʸ���༭
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
	m_MainButton.SetToolTipText (_T("�ļ�"));
	m_MainButton.SetDescription (_T("�����˴��򿪡������ͼ�ļ�"));
	m_MainButton.SetID (ID_MAIN_BUTTON);

	m_wndRibbonBar.SetMainButton (&m_MainButton, CSize (45, 45));

	CBCGPRibbonMainPanel* pMainPanel = m_wndRibbonBar.AddMainCategory (
		_T("�ļ�"), IDB_FILESMALL, IDB_FILELARGE);
	
	pMainPanel->Add (new CBCGPRibbonButton (ID_NEWMAPCLASS, _T("�½���ͼ"), 0, 0));
	pMainPanel->Add (new CBCGPRibbonButton (ID_OPENMAPCLASS, _T("�򿪵�ͼ"), 1, 1));
	pMainPanel->Add (new CBCGPRibbonButton (ID_SAVEMAPCLASS, _T("�����ͼ"), 2, 2));
	//pMainPanel->Add (new CBCGPRibbonButton (ID_SAVEASMAPCLASS, _T("��ͼ���Ϊ..."), 3, 3));
}

//��ӵ�ͼ��ʾ�˵�
void CMainFrame::AddTab_MapControl()
{
	CBCGPRibbonCategory* pCategory = m_wndRibbonBar.AddCategory (
		_T("��ʼ"),
		IDB_ZOOMBARSMALL,
		IDB_ZOOMBAR);
	
	//�������̹���
	CBCGPRibbonPanel* pPanelProject = pCategory->AddPanel (
		_T("����"));
	CBCGPRibbonButton* pBtnNewXTD = new CBCGPRibbonButton (ID_NEWMAPCLASS, _T("�½�"), 11, 11);
	pPanelProject->Add (pBtnNewXTD);
	CBCGPRibbonButton* pBtnOpenXTD = new CBCGPRibbonButton (ID_OPENMAPCLASS, _T("��"), 12,12);
	pPanelProject->Add (pBtnOpenXTD);
	CBCGPRibbonButton* pBtnSaveXTD = new CBCGPRibbonButton (ID_SAVEMAPCLASS, _T("����"), 13,13);
	pPanelProject->Add (pBtnSaveXTD);
	/*CBCGPRibbonButton* pBtnSaveAsXTD = new CBCGPRibbonButton (ID_SAVEASMAPCLASS, _T("���Ϊ"), 14,14);
	pPanelProject->Add (pBtnSaveAsXTD);*/
	//ͼ��
	CBCGPRibbonPanel* pPanelFile = pCategory->AddPanel (_T("�ļ�"));
	CBCGPRibbonComboBox* pDisplayCombo = new CBCGPRibbonComboBox (ID_DUMMY_COMBO, FALSE, 50, "������:");
	pDisplayCombo->EnableDropDownListResize (FALSE);
	pDisplayCombo->AddItem(_T("1:1000"));
	pDisplayCombo->AddItem(_T("1:10000"));
	pDisplayCombo->AddItem(_T("1:50000"));
	pDisplayCombo->AddItem(_T("1:100000"));
	pDisplayCombo->AddItem(_T("1:250000"));
	pDisplayCombo->AddItem(_T("1:500000"));
	pDisplayCombo->AddItem(_T("1:1000000"));
	pPanelFile->Add (pDisplayCombo);
	//��������
	CBCGPRibbonButton* pPanelRaster = new CBCGPRibbonButton (ID_OPEN_IMG, _T("դ�����ݼ���"), 20);
	pPanelFile->Add (pPanelRaster);
	CBCGPRibbonButton* pPanelFeature = new CBCGPRibbonButton (ID_OPEN_Vector, _T("ʸ�����ݼ���"), 21);
	pPanelFile->Add (pPanelFeature);

	//������ͼ��������
	CBCGPRibbonPanel* pPanelMap = pCategory->AddPanel (_T("�������"));
	//--------------------------
	// �Ŵ�:
	//--------------------------
	CBCGPRibbonButton* pBtnZoomIn = new CBCGPRibbonButton (ID_MAP_ZOOM_IN, _T("�Ŵ�"), 0, 0);
	pPanelMap->Add (pBtnZoomIn);
	//--------------------------
	// ��С:
	//--------------------------
	CBCGPRibbonButton* pBtnZoomOut = new CBCGPRibbonButton (ID_ZOOM_OUT,_T("��С"), 1, 1);
	pPanelMap->Add (pBtnZoomOut);
	//--------------------------
	// ��Ŵ�:
	//--------------------------
	//CBCGPRibbonButton* pBtnPZoomIn = new CBCGPRibbonButton (ID_FIXEDZOOM_IN, _T("��Ŵ�"), 2, 2);
	//pPanelMap->Add (pBtnPZoomIn);
	////--------------------------
	//// ����С:
	////--------------------------
	//CBCGPRibbonButton* pBtnPZoomOut = new CBCGPRibbonButton (ID_FIXEDZOOM_OUT, _T("����С"), 3, 3);
	//pPanelMap->Add (pBtnPZoomOut);
	//--------------------------
	// ����:
	//--------------------------

	CBCGPRibbonButton* pBtnPan = new CBCGPRibbonButton (ID_MAP_PAN, _T("����"), 4, 4);
	pPanelMap->Add (pBtnPan);
	//--------------------------
	// ȫͼ:
	//--------------------------
	CBCGPRibbonButton* pBtnOvewView = new CBCGPRibbonButton (ID_MAP_FULLVIEW,_T("ȫͼ"), 5, 5);
	pPanelMap->Add (pBtnOvewView);

	//--------------------------
	// ǰһ��ͼ:
	//--------------------------
	CBCGPRibbonButton* pBtnPreView = new CBCGPRibbonButton (ID_PRE_EXTENT, _T("ǰ��ͼ"), 7, 7);
	pPanelMap->Add (pBtnPreView);


	//--------------------------
	// ��һ��ͼ:
	//--------------------------
	CBCGPRibbonButton* pBtnNextView = new CBCGPRibbonButton (ID_NEXT_EXTENT, _T("����ͼ"), 8, 8);
	pPanelMap->Add (pBtnNextView);

	//

	//CBCGPRibbonPanel* pPanelLabel = pCategory->AddPanel (_T("��湤��"));
	////--------------------------
	//// ѡ��:
	////--------------------------
	//CBCGPRibbonButton* pBtnSelected = new CBCGPRibbonButton(ID_DRAW_SELECT, _T("ѡ��"), -1, 0);
	//pPanelLabel->Add (pBtnSelected);
	////--------------------------
	//// ʸ��Ҫ��:
	////--------------------------
	//CBCGPRibbonButton* pBtnRect = new CBCGPRibbonButton (ID_DRAW_RECT, _T("����"), -1, 1);
	//pPanelLabel->Add (pBtnRect);
	////--------------------------
	//// ʸ��Ҫ��:
	////--------------------------
	//CBCGPRibbonButton* pBtnPolygon = new CBCGPRibbonButton(ID_DRAW_POLYGON, _T("�����"), -1, 4);
	//pPanelLabel->Add (pBtnPolygon);		
	////--------------------------
	////��ӱ���߹���
	////--------------------------
	//CBCGPRibbonButton* pBtnPolyline = new CBCGPRibbonButton(ID_DRAW_POLYLINE, _T("�����"), -1, 5);
	//pPanelLabel->Add (pBtnPolyline);	
	//// ����:
	////--------------------------
	//CBCGPRibbonButton* pBtnPoint = new CBCGPRibbonButton(ID_DRAW_MARKER, _T("��"), -1, 8);
	//pPanelLabel->Add (pBtnPoint);

	////--------------------------
	//// �ı����:
	////--------------------------
	//CBCGPRibbonButton* pBtnText = new CBCGPRibbonButton(ID_DRAW_TEXT, _T("�ı�"), -1, 9);
	//pPanelLabel->Add (pBtnText);

	//////--------------------------
	////// ����ͼƬ:
	//////--------------------------
	//CBCGPRibbonButton* pBtnPic = new CBCGPRibbonButton(ID_DRAW_CURVE, _T("����"), -1, 11);
	//pPanelLabel->Add (pBtnPic); 

	////--------------------------
	////�����תѡ��Ҫ�ع���
	////--------------------------
	//CBCGPRibbonButton* pBtnRotationElement = new CBCGPRibbonButton(ID_DRAW_HANDLINE, _T("�ֻ�"), -1, 5);
	//pPanelLabel->Add (pBtnRotationElement);
	//
	////--------------------------
	////��ӱ༭ѡ��Ҫ�ع���Ҫ�ع���
	////--------------------------
	//CBCGPRibbonButton* pBtnEditNodeElement = new CBCGPRibbonButton(ID_DRAW_EDITOR, _T("�༭���"), -1, 5);
	//pPanelLabel->Add (pBtnEditNodeElement);

	////--------------------------
	////�����Ҫ�ر���Ϊshp
	////--------------------------
	//CBCGPRibbonButton* pBtnElementSaveAs = new CBCGPRibbonButton(ID_DRAW_SAVEAS, _T("����"), -1, 17);
	//pPanelLabel->Add (pBtnElementSaveAs);

	CBCGPRibbonPanel* pPanelSystem = pCategory->AddPanel (_T("ϵͳ"));
	CBCGPRibbonButton* pBtnSetting = new CBCGPRibbonButton (ID_SETTING,_T("����"), 3, 22);
	pPanelSystem->Add(pBtnSetting);
	CBCGPRibbonButton* pBtnHelp = new CBCGPRibbonButton (ID_FOR_HELP,_T("����"), 1, 26);
	pPanelSystem->Add(pBtnHelp);
	CBCGPRibbonButton* pBtnClose = new CBCGPRibbonButton (ID_FOR_EXIT,_T("�˳�"), 2, 25);
	pPanelSystem->Add(pBtnClose);
}

void CMainFrame::AddTab_ImageAnalyse()
{
	CBCGPRibbonCategory* pCategory = m_wndRibbonBar.AddCategory (
		_T("Ӱ����ǿ"),
		IDB_FILESMALL,
		IDB_FILELARGE);

	//��ӵ�ǰͼ��
	CBCGPRibbonPanel* pPanelTargetLayer = pCategory->AddPanel (_T("��ʾ"));
	CBCGPRibbonComboBox* pBtnCurrLayer = new CBCGPRibbonComboBox(ID_CURRLAYER_COMBO,FALSE,80,"Ŀ���:");
	pPanelTargetLayer->Add(pBtnCurrLayer);
	CBCGPRibbonButton* pBtnShowOverView = new CBCGPRibbonButton (ID_ZOOMTO_LYREXTENT, _T("���ŵ�ͼ�㷶Χ"), 1);
	pPanelTargetLayer->Add (pBtnShowOverView);
	CBCGPRibbonButton* pBtnHideOverView = new CBCGPRibbonButton (ID_ZOOMTO_LYRRESOLUTION, _T("1:1��ʾ"), 0);
	pPanelTargetLayer->Add (pBtnHideOverView);
	pPanelTargetLayer->AddSeparator();

	
	pPanelTargetLayer->Add (new CBCGPRibbonLabel (_T("   ��  ��:")));
	CBCGPRibbonButton* pBtnBright = new CBCGPRibbonButton (ID_BRIGHT_RESTORE, _T("��  ��:"),3);
	pPanelTargetLayer->Add (pBtnBright);
	CBCGPRibbonButton* pBtnContrast = new CBCGPRibbonButton (ID_CONTRAST_RESTORE, _T("�Աȶ�:"), 4);
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
	CBCGPRibbonButton* pBtnTrans = new CBCGPRibbonButton (ID_TRANSPARENT_RESTORE, _T("͸����:"), 5);
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
	CBCGPRibbonButton* pBtnSwipView = new CBCGPRibbonButton (ID_SWIPE, _T("����"),0,3);
	pPanelTargetLayer->Add ( pBtnSwipView);
	CBCGPRibbonButton* pBtnStretch = new CBCGPRibbonButton (ID_RASLUT_EDIT, _T("��˸"),1,4);
	pPanelTargetLayer->Add ( pBtnStretch);
}

void CMainFrame::AddTab_Editor()
{
	CBCGPRibbonCategory* pCategory = m_wndRibbonBar.AddCategory (
		_T("ʸ���༭"),
		IDB_EDITORSMALL,
		IDB_EDITORLARGE);

		


	//�����༭��������
	CBCGPRibbonPanel* pPanelEditor = pCategory->AddPanel (_T("�༭����"));
	//��ӵ�ǰͼ��
	pPanelEditor->Add (new CBCGPRibbonLabel (_T("�༭Ŀ��㣺")));
	CBCGPRibbonComboBox* pBtnCurrLayer = new CBCGPRibbonComboBox(ID_CURRLAYER_COMBO_VECTOR,FALSE,100,"");

	pPanelEditor->Add(pBtnCurrLayer);
	CBCGPRibbonButton* pBtnShowOverView = new CBCGPRibbonButton (ID_ZOOMTO_LYREXTENT, _T("���ŵ�ͼ�㷶Χ"), 1);
	pPanelEditor->Add (pBtnShowOverView);

	pPanelEditor->AddSeparator();
	//--------------------------
	// ��ʼ�༭:
	//--------------------------
	CBCGPRibbonButton* pBtnEditStart = new CBCGPRibbonButton (ID_EDITOR_START, _T("��ʼ�༭"), 0, 0);
	pPanelEditor->Add (pBtnEditStart);
	//--------------------------
	// ����:
	//--------------------------
	CBCGPRibbonButton* pBtnEditSketch = new CBCGPRibbonButton (ID_EDITOR_SKETCH,_T("����"), 1, 1);
	pPanelEditor->Add (pBtnEditSketch);
	//--------------------------
	// �༭:
	//--------------------------
	CBCGPRibbonButton* pBtnEdit = new CBCGPRibbonButton (ID_EDITOR_EDIT, _T("�༭"), 2, 2);
	pPanelEditor->Add (pBtnEdit);
	//--------------------------
	// ����:
	//--------------------------

	CBCGPRibbonButton* pBtnEditUndo = new CBCGPRibbonButton (ID_EDITOR_UNDO, _T("����"), 3, 3);
	pPanelEditor->Add (pBtnEditUndo);
	//--------------------------
	// �ظ�:
	//--------------------------
	CBCGPRibbonButton* pBtnEditRedo = new CBCGPRibbonButton (ID_EDITOR_REDO, _T("�ظ�"), 4, 4);
	pPanelEditor->Add (pBtnEditRedo);

	//--------------------------
	// �����༭:
	//--------------------------
	CBCGPRibbonButton* pBtnEditEnd = new CBCGPRibbonButton (ID_EDITOR_END,_T("�����༭"), 5, 5);
	pPanelEditor->Add (pBtnEditEnd);

	//--------------------------
	// ����:
	//--------------------------
	CBCGPRibbonButton* pBtnEditSave = new CBCGPRibbonButton (ID_EDITOR_SAVE, _T("����"), 6, 6);
	pPanelEditor->Add (pBtnEditSave);
	//--------------------------
	// ɾ��:
	//--------------------------
	CBCGPRibbonButton* pBtnEditDel = new CBCGPRibbonButton (ID_DELETE_FEATURES, _T("ɾ��"), 7, 7);
	pPanelEditor->Add (pBtnEditDel);
	//--------------------------
	// �ϲ�Ҫ��:
	//--------------------------
	CBCGPRibbonButton* pBtnEditUnion = new CBCGPRibbonButton (ID_UNION_FEATURES, _T("�ϲ�Ҫ��"), 8, 8);
	pPanelEditor->Add (pBtnEditUnion);

	//--------------------------
	// Ҫ�����Ա༭:
	//--------------------------
	CBCGPRibbonButton* pBtnAtiEdit = new CBCGPRibbonButton (ID_ATTRIBUTE_EDIT, _T("���Ա༭"), 9, 9);
	pPanelEditor->Add (pBtnAtiEdit);


	//--------------------------
	// Ҫ����Ϣ:
	//--------------------------
	CBCGPRibbonButton* pBtnFeatureInfo = new CBCGPRibbonButton (ID_FEATURES_INFO, _T("Ҫ����Ϣ"), 10, 10);
	pPanelEditor->Add (pBtnFeatureInfo);

	//--------------------------
	// Ҫ��ѡ��:
	//--------------------------
	CBCGPRibbonButton* pBtnFeatureSelect = new CBCGPRibbonButton (ID_SELECTFEATURE, _T("Ҫ��ѡ��"), 11, 11);
	pPanelEditor->Add (pBtnFeatureSelect);

	//--------------------------
	// ��������:
	//--------------------------
	CBCGPRibbonButton* pBtnIncrementalImport = new CBCGPRibbonButton (ID_IncrementalImport, _T("��������"), 12, 12);
	pPanelEditor->Add (pBtnIncrementalImport);

}

void CMainFrame::AddTab_GeoInfoExtract()
{
	CBCGPRibbonCategory* pCategory = m_wndRibbonBar.AddCategory (
		_T("����Ҫ����ȡ"),
		IDB_FILELARGE,
		IDB_ChangeDetect);




	CBCGPRibbonPanel* pPanelLabel = pCategory->AddPanel (_T("�ֶ���ȡ����"));
	//--------------------------
	// ѡ��:
	//--------------------------
	CBCGPRibbonButton* pBtnSelected = new CBCGPRibbonButton(ID_DRAW_SELECT, _T("ѡ��"), -1, 2);
	pPanelLabel->Add (pBtnSelected);

	//--------------------------
	// ɾ��ȫ��:
	//--------------------------
	CBCGPRibbonButton* pBtnDelAll = new CBCGPRibbonButton(ID_DEL_ALL, _T("ɾ��ȫ��"), -1, 14);
	pPanelLabel->Add (pBtnDelAll);

	//--------------------------
	// ʸ��Ҫ��:
	//--------------------------
	CBCGPRibbonButton* pBtnRect = new CBCGPRibbonButton (ID_DRAW_RECT, _T("����"), -1, 3);
	pPanelLabel->Add (pBtnRect);
	//--------------------------
	// ʸ��Ҫ��:
	//--------------------------
	CBCGPRibbonButton* pBtnPolygon = new CBCGPRibbonButton(ID_DRAW_POLYGON, _T("�����"), -1, 4);
	pPanelLabel->Add (pBtnPolygon);		
	//--------------------------
	//��ӱ���߹���
	//--------------------------
	CBCGPRibbonButton* pBtnPolyline = new CBCGPRibbonButton(ID_DRAW_POLYLINE, _T("�����"), -1, 5);
	pPanelLabel->Add (pBtnPolyline);	
	// ����:
	//--------------------------
	CBCGPRibbonButton* pBtnPoint = new CBCGPRibbonButton(ID_DRAW_MARKER, _T("��"), -1, 6);
	pPanelLabel->Add (pBtnPoint);

	//--------------------------
	//��ӱ༭ѡ��Ҫ�ع���Ҫ�ع���
	//--------------------------
	CBCGPRibbonButton* pBtnEditNodeElement = new CBCGPRibbonButton(ID_DRAW_EDITOR, _T("�༭���"), -1, 7);
	pPanelLabel->Add (pBtnEditNodeElement);

	//--------------------------
	//�����Ҫ�ر���Ϊshp
	//--------------------------
	CBCGPRibbonButton* pBtnElementSaveAs = new CBCGPRibbonButton(ID_DRAW_SAVEAS, _T("����"), -1, 8);
	pPanelLabel->Add (pBtnElementSaveAs);
	//--------------------------
	//�����Ҫ�ر���Ϊshp
	//--------------------------
	CBCGPRibbonButton* pBtnElementExport = new CBCGPRibbonButton(ID_DRAW_Export, _T("��������"), -1, 8);
	pPanelLabel->Add (pBtnElementExport);

	//���Զ���ȡ
	CBCGPRibbonPanel* pPanelHalfAuto = pCategory->AddPanel (_T("���Զ���ȡ����"));

	//��ӵ�ǰͼ��
	//CBCGPRibbonButtonsGroup* pMagicGroup = new CBCGPRibbonButtonsGroup;

	CBCGPRibbonComboBox* pBtnCurrLayer = new CBCGPRibbonComboBox(ID_MAGICSTICK_LAYER,FALSE,85,"Ŀ��ͼ��:");
	pPanelHalfAuto->Add(pBtnCurrLayer);
	CBCGPRibbonEdit *pEditButton =new CBCGPRibbonEdit(ID_MAGICSTICK_TOL,100,"������ֵ:");
	pEditButton->SetEditText("20");
    pPanelHalfAuto->Add(pEditButton);

//--------------------------
	// ħ����
	//--------------------------
	CBCGPRibbonButton* pBtnMagic = new CBCGPRibbonButton (ID_MAGIC_STICK, _T("ħ������ȡ"), 10, 10);

    pPanelHalfAuto->Add (pBtnMagic);

	// ɾ���ϴ�ħ������ȡ���
	//--------------------------
	CBCGPRibbonButton* pBtnRemoveMagic = new CBCGPRibbonButton (ID_REMOVELASTMAGIC, _T("ȡ���ϴβ���"), 12, 12);

	pPanelHalfAuto->Add (pBtnRemoveMagic);

	pPanelHalfAuto->AddSeparator();
	
	
	//--------------------------
	// ��Ե��ȡ
	//--------------------------
	CBCGPRibbonButton* pBtnEdge = new CBCGPRibbonButton (ID_EDGE_EXTRACT,_T("�߽������ȡ"), 0, 0);
	pPanelHalfAuto->Add (pBtnEdge);

	//ˮ���Զ���ȡ
	CBCGPRibbonPanel* pPanelAuto = pCategory->AddPanel (_T("�Զ���ȡ"));
	//--------------------------
	// ˮ���Զ�
	//--------------------------
	CBCGPRibbonButton* pBtnWater = new CBCGPRibbonButton (ID_WATER_EXTRACT, _T("ˮ���Զ���ȡ"), 11, 11);
	pPanelAuto->Add (pBtnWater);

	//����
	//CBCGPRibbonPanel* pPanelBlueTooth = pCategory->AddPanel (_T("�ļ�����"));
	//--------------------------
	// ��������
	//--------------------------
	/*CBCGPRibbonButton* pBtnBlue = new CBCGPRibbonButton (ID_SEND_BLUEFILE, _T("��������"), 13, 13);
	pPanelBlueTooth->Add (pBtnBlue);*/
}

void CMainFrame::AddTab_ChangeDetect()
{
	CBCGPRibbonCategory* pCategory = m_wndRibbonBar.AddCategory (
		_T("�仯���"),
		IDB_FILELARGE,
		IDB_ChangeDetect);


	CBCGPRibbonPanel* pPanel = pCategory->AddPanel (_T("�仯���ֹ���"));
	//--------------------------
	// �仯���
	//--------------------------
	CBCGPRibbonButton* pBtnChange = new CBCGPRibbonButton (ID_CHANGE_DETECT, _T("�仯����"), 1, 1);
	pPanel->Add (pBtnChange);
	//--------------------------
	// �仯��ʶ
	//--------------------------
	/*CBCGPRibbonButton* pBtnChangeRender = new CBCGPRibbonButton (ID_CHANGE_RENDER,_T("��ȡ����"), 9, 9);
	pPanel->Add (pBtnChangeRender);*/


	//--------------------------
	// �仯�������
	//--------------------------
	CBCGPRibbonButton* pBtnChangeExport = new CBCGPRibbonButton (ID_CHANGE_SETSYMBOL,_T("�仯��ʶ"), -1, 8);
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	Control::CImageProcessTool::ReleaseSheets();
	CBCGPFrameWnd::OnClose();
}
