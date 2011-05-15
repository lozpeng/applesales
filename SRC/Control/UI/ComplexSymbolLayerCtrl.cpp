// ComplexSymbolLayerCtrl.cpp : 实现文件
//

#include "stdafx.h"
#include "ComplexSymbolLayerCtrl.h"
#include "atlimage.h"
#include "IComplexSymbol.h"
#include "IDisplay.h"
// CComplexSymbolLayerCtrl

IMPLEMENT_DYNAMIC(CComplexSymbolLayerCtrl, CListCtrl)

CComplexSymbolLayerCtrl::CComplexSymbolLayerCtrl()
{
	m_nSelect = 0;
	m_bDraw = true;
	m_Bitmap = NULL;
	m_LargeImageList = NULL;
	m_MaskBitmap = NULL ;
}

CComplexSymbolLayerCtrl::~CComplexSymbolLayerCtrl()
{
	
	if(m_LargeImageList)
	{
		int nCount = m_LargeImageList->GetImageCount();

		for ( int i=0 ; nCount<i ; i++ )
			m_LargeImageList->Remove( i );
		m_LargeImageList->DeleteImageList();
		delete m_LargeImageList;
		m_LargeImageList=NULL;
	}
	if(m_MaskBitmap!= NULL)
	{
		m_MaskBitmap->DeleteObject();
		m_MaskBitmap = NULL;
	}
}

BEGIN_MESSAGE_MAP(CComplexSymbolLayerCtrl, CListCtrl)

	ON_NOTIFY_REFLECT(NM_CLICK, &CComplexSymbolLayerCtrl::OnNMClick)
	ON_NOTIFY_REFLECT(NM_RCLICK, &CComplexSymbolLayerCtrl::OnNMRclick)
	ON_NOTIFY_REFLECT(LVN_BEGINDRAG, &CComplexSymbolLayerCtrl::OnLvnBegindrag)
	ON_NOTIFY_REFLECT(LVN_BEGINRDRAG, &CComplexSymbolLayerCtrl::OnLvnBeginrdrag)

