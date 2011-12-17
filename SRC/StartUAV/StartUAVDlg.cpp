// StartUAVDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "StartUAV.h"
#include "StartUAVDlg.h"
#include "tinyxml.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CStartUAVDlg 对话框




CStartUAVDlg::CStartUAVDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStartUAVDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CStartUAVDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PICCONTAINER, m_picLoc);
}

BEGIN_MESSAGE_MAP(CStartUAVDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// CStartUAVDlg 消息处理程序

BOOL CStartUAVDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	m_ToolTip.Create(this);
	m_ToolTip.Activate(true);

    //图像大小
	int nImageWidth =800;
	int nImageHeight =600;

	//计算对话框大小
	int nDlgWidth =nImageWidth+10;
	int nDlgHeight =nImageHeight+110;
    
	CRect myRect;
	GetClientRect(&myRect);

	ClientToScreen(myRect);
	SetWindowPos(&CWnd::wndTop,myRect.left, myRect.top,
		nDlgWidth, nDlgHeight,SWP_NOMOVE);


    m_picLoc.MoveWindow(0,0,nImageWidth+5,nImageHeight+5);


	CRect rectPic;
	m_picLoc.GetWindowRect(&rectPic);
	ScreenToClient(&rectPic);

	m_BgContainer.Create ("STATIC" , _T(""), WS_CHILD|WS_VISIBLE|SS_NOTIFY , rectPic , this ,(UINT)-1);

	CString bmp_path = GetExePath() + "pic\\" + "界面.bmp";
	m_BgContainer.SetImage(bmp_path);

	InitXML();

	CreateButtons();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CStartUAVDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
//
HCURSOR CStartUAVDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



CString CStartUAVDlg::GetExePath()
{
	char szFullPath[_MAX_PATH];
	char szDriver[_MAX_DRIVE];
	char szDir[_MAX_DIR];
	char szExePath[_MAX_DIR];

	GetModuleFileName(AfxGetApp()->m_hInstance, szFullPath, MAX_PATH);
	_splitpath(szFullPath, szDriver, szDir, NULL, NULL);
	_makepath(szExePath, szDriver, szDir, NULL, NULL);

	return szExePath;
}


void CStartUAVDlg::InitXML()
{
	//初始化xml文件
	CString filepath = GetExePath();
	filepath += "Start.xml";

	TiXmlDocument xmldoc;
	bool b = xmldoc.LoadFile(filepath); 
	if (!b)
	{
		MessageBox("读取配置文件失败！");
		return;
	}

	stProduct pro;
	TiXmlElement* pElemRoot = xmldoc.FirstChildElement();	// 根节点
	TiXmlElement *pHead = pElemRoot->FirstChildElement();	
	m_strAppName = pHead->Attribute("AppName");				//取出AppName属性值,用于设置标题

	TiXmlElement * pChild = pHead->FirstChildElement();		
	TiXmlElement *pBody = pChild;

	CString temp = pBody->Attribute("valid");

	while (pBody != NULL)
	{
		if (temp == "true")
		{
			pro.strIdentity = pBody->Attribute("identity");
			pro.strExeName = pBody->Attribute("exename");
			pro.strTitle = pBody->Attribute("title");
			pro.strToolTip = pBody->Attribute("tooltip");
			pro.strIsWeb = pBody->Attribute("isweb");
			pro.strURL = pBody->Attribute("URL");
			m_ButtonInfo.push_back(pro);
		}
		pBody = pBody->NextSiblingElement();
	}
}

void CStartUAVDlg::CreateButtons()
{
	CRect ClientRect;
	GetClientRect(&ClientRect);
	CRect rect;
	long maxnum;
	long lButtonSizeX=70;
	long lButtonSizeY=60;
	long lDelta =7;
	long lext =0;
	//计算每行容纳的按钮数目
	maxnum =(ClientRect.Width()-lDelta)/(lButtonSizeX+lDelta);

	lext =(ClientRect.Width()-lDelta-(lButtonSizeX+lDelta)*m_ButtonInfo.size())/2;

	int PosX,PosY;
	CString exepath =GetExePath();
	stButIDandName m_BtnIDandName;
	for(size_t i=0;i<m_ButtonInfo.size();i++)
	{
		CTransButton *pButton =new CTransButton;

		rect.left =lext+lDelta*(i+1)+lButtonSizeX*i;
		rect.top =ClientRect.Height()-10-lButtonSizeY;
		rect.bottom =rect.top+lButtonSizeY;
		rect.right =rect.left+lButtonSizeX;
		m_ButtonInfo[i].rect =rect;
		pButton->Create(NULL, WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON|BS_BITMAP/*|BS_OWNERDRAW*/ , rect, this, ID_FB+i);

		CString bmptemp = m_ButtonInfo[i].strIdentity.c_str();
		CString bmp_path = exepath + "pic\\" + bmptemp + ".bmp";

		HBITMAP hBmp = (HBITMAP)::LoadImage(NULL,bmp_path,IMAGE_BITMAP,0,0,LR_CREATEDIBSECTION|LR_DEFAULTSIZE|LR_LOADFROMFILE);

		pButton->SetBitmap(hBmp);
		m_buttons.push_back(pButton);

		m_ToolTip.AddTool(pButton, m_ButtonInfo[i].strToolTip.c_str());

		m_BtnIDandName.m_ButtonID = ID_FB + i;
		m_BtnIDandName.strExeName = m_ButtonInfo[i].strExeName;
		m_BtnIDandName.strURL  = m_ButtonInfo[i].strURL;

		if (m_ButtonInfo[i].strIsWeb == "true")
			m_BtnIDandName.bIsWebURL = true;
		else
			m_BtnIDandName.bIsWebURL = false;

		m_ButtonIDandName.push_back(m_BtnIDandName);
	}
}
BOOL CStartUAVDlg::OnCommand(WPARAM wParam, LPARAM lParam)
{
	WORD nCode = HIWORD(wParam);
	WORD nID = LOWORD(wParam);
	UINT nButtonID;

	CString filepath = GetExePath();
	filepath += "Start.xml";

	for (int i=0; i<m_ButtonInfo.size(); i++)
	{
		nButtonID = m_ButtonIDandName[i].m_ButtonID;
		CString strExeName = m_ButtonIDandName[i].strExeName.c_str();
		CString strURL = m_ButtonIDandName[i].strURL.c_str();
		bool bisweburl = m_ButtonIDandName[i].bIsWebURL;


		if ((nID == nButtonID) && (nCode ==BN_CLICKED))
		{
			if (!bisweburl)	//是应用程序
			{
				//获得要启动的程序所在路径
				CString strCurrentPath = GetExePath();
				strCurrentPath +=strURL;
				TCHAR szOldPath[MAX_PATH] = {0};
				::GetCurrentDirectory(MAX_PATH, szOldPath);
				//kdk,设置当前文件夹路径，可以执行chm文件
				bool bsuc =::SetCurrentDirectory(strCurrentPath);

				UINT flag =(UINT)ShellExecute(NULL,"open",strExeName,NULL,NULL,SW_NORMAL);
				if (flag <= 31)
			 {
				 switch (flag)
				 {
				 case 0:
					 MessageBox("运行错误!","提示");
					 break;
				 case ERROR_BAD_FORMAT:
					 MessageBox("可执行文件已经损坏!","提示");
					 break;
				 case ERROR_FILE_NOT_FOUND:
					 MessageBox("没有找到可执行的文件!","提示");
					 break;
				 case ERROR_PATH_NOT_FOUND:
					 MessageBox("指定的执行文件路径没有找到!","提示");
					 break;
				 default:
					 break;
				 }
			 }
				::SetCurrentDirectory(szOldPath);
			}
			else
			{
				ShellExecute(NULL,"open",strURL,NULL,NULL,SW_MAXIMIZE);
			}
		}
	}

	return CDialog::OnCommand(wParam, lParam);
}

BOOL CStartUAVDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message >= WM_MOUSEFIRST && pMsg->message <= WM_MOUSELAST)
	{
		MSG msg;
		::CopyMemory(&msg, pMsg, sizeof(MSG));
		HWND hWndParent = ::GetParent(msg.hwnd);
		while (hWndParent && hWndParent != m_hWnd)
		{
			msg.hwnd = hWndParent;
			hWndParent = ::GetParent(hWndParent);
		}
		if (msg.hwnd)
		{
			m_ToolTip.RelayEvent(&msg);
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}