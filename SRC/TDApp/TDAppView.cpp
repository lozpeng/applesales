// TDAppView.cpp : implementation of the CTDAppView class
//

#include "stdafx.h"
#include "TDApp.h"

#include "TDAppDoc.h"
#include "TDAppView.h"

#include "ShapefileWorkspaceFactory.h"
#include "ShapefileWorkspace.h"
#include "ShapefileFeatureClass.h"
#include "FeatureLayer.h"
#include "RasterLayer.h"
#include "RasterWSFactory.h"
#include "RasterRGBRender.h"
#include "ProgressBar.h"
#include "MainFrm.h"
#include "CEditor.h"
#include "DlgDrawingExport.h"
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include "Tool/MagicStickTool.h"
#include "ImageProcessTool.h"
#include "ILayer.h"
#include "DlgIncrementalExport.h"
#include "DlgIncrementalImport.h"
#include "DlgBlueTooth.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTDAppView

IMPLEMENT_DYNCREATE(CTDAppView, CView)

BEGIN_MESSAGE_MAP(CTDAppView, CView)
	ON_WM_DESTROY()
	//ON_WM_SETFOCUS()
	ON_WM_SIZE()
	ON_WM_CREATE()


	ON_COMMAND(ID_FILE_PRINT, OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_OPEN_Vector, &CTDAppView::OnOpenVector)
	ON_COMMAND(ID_OPEN_IMG, &CTDAppView::OnOpenImg)
	ON_COMMAND(ID_LOAD_TARGET,&CTDAppView::OnLoadTarget)
	ON_COMMAND(ID_LINK_IMG,&CTDAppView::OnLinkImg)
	ON_COMMAND(ID_LINK_VECTOR,&CTDAppView::OnLinkVector)
	ON_COMMAND(ID_LOAD_DB,&CTDAppView::OnLoadDb)
	ON_COMMAND(ID_CHECK_RESULT,&CTDAppView::OnCheckResult)

	//浏览工具
	ON_COMMAND(ID_MAP_PAN, OnMapPan)
	ON_UPDATE_COMMAND_UI(ID_MAP_PAN, OnUpdateMapPan)
	ON_COMMAND(ID_MAP_ZOOM_IN, OnMapZoomin)
	ON_UPDATE_COMMAND_UI(ID_MAP_ZOOM_IN, OnUpdateMapZoomin)
	ON_COMMAND(ID_ZOOM_OUT, OnMapZoomout)
	ON_UPDATE_COMMAND_UI(ID_ZOOM_OUT, OnUpdateMapZoomout)
	ON_COMMAND(ID_MAP_FULLVIEW, OnMapFullView)

	ON_COMMAND(ID_PRE_EXTENT, OnMapPreExtent)
	ON_UPDATE_COMMAND_UI(ID_PRE_EXTENT, OnUpdateMapPreExtent)
	ON_COMMAND(ID_NEXT_EXTENT, OnMapNextExtent)
	ON_UPDATE_COMMAND_UI(ID_NEXT_EXTENT, OnUpdateMapNextExtent)



	ON_COMMAND(ID_POINT_SELECTFEATURE, OnSelectFeatureByPoint)
	ON_UPDATE_COMMAND_UI(ID_POINT_SELECTFEATURE, OnUpdateSelectFeatureByPoint)

	ON_COMMAND(ID_CURRLAYER_COMBO, OnCurrLayerCombo)
	ON_COMMAND(ID_CURRLAYER_COMBO_VECTOR, OnCurrLayerCombo_Vector)
	ON_UPDATE_COMMAND_UI(ID_CURRLAYER_COMBO_VECTOR,OnUpdateCurrlayerCombo_Vector)
	//调整
	ON_COMMAND(ID_BRIGHT_RESTORE, OnBrightRestore)
	ON_COMMAND(ID_BRIGHT_SLIDER, OnBrightSlider)
	ON_COMMAND(ID_CONTRAST_RESTORE, OnContrastRestore)
	ON_COMMAND(ID_CONTRAST_SLIDER, OnContrastSlider)
	ON_COMMAND(ID_TRANSPARENT_RESTORE, OnTransparentRestore)
	ON_COMMAND(ID_TRANSPARENT_SLIDER, OnTransparentSlider)

	ON_UPDATE_COMMAND_UI(ID_BRIGHT_RESTORE, OnUpdateBrightRestore)
	ON_UPDATE_COMMAND_UI(ID_BRIGHT_SLIDER, OnUpdateBrightSlider)
	ON_UPDATE_COMMAND_UI(ID_CONTRAST_RESTORE, OnUpdateContrastRestore)
	ON_UPDATE_COMMAND_UI(ID_CONTRAST_SLIDER, OnUpdateContrastSlider)
	ON_UPDATE_COMMAND_UI(ID_TRANSPARENT_RESTORE, OnUpdateTransparentRestore)
	ON_UPDATE_COMMAND_UI(ID_TRANSPARENT_SLIDER, OnUpdateTransparentSlider)

	ON_COMMAND(ID_SWIPE, OnSwipe)
	ON_UPDATE_COMMAND_UI(ID_SWIPE, OnUpdateSwipe)
	ON_COMMAND(ID_RASLUT_EDIT, OnFlick)
	ON_UPDATE_COMMAND_UI(ID_RASLUT_EDIT, OnUpdateFlick)
	//标绘工具

	ON_COMMAND(ID_DRAW_SELECT, OnDrawSelect)
	ON_UPDATE_COMMAND_UI(ID_DRAW_SELECT, OnUpdateDrawSelect)
    
	ON_COMMAND(ID_DEL_ALL, OnDelAll)

	ON_COMMAND(ID_DRAW_RECT, OnDrawRect)
	ON_UPDATE_COMMAND_UI(ID_DRAW_RECT, OnUpdateDrawRect)

	ON_COMMAND(ID_DRAW_MARKER, OnDrawMarker)
	ON_UPDATE_COMMAND_UI(ID_DRAW_MARKER, OnUpdateDrawMarker)

	ON_COMMAND(ID_DRAW_CIRCLE, OnDrawCircle)
	ON_UPDATE_COMMAND_UI(ID_DRAW_CIRCLE, OnUpdateDrawCircle)
	ON_COMMAND(ID_DRAW_POLYGON, OnDrawPolygon)
	ON_UPDATE_COMMAND_UI(ID_DRAW_POLYGON, OnUpdateDrawPolygon)
	ON_COMMAND(ID_DRAW_POLYLINE, OnDrawPolyline)
	ON_UPDATE_COMMAND_UI(ID_DRAW_POLYLINE, OnUpdateDrawPolyline)
	ON_COMMAND(ID_DRAW_CURVE, OnDrawCurve)
	ON_UPDATE_COMMAND_UI(ID_DRAW_CURVE, OnUpdateDrawCurve)
	ON_COMMAND(ID_DRAW_TEXT, OnDrawText)
	ON_UPDATE_COMMAND_UI(ID_DRAW_TEXT, OnUpdateDrawtext)

	ON_COMMAND(ID_DRAW_EDITOR, OnEditElement)
	ON_UPDATE_COMMAND_UI(ID_DRAW_EDITOR, OnUpdateEditElement)
	ON_COMMAND(ID_DRAW_Ellipse, OnDrawEllipse)
	ON_UPDATE_COMMAND_UI(ID_DRAW_Ellipse, OnUpdateDrawEllipse)
	ON_COMMAND(ID_DRAW_CalloutText, OnDrawCalloutText)
	ON_UPDATE_COMMAND_UI(ID_DRAW_CalloutText, OnUpdateDrawCalloutText)
	ON_COMMAND(ID_DRAW_HANDLINE, OnDrawFreeHandline)
	ON_UPDATE_COMMAND_UI(ID_DRAW_HANDLINE, OnUpdateDrawFreeHandline)
	ON_COMMAND(ID_DRAW_SAVEAS, OnDrawSaveAs)
	ON_UPDATE_COMMAND_UI(ID_DRAW_SAVEAS, OnUpdateDrawSaveAs)
	ON_COMMAND(ID_DRAW_Export, OnDrawExport)
	ON_UPDATE_COMMAND_UI(ID_DRAW_Export, OnUpdateDrawExport)
	//编辑工具
	
	ON_COMMAND(ID_EDITOR_START, OnEditorStart)
	ON_UPDATE_COMMAND_UI(ID_EDITOR_START, OnUpdateEditorStart)
	ON_COMMAND(ID_EDITOR_SKETCH, OnEditorSketch)
	ON_UPDATE_COMMAND_UI(ID_EDITOR_SKETCH, OnUpdateEditorSketch)
	ON_COMMAND(ID_EDITOR_EDIT, OnEditerEdit)
	ON_UPDATE_COMMAND_UI(ID_EDITOR_EDIT, OnUpdateEditerEdit)
	ON_COMMAND(ID_EDITOR_REDO, OnEditerRedo)
	ON_UPDATE_COMMAND_UI(ID_EDITOR_REDO, OnUpdateEditerRedo)
	ON_COMMAND(ID_EDITOR_UNDO, OnEditerUndo)
	ON_UPDATE_COMMAND_UI(ID_EDITOR_UNDO, OnUpdateEditerUndo)
	ON_COMMAND(ID_EDITOR_END, OnEditerEnd)
	ON_UPDATE_COMMAND_UI(ID_EDITOR_END, OnUpdateEditerEnd)
	ON_COMMAND(ID_EDITOR_SAVE, OnEditerSave)
	ON_UPDATE_COMMAND_UI(ID_EDITOR_SAVE, OnUpdateEditerSave)
	ON_COMMAND(ID_DELETE_FEATURES, OnEditerDel)
	ON_UPDATE_COMMAND_UI(ID_DELETE_FEATURES, OnUpdateEditerSave)
	ON_COMMAND(ID_UNION_FEATURES, OnEditerUnion)
	ON_UPDATE_COMMAND_UI(ID_UNION_FEATURES, OnUpdateEditerUnion)
	ON_COMMAND(ID_FEATURES_INFO, OnFeatureInfo)
	ON_COMMAND(ID_ATTRIBUTE_EDIT, OnEditerAttribute)
	ON_UPDATE_COMMAND_UI(ID_ATTRIBUTE_EDIT, OnUpdateEditerAttribute)
	ON_COMMAND(ID_SELECTFEATURE, OnSelectFeature)
	ON_UPDATE_COMMAND_UI(ID_SELECTFEATURE, OnUpdateSelectFeature)
	ON_COMMAND(ID_IncrementalImport, OnIncrementalImport)
	ON_UPDATE_COMMAND_UI(ID_IncrementalImport, OnUpdateIncrementalImport)

	
	ON_COMMAND(ID_CHANGE_DETECT, OnImgChangeDetect)
	ON_COMMAND(ID_TARGET_CLIP, OnImgTargetClip)
	ON_COMMAND(ID_CHANGE_TARGET,OnChangeTarget)
	ON_COMMAND(ID_CHANGE_RENDER, OnImgChangeRender)
	ON_COMMAND(ID_WATER_EXTRACT, OnWaterExtract)
	ON_COMMAND(ID_MAGIC_STICK, OnMagicStick)
	ON_UPDATE_COMMAND_UI(ID_MAGIC_STICK, OnUpdateMagicStick)
	

	ON_COMMAND(ID_MAGICSTICK_LAYER,OnMagicStickLayer)
	ON_COMMAND(ID_MAGICSTICK_TOL,OnMagicTol)

	ON_COMMAND(ID_MAGIC_STICK, OnMagicStick)
	
	ON_COMMAND(ID_REMOVELASTMAGIC,OnDeleteLastMagic)
	
	ON_COMMAND(ID_EDGE_EXTRACT,OnEdgeTrack)

	ON_COMMAND(ID_CHANGE_SETSYMBOL,OnChangeSetSymbol)

	ON_COMMAND(ID_SEND_BLUEFILE,OnSendBlueToothFile)

	ON_COMMAND(ID_FOR_HELP,OnOpenHelp)

	ON_REGISTERED_MESSAGE(BCGM_CHANGE_ACTIVE_TAB,OnChangeActiveTab)


