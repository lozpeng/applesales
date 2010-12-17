#include "StdAfx.h"
#include "IDrawElementTool.h"
#include "MapControl.h"
#include "GraphicLayer.h"
#include "Control.h"

namespace Control
{

	IDrawElementTool::IDrawElementTool(const char* name): ITool(name)
	{
		m_pMapCtrl =NULL;

		m_hCursor =NULL;
	}

	IDrawElementTool::~IDrawElementTool(void)
	{
	}

	void IDrawElementTool::Initialize(Framework::IUIObject *pTargetControl)
	{

		ITool::Initialize(pTargetControl);

		//��ʼ�����
		if(m_hCursor==NULL)
		{
			//m_hCursor =::LoadCursor( theApp.m_hInstance , MAKEINTRESOURCE( IDC_PAN) );
		}


		//��ȡ���ͼ�ؼ�
		m_pMapCtrl = dynamic_cast<Framework::IMapCtrl*>(pTargetControl);
		if(!m_pMapCtrl)
			return;


		//��ȡ�����
		m_pMap = m_pMapCtrl->GetMap();
		if(!m_pMap)
			return;

		Carto::CGraphicLayerPtr pGraphicLayer = m_pMap->GetGraphicLayer();
		if(!pGraphicLayer)
			return;

		//���ѡ��
		pGraphicLayer->UnselectAllElements();

		//���ù������
		//m_pMapCtrl->SetCursorType(cursorCross);
	}

	void IDrawElementTool::LButtonDownEvent (UINT nFlags, CPoint point)
	{
		//��¼�ƶ����
		cPtStart = cPtEnd = point;


		//�������
		SetCapture(m_pMapCtrl->GetHWnd());
	}
	void IDrawElementTool::MouseMoveEvent (UINT nFlags, CPoint point)
	{
		if(!(nFlags&MK_LBUTTON)) 
			return;

		//��¼�ƶ���λ��
		cPtEnd = point;
	}
	void IDrawElementTool::LButtonUpEvent (UINT nFlags, CPoint point)
	{

		//�������
		ReleaseCapture();

	}

	void IDrawElementTool::LButtonDblClkEvent (UINT nFlags, CPoint point)
	{

		//���»���
		m_pMapCtrl->UpdateControl((DrawContent)(drawElement));

		ReleaseCapture();

		//������Ϊѡ��
		Framework::ITool* pTool = NULL;
		m_pMapCtrl->SetCurTool("SelectElementTool");

		pTool=Framework::ITool::FindTool("SelectElementTool");
		if(pTool)
		{
			pTool->Initialize(dynamic_cast<Framework::IUIObject*>(m_pMapCtrl));
		}
	}

}