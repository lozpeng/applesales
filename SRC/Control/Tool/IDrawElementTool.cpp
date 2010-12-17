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

		//初始化光标
		if(m_hCursor==NULL)
		{
			//m_hCursor =::LoadCursor( theApp.m_hInstance , MAKEINTRESOURCE( IDC_PAN) );
		}


		//获取活动地图控件
		m_pMapCtrl = dynamic_cast<Framework::IMapCtrl*>(pTargetControl);
		if(!m_pMapCtrl)
			return;


		//获取活动地区
		m_pMap = m_pMapCtrl->GetMap();
		if(!m_pMap)
			return;

		Carto::CGraphicLayerPtr pGraphicLayer = m_pMap->GetGraphicLayer();
		if(!pGraphicLayer)
			return;

		//清空选择集
		pGraphicLayer->UnselectAllElements();

		//设置光标类型
		//m_pMapCtrl->SetCursorType(cursorCross);
	}

	void IDrawElementTool::LButtonDownEvent (UINT nFlags, CPoint point)
	{
		//记录移动起点
		cPtStart = cPtEnd = point;


		//锁定鼠标
		SetCapture(m_pMapCtrl->GetHWnd());
	}
	void IDrawElementTool::MouseMoveEvent (UINT nFlags, CPoint point)
	{
		if(!(nFlags&MK_LBUTTON)) 
			return;

		//记录移动点位置
		cPtEnd = point;
	}
	void IDrawElementTool::LButtonUpEvent (UINT nFlags, CPoint point)
	{

		//锁定鼠标
		ReleaseCapture();

	}

	void IDrawElementTool::LButtonDblClkEvent (UINT nFlags, CPoint point)
	{

		//更新绘制
		m_pMapCtrl->UpdateControl((DrawContent)(drawElement));

		ReleaseCapture();

		//工具设为选择
		Framework::ITool* pTool = NULL;
		m_pMapCtrl->SetCurTool("SelectElementTool");

		pTool=Framework::ITool::FindTool("SelectElementTool");
		if(pTool)
		{
			pTool->Initialize(dynamic_cast<Framework::IUIObject*>(m_pMapCtrl));
		}
	}

}