#include "stdafx.h"
#include "SelectFrameElementsTool.h"
#include "IElement.h"
#include "MapFrame.h"

#include "Control.h"

extern CControlApp theApp;

static CSelectFrameElementsTool gSelectFrameElementsTool;


CSelectFrameElementsTool::CSelectFrameElementsTool() : Framework::ITool("SelectFrameElementsTool")
{
	m_hCursor = NULL;
	m_nMoveStatus = NO_MOVING;
	m_nCanMoveContent = CMC_CANMOVE_NONE;

	m_nBufferDis = 3;

	m_pCurElement.reset();

	m_nCurHandle = Element::HH_HIT_NONE;

}

CSelectFrameElementsTool::~CSelectFrameElementsTool()
{
	if(m_hCursor)
	{
		DeleteObject( m_hCursor );
	}
}


void CSelectFrameElementsTool::Initialize(Framework::IUIObject *pTargetControl)
{
	ITool::Initialize(pTargetControl);

	//��ʼ�����
	if(m_hCursor==NULL)
	{
		m_hCursor =::LoadCursor( theApp.m_hInstance , MAKEINTRESOURCE( IDC_Arrow) );
	}


	//��ȡ���ͼ�ؼ�
	m_pLayoutCtrl = dynamic_cast<Framework::ILayoutCtrl*>(pTargetControl);
	if(!m_pLayoutCtrl)
		return;

	//���ù������
	m_pLayoutCtrl->SetCursor(m_hCursor);


}

void CSelectFrameElementsTool::LButtonDownEvent (UINT nFlags, CPoint point)
{
	if(!m_pLayoutCtrl)
		return;


	if(!m_pLayoutCtrl->GetPageLayout())
		return;

	//��¼�ƶ����
	UpdateStartPoint(point);
	UpdateEndPoint(point);

	//������ʼ���ʼ��ѡ���
	m_selectBox.Init(m_startCoord);

	//���ݵ�ǰ�Ŀ��ƶ����ݣ����õ�ǰ���ƶ�״̬
	

	if(m_nCanMoveContent == CMC_CANMOVE_NONE)
	{
		m_nMoveStatus = SELECTTRAKER_DRAWING;
	}
	else if(m_nCanMoveContent == CMC_CANMOVE_ELEMENT)
	{
		m_nMoveStatus = ELEMENT_MOVING;
		//������˶�ջ
		//m_pLayoutCtrl->GetPageLayout()->GetElementOperationStack()->AddOperation(Element::OPT_EDIT_PROPERTY, m_pLayoutCtrl->GetPageLayout()->GetGraphicLayer()->GetSelectedElements());
	}
	else if(m_nCanMoveContent == CMC_CANMOVE_HANDLE)
	{
		//������˶�ջ
		//m_pLayoutCtrl->GetPageLayout()->GetElementOperationStack()->AddOperation(Element::OPT_EDIT_PROPERTY, m_pLayoutCtrl->GetPageLayout()->GetGraphicLayer()->GetSelectedElements());
		m_nMoveStatus = HANDLE_MOVING;
	}


	SetCapture(m_pLayoutCtrl->GetHWnd());
}

