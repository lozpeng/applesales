#include "stdafx.h"
#include "LayoutPanTool.h"
#include "Control.h"

extern CControlApp theApp;

static CLayoutPanTool glayoutPanTool;

CLayoutPanTool::CLayoutPanTool() : ITool("LayoutPanTool")
{
	m_hCursor = NULL;
}

CLayoutPanTool::~CLayoutPanTool()
{
	if(m_hCursor)
	{
		DeleteObject( m_hCursor );
	}
}

void CLayoutPanTool::Initialize(Framework::IUIObject *pTargetControl)
{
	ITool::Initialize(pTargetControl);

	//��ʼ�����
	if(m_hCursor==NULL)
	{
		m_hCursor =::LoadCursor( theApp.m_hInstance , MAKEINTRESOURCE( IDC_PAN) );
	}


	//��ȡ���ͼ�ؼ�
	m_pLayoutCtrl = dynamic_cast<Framework::ILayoutCtrl*>(pTargetControl);
	if(!m_pLayoutCtrl)
		return;

	//���ù������
	m_pLayoutCtrl->SetCursor(m_hCursor);


}
void CLayoutPanTool::LButtonDownEvent (UINT nFlags, CPoint point)
{

	if(!m_pLayoutCtrl)
		return;


	if(!m_pLayoutCtrl->GetPageLayout())
		return;

	//��¼�ƶ����
	cPt0 = cPt1 = point;

	//
	SetCapture(m_pLayoutCtrl->GetHWnd());

}

void CLayoutPanTool::MouseMoveEvent (UINT nFlags, CPoint point)
{

	if(!(nFlags&MK_LBUTTON)) 
		return;

	if(!m_pLayoutCtrl)
		return;


	if(!m_pLayoutCtrl->GetPageLayout())
		return;

	//��¼�ƶ���λ��
	cPt2 = point;

	//�ƶ�����
	m_pLayoutCtrl->OffsetClient(cPt2.x-cPt1.x, cPt2.y-cPt1.y);

	cPt1 = cPt2;

}

void CLayoutPanTool::LButtonUpEvent (UINT nFlags, CPoint point)
{
	if(!m_pLayoutCtrl)
		return;


	if(!m_pLayoutCtrl->GetPageLayout())
		return;

	//��¼����λ��
	cPt2=point;

	double dScale = m_pLayoutCtrl->GetPageLayout()->GetDisplay()->GetDisplayTransformation().GetScale();
	double OffsetX = dScale * (cPt2.x-cPt0.x);
	double OffsetY = dScale * (cPt0.y-cPt2.y);
	m_pLayoutCtrl->GetPageLayout()->GetDisplay()->GetDisplayTransformation().MoveViewBound(OffsetX,OffsetY);

	//
	m_pLayoutCtrl->UpdateControl(drawAll);

	//
	ReleaseCapture();

}