END_MESSAGE_MAP()
// CComplexSymbolLayerCtrl 消息处理程序
void CComplexSymbolLayerCtrl::DrawItem(LPDRAWITEMSTRUCT lpDIS)
{

	if(lpDIS->itemAction==ODA_DRAWENTIRE)
	{
		int nSelect = GetItemState( lpDIS->itemID , LVIS_STATEIMAGEMASK );
		HPEN pen;
		POINT point[5];
		CDC * dc=GetDC();
		POINT pDest;
		pDest.x = lpDIS->rcItem.left;
		pDest.y = lpDIS->rcItem.top;
		if( m_SymbolType & MARKER_SYMBOL )
		{
			if(nSelect==INDEXTOSTATEIMAGEMASK(1))	
			{
				m_StateImageList.Draw( dc , 0 , pDest ,ILD_TRANSPARENT );
				pDest.y+=4;
				pDest.x+=m_nWidth;
				m_LargeImageList->Draw( dc, lpDIS->itemID ,pDest , ILD_TRANSPARENT );
			}
			else if(nSelect==INDEXTOSTATEIMAGEMASK(2))
			{
				m_StateImageList.Draw( dc , 1 , pDest ,ILD_TRANSPARENT );
				pDest.y+=4;
				pDest.x+=m_nWidth;
				m_LargeImageList->Draw( dc, lpDIS->itemID ,pDest , ILD_TRANSPARENT );
			}
			else if(nSelect==INDEXTOSTATEIMAGEMASK(3))
			{
				m_StateImageList.Draw( dc , 2 , pDest ,ILD_TRANSPARENT );
				pDest.y+=4;
				pDest.x+=m_nWidth;
				m_LargeImageList->Draw( dc, lpDIS->itemID ,pDest , ILD_TRANSPARENT );
			}
			else if(nSelect==INDEXTOSTATEIMAGEMASK(4))
			{
				m_StateImageList.Draw( dc , 3 , pDest ,ILD_TRANSPARENT );
				pDest.y+=4;
				pDest.x+=m_nWidth;
				m_LargeImageList->Draw( dc, lpDIS->itemID ,pDest , ILD_TRANSPARENT );
			}
			if(nSelect==INDEXTOSTATEIMAGEMASK(3)||nSelect==INDEXTOSTATEIMAGEMASK(4))
			{	
				UINT uSelect=this->GetItemState( 0 , LVIS_STATEIMAGEMASK) |  LVIS_DROPHILITED;

				point[0].x = lpDIS->rcItem.left + 1;
				point[0].y = lpDIS->rcItem.top + 3;
				point[1].x = lpDIS->rcItem.right - 7;
				point[1].y = lpDIS->rcItem.top + 3;
				point[2].x = lpDIS->rcItem.right - 7;
				point[2].y = lpDIS->rcItem.bottom - 2;
				point[3].x = lpDIS->rcItem.left + 1;
				point[3].y = lpDIS->rcItem.bottom - 2;
				point[4].x = lpDIS->rcItem.left + 1;
				point[4].y = lpDIS->rcItem.top + 3;

				pen=CreatePen( PS_SOLID , 1 , RGB(0,0,0) );
				HPEN oldp;
				oldp=(HPEN)SelectObject( lpDIS->hDC , pen );

				Polyline( lpDIS->hDC , point , 5 );
				DeleteObject( (HPEN)SelectObject( lpDIS->hDC ,oldp ) );
			}
		}
		else
		{
			if(nSelect==INDEXTOSTATEIMAGEMASK(1))	
			{
				m_StateImageList.Draw( dc , 0 , pDest ,ILD_TRANSPARENT );
				pDest.y+=4;
				pDest.x+=m_nWidth;
				m_LargeImageList->Draw( dc, lpDIS->itemID ,pDest , ILD_TRANSPARENT );
			}
			else if(nSelect==INDEXTOSTATEIMAGEMASK(2))
			{
				m_StateImageList.Draw( dc , 1 , pDest ,ILD_TRANSPARENT );
				pDest.y+=4;
				pDest.x+=m_nWidth;
				m_LargeImageList->Draw( dc, lpDIS->itemID ,pDest , ILD_TRANSPARENT );
			}
			else if(nSelect==INDEXTOSTATEIMAGEMASK(3))
			{
				m_StateImageList.Draw( dc , 2 , pDest ,ILD_TRANSPARENT );
				pDest.y+=4;
				pDest.x+=m_nWidth;
				m_LargeImageList->Draw( dc, lpDIS->itemID ,pDest , ILD_TRANSPARENT );
			}
			else if(nSelect==INDEXTOSTATEIMAGEMASK(4))
			{
				m_StateImageList.Draw( dc , 3 , pDest ,ILD_TRANSPARENT );
				pDest.y+=4;
				pDest.x+=m_nWidth;
				m_LargeImageList->Draw( dc, lpDIS->itemID ,pDest , ILD_TRANSPARENT );
			}
			if(nSelect==INDEXTOSTATEIMAGEMASK(3)||nSelect==INDEXTOSTATEIMAGEMASK(4))
			{	
				UINT uSelect=this->GetItemState( 0 , LVIS_STATEIMAGEMASK) |  LVIS_DROPHILITED;

				point[0].x = lpDIS->rcItem.left ;
				point[0].y = lpDIS->rcItem.top + 3;
				point[1].x = lpDIS->rcItem.right - 5;
				point[1].y = lpDIS->rcItem.top + 3;
				point[2].x = lpDIS->rcItem.right - 5;
				point[2].y = lpDIS->rcItem.bottom - 1;
				point[3].x = lpDIS->rcItem.left;
				point[3].y = lpDIS->rcItem.bottom - 1;
				point[4].x = lpDIS->rcItem.left + 1;
				point[4].y = lpDIS->rcItem.top + 3;

				pen=CreatePen( PS_SOLID , 1 , RGB(0,0,0) );
				HPEN oldp;
				oldp=(HPEN)SelectObject( lpDIS->hDC , pen );

				Polyline( lpDIS->hDC , point , 5 );
				DeleteObject( (HPEN)SelectObject( lpDIS->hDC ,oldp ) );
			}
		}
		ReleaseDC( dc );
	}
}

