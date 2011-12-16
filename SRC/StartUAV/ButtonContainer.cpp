#include "StdAfx.h"
#include "ButtonContainer.h"
#include "Resource.h"

IMPLEMENT_DYNAMIC(CButtonContainer, CWnd)

CButtonContainer::CButtonContainer(void)
{
}

CButtonContainer::~CButtonContainer(void)
{
}
BEGIN_MESSAGE_MAP(CButtonContainer, CWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


static CString GetExePath()
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

int CButtonContainer::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect ClientRect;
	GetClientRect(&ClientRect);
	CRect rect;
	long lButtonSizeX=70;
	long lButtonSizeY=60;
	long lDelta =7;
	int PosX,PosY;
	CString exepath =GetExePath();
	for(size_t i=0;i<m_ButtonInfo.size();i++)
	{
        CTransButton *pButton =new CTransButton;
		
		rect.left =lDelta*(i+1)+lButtonSizeX*i;
		rect.top =ClientRect.Height()-10-lButtonSizeY;
		rect.bottom =rect.top+lButtonSizeY;
		rect.right =rect.left+lButtonSizeX;
		m_ButtonInfo[i].rect =rect;
		pButton->Create(NULL, WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON|BS_BITMAP/*|BS_OWNERDRAW*/ , rect, this, ID_FB+i);

		CString bmptemp = m_ButtonInfo[i].strIdentity.c_str();
		//启动图标的路径
		CString bmp_path = exepath + "pic\\" + bmptemp + ".bmp";

		HBITMAP hBmp = (HBITMAP)::LoadImage(NULL,bmp_path,IMAGE_BITMAP,0,0,LR_CREATEDIBSECTION|LR_DEFAULTSIZE|LR_LOADFROMFILE);

		pButton->SetBitmap(hBmp);
		m_buttons.push_back(pButton);
	}
    
	return 0;
}

#define  ICON_BGCOLOR RGB(211,206,202)

void CButtonContainer::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CWnd::OnPaint()

	//绘制背景色
	CRect rect;
	this->GetClientRect(rect);

	CBrush newBrush(ICON_BGCOLOR);
	CBrush *oldBrush =dc.SelectObject(&newBrush);

	dc.Rectangle(rect);

	dc.SelectObject(oldBrush);
}

void CButtonContainer::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
    

	CWnd::OnMouseMove(nFlags, point);
}

void CButtonContainer::SetButtonInfo(std::vector<stProduct> &ButtonInfo)
{
	m_ButtonInfo =ButtonInfo;
}