END_MESSAGE_MAP()

//得到程序启动的路径
CString  GetAppPathName()
{
	TCHAR	szProgPath[MAX_PATH*2];
	::GetModuleFileName(NULL, szProgPath, sizeof(szProgPath)/sizeof(TCHAR));    
	CString PathName =szProgPath;
	CString  FileName= PathName;
	int     SplashPos=PathName.ReverseFind('\\');
	if(SplashPos>=2 && SplashPos<=PathName.GetLength()-4)
		FileName=PathName.Left(SplashPos);
	return FileName;
}


DWORD 	WinExecAndWait32(	LPCTSTR lpszAppPath,   // 执行程序的路径
		LPCTSTR lpParameters,  // 参数
		LPCTSTR lpszDirectory, // 执行环境目录
		DWORD dwMilliseconds)  // 最大等待时间, 超过这个时间强行终止
	{
		SHELLEXECUTEINFO ShExecInfo = {0};
		ShExecInfo.cbSize	= sizeof(SHELLEXECUTEINFO);
		ShExecInfo.fMask	= SEE_MASK_NOCLOSEPROCESS;
		ShExecInfo.hwnd		= NULL;
		ShExecInfo.lpVerb	= NULL;
		ShExecInfo.lpFile	= lpszAppPath;		
		ShExecInfo.lpParameters = lpParameters;	
		ShExecInfo.lpDirectory	= lpszDirectory;
		ShExecInfo.nShow	= SW_SHOWNORMAL;
		ShExecInfo.hInstApp = NULL;	
		ShellExecuteEx(&ShExecInfo);

		// 指定时间没结束
		if (WaitForSingleObject(ShExecInfo.hProcess, dwMilliseconds) == WAIT_TIMEOUT)
		{	// 强行杀死进程
			TerminateProcess(ShExecInfo.hProcess, 0);
			return 0;	//强行终止
		}

		DWORD dwExitCode;
		BOOL bOK = GetExitCodeProcess(ShExecInfo.hProcess, &dwExitCode);
		ASSERT(bOK);

		Sleep(1000);

		return dwExitCode;
	}


// CTDAppView construction/destruction

CTDAppView::CTDAppView()
{
	boost::function<void (Carto::ILayerPtr)> fundl = boost::bind(&CTDAppView::LayerDelEvent,this, _1);

	m_ConnectionMapLayerDeleted = Carto::CMap::RegisterDeleteLayer(fundl);
}

CTDAppView::~CTDAppView()
{
    m_ConnectionMapLayerDeleted.disconnect();
}

BOOL CTDAppView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CTDAppView drawing

void CTDAppView::OnDraw(CDC* pDC)
{
	CTDAppDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);


	m_MapCtrl.OnPaint();
}



// CTDAppView printing

void CTDAppView::OnFilePrintPreview()
{
	BCGPPrintPreview (this);
}

BOOL CTDAppView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CTDAppView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CTDAppView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CTDAppView::OnDestroy()
{
	CView::OnDestroy();
}



void CTDAppView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	m_WndTab.SetWindowPos (NULL, -1, -1, cx + 1, cy + 3,
		SWP_SHOWWINDOW | SWP_NOZORDER);

}

void CTDAppView::OnFilePrint()
{
	CPrintInfo printInfo;
	ASSERT(printInfo.m_pPD != NULL); 
	if (S_OK == COleDocObjectItem::DoDefaultPrinting(this, &printInfo))
		return;

	CView::OnFilePrint();

}

int CTDAppView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	m_WndTab.Create (CBCGPTabWnd::STYLE_3D_VS2005, CRect(0,0,0,0), this, ID_TABCONTROL);


	m_MapCtrl.CreateControl(Framework::CommonUIName::AppMapControl, &m_WndTab, ID_MAPCTRL);
	m_WndTab.AddTab( &m_MapCtrl , "Map" );

	//m_LayoutCtrl.CreateControl(Framework::CommonUIName::AppLayoutControl, &m_WndTab,ID_LAYOUTCTRL);
	//m_wndButton.Create(_T("Test"),WS_CHILD|WS_VISIBLE,CRect(0,0,10,20),&m_WndTab,IDC_TEST);
	//m_WndTab.AddTab(&m_LayoutCtrl,_T("Layout"));


	CTDAppDoc* pDoc = GetDocument();
	pDoc->SetLinkMapCtrl(&m_MapCtrl);
	pDoc->SetLinkLayoutCtrl(&m_LayoutCtrl);

	m_WndTab.SetActiveTab(0);
	m_WndTab.SetFlatFrame ();
	m_WndTab.SetTabBorderSize (0);
	m_WndTab.AutoDestroyWindow (FALSE);
	return true;
}

// CTDAppView diagnostics

#ifdef _DEBUG
void CTDAppView::AssertValid() const
{
	CView::AssertValid();
}

void CTDAppView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTDAppDoc* CTDAppView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTDAppDoc)));
	return (CTDAppDoc*)m_pDocument;
}


#endif //_DEBUG

CBCGPRibbonComboBox* CTDAppView::GetCurLyrCombox()
{
	CMainFrame* pMainFrm = (CMainFrame*)::AfxGetApp()->GetMainWnd();
	CBCGPRibbonComboBox* pCombox = (CBCGPRibbonComboBox*)pMainFrm->m_wndRibbonBar.FindByID(ID_CURRLAYER_COMBO);
	return pCombox;
}
CBCGPRibbonComboBox* CTDAppView::GetCurLyrCombox_Vector()
{
	CMainFrame* pMainFrm = (CMainFrame*)::AfxGetApp()->GetMainWnd();
	CBCGPRibbonComboBox* pCombox = (CBCGPRibbonComboBox*)pMainFrm->m_wndRibbonBar.FindByID(ID_CURRLAYER_COMBO_VECTOR);
	return pCombox;
}
// CTDAppView message handlers



//打开矢量数据
void CTDAppView::OnOpenVector()
{
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

	//_crtBreakAlloc = 9878;




	char	szBigBuf[4096] = "";
	CString fileName ="";

	CFileDialog dlg(true, "*.*", "",OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT|OFN_ALLOWMULTISELECT,"shapefile(*.shp)|*.shp|All file(*.*)|*.*|",this);
	dlg.m_ofn.lpstrFile = szBigBuf;
	dlg.m_ofn.nMaxFile = sizeof (szBigBuf);
	if(dlg.DoModal()==IDOK) 
	{
		POSITION pos = dlg.GetStartPosition();
		while (pos != NULL)
		{
			fileName = dlg.GetNextPathName (pos);
			this->GetDocument()->LoadShpFile(fileName);

		}
		m_MapCtrl.UpdateControl(drawAll);
		RefreshLayerCombo();
	}

	
}

