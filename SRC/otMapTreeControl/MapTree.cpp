#include "StdAfx.h"
#include "MapTree.h"
#include "otMapTreeCtrl.h"
#include "FeatureLayer.h"
#include "RasterLayer.h"
#include "Resource.h"
#include "DllResource.h"
#include "otLayerProp.h"
#include "MapTreeCallback.h"
#include <geometry/geom/Geometry.h>

#define   DRAG_DELAY   60

typedef std::pair< HTREEITEM , Carto::CMap*> MapItem_Pair;	
std::map<HTREEITEM, Carto::CMap*>::const_iterator Map_Iterator;

IMPLEMENT_DYNAMIC(CMapTree, CTreeCtrl)

CMapTree::CMapTree()
{
	m_bDragging = false;
	m_pDragImage = NULL;
	m_hActMapItem = NULL;
	m_nHoverTimerID =m_nScrollTimerID =0;

	m_pMapControl =NULL;

	m_bShowMenu =TRUE;
}

CMapTree::~CMapTree()
{
	if (m_pDragImage)
	{	
		delete m_pDragImage;
		m_pDragImage = NULL;
	}	
}

BEGIN_MESSAGE_MAP(CMapTree, CTreeCtrl)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_NCLBUTTONDOWN()
	ON_NOTIFY_REFLECT(NM_CLICK, &CMapTree::OnNMClick)
	ON_WM_RBUTTONDOWN()

	ON_NOTIFY_REFLECT(TVN_BEGINDRAG, OnBegindrag)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_TIMER()
	ON_NOTIFY_REFLECT(TVN_ENDLABELEDIT, OnEndlabeledit)
	ON_WM_CONTEXTMENU()
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, &CMapTree::OnTvnSelchanged)

	ON_WM_LBUTTONDBLCLK()
	ON_WM_RBUTTONUP()

	ON_COMMAND(ID_REMOVE_LAYER, &CMapTree::OnRemoveLayer)
	ON_COMMAND(ID_LAYER_PROP, &CMapTree::OnLayerProp)

END_MESSAGE_MAP()

int CMapTree::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CTreeCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;

	CDllResource dllRes;

	//��Ҫָ��imagelist����ɫΪ���ɫ
	m_imageList.Create(16,16,ILC_COLOR24|ILC_MASK,1,1);
	CBitmap bmp;
	bmp.LoadBitmap(IDB_MAP_TREE);
	m_imageList.Add(&bmp,RGB(255,255,255));

	//m_imageList.Create ( IDB_MAP_TREE, 16, 1, RGB(255,255,255) );
	SetImageList (&m_imageList, TVSIL_NORMAL);

	m_imgState.Create ( IDB_MAPTREE_STATE, 16, 1, RGB(255,255,255) );
	SetImageList (&m_imgState,TVSIL_STATE);

	return 0;
} 
void CMapTree:: OnSize(UINT nType, int cx, int cy)
{
	CTreeCtrl::OnSize(nType, cx, cy);
}

void CMapTree:: OnNcLButtonDown(UINT nHitTest, CPoint point)
{

}
void CMapTree:: OnNMClick(NMHDR *pNMHDR, LRESULT *pResult)
{

}
void CMapTree:: OnRButtonDown(UINT nFlags, CPoint point)
{

	SetFocus();

	//���������¼�
	m_pTreeCtrl->FireMouseDown(2,0,point.x,point.y);

    //�Ƿ���ʾ�����Ĳ˵�
	if(!m_bShowMenu)
	{
		return;
	}
	HTREEITEM hHit = NULL;
	UINT flag;

	hHit = HitTest(point, &flag);

	//�ж��Ƿ��ڽڵ��ϵ���Ҽ�
	if(hHit && (flag & TVHT_ONITEM))
	{
		SelectItem(hHit);
	}
	else
	{
		return;
	}

	CMenu menu;

	//���ѡ��ͼ��ڵ�
    if(m_iSelectedItemType ==eLayerItem)
	{
		if(!menu.LoadMenu(IDR_MAPTREE_CONTENT_MEMU))
			return;

		CMenu* pPopup = menu.GetSubMenu(0);

		UpdateMenuStatus(pPopup);

		CPoint srnPoint = point;
		ClientToScreen(&srnPoint);
		pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, srnPoint.x, srnPoint.y, dynamic_cast<CWnd*>(this));
	}
	
	
}

