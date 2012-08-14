// MaptreeCtrl.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MaptreeCtrl.h"
#include "IMapCtrl.h"
#include "IDocument.h"
#include "FeatureLayer.h"
#include "RasterLayer.h"
#include "SimpleRender.h"
#include "Resource.h"
#include <geometry/geom/Geometry.h>
#include "DllResource.h"
#include "LayerPropSheet.h"
#include "DlgObjExport.h"

#define   DRAG_DELAY   60

namespace Control
{

typedef std::pair< HTREEITEM , Carto::CMapPtr> MapItem_Pair;	
std::map<HTREEITEM, Carto::CMapPtr>::const_iterator Map_Iterator;

IMPLEMENT_DYNAMIC(CMaptreeCtrl, CTreeCtrl)

CMaptreeCtrl::CMaptreeCtrl()
{
	m_bDragging = false;
	m_pDragImage = NULL;
	m_hActMapItem = NULL;
	m_nHoverTimerID =m_nScrollTimerID =0;
}

CMaptreeCtrl::~CMaptreeCtrl()
{
	if (m_pDragImage)
	{	
		delete m_pDragImage;
		m_pDragImage = NULL;
	}	
}

BEGIN_MESSAGE_MAP(CMaptreeCtrl, CTreeCtrl)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_NCLBUTTONDOWN()
	ON_NOTIFY_REFLECT(NM_CLICK, &CMaptreeCtrl::OnNMClick)
	ON_WM_RBUTTONDOWN()

	ON_NOTIFY_REFLECT(TVN_BEGINDRAG, OnBegindrag)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_TIMER()
	ON_NOTIFY_REFLECT(TVN_ENDLABELEDIT, OnEndlabeledit)
	ON_WM_CONTEXTMENU()
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, &CMaptreeCtrl::OnTvnSelchanged)

	ON_COMMAND(ID_REMOVE_LAYER, &CMaptreeCtrl::OnRemoveLayer)
	ON_COMMAND(ID_LAYER_PROP, &CMaptreeCtrl::OnLayerProp)
	ON_COMMAND(ID_ZOOMTO_LAYER, &CMaptreeCtrl::OnZoomToLayer)
	ON_COMMAND(ID_OBJ_EXPORT, &CMaptreeCtrl::OnObjExport)
	ON_COMMAND(ID_OPEN_ATTRIBUTETABLE, &CMaptreeCtrl::OnOpenAttribute)

END_MESSAGE_MAP()

int CMaptreeCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CTreeCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;

	CDllResource dllRes;

	//��Ҫָ��imagelist����ɫΪ���ɫ
	m_imageList.Create(16,16,ILC_COLOR24|ILC_MASK,1,1);
	CBitmap bmp;
	bmp.LoadBitmap(IDB_MAP_TREE);
	m_imageList.Add(&bmp,RGB(255,255,255));

	
	SetImageList (&m_imageList, TVSIL_NORMAL);

	m_imgState.Create ( IDB_MAPTREE_STATE, 16, 1, RGB(255,255,255) );
	SetImageList (&m_imgState,TVSIL_STATE);
	return 0;
} 
void CMaptreeCtrl:: OnSize(UINT nType, int cx, int cy)
{
    CTreeCtrl::OnSize(nType, cx, cy);
}

void CMaptreeCtrl:: OnNcLButtonDown(UINT nHitTest, CPoint point)
{

}
void CMaptreeCtrl:: OnNMClick(NMHDR *pNMHDR, LRESULT *pResult)
{

}
void CMaptreeCtrl:: OnRButtonDown(UINT nFlags, CPoint point)
{
    CDllResource hdll;
	SetFocus();

	HTREEITEM hHit = NULL;
	UINT flag;

	hHit = HitTest(point, &flag);
	if(hHit && (flag & TVHT_ONITEM))
		SelectItem(hHit);

	
	CMenu menu;
	if(m_iSelectedItemType==Framework::eLayerItem)
	{
		if(!menu.LoadMenu(IDR_LAYER_MENU))
			return;

		CMenu* pPopup = menu.GetSubMenu(0);

		//UpdateMenuStatus(pPopup);

		CPoint srnPoint = point;
		ClientToScreen(&srnPoint);
		pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, srnPoint.x, srnPoint.y, dynamic_cast<CWnd*>(this));
	}

	
	
}