void CTDAppView::OnOpenImg()
{
	char	szBigBuf[4096] = "";
	

	CString fileName("");
	CFileDialog dlg(true, "*.*", "",OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT|OFN_ALLOWMULTISELECT,"影像数据(*.tif;*.img;*.tiff;*.bmp)|*.tif;*.img;*.tiff;*.bmp|All Files(*.*)|*.*||",this);
	dlg.m_ofn.lpstrFile = szBigBuf;
	dlg.m_ofn.nMaxFile = sizeof (szBigBuf);

	if(dlg.DoModal()==IDOK) 
	{
		POSITION pos = dlg.GetStartPosition();
		while (pos != NULL)
		{
			fileName = dlg.GetNextPathName (pos);
			this->GetDocument()->LoadImageFile(fileName);

		}
       
		m_MapCtrl.UpdateControl(drawAll);
		RefreshLayerCombo();

	}
	
	
	
}


void CTDAppView::OnMapPan()
{
	//Framework::ITool* pTool = NULL;
	//m_LayoutCtrl.SetCurTool("LayoutPanTool");

	//pTool=Framework::ITool::FindTool("LayoutPanTool");
	//if(pTool)
	//{
	//	pTool->Initialize(dynamic_cast<Framework::IUIObject*>(&m_LayoutCtrl));
	//}
	Framework::ITool* pTool = NULL;
	m_MapCtrl.SetCurTool("MapPan");

	pTool=Framework::ITool::FindTool("MapPan");
	if(pTool)
	{
		pTool->Initialize(dynamic_cast<Framework::IUIObject*>(&m_MapCtrl));
	}
}

void CTDAppView::OnUpdateMapPan(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_MapCtrl.GetCurToolName() == "MapPan");

}

void CTDAppView::OnMapZoomin()
{
	Framework::ITool* pTool = NULL;
	m_MapCtrl.SetCurTool("MapZoomin");

	pTool=Framework::ITool::FindTool("MapZoomin");
	if(pTool)
	{
		pTool->Initialize(dynamic_cast<Framework::IUIObject*>(&m_MapCtrl));
	}
}

void CTDAppView::OnUpdateMapZoomin(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_MapCtrl.GetCurToolName() == "MapZoomin");
}

void CTDAppView::OnMapZoomout()
{
	Framework::ITool* pTool = NULL;
	m_MapCtrl.SetCurTool("MapZoomout");

	pTool=Framework::ITool::FindTool("MapZoomout");
	if(pTool)
	{
		pTool->Initialize(dynamic_cast<Framework::IUIObject*>(&m_MapCtrl));
	}
}

void CTDAppView::OnUpdateMapZoomout(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_MapCtrl.GetCurToolName() == "MapZoomout");
}

void CTDAppView::OnMapPreExtent()
{
	Carto::CMapPtr pMap =m_MapCtrl.GetMap();
	if(!pMap)
	{
		return;
	}
	pMap->GetDisplay()->GetDisplayTransformation().SetPreExtent();
	m_MapCtrl.UpdateControl(drawAll);
}

void CTDAppView::OnUpdateMapPreExtent(CCmdUI* pCmdUI)
{
	Carto::CMapPtr pMap =m_MapCtrl.GetMap();
	if(!pMap)
	{
		pCmdUI->Enable(FALSE);
	}
	pCmdUI->Enable(pMap->GetDisplay()->GetDisplayTransformation().HasPreExtent());
}

void CTDAppView::OnMapNextExtent()
{
	Carto::CMapPtr pMap =m_MapCtrl.GetMap();
	if(!pMap)
	{
		return;
	}
	pMap->GetDisplay()->GetDisplayTransformation().SetNextExtent();
	m_MapCtrl.UpdateControl(drawAll);
}

void CTDAppView::OnUpdateMapNextExtent(CCmdUI* pCmdUI)
{
	Carto::CMapPtr pMap =m_MapCtrl.GetMap();
	if(!pMap)
	{
		pCmdUI->Enable(FALSE);
	}
	pCmdUI->Enable(pMap->GetDisplay()->GetDisplayTransformation().HasNextExtent());
}

//全图显示
void CTDAppView::OnMapFullView()
{
	Carto::CMapPtr pMap =m_MapCtrl.GetMap();
	if(!pMap)
	{
		return;
	}
	GEOMETRY::geom::Envelope env = pMap->GetExtent();

	pMap->GetDisplay()->GetDisplayTransformation().FitViewBound(env);

	m_MapCtrl.UpdateControl(drawAll);
}




void CTDAppView::OnDrawRect()
{
	Framework::ITool* pTool = NULL;
	m_MapCtrl.SetCurTool("DrawRectElementTool");

	pTool=Framework::ITool::FindTool("DrawRectElementTool");
	if(pTool)
	{
		pTool->Initialize(dynamic_cast<Framework::IUIObject*>(&m_MapCtrl));
	}
}

void CTDAppView::OnUpdateDrawRect(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_MapCtrl.GetCurToolName() == "DrawRectElementTool");

}

void CTDAppView::OnDrawSelect()
{
	Framework::ITool* pTool = NULL;
	m_MapCtrl.SetCurTool("SelectElementTool");

	pTool=Framework::ITool::FindTool("SelectElementTool");
	if(pTool)
	{
		pTool->Initialize(dynamic_cast<Framework::IUIObject*>(&m_MapCtrl));
	}
}

void CTDAppView::OnUpdateDrawSelect(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_MapCtrl.GetCurToolName() == "SelectElementTool");

}

afx_msg void CTDAppView::OnDrawMarker()
{
	Framework::ITool* pTool = NULL;
	m_MapCtrl.SetCurTool("DrawSimpleMarkerElementTool");

	pTool=Framework::ITool::FindTool("DrawSimpleMarkerElementTool");
	if(pTool)
	{
		pTool->Initialize(dynamic_cast<Framework::IUIObject*>(&m_MapCtrl));
	}
}
afx_msg void CTDAppView::OnUpdateDrawMarker(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_MapCtrl.GetCurToolName() == "DrawSimpleMarkerElementTool");
}
afx_msg void CTDAppView::OnDrawCircle()
{
	Framework::ITool* pTool = NULL;
	m_MapCtrl.SetCurTool("DrawCircleElementTool");

	pTool=Framework::ITool::FindTool("DrawCircleElementTool");
	if(pTool)
	{
		pTool->Initialize(dynamic_cast<Framework::IUIObject*>(&m_MapCtrl));
	}
	//Framework::ICommand* pCommand = NULL;
	//m_MapCtrl.SetCurTool("UndoOperationCmd");

	//pCommand=Framework::ICommand::FindCommand("UndoOperationCmd");
	//if(pCommand)
	//{
	//	pCommand->Initialize(dynamic_cast<Framework::IUIObject*>(&m_MapCtrl));
	//	pCommand->Click();
	//}

}
afx_msg void CTDAppView::OnUpdateDrawCircle(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_MapCtrl.GetCurToolName() == "DrawCircleElementTool");
}
afx_msg void CTDAppView::OnDrawPolygon()
{
	Framework::ITool* pTool = NULL;
	m_MapCtrl.SetCurTool("DrawPolygonElementTool");

	pTool=Framework::ITool::FindTool("DrawPolygonElementTool");
	if(pTool)
	{
		pTool->Initialize(dynamic_cast<Framework::IUIObject*>(&m_MapCtrl));
	}
}
afx_msg void CTDAppView::OnUpdateDrawPolygon(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_MapCtrl.GetCurToolName() == "DrawPolygonElementTool");
}
afx_msg void CTDAppView::OnDrawPolyline()
{
	Framework::ITool* pTool = NULL;
	m_MapCtrl.SetCurTool("DrawPolylineElementTool");

	pTool=Framework::ITool::FindTool("DrawPolylineElementTool");
	if(pTool)
	{
		pTool->Initialize(dynamic_cast<Framework::IUIObject*>(&m_MapCtrl));
	}
}
afx_msg void CTDAppView::OnUpdateDrawPolyline(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_MapCtrl.GetCurToolName() == "DrawPolylineElementTool");
}
afx_msg void CTDAppView::OnDrawCurve()
{
	Framework::ITool* pTool = NULL;
	m_MapCtrl.SetCurTool("DrawBezierCurveElementTool");

	pTool=Framework::ITool::FindTool("DrawBezierCurveElementTool");
	if(pTool)
	{
		pTool->Initialize(dynamic_cast<Framework::IUIObject*>(&m_MapCtrl));
	}
}
afx_msg void CTDAppView::OnUpdateDrawCurve(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_MapCtrl.GetCurToolName() == "DrawBezierCurveElementTool");
}
afx_msg void CTDAppView::OnDrawText()
{
	Framework::ITool* pTool = NULL;
	m_MapCtrl.SetCurTool("DrawTextElementTool");

	pTool=Framework::ITool::FindTool("DrawTextElementTool");
	if(pTool)
	{
		pTool->Initialize(dynamic_cast<Framework::IUIObject*>(&m_MapCtrl));
	}
}
afx_msg void CTDAppView::OnUpdateDrawtext(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_MapCtrl.GetCurToolName() == "DrawTextElementTool");
}


afx_msg void CTDAppView::OnEditElement()
{
	Framework::ITool* pTool = NULL;
	m_MapCtrl.SetCurTool("EditElementVertixTool");

	pTool=Framework::ITool::FindTool("EditElementVertixTool");
	if(pTool)
	{
		pTool->Initialize(dynamic_cast<Framework::IUIObject*>(&m_MapCtrl));
	}
}
afx_msg void CTDAppView::OnUpdateEditElement(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_MapCtrl.GetCurToolName() == "EditElementVertixTool");
}