//���²˵����״̬
void CMapTree::UpdateMenuStatus(CMenu *pMenu)
{
	//if(!pMenu)
	//{
	//	return;
	//}
	//HTREEITEM item =GetSelectedItem();
	//long lNumItems;
	//UINT nID = 0;
	//BOOL bIsEnable;
	//lNumItems =pMenu->GetMenuItemCount();
	//for( long l = 0;l<lNumItems;l++)
	//{
	//	bIsEnable =TRUE;
	//	nID = pMenu->GetMenuItemID(l);
	//	if(nID == 0xFFFFFFFF)
	//	{
	//		CMenu popMenu;
	//		MENUITEMINFO menuInfo;
	//		menuInfo.cbSize = sizeof(MENUITEMINFO);
	//		menuInfo.fMask = MIIM_SUBMENU;
	//		pMenu->GetMenuItemInfo((UINT)l,&menuInfo,TRUE);
	//		if(NULL != menuInfo.hSubMenu)
	//		{
	//			popMenu.Attach(menuInfo.hSubMenu);
	//			UpdateMenuStatus(&popMenu);
	//		}

	//	}
	//	else if(nID == ID_ACTIVE_MAP)//�����ͼ
	//	{
	//		if(m_iSelectedItemType==otFramework::eMapItem )
	//		{
	//			bIsEnable =TRUE;
	//		}
	//		else
	//		{
	//			bIsEnable = FALSE;
	//		}
	//	}
	//	else if(nID == ID_DELETE_MAP) //ɾ����ͼ
	//	{
	//		if(m_iSelectedItemType==otFramework::eMapItem/* || m_iSelectedItemType==otFramework::eActiveMapItem*/)
	//		{
	//			bIsEnable =TRUE;
	//		}
	//		else
	//		{
	//			bIsEnable = FALSE;
	//		}
	//	}
	//	else if(nID == ID_MAP_PROP)  //��ͼ����
	//	{
	//		if(m_iSelectedItemType==otFramework::eMapItem || m_iSelectedItemType==otFramework::eActiveMapItem)
	//		{
	//			bIsEnable =TRUE;
	//		}
	//		else
	//		{
	//			bIsEnable = FALSE;
	//		}
	//	}
	//	else if(nID == ID_REMOVE_LAYER) //ɾ��ͼ��
	//	{
	//		if(m_iSelectedItemType==otFramework::eLayerItem || m_iSelectedItemType==otFramework::eLegendItem)
	//		{
	//			bIsEnable =TRUE;
	//		}
	//		else
	//		{
	//			bIsEnable = FALSE;
	//		}
	//	}
	//	else if(nID == ID_REMOVE_ALL_LAYER) //ɾ������ͼ��
	//	{

	//		BOOL bEnable = FALSE;

	//		bEnable = IsCurItemActivated();

	//		BOOL bHasLayer = FALSE;

	//		otFramework::IMapCtrl *pMapCtrl =otFramework::IMapCtrl::GetActiveMapCtrl();
	//		if(!pMapCtrl)
	//		{
	//			return;
	//		}

	//		Carto::CMapPtr ptrMap = pMapCtrl->GetActiveMap();
	//		if (ptrMap != NULL)
	//		{
	//			Carto::CLayerArray layerArray = ptrMap->GetLayers();
	//			bHasLayer = bEnable && (layerArray.GetSize() > 0);
	//		}

	//		if((m_iSelectedItemType == otFramework::eLayerItem && bEnable) || (m_iSelectedItemType == otFramework::eActiveMapItem) && bHasLayer)
	//		{
	//			bIsEnable =TRUE;
	//		}
	//		else
	//		{
	//			bIsEnable =FALSE;
	//		}
	//	}
	//	else if(nID == ID_OPEN_ATTRIBUTETABLE)
	//	{
	//		if(m_iSelectedItemType==otFramework::eLayerItem || m_iSelectedItemType==otFramework::eLegendItem)
	//		{
	//			bIsEnable =TRUE;
	//		}
	//		else
	//		{
	//			bIsEnable = FALSE;
	//		}

	//	}
	//	else if( nID == ID_LAYER_PROP )
	//	{
	//		if(m_iSelectedItemType==otFramework::eLayerItem || m_iSelectedItemType==otFramework::eLegendItem)
	//		{
	//			bIsEnable =TRUE;
	//		}
	//		else
	//		{
	//			bIsEnable = FALSE;
	//		}
	//	}


	//	if(bIsEnable)
	//		pMenu->EnableMenuItem(nID,MF_BYCOMMAND|MF_ENABLED);
	//	else
	//		pMenu->EnableMenuItem(nID,MF_BYCOMMAND|MF_DISABLED|MF_GRAYED);
	//}
}