//���²˵����״̬
void CMaptreeCtrl::UpdateMenuStatus(CMenu *pMenu)
{
    if(!pMenu)
	{
		return;
	}
 //   HTREEITEM item =GetSelectedItem();
	//long lNumItems;
	//UINT nID = 0;
	//BOOL bIsEnable;
 //   lNumItems =pMenu->GetMenuItemCount();
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
	//		if(m_iSelectedItemType==Framework::eMapItem )
	//		{
 //               bIsEnable =TRUE;
	//		}
	//		else
	//		{
	//			bIsEnable = FALSE;
	//		}
	//	}
	//	else if(nID == ID_DELETE_MAP) //ɾ����ͼ
	//	{
	//		if(m_iSelectedItemType==Framework::eMapItem/* || m_iSelectedItemType==Framework::eActiveMapItem*/)
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
	//		if(m_iSelectedItemType==Framework::eMapItem || m_iSelectedItemType==Framework::eActiveMapItem)
	//		{
	//			bIsEnable =TRUE;
	//		}
	//		else
	//		{
	//			bIsEnable = FALSE;
	//		}
	//	}
	//	else if(nID == ID_LAYER_ACTIVE)  //����ͼ��
	//	{	
	//		BOOL bEnable = FALSE;
	//		bEnable = IsCurItemActivated();
	//		if (bEnable)
	//		{
	//			if(m_iSelectedItemType==Framework::eLayerItem || m_iSelectedItemType==Framework::eLegendItem)				
	//				bIsEnable =TRUE;				
	//			else				
	//				bIsEnable = FALSE;
	//		}
	//		else
	//			bIsEnable = FALSE;
	//		
	//	}
	//	else if(nID == ID_REMOVE_LAYER) //ɾ��ͼ��
	//	{
	//		BOOL bEnable = FALSE;
	//		bEnable = IsCurItemActivated();
	//		if (bEnable)
	//		{
	//			if(m_iSelectedItemType==Framework::eLayerItem || m_iSelectedItemType==Framework::eLegendItem)			
	//				bIsEnable =TRUE;			
	//			else			
	//				bIsEnable = FALSE;			
	//		}
	//		else
	//			bIsEnable = FALSE;
	//	}
	//	else if(nID == ID_REMOVE_ALL_LAYER) //ɾ������ͼ��
	//	{

	//		BOOL bEnable = FALSE;

	//		bEnable = IsCurItemActivated();

	//		BOOL bHasLayer = FALSE;

	//		Framework::IMapCtrl *pMapCtrl =Framework::IMapCtrl::GetActiveMapCtrl();
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

	//		if((m_iSelectedItemType == Framework::eMapItem && bEnable) || (m_iSelectedItemType == Framework::eActiveMapItem) && bHasLayer)
	//		{
	//			bIsEnable =TRUE;
	//		}
	//		else
	//		{
	//			bIsEnable =FALSE;
	//		}
	//	}
	//	else if(nID == ID_ZOOM_TO_CURRENT_LAYER) //ɾ��ͼ��
	//	{
	//		BOOL bEnable = FALSE;
	//		bEnable = IsCurItemActivated();
	//		if (bEnable)
	//		{
	//			if(m_iSelectedItemType==Framework::eLayerItem || m_iSelectedItemType==Framework::eLegendItem)
	//				bIsEnable =TRUE;		
	//			else			
	//				bIsEnable = FALSE;
	//		}
	//		else
	//			bIsEnable = FALSE;
	//	}
	//	else if(nID == ID_OPEN_ATTRIBUTETABLE)  //�����Ա�
	//	{
	//		BOOL bEnable = FALSE;
	//		bEnable = IsCurItemActivated();
	//		if (bEnable)
	//		{
	//			if(m_iSelectedItemType==Framework::eLayerItem || m_iSelectedItemType==Framework::eLegendItem)
	//				bIsEnable =TRUE;				
	//			else				
	//				bIsEnable = FALSE;
	//		}
	//		else
	//			bIsEnable = FALSE;
	//	}
	//	else if( nID == ID_LAYER_PROP ) //ͼ������
	//	{
	//		BOOL bEnable = FALSE;
	//		bEnable = IsCurItemActivated();
	//		if (bEnable)
	//		{
	//			if(m_iSelectedItemType==Framework::eLayerItem || m_iSelectedItemType==Framework::eLegendItem)
	//				bIsEnable =TRUE;				
	//			else				
	//				bIsEnable = FALSE;
	//		}
	//		else
	//			bIsEnable = FALSE;
	//	}
	//	

	//	if(bIsEnable)
	//		pMenu->EnableMenuItem(nID,MF_BYCOMMAND|MF_ENABLED);
	//	else
	//		pMenu->EnableMenuItem(nID,MF_BYCOMMAND|MF_DISABLED|MF_GRAYED);
	//}
}


void CMaptreeCtrl:: OnLButtonDown(UINT nFlags, CPoint point)
{
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
		Framework::IMapCtrl *pMapCtrl =Framework::IMapCtrl::GetActiveMapCtrl();

		if(pMapCtrl)
		{
			pMapCtrl->UpdateControl(drawAll);
		}

	}
	else
	{
		//���¿�ʼ��ק��ʱ��
        m_dwDragStart = GetTickCount();
	}

	

	CTreeCtrl::OnLButtonDown(nFlags,point);
}
void CMaptreeCtrl:: OnBegindrag(NMHDR* pNMHDR, LRESULT* pResult)
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
void CMaptreeCtrl:: OnMouseMove(UINT nFlags, CPoint point)
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

	CTreeCtrl::OnMouseMove(nFlags,point);
}
void CMaptreeCtrl:: OnLButtonUp(UINT nFlags, CPoint point)
{
	CTreeCtrl::OnLButtonUp(nFlags,point);
	

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

		
		Framework::IMapCtrl *pMapCtrl =Framework::IMapCtrl::GetActiveMapCtrl();

		if(pMapCtrl)
		{
			pMapCtrl->UpdateControl(drawAll);
		}

		//�϶���ɺ󹤾���״̬�ĸ���
		HTREEITEM hSelected = GetSelectedItem();
		if (m_LayerItemMap.end() != m_LayerItemMap.find(hSelected))
		{
			m_iSelectedItemType = Framework::eLayerItem;
		}
		else if (m_itemToMapPtr.end() != m_itemToMapPtr.find(hSelected))
		{
			if (hSelected == m_hActMapItem)
			{
				m_iSelectedItemType = Framework::eActiveMapItem;
			}
			else
			{
				m_iSelectedItemType = Framework::eMapItem;
			}
		}
		else
		{
			m_iSelectedItemType = Framework::eLegendItem;
		}

	}
}

BOOL CMaptreeCtrl::IsCurItemActivated()
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

BOOL CMaptreeCtrl::ModifyLayersOrder(HTREEITEM  htiNew, HTREEITEM hItemDragS, HTREEITEM hItemDragD)
{

	///////////////////////////////////////////////////////////////��˳��ĸı䱣�浽LayerArray��	
	HTREEITEM  hParentS = GetParentItem(hItemDragS) ;
	Carto::ILayerPtr layerPtrS = m_LayerItemMap[hItemDragS];

	Framework::IMapCtrl *pMapCtrl =Framework::IMapCtrl::GetActiveMapCtrl();
	Carto::CMapPtr ptrMap = pMapCtrl->GetMap();
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
			if(lIndexD>0)
			{
				LayerArray.InsertAt(lIndexD-1, layerPtrS);
			}
			else
			{
				LayerArray.InsertAt(0, layerPtrS);
			}
			//LayerArray.InsertAt(lIndexD, layerPtrS);
		}
		else
		{        
			LayerArray.RemoveAt(lIndexS);
			if(lIndexD>0)
			{
               LayerArray.InsertAt(lIndexD, layerPtrS);
			}
			else
			{
                LayerArray.InsertAt(0, layerPtrS);
			}
			
		}

	}
	else
	{
		
		LayerArray.RemoveAt(lIndexS);
		//�ӵ����ϲ�
		LayerArray.Add( layerPtrS );
	}

	m_LayerItemMap.erase(hItemDragS);
	m_LayerItemMap.insert(std::map<HTREEITEM, Carto::ILayerPtr>::value_type(htiNew, layerPtrS));
	return TRUE;

}