afx_msg void CTDAppView::OnDrawEllipse()
{
	Framework::ITool* pTool = NULL;
	m_MapCtrl.SetCurTool("DrawEllipseElementTool");

	pTool=Framework::ITool::FindTool("DrawEllipseElementTool");
	if(pTool)
	{
		pTool->Initialize(dynamic_cast<Framework::IUIObject*>(&m_MapCtrl));
	}
}
afx_msg void CTDAppView::OnUpdateDrawEllipse(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_MapCtrl.GetCurToolName() == "DrawEllipseElementTool");
}
afx_msg void CTDAppView::OnDrawCalloutText()
{
	Framework::ITool* pTool = NULL;
	m_MapCtrl.SetCurTool("DrawCalloutTextElementTool");

	pTool=Framework::ITool::FindTool("DrawCalloutTextElementTool");
	if(pTool)
	{
		pTool->Initialize(dynamic_cast<Framework::IUIObject*>(&m_MapCtrl));
	}
}
afx_msg void CTDAppView::OnUpdateDrawCalloutText(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_MapCtrl.GetCurToolName() == "DrawCalloutTextElementTool");
}


afx_msg void CTDAppView::OnDrawFreeHandline()
{
	Framework::ITool* pTool = NULL;
	m_MapCtrl.SetCurTool("DrawFreehandLineElement");

	pTool=Framework::ITool::FindTool("DrawFreehandLineElement");
	if(pTool)
	{
		pTool->Initialize(dynamic_cast<Framework::IUIObject*>(&m_MapCtrl));
	}
}
afx_msg void CTDAppView::OnUpdateDrawFreeHandline(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_MapCtrl.GetCurToolName() == "DrawFreehandLineElement");
}
afx_msg void CTDAppView::OnDrawSaveAs()
{
	//element 转成shp

	Carto::CMapPtr ipMap = m_MapCtrl.GetMap();
	Carto::CGraphicLayerPtr ipGraphicLayer = ipMap->GetGraphicLayer();
	long lElementCnt = ipGraphicLayer->GetElementCount();
	if(lElementCnt <1)return;

	CDlgDrawingExport Dlg;
	if(Dlg.DoModal()==IDOK)
	{
		char* fileName = Dlg.m_ExportPath.GetBuffer(Dlg.m_ExportPath.GetLength());

		Carto::CLayerArray &layers = ipMap->GetLayers();

		Carto::ILayerPtr pLayer;
		int index;
		bool bfind =false;
		bool flag = false;
		for(int i=0;i<layers.GetSize();i++)
		{
			pLayer =layers.GetAt(i);
			if(!pLayer)
			{
				continue;
			}
			if(pLayer->GetLayerType()==Carto::FeatureLayer)
			{
				if (strcmp(pLayer->GetName().c_str(),fileName) == 0)
				{
					flag = true;
					break;
				}
			}
		}
		if(flag)
		{
			Geodatabase::IWorkspace *pWorkspace = pLayer->GetDataObject()->GetWorkspace();
			//开始编辑
			bool srcState = pWorkspace->IsEditing();
			if(srcState== false)
				pWorkspace->StartEdit();
			Geodatabase::IFeatureClassPtr pFeatureClass =  (Geodatabase::IFeatureClassPtr) pLayer->GetDataObject();
			ipGraphicLayer->SaveElementAsShp(pFeatureClass,!Dlg.m_bExpoertAll,Dlg.m_DrawingType);

			pWorkspace->StopEditOperation();
			if(srcState == false)
				pWorkspace->StopEdit(true);
		}
		else
		{
			ipGraphicLayer->SaveElementAsShp(fileName,!Dlg.m_bExpoertAll,Dlg.m_DrawingType);

			if (Dlg.m_CheckAddMap)
			{	
				this->GetDocument()->LoadShpFile(fileName);
				RefreshLayerCombo();
			}
		}
		m_MapCtrl.UpdateControl((DrawContent)(drawElement | drawAll));
		
	}


}
afx_msg void CTDAppView::OnUpdateDrawSaveAs(CCmdUI* pCmdUI)
{

}
#include "DrawingIncrExport.h"
afx_msg void CTDAppView::OnDrawExport()
{
	//element 转成shp

	Carto::CMapPtr ipMap = m_MapCtrl.GetMap();
	Carto::CGraphicLayerPtr ipGraphicLayer = ipMap->GetGraphicLayer();
	long lElementCnt = ipGraphicLayer->GetElementCount();
	if(lElementCnt <1)
		return;
	CDrawingIncrExport dlg;
	if(dlg.DoModal()!=IDOK)
		return;

	CString targetLayerName_P = dlg.m_TargetLayerName_P;
	CString targetLayerName_L = dlg.m_TargetLayerName_L;
	CString targetLayerName_A = dlg.m_TargetLayerName_A;

	CString strIncrementalPath = dlg.m_ExportPath;
	ipGraphicLayer->IncrementalExport(strIncrementalPath.GetBuffer(strIncrementalPath.GetLength()),
		targetLayerName_P.GetBuffer(targetLayerName_P.GetLength()),
		targetLayerName_L.GetBuffer(targetLayerName_L.GetLength()),
		targetLayerName_A.GetBuffer(targetLayerName_A.GetLength()),
		dlg.m_bExpoertAll);
	strIncrementalPath.ReleaseBuffer();
	targetLayerName_P.ReleaseBuffer();
	targetLayerName_L.ReleaseBuffer();
	targetLayerName_A.ReleaseBuffer();
	m_MapCtrl.UpdateControl((DrawContent)(drawElement | drawAll));

	


}
afx_msg void CTDAppView::OnUpdateDrawExport(CCmdUI* pCmdUI)
{

}