void CMapTree:: OnLButtonDown(UINT nFlags, CPoint point)
{
	//���������¼�
	m_pTreeCtrl->FireMouseDown(1,0,point.x,point.y);

	UINT uFlags=0;
	HTREEITEM hti = NULL;
	hti = HitTest(point,&uFlags);

	if (hti == NULL)
	{
		CTreeCtrl::OnLButtonDown(nFlags, point);
		return ;
	}

	//���ѡ���˸ı�ɼ��Եİ�ť
	if( uFlags & TVHT_ONITEMSTATEICON )
	{ 

		int iImage = GetItemState( hti, TVIS_STATEIMAGEMASK )>>12;
		iImage =(iImage==1)?2:1;
		SetLayerVisible(iImage,hti);
		if(m_pMapControl)
		{
			m_pMapControl->Refresh();
		}

	}
	else
	{
		//���¿�ʼ��ק��ʱ��
		m_dwDragStart = GetTickCount();
	}



	CTreeCtrl::OnLButtonDown(nFlags,point);
}
void CMapTree:: OnBegindrag(NMHDR* pNMHDR, LRESULT* pResult)
{

	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	*pResult = 0;

	//�����������ҷ�����������
	if( (GetTickCount() - m_dwDragStart) < DRAG_DELAY )
		return;

	m_hItemDragS = pNMTreeView->itemNew.hItem;
	m_hItemDragD = NULL;

	//��LayerMap�в���Ҫ�ƶ���Item����ȷ��Item�Ƿ��ж�Ӧ��layer

	if (m_LayerItemMap.end() == m_LayerItemMap.find(m_hItemDragS))
	{
		return;
	}

	Carto::ILayerPtr layerPtr = m_LayerItemMap[m_hItemDragS];
	if (!layerPtr)
	{
		return ;
	}

	//�õ������϶�ʱ��ʾ��ͼ���б�
	m_pDragImage = CreateDragImage( m_hItemDragS );
	if( !m_pDragImage )
		return;

	m_bDragging = true;
	m_pDragImage->BeginDrag ( 0,CPoint(8,8) );
	CPoint  pt = pNMTreeView->ptDrag;
	ClientToScreen( &pt );
	m_pDragImage->DragEnter ( this,pt );  //"this"����ҷ���������ڸô���
	SetCapture();

	m_nScrollTimerID = SetTimer( 2,50,NULL );
}
void CMapTree:: OnMouseMove(UINT nFlags, CPoint point)
{
	HTREEITEM  hItem;
	UINT       flags;

	//���������ж�ʱ���Ƿ����,���������ɾ��,ɾ�����ٶ�ʱ
	if( m_nHoverTimerID )
	{
		KillTimer( m_nHoverTimerID );
		m_nHoverTimerID = 0;
	}
	m_nHoverTimerID = SetTimer( 1,800,NULL );  //��ʱΪ 0.8 �����Զ�չ��
	m_HoverPoint = point;

	if( m_bDragging )
	{
		CPoint  pt = point;
		CImageList::DragMove( pt );

		//��꾭��ʱ������ʾ
		CImageList::DragShowNolock( false );  //������꾭��ʱ�����ѿ��ĺۼ�
		if( (hItem = HitTest(point,&flags)) != NULL )
		{
			SelectDropTarget( hItem );
			m_hItemDragD = hItem;
		}

		CImageList::DragShowNolock( true );

	}

	long button =0;
	if(nFlags&MK_LBUTTON)
	{
		button =1;
	}
	else if(nFlags & MK_RBUTTON)
	{
		button =2;
	}
	else if(nFlags & MK_MBUTTON)
	{
		button =3;
	}
	else
	{
		button =0;
	}
	//�����ƶ��¼�
	m_pTreeCtrl->FireMouseMove(button,0,point.x,point.y);

	CTreeCtrl::OnMouseMove(nFlags,point);
}
void CMapTree:: OnLButtonUp(UINT nFlags, CPoint point)
{
	CTreeCtrl::OnLButtonUp(nFlags,point);

	//�������̧���¼�
	m_pTreeCtrl->FireMouseUp(1,0,point.x,point.y);


	if( m_bDragging )
	{
		/////////TreeCtrl���϶�����
		m_bDragging = FALSE;
		CImageList::DragLeave( this );
		CImageList::EndDrag();
		ReleaseCapture();

		if (m_pDragImage)
		{	
			delete m_pDragImage;
			m_pDragImage=NULL;
		}		

		SelectDropTarget( NULL );
		KillTimer( m_nScrollTimerID );

		if( m_hItemDragS == m_hItemDragD )
		{
			return;
		}


		HTREEITEM  hParentS = GetParentItem(m_hItemDragS) ;
		//��LayerMap�в���Item����ȷ��Ŀ��Item�Ƿ��ж�Ӧ��layer��layer�ĸ��ڵ�

		if (m_hItemDragD != hParentS)
		{		
			HTREEITEM hPreItem = GetNextItem(m_hItemDragS, TVGN_PREVIOUS);
			if (hPreItem == m_hItemDragD)
			{

				return ;
			}

			if (m_LayerItemMap.end() == m_LayerItemMap.find(m_hItemDragD))
			{

				return;
			}

			Carto::ILayerPtr layerPtr =m_LayerItemMap[m_hItemDragD];
			if (!layerPtr)
			{

				return ;
			}

			//ʵ�ֶ�Mapʱ����
			HTREEITEM  hParentD = GetParentItem(m_hItemDragD) ;
			if (m_itemToMapPtr[m_hActMapItem] != m_itemToMapPtr[hParentD])
			{

				return;
			}

		}
		else
		{
			HTREEITEM hPreItem = GetNextItem(m_hItemDragS, TVGN_PREVIOUS);
			if (hPreItem == NULL)
			{

				return ;
			}

			if (m_itemToMapPtr[m_hActMapItem] != m_itemToMapPtr[m_hItemDragD])
			{

				return;
			}
		}

		if (m_itemToMapPtr[m_hActMapItem] != m_itemToMapPtr[hParentS])
		{

			return;
		}


		/*HTREEITEM  htiParent = m_hItemDragD;
		while( (htiParent = GetParentItem(htiParent)) != NULL )
		{
		if( htiParent == m_hItemDragS )
		{
		HTREEITEM  htiNewTemp = CopyBranch( m_hItemDragS,NULL,TVI_LAST );
		HTREEITEM  htiNew = CopyBranch( htiNewTemp,m_hItemDragD,TVI_LAST );
		DeleteItem( htiNewTemp );
		SelectItem( htiNew );

		return;
		}
		}*/

		HTREEITEM htiNewParent = GetParentItem(m_hItemDragD);
		HTREEITEM  htiNew ;
		if (m_hItemDragD != hParentS)
		{
			htiNew = CopyBranch( m_hItemDragS, htiNewParent, m_hItemDragD);
		}
		else
		{
			htiNew = CopyBranch( m_hItemDragS, m_hItemDragD, TVI_FIRST);
		}

		SelectItem( htiNew );


		if ( !ModifyLayersOrder(htiNew, m_hItemDragS, m_hItemDragD) )
		{
			return ;
		}

		DeleteItem( m_hItemDragS );
		SelectItem( htiNew );
		UpdateWindow();


		

		if(m_pMapControl)
		{
			m_pMapControl->Refresh();
		}

		//�϶���ɺ󹤾���״̬�ĸ���
		HTREEITEM hSelected = GetSelectedItem();
		if (m_LayerItemMap.end() != m_LayerItemMap.find(hSelected))
		{
			m_iSelectedItemType = eLayerItem;
		}
		else if (m_itemToMapPtr.end() != m_itemToMapPtr.find(hSelected))
		{
			if (hSelected == m_hActMapItem)
			{
				m_iSelectedItemType = eActiveMapItem;
			}
			else
			{
				m_iSelectedItemType = eMapItem;
			}
		}
		else
		{
			m_iSelectedItemType = eLegendItem;
		}

	}
}

BOOL CMapTree::IsCurItemActivated()
{
	HTREEITEM hSelected = GetSelectedItem();

	while (hSelected != m_hRootItem && hSelected != NULL)
	{
		if (hSelected == m_hActMapItem)
			return TRUE;
		hSelected = GetParentItem(hSelected);
	}
	return FALSE;
}

BOOL CMapTree::ModifyLayersOrder(HTREEITEM  htiNew, HTREEITEM hItemDragS, HTREEITEM hItemDragD)
{

	///////////////////////////////////////////////////////////////��˳��ĸı䱣�浽LayerArray��	
	HTREEITEM  hParentS = GetParentItem(hItemDragS) ;
	Carto::ILayerPtr layerPtrS = m_LayerItemMap[hItemDragS];

	
	Carto::CMap* ptrMap = GetMap();
	if(!ptrMap)
	{
		return FALSE;
	}
	Carto::CLayerArray& LayerArray = ptrMap->GetLayers();

	long lIndexS = LayerArray.FindIndex(layerPtrS);
	if (lIndexS == -1)
	{
		return FALSE;
	}

	if ( m_hItemDragD != hParentS)
	{		
		if (m_LayerItemMap.end() == m_LayerItemMap.find(hItemDragD))
		{
			return FALSE;
		}

		Carto::ILayerPtr layerPtrD = m_LayerItemMap[hItemDragD];

		long lIndexD = LayerArray.FindIndex(layerPtrD);
		if (lIndexD == -1 )
		{
			return FALSE;
		}

		//std::swap(LayerArray[lIndexD] ,LayerArray[lIndexS]);

		if (lIndexS < lIndexD)
		{
			LayerArray.RemoveAt(lIndexS);        
			LayerArray.InsertAt(lIndexD, layerPtrS);
		}
		else
		{        
			LayerArray.RemoveAt(lIndexS);        
			LayerArray.InsertAt(lIndexD + 1, layerPtrS);
		}

	}
	else
	{

		LayerArray.RemoveAt(lIndexS);
		LayerArray.InsertAt( 0, layerPtrS );
	}

	m_LayerItemMap.erase(hItemDragS);
	m_LayerItemMap.insert(std::map<HTREEITEM, Carto::ILayerPtr>::value_type(htiNew, layerPtrS));
	return TRUE;

}