// Description     : �϶�ItemʱӦ�ã�������֧
// Return type     : void
HTREEITEM CMaptreeCtrl::CopyBranch(HTREEITEM htiBranch, HTREEITEM htiNewParent, HTREEITEM htiAfter)
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
HTREEITEM CMaptreeCtrl::CopyItem(HTREEITEM hItem, HTREEITEM htiNewParent, HTREEITEM htiAfter)
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

void CMaptreeCtrl:: OnTimer(UINT nIDEvent)
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
void CMaptreeCtrl:: OnEndlabeledit(NMHDR* pNMHDR, LRESULT* pResult)
{

}
void CMaptreeCtrl:: OnContextMenu(CWnd* pWnd, CPoint point)
{
	//CTreeCtrl::OnContextMenu(pWnd,point);
}

//��ѡ��Ľڵ㷢���ı�ʱ
void CMaptreeCtrl:: OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	
	HTREEITEM hSelected = GetSelectedItem();

	if (m_LayerItemMap.end() != m_LayerItemMap.find(hSelected))
	{
		m_iSelectedItemType = Framework::eLayerItem;
	}
	else if (m_itemToMapPtr.end() != m_itemToMapPtr.find(hSelected))
	{
		if (hSelected == m_hActMapItem)
		{
			m_iSelectedItemType = Framework::eActiveMapItem;
		}
		else
		{
			m_iSelectedItemType = Framework::eMapItem;
		}
	}
	else
	{
		m_iSelectedItemType = Framework::eLegendItem;
	}
	
	*pResult = 0;
}

BOOL CMaptreeCtrl::SetItemState( HTREEITEM hItem, UINT nState, UINT nStateMask, BOOL bSearch)
{
	CTreeCtrl::SetItemState(hItem,nState,nStateMask);
    return TRUE;
}

//�ı�ͼ��Ŀɼ���
BOOL CMaptreeCtrl::SetLayerVisible(int nState, HTREEITEM hItem)
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

BOOL CMaptreeCtrl::AddMap(long lIndex)
{

	//Framework::IMapCtrl *pMapCtrl =Framework::IMapCtrl::GetActiveMapCtrl();

	//if(!pMapCtrl)
	//{
	//	return FALSE;
	//}
	//Carto::CMapPtr pMap = pMapCtrl->GetMapByID(lIndex);
	//
	//if(!pMap)
	//{
	//	return FALSE;
	//}
	//std::string csName = pMap->GetName();
	//HTREEITEM hMapItem = InsertItem(csName.c_str(), 0, 0 );
	////SetItemState( hMapItem,INDEXTOSTATEIMAGEMASK(2)|TVIS_BOLD,TVIS_STATEIMAGEMASK|TVIS_BOLD);

	//m_itemToMapPtr.insert(std::map<HTREEITEM,Carto::CMapPtr>::value_type(hMapItem,pMap));

	//SelectItem(hMapItem);
	//m_iSelectedItemType = Framework::eMapItem;

	////���Layer
	//Carto::CLayerArray layerArray = pMap->GetLayers();
	//HTREEITEM hBefore;

	//for(int i=0; i<layerArray.GetSize(); i++)
	//{
	//	Carto::ILayerPtr ptrLayer = NULL, ptrLayerBefore = NULL;
	//	ptrLayer  = layerArray[i];

	//	if(i==0)
	//	{
	//		hBefore = TVI_FIRST;
	//	}
	//	else
	//	{
	//		ptrLayerBefore = layerArray[i-1];
	//		hBefore = SearchItemByLayer(ptrLayerBefore);
	//	}

	//	//ΪRasterLayer��VectorLayer���layer
	//	AddLayerNode( ptrLayer, hMapItem, hBefore,FALSE);		
	//}

	//UpdateInterface();

	return TRUE;
}

void CMaptreeCtrl::UpdateInterface()
{
	Invalidate();
    UpdateWindow();
}

BOOL CMaptreeCtrl::CreateControl(std::string Name, void *pParent, long nID)
{
	CreateAss( Name );
	m_csCtrlName = Name;
	CWnd *pWnd = (CWnd*)(pParent);

	BOOL bRet = Create( WS_CHILD | WS_VISIBLE | TVS_HASLINES |TVS_LINESATROOT| TVS_HASBUTTONS | TVS_SHOWSELALWAYS , CRect(0,0,0,0) , pWnd , nID );

	return bRet;
}


//���ͼ��
void CMaptreeCtrl::AddLayer(Carto::ILayerPtr layerPtr, BOOL bExpand)
{
	
	Framework::IMapCtrl *pMapCtrl =Framework::IMapCtrl::GetActiveMapCtrl();

	if(!pMapCtrl)
	{
		return;
	}

	Carto::CMapPtr ptrMap = pMapCtrl->GetMap();
	if (ptrMap == NULL)
	{
		return;
	}


	//�õ���ǰͼ����map�е�λ��
	Carto::CLayerArray layerArray = ptrMap->GetLayers();
	long lLocation = layerArray.FindIndex(layerPtr);
	HTREEITEM hInsertAfter;
	/*if (lLocation > 0) 
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
	}*/

	if (lLocation == layerArray.GetSize()-1) 
	{	
		hInsertAfter = TVI_FIRST;
	
	}
	else if(lLocation>=0)
	{

		Carto::ILayerPtr ptrLayerInsertAfter = layerArray[lLocation + 1];
		hInsertAfter = SearchItemByLayer(ptrLayerInsertAfter);
	}
	else
	{
	   return;
	}



	//ΪRasterLayer��VectorLayer���layer
	AddLayerNode( layerPtr, m_hActMapItem, hInsertAfter,bExpand);

	UpdateInterface();
}

