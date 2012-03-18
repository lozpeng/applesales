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

	//需要指定imagelist的颜色为真彩色
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

	//触发单击事件
	m_pTreeCtrl->FireMouseDown(2,0,point.x,point.y);

    //是否显示上下文菜单
	if(!m_bShowMenu)
	{
		return;
	}
	HTREEITEM hHit = NULL;
	UINT flag;

	hHit = HitTest(point, &flag);

	//判断是否在节点上点击右键
	if(hHit && (flag & TVHT_ONITEM))
	{
		SelectItem(hHit);
	}
	else
	{
		return;
	}

	CMenu menu;

	//如果选中图层节点
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

//更新菜单项的状态
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
	//	else if(nID == ID_ACTIVE_MAP)//激活地图
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
	//	else if(nID == ID_DELETE_MAP) //删除地图
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
	//	else if(nID == ID_MAP_PROP)  //地图属性
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
	//	else if(nID == ID_REMOVE_LAYER) //删除图层
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
	//	else if(nID == ID_REMOVE_ALL_LAYER) //删除所有图层
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
	//触发单击事件
	m_pTreeCtrl->FireMouseDown(1,0,point.x,point.y);

	UINT uFlags=0;
	HTREEITEM hti = NULL;
	hti = HitTest(point,&uFlags);

	if (hti == NULL)
	{
		CTreeCtrl::OnLButtonDown(nFlags, point);
		return ;
	}

	//如果选择了改变可见性的按钮
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
		//记下开始拖拽的时间
		m_dwDragStart = GetTickCount();
	}



	CTreeCtrl::OnLButtonDown(nFlags,point);
}
void CMapTree:: OnBegindrag(NMHDR* pNMHDR, LRESULT* pResult)
{

	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	*pResult = 0;

	//如果是无意拖曳，则放弃操作
	if( (GetTickCount() - m_dwDragStart) < DRAG_DELAY )
		return;

	m_hItemDragS = pNMTreeView->itemNew.hItem;
	m_hItemDragD = NULL;

	//从LayerMap中查找要移动的Item，以确定Item是否有对应的layer

	if (m_LayerItemMap.end() == m_LayerItemMap.find(m_hItemDragS))
	{
		return;
	}

	Carto::ILayerPtr layerPtr = m_LayerItemMap[m_hItemDragS];
	if (!layerPtr)
	{
		return ;
	}

	//得到用于拖动时显示的图象列表
	m_pDragImage = CreateDragImage( m_hItemDragS );
	if( !m_pDragImage )
		return;

	m_bDragging = true;
	m_pDragImage->BeginDrag ( 0,CPoint(8,8) );
	CPoint  pt = pNMTreeView->ptDrag;
	ClientToScreen( &pt );
	m_pDragImage->DragEnter ( this,pt );  //"this"将拖曳动作限制在该窗口
	SetCapture();

	m_nScrollTimerID = SetTimer( 2,50,NULL );
}
void CMapTree:: OnMouseMove(UINT nFlags, CPoint point)
{
	HTREEITEM  hItem;
	UINT       flags;

	//检测鼠标敏感定时器是否存在,如果存在则删除,删除后再定时
	if( m_nHoverTimerID )
	{
		KillTimer( m_nHoverTimerID );
		m_nHoverTimerID = 0;
	}
	m_nHoverTimerID = SetTimer( 1,800,NULL );  //定时为 0.8 秒则自动展开
	m_HoverPoint = point;

	if( m_bDragging )
	{
		CPoint  pt = point;
		CImageList::DragMove( pt );

		//鼠标经过时高亮显示
		CImageList::DragShowNolock( false );  //避免鼠标经过时留下难看的痕迹
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
	//触发移动事件
	m_pTreeCtrl->FireMouseMove(button,0,point.x,point.y);

	CTreeCtrl::OnMouseMove(nFlags,point);
}
void CMapTree:: OnLButtonUp(UINT nFlags, CPoint point)
{
	CTreeCtrl::OnLButtonUp(nFlags,point);

	//触发鼠标抬起事件
	m_pTreeCtrl->FireMouseUp(1,0,point.x,point.y);


	if( m_bDragging )
	{
		/////////TreeCtrl的拖动过程
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
		//从LayerMap中查找Item，以确定目的Item是否有对应的layer或layer的父节点

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

			//实现多Map时加入
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

		//拖动完成后工具栏状态的更新
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

	///////////////////////////////////////////////////////////////把顺序的改变保存到LayerArray中	
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


// Description     : 拖动Item时应用，拷贝分支
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
// Description     : 拖动Item时应用，拷贝条目
// Return type     : void
HTREEITEM CMapTree::CopyItem(HTREEITEM hItem, HTREEITEM htiNewParent, HTREEITEM htiAfter)
{
	TV_INSERTSTRUCT  tvstruct;
	HTREEITEM        hNewItem;
	CString          sText;

	//得到源条目的信息
	tvstruct.item.hItem = hItem;
	tvstruct.item.mask  = TVIF_CHILDREN|TVIF_HANDLE|TVIF_IMAGE|TVIF_SELECTEDIMAGE;
	GetItem( &tvstruct.item );
	sText = GetItemText( hItem );
	tvstruct.item.cchTextMax = sText.GetLength ();
	tvstruct.item.pszText    = sText.LockBuffer ();

	//将条目插入到合适的位置
	tvstruct.hParent         = htiNewParent;
	tvstruct.hInsertAfter    = htiAfter;
	tvstruct.item.mask       = TVIF_IMAGE|TVIF_SELECTEDIMAGE|TVIF_TEXT;
	hNewItem = InsertItem( &tvstruct );
	sText.ReleaseBuffer ();

	//	hNewItem = InsertItem( &tvstruct );
	//限制拷贝条目数据和条目状态

	CTreeCtrl::SetItemData( hNewItem,GetItemData(hItem) );
	CTreeCtrl::SetItemState( hNewItem,GetItemState(hItem,TVIS_STATEIMAGEMASK),TVIS_STATEIMAGEMASK);

	return hNewItem;
}

void CMapTree:: OnTimer(UINT nIDEvent)
{
	//鼠标敏感节点
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
	//处理拖曳过程中的滚动问题
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
			//向上滚动
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
			//向下滚动
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

//当选择的节点发生改变时
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

//改变图层的可见性
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

//添加图层
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


	//得到当前图层在map中的位置
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


	//为RasterLayer和VectorLayer添加layer
	AddLayerNode( layerPtr, m_hActMapItem, hInsertAfter,bExpand);

}

//添加图层节点
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

	//用m_LayerItemMap保存每个Layer对应得Item
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



	//添加图例
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

	//用m_LayerItemMap保存每个Layer对应得Item
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



	//添加图例


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
//通过图层的指针查找它在树中的节点
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

//删除当前图层	
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

//添加（初始化一个）图层组
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

	//	//此处需要添加回调
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

		//需要指定imagelist的颜色为真彩色
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

	//查找父节点，没有就结束
	hParentItem=GetParentItem(hItem);
	if(hParentItem!=NULL)
	{
		int nState1=nState;//设初始值，防止没有兄弟节点时出错

		//查找当前节点下面的兄弟节点的状态
		hNextSiblingItem=GetNextSiblingItem(hItem);
		while(hNextSiblingItem!=NULL)
		{
			nState1 = GetItemState( hNextSiblingItem, TVIS_STATEIMAGEMASK ) >> 12;
			if(nState1!=nState && nState1!=0) break;
			else hNextSiblingItem=GetNextSiblingItem(hNextSiblingItem);
		}

		if(nState1==nState)
		{
			//查找当前节点上面的兄弟节点的状态
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
				//如果状态一致，则父节点的状态与当前节点的状态一致
				CTreeCtrl::SetItemState( hParentItem, INDEXTOSTATEIMAGEMASK(nState), TVIS_STATEIMAGEMASK );
			}
			//再递归处理父节点的兄弟节点和其父节点
			TravelSiblingAndParent(hParentItem,nState);
		}
		else
		{
			//状态不一致，则当前节点的父节点、父节点的父节点……状态均为第三态
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
* 以下是图例绘制相关的函数
************************************************************************************************************/

void CMapTree::CreateSymbolBmp(Display::ISymbolPtr pSymbol,CBitmap &bmp)
{ 
	CDC *pDC,memDC;
	pDC = GetDC();
	memDC.CreateCompatibleDC(pDC);


	bmp.CreateCompatibleBitmap( pDC,16,16); //不能用内存DC(总是单色)，用窗体DC
	CBitmap *pOld = (CBitmap *)memDC.SelectObject(&bmp);

	//绘制图片的背景
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
	//通过符号绘制图例
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

	//获得Render的类型
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
				//添加Heading
				InsertItem(Heading,14,14,hParent,TVI_LAST);
			}

			long Itemnum =pGroup->GetItemCount();
			for(long j=0;j<Itemnum;j++)
			{
				item =pGroup->GetItem(j);

				CreateSymbolBmp(item.pSymbol,bmp);


				lStartIndex = pImgList->GetImageCount();
				pImgList->Add(&bmp,RGB(255,255,255));


				//加入图例节点
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

	//删除图例
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

		//添加图例
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
	//添加地图
	if(pMap)
	{
		std::string csName = pMap->GetName();
		HTREEITEM hMapItem = InsertItem(_bstr_t(csName.c_str()), 0, 0 );

		m_itemToMapPtr.insert(std::map<HTREEITEM,Carto::CMap*>::value_type(hMapItem,pMap));
        
		SelectItem(hMapItem);

		//地图名称设为黑体
		CTreeCtrl::SetItemState( hMapItem, TVIS_BOLD, TVIS_BOLD);

		m_hActMapItem = hMapItem;
		m_iSelectedItemType = eMapItem;

		Carto::CLayerArray &layers =pMap->GetLayers();

		//添加每个图层的图例
		for(int i=0;i<layers.GetSize();i++)
		{
			AddLayer(layers.GetAt(i));
		}
	}


}



void CMapTree::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	//触发双击事件
	m_pTreeCtrl->FireDoubleClick(1,0,point.x,point.y);

	CTreeCtrl::OnLButtonDblClk(nFlags, point);
}

void CMapTree::OnRButtonUp(UINT nFlags, CPoint point)
{
	//触发鼠标抬起事件
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
	//查找图层
	layerIter =m_LayerItemMap.find(layerItem);
	if(layerIter ==m_LayerItemMap.end())
	{
		return;
	}
	//图层所在的地图
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
	//查找图层
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