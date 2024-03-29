// TDApp.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "TDApp.h"
#include "MainFrm.h"

#include "TDAppDoc.h"
#include "TDAppView.h"
#include "afxcmn.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTDAppApp

BEGIN_MESSAGE_MAP(CTDAppApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()


// CTDAppApp construction

CTDAppApp::CTDAppApp() :
	CBCGPWorkspace (TRUE /* m_bResourceSmartUpdate */)
{
	EnableHtmlHelp();

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CTDAppApp object

CTDAppApp theApp;


// CTDAppApp initialization

BOOL CTDAppApp::InitInstance()
{

	CWinApp::InitInstance();

	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		//AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	globalData.SetDPIAware ();


	SetRegistryKey(_T("BCGP AppWizard-Generated Applications"));
	LoadStdProfileSettings(4);  // Load standard INI file options (including MRU)

	SetRegistryBase (_T("Settings"));

	// Initialize all Managers for usage. They are automatically constructed
	// if not yet present
	InitContextMenuManager();
	InitKeyboardManager();

	// TODO: Remove this if you don't want extended tooltips:
	InitTooltipManager();

	CBCGPToolTipParams params;
	params.m_bVislManagerTheme = TRUE;

	theApp.GetTooltipManager ()->SetTooltipParams (
		BCGP_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS (CBCGPToolTipCtrl),
		&params);

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CTDAppDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CTDAppView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);


	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	//
	struct AFX_OLDNONCLIENTMETRICS
	{
		UINT    cbSize;
		int     iBorderWidth;
		int     iScrollWidth;
		int     iScrollHeight;
		int     iCaptionWidth;
		int     iCaptionHeight;
		LOGFONT lfCaptionFont;
		int     iSmCaptionWidth;
		int     iSmCaptionHeight;
		LOGFONT lfSmCaptionFont;
		int     iMenuWidth;
		int     iMenuHeight;
		LOGFONT lfMenuFont;
		LOGFONT lfStatusFont;
		LOGFONT lfMessageFont;
	};

	const UINT cbProperSize = sizeof(AFX_OLDNONCLIENTMETRICS);/*(_AfxGetComCtlVersion() < MAKELONG(1, 6))
															  ? sizeof(AFX_OLDNONCLIENTMETRICS) : sizeof(NONCLIENTMETRICS);*/

	NONCLIENTMETRICS info;
	info.cbSize = cbProperSize;

	::SystemParametersInfo(SPI_GETNONCLIENTMETRICS, cbProperSize, &info, 0);

	LONG prelfHeight = info.lfMenuFont.lfHeight;
	info.lfMenuFont.lfHeight = -14;

	::SystemParametersInfo(SPI_SETNONCLIENTMETRICS, cbProperSize, &info, 0);
	globalData.UpdateFonts();

	//设置文档连接地图管理控件
	CMainFrame *pMainFrame = (CMainFrame *)AfxGetMainWnd();

	CTDAppDoc *pDoc =dynamic_cast<CTDAppDoc*>(pMainFrame->GetActiveDocument());
	pDoc->SetLinkMapTree(pMainFrame->GetTOC());
	pMainFrame->GetTOC()->RefreshFromDoc();

	m_pMainWnd->SetWindowText(" 重点目标震害信息提取");
	m_pMainWnd->ShowWindow(SW_SHOWMAXIMIZED);
	m_pMainWnd->UpdateWindow();

	// call DragAcceptFiles only if there's a suffix
	//  In an SDI app, this should occur after ProcessShellCommand
	return TRUE;
}

// CTDAppApp message handlers

int CTDAppApp::ExitInstance() 
{
	BCGCBProCleanUp();

	std::string path = SYSTEM::CSystemPath::GetSystemPath();
	std::string result = path + "result\\message.txt";

	if(AfxMessageBox("保存结果？", MB_YESNO) == IDYES )
	{
		FILE* fp = NULL;
		fp = fopen(result.c_str(), "w");
		if(!fp) return 0 ;

		fprintf(fp, "YES");

		fclose(fp);
	}
	else
	{
		FILE* fp = NULL;
		fp = fopen(result.c_str(), "w");
		if(!fp) return 0;

		fprintf(fp, "NO");

		fclose(fp);
	}


	return CWinApp::ExitInstance();
}

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };
	CBCGPURLLinkButton m_btnURL;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_TabCtrl;
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMPANY_URL, m_btnURL);
	DDX_Control(pDX, IDC_TAB1, m_TabCtrl);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CAboutDlg::OnTcnSelchangeTab1)
END_MESSAGE_MAP()

// App command to run the dialog
void CTDAppApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}


// CTDAppApp message handlers


void CTDAppApp::PreLoadState ()
{

	GetContextMenuManager()->AddMenu (_T("My menu"), IDR_CONTEXT_MENU);

	// TODO: add another context menus here
}


void CAboutDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}