//���ͼ��ڵ�
void CMaptreeCtrl::AddLayerNode(Carto::ILayerPtr layerPtr, HTREEITEM hParent, HTREEITEM hInsertAfter, BOOL bExpand )
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
		m_iSelectedItemType = Framework::eLayerItem;
	}

	ActiveLayer(hLayerItem);
}

HTREEITEM CMaptreeCtrl::AddFeatureLayerNode(Carto::ILayerPtr layerPtr, HTREEITEM hParent, HTREEITEM hInsertAfter, BOOL bExpand )
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

	HTREEITEM hLayerItem = InsertItem(layerPtr->GetName().c_str(), ImageIndex, ImageIndex, hParent, hInsertAfter);

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

HTREEITEM CMaptreeCtrl::AddRasterLayerNode(Carto::ILayerPtr layerPtr, HTREEITEM hParent, HTREEITEM hInsertAfter, BOOL bExpand )
{
	if (layerPtr == NULL || hParent == NULL)
	{
		return NULL;
	}

	Carto::CRasterLayerPtr RasterLayerlayerPtr = (Carto::CRasterLayerPtr)layerPtr;
	long lband =RasterLayerlayerPtr->BandCount();
	int ImageIndex =(lband<3)?13:11;


	HTREEITEM hLayerItem = InsertItem(layerPtr->GetName().c_str(), ImageIndex, ImageIndex, hParent, hInsertAfter);

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
	AddRasterLayerLegend(layerPtr,hLayerItem);

	if(bExpand)
	{
		Expand(hLayerItem,TVE_EXPAND);
	}

	return hLayerItem;
}

HTREEITEM CMaptreeCtrl::AddTinLayerNode(Carto::ILayerPtr layerPtr, HTREEITEM hParent, HTREEITEM hInsertAfter, BOOL bExpand /* = TRUE */)
{
   return NULL;
}
//ͨ��ͼ���ָ������������еĽڵ�
HTREEITEM CMaptreeCtrl::SearchItemByLayer(Carto::ILayerPtr ptrLayer)
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
void CMaptreeCtrl::DeleteLayer(Carto::ILayerPtr ptrLayer)
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



void CMaptreeCtrl::DeleteAllLayers()
{
	Framework::IMapCtrl *pMapCtrl =Framework::IMapCtrl::GetActiveMapCtrl();
	if(!pMapCtrl)
	{
		return;
	}

	Carto::CMapPtr ptrMap = pMapCtrl->GetMap();
	if (ptrMap == NULL )
	{
		return;
	}

	Carto::CLayerArray& LayerArray = ptrMap->GetLayers();
	size_t nSize = LayerArray.GetSize();
	Carto::ILayerPtr ptrLayer = NULL;

	while (LayerArray.GetSize() != 0)
	{
		ptrLayer = LayerArray.GetAt(LayerArray.GetSize() - 1);
		DeleteLayer(ptrLayer);

		//�˴���Ҫ��ӻص�
		ptrMap->DeleteLayer(ptrLayer);

	}
	pMapCtrl->UpdateControl(drawAll);

}




//
void CMaptreeCtrl::ClearControl()
{
	HTREEITEM hItem = NULL,hRoot = NULL;


	hItem = GetRootItem();
	if(!hItem)
		return;

	
	while(hItem)
	{
		std::map<HTREEITEM,Carto::CMapPtr>::iterator it = m_itemToMapPtr.find(hItem);
		if (it != m_itemToMapPtr.end())
		{	
			SelectItem(hItem);
			
			//ɾ��tree�м�¼
			Carto::CMapPtr pMap = NULL;
			pMap = DeleteMap();

			//ɾ��MAP������MAP
			//pMapCtrl->DeleteMap(id);
			if (pMap != NULL)
			{
				/*Framework::IMapCtrl *pMapCtrl =Framework::IMapCtrl::GetActiveMapCtrl();
				if(!pMapCtrl)
				{
					return;
				}*/
				//pMapCtrl->DeleteMap(pMap);
			}

		}

		hItem = GetRootItem();
	}

	/*Framework::IMapCtrl *pMapCtrl =Framework::IMapCtrl::GetActiveMapCtrl();
	if(!pMapCtrl)
	{
		return;
	}
	pMapCtrl->ClearMapID();*/
}

//
Carto::CMapPtr CMaptreeCtrl::ActivateMap()
{
	HTREEITEM hMapItem = GetSelectedItem();

	Carto::CMapPtr pMap = m_itemToMapPtr[hMapItem];

	if (m_hActMapItem != NULL)
	{	
		CTreeCtrl::SetItemState( m_hActMapItem, ~TVIS_BOLD, TVIS_BOLD);
	}
	else
		return NULL;

	CTreeCtrl::SetItemState( hMapItem, TVIS_BOLD, TVIS_BOLD);

	m_hActMapItem = hMapItem;
	m_iSelectedItemType = Framework::eActiveMapItem;

	//�����ͼ�������ݼ���ĳһ��ͼ��
	ActiveLayer(pMap);

	return pMap;
}


void CMaptreeCtrl::ActivateMap(Carto::CMapPtr pMap)
{
	HTREEITEM hTreeItem = NULL;
	std::map<HTREEITEM, Carto::CMapPtr>::iterator iter;
	for (iter = m_itemToMapPtr.begin(); iter != m_itemToMapPtr.end(); iter++)
	{
		if ((*iter).second == pMap)
		{
			hTreeItem = (*iter).first;
			break;
		}
	}
	if (hTreeItem == NULL)
	{
		//error
		return;
	}

	if (m_hActMapItem != NULL)
	{	
		CTreeCtrl::SetItemState( m_hActMapItem, ~TVIS_BOLD, TVIS_BOLD);
	}

	CTreeCtrl::SetItemState( hTreeItem, TVIS_BOLD, TVIS_BOLD);

	m_hActMapItem = hTreeItem;
	m_iSelectedItemType = Framework::eActiveMapItem;
}


