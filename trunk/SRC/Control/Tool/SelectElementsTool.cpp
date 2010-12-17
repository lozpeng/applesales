#include "stdafx.h"
#include "SelectElementsTool.h"
#include "MapControl.h"

#include "IElement.h"
//#include "CotElementProp.h"



//void CElementPropCallback::UpdateMapCtrl()
//{
//	if(m_pMapControl)
//	{
//        m_pMapControl->UpdateControl((otDrawContent)(DrawElement | DrawEdit));
//	}
//}
namespace Control
{
	static CSelectElementsTool gSelectTool;


	CSelectElementsTool::CSelectElementsTool() : ITool("SelectElementTool")
	{
		
		m_nMoveStatus = NO_MOVING;
		m_nCanMoveContent = CMC_CANMOVE_NONE;

		m_nBufferDis = 3;

		m_pCurElement.reset();

		m_nCurHandle = Element::HH_HIT_NONE;

	}

	CSelectElementsTool::~CSelectElementsTool()
	{

	}


	void CSelectElementsTool::Initialize(Framework::IUIObject *pTargetControl)
	{

		ITool::Initialize(pTargetControl);

		//获取活动地图控件
		m_pMapCtrl = dynamic_cast<Framework::IMapCtrl*>(pTargetControl);
		if(!m_pMapCtrl)
			return;

		//获取活动地区
		m_pMap = m_pMapCtrl->GetMap();
		if(!m_pMap)
			return;

		//设置光标类型
		//m_pMapCtrl->SetCursorType(cursorNormal);

		ITool::Initialize(pTargetControl);
	}
	void CSelectElementsTool::LButtonDownEvent (UINT nFlags, CPoint point)
	{
		//记录移动起点
		UpdateStartPoint(point);
		UpdateEndPoint(point);

		//根据起始点初始化选择框
		m_selectBox.Init(m_startCoord);

		//根据当前的可移动内容，设置当前的移动状态
		if(m_nCanMoveContent == CMC_CANMOVE_NONE)
		{
			m_nMoveStatus = SELECTTRAKER_DRAWING;
		}
		else if(m_nCanMoveContent == CMC_CANMOVE_ELEMENT)
		{
			m_nMoveStatus = ELEMENT_MOVING;
		}
		else if(m_nCanMoveContent == CMC_CANMOVE_HANDLE)
		{
			m_nMoveStatus = HANDLE_MOVING;
		}

		//锁定鼠标
		SetCapture(m_pMapCtrl->GetHWnd());
	}

	void CSelectElementsTool::MouseMoveEvent (UINT nFlags, CPoint point)
	{

		if(m_pMap == NULL)
			return;
		Carto::CGraphicLayerPtr pGraphicLayer = m_pMap->GetGraphicLayer();
		if(!pGraphicLayer)
			return;

		Display::IDisplayPtr pDisplay = m_pMap->GetDisplay();
		if(!pDisplay)
			return;

		pDisplay->GetDisplayTransformation().ConvertDisplayToGeo(m_nBufferDis, m_dbBufferDis);


		GEOMETRY::geom::Coordinate curCoord;	
		pDisplay->GetDisplayTransformation().ConvertDisplayToGeo(point.x, point.y, curCoord);

		//根据当前移动状态分别进行处理
		switch(m_nMoveStatus)
		{
		case NO_MOVING://不能移动状态
			{
				//没有已经选中的图元，不判断是否击中
				long lSelectedElementCount = pGraphicLayer->GetSelectedElementCount();
				if(lSelectedElementCount<1)
					return;

				//判断是否击中所选图元
				Element::HIT_TEST_RES hitRes;
				Element::HIT_HANDLE handle = Element::HH_HIT_NONE;
				Element::IElementPtr pElement;
				m_pCurElement.reset();
				m_nCurHandle = Element::HH_HIT_NONE;
				for(int i=0; i<lSelectedElementCount; i++)
				{
					pElement = pGraphicLayer->GetSelectedElement(i);
					hitRes = pElement->HitTest(curCoord, m_dbBufferDis, Element::HH_HIT_HANDLE);
					handle = (Element::HIT_HANDLE)hitRes.lHitLocation;

					if(handle != Element::HH_HIT_NONE)
					{
						m_pCurElement = pElement;
						m_nCurHandle = handle;
						break;
					}
				}

				//分别对不同击中结果进行处理
				if( m_nCurHandle== Element::HH_HIT_NONE)//未击中
				{
					m_nCanMoveContent = CMC_CANMOVE_NONE;//设置当前可移动内容为：无
					//m_pMapCtrl->SetCursorType(GetHandleCursor(m_nCurHandle));
				}
				else if(m_nCurHandle == Element::HH_HIT_INTERIOR)//击中图元内部
				{
					m_nCanMoveContent = CMC_CANMOVE_ELEMENT;//设置当前可移动内容为：element可以平移
					//m_pMapCtrl->SetCursorType(GetHandleCursor(m_nCurHandle));
				}
				else //击中图元handle
				{
					m_nCanMoveContent = CMC_CANMOVE_HANDLE;//设置当前可移动内容为：handle可以移动
					//m_pMapCtrl->SetCursorType(GetHandleCursor(m_nCurHandle));
				}
			}
			break;
		case SELECTTRAKER_DRAWING://选择框绘制状态
			{
				//更新并绘制选择框
				pDisplay->SetDrawBuffer(drawEdit);
				pDisplay->DrawBackgroud();
				m_selectBox.Update(curCoord);
				m_selectBox.Draw(pDisplay);
				m_pMapCtrl->RefreshScreen();			
			}
			break;
		case ELEMENT_MOVING://图元移动状态
			{
				for(int i=0; i<pGraphicLayer->GetSelectedElementCount(); i++)
				{
					Element::IElementPtr pElement = pGraphicLayer->GetSelectedElement(i);
					pElement->SetEditMode(Element::EEM_MOVE);
					pElement->Move(curCoord.x-m_endCoord.x, curCoord.y-m_endCoord.y );
				}
				m_pMapCtrl->UpdateControl(drawEdit);

			}
			break;
		case HANDLE_MOVING://handle移动状态
			{
				m_pCurElement->SetEditMode(Element::EEM_ONDRAW);
				m_pCurElement->MoveHandleTo(m_nCurHandle,curCoord);
				m_pMapCtrl->UpdateControl(drawEdit);
			}
			break;
		default:
			break;
		}

		//更新移动点
		UpdateEndPoint(point);
	}

