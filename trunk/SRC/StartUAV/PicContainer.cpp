#include "StdAfx.h"
#include "PicContainer.h"
#include "Resource.h"

IMPLEMENT_DYNAMIC(CPicContainer, CWnd)

CPicContainer::CPicContainer(void)
{
	m_pBitmap =NULL;
}

CPicContainer::~CPicContainer(void)
{
	if(m_pBitmap)
	{
		delete m_pBitmap;
		m_pBitmap =NULL;
	}
}
BEGIN_MESSAGE_MAP(CPicContainer, CWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
END_MESSAGE_MAP()

void CPicContainer::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CWnd::OnPaint()

	CDC *pDC =GetDC();

	//绘制背景图片
	if(m_pBitmap)
	{
		CDC dcMemory;
		dcMemory.CreateCompatibleDC(pDC);

		BITMAP bmpInfo;
		m_pBitmap->GetBitmap(&bmpInfo);

		CBitmap* pOldBitmap = dcMemory.SelectObject(m_pBitmap);

		CRect rect;
		GetClientRect(&rect);
	
		pDC->SetStretchBltMode(COLORONCOLOR);
		BOOL bsuc =pDC->StretchBlt(0, 0, rect.Width(), rect.Height(), &dcMemory, 
			0, 0,bmpInfo.bmWidth,bmpInfo.bmHeight, SRCCOPY);

		dcMemory.SelectObject(pOldBitmap);

	}
	if(m_text!="")
	{
		//背景色设置成透明
		int oldMode =pDC->SetBkMode(TRANSPARENT);
		CRect rect;
		rect.left =50;
		rect.top =50;
		rect.bottom =rect.right =100;
		pDC->DrawText(m_text,&rect,DT_NOCLIP | DT_NOPREFIX | DT_LEFT | DT_TOP);
		pDC->SetBkMode(oldMode);
	}
	for(size_t i=0;i<m_buttons.size();i++)
	{
		m_buttons[i]->Invalidate();
	}
}

void CPicContainer::SetImage(CString path)
{
	m_ImagePath =path;
	//加载图片
    HBITMAP hbmp =LoadBMP(path);
	if(hbmp)
	{
		if(m_pBitmap)
		{
			delete m_pBitmap;
			m_pBitmap =NULL;
		}
		m_pBitmap =new CBitmap();
		m_pBitmap->Attach(hbmp);
	}
}

HBITMAP CPicContainer::LoadBMP(CString bmpPath)
{
	return (HBITMAP)::LoadImage(NULL,bmpPath,IMAGE_BITMAP,0,0,LR_CREATEDIBSECTION|LR_DEFAULTSIZE|LR_LOADFROMFILE);
}
int CPicContainer::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	//创建按钮
	CRect ClientRect;
	GetClientRect(&ClientRect);
	CRect rect;
	long lButtonSizeX=70;
	long lButtonSizeY=60;
	long lDelta =20;
	int PosX,PosY;
	for(size_t i=0;i<m_ButtonInfo.size();i++)
	{
		CButton *pButton =new CButton;

		rect.left =lDelta*(i+1)+lButtonSizeX*i;
		rect.top =ClientRect.Height()-lDelta-lButtonSizeY;
		rect.bottom =rect.top+lButtonSizeY;
		rect.right =rect.left+lButtonSizeX;
		m_ButtonInfo[i].rect =rect;
		pButton->Create(NULL, WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON/*|BS_OWNERDRAW*/ , rect, this, ID_FB+i);
		m_buttons.push_back(pButton);
	}

	return 0;
}