void CSelectFrameElementsTool::MouseMoveEvent (UINT nFlags, CPoint point)
{
	if(!m_pLayoutCtrl)
		return;


	if(!m_pLayoutCtrl->GetPageLayout())
		return;

	
	Carto::CGraphicLayerPtr pGraphicLayer = m_pLayoutCtrl->GetPageLayout()->GetGraphicLayer();
	if(!pGraphicLayer)
		return;

	Display::IDisplayPtr pDisplay = m_pLayoutCtrl->GetPageLayout()->GetDisplay();
	if(!pDisplay)
		return;

	pDisplay->GetDisplayTransformation().ConvertDisplayToGeo(m_nBufferDis, m_dbBufferDis);

	GEOMETRY::geom::Coordinate curCoord;	
	pDisplay->GetDisplayTransformation().ConvertDisplayToGeo(point.x, point.y, curCoord);

	//���ݵ�ǰ�ƶ�״̬�ֱ���д���
	switch(m_nMoveStatus)
	{
	case NO_MOVING://�����ƶ�״̬
		{
			//û���Ѿ�ѡ�е�ͼԪ�����ж��Ƿ����
			long lSelectedElementCount = pGraphicLayer->GetSelectedElementCount();
			if(lSelectedElementCount<1)
				return;
			
            //�ж��Ƿ������ѡͼԪ
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

			//�ֱ�Բ�ͬ���н�����д���
			if( m_nCurHandle== Element::HH_HIT_NONE)//δ����
			{
				m_nCanMoveContent = CMC_CANMOVE_NONE;//���õ�ǰ���ƶ�����Ϊ����
				//m_pLayoutCtrl->SetCursor(GetHandleCursor(m_nCurHandle));
			}
			else if(m_nCurHandle == Element::HH_HIT_INTERIOR)//����ͼԪ�ڲ�
			{
				m_nCanMoveContent = CMC_CANMOVE_ELEMENT;//���õ�ǰ���ƶ�����Ϊ��element����ƽ��
				//m_pLayoutCtrl->SetCursor(GetHandleCursor(m_nCurHandle));
			}
			else //����ͼԪhandle
			{
				m_nCanMoveContent = CMC_CANMOVE_HANDLE;//���õ�ǰ���ƶ�����Ϊ��handle�����ƶ�
				//m_pLayoutCtrl->SetCursor(GetHandleCursor(m_nCurHandle));
			}
		}
		break;
	case SELECTTRAKER_DRAWING://ѡ������״̬
		{
			//���²�����ѡ���
			pDisplay->SetDrawBuffer(drawEdit);
			pDisplay->DrawBackgroud();
			m_selectBox.Update(curCoord);
			m_selectBox.Draw(pDisplay);
			m_pLayoutCtrl->RefreshScreen();			
		}
		break;
	case ELEMENT_MOVING://ͼԪ�ƶ�״̬
		{
			for(int i=0; i<pGraphicLayer->GetSelectedElementCount(); i++)
			{
				Element::IElementPtr pElement = pGraphicLayer->GetSelectedElement(i);
				pElement->SetEditMode(Element::EEM_MOVE);
				pElement->Move(curCoord.x-m_endCoord.x, curCoord.y-m_endCoord.y );
			}
			m_pLayoutCtrl->UpdateControl(drawEdit);
			
		}
		break;
	case HANDLE_MOVING://handle�ƶ�״̬
		{
			m_pCurElement->SetEditMode(Element::EEM_ONDRAW);
			m_pCurElement->MoveHandleTo(m_nCurHandle,curCoord);
			m_pLayoutCtrl->UpdateControl(drawEdit);
		}
		break;
	default:
		break;
	}

	//�����ƶ���
	UpdateEndPoint(point);
}