// Description     : �϶�ItemʱӦ�ã�������֧
// Return type     : void
HTREEITEM CMapTree::CopyBranch(HTREEITEM htiBranch, HTREEITEM htiNewParent, HTREEITEM htiAfter)
{
	HTREEITEM  hChild;
	HTREEITEM  hNewItem = CopyItem( htiBranch,htiNewParent,htiAfter );
	hChild = GetChildItem( htiBranch );

	while( hChild != NULL )
	{
		CopyBranch( hChild,hNewItem );
		hChild = GetNextSiblingItem( hChild );
	}

	return  hNewItem;
}

// Function name   : CotSymbolLayerListCtrl::CopyItem
// Description     : �϶�ItemʱӦ�ã�������Ŀ
// Return type     : void
HTREEITEM CMapTree::CopyItem(HTREEITEM hItem, HTREEITEM htiNewParent, HTREEITEM htiAfter)
{
	TV_INSERTSTRUCT  tvstruct;
	HTREEITEM        hNewItem;
	CString          sText;

	//�õ�Դ��Ŀ����Ϣ
	tvstruct.item.hItem = hItem;
	tvstruct.item.mask  = TVIF_CHILDREN|TVIF_HANDLE|TVIF_IMAGE|TVIF_SELECTEDIMAGE;
	GetItem( &tvstruct.item );
	sText = GetItemText( hItem );
	tvstruct.item.cchTextMax = sText.GetLength ();
	tvstruct.item.pszText    = sText.LockBuffer ();

	//����Ŀ���뵽���ʵ�λ��
	tvstruct.hParent         = htiNewParent;
	tvstruct.hInsertAfter    = htiAfter;
	tvstruct.item.mask       = TVIF_IMAGE|TVIF_SELECTEDIMAGE|TVIF_TEXT;
	hNewItem = InsertItem( &tvstruct );
	sText.ReleaseBuffer ();

	//	hNewItem = InsertItem( &tvstruct );
	//���ƿ�����Ŀ���ݺ���Ŀ״̬

	CTreeCtrl::SetItemData( hNewItem,GetItemData(hItem) );
	CTreeCtrl::SetItemState( hNewItem,GetItemState(hItem,TVIS_STATEIMAGEMASK),TVIS_STATEIMAGEMASK);

	return hNewItem;
}

void CMapTree:: OnTimer(UINT nIDEvent)
{
	//������нڵ�
	if( nIDEvent == m_nHoverTimerID )
	{
		KillTimer( m_nHoverTimerID );
		m_nHoverTimerID = 0;
		HTREEITEM  trItem = 0;
		UINT  uFlag = 0;
		trItem = HitTest( m_HoverPoint,&uFlag );
		if( trItem && m_bDragging )
		{
			SelectItem( trItem );
			Expand( trItem,TVE_EXPAND );
		}
	}
	//������ҷ�����еĹ�������
	else if( nIDEvent == m_nScrollTimerID )
	{
		m_TimerTicks++;
		CPoint  pt;
		GetCursorPos( &pt );
		CRect  rect;
		GetClientRect( &rect );
		ClientToScreen( &rect );

		HTREEITEM  hItem = GetFirstVisibleItem();

		if( pt.y < rect.top +10 )
		{
			//���Ϲ���
			int  slowscroll = 6 - (rect.top + 10 - pt.y )/20;
			if( 0 == (m_TimerTicks % ((slowscroll > 0) ? slowscroll : 1)) )
			{
				CImageList::DragShowNolock ( false );
				SendMessage( WM_VSCROLL,SB_LINEUP );
				SelectDropTarget( hItem );
				m_hItemDragD = hItem;
				CImageList::DragShowNolock ( true );
			}
		}
		else if( pt.y > rect.bottom - 10 )
		{
			//���¹���
			int  slowscroll = 6 - (pt.y - rect.bottom + 10)/20;
			if( 0 == (m_TimerTicks % ((slowscroll > 0) ? slowscroll : 1)) )
			{
				CImageList::DragShowNolock ( false );
				SendMessage( WM_VSCROLL,SB_LINEDOWN );
				int  nCount = GetVisibleCount();
				for( int i=0 ; i<nCount-1 ; i++ )
					hItem = GetNextVisibleItem( hItem );
				if( hItem )
					SelectDropTarget( hItem );
				m_hItemDragD = hItem;
				CImageList::DragShowNolock ( true );
			}
		}
	}

	CTreeCtrl::OnTimer(nIDEvent);

}
void CMapTree:: OnEndlabeledit(NMHDR* pNMHDR, LRESULT* pResult)
{

}
void CMapTree:: OnContextMenu(CWnd* pWnd, CPoint point)
{
	CTreeCtrl::OnContextMenu(pWnd,point);
}

//��ѡ��Ľڵ㷢���ı�ʱ
void CMapTree:: OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);

	HTREEITEM hSelected = GetSelectedItem();

	if (m_LayerItemMap.end() != m_LayerItemMap.find(hSelected))
	{
		m_iSelectedItemType = eLayerItem;
	}
	else if (m_itemToMapPtr.end() != m_itemToMapPtr.find(hSelected))
	{
		if (hSelected == m_hActMapItem)
		{
			m_iSelectedItemType = eActiveMapItem;
		}
		else
		{
			m_iSelectedItemType = eMapItem;
		}
	}
	else
	{
		m_iSelectedItemType = eLegendItem;
	}

	*pResult = 0;
}