Carto::CMapPtr CMaptreeCtrl::DeleteMap(Carto::CMapPtr pMap)
{
	HTREEITEM hItem = NULL,hRoot = NULL;
	HTREEITEM hSelectedItem = NULL;

	if(!pMap)
		return NULL;

	hItem = GetRootItem();
	if(!hItem)
		return NULL;

	/*hItem = GetChildItem(hRoot);
	if(!hItem)
		return NULL;*/

	while(hItem)
	{
		std::map<HTREEITEM,Carto::CMapPtr>::iterator it = m_itemToMapPtr.find(hItem);
		if (it != m_itemToMapPtr.end())
		{
			if(pMap == it->second)
			{
				hSelectedItem = hItem;
				break;
			}
		}
		hItem = GetNextSiblingItem(hItem);
	}

	if(hSelectedItem)
		SelectItem(hSelectedItem);

	return DeleteMap();
}


Carto::CMapPtr CMaptreeCtrl::DeleteMap()
{
	HTREEITEM hMapItem = GetSelectedItem();

	if (m_hActMapItem == hMapItem)
	{
		m_hActMapItem = NULL;
	}

	if (ItemHasChildren(hMapItem))
	{
		HTREEITEM hNextItem;
		HTREEITEM hChildItem = GetChildItem(hMapItem);

		while (hChildItem != NULL)
		{
			hNextItem = GetNextItem(hChildItem, TVGN_NEXT);	
			m_LayerItemMap.erase(hChildItem);
			DeleteItem(hChildItem);
			hChildItem = hNextItem;
		}
	}

	Carto::CMapPtr pMap = NULL;
	std::map<HTREEITEM,Carto::CMapPtr>::iterator it = m_itemToMapPtr.find(hMapItem);
	if (it != m_itemToMapPtr.end())
	{
		pMap = it->second;
	   m_itemToMapPtr.erase(hMapItem);
	}

	DeleteItem(hMapItem);
	SetParentItemState(m_hRootItem);

	return pMap;
}


void CMaptreeCtrl::SetParentItemState(HTREEITEM hParentItem)
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

void CMaptreeCtrl::TravelSiblingAndParent(HTREEITEM hItem, int nState)
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

HTREEITEM CMaptreeCtrl::SearchItemByMap(Carto::CMapPtr pMap)
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

void* CMaptreeCtrl::GetSelectedItemData()
{
    HTREEITEM item =GetSelectedItem();
	if(item!=NULL)
	{
       return (void*)GetItemData(item);
	}
	return NULL;
}


/***********************************************************************************************************
* ������ͼ��������صĺ���
************************************************************************************************************/

void CMaptreeCtrl::CreateSymbolBmp(Display::ISymbolPtr pSymbol,CBitmap &bmp)
{ 
	if (pSymbol == NULL)
		return;

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

void CMaptreeCtrl::AddFeatureLayerLegend(Carto::ILayerPtr ptrLayer, HTREEITEM hParent)
{
	Carto::CFeatureLayer *pLayer =(Carto::CFeatureLayer*)(ptrLayer.get());

	//���Render������
	Carto::IRenderPtr pRender =pLayer->GetFeatureRender();
	Carto::RENDER_TYPE rendertype =pRender->GetRenderType();

	//switch(rendertype)
	//{
	//	//�򵥷���
	//case Carto::OT_SIMPLERENDER:
	//	{
	//		Carto::CSimpleRender *pSimpleRender =(Carto::CSimpleRender*)(pRender.get());
	//		Display::ISymbolPtr pSymbol =pSimpleRender->GetSymbol();


	//		CBitmap bmp;
	//		CreateSymbolBmp(pSymbol,bmp);

	//		CImageList *pImgList = GetImageList(TVSIL_NORMAL);
	//		int lStartIndex = pImgList->GetImageCount();
	//		int iAppend = pImgList->Add(&bmp,(CBitmap*)NULL);
	//		CTreeCtrl::SetImageList(pImgList,TVSIL_NORMAL);

	//		//����ͼ���ڵ�
	//		InsertItem("",lStartIndex,lStartIndex,hParent,TVI_LAST);

	//		bmp.DeleteObject();




	//		break;
	//	}
	//	//Ψһֵͼ��
	//case Carto::OT_UNIQUERENDER:
	//	{
	//		Carto::CUniqueRender *pUniRender =(Carto::CUniqueRender*)(pRender.get());

	//		//���ȼ���ͼ��Heading
	//		std::string strHeading =pUniRender->GetHeading();
	//		if(!strHeading.empty())
	//		{
	//			InsertItem(strHeading.c_str(),14,14,hParent,TVI_LAST);
	//		}

	//		//����ÿ�����Žڵ�
	//		int lStartIndex;
	//		std::string strLable;
	//		std::string strValue;
	//		Display::ISymbolPtr pSymbol;
	//		CBitmap bmp;
	//		CImageList *pImgList = GetImageList(TVSIL_NORMAL);
	//		for(long i=0;i<pUniRender->GetCount();i++)
	//		{
	//			strValue =pUniRender->GetValue(i);
	//			strLable =pUniRender->GetLabel(strValue);
	//			pSymbol =pUniRender->GetUniqueValue(strValue);

	//			CreateSymbolBmp(pSymbol,bmp);


	//			lStartIndex = pImgList->GetImageCount();
	//			pImgList->Add(&bmp,(CBitmap*)NULL);


	//			//����ͼ���ڵ�
	//			InsertItem(strLable.c_str(),lStartIndex,lStartIndex,hParent,TVI_LAST);

	//			bmp.DeleteObject();

	//		}

	//		break;
	//	}

	//default:
	//	break;
	//}
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
				InsertItem(item.strLabel.c_str(),lStartIndex,lStartIndex,hParent,TVI_LAST);

				bmp.DeleteObject();

			}
		}
	}
}