void CTDAppView::OnSelectFeatureByPoint()
{
	Framework::ITool* pTool = NULL;
	m_MapCtrl.SetCurTool("SelectbyPoint");

	pTool=Framework::ITool::FindTool("SelectbyPoint");
	if(pTool)
	{
		pTool->Initialize(dynamic_cast<Framework::IUIObject*>(&m_MapCtrl));
	}
}
Carto::ILayerPtr CTDAppView::GetComboLayer()
{
	int nSize = m_MapCtrl.GetMap()->GetLayers().GetSize();
	int nSel = GetCurLyrCombox()->GetCurSel();
	if (nSel >=0 && nSel<nSize)
	{
		return FindLayerbyPointer((Carto::ILayer*)GetCurLyrCombox()->GetItemData(nSel));
	}
	return NULL;
}
Carto::ILayerPtr CTDAppView::GetComboLayer_Vector()
{
	int nSize = m_MapCtrl.GetMap()->GetLayers().GetSize();
	int nSel = GetCurLyrCombox_Vector()->GetCurSel();
	if (nSel >=0 && nSel<nSize)
	{
		return FindLayerbyPointer((Carto::ILayer*)GetCurLyrCombox()->GetItemData(nSel));
	}
	return NULL;
}
void CTDAppView::OnCurrLayerCombo()
{

}
void CTDAppView::OnCurrLayerCombo_Vector()
{
	std::string curLayerName = GetCurLyrCombox_Vector()->GetItem(GetCurLyrCombox_Vector()->GetCurSel());
	Carto::CMapPtr pMap =m_MapCtrl.GetMap();
	if(pMap)
	{
		if(!pMap->GetEditor())
		{
			pMap->SetEditor(new Editor::CEditor(pMap.get()));

		}
		Editor::CEditor* pEditor = (Editor::CEditor*)pMap->GetEditor().get();
		pEditor->ChangeCurLayer(curLayerName);
	}
	
}
void CTDAppView::OnUpdateCurrlayerCombo_Vector(CCmdUI* pCmdUI)
{
	
	Carto::CMapPtr pMap =m_MapCtrl.GetMap();
	if(!pMap)
	{
		pCmdUI->Enable(FALSE);
	}
	if(!pMap->GetEditor())
	{
		pMap->SetEditor(new Editor::CEditor(pMap.get()));

	}
	pCmdUI->Enable(pMap->GetEditor()->IsEditing());
}
void CTDAppView::OnBrightRestore()
{
}
void CTDAppView::OnContrastRestore()
{
}
void CTDAppView::OnTransparentRestore()
{
}
void CTDAppView::OnBrightSlider()
{
	BrightContrast();
	CMainFrame* pMainFrm = (CMainFrame*)::AfxGetApp()->GetMainWnd();
	CBCGPRibbonSlider* pSlider = DYNAMIC_DOWNCAST (CBCGPRibbonSlider,(CBCGPRibbonComboBox*)pMainFrm->m_wndRibbonBar.FindByID (ID_BRIGHT_SLIDER));
	ASSERT_VALID (pSlider);
	int nPos = pSlider->GetPos();
	CString str;
	str.Format("%d", nPos);
	CBCGPRibbonEdit* pZoom = DYNAMIC_DOWNCAST (CBCGPRibbonEdit,(CBCGPRibbonComboBox*)pMainFrm->m_wndRibbonBar.FindByID (ID_BRIGHT_TEXT));
	ASSERT_VALID (pZoom);
	pZoom->SetEditText(str);
}
void CTDAppView::OnTransparentSlider()
{
	CMainFrame* pMainFrm = (CMainFrame*)::AfxGetApp()->GetMainWnd();
	CBCGPRibbonSlider* pSlider = DYNAMIC_DOWNCAST (CBCGPRibbonSlider,(CBCGPRibbonComboBox*)pMainFrm->m_wndRibbonBar.FindByID (ID_TRANSPARENT_SLIDER));
	ASSERT_VALID (pSlider);
	int nPos = pSlider->GetPos();
	Carto::CRasterLayerPtr layer = Carto::CRasterLayerPtr(GetComboLayer());
	layer->SetTransparent(nPos);
	CString str;
	str.Format("%d", nPos);
	CBCGPRibbonEdit* pZoom = DYNAMIC_DOWNCAST (CBCGPRibbonEdit,(CBCGPRibbonComboBox*)pMainFrm->m_wndRibbonBar.FindByID (ID_TRANSPARENT_TEXT));
	ASSERT_VALID (pZoom);
	pZoom->SetEditText(str);
	m_MapCtrl.UpdateControl(drawAll);
	UpdateData(FALSE);
}
void CTDAppView::OnContrastSlider()
{
	BrightContrast();
	CMainFrame* pMainFrm = (CMainFrame*)::AfxGetApp()->GetMainWnd();
	CBCGPRibbonSlider* pSlider = DYNAMIC_DOWNCAST (CBCGPRibbonSlider,(CBCGPRibbonComboBox*)pMainFrm->m_wndRibbonBar.FindByID (ID_CONTRAST_SLIDER));
	ASSERT_VALID (pSlider);
	int nPos = pSlider->GetPos();
	CString str;
	str.Format("%d", nPos);
	CBCGPRibbonEdit* pZoom = DYNAMIC_DOWNCAST (CBCGPRibbonEdit,(CBCGPRibbonComboBox*)pMainFrm->m_wndRibbonBar.FindByID (ID_CONTRAST_TEXT));
	ASSERT_VALID (pZoom);
	pZoom->SetEditText(str);
}
void CTDAppView::OnUpdateBrightRestore(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(IsLayerComboNull());
}
void CTDAppView::OnUpdateContrastRestore(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(IsLayerComboNull());
}
void CTDAppView::OnUpdateTransparentRestore(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(IsLayerComboNull());
}
void CTDAppView::OnUpdateBrightSlider(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(IsLayerComboNull());
}
void CTDAppView::OnUpdateContrastSlider(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(IsLayerComboNull());
}
void CTDAppView::OnUpdateTransparentSlider(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(IsLayerComboNull());
}
void CTDAppView::OnSwipe()
{
	Framework::ICommand* pCmd = NULL;
	m_MapCtrl.SetCurTool("SwipeEnhance");
	m_MapCtrl.GetMap()->SetOperLayer(GetComboLayer());
	pCmd= Framework::ICommand::FindCommand("SwipeEnhance");
	if(pCmd)
	{
		pCmd->Click();
	}
}
void CTDAppView::OnUpdateSwipe(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(IsLayerComboNull());
}
void CTDAppView::OnFlick()
{
	Framework::ICommand* pCmd = NULL;
	m_MapCtrl.SetCurTool("Flick");
	m_MapCtrl.GetMap()->SetOperLayer(GetComboLayer());
	pCmd= Framework::ICommand::FindCommand("Flick");
	if(pCmd)
	{
		pCmd->Click();
	}
}
void CTDAppView::OnUpdateFlick(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(IsLayerComboNull());
}
void CTDAppView::BrightContrast(int nBright,int nContrast)
{
	if (nBright == -1)
	{
		CMainFrame* pMainFrm = (CMainFrame*)::AfxGetApp()->GetMainWnd();
		CBCGPRibbonSlider* pSlider = DYNAMIC_DOWNCAST (CBCGPRibbonSlider,(CBCGPRibbonComboBox*)pMainFrm->m_wndRibbonBar.FindByID (ID_BRIGHT_SLIDER));
		ASSERT_VALID (pSlider);
		nBright = pSlider->GetPos();
	}
	if (nContrast == -1)
	{
		CMainFrame* pMainFrm = (CMainFrame*)::AfxGetApp()->GetMainWnd();
		CBCGPRibbonSlider* pSlider = DYNAMIC_DOWNCAST (CBCGPRibbonSlider,(CBCGPRibbonComboBox*)pMainFrm->m_wndRibbonBar.FindByID (ID_CONTRAST_SLIDER));
		ASSERT_VALID (pSlider);
		nContrast = pSlider->GetPos();
	}

	Carto::CRasterLayerPtr layer = Carto::CRasterLayerPtr(GetComboLayer());
	Carto::IRasterRenderPtr pRender = layer->GetRender();
	if(!pRender)
		return;
	Carto::CRasterRGBRender* pRGBRender =  dynamic_cast<Carto::CRasterRGBRender*>(pRender.get());
	long RChannel=pRGBRender->GetRedBandIndex();
	long GChannel=pRGBRender->GetGreenBandIndex();
	long BChannel=pRGBRender->GetBlueBandIndex();
	BYTE *srcRLUT = new BYTE[256];
	BYTE *srcGLUT = new BYTE[256];
	BYTE *srcBLUT = new BYTE[256];
	//这里计算LUT是有问题的，应该获取当前的LUT，暂时先这样
	for (int i=0; i<256; ++i)
	{
		srcRLUT[i] = i;
		srcGLUT[i] = i;
		srcBLUT[i] = i;
	}
	if (pRGBRender->GetRGBMode())
	{
		pRGBRender->SetBrightAndContrast(srcRLUT,srcGLUT,srcBLUT,nBright,nContrast);
	}
	else
	{
		pRGBRender->SetBrightAndContrast(srcRLUT,nBright,nContrast);
	}
	if(srcRLUT != NULL)
	{
		delete []srcRLUT;
		srcRLUT = NULL;

	}
	if(srcGLUT != NULL)
	{
		delete []srcGLUT;
		srcGLUT = NULL;

	}
	if(srcBLUT != NULL)
	{
		delete []srcBLUT;
		srcBLUT = NULL;
	}
	m_MapCtrl.UpdateControl(drawAll);
	UpdateData(FALSE);
}
bool CTDAppView::IsLayerComboNull()
{
	int nSize = m_MapCtrl.GetMap()->GetLayers().GetSize();
	int nSel = GetCurLyrCombox()->GetCurSel();
	if (nSel>=0 && nSel<nSize)
	{
	    return true;	
	}
	return false;
}

bool  CTDAppView::IsLayerComboCurFirstVisual()
{
	int nSize = m_MapCtrl.GetMap()->GetLayers().GetSize();
	Carto::ILayerPtr pCurLyr = GetComboLayer();
	if (NULL == pCurLyr)
	{
		return false;
	}
	BOOL bVisual = FALSE;
	bVisual = pCurLyr->GetVisible();
	if (!bVisual)
	{
		return false;
	}
	Carto::ILayerPtr pLyr = NULL;
	for (int i=nSize - 1; i> -1; i--)
	{
		pLyr = m_MapCtrl.GetMap()->GetLayers().GetAt(i);
		bVisual = pLyr->GetVisible();
		if (bVisual && pLyr != pCurLyr)
		{
			return false;
		}
		else if (pLyr == pCurLyr)
		{
			break;
		}
	}
	return true;
}

//通过指针查找图层的智能指针
Carto::ILayerPtr CTDAppView::FindLayerbyPointer(Carto::ILayer* pLayer)
{
	Carto::CLayerArray &layers =m_MapCtrl.GetMap()->GetLayers();
	Carto::ILayerPtr pl;
	for(int i=0;i<layers.GetSize();i++)
	{
        pl =layers.GetAt(i);
		if(pl.get()==pLayer)
		{
			return pl;
		}
	}
	return NULL;
}
void CTDAppView::RefreshLayerCombo()
{
	int nSize = m_MapCtrl.GetMap()->GetLayers().GetSize();
	GetCurLyrCombox()->RemoveAllItems();
	GetCurLyrCombox_Vector()->RemoveAllItems();
	//GetMagicLayer()->RemoveAllItems();
	for (int i=0; i<nSize; ++i)
	{
		Carto::ILayerPtr pLayer = m_MapCtrl.GetMap()->GetLayers().GetAt(i);
		std::string strName = pLayer->GetName();
		//判断图层类型
		if(pLayer->GetLayerType()==Carto::RasterLayer)
		{
           GetCurLyrCombox()->AddItem(strName.c_str(),(DWORD_PTR)pLayer.get());
		   //GetMagicLayer()->AddItem(strName.c_str(),(DWORD_PTR)pLayer.get());
		   
		}
		else if(pLayer->GetLayerType()==Carto::FeatureLayer)
		{
           GetCurLyrCombox_Vector()->AddItem(strName.c_str(),(DWORD_PTR)pLayer.get());
		   
		}
		
		
	}
	if(GetCurLyrCombox()->GetCount() > 0)
		GetCurLyrCombox()->SelectItem(0);
	if(GetCurLyrCombox_Vector()->GetCount() > 0)
		GetCurLyrCombox_Vector()->SelectItem(0);
	//if(GetMagicLayer()->GetCount() > 0)
	//{
	//	GetMagicLayer()->SelectItem(0);
	//}

}

void CTDAppView::OnUpdateSelectFeatureByPoint(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_MapCtrl.GetCurToolName() == "SelectbyPoint");
}