BOOL CMapTree::SetItemState( HTREEITEM hItem, UINT nState, UINT nStateMask, BOOL bSearch)
{
	CTreeCtrl::SetItemState(hItem,nState,nStateMask);
	return TRUE;
}

//�ı�ͼ��Ŀɼ���
BOOL CMapTree::SetLayerVisible(int nState, HTREEITEM hItem)
{
	if (m_LayerItemMap.end() == m_LayerItemMap.find(hItem))
	{
		return FALSE;
	}
	SetItemState( hItem,INDEXTOSTATEIMAGEMASK(nState),TVIS_STATEIMAGEMASK );
	Carto::ILayerPtr layerPtr =m_LayerItemMap[hItem];
	if (layerPtr)
	{
		if (nState == 2)
		{
			layerPtr->SetVisible(TRUE);
		}
		else
		{
			layerPtr->SetVisible(FALSE);
		}
	}
	else
	{
		return FALSE;
	}
	return TRUE;
}

BOOL CMapTree::AddMap(long lIndex)
{

	//otFramework::IMapCtrl *pMapCtrl =otFramework::IMapCtrl::GetActiveMapCtrl();

	//if(!pMapCtrl)
	//{
	//	return FALSE;
	//}
	//Carto::CMapPtr pMap = pMapCtrl->GetMapByID(lIndex);

	//if(!pMap)
	//{
	//	return FALSE;
	//}
	//std::string csName = pMap->GetName();
	//HTREEITEM hMapItem = InsertItem(csName.c_str(), 0, 0 );
	////SetItemState( hMapItem,INDEXTOSTATEIMAGEMASK(2)|TVIS_BOLD,TVIS_STATEIMAGEMASK|TVIS_BOLD);

	//m_itemToMapPtr.insert(std::map<HTREEITEM,Carto::CMapPtr>::value_type(hMapItem,pMap));

	//SelectItem(hMapItem);
	//m_iSelectedItemType = otFramework::eMapItem;

	return TRUE;
}








void CMapTree::SetSelectedLayer(Carto::ILayerPtr ptrLayer)
{

}

//���ͼ��
void CMapTree::AddLayer(Carto::ILayerPtr layerPtr, BOOL bExpand)
{

	

	if(!m_pMapControl)
	{
		return;
	}

	Carto::CMap *ptrMap =GetMap();
	if (ptrMap == NULL)
	{
		return;
	}


	//�õ���ǰͼ����map�е�λ��
	Carto::CLayerArray layerArray = ptrMap->GetLayers();
	long lLocation = layerArray.FindIndex(layerPtr);
	HTREEITEM hInsertAfter;
	if (lLocation > 0) 
	{	
		Carto::ILayerPtr ptrLayerInsertAfter = layerArray[lLocation - 1];
		hInsertAfter = SearchItemByLayer(ptrLayerInsertAfter);
	}
	else if(lLocation==0)
	{

		hInsertAfter = TVI_FIRST;
	}
	else
	{
		return;
	}


	//ΪRasterLayer��VectorLayer���layer
	AddLayerNode( layerPtr, m_hActMapItem, hInsertAfter,bExpand);

}

//���ͼ��ڵ�
void CMapTree::AddLayerNode(Carto::ILayerPtr layerPtr, HTREEITEM hParent, HTREEITEM hInsertAfter, BOOL bExpand )
{
	Carto::LAYER_TYPE layerType = layerPtr->GetLayerType();
	HTREEITEM hLayerItem = NULL;
	switch(layerType)
	{
	case Carto::FeatureLayer:

		hLayerItem = AddFeatureLayerNode(layerPtr, hParent, hInsertAfter, bExpand);
		break;

	case Carto::RasterLayer :

		hLayerItem = AddRasterLayerNode(layerPtr, hParent, hInsertAfter, bExpand);
		break;

	case Carto::TinLayer :

		hLayerItem = AddTinLayerNode(layerPtr, hParent, hInsertAfter, bExpand);
		break;

	}

	if (bExpand)
	{
		Expand(hParent,TVE_EXPAND);
	}
	if (NULL != hLayerItem)
	{
		SelectItem(hLayerItem);
		m_iSelectedItemType = eLayerItem;
	}
}

HTREEITEM CMapTree::AddFeatureLayerNode(Carto::ILayerPtr layerPtr, HTREEITEM hParent, HTREEITEM hInsertAfter, BOOL bExpand )
{
	if (layerPtr == NULL || hParent == NULL)
	{
		return NULL;
	}

	Carto::IFeatureLayerPtr FeaturelayerPtr = (Carto::IFeatureLayerPtr)layerPtr;
	long enType = FeaturelayerPtr->GetFeatureType();

	int ImageIndex = 3;
	switch(enType)
	{

	case GEOMETRY::geom::GEOS_POINT:
	case GEOMETRY::geom::GEOS_MULTIPOINT:
		ImageIndex = 1;
		break;
	case GEOMETRY::geom::GEOS_LINESTRING:
	case GEOMETRY::geom::GEOS_MULTILINESTRING:
	case GEOMETRY::geom::GEOS_LINEARRING:
		ImageIndex = 2;
		break;
	case GEOMETRY::geom::GEOS_POLYGON:
	case GEOMETRY::geom::GEOS_MULTIPOLYGON:
		ImageIndex = 3;
		break;
	default:
		break;
	}

	HTREEITEM hLayerItem = InsertItem(_bstr_t(layerPtr->GetName().c_str()), 14, 14, hParent, hInsertAfter);

	//��m_LayerItemMap����ÿ��Layer��Ӧ��Item
	typedef std::pair< HTREEITEM , Carto::ILayerPtr>  LayerItem_Pair;	
	m_LayerItemMap.insert(LayerItem_Pair(hLayerItem, layerPtr));
	BOOL bVisible = layerPtr->GetVisible();
	if (bVisible)
	{
		SetItemState( hLayerItem, INDEXTOSTATEIMAGEMASK(2), TVIS_STATEIMAGEMASK );
	}
	else
	{ 
		SetItemState( hLayerItem, INDEXTOSTATEIMAGEMASK(1), TVIS_STATEIMAGEMASK );
	}



	//���ͼ��
	AddFeatureLayerLegend(layerPtr,hLayerItem);

	if(bExpand)
	{
		Expand(hLayerItem,TVE_EXPAND);
	}

	return hLayerItem;
}