void CComplexSymbolLayerCtrl::InitComplexSymbolLayerCtrl(RECT * rect, 
														 UINT nIDResource , 
														 unsigned int nWidth)
{
	if( !rect )
	{
		return;
	}
	m_rc.bottom = rect->bottom - 5;
	m_rc.right = rect->right+1;
	m_rc.left = rect->left;
	m_rc.top = rect->top;
	m_nX = m_rc.right-m_rc.left;
	m_nY = m_rc.bottom-m_rc.top;
	if( m_LargeImageList!= NULL )
	{
		int nCount = m_LargeImageList->GetImageCount();
		for ( int i=0 ; nCount<i ; i++ )
		m_LargeImageList->Remove( i );
		m_LargeImageList->DeleteImageList();
		delete m_LargeImageList;
		m_LargeImageList=NULL;
	}
	m_LargeImageList=new CImageList;
	m_LargeImageList->Create(m_nX,m_nY,ILC_COLOR24,0,1);

	if( nIDResource!=-1 )
	{
		m_nWidth=nWidth;
		m_StateImageList.Create( nIDResource , nWidth , 1 , RGB(255,0,0) );
	}
	CDC * dc = GetDC();
	CDC MemDC;//创建相容的bitmap和dc

	HBITMAP hbitmap1 = CreateCompatibleBitmap( dc->GetSafeHdc() , m_nX , m_nY );
	HBITMAP hBitmapTemp;

	MemDC.CreateCompatibleDC(dc);
	hBitmapTemp = ( HBITMAP )SelectObject( MemDC , hbitmap1 );

	RECT rectMask;
	rectMask.top=rectMask.left= 0;
	rectMask.right = m_rc.right;
	rectMask.bottom = m_rc.bottom;

	HBRUSH hSolidBrush = CreateSolidBrush( DEFAULTCOLOR );
	FillRect( MemDC.GetSafeHdc() , &rectMask,hSolidBrush );
	hbitmap1=( HBITMAP )SelectObject( MemDC.m_hDC , hBitmapTemp );
	if(m_MaskBitmap!= NULL)
	{
		m_MaskBitmap->DeleteObject();
		m_MaskBitmap = NULL;
	}

	m_MaskBitmap=CBitmap::FromHandle( hbitmap1 );

	DeleteObject( hSolidBrush );
	ReleaseDC( dc );
	MemDC.DeleteDC();
	this->SetImageList( m_LargeImageList , LVSIL_NORMAL );
	this->SetImageList( &m_StateImageList , LVSIL_STATE );

	AddCOL();
}

BOOL CComplexSymbolLayerCtrl::ReplaceSymbol(Display::ISymbolPtr pSymbol , long nIndex , unsigned long nColor)
{
	if(!pSymbol)
	{
		return FALSE;
	}
	HBITMAP hbitmap = this->CoverBitmap( pSymbol );
	m_Bitmap = CBitmap::FromHandle( hbitmap );
	if( m_MaskBitmap!=NULL )
	{
		return m_LargeImageList->Replace( nIndex , m_Bitmap , m_MaskBitmap );
	}
	else
	{
		return FALSE;
	}
	return TRUE;
}