	void CSelectElementsTool::LButtonUpEvent (UINT nFlags, CPoint point)
	{


		if(!m_pMapCtrl)
			return;

		////根据当前移动状态分别进行处理
		switch(m_nMoveStatus)
		{
		case SELECTTRAKER_DRAWING://选择状态，选择图元
			{
				GEOMETRY::geom::Geometry*pSelGeometry = NULL;
				if( abs(point.x - m_cPtStart.x) < m_nBufferDis && abs(point.y - m_cPtStart.y) < m_nBufferDis)
					pSelGeometry = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->createPoint(m_endCoord) ;
				else
					pSelGeometry =  m_selectBox.GetGeometry()->clone();
				if(pSelGeometry)
				{
					//构造一个空间查询条件
					Geodatabase::CSpatialQuery queryfilter;
					queryfilter.SetGeometry(pSelGeometry->clone());
					queryfilter.SetSpatialRel(Geodatabase::SpatialRelContains);

					Carto::SELECT_OPTION selctOption ; 
					if((nFlags & MK_CONTROL) == 0)
						selctOption = Carto::SELECT_REPLACE;
					else
						selctOption =  Carto::SELECT_ADD;

					m_pMap->GetGraphicLayer()->Select(&queryfilter, selctOption);
					GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(pSelGeometry);
				}
			}
			break;
		case ELEMENT_MOVING://图元平移状态
			{
				//未移动则做点选处理
				if( point.x == m_cPtStart.x)
				{
					if(m_selectBox.GetGeometry())
					{
						//构造一个空间查询条件
						Geodatabase::CSpatialQuery queryfilter;
						queryfilter.SetGeometry(m_selectBox.GetGeometry()->clone());
						queryfilter.SetSpatialRel(Geodatabase::SpatialRelContains);

						Carto::SELECT_OPTION selctOption ; 
						if((nFlags & MK_CONTROL) == 0)
							selctOption = Carto::SELECT_REPLACE;
						else
							selctOption =  Carto::SELECT_ADD;

						m_pMap->GetGraphicLayer()->Select(&queryfilter, selctOption);
					}
				}
				//移动了则更新图元
				else
				{
					Carto::CGraphicLayerPtr pGraphicLayer = m_pMap->GetGraphicLayer();
					if(!pGraphicLayer)
						return;

					//更新图元
					Element::IElementPtr pElement;
					long SelCount = pGraphicLayer->GetSelectedElementCount();	
					for(int i=0; i<SelCount; i++)
					{
						pElement = pGraphicLayer->GetSelectedElement(i);
						pElement->SetEditMode(Element::EEM_SELECT);
					}
				}	
			}
			break;
		case HANDLE_MOVING://handle移动状态，更新图元
			{
				//更新element bitmap 以及editbitmap
				m_pCurElement->SetEditMode(Element::EEM_SELECT);
			}
			break;
		default:
			break;
		}


		m_nMoveStatus = NO_MOVING;
		m_nCanMoveContent = CMC_CANMOVE_NONE;

		m_pMapCtrl->UpdateControl((DrawContent)(drawElement | drawEdit));
		//m_pMapCtrl->SetCursorType(::LoadCursor(NULL,IDC_ARROW));

		ReleaseCapture();

	}


