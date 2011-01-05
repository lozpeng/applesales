#include "stdafx.h"
#include "EditElementVertixTool.h"
#include "IElement.h"
#include "Control.h"
extern CControlApp theApp;

namespace Control
{

	static CEditElementVertixTool gEditElementVertixTool;

	CEditElementVertixTool::CEditElementVertixTool() : ITool("EditElementVertixTool")
	{
		m_nMoveStatus = NO_MOVING;
		m_nCanMoveContent = CMC_CANMOVE_NONE;

		m_nBufferDis = 3;

		m_pCurElement.reset();
		
		cursorNormal = NULL;
		cursorSizeAll = NULL;
		cursorVertixMove = NULL;
		cursorOnVertix = NULL;
	}

	CEditElementVertixTool::~CEditElementVertixTool()
	{

	}

	void CEditElementVertixTool::Initialize(Framework::IUIObject *pTargetControl)
	{
		//获取活动地图控件
		m_pMapCtrl = dynamic_cast<Framework::IMapCtrl*>(pTargetControl);
		if(!m_pMapCtrl)
			return;

		//初始化光标
		if(cursorNormal == NULL)
			cursorNormal =::LoadCursor( theApp.m_hInstance , MAKEINTRESOURCE( IDC_Arrow));
		if(cursorSizeAll == NULL)
			cursorSizeAll =::LoadCursor( theApp.m_hInstance , MAKEINTRESOURCE( IDC_SIZE_ALL));
		if(cursorVertixMove == NULL)
			cursorVertixMove =::LoadCursor( theApp.m_hInstance , MAKEINTRESOURCE( IDC_VERTIX_MOVE));
		if(cursorOnVertix == NULL)
			cursorOnVertix =::LoadCursor( theApp.m_hInstance , MAKEINTRESOURCE( IDC_ON_VERTIX));


		m_pCurElement = m_pMapCtrl->GetMap()->GetGraphicLayer()->GetSelectedElement(0);

		if(m_pCurElement)
			m_pCurElement->SetEditMode(Element::EEM_EDIT_VERTIX);

		m_pMapCtrl->UpdateControl(drawEdit);

		ITool::Initialize(pTargetControl);
	}

	void CEditElementVertixTool::LButtonDownEvent (UINT nFlags, CPoint point)
	{
		if(!m_pCurElement)
			return;

		//记录移动起点
		UpdateStartPoint(point);
		UpdateEndPoint(point);


		//若鼠标在图元范围内，则设置为移动状态
		if(!m_pMapCtrl)
			return;

		if(m_nCanMoveContent == CMC_CANMOVE_NONE)
		{
			m_nMoveStatus = SELECTTRAKER_DRAWING;
		}
		else if(m_nCanMoveContent == CMC_CANMOVE_ELEMENT)
		{
			m_nMoveStatus = ELEMENT_MOVING;

			//加入回退堆栈
			//m_pMapCtrl->GetMap()->GetElementOperationStack()->AddOperation(Element::OPT_EDIT_PROPERTY, m_pCurElement);
		}
		else if(m_nCanMoveContent == CMC_CANMOVE_VERTIX)
		{
			m_nMoveStatus = VERTIX_MOVING;

			//加入回退堆栈
			//m_pMapCtrl->GetMap()->GetElementOperationStack()->AddOperation(Element::OPT_EDIT_PROPERTY, m_pCurElement);
		}

		SetCapture(m_pMapCtrl->GetHWnd());
	}

	void CEditElementVertixTool::MouseMoveEvent (UINT nFlags, CPoint point)
	{
		if(!m_pCurElement)
			return;

		if(!m_pMapCtrl)
			return;

		Carto::CGraphicLayerPtr pGraphicLayer = m_pMapCtrl->GetMap()->GetGraphicLayer();
		if(!pGraphicLayer)
			return;

		Display::IDisplayPtr pDisplay = m_pMapCtrl->GetMap()->GetDisplay();
		if(!pDisplay)
			return;

		GEOMETRY::geom::Coordinate curCoord;	
		pDisplay->GetDisplayTransformation().ConvertDisplayToGeo(point.x, point.y, curCoord);

		switch(m_nMoveStatus)
		{
		case NO_MOVING:
			{
				double bufferDis;	
				pDisplay->GetDisplayTransformation().ConvertDisplayToGeo(m_nBufferDis, bufferDis);

				Element::HIT_TEST_RES hitRes = m_pCurElement->HitTest(curCoord, bufferDis, Element::HH_HIT_GEOMETRY);
				if(hitRes.lHitLocation == Element::HH_HIT_INTERIOR)
				{
					m_nCanMoveContent = CMC_CANMOVE_ELEMENT;
					m_pMapCtrl->SetCursor(cursorSizeAll);
				}
				else
				{
					m_nCanMoveContent = CMC_CANMOVE_NONE;
					m_pMapCtrl->SetCursor(cursorNormal);
				}

				hitRes = m_pCurElement->HitTest(curCoord, bufferDis, Element::HH_HIT_VERTIX);
				if(hitRes.lHitLocation > -1)
				{
					m_nCanMoveContent = CMC_CANMOVE_VERTIX;
					m_pMapCtrl->SetCursor(cursorOnVertix);
					m_hitTestRes = hitRes;
				}
			}
			break;
		case ELEMENT_MOVING:
			{
				m_pCurElement->SetEditMode(Element::EEM_MOVE);
				m_pCurElement->Move(curCoord.x-m_endCoord.x, curCoord.y-m_endCoord.y );

				m_pMapCtrl->UpdateControl(drawEdit);
			}
			break;
		case VERTIX_MOVING:
			{
				m_pCurElement->SetEditMode(Element::EEM_ONDRAW);
				m_pMapCtrl->SetCursor(cursorVertixMove);
				m_pCurElement->MoveVertixTo(m_hitTestRes.lHitLocation,curCoord);
				
				m_pMapCtrl->UpdateControl(drawEdit);
			}
			break;
		default:
			break;
		}


		//更新移动点
		UpdateEndPoint(point);
	}

	void CEditElementVertixTool::LButtonUpEvent (UINT nFlags, CPoint point)
	{
		if(!m_pCurElement)
			return;

		if(!m_pMapCtrl)
			return;

		m_pCurElement->SetEditMode(Element::EEM_EDIT_VERTIX);

		m_nMoveStatus = NO_MOVING;
		m_nCanMoveContent = CMC_CANMOVE_NONE;

		m_pMapCtrl->SetCursor(cursorNormal);
		m_pMapCtrl->UpdateControl(drawElement | drawEdit);

		ReleaseCapture();

	}


	//////////////////////////////////////////////////////////////////////////

	void CEditElementVertixTool::UpdateStartPoint(CPoint pt)
	{
		if(!m_pMapCtrl)
			return;

		Display::IDisplayPtr pDisplay = m_pMapCtrl->GetMap()->GetDisplay();
		if(!pDisplay)
			return;

		m_cPtStart = pt;

		//更新矩形角点坐标
		pDisplay->GetDisplayTransformation().ConvertDisplayToGeo(m_cPtStart.x, m_cPtStart.y, m_startCoord);
	}

	void CEditElementVertixTool::UpdateEndPoint(CPoint pt)
	{
		if(!m_pMapCtrl)
			return;

		Display::IDisplayPtr pDisplay = m_pMapCtrl->GetMap()->GetDisplay();
		if(!pDisplay)
			return;

		m_cPtEnd = pt;

		//更新矩形角点坐标
		pDisplay->GetDisplayTransformation().ConvertDisplayToGeo(m_cPtEnd.x, m_cPtEnd.y, m_endCoord);
	}
}