HTREEITEM CMapTree::AddRasterLayerNode(Carto::ILayerPtr layerPtr, HTREEITEM hParent, HTREEITEM hInsertAfter, BOOL bExpand )
{
	if (layerPtr == NULL || hParent == NULL)
	{
		return NULL;
	}

	Carto::CRasterLayerPtr RasterLayerlayerPtr = (Carto::CRasterLayerPtr)layerPtr;
	long lband =RasterLayerlayerPtr->BandCount();
	int ImageIndex =(lband<3)?13:11;


	HTREEITEM hLayerItem = InsertItem(_bstr_t(layerPtr->GetName().c_str()), 14, 14, hParent, hInsertAfter);

	//��m_LayerItemMap����ÿ��Layer��Ӧ��Item
	typedef std::pair< HTREEITEM , Carto::ILayerPtr>  LayerItem_Pair;	
	m_LayerItemMap.insert(LayerItem_Pair(hLayerItem, layerPtr));
	BOOL bVisible = layerPtr->GetVisible();
	if (bVisible)
	{
		SetItemState( hLayerItem, INDEXTOSTATEIMAGEMASK(2), TVIS_STATEIMAGEMASK );
	}
	else
	{ 
		SetItemState( hLayerItem, INDEXTOSTATEIMAGEMASK(1), TVIS_STATEIMAGEMASK );
	}



	//���ͼ��


	if(bExpand)
	{
		Expand(hLayerItem,TVE_EXPAND);
	}

	return hLayerItem;
}

HTREEITEM CMapTree::AddTinLayerNode(Carto::ILayerPtr layerPtr, HTREEITEM hParent, HTREEITEM hInsertAfter, BOOL bExpand /* = TRUE */)
{
	return NULL;
}
//ͨ��ͼ���ָ������������еĽڵ�
HTREEITEM CMapTree::SearchItemByLayer(Carto::ILayerPtr ptrLayer)
{
	std::map<HTREEITEM, Carto::ILayerPtr>::const_iterator Layer_Iterator;

	for (Layer_Iterator = m_LayerItemMap.begin(); Layer_Iterator != m_LayerItemMap.end(); Layer_Iterator++)
	{
		if (Layer_Iterator->second == ptrLayer)
		{
			break;
		}

	}

	if (Layer_Iterator == m_LayerItemMap.end())
	{
		return NULL;
	}

	return Layer_Iterator->first;
}

//ɾ����ǰͼ��	
void CMapTree::DeleteLayer(Carto::ILayerPtr ptrLayer)
{
	HTREEITEM hItem = SearchItemByLayer(ptrLayer);
	if (hItem == NULL)
	{
		return;
	}

	HTREEITEM hPatentItem = GetParentItem(hItem);	

	m_LayerItemMap.erase(hItem);

	DeleteItem(hItem);
	//SetParentItemState(hPatentItem);

}

//��ӣ���ʼ��һ����ͼ����
void CMapTree::AddLayerGroup()
{

}

void CMapTree::DeleteAllLayers()
{
	//otFramework::IMapCtrl *pMapCtrl =otFramework::IMapCtrl::GetActiveMapCtrl();
	//if(!pMapCtrl)
	//{
	//	return;
	//}

	//Carto::CMapPtr ptrMap = pMapCtrl->GetActiveMap();
	//if (ptrMap == NULL )
	//{
	//	return;
	//}

	//Carto::CLayerArray& LayerArray = ptrMap->GetLayers();
	//size_t nSize = LayerArray.GetSize();
	//Carto::ILayerPtr ptrLayer = NULL;

	//while (LayerArray.GetSize() != 0)
	//{
	//	ptrLayer = LayerArray.GetAt(LayerArray.GetSize() - 1);
	//	DeleteLayer(ptrLayer);

	//	//�˴���Ҫ��ӻص�
	//	ptrMap->DeleteLayer(ptrLayer);

	//}
	//pMapCtrl->UpdateControl(drawAll);

}

//
BOOL CMapTree::MoveLayerUp()
{
	return FALSE;
}
BOOL CMapTree::MoveLayerDown()
{
	return FALSE;
}
BOOL CMapTree::MoveLayerToTop()
{
	return FALSE;
}
BOOL CMapTree::MoveLayerToBottom()
{
	return FALSE;
}

//
void CMapTree::ModifyItemText(Carto::ILayerPtr ptrLayer, std::string strName)
{

}

//
void CMapTree::Clear()
{
    DeleteAllItems();
	m_LayerItemMap.clear();
	m_itemToMapPtr.clear();

	if(m_imageList.GetImageCount()!=0)
	{
		
	    m_imageList.DeleteImageList();

		//��Ҫָ��imagelist����ɫΪ���ɫ
		m_imageList.Create(16,16,ILC_COLOR24|ILC_MASK,1,1);
		CBitmap bmp;
		bmp.LoadBitmap(IDB_MAP_TREE);
		m_imageList.Add(&bmp,RGB(255,255,255));

		SetImageList (&m_imageList, TVSIL_NORMAL);
	}
	

}




void CMapTree::SetParentItemState(HTREEITEM hParentItem)
{	

	HTREEITEM hItem = GetChildItem(hParentItem);

	if (hItem == NULL)
	{
		while(hParentItem != NULL)
		{
			CTreeCtrl::SetItemState( hParentItem, INDEXTOSTATEIMAGEMASK(1), TVIS_STATEIMAGEMASK );
			hParentItem = GetParentItem(hParentItem);

		}

		return;
	}

	int nState = GetItemState( hItem , TVIS_STATEIMAGEMASK ) >> 12;

	TravelSiblingAndParent( hItem,  nState);

}