void CMaptreeCtrl::AddRasterLayerLegend(Carto::ILayerPtr ptrLayer, HTREEITEM hParent)
{
	Carto::CRasterLayerPtr pLayer =ptrLayer;

	
	Carto::CLegendInfoPtr pLegendInfo =pLayer->GetLegendInfo();
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
				InsertItem(item.strLabel.c_str(),lStartIndex,lStartIndex,hParent,TVI_LAST);

				bmp.DeleteObject();

			}
		}
	}
}

//����ʸ������
void CMaptreeCtrl::OnLoadFeatureData()
{
	/*Framework::IDocument* pDoc =Framework::IDocument::GetActiveDocument();
	if(!pDoc)
	{
		return;
	}
	CString csFilter =	"Titan40 Themes (*.tms)|*.tms|ArcGis shp(*.shp)|*.shp||";
	char	szBigBuf[4096] = "";
	CString csDataSource("");
	CString csThemeName;

	CFileDialog dlg(TRUE, "tms", csThemeName, OFN_HIDEREADONLY|OFN_ALLOWMULTISELECT, csFilter);
	dlg.m_ofn.lpstrFile = szBigBuf;
	dlg.m_ofn.nMaxFile = sizeof (szBigBuf);


	if (IDOK != dlg.DoModal())
		return;

	POSITION pos = dlg.GetStartPosition();
	while (pos != NULL)
	{
		csDataSource = dlg.GetNextPathName (pos);
		pDoc->LoadVectorData (csDataSource);
		
	}
	Framework::IMapCtrl *pMapCtrl =Framework::IMapCtrl::GetActiveMapCtrl();
	pMapCtrl->GetActiveMap()->GetDisplay()->GetDisplayTransformation().FitViewBound(pMapCtrl->GetActiveMap()->GetExtent());
	pMapCtrl->UpdateControl(drawAll);*/


	
}

//����Ӱ������
void CMaptreeCtrl::OnLoadRaster()
{
	/*Framework::IDocument* pDoc =Framework::IDocument::GetActiveDocument();
	if(!pDoc)
	{
		return;
	}

	CString csFilter =	"�����ļ�(*.*)|*.*|Titan Image �ļ�(*.tmg)|*.tmg|Titan Image �ļ�(*.tmb)|*.tmb|BMP(*.bmp)|*.bmp|RAW(*.raw)|*.raw|PCI Pix(*.pix)|*.pix|Erdas 8.x(*.img)|*.img|Erdas 7.x(*.lan)|*.lan|TIFF(*.tif)|*.tif|TIFF(*.tiff)|*.tiff|JPEG(*.jpg)|*.jpg||";
	char	szBigBuf[4096] = "";
	CString csDataSource("");
	CString csThemeName("");
	CString csCurDirectory;

	CFileDialog dlg(TRUE, "tmg", csThemeName, OFN_HIDEREADONLY|OFN_ALLOWMULTISELECT, csFilter);
	dlg.m_ofn.lpstrFile = szBigBuf;
	dlg.m_ofn.nMaxFile = sizeof (szBigBuf);


	if (IDOK != dlg.DoModal())
		return;

	POSITION pos = dlg.GetStartPosition();
	while (pos != NULL)
	{
		csDataSource = dlg.GetNextPathName (pos);
		pDoc->LoadImageData(csDataSource);
	
	}
	Framework::IMapCtrl *pMapCtrl =Framework::IMapCtrl::GetActiveMapCtrl();
	pMapCtrl->GetActiveMap()->GetDisplay()->GetDisplayTransformation().FitViewBound(pMapCtrl->GetActiveMap()->GetExtent());
	pMapCtrl->UpdateControl(drawAll);*/
}

void CMaptreeCtrl::OnRemoveLayer()
{
	HTREEITEM item =CTreeCtrl::GetSelectedItem();
	if(!item)
	{
		return;
	}
    Framework::IMapCtrl *pMapCtrl =Framework::IMapCtrl::GetActiveMapCtrl();
	if(!pMapCtrl)
	{
		return;
	}
	HTREEITEM layerItem,mapItem;
	if(m_iSelectedItemType==Framework::eLayerItem)
	{
		layerItem =item;
	}
	else if(m_iSelectedItemType ==Framework::eLegendItem)
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
	std::map<HTREEITEM, Carto::CMapPtr>::iterator mapIter;
	mapIter = m_itemToMapPtr.find(mapItem);
	if(mapIter ==m_itemToMapPtr.end())
	{
		return;
	}

	Carto::CMapPtr pMap = mapIter->second;
	if(!pMap)
	{
		return;
	}

	//ȡ����ǰͼ��Ӵ�ǿ����ʾ��������ɾ��ͼ��ǰ���ã�
	CTreeCtrl::SetItemState( layerItem, ~TVIS_BOLD, TVIS_BOLD);
	//ɾ��ͼ��
	pMap->DeleteLayer(layerIter->second);
	CTreeCtrl::DeleteItem(layerItem);
	m_LayerItemMap.erase(layerIter);		

	Carto::CMapPtr pActiveMap = pMapCtrl->GetMap();
	ActiveLayer(pActiveMap);

	pMapCtrl->UpdateControl(drawAll);
}

void CMaptreeCtrl::OnRemoveAllLayer()
{
   DeleteAllLayers();
}

void CMaptreeCtrl::OnLayerProp()
{
	HTREEITEM item =CTreeCtrl::GetSelectedItem();
	if(!item)
	{
		return;
	}
	Framework::IMapCtrl *pMapCtrl =Framework::IMapCtrl::GetActiveMapCtrl();
	if(!pMapCtrl)
	{
		return;
	}
	HTREEITEM layerItem,mapItem;
	if(m_iSelectedItemType==Framework::eLayerItem)
	{
		layerItem =item;
	}
	else if(m_iSelectedItemType ==Framework::eLegendItem)
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
	CDllResource hdll;

	CLayerPropSheet sheet("ͼ������");
	sheet.SetLayer(layerIter->second);
	if(sheet.DoModal()==IDOK)
	{
        pMapCtrl->UpdateControl(drawAll);
		UpdateLayerNode(layerIter->second,layerItem);
	}



}

