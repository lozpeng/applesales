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
//	// TODO: �ڴ˴������Ϣ����������
//	// ��Ϊ��ͼ��Ϣ���� 
//    CButton::OnPaint();
//}

void CTransButton::DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/)
{

	
}

BOOL CTransButton::OnEraseBkgnd(CDC* pDC)
{
	

	return TRUE;
}