void CMapTree::TravelSiblingAndParent(HTREEITEM hItem, int nState)
{
	HTREEITEM hNextSiblingItem,hPrevSiblingItem,hParentItem;

	//���Ҹ��ڵ㣬û�оͽ���
	hParentItem=GetParentItem(hItem);
	if(hParentItem!=NULL)
	{
		int nState1=nState;//���ʼֵ����ֹû���ֵܽڵ�ʱ����

		//���ҵ�ǰ�ڵ�������ֵܽڵ��״̬
		hNextSiblingItem=GetNextSiblingItem(hItem);
		while(hNextSiblingItem!=NULL)
		{
			nState1 = GetItemState( hNextSiblingItem, TVIS_STATEIMAGEMASK ) >> 12;
			if(nState1!=nState && nState1!=0) break;
			else hNextSiblingItem=GetNextSiblingItem(hNextSiblingItem);
		}

		if(nState1==nState)
		{
			//���ҵ�ǰ�ڵ�������ֵܽڵ��״̬
			hPrevSiblingItem=GetPrevSiblingItem(hItem);
			while(hPrevSiblingItem!=NULL)
			{
				nState1 = GetItemState( hPrevSiblingItem, TVIS_STATEIMAGEMASK ) >> 12;
				if(nState1!=nState && nState1!=0) break;
				else hPrevSiblingItem=GetPrevSiblingItem(hPrevSiblingItem);
			}
		}

		if(nState1==nState || nState1==0)
		{
			nState1 = GetItemState( hParentItem, TVIS_STATEIMAGEMASK ) >> 12;
			if(nState1!=0)
			{
				//���״̬һ�£��򸸽ڵ��״̬�뵱ǰ�ڵ��״̬һ��
				CTreeCtrl::SetItemState( hParentItem, INDEXTOSTATEIMAGEMASK(nState), TVIS_STATEIMAGEMASK );
			}
			//�ٵݹ鴦���ڵ���ֵܽڵ���丸�ڵ�
			TravelSiblingAndParent(hParentItem,nState);
		}
		else
		{
			//״̬��һ�£���ǰ�ڵ�ĸ��ڵ㡢���ڵ�ĸ��ڵ㡭��״̬��Ϊ����̬
			hParentItem=GetParentItem(hItem);
			while(hParentItem!=NULL)
			{
				nState1 = GetItemState( hParentItem, TVIS_STATEIMAGEMASK ) >> 12;
				if(nState1!=0)
				{
					CTreeCtrl::SetItemState( hParentItem, INDEXTOSTATEIMAGEMASK(2), TVIS_STATEIMAGEMASK );
				}
				hParentItem=GetParentItem(hParentItem);
			}
		}
	}	
}

HTREEITEM CMapTree::SearchItemByMap(Carto::CMap* pMap)
{

	for (Map_Iterator = m_itemToMapPtr.begin(); Map_Iterator != m_itemToMapPtr.end(); Map_Iterator++)
	{
		if (Map_Iterator->second == pMap)
		{
			break;
		}

	}

	if (Map_Iterator == m_itemToMapPtr.end())
	{
		return NULL;
	}

	return Map_Iterator->first;
}

void* CMapTree::GetSelectedItemData()
{
	HTREEITEM item =GetSelectedItem();
	if(item!=NULL)
	{
		return (void*)GetItemData(item);
	}
	return NULL;
}

void CMapTree::serialization(SYSTEM::IArchive &ar)
{

}

/***********************************************************************************************************
* ������ͼ��������صĺ���
************************************************************************************************************/

void CMapTree::CreateSymbolBmp(Display::ISymbolPtr pSymbol,CBitmap &bmp)
{ 
	CDC *pDC,memDC;
	pDC = GetDC();
	memDC.CreateCompatibleDC(pDC);


	bmp.CreateCompatibleBitmap( pDC,16,16); //�������ڴ�DC(���ǵ�ɫ)���ô���DC
	CBitmap *pOld = (CBitmap *)memDC.SelectObject(&bmp);

	//����ͼƬ�ı���
	memDC.FillSolidRect(0,0,16,16,/*GetSysColor(COLOR_WINDOW)*/RGB(255,255,255));

	Display::CDC *pDrawDC =new Display::CDC();
	pDrawDC->SetDC((long)memDC.GetSafeHdc(),16,16);

	DIS_RECT *pDrawRect =NULL;
	CreateDisplayRect(pDrawRect);

	pDrawRect->left=0;
	pDrawRect->top =0;
	pDrawRect->right =16;
	pDrawRect->bottom =16;

	pSymbol->SelectDC(pDrawDC);
	pSymbol->SetReadyDraw();
	//ͨ�����Ż���ͼ��
	pSymbol->DrawLegend(pDrawRect,0);

	pSymbol->ClearDC();

	FreeDisplayObj(pDrawRect);

	memDC.SelectObject(pOld);
	delete pDrawDC;
	ReleaseDC(pDC);
}

void CMapTree::AddFeatureLayerLegend(Carto::ILayerPtr ptrLayer, HTREEITEM hParent)
{
	Carto::CFeatureLayer *pLayer =(Carto::CFeatureLayer*)(ptrLayer.get());

	//���Render������
	Carto::IRenderPtr pRender =pLayer->GetFeatureRender();
	Carto::RENDER_TYPE rendertype =pRender->GetRenderType();

	
	Carto::CLegendInfoPtr pLegendInfo =pRender->GetLegendInfo();
	if(pLegendInfo)
	{
		long GroupCount =pLegendInfo->LegendGroupCount();

		CString Heading;
		int lStartIndex;
		std::string strLable;
		std::string strValue;

		CBitmap bmp;
		CImageList *pImgList = GetImageList(TVSIL_NORMAL);
		Carto::LegendItem item;

		for(long i=0;i<GroupCount;i++)
		{
			Carto::CLegendGroupPtr pGroup =pLegendInfo->GetLegendGroup(i);

			Heading =pGroup->GetHeading().c_str();
			if(!Heading.IsEmpty())
			{
				//���Heading
				InsertItem(Heading,14,14,hParent,TVI_LAST);
			}

			long Itemnum =pGroup->GetItemCount();
			for(long j=0;j<Itemnum;j++)
			{
				item =pGroup->GetItem(j);

				CreateSymbolBmp(item.pSymbol,bmp);


				lStartIndex = pImgList->GetImageCount();
				pImgList->Add(&bmp,RGB(255,255,255));


				//����ͼ���ڵ�
				InsertItem(_bstr_t(item.strLabel.c_str()),lStartIndex,lStartIndex,hParent,TVI_LAST);

				bmp.DeleteObject();

			}
		}
	}
}