HBITMAP CComplexSymbolLayerCtrl::CoverBitmap(Display::ISymbolPtr pSymbol)
{
		if(!pSymbol)
		{
			return 0;
		}
		m_SymbolType = pSymbol->GetType();
		Display::IDisplay  SimpleDisplay;			//绘制对象
		CDC * dc = GetDC();
		CDC MemDC;//创建相容的bitmap和dc
		HBITMAP hbitmap = CreateCompatibleBitmap( dc->GetSafeHdc() , m_nX , m_nY );
		HBITMAP hBitmapTemp;

		MemDC.CreateCompatibleDC( dc );
		hBitmapTemp = (HBITMAP)SelectObject( MemDC,hbitmap );
		SimpleDisplay.SetDC(( long )MemDC.GetSafeHdc(), m_nX , m_nY );

		RECT rect;
		rect.top = rect.left = 0;
		rect.right = m_rc.right;
		rect.bottom = m_rc.bottom;

		HBRUSH hSolidBrush = CreateSolidBrush( RGB(255,255,255) );
		FillRect( MemDC.GetSafeHdc() , &rect,hSolidBrush );

		DIS_RECT dRect;
		dRect.top = dRect.left = m_rc.top = 1;
		dRect.right = rect.right ;
		dRect.bottom = rect.bottom;

		SimpleDisplay.DrawLegend( pSymbol.get() , &dRect , 0 );
		hbitmap=(HBITMAP)SelectObject( MemDC.m_hDC , hBitmapTemp );

		DeleteObject( hSolidBrush );
		ReleaseDC( dc );
		MemDC.DeleteDC();
		return hbitmap;
}

void CComplexSymbolLayerCtrl::AddSymbol(Display::ISymbolPtr pSymbol, int nIndex)
{
		if(!pSymbol)
		{
			return;
		}
		if(!m_LargeImageList)
		{
			return;
		}

		HBITMAP hbitmap = this->CoverBitmap( pSymbol );
		m_Bitmap = CBitmap::FromHandle( hbitmap );

		m_LargeImageList->Add( m_Bitmap , DEFAULTCOLOR );
		m_Bitmap->Detach();
		DeleteObject( hbitmap );

		m_Bitmap=NULL;
		hbitmap=NULL;
}
BOOL CComplexSymbolLayerCtrl::RemoveSymbol(int nIndex)
{
	return m_LargeImageList->Remove( nIndex );
}

void CComplexSymbolLayerCtrl::SetSymbol( Display::ISymbolPtr pSymbol, SYMBOL_TYPE enumSymbolType )
{
	int lens;
	ImageListRemoveAll();	
	Display::IComplexSymbolPtr ICSymbol=(Display::IComplexSymbolPtr)pSymbol;
	lens=ICSymbol->GetSize();
	
		for( int i=0 ; i<lens ; i++ )
		{
			Display::ISymbolPtr isp = ( Display::ISymbolPtr )(ICSymbol->GetAt( i ));
			m_arState.Add(AnalyseState(ICSymbol->IsVisible(i),i));
			this->AddItem(i,m_arState[i]);	
			this->AddSymbol( isp , i );
		}
}

// 删除CImageList所用图片
BOOL CComplexSymbolLayerCtrl::ImageListRemoveAll(void)
{
	int nCount = m_LargeImageList->GetImageCount();

	for ( int i=0 ; nCount<i ; i++ )
		m_LargeImageList->Remove( i );
	m_LargeImageList->DeleteImageList();
	delete m_LargeImageList;
	m_LargeImageList=NULL;
	m_LargeImageList=new CImageList;
	m_LargeImageList->Create(m_nX,m_nY,ILC_COLOR24,0,1);

	return TRUE;
}
void CComplexSymbolLayerCtrl::AddItem(int nIndex, int nState)
{
	LV_ITEM lvi;
	lvi.mask =  LVIF_IMAGE|LVIF_STATE;
	lvi.iItem = nIndex;
	lvi.iSubItem = 0;
	lvi.iImage = nIndex;
	lvi.pszText = "";
	lvi.stateMask =  LVIS_STATEIMAGEMASK|LVIS_DROPHILITED;

	switch(nState)
	{
	case 1:
		lvi.state = INDEXTOSTATEIMAGEMASK( 1 );
		break;
	case 2:
		lvi.state =INDEXTOSTATEIMAGEMASK( 2 );
		break;
	case 3:
		lvi.state = INDEXTOSTATEIMAGEMASK( 3 )|LVIS_DROPHILITED ;
		break;
	case 4:
		lvi.state = INDEXTOSTATEIMAGEMASK( 4 )|LVIS_DROPHILITED;
		break;
	}

	InsertItem( &lvi );
}
void CComplexSymbolLayerCtrl::UpDataCSLC(Display::ISymbolPtr pSymbol, SYMBOL_TYPE enumSymbolType)
{
	this->DeleteAllItems();
	m_arState.RemoveAll();
	SetSymbol(pSymbol,enumSymbolType);
}