void CMaptreeCtrl::ActiveLayer(HTREEITEM item)
{
	
	if(!item)
	{
		return;
	}
	Framework::IMapCtrl *pMapCtrl =Framework::IMapCtrl::GetActiveMapCtrl();
	if(!pMapCtrl)
	{
		return;
	}
	HTREEITEM layerItem,mapItem;
	if(m_iSelectedItemType==Framework::eLayerItem)
	{	
		layerItem = item;		
	}
	else if(m_iSelectedItemType ==Framework::eLegendItem)
	{
		layerItem =GetParentItem(item);		
	}	
	else if (m_iSelectedItemType == Framework::eActiveMapItem)
	{
		
		layerItem = GetChildItem(item);		
	}
	else if (m_iSelectedItemType == Framework::eMapItem)
	{		
		layerItem = GetChildItem(item);		
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
	std::map<HTREEITEM, Carto::CMapPtr>::iterator mapIter;
	mapIter = m_itemToMapPtr.find(mapItem);
	if(mapIter ==m_itemToMapPtr.end())
	{
		return;
	}
	Carto::CMapPtr pGeoMap = mapIter->second;
	pGeoMap->MoveLayerToBottom(layerIter->second);
	pGeoMap->SetActiveLayer(layerIter->second);

	//�Ӵּ���ͼ������
	HTREEITEM pChildItem,pParentItem;

	if (m_hActLayerItem != NULL)
	{
		pChildItem = GetChildItem(m_hActLayerItem);
		pParentItem = GetParentItem(m_hActLayerItem);

		CTreeCtrl::SetItemState( m_hActLayerItem, ~TVIS_BOLD, TVIS_BOLD);

		while(ItemHasChildren(pChildItem))
		{
			CTreeCtrl::SetItemState(pChildItem, ~TVIS_BOLD, TVIS_BOLD);
			pChildItem = GetChildItem(pChildItem);
		}	
		while(pParentItem!=NULL)
		{
			CTreeCtrl::SetItemState(pParentItem, ~TVIS_BOLD, TVIS_BOLD);	
			pParentItem = GetParentItem(pParentItem);
		}
	}

	CTreeCtrl::SetItemState(layerItem, TVIS_BOLD, TVIS_BOLD);	

	pChildItem = GetChildItem(layerItem);
	pParentItem = GetParentItem(layerItem);

	while(ItemHasChildren(pChildItem))
	{
		CTreeCtrl::SetItemState(pChildItem, TVIS_BOLD, TVIS_BOLD);
		pChildItem = GetChildItem(pChildItem);
	}	
	while(pParentItem!=NULL)
	{
		CTreeCtrl::SetItemState(pParentItem, TVIS_BOLD, TVIS_BOLD);	
		pParentItem = GetParentItem(pParentItem);
	}
	m_hActLayerItem = layerItem;

	//pMapCtrl->UpdateControl(drawAll);		

}

void CMaptreeCtrl::ActiveLayer(Carto::CMapPtr pMap)
{
	Carto::CLayerArray layerArray = pMap->GetLayers();
	Carto::ILayerPtr ptrLayer = NULL;
	HTREEITEM pLayerTreeItem;

	if (layerArray.GetSize()<1)
	{
		HTREEITEM pChildItem,pParentItem;

		if (m_hActLayerItem != NULL)
		{
			pChildItem = GetChildItem(m_hActLayerItem);
			pParentItem = GetParentItem(m_hActLayerItem);

			CTreeCtrl::SetItemState( m_hActLayerItem, ~TVIS_BOLD, TVIS_BOLD);

			while(ItemHasChildren(pChildItem))
			{
				CTreeCtrl::SetItemState(pChildItem, ~TVIS_BOLD, TVIS_BOLD);
				pChildItem = GetChildItem(pChildItem);
			}	
			while(pParentItem!=NULL)
			{
				CTreeCtrl::SetItemState(pParentItem, ~TVIS_BOLD, TVIS_BOLD);	
				pParentItem = GetParentItem(pParentItem);
			}
		}
	}
	else
	{
		for(int i=0; i<layerArray.GetSize(); i++)
		{		
			ptrLayer  = layerArray[i];
			std::map<HTREEITEM, Carto::ILayerPtr>::iterator iter;

			for (iter = m_LayerItemMap.begin(); iter != m_LayerItemMap.end(); iter++)
			{
				if ((*iter).second == ptrLayer)
				{
					pLayerTreeItem = (*iter).first;
					break;
				}
			}
			m_iSelectedItemType = Framework::eLayerItem;
			ActiveLayer(pLayerTreeItem);			
		}
	}		
}

void CMaptreeCtrl::OnActiveLayer()
{
	HTREEITEM item =CTreeCtrl::GetSelectedItem();
	ActiveLayer(item);	
}

void CMaptreeCtrl::UpdateLayerNode(Carto::ILayerPtr layerPtr, HTREEITEM LayerItem)
{
	SetItemText(LayerItem,layerPtr->GetName().c_str());

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

		AddRasterLayerLegend(layerPtr,LayerItem);
		break;

	case Carto::TinLayer :

		
		break;

	}

}

//���Ǽ�����ͼ����ɾ��
void CMaptreeCtrl::OnDeleteMap()
{
	//if(m_iSelectedItemType == Framework::eActiveMapItem)
	//	return;

	//Framework::IMapCtrl *pMapCtrl =Framework::IMapCtrl::GetActiveMapCtrl();
	//if(!pMapCtrl)
	//{
	//	return;
	//}
	//if (pMapCtrl->GetMapCount() == 1)
	//	return;

	////ɾ��tree�м�¼
	//Carto::CMapPtr pMap = NULL;
	//pMap = DeleteMap();

	////ɾ��MAP������MAP
	////pMapCtrl->DeleteMap(id);
	//if (pMap != NULL)
	//{
	//	pMapCtrl->DeleteMap(pMap);
	//}


}