void CSelectFrameElementsTool::LButtonUpEvent (UINT nFlags, CPoint point)
{
	if(!m_pLayoutCtrl)
		return;


	if(!m_pLayoutCtrl->GetPageLayout())
		return;

	////���ݵ�ǰ�ƶ�״̬�ֱ���д���
	switch(m_nMoveStatus)
	{
	case SELECTTRAKER_DRAWING://ѡ��״̬��ѡ��ͼԪ
		{
			GEOMETRY::geom::Geometry*pSelGeometry = NULL;
			if( abs(point.x - m_cPtStart.x) < m_nBufferDis && abs(point.y - m_cPtStart.y) < m_nBufferDis)
				pSelGeometry = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->createPoint(m_endCoord) ;
			else
				pSelGeometry =  m_selectBox.GetGeometry()->clone();
			if(pSelGeometry)
			{
				//��ȡ�����
				Display::IDisplayPtr pDisplay = m_pLayoutCtrl->GetPageLayout()->GetDisplay();
				if(!pDisplay)
					return;

				//displaytoGeo
				double dbTolerance;
				pDisplay->GetDisplayTransformation().ConvertDisplayToGeo(3,dbTolerance);

				//����һ���ռ��ѯ����
				Geodatabase::CSpatialQuery queryfilter;
				queryfilter.SetGeometry(pSelGeometry->clone());
				queryfilter.SetSpatialRel(Geodatabase::SpatialRelContains);
				//queryfilter.SetTolerance(dbTolerance);

				Carto::SELECT_OPTION selctOption ; 
				if((nFlags & MK_CONTROL) == 0)
					selctOption = Carto::SELECT_REPLACE;
				else
					selctOption =  Carto::SELECT_ADD;

				m_pLayoutCtrl->GetPageLayout()->GetGraphicLayer()->Select(&queryfilter, selctOption);
				GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(pSelGeometry);
			}
		}
		break;
	case ELEMENT_MOVING://ͼԪƽ��״̬
		{
			//δ�ƶ�������ѡ����
			if( point.x == m_cPtStart.x)
			{
				if(m_selectBox.GetGeometry())
				{
					//��ȡ�����
					Display::IDisplayPtr pDisplay = m_pLayoutCtrl->GetPageLayout()->GetDisplay();
					if(!pDisplay)
						return;

					//displaytoGeo
					double dbTolerance;
					pDisplay->GetDisplayTransformation().ConvertDisplayToGeo(3,dbTolerance);

					//����һ���ռ��ѯ����
					Geodatabase::CSpatialQuery queryfilter;
					queryfilter.SetGeometry(m_selectBox.GetGeometry()->clone());
					queryfilter.SetSpatialRel(Geodatabase::SpatialRelContains);
//					queryfilter.SetTolerance(dbTolerance);

					Carto::SELECT_OPTION selctOption ; 
					if((nFlags & MK_CONTROL) == 0)
						selctOption = Carto::SELECT_REPLACE;
					else
						selctOption =  Carto::SELECT_ADD;

					m_pLayoutCtrl->GetPageLayout()->GetGraphicLayer()->Select(&queryfilter, selctOption);
				}
			}
			//�ƶ��������ͼԪ
			else
			{
				Carto::CGraphicLayerPtr pGraphicLayer = m_pLayoutCtrl->GetPageLayout()->GetGraphicLayer();
				if(!pGraphicLayer)
					return;

				//����ͼԪ
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
	case HANDLE_MOVING://handle�ƶ�״̬������ͼԪ
		{
			//����element bitmap �Լ�editbitmap
			m_pCurElement->SetEditMode(Element::EEM_SELECT);
		}
		break;
	default:
		break;
	}


	m_nMoveStatus = NO_MOVING;
	m_nCanMoveContent = CMC_CANMOVE_NONE;

	m_pLayoutCtrl->UpdateControl(drawAll);
	//m_pLayoutCtrl->SetCursor(cursorNormal);

	ReleaseCapture();

}

void CSelectFrameElementsTool::LButtonDblClkEvent (UINT nFlags, CPoint point)
{
	
	Carto::CGraphicLayerPtr pGraphicLayer = m_pLayoutCtrl->GetPageLayout()->GetGraphicLayer();
	if(!pGraphicLayer)
		return;

	Display::IDisplayPtr pDisplay = m_pLayoutCtrl->GetPageLayout()->GetDisplay();
	if(!pDisplay)
		return;

	GEOMETRY::geom::Coordinate curCoord;	
	pDisplay->GetDisplayTransformation().ConvertDisplayToGeo(point.x, point.y, curCoord);

	GEOMETRY::geom::Geometry*pSelGeometry = NULL;
	pSelGeometry = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->createPoint(curCoord) ;
	
	if(pSelGeometry)
	{
		//��ȡ�����
		Display::IDisplayPtr pDisplay = m_pLayoutCtrl->GetPageLayout()->GetDisplay();
		if(!pDisplay)
			return;

		//displaytoGeo
		double dbTolerance;
		pDisplay->GetDisplayTransformation().ConvertDisplayToGeo(3,dbTolerance);

		//����һ���ռ��ѯ����
		Geodatabase::CSpatialQuery queryfilter;
		queryfilter.SetGeometry(pSelGeometry->clone());
		queryfilter.SetSpatialRel(Geodatabase::SpatialRelContains);
//		queryfilter.SetTolerance(dbTolerance);

		Carto::SELECT_OPTION selctOption ; 
		selctOption = Carto::SELECT_REPLACE;

		m_pLayoutCtrl->GetPageLayout()->GetGraphicLayer()->Select(&queryfilter, selctOption);
		GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(pSelGeometry);

		OnEditElementProp();
	}
}

void CSelectFrameElementsTool::RButtonDownEvent (UINT nFlags, CPoint point)
{

	

	Carto::CGraphicLayerPtr pGraphicLayer = m_pLayoutCtrl->GetPageLayout()->GetGraphicLayer();
	if(!pGraphicLayer)
		return;

	//otLayout::CDllResource dllRes;

	//CMenu menu;
	//if(!menu.LoadMenu(IDR_MENU_ELEMENT_PROP))
	//	return;

	//CMenu* pPopup = menu.GetSubMenu(0);
	//CPoint srnPoint = point;
	//CWnd *pWnd =dynamic_cast<CWnd*>(pLayoutCtrl);
	//pWnd->ClientToScreen(&srnPoint);
	//if (pPopup!=NULL)
	//{		

	//	//��������ĿС�ڵ���1������ɾ���ڵ�
	//	if(pGraphicLayer->GetSelectedElementCount()<1)
	//	{
	//		pPopup->EnableMenuItem( ID_COPY_ELEMENT,MF_GRAYED);
	//		pPopup->EnableMenuItem( ID_CUT_ELEMENT,MF_GRAYED);
	//		pPopup->EnableMenuItem( ID_DELETE_ELEMENT,MF_GRAYED);
	//		pPopup->EnableMenuItem( ID_ELEMENT_PROPERTY,MF_GRAYED);

	//		pPopup->EnableMenuItem( ID_ELEMENT_MOVE_DOWN,MF_GRAYED);
	//		pPopup->EnableMenuItem( ID_ELEMENT_MOVE_UP,MF_GRAYED);
	//		pPopup->EnableMenuItem( ID_ELEMENT_MOVE_TOP,MF_GRAYED);
	//		pPopup->EnableMenuItem( ID_ELEMENT_MOVE_BOTTOM,MF_GRAYED);
	//	}

	//	if(pGraphicLayer->GetSelectedElementCount()<2)
	//	{
	//		pPopup->EnableMenuItem( ID_GROUP_ELEMENT,MF_GRAYED);

	//		pPopup->EnableMenuItem( ID_ELEMENT_ALIGN_LEFT,MF_GRAYED);
	//		pPopup->EnableMenuItem( ID_ELEMENT_ALIGN_RIGHT,MF_GRAYED);
	//		pPopup->EnableMenuItem( ID_ELEMENT_ALIGN_TOP,MF_GRAYED);
	//		pPopup->EnableMenuItem( ID_ELEMENT_ALIGN_BOTTOM,MF_GRAYED);
	//		pPopup->EnableMenuItem( ID_ELEMENT_ALIGN_HORI_CENTER,MF_GRAYED);
	//		pPopup->EnableMenuItem( ID_ELEMENT_ALIGN_VERT_CENTER,MF_GRAYED);
	//		
	//		pPopup->EnableMenuItem( ID_ELEMENT_VERT_SCATTER,MF_GRAYED);
	//		pPopup->EnableMenuItem( ID_ELEMENT_HORI_SCATTER,MF_GRAYED);
	//		
	//		pPopup->EnableMenuItem( ID_ELEMENT_SAME_HEIGHT,MF_GRAYED);
	//		pPopup->EnableMenuItem( ID_ELEMENT_SAME_WIDTH,MF_GRAYED);
	//		pPopup->EnableMenuItem( ID_ELEMENT_SAME_WIDTH_HEIGHT,MF_GRAYED);
	//	}

	//	int nSelCnt = pGraphicLayer->GetSelectedElementCount();
	//	BOOL bGroupExist = FALSE;
	//	if( nSelCnt> 0)
	//	{
	//		for(int i=0; i<nSelCnt; i++)
	//		{
	//			if(pGraphicLayer->GetSelectedElement(i)->GetType() == Element::ET_GROUP_ELEMENT)
	//			{
	//				bGroupExist = TRUE;
	//				break;
	//			}
	//		}
	//	}
	//	if(!bGroupExist)
	//		pPopup->EnableMenuItem( ID_UNGROUP_ELEMENT,MF_GRAYED);

	//	if(pLayoutCtrl->GetElementCopyBoard()->Count() <1)
	//	{
	//		pPopup->EnableMenuItem( ID_PASTE_ELEMENT,MF_GRAYED);
	//	}
	//}

	//pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, srnPoint.x, srnPoint.y, pWnd);

}

void CSelectFrameElementsTool::KeyDownEvent (UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_DELETE)//
	{
		Carto::CGraphicLayerPtr pLayer = m_pLayoutCtrl->GetPageLayout()->GetGraphicLayer();
		if(!pLayer)
			return;

		Element::CElementCollection deletes;

		for(int i=0; i<pLayer->GetSelectedElementCount(); i++)
		{
			Element::IElementPtr pElement = pLayer->GetSelectedElement(i);

			pLayer->RemoveElement(pElement);

			deletes.Add(pElement);

			if(pElement->GetType() == Element::ET_MAP_FRAME_ELEMENT)
			{
				long cnt = pLayer->GetElementCount();
				for(int i=0;i<cnt; i++)
				{
					Element::IElementPtr pElementInner = pLayer->GetElement(i);
					if(pElementInner == NULL)
						continue;

					if(pElementInner->GetType() & Element::ET_MAP_SURROUND_ELEMENT)
					{
						Element::IMapSurround* pMapSurround = dynamic_cast<Element::IMapSurround*>(pElementInner.get());
						if(pMapSurround->GetMapFrame() == pElement.get())
						{
							pLayer->RemoveElement(pElementInner);
							deletes.Add(pElementInner);
						}
					}
					else if(pElementInner->GetType() == Element::ET_GROUP_ELEMENT)
					{
						Element::CGroupElement* pGroupElement = dynamic_cast<Element::CGroupElement*>(pElementInner.get());
						if(pGroupElement->IsMapSurroundElementExist())
						{
							pLayer->RemoveElement(pElementInner);
							deletes.Add(pElementInner);
						}
					}
				}
			}
		}

		pLayer->UnselectAllElements();

		m_pLayoutCtrl->UpdateControl(drawAll);
	}

}

//////////////////////////////////////////////////////////////////////////

void CSelectFrameElementsTool::UpdateStartPoint(CPoint pt)
{
	
	Display::IDisplayPtr pDisplay =m_pLayoutCtrl->GetPageLayout()->GetDisplay();
	if(!pDisplay)
		return;

	m_cPtStart = pt;

	//���¾��νǵ�����
	pDisplay->GetDisplayTransformation().ConvertDisplayToGeo(m_cPtStart.x, m_cPtStart.y, m_startCoord);
}

void CSelectFrameElementsTool::UpdateEndPoint(CPoint pt)
{
	

	Display::IDisplayPtr pDisplay = m_pLayoutCtrl->GetPageLayout()->GetDisplay();
	if(!pDisplay)
		return;

	m_cPtEnd = pt;

	//���¾��νǵ�����
	pDisplay->GetDisplayTransformation().ConvertDisplayToGeo(m_cPtEnd.x, m_cPtEnd.y, m_endCoord);
}

long CSelectFrameElementsTool::GetHandleCursor(Element::HIT_HANDLE nHandle)
{

	switch(nHandle)
	{
	//case Element::HH_HIT_NONE:
	//	return cursorNormal;
	//case Element::HH_HIT_INTERIOR:
	//	return cursorSizeAll;
	//case Element::HH_HIT_MINX_MINY:
	//	return cursorRightTop;
	//case Element::HH_HIT_MIDX_MINY:
	//	return cursorTopBottom;
	//case Element::HH_HIT_MAXX_MINY:
	//	return cursorleftTop;
	//case Element::HH_HIT_MAXX_MIDY:
	//	return cursorLeftRight;
	//case Element::HH_HIT_MAXX_MAXY:
	//	return cursorRightTop;
	//case Element::HH_HIT_MIDX_MAXY:
	//	return cursorTopBottom;
	//case Element::HH_HIT_MINX_MAXY:
	//	return cursorleftTop;
	//case Element::HH_HIT_MINX_MIDY:
	//	return cursorLeftRight;
	//default:
	//	return cursorNormal;
	}
	return 1;
}

void CSelectFrameElementsTool::OnEditElementProp()
{
	//Framework::ILayoutCtrl* pLayoutCtrl = Framework::ILayoutCtrl::GetActiveLayoutCtrl();
	//if(!pLayoutCtrl)
	//	return;

	//Carto::CGraphicLayerPtr pGraphicLayer = pLayoutCtrl->GetPageLayout()->GetGraphicLayer();
	//if(!pGraphicLayer)
	//	return;

	//Element::IElementPtr pElement =  pGraphicLayer->GetSelectedElement(0);

	////������˶�ջ
	//pLayoutCtrl->GetPageLayout()->GetElementOperationStack()->AddOperation(Element::OPT_EDIT_PROPERTY, pElement);

	//switch(pElement->GetType())
	//{
	//case Element::ET_GROUP_ELEMENT:
	//	{
	//		otLayout::CDllResource hdll;

	//		CSimpleElementProperSheet sheet("����");
	//		sheet.SetElement(pElement);
	//		if(sheet.DoModal()==IDOK)
	//		{
	//			pLayoutCtrl->UpdateControl(drawAll);
	//		}
	//	}
	//	break;
	//case Element::ET_SIMPLE_TEXT_ELEMENT:
	//	{
	//		otLayout::CDllResource hdll;

	//		CSimpleTextProperSheet sheet("����");
	//		sheet.SetElement(pElement);
	//		if(sheet.DoModal()==IDOK)
	//		{
	//			pLayoutCtrl->UpdateControl(drawAll);
	//		}
	//	}
	//	break;
	//case Element::ET_MAP_TITLE:	
	//	{
	//		otLayout::CDllResource hdll;

	//		CMapTitleProperSheet sheet("����");
	//		sheet.SetElement(pElement);
	//		if(sheet.DoModal()==IDOK)
	//		{
	//			pLayoutCtrl->UpdateControl(drawAll);
	//		}
	//	}
	//	break;
	//case Element::ET_MAP_FRAME_ELEMENT:
	//	{
	//		otLayout::CDllResource hdll;

	//		CMapFrameProperSheet sheet("����");
	//		sheet.SetElement(pElement);
	//		if(sheet.DoModal()==IDOK)
	//		{
	//			pLayoutCtrl->UpdateControl(drawAll);
	//		}
	//	}
	//	break;
	//case Element::ET_MARKER_NORTH_ARROW:
	//	{
	//		otLayout::CDllResource hdll;

	//		CMarkerNorthArrowProperSheet sheet("����");
	//		sheet.SetElement(pElement);
	//		if(sheet.DoModal()==IDOK)
	//		{
	//			pLayoutCtrl->UpdateControl(drawAll);
	//		}
	//	}
	//	break;
	//case Element::ET_ALTERNATING_SCALEBAR:
	//case Element::ET_SCALELINE:
	//	{
	//		otLayout::CDllResource hdll;

	//		CScaleBarProperSheet sheet("����");
	//		sheet.SetElement(pElement);
	//		if(sheet.DoModal()==IDOK)
	//		{

	//			pLayoutCtrl->UpdateControl(drawAll);
	//		}
	//	}
	//	break;
	//case Element::ET_LEGEND:
	//	{
	//		otLayout::CDllResource hdll;

	//		CLegendProperSheet sheet("����");
	//		sheet.SetElement(pElement);
	//		if(sheet.DoModal()==IDOK)
	//		{
	//			pLayoutCtrl->UpdateControl(drawAll);
	//		}
	//	}
	//	break;
	//case Element::ET_RELATIONDISTRICT_TABLE:
	//	{
	//		otLayout::CDllResource hdll;

	//		CDistrictRelationTableProperSheet sheet("����");
	//		sheet.SetElement( pElement );
	//		if( sheet.DoModal() == IDOK )
	//		{
	//			pLayoutCtrl->UpdateControl( drawAll );
	//		}
	//	}
	//	break;
	//default:
	//	break;
	//}
}