void CComplexSymbolLayerCtrl::OnNMClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	/*UINT uFlags = 0;
	LPNMITEMACTIVATE phdr = reinterpret_cast< LPNMITEMACTIVATE >( pNMHDR );
	POINT 	point;
	bool bSet;

	point.x=phdr->ptAction.x;
	point.y=phdr->ptAction.y;
	if( phdr->iItem!=-1 )
	{
		ResetItem( m_nSelect );
		if( m_nSelect==phdr->iItem )
			bSet = false;
		else
			bSet = true;
		m_nSelect = phdr->iItem;
		CRect rect;
		this->GetItemRect( m_nSelect , rect , LVIR_ICON );
		if ( point.x < rect.left)
		{		
			CheckItem( phdr->iItem );
			m_IComplexSymbolLayerCtrl->SetCopySymbol();
		}
		else
		{			
			CheckItemEx( phdr->iItem );
		}
		if(bSet)
			m_IComplexSymbolLayerCtrl->SetPropList( phdr->iItem );
		::SendMessage(GetParent()->m_hWnd , WM_REPAINTLEGEND , 0L , 0L );

	}*/
}

void CComplexSymbolLayerCtrl::OnNMRclick(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码

	*pResult = 0;
}

void CComplexSymbolLayerCtrl::OnLvnBegindrag(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}

void CComplexSymbolLayerCtrl::OnLvnBeginrdrag(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}

int CComplexSymbolLayerCtrl::AnalyseState(bool bState, int nSelect)
{	
	if(bState)
	{
		if(nSelect==m_nSelect)
		{
			return 4;
		}
		else
		{
			return 2;
		}
	}
	else
	{
		if(nSelect==m_nSelect)
		{
			return 3;
		}
		else
		{
			return 1;
		}
	}
	return -1;
}
void CComplexSymbolLayerCtrl::AddCOL(void)
{
	LV_COLUMN lvc;
	lvc.mask =  LVCF_FMT | LVCF_WIDTH  | LVCF_SUBITEM;
	lvc.iSubItem = 0;
	lvc.pszText = "";
	lvc.cx = m_nX+30;
	lvc.fmt =0;
	this->InsertColumn(0,&lvc);
}


void CComplexSymbolLayerCtrl::ResetItem(int nSelect)
{
	UINT state = GetItemState( nSelect , LVIS_STATEIMAGEMASK );
	LV_ITEM lvi;
	m_nSelect = nSelect;
	lvi.mask =  LVIF_IMAGE|LVIF_STATE;
	lvi.iItem = nSelect;
	lvi.iSubItem = 0;
	lvi.iImage = nSelect;
	lvi.pszText = "";
	lvi.stateMask  = LVIS_STATEIMAGEMASK|LVIS_DROPHILITED;

	switch ( state )
	{
	case  INDEXTOSTATEIMAGEMASK( 1 ):
		{
			lvi.state =INDEXTOSTATEIMAGEMASK( 1 );
			break;
		}
	case INDEXTOSTATEIMAGEMASK( 2 ):
		{
			lvi.state =INDEXTOSTATEIMAGEMASK( 2 ) ;
			break;
		}
	case 	INDEXTOSTATEIMAGEMASK( 3 ):
		{
			lvi.state=INDEXTOSTATEIMAGEMASK( 1 );
			break;
		}
	case  INDEXTOSTATEIMAGEMASK( 4 ):
		{
			lvi.state=INDEXTOSTATEIMAGEMASK( 2 ) ;
			break;
		}
	}

	SetItemState(m_nSelect,&lvi);
}

void CComplexSymbolLayerCtrl::CheckItem(int nItem)
{
	UINT state = GetItemState( nItem , LVIS_STATEIMAGEMASK );
	LV_ITEM lvi;
	lvi.mask =  LVIF_IMAGE | LVIF_STATE;
	lvi.iItem = nItem;
	lvi.iSubItem = 0;
	lvi.iImage = nItem;

	lvi.stateMask =LVIS_STATEIMAGEMASK | LVIS_DROPHILITED;

	switch (state)
	{
	case  INDEXTOSTATEIMAGEMASK( 1 ):
		{
			lvi.state =INDEXTOSTATEIMAGEMASK( 4 )|LVIS_DROPHILITED;
			m_IComplexSymbolLayerCtrl->UPdateSymbol(nItem,4);
			break;
		}
	case INDEXTOSTATEIMAGEMASK( 2 ):
		{			
			lvi.state =INDEXTOSTATEIMAGEMASK( 3 )|LVIS_DROPHILITED ;
			m_IComplexSymbolLayerCtrl->UPdateSymbol(nItem,3);
			break;
		}
	case 	INDEXTOSTATEIMAGEMASK( 3 ):
		{
			lvi.state=INDEXTOSTATEIMAGEMASK( 4 )|LVIS_DROPHILITED;
			m_IComplexSymbolLayerCtrl->UPdateSymbol(nItem,4);
			break;
		}
	case  INDEXTOSTATEIMAGEMASK( 4 ):
		{
			lvi.state=INDEXTOSTATEIMAGEMASK( 3 ) |LVIS_DROPHILITED;
			m_IComplexSymbolLayerCtrl->UPdateSymbol(nItem,3);
			break;
		}
	}

	SetItemState( nItem , &lvi );
}

void CComplexSymbolLayerCtrl::CheckItemEx(int nIndex)
{
	UINT state = GetItemState(nIndex,LVIS_STATEIMAGEMASK );
	LV_ITEM lvi;

	lvi.mask =  LVIF_IMAGE|LVIF_STATE;
	lvi.iItem = m_nSelect;
	lvi.iSubItem = 0;
	lvi.iImage = m_nSelect;
	lvi.pszText = "";
	lvi.stateMask = LVIS_DROPHILITED | LVIS_STATEIMAGEMASK;

	switch ( state )
	{
	case  INDEXTOSTATEIMAGEMASK(1):
		{
			lvi.state =INDEXTOSTATEIMAGEMASK(3)|LVIS_DROPHILITED;
			m_IComplexSymbolLayerCtrl->UPdateSymbol(m_nSelect,3);
			break;
		}
	case INDEXTOSTATEIMAGEMASK(2):
		{
			lvi.state =INDEXTOSTATEIMAGEMASK(4)|LVIS_DROPHILITED ;
			m_IComplexSymbolLayerCtrl->UPdateSymbol(m_nSelect,4);
			break;
		}
	case 	INDEXTOSTATEIMAGEMASK(3):
		{
			lvi.state=INDEXTOSTATEIMAGEMASK(3)|LVIS_DROPHILITED;
			m_IComplexSymbolLayerCtrl->UPdateSymbol(m_nSelect,3);
			break;
		}
	case  INDEXTOSTATEIMAGEMASK(4):
		{
			lvi.state=INDEXTOSTATEIMAGEMASK(4)|LVIS_DROPHILITED ;
			m_IComplexSymbolLayerCtrl->UPdateSymbol(m_nSelect,4);
			break;
		}
	}
	SetItemState(m_nSelect,&lvi);

}


void CComplexSymbolLayerCtrl::SetManageControl(IComplexSymbolLayerCtrlInterface * IComplexSymbolLayerCtrl)
{
	m_IComplexSymbolLayerCtrl = IComplexSymbolLayerCtrl;
}
int CComplexSymbolLayerCtrl::GetSelect()
{
	return m_nSelect;
}
void CComplexSymbolLayerCtrl::SetSelect(int nSelect)
{
	m_nSelect = nSelect;
}