void CMaptreeCtrl::OnActiveMap()
{
	/*if(m_iSelectedItemType == Framework::eActiveMapItem)
		return;

	Framework::IMapCtrl *pMapCtrl =Framework::IMapCtrl::GetActiveMapCtrl();
	if(!pMapCtrl)
	{
		return;
	}
	Carto::CMapPtr pMap = ActivateMap();
	if(pMap == NULL)
		return;
	pMapCtrl->SetActiveMap(pMap);*/
}

void CMaptreeCtrl::OnMapProp()
{
	/*Framework::IMapCtrl *pMapCtrl =Framework::IMapCtrl::GetActiveMapCtrl();
	if(!pMapCtrl)
	{
		return;
	}
	Carto::CMapPtr pMap = ActivateMap();
	if(pMap == NULL)
		return;

	CDllResource hdll;

	CMapProperSheet sheet("��ͼ����");
	sheet.SetMap(pMap);
	if(sheet.DoModal()==IDOK)
	{
		pMapCtrl->UpdateControl(drawAll);
	}*/

}

void CMaptreeCtrl::OnZoomToLayer()
{
	HTREEITEM item =CTreeCtrl::GetSelectedItem();
	if(!item)
	{
		return;
	}
	Framework::IMapCtrl *pMapCtrl =Framework::IMapCtrl::GetActiveMapCtrl();
	if(!pMapCtrl)
	{
		return;
	}
	HTREEITEM layerItem,mapItem;
	if(m_iSelectedItemType==Framework::eLayerItem)
	{
		layerItem =item;
	}
	else if(m_iSelectedItemType ==Framework::eLegendItem)
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
	std::map<HTREEITEM, Carto::CMapPtr>::iterator mapIter;
	mapIter = m_itemToMapPtr.find(mapItem);
	if(mapIter ==m_itemToMapPtr.end())
	{
		return;
	}

	Carto::CMapPtr pMap = mapIter->second;
	if(!pMap)
	{
		return;
	}

	Carto::ILayerPtr pLayer = layerIter->second;

	GEOMETRY::geom::Envelope env = pLayer->GetEnvelope();

	pMap->GetDisplay()->GetDisplayTransformation().FitViewBound(env);

	pMapCtrl->UpdateControl(drawAll);
}
void CMaptreeCtrl::OnObjExport()
{
	HTREEITEM item =CTreeCtrl::GetSelectedItem();
	if(!item)
	{
		return;
	}
	Framework::IMapCtrl *pMapCtrl =Framework::IMapCtrl::GetActiveMapCtrl();
	if(!pMapCtrl)
	{
		return;
	}
	HTREEITEM layerItem,mapItem;
	if(m_iSelectedItemType==Framework::eLayerItem)
	{
		layerItem =item;
	}
	else if(m_iSelectedItemType ==Framework::eLegendItem)
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
	std::map<HTREEITEM, Carto::CMapPtr>::iterator mapIter;
	mapIter = m_itemToMapPtr.find(mapItem);
	if(mapIter ==m_itemToMapPtr.end())
	{
		return;
	}

	Carto::CMapPtr pMap = mapIter->second;
	if(!pMap)
	{
		return;
	}

	Carto::ILayerPtr pLayer = layerIter->second;
	if (pLayer->GetLayerType() != Carto::LAYER_TYPE::FeatureLayer)
		return;

	CDllResource hdll;
	CDlgObjExport dlg;
	dlg.m_SrcFeatureLayer = pLayer;
	dlg.DoModal();
	
}

void CMaptreeCtrl::RefreshFromDoc()
{
	DeleteAllItems();
	Framework::IDocument* pDoc =(Framework::IDocument*)Framework::IUIObject::GetUIObjectByName(Framework::CommonUIName::AppDocument);

	if(!pDoc)
	{
		return;
	}
    
	long nCount =pDoc->GetMapCount();
	for(long lIndex=0;lIndex<nCount;lIndex++)
	{
		Carto::CMapPtr pMap = pDoc->GetMap(lIndex);

		if(!pMap)
		{
			continue;
		}
		std::string csName = pMap->GetName();
		HTREEITEM hMapItem = InsertItem(csName.c_str(), 0, 0 );

		m_itemToMapPtr.insert(std::map<HTREEITEM,Carto::CMapPtr>::value_type(hMapItem,pMap));

		SelectItem(hMapItem);
		m_iSelectedItemType = Framework::eMapItem;

		//���Layer
		Carto::CLayerArray layerArray = pMap->GetLayers();
		HTREEITEM hBefore;

		for(int i=0; i<layerArray.GetSize(); i++)
		{
			Carto::ILayerPtr ptrLayer = NULL, ptrLayerBefore = NULL;
			ptrLayer  = layerArray[i];

			/*if(i==0)
			{
				hBefore = TVI_FIRST;
			}
			else
			{
				ptrLayerBefore = layerArray[i-1];
				hBefore = SearchItemByLayer(ptrLayerBefore);
			}*/

            hBefore = TVI_FIRST;

			//ΪRasterLayer��VectorLayer���layer
			AddLayerNode( ptrLayer, hMapItem, hBefore,FALSE);		
		}
	}

	//���û��ͼ
	ActivateMap(pDoc->GetActiveMap());
	

}

void CMaptreeCtrl::OnOpenAttribute()
{
	HTREEITEM item =CTreeCtrl::GetSelectedItem();
	if(!item)
		return;

	Framework::IMapCtrl *pMapCtrl = Framework::IMapCtrl::GetActiveMapCtrl();
	if(!pMapCtrl)
		return;
	
	HTREEITEM layerItem, mapItem;
	if(m_iSelectedItemType == Framework::eLayerItem)
		layerItem =item;
	else if(m_iSelectedItemType == Framework::eLegendItem)
		layerItem =GetParentItem(item);

	std::map  <HTREEITEM, Carto::ILayerPtr>::iterator layerIter;
	//����ͼ��
	layerIter =m_LayerItemMap.find(layerItem);
	if(layerIter ==m_LayerItemMap.end())
		return;
	
	Carto::ILayerPtr pLayer = layerIter->second;
	if(pLayer->GetLayerType() != Carto::FeatureLayer)
		return;

	OpenAttributeTable(pLayer, pLayer->GetDataObject());
}


}//namespace Control