void CTDAppView::OnIncrementalImport()
{
	Carto::CMapPtr m_pGeoMap =m_MapCtrl.GetMap();

	if(!m_pGeoMap->GetEditor())
	{
		m_pGeoMap->SetEditor(new Editor::CEditor(m_pGeoMap.get()));

	}

	CDlgIncrementalImport Dlg;
	if(Dlg.DoModal()==IDOK)
	{
		std::string szIncrementalPath = Dlg.m_IncrementalPath;

		Carto::CLayerArray &layers =m_pGeoMap->GetLayers();
		int num =layers.GetSize();
		Carto::ILayerPtr pLayer;
		Geodatabase::IFeatureClass *pFeatureClass =NULL;
		Geodatabase::IWorkspace *pWorkspace =NULL;


		bool bImport = false;
		//结束编辑
		for(int i=0;i<num;i++)
		{
			pLayer =layers.GetAt(i);
			if(pLayer->GetLayerType()!=Carto::FeatureLayer)
			{
				continue;
			}

			pFeatureClass =dynamic_cast<Geodatabase::IFeatureClass*>(pLayer->GetDataObject().get());
			if(!pFeatureClass)
			{
				continue;
			}

			pWorkspace =pFeatureClass->GetWorkspace();
			if(bImport)
			{
				m_MapCtrl.UpdateControl(drawAll);
				return;
			}

			CShapefileWorkspace* pShapeWS = dynamic_cast<CShapefileWorkspace* >(pWorkspace);
			//导出增量信息
			if(pShapeWS)
			{
				pShapeWS->IncrementalImport(szIncrementalPath.c_str());
				bImport =true;
			}

		}
		m_MapCtrl.UpdateControl(drawAll);
	}
}
void CTDAppView::OnUpdateIncrementalImport(CCmdUI* pCmdUI)
{
	Carto::CMapPtr pMap =m_MapCtrl.GetMap();
	if(!pMap)
	{
		pCmdUI->Enable(FALSE);
	}
	if(!pMap->GetEditor())
	{
		pMap->SetEditor(new Editor::CEditor(pMap.get()));

	}
	pCmdUI->Enable(pMap->GetEditor()->IsEditing());
}


//map与layout之间切换
LRESULT CTDAppView::OnChangeActiveTab(WPARAM wp,LPARAM lp)
{
	int iTabIndex=(int)wp;//激活哪个tab的索引
	if(iTabIndex== 1)
	{
		//在此初始化layout
		if(!m_LayoutCtrl.Initialized())
		{
			m_LayoutCtrl.Initialize();
			OnDrawMapFrameElement();
			//load temp
			CString strTempFile =GetAppPathName()+"\\china.TMP";
			//m_LayoutCtrl.LoadTemplate(m_MapCtrl.GetMap(),strTempFile.AllocSysString());
		}
	}
	return 0;
}
void CTDAppView::OnSelectFrameElement()
{
	Framework::ITool* pTool = NULL;
	m_LayoutCtrl.SetCurTool("SelectFrameElementsTool");

	pTool=Framework::ITool::FindTool("SelectFrameElementsTool");
	if(pTool)
	{
		pTool->Initialize(dynamic_cast<Framework::IUIObject*>(&m_LayoutCtrl));
	}
}
void CTDAppView::OnUpdateSelectFrameElement(CCmdUI* pCmdUI)
{

	pCmdUI->SetCheck(m_LayoutCtrl.GetCurToolName() == "SelectFrameElementsTool");
	//pCmdUI->Enable(m_bLayout);
}


void CTDAppView::OnDrawMapFrameElement()
{

	Framework::ICommand* pCommand = NULL;
	m_LayoutCtrl.SetCurTool("DrawMapFrameElementCmd");

	pCommand=Framework::ICommand::FindCommand("DrawMapFrameElementCmd");
	if(pCommand)
	{
		pCommand->Initialize(dynamic_cast<Framework::IUIObject*>(&m_LayoutCtrl));
		pCommand->Click();
	}
	OnSelectFrameElement();
}
void CTDAppView::OnUpdateDrawMapFrameElement(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_LayoutCtrl.GetCurToolName() == "DrawMapFrameElementCmd");
	//pCmdUI->Enable(m_bLayout);
}
//编辑工具

afx_msg void CTDAppView::OnEditorStart()
{
	Carto::CMapPtr pMap =m_MapCtrl.GetMap();

	if(pMap)
	{
		if(!pMap->GetEditor())
		{
			pMap->SetEditor(new Editor::CEditor(pMap.get()));

		}
		pMap->GetEditor()->StartEdit();

		CShapefileWorkspace* pShapeWS = NULL;
		Carto::CLayerArray &layers =pMap->GetLayers();
		int num =layers.GetSize();
		Carto::ILayerPtr pLayer;
		Geodatabase::IFeatureClass *pFeatureClass =NULL;
		Geodatabase::IWorkspace *pWorkspace =NULL;

		bool bImport = false;
		//结束编辑
		for(int i=0;i<num;i++)
		{
			pLayer =layers.GetAt(i);
			if(pLayer->GetLayerType()!=Carto::FeatureLayer)
			{
				continue;
			}

			pFeatureClass =dynamic_cast<Geodatabase::IFeatureClass*>(pLayer->GetDataObject().get());
			if(!pFeatureClass)
			{
				continue;
			}

			pWorkspace =pFeatureClass->GetWorkspace();
			if(bImport)
			{
				return;
			}

			pShapeWS = dynamic_cast<CShapefileWorkspace* >(pWorkspace);

		}

		if(pShapeWS==NULL)
			return;

		int flagSave = MessageBox("是否导出数据编辑增量信息？\n若导出，编辑将被保存到增量文件","提示",MB_YESNO);
		if (flagSave == 6)
		{
			//导出增量信息
			CDlgIncrementalExport Dlg;
			if(Dlg.DoModal()==IDOK)
			{
				std::string szIncrementalPath = Dlg.m_IncrementalPath;
				pShapeWS->m_IncrementalPath = szIncrementalPath;
				pShapeWS->m_bEditIncremental = true;
				bImport =true;
			}

		}
		else
		{
			pShapeWS->m_bEditIncremental = false;
			bImport =false;
		}
		m_MapCtrl.UpdateControl(drawAll);
	}
}
afx_msg void CTDAppView::OnUpdateEditorStart(CCmdUI *pCmdUI)
{
	Carto::CMapPtr pMap =m_MapCtrl.GetMap();
	if(!pMap )
	{
		pCmdUI->Enable(FALSE);
	}

	if(!pMap->GetEditor())
	{
		pMap->SetEditor(new Editor::CEditor(pMap.get()));

	}
	if(GetCurLyrCombox_Vector()->GetCount()<1)
		pCmdUI->Enable(FALSE);
	else
		pCmdUI->Enable(!pMap->GetEditor()->IsEditing());
}
afx_msg void CTDAppView::OnEditorSketch()
{
	Framework::ITool* pTool = NULL;
	m_MapCtrl.SetCurTool("SketchTool");
	pTool=Framework::ITool::FindTool("SketchTool");
	if(pTool)
	{
		pTool->Initialize(dynamic_cast<Framework::IUIObject*>(&m_MapCtrl));
	}
}
afx_msg void CTDAppView::OnUpdateEditorSketch(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_LayoutCtrl.GetCurToolName() == "SketchTool");
	Carto::CMapPtr pMap =m_MapCtrl.GetMap();
	if(!pMap)
	{
		pCmdUI->Enable(FALSE);
	}
	if(!pMap->GetEditor())
	{
		pMap->SetEditor(new Editor::CEditor(pMap.get()));

	}
	pCmdUI->Enable(pMap->GetEditor()->IsEditing());
}
afx_msg void CTDAppView::OnEditerEdit()
{
	Framework::ITool* pTool = NULL;
	m_MapCtrl.SetCurTool("EditFeatureTool");
	pTool=Framework::ITool::FindTool("EditFeatureTool");
	if(pTool)
	{
		pTool->Initialize(dynamic_cast<Framework::IUIObject*>(&m_MapCtrl));
	}
}
afx_msg void CTDAppView::OnUpdateEditerEdit(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_LayoutCtrl.GetCurToolName() == "EditFeatureTool");
	Carto::CMapPtr pMap =m_MapCtrl.GetMap();
	if(!pMap)
	{
		pCmdUI->Enable(FALSE);
	}
	if(!pMap->GetEditor())
	{
		pMap->SetEditor(new Editor::CEditor(pMap.get()));

	}
	pCmdUI->Enable(pMap->GetEditor()->IsEditing());
}
afx_msg void CTDAppView::OnEditerRedo()
{
	Carto::CMapPtr pMap =m_MapCtrl.GetMap();

	if(pMap)
	{
		if(!pMap->GetEditor())
		{
			pMap->SetEditor(new Editor::CEditor(pMap.get()));

		}
		if(pMap->GetEditor()->CanRedo())
			pMap->GetEditor()->Redo();
	}
}
afx_msg void CTDAppView::OnUpdateEditerRedo(CCmdUI *pCmdUI)
{
	Carto::CMapPtr pMap =m_MapCtrl.GetMap();
	if(!pMap)
	{
		pCmdUI->Enable(FALSE);
	}
	if(!pMap->GetEditor())
	{
		pMap->SetEditor(new Editor::CEditor(pMap.get()));

	}
	pCmdUI->Enable(pMap->GetEditor()->CanRedo());
}
afx_msg void CTDAppView::OnEditerUndo()
{
	Carto::CMapPtr pMap =m_MapCtrl.GetMap();

	if(pMap)
	{
		if(!pMap->GetEditor())
		{
			pMap->SetEditor(new Editor::CEditor(pMap.get()));

		}
		if(pMap->GetEditor()->CanUndo())
			pMap->GetEditor()->Undo();
	}
}
afx_msg void CTDAppView::OnUpdateEditerUndo(CCmdUI *pCmdUI)
{
	Carto::CMapPtr pMap =m_MapCtrl.GetMap();
	if(!pMap)
	{
		pCmdUI->Enable(FALSE);
	}
	if(!pMap->GetEditor())
	{
		pMap->SetEditor(new Editor::CEditor(pMap.get()));

	}
	pCmdUI->Enable(pMap->GetEditor()->CanUndo());
}
afx_msg void CTDAppView::OnEditerEnd()
{
	Carto::CMapPtr pMap =m_MapCtrl.GetMap();

	if(pMap)
	{
		if(!pMap->GetEditor())
		{
			pMap->SetEditor(new Editor::CEditor(pMap.get()));

		}
		int flagSave = MessageBox("是否保存编辑！","提示",MB_YESNOCANCEL);
		if (flagSave == 6)
		{
			pMap->GetEditor()->StopEdit(true);
		}
		else if(flagSave == 7)
		{
			pMap->GetEditor()->StopEdit(false);
		}
		
	}
}
afx_msg void CTDAppView::OnUpdateEditerEnd(CCmdUI *pCmdUI)
{
	Carto::CMapPtr pMap =m_MapCtrl.GetMap();
	if(!pMap)
	{
		pCmdUI->Enable(FALSE);
	}
	if(!pMap->GetEditor())
	{
		pMap->SetEditor(new Editor::CEditor(pMap.get()));

	}
	pCmdUI->Enable(pMap->GetEditor()->IsEditing());
}