	void CSelectElementsTool::LButtonDblClkEvent (UINT nFlags, CPoint point)
	{


		Carto::CGraphicLayerPtr pLayer =m_pMap->GetGraphicLayer();
		if(!pLayer)
			return;

		Display::IDisplayPtr pDisplay = m_pMap->GetDisplay();
		if(!pDisplay)
			return;

		GEOMETRY::geom::Coordinate curCoord;	
		pDisplay->GetDisplayTransformation().ConvertDisplayToGeo(point.x, point.y, curCoord);

		GEOMETRY::geom::Geometry*pSelGeometry = NULL;
		pSelGeometry = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->createPoint(curCoord) ;

		if(pSelGeometry)
		{


			//displaytoGeo
			double dbTolerance;
			pDisplay->GetDisplayTransformation().ConvertDisplayToGeo(3,dbTolerance);

			//构造一个空间查询条件
			Geodatabase::CSpatialQuery queryfilter;
			queryfilter.SetGeometry(pSelGeometry->clone());
			queryfilter.SetSpatialRel(Geodatabase::SpatialRelContains);
			//queryfilter.SetTolerance(dbTolerance);

			Carto::SELECT_OPTION selctOption ; 
			selctOption = Carto::SELECT_REPLACE;

			m_pMap->GetGraphicLayer()->Select(&queryfilter, selctOption);
			GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(pSelGeometry);


			OnEditElementProp();
		}
	}

	void CSelectElementsTool::KeyDownEvent (UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		if (nChar == VK_DELETE)//
		{


			Carto::CGraphicLayerPtr pLayer = m_pMap->GetGraphicLayer();
			if(!pLayer)
				return;

			for(int i=0; i<pLayer->GetSelectedElementCount(); i++)
			{
				pLayer->RemoveElement(pLayer->GetSelectedElement(i));
			}

			pLayer->UnselectAllElements();

			m_pMapCtrl->UpdateControl((DrawContent)(drawElement | drawEdit));

			m_pMapCtrl->SetCurTool("SelectElementTool");

		}

	}


	//////////////////////////////////////////////////////////////////////////

	void CSelectElementsTool::UpdateStartPoint(CPoint pt)
	{
		if(m_pMap == NULL)
			return;
		Display::IDisplayPtr pDisplay = m_pMap->GetDisplay();
		if(!pDisplay)
			return;

		m_cPtStart = pt;

		//更新矩形角点坐标
		pDisplay->GetDisplayTransformation().ConvertDisplayToGeo(m_cPtStart.x, m_cPtStart.y, m_startCoord);
	}

	void CSelectElementsTool::UpdateEndPoint(CPoint pt)
	{

		if(m_pMap == NULL)
			return;
		Display::IDisplayPtr pDisplay =m_pMap->GetDisplay();
		if(!pDisplay)
			return;

		m_cPtEnd = pt;

		//更新矩形角点坐标
		pDisplay->GetDisplayTransformation().ConvertDisplayToGeo(m_cPtEnd.x, m_cPtEnd.y, m_endCoord);
	}

	long CSelectElementsTool::GetHandleCursor(Element::HIT_HANDLE nHandle)
	{

		/*switch(nHandle)
		{
		case Element::HH_HIT_NONE:
			return cursorNormal;
		case Element::HH_HIT_INTERIOR:
			return cursorSizeAll;
		case Element::HH_HIT_MINX_MINY:
			return cursorRightTop;
		case Element::HH_HIT_MIDX_MINY:
			return cursorTopBottom;
		case Element::HH_HIT_MAXX_MINY:
			return cursorleftTop;
		case Element::HH_HIT_MAXX_MIDY:
			return cursorLeftRight;
		case Element::HH_HIT_MAXX_MAXY:
			return cursorRightTop;
		case Element::HH_HIT_MIDX_MAXY:
			return cursorTopBottom;
		case Element::HH_HIT_MINX_MAXY:
			return cursorleftTop;
		case Element::HH_HIT_MINX_MIDY:
			return cursorLeftRight;
		case Element::HH_HIT_ONE:
			return cursorSizeAll;
		default:
			return cursorNormal;
		}*/
		return 1;
	}

	void CSelectElementsTool::OnEditElementProp()
	{


		Carto::CGraphicLayerPtr pGraphicLayer = m_pMap->GetGraphicLayer();
		if(!pGraphicLayer)
			return;

		if(pGraphicLayer->GetSelectedElementCount()==0)
			return;

		Element::IElementPtr pElement =  pGraphicLayer->GetSelectedElement(0);


		//CElementPropCallback callback;
		//callback.SetMapCtrl(m_pMapCtrl);

		////显示图元属性
		//if(IDOK==otComUI::CotElementProp::ShowElementProp(pElement,m_pMap,&callback))
		//{
		//	m_pMapCtrl->UpdateControl((otDrawContent)(otDrawElement | otDrawEdit));
		//}

	}


}