#include "StdAfx.h"
#include "TransButton.h"

CTransButton::CTransButton(void)
{
}

CTransButton::~CTransButton(void)
{
}
BEGIN_MESSAGE_MAP(CTransButton, CButton)
	
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

//void CTransButton::OnPaint()
//{
//	CPaintDC dc(this); // device context for painting
//	// TODO: 在此处添加消息处理程序代码
//	// 不为绘图消息调用 
//    CButton::OnPaint();
//}

void CTransButton::DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/)
{

	
}

BOOL CTransButton::OnEraseBkgnd(CDC* pDC)
{
	

	return TRUE;
}