afx_msg void CTDAppView::OnEditerSave()
{
	Carto::CMapPtr pMap =m_MapCtrl.GetMap();

	if(pMap)
	{
		if(!pMap->GetEditor())
		{
			pMap->SetEditor(new Editor::CEditor(pMap.get()));

		}
		pMap->GetEditor()->StopEdit(true);
	}
}
afx_msg void CTDAppView::OnUpdateEditerSave(CCmdUI *pCmdUI)
{
	Carto::CMapPtr pMap =m_MapCtrl.GetMap();
	if(!pMap)
	{
		pCmdUI->Enable(FALSE);
	}
	if(!pMap->GetEditor())
	{
		pMap->SetEditor(new Editor::CEditor(pMap.get()));

	}
	pCmdUI->Enable(pMap->GetEditor()->IsEditing());
}

afx_msg void CTDAppView::OnEditerDel()
{
	Carto::CMapPtr pMap =m_MapCtrl.GetMap();

	if(pMap)
	{
		if(!pMap->GetEditor())
		{
			pMap->SetEditor(new Editor::CEditor(pMap.get()));

		}
		Editor::CEditorPtr pEditor = pMap->GetEditor();
		pEditor->DeleteFeature();
	}
}
afx_msg void CTDAppView::OnUpdateEditerDel(CCmdUI *pCmdUI)
{
	Carto::CMapPtr pMap =m_MapCtrl.GetMap();
	if(!pMap)
	{
		pCmdUI->Enable(FALSE);
	}
	if(!pMap->GetEditor())
	{
		pMap->SetEditor(new Editor::CEditor(pMap.get()));

	}
	pCmdUI->Enable(pMap->GetEditor()->IsEditing());
}

afx_msg void CTDAppView::OnEditerUnion()
{
	Carto::CMapPtr pMap =m_MapCtrl.GetMap();

	if(pMap)
	{
		if(!pMap->GetEditor())
		{
			pMap->SetEditor(new Editor::CEditor(pMap.get()));

		}
		Framework::ICommand* pCommand = NULL;
		//m_MapCtrl.SetCurTool("PolygonUnionCmd");
		pCommand=Framework::ICommand::FindCommand("PolygonUnionCmd");
		if(pCommand)
		{
			pCommand->Initialize(dynamic_cast<Framework::IUIObject*>(&m_MapCtrl));
			pCommand->Click();
		}
	}
}
afx_msg void CTDAppView::OnUpdateEditerUnion(CCmdUI *pCmdUI)
{
	Carto::CMapPtr pMap =m_MapCtrl.GetMap();
	if(!pMap)
	{
		pCmdUI->Enable(FALSE);
	}
	if(!pMap->GetEditor())
	{
		pMap->SetEditor(new Editor::CEditor(pMap.get()));

	}
	pCmdUI->Enable(pMap->GetEditor()->IsEditing());
}
afx_msg void CTDAppView::OnEditerAttribute()
{
	Carto::CMapPtr pMap =m_MapCtrl.GetMap();

	if(pMap)
	{
		if(!pMap->GetEditor())
		{
			pMap->SetEditor(new Editor::CEditor(pMap.get()));

		}
		Framework::ICommand* pCommand = NULL;
		pCommand=Framework::ICommand::FindCommand("FeatureAtrEditCmd");
		if(pCommand)
		{
			pCommand->Initialize(dynamic_cast<Framework::IUIObject*>(&m_MapCtrl));
			pCommand->Click();
		}
	}
}
afx_msg void CTDAppView::OnUpdateEditerAttribute(CCmdUI *pCmdUI)
{
	Carto::CMapPtr pMap =m_MapCtrl.GetMap();
	if(!pMap)
	{
		pCmdUI->Enable(FALSE);
	}
	if(!pMap->GetEditor())
	{
		pMap->SetEditor(new Editor::CEditor(pMap.get()));

	}
	pCmdUI->Enable(pMap->GetEditor()->IsEditing());
}
afx_msg void CTDAppView::OnSelectFeature()
{
	Framework::ITool* pTool = NULL;
	m_MapCtrl.SetCurTool("SelectbyPoint");
	pTool=Framework::ITool::FindTool("SelectbyPoint");
	if(pTool)
	{
		pTool->Initialize(dynamic_cast<Framework::IUIObject*>(&m_MapCtrl));
	}
}
afx_msg void CTDAppView::OnUpdateSelectFeature(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_MapCtrl.GetCurToolName() == "SelectbyPoint");
}

afx_msg void CTDAppView::OnFeatureInfo()
{
	Framework::ITool* pTool = NULL;
	m_MapCtrl.SetCurTool("FeatureInfoTool");
	pTool=Framework::ITool::FindTool("FeatureInfoTool");
	if(pTool)
	{
		pTool->Initialize(dynamic_cast<Framework::IUIObject*>(&m_MapCtrl));
	}
}
void CTDAppView::OnMagicStick()
{
	Framework::ITool* pTool = NULL;
	m_MapCtrl.SetCurTool("MagicStickTool");
	pTool=Framework::ITool::FindTool("MagicStickTool");

	Carto::ILayer* pLayer =(Carto::ILayer*)GetMagicLayer()->GetItemData(GetMagicLayer()->GetCurSel());
	CMainFrame* pMainFrm = (CMainFrame*)::AfxGetApp()->GetMainWnd();
	CBCGPRibbonEdit* pEdit = (CBCGPRibbonEdit*)pMainFrm->m_wndRibbonBar.FindByID(ID_MAGICSTICK_TOL);
	CString strValue =pEdit->GetEditText();
	int ntol =atoi(strValue);
	if(ntol<=0 || ntol>100)
	{
		ntol =20;
	}
	Control::CMagicStickTool::SetParam(ntol,pLayer);

	//设置目标图层和阈值
	if(pTool)
	{
		pTool->Initialize(dynamic_cast<Framework::IUIObject*>(&m_MapCtrl));
	}
}

void CTDAppView::OnUpdateMagicStick(CCmdUI* pCmdUI)
{
	std::string strtool =m_MapCtrl.GetCurToolName();
	if(strtool=="MagicStickTool")
	{
		pCmdUI->SetCheck(TRUE);
	}
	else
	{
		pCmdUI->SetCheck(FALSE);
	}
}
void CTDAppView::LayerDelEvent(Carto::ILayerPtr pLayer)
{
	//更新图层下拉框
	RefreshLayerCombo();
}

void CTDAppView::OnMagicStickLayer()
{
	Framework::ITool* pTool = NULL;

	pTool=Framework::ITool::FindTool("MagicStickTool");

	Carto::ILayer* pLayer =(Carto::ILayer*)GetMagicLayer()->GetItemData(GetMagicLayer()->GetCurSel());
	CMainFrame* pMainFrm = (CMainFrame*)::AfxGetApp()->GetMainWnd();
	CBCGPRibbonEdit* pEdit = (CBCGPRibbonEdit*)pMainFrm->m_wndRibbonBar.FindByID(ID_MAGICSTICK_TOL);
	CString strValue =pEdit->GetEditText();
	int ntol =atoi(strValue);
	if(ntol<=0 || ntol>100)
	{
		ntol =20;
	}
	//设置目标图层和阈值
	Control::CMagicStickTool::SetParam(ntol,pLayer);

	
	
}

void CTDAppView::OnMagicTol()
{
	Framework::ITool* pTool = NULL;

	pTool=Framework::ITool::FindTool("MagicStickTool");

	Carto::ILayer* pLayer =(Carto::ILayer*)GetMagicLayer()->GetItemData(GetMagicLayer()->GetCurSel());
	CMainFrame* pMainFrm = (CMainFrame*)::AfxGetApp()->GetMainWnd();
	CBCGPRibbonEdit* pEdit = (CBCGPRibbonEdit*)pMainFrm->m_wndRibbonBar.FindByID(ID_MAGICSTICK_TOL);
	CString strValue =pEdit->GetEditText();
	int ntol =atoi(strValue);
	if(ntol<=0 || ntol>100)
	{
		ntol =20;
	}
	//设置目标图层和阈值
	Control::CMagicStickTool::SetParam(ntol,pLayer);
}

CBCGPRibbonComboBox* CTDAppView::GetMagicLayer()
{
	CMainFrame* pMainFrm = (CMainFrame*)::AfxGetApp()->GetMainWnd();
	CBCGPRibbonComboBox* pCombox = (CBCGPRibbonComboBox*)pMainFrm->m_wndRibbonBar.FindByID(ID_MAGICSTICK_LAYER);
	return pCombox;
}

void CTDAppView::OnImgChangeDetect()
{
	Control::CImageProcessTool::ShowImgChangeDetectDlg();

}

void CTDAppView::OnImgTargetClip()
{
	Control::CImageProcessTool::ShowTargetClipDlg();
}

void CTDAppView::OnImgChangeRender()
{
	CMainFrame* pMainFrm = (CMainFrame*)::AfxGetApp()->GetMainWnd();
	Control::CImageProcessTool::ShowDistillWaterSheet(&m_MapCtrl, pMainFrm);
	//Framework::ITool* pTool = NULL;
	//m_MapCtrl.SetCurTool("DiTillTool");
	//pTool=Framework::ITool::FindTool("DiTillTool");
	////设置目标图层和阈值
	//if(pTool)
	//{
	//	pTool->Initialize(dynamic_cast<Framework::IUIObject*>(&m_MapCtrl));
	//}
}
void CTDAppView::OnWaterExtract()
{
	CMainFrame* pMainFrm = (CMainFrame*)::AfxGetApp()->GetMainWnd();
	Control::CImageProcessTool::ShowDistillWaterSheet(&m_MapCtrl, pMainFrm);
}

//删除上次魔术棒提取结果
void CTDAppView::OnDeleteLastMagic()
{
	Carto::CMapPtr pMap =m_MapCtrl.GetMap();

	if(!pMap)
	{
		return;
	}
	Carto::CGraphicLayerPtr pLayer =pMap->GetGraphicLayer();
	Element::IElementPtr pElement;
	int count =pLayer->GetElementCount();
	if(count<=0)
	{
		return;
	}
	long ldata;
	for(int i=count-1;i>=0;i--)
	{
		pElement =pLayer->GetElement(i);
		if(!pElement)
		{
			continue;
		}
        ldata =pElement->GetUserdata();
        if(ldata==1 ||ldata ==3 ||ldata==2)
		{
            pLayer->RemoveElement(pElement);
			//更新视图
			m_MapCtrl.UpdateControl(drawElement);
			break;
		}
	}
	
	
}

void CTDAppView::OnEdgeTrack()
{
	Framework::ITool* pTool = NULL;
	m_MapCtrl.SetCurTool("EdgeTrackTool");
	pTool=Framework::ITool::FindTool("EdgeTrackTool");
	if(pTool)
	{
		pTool->Initialize(dynamic_cast<Framework::IUIObject*>(&m_MapCtrl));
	}
}

void CTDAppView::OnChangeSetSymbol()
{
	Control::CImageProcessTool::ShowChangeSymbolDlg();
}

void CTDAppView::OnSendBlueToothFile()
{
    CDlgBlueTooth dlg;
	dlg.DoModal();
}

CString GetExePath()
{
	char szFullPath[_MAX_PATH];
	char szDriver[_MAX_DRIVE];
	char szDir[_MAX_DIR];
	char szExePath[_MAX_DIR];

	GetModuleFileName(AfxGetApp()->m_hInstance, szFullPath, MAX_PATH);
	_splitpath(szFullPath, szDriver, szDir, NULL, NULL);
	_makepath(szExePath, szDriver, szDir, NULL, NULL);

	CString  exepath= szExePath;
	return exepath;
}

void CTDAppView::OnOpenHelp()
{
	//获得要启动的程序所在路径
	CString strCurrentPath = GetExePath();
	strCurrentPath +="help\\";
	TCHAR szOldPath[MAX_PATH] = {0};
	::GetCurrentDirectory(MAX_PATH, szOldPath);
	//kdk,设置当前文件夹路径，可以执行chm文件
	bool bsuc =::SetCurrentDirectory(strCurrentPath);

	CString strExeName ="help.doc";
	UINT flag =(UINT)ShellExecute(NULL,"open",strExeName,NULL,NULL,SW_NORMAL);
	if (flag <= 31)
	{
		switch (flag)
		{
	
		case ERROR_BAD_FORMAT:
			MessageBox("可执行文件已经损坏","提示");
			break;
		case ERROR_FILE_NOT_FOUND:
			MessageBox("没有找到可执行的文件","提示");
			break;
		case ERROR_PATH_NOT_FOUND:
			MessageBox("指定的执行文件路径没有找到","提示");
			break;
		default:
			break;
		}
	}
	::SetCurrentDirectory(szOldPath);
}

void CTDAppView::OnDelAll()
{
	Carto::CMapPtr pMap =m_MapCtrl.GetMap();

	if(!pMap)
	{
		return;
	}
	Carto::CGraphicLayerPtr pLayer =pMap->GetGraphicLayer();
	
	pLayer->UnselectAllElements();
	pLayer->RemoveAllElements();
	//更新视图
	m_MapCtrl.UpdateControl(drawAll);
	
}

void CTDAppView::OnLoadTarget()
{
	std::string path = SYSTEM::CSystemPath::GetSystemPath();
	std::string eqfile = path + "\\result\\eq.txt";
	
	FILE* fp = NULL;
	fp =fopen(eqfile.c_str(),"r");
	if(!fp)
		return;

	char cs[20];
	fscanf(fp, "%s", cs);
	fclose(fp);

	std::string eqID;
	eqID = cs;

	std::string targetName = 	"dmg" + eqID.substr(2,2) + "keyobjdampt.shp";
	std::string targetPath = path + "result\\" + eqID +"\\" + targetName;
	this->GetDocument()->LoadShpFile(targetPath.c_str());

	m_MapCtrl.UpdateControl(drawAll);
	RefreshLayerCombo();
}

void CTDAppView::OnLinkImg()
{
	std::string path = SYSTEM::CSystemPath::GetSystemPath();
	std::string exeName = path + "loaddbraster.exe";

	WinExecAndWait32(exeName.c_str(), NULL, NULL, INFINITE);

	//
	char file[1024];
	FILE* fp = NULL;

	std::string rasterDB = path + "seldbraster.txt";
	fp = fopen(rasterDB.c_str(), "r");
	if(fp)
	{
		while (fscanf(fp,"%s", file) != EOF)
		{
			std::string filepath = file;
			this->GetDocument()->LoadImageFile(filepath.c_str());
		}

		fclose(fp);

		m_MapCtrl.UpdateControl(drawAll);
		RefreshLayerCombo();
	}
}

void CTDAppView::OnLinkVector()
{
	std::string path = SYSTEM::CSystemPath::GetSystemPath();
	std::string exeName = path + "loaddbvector.exe";

	WinExecAndWait32(exeName.c_str(), NULL, NULL, INFINITE);

	//
	char file[1024];
	FILE* fp = NULL;

	std::string rasterDB = path + "seldbvector.txt";
	fp = fopen(rasterDB.c_str(), "r");
	if(fp)
	{
		while (fscanf(fp,"%s", file) != EOF)
		{
			std::string filepath = file;
			this->GetDocument()->LoadShpFile(filepath.c_str());
		}

		fclose(fp);

		m_MapCtrl.UpdateControl(drawAll);
		RefreshLayerCombo();
	}


}

void CTDAppView::OnChangeTarget()
{
	Control::CImageProcessTool::ShowTargetFeature();
}

void CTDAppView::OnLoadDb()
{

	std::string path = SYSTEM::CSystemPath::GetSystemPath();
	char file[1024];
	FILE* fp = NULL;

	//
	std::string rasterDB = path + "seldbraster.txt";
	fp = fopen(rasterDB.c_str(), "r");
	if(fp)
	{
		while (fscanf(fp,"%s", file) != EOF)
		{
			std::string filepath = file;
			this->GetDocument()->LoadImageFile(filepath.c_str());
		}

		fclose(fp);
	}

	
	//
	rasterDB = path + "seldbvector.txt";
	fp = fopen(rasterDB.c_str(), "r");
	if(fp)
	{
		while (fscanf(fp,"%s", file) != EOF)
		{
			std::string filepath = file;
			this->GetDocument()->LoadShpFile(filepath.c_str());
		}

		fclose(fp);
	}



	m_MapCtrl.UpdateControl(drawAll);
	RefreshLayerCombo();
}

void CTDAppView::OnCheckResult()
{
	std::string path = SYSTEM::CSystemPath::GetSystemPath();
	std::string result = path + "result\\message.txt";

	if(AfxMessageBox("保存结果？", MB_YESNO) == IDYES )
	{
		FILE* fp = NULL;
		fp = fopen(result.c_str(), "w");
		if(!fp) return;

		fprintf(fp, "YES");

		fclose(fp);
	}
	else
	{
		FILE* fp = NULL;
		fp = fopen(result.c_str(), "w");
		if(!fp) return;

		fprintf(fp, "NO");

		fclose(fp);
	}


}