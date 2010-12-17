#include "stdafx.h"
#include "MapPanTool.h"
#include "Control.h"


extern CControlApp theApp;
namespace Control
{
	static CToolMapPan gPanTool;

	CToolMapPan::CToolMapPan() : Framework::ITool("MapPan")
	{
		m_pMapCtrl =NULL;

		m_hCursor =NULL;
	}

	CToolMapPan::~CToolMapPan()
	{
		if(m_hCursor)
		{
			DeleteObject( m_hCursor );
		}
	}

	void CToolMapPan::Initialize(Framework::IUIObject *pTargetControl)
	{
		ITool::Initialize(pTargetControl);

		//��ʼ�����
		if(m_hCursor==NULL)
		{
			m_hCursor =::LoadCursor( theApp.m_hInstance , MAKEINTRESOURCE( IDC_PAN) );
		}


		//��ȡ���ͼ�ؼ�
		m_pMapCtrl = dynamic_cast<Framework::IMapCtrl*>(pTargetControl);
		if(!m_pMapCtrl)
			return;

		//���ù������
		m_pMapCtrl->SetCursor(m_hCursor);


	}

	void CToolMapPan::LButtonDownEvent (UINT nFlags, CPoint point)
	{
		//��ȡ���ͼ�ؼ�
		if(!m_pMapCtrl)
			return;

		//��¼�ƶ����
		cPt0 = cPt1 = point;

		//
		SetCapture(m_pMapCtrl->GetHWnd());

	}

	void CToolMapPan::MouseMoveEvent (UINT nFlags, CPoint point)
	{

		if(!(nFlags&MK_LBUTTON)) 
			return;

		if(!m_pMapCtrl)
			return;

		//��¼�ƶ���λ��
		cPt2 = point;

		//�ƶ�����
		m_pMapCtrl->OffsetClient(cPt2.x-cPt1.x, cPt2.y-cPt1.y);

		cPt1 = cPt2;

	}

	void CToolMapPan::LButtonUpEvent (UINT nFlags, CPoint point)
	{
		//��ȡ���ͼ�ؼ�
		if(!m_pMapCtrl)
			return;

		//��ȡ�����
		Carto::CMapPtr pMap = m_pMapCtrl->GetMap();
		if(!pMap)
			return;

		//��¼����λ��
		cPt2=point;

		double dScale = pMap->GetDisplay()->GetDisplayTransformation().GetScale();
		double OffsetX = dScale * (cPt2.x-cPt0.x);
		double OffsetY = dScale * (cPt0.y-cPt2.y);
		pMap->GetDisplay()->GetDisplayTransformation().MoveViewBound(OffsetX,OffsetY);

		//
		m_pMapCtrl->UpdateControl(drawAll);

		//
		ReleaseCapture();

	}
}