void CMapTree::UpdateLayerNode(Carto::ILayerPtr layerPtr, HTREEITEM LayerItem)
{
	SetItemText(LayerItem,_bstr_t(layerPtr->GetName().c_str()));

	BOOL bVisible = layerPtr->GetVisible();
	if (bVisible)
	{
		SetItemState( LayerItem, INDEXTOSTATEIMAGEMASK(2), TVIS_STATEIMAGEMASK );
	}
	else
	{ 
		SetItemState( LayerItem, INDEXTOSTATEIMAGEMASK(1), TVIS_STATEIMAGEMASK );
	}

	//ɾ��ͼ��
	HTREEITEM hCurrent = GetNextItem(LayerItem, TVGN_CHILD);
	HTREEITEM hnext;
	while (hCurrent != NULL) 
	{

		hnext = GetNextItem(hCurrent, TVGN_NEXT);
		DeleteItem(hCurrent);
		hCurrent =hnext;

	}

	Carto::LAYER_TYPE layerType = layerPtr->GetLayerType();

	switch(layerType)
	{
	case Carto::FeatureLayer:

		//���ͼ��
		AddFeatureLayerLegend(layerPtr,LayerItem);
		break;

	case Carto::RasterLayer :


		break;

	case Carto::TinLayer :


		break;

	}

}

Carto::CMap* CMapTree::GetMap()
{
	if(!m_pMapControl)
	{
		return NULL;
	}
	IOriginDataPtr pData;
	

	IGeoMap *pMap =m_pMapControl->GetMap();

	pMap->QueryInterface(__uuidof(IOriginData),(void**)&pData);
	long p;
	pData->get_OriginData(&p);

	pMap->Release();

	return (*((Carto::CMapPtr*)p)).get();


}

void CMapTree::Refresh()
{
	Clear();
	Carto::CMap *pMap =GetMap();
	//��ӵ�ͼ
	if(pMap)
	{
		std::string csName = pMap->GetName();
		HTREEITEM hMapItem = InsertItem(_bstr_t(csName.c_str()), 0, 0 );

		m_itemToMapPtr.insert(std::map<HTREEITEM,Carto::CMap*>::value_type(hMapItem,pMap));
        
		SelectItem(hMapItem);

		//��ͼ������Ϊ����
		CTreeCtrl::SetItemState( hMapItem, TVIS_BOLD, TVIS_BOLD);

		m_hActMapItem = hMapItem;
		m_iSelectedItemType = eMapItem;

		Carto::CLayerArray &layers =pMap->GetLayers();

		//���ÿ��ͼ���ͼ��
		for(int i=0;i<layers.GetSize();i++)
		{
			AddLayer(layers.GetAt(i));
		}
	}


}



void CMapTree::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	//����˫���¼�
	m_pTreeCtrl->FireDoubleClick(1,0,point.x,point.y);

	CTreeCtrl::OnLButtonDblClk(nFlags, point);
}

void CMapTree::OnRButtonUp(UINT nFlags, CPoint point)
{
	//�������̧���¼�
	m_pTreeCtrl->FireMouseUp(2,0,point.x,point.y);

	CTreeCtrl::OnRButtonUp(nFlags, point);
}


void CMapTree::OnRemoveLayer()
{
	HTREEITEM item =CTreeCtrl::GetSelectedItem();
	if(!item)
	{
		return;
	}
	
	HTREEITEM layerItem,mapItem;
	if(m_iSelectedItemType==eLayerItem)
	{
		layerItem =item;
	}
	else if(m_iSelectedItemType ==eLegendItem)
	{
		layerItem =GetParentItem(item);
	}
	mapItem =GetParentItem(layerItem);
	std::map  <HTREEITEM, Carto::ILayerPtr>::iterator layerIter;
	//����ͼ��
	layerIter =m_LayerItemMap.find(layerItem);
	if(layerIter ==m_LayerItemMap.end())
	{
		return;
	}
	//ͼ�����ڵĵ�ͼ
	std::map<HTREEITEM, Carto::CMap*>::iterator mapIter;
	mapIter = m_itemToMapPtr.find(mapItem);
	if(mapIter ==m_itemToMapPtr.end())
	{
		return;
	}

	Carto::CMap* pMap = mapIter->second;
	if(!pMap)
	{
		return;
	}

	pMap->DeleteLayer(layerIter->second);

	CTreeCtrl::DeleteItem(layerItem);

	m_LayerItemMap.erase(layerIter);

	m_pMapControl->Refresh();
}

void CMapTree::OnRemoveAllLayer()
{
	DeleteAllLayers();
}

void CMapTree::OnLayerProp()
{
	HTREEITEM item =CTreeCtrl::GetSelectedItem();
	if(!item)
	{
		return;
	}
	
	HTREEITEM layerItem,mapItem;
	if(m_iSelectedItemType==eLayerItem)
	{
		layerItem =item;
	}
	else if(m_iSelectedItemType ==eLegendItem)
	{
		layerItem =GetParentItem(item);
	}
	std::map  <HTREEITEM, Carto::ILayerPtr>::iterator layerIter;
	//����ͼ��
	layerIter =m_LayerItemMap.find(layerItem);
	if(layerIter ==m_LayerItemMap.end())
	{
		return;
	}
	
	CMapTreeCallback callback;
	callback.SetMapCtrl(m_pMapControl);
	if(otComUI::CotLayerProp::ShowLayerProp(layerIter->second,&callback)==IDOK)
	{
		m_pMapControl->Refresh();
		UpdateLayerNode(layerIter->second,layerItem);
	}



}