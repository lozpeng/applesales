// otRenderList.cpp : 实现文件
//

#include "stdafx.h"
#include "UniqueRenderList.h"
#include "UniqueRenderPage.h"
#include "IDisplay.h"
#include "DlgModifyUniClass.h"

#ifdef DEBUG
#define new DEBUG_NEW
#endif
// CUniquerRenderSymbolList

IMPLEMENT_DYNAMIC(CUniquerRenderSymbolList, CListCtrl)

CUniquerRenderSymbolList::CUniquerRenderSymbolList()
{
	m_SymbolImage = NULL;
	m_nSelect = 0;
	m_bFullRowSel = FALSE;
	m_bClientWidthSel = TRUE;
	m_cxClient = 0;
	m_cxStateImageOffset = 0;
	m_clrText = ::GetSysColor(COLOR_WINDOWTEXT);
	m_clrTextBk = ::GetSysColor(COLOR_WINDOW);
	m_clrBkgnd = ::GetSysColor(COLOR_WINDOW);
	m_UniqueRenderPage = NULL;

	m_LegendnWidth =m_LegendnHeight =16;


}

CUniquerRenderSymbolList::~CUniquerRenderSymbolList()
{
	if(m_SymbolImage)
	{
		m_SymbolImage->DeleteImageList();
		delete m_SymbolImage;
	}
	
}


BEGIN_MESSAGE_MAP(CUniquerRenderSymbolList, CListCtrl)
	ON_NOTIFY_REFLECT(NM_CLICK, &CUniquerRenderSymbolList::OnNMClick)
	ON_NOTIFY_REFLECT(NM_DBLCLK, &CUniquerRenderSymbolList::OnNMDblclk)

END_MESSAGE_MAP()





void CUniquerRenderSymbolList::InitCol()
{
	CRect rect;
	GetClientRect(rect);
	long lwidth =rect.Width();
	this->InsertColumn( 0, "符号", LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM, lwidth*0.2, 0 );
	this->InsertColumn( 1, "值", LVCFMT_LEFT, lwidth*0.3, 0 );
	this->InsertColumn( 2, "标签", LVCFMT_LEFT, lwidth*0.3, 0 );
	this->InsertColumn( 3, "数量", LVCFMT_LEFT, lwidth*0.2, 0 );
	/*this->InsertColumn( 1, "值", LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM|LVCFMT_LEFT, lwidth*0.3, 0 );
	this->InsertColumn( 2, "标签", LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM|LVCFMT_LEFT, lwidth*0.3, 0 );
	this->InsertColumn( 3, "数量", LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM|LVCFMT_LEFT, lwidth*0.2, 0 );*/
}

void CUniquerRenderSymbolList::InsertItemEX(int nItem, CString str,CString strLabel,  CString strCount)
{
	LV_ITEM lvi;

	lvi.mask = /*LVIF_TEXT |*/ LVIF_IMAGE /*| LVIF_STATE*/;
	lvi.iItem = nItem;
	lvi.iSubItem = 0;
	//		lvi.pszText = _gszItem[i][0];
	lvi.iImage = nItem;
	//lvi.stateMask = LVIS_STATEIMAGEMASK;
	//lvi.state = INDEXTOSTATEIMAGEMASK(1);
	InsertItem( &lvi );
	AddItem( nItem, 1, str);
	AddItem( nItem, 2, strLabel );
	
	AddItem( nItem, 3, strCount );
}

void CUniquerRenderSymbolList::AddItem(int nItem, int nSubItem, CString strName)
{
	LV_ITEM lvi;
	lvi.mask =  LVIF_TEXT;
	lvi.iItem = nItem;
	lvi.iSubItem = nSubItem;
	//lvi.pszText = new char[strName.GetLength()+1];
 //   lvi.pszText[strName.GetLength()] ='\0';
	//strcpy(lvi.pszText,strName);
	lvi.pszText =strName.GetBuffer();
	this->SetItem(&lvi);
}

void CUniquerRenderSymbolList::SetImgList(CImageList * pImgList)
{
	m_SymbolImage = pImgList ;
	if ( m_SymbolImage != NULL )
	{
		this->SetImageList( m_SymbolImage , LVSIL_NORMAL );
	}
}

void CUniquerRenderSymbolList::AddImgList(CBitmap * hBitmap)
{
	m_SymbolImage->Add( hBitmap , RGB( 255 ,255 ,255 ) );
}

void CUniquerRenderSymbolList::DeleteAll(void)
{
	int nCount = m_SymbolImage->GetImageCount();

	m_SymbolImage->DeleteImageList();

	delete m_SymbolImage;
	m_SymbolImage = NULL;
	m_SymbolImage = new CImageList;
	m_SymbolImage->Create( m_LegendnWidth, m_LegendnHeight,  ILC_COLOR32, 1, 1 );
	this->DeleteAllItems();
}

void CUniquerRenderSymbolList::SetbString(bool bStr)
{
	m_bString = bStr;
}

bool CUniquerRenderSymbolList::GetbString(void)
{
	return m_bString;
}

void CUniquerRenderSymbolList::OnNMClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	LPNMITEMACTIVATE phdr = reinterpret_cast< LPNMITEMACTIVATE >( pNMHDR );

	if( phdr->iItem == -1 )
	{
		return ;

	}

	m_iSubItem = phdr->iSubItem;
	if(m_UniqueRenderPage != NULL)
	{
		((CUniqueRenderPage *)m_UniqueRenderPage)->ShowSymbol(GetItemText(phdr->iItem,1));
	}
	
	if( phdr->iItem >= 0 )
	{
		m_nSelect = phdr->iItem;
	}
}


void CUniquerRenderSymbolList::CreateSymbolArrayBitmap(vector<Display::ISymbolPtr>& m_pSymbolArray)
{
	

	m_Bitmap.DeleteObject();
	Display::IDisplay SimpleDisplay;
	CDC * dc = GetDC();
	CDC MemDC;
	CString Str1;
	BOOL b = m_Bitmap.CreateCompatibleBitmap(dc,m_LegendnWidth*m_pSymbolArray.size(),m_LegendnHeight);
	MemDC.CreateCompatibleDC(dc);

	CBitmap *pOldBmp=(CBitmap *)MemDC.SelectObject(&m_Bitmap);
	RECT rc1;
	rc1.top=rc1.left=0;
	rc1.right=m_LegendnWidth*m_pSymbolArray.size();
	rc1.bottom=m_LegendnHeight;
	CBrush brush(RGB(255,254,253));
	MemDC.FillRect( &rc1, &brush );

	SimpleDisplay.SetBgColor(RGB(255,255,255));
	SimpleDisplay.SetDC( (long)MemDC.GetSafeHdc(), rc1.right, rc1.bottom );
	DIS_RECT rc;
	rc.left = rc.top = 0;
	rc.right = m_LegendnWidth;
	rc.bottom= m_LegendnHeight;
	HRGN hr = 0;
	long i,lCount =  m_pSymbolArray.size();

	for( i = 0 ; i < lCount ; i++,rc.left+=m_LegendnWidth,rc.right+=m_LegendnWidth )
	{
		hr=CreateRectRgn(rc.left,rc.top,rc.right,rc.bottom);
		SelectClipRgn(MemDC.GetSafeHdc(),hr);
		SimpleDisplay.DrawLegend( m_pSymbolArray[i].get() , &rc, 0 ); 
		SelectClipRgn(MemDC.GetSafeHdc(),NULL);
		if(hr!=0)
			DeleteObject(hr);
	}

	MemDC.SelectObject(pOldBmp);
	DeleteDC(MemDC);
	int p = m_SymbolImage->Add( &m_Bitmap, RGB(255,255,255));

	SelectClipRgn(MemDC.GetSafeHdc(),NULL);
	ReleaseDC(dc);
	long oldCount = GetItemCount();
}
void CUniquerRenderSymbolList::SetImageSize(int nWidth , int nHeight)
{
	m_LegendnWidth = nWidth;
	m_LegendnHeight = nHeight;
	if(m_SymbolImage)
	{
		m_SymbolImage->DeleteImageList();
		delete m_SymbolImage;
	}
	m_SymbolImage = new CImageList;
	m_SymbolImage->Create( nWidth, nHeight, ILC_COLOR32, 1, 1 );
	SetImageList( m_SymbolImage , LVSIL_NORMAL );
}
#define OFFSET_FIRST    2
#define OFFSET_OTHER    6
void CUniquerRenderSymbolList::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{

	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	CRect rcItem(lpDrawItemStruct->rcItem);
	UINT uiFlags = ILD_TRANSPARENT;
	CImageList* pImageList;
	int nItem = lpDrawItemStruct->itemID;
	BOOL bFocus = (GetFocus() == this);
	COLORREF clrTextSave = 0;
	COLORREF clrBkSave = 0;
	COLORREF clrImage = m_clrBkgnd;
	static _TCHAR szBuff[MAX_PATH];
	LPCTSTR pszText;

	//绘制Item

	LV_ITEM lvi;
	lvi.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_STATE;
	lvi.iItem = nItem;
	lvi.iSubItem = 0;
	lvi.pszText = szBuff;
	lvi.cchTextMax = sizeof(szBuff);
	lvi.stateMask = 0xFFFF;     
	this->GetItem(&lvi);

	BOOL bSelected = /*bFocus || *//*(GetStyle() & LVS_SHOWSELALWAYS)) &&*/ lvi.state & LVIS_SELECTED;
	bSelected = bSelected || (lvi.state & LVIS_DROPHILITED);



	CRect rcAllLabels;
	GetItemRect(nItem, rcAllLabels, LVIR_BOUNDS);

	CRect rcLabel;
	GetItemRect(nItem, rcLabel, LVIR_LABEL);
	//排除图片位置
	rcAllLabels.left = rcLabel.left;
	if (m_bClientWidthSel && rcAllLabels.right<m_cxClient)
		rcAllLabels.right = m_cxClient;
	rcAllLabels.left = rcLabel.right;
	//绘制选中区域
	if (bSelected)
	{
		clrTextSave = pDC->SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT));
		clrBkSave = pDC->SetBkColor(::GetSysColor(COLOR_HIGHLIGHT));

		CBrush cbr(::GetSysColor(COLOR_HIGHLIGHT));
		pDC->FillRect(rcAllLabels, &cbr);
	}
	else
	{
		CBrush cbr(m_clrTextBk);
		pDC->FillRect(rcAllLabels, &cbr);
	}

	//设置选中颜色

	if (lvi.state & LVIS_CUT)
	{
		clrImage = m_clrBkgnd;
		uiFlags |= ILD_BLEND50;
	}
	else if (bSelected)
	{
		clrImage = ::GetSysColor( COLOR_HIGHLIGHT );
		uiFlags |= ILD_BLEND50;
	}

	//绘制图片

	pImageList = GetImageList(LVSIL_NORMAL);
	if (pImageList)
	{

		if (pImageList)
		{
			int nImg = lvi.iImage;
			if( nImg==0 )
			{
				nImg = 1;

			}
			CRect rcIcon;
			GetItemRect(nItem, rcIcon, LVSIL_NORMAL);
			BOOL bDraw = ImageList_DrawEx(pImageList->m_hImageList, lvi.iImage, pDC->m_hDC,  
				rcIcon.left,rcIcon.top , m_LegendnWidth , m_LegendnHeight ,CLR_DEFAULT, CLR_DEFAULT, ILD_TRANSPARENT );
		}
	}



	//绘制文字

	GetItemRect(nItem, rcItem, LVIR_LABEL);
	rcItem.right -= m_cxStateImageOffset;

	pszText = MakeShortString(pDC, szBuff,
		rcItem.right-rcItem.left, 2*OFFSET_FIRST);

	rcLabel = rcItem;
	rcLabel.left += OFFSET_FIRST;
	rcLabel.right -= OFFSET_FIRST;

	pDC->DrawText(pszText,-1,rcLabel,DT_LEFT | DT_SINGLELINE | DT_NOPREFIX | DT_NOCLIP | DT_VCENTER);


	LV_COLUMN lvc;
	lvc.mask = LVCF_FMT | LVCF_WIDTH;

	for(int nColumn = 1; GetColumn(nColumn, &lvc); nColumn++)
	{
		rcItem.left = rcItem.right;
		rcItem.right += lvc.cx;

		int nRetLen =GetItemText(nItem, nColumn,
			szBuff, sizeof(szBuff));
		if (nRetLen == 0)
			continue;

		pszText = MakeShortString(pDC, szBuff,
			rcItem.right - rcItem.left, 2*OFFSET_OTHER);

		UINT nJustify = DT_LEFT;

		if(pszText == szBuff)
		{
			switch(lvc.fmt & LVCFMT_JUSTIFYMASK)
			{
			case LVCFMT_RIGHT:
				nJustify = DT_RIGHT;
				break;
			case LVCFMT_CENTER:
				nJustify = DT_CENTER;
				break;
			default:
				break;
			}
		}

		rcLabel = rcItem;
		rcLabel.left += OFFSET_OTHER;
		rcLabel.right -= OFFSET_OTHER;

		pDC->DrawText(pszText, -1, rcLabel,
			nJustify | DT_SINGLELINE | DT_NOPREFIX | DT_NOCLIP | DT_VCENTER);
	}

	if (lvi.state & LVIS_FOCUSED && bFocus)
		pDC->DrawFocusRect(rcAllLabels);


	if (bSelected)
	{
		pDC->SetTextColor(clrTextSave);
		pDC->SetBkColor(clrBkSave);
	}
}
LPCTSTR CUniquerRenderSymbolList::MakeShortString(CDC* pDC, LPCTSTR lpszLong, int nColumnLen, int nOffset)
{
	static const _TCHAR szThreeDots[] = _T("...");

	int nStringLen = lstrlen(lpszLong);

	if(nStringLen == 0 ||
		(pDC->GetTextExtent(lpszLong, nStringLen).cx + nOffset) <= nColumnLen)
	{
		return(lpszLong);
	}

	static _TCHAR szShort[MAX_PATH];

	_tcsncpy_s(szShort,MAX_PATH,lpszLong,_TRUNCATE);
	int nAddLen = pDC->GetTextExtent(szThreeDots,sizeof(szThreeDots)).cx;

	for(int i = nStringLen-1; i > 0; i--)
	{
		szShort[i] = 0;
		if((pDC->GetTextExtent(szShort, i).cx + nOffset + nAddLen)
			<= nColumnLen)
		{
			break;
		}
	}

	_tcscat_s(szShort, MAX_PATH, szThreeDots);
	return(szShort);
}
void CUniquerRenderSymbolList::SetUniquePage(void* pUniqueRenderPage)
{
	m_UniqueRenderPage = pUniqueRenderPage;
}

void CUniquerRenderSymbolList::OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	LPNMITEMACTIVATE phdr = reinterpret_cast< LPNMITEMACTIVATE >( pNMHDR );
	if( phdr->iItem == -1 )
	{
		return;
	}
	m_nSelect = phdr->iItem;
	if(m_UniqueRenderPage != NULL && m_nSelect >= 0)
	{
		

		CUniqueRenderPage* pPage =(CUniqueRenderPage *)m_UniqueRenderPage;

		if(pPage)
		{
			pPage->ModifySelItem(m_nSelect);
		}
	}
	*pResult = 0;
}

void CUniquerRenderSymbolList::DelItem(int nItem)
{
	this->DeleteItem( nItem );
}

void CUniquerRenderSymbolList::ReplaceSymbol(Display::ISymbolPtr pSymbol, int nItem)
{
	HBITMAP TempBitmap = CoverBitmap( pSymbol );
	CBitmap * bitmap = CBitmap::FromHandle( TempBitmap );
	CDC * dc=GetDC();
	CDC MemDC;//创建相容的bitmap和dc
	HBITMAP hbitmap = CreateCompatibleBitmap( dc->GetSafeHdc(), m_LegendnWidth, m_LegendnHeight );
	HBITMAP hBitmapTemp;
	MemDC.CreateCompatibleDC( dc );
	hBitmapTemp=( HBITMAP )SelectObject( MemDC, hbitmap );

	RECT rc1;
	rc1.top = rc1.left = 0;
	rc1.right = m_LegendnWidth;
	rc1.bottom = m_LegendnHeight;
	CBrush brush( RGB(255,254,253) );
	MemDC.FillRect( &rc1, &brush );
	CBitmap * Maskbitmap = CBitmap::FromHandle( hbitmap );
	m_SymbolImage->Replace( nItem, bitmap , Maskbitmap );
	bitmap->Detach();
	Maskbitmap->Detach();
	DeleteObject( TempBitmap );
	DeleteObject( hbitmap );

	Invalidate(FALSE);
}

//产生一个Symbol的图片
HBITMAP CUniquerRenderSymbolList::CoverBitmap( Display::ISymbolPtr pSymbol )
{
	Display::IDisplay SimpleDisplay;
	CDC * dc=GetDC();
	CDC MemDC;//创建相容的bitmap和dc
	HBITMAP hbitmap = CreateCompatibleBitmap( dc->GetSafeHdc(), m_LegendnWidth, m_LegendnHeight );
	HBITMAP hBitmapTemp;
	MemDC.CreateCompatibleDC( dc );
	hBitmapTemp=( HBITMAP )SelectObject( MemDC, hbitmap );

	RECT rc1;
	rc1.top = rc1.left = 0;
	rc1.right = m_LegendnWidth;
	rc1.bottom = m_LegendnHeight;
	CBrush brush( RGB(255,254,253) );
	MemDC.FillRect( &rc1, &brush );

	SimpleDisplay.SetBgColor( RGB(255,255,255) );
	SimpleDisplay.SetDC( (long)MemDC.GetSafeHdc(), rc1.right, rc1.bottom );
	DIS_RECT rc;
	rc.left = rc.top = 0;
	rc.right = m_LegendnWidth;
	rc.bottom= m_LegendnHeight;
	HRGN hr = 0;
	SimpleDisplay.DrawLegend( pSymbol.get(), &rc, 0 );
	hbitmap=(HBITMAP)SelectObject(MemDC.m_hDC,hBitmapTemp);
	MemDC.DeleteDC();
	return hbitmap;
}

void CUniquerRenderSymbolList::AddSymbolItem(Display::ISymbolPtr pSymbol, CString str, CString strLabel, CString strCount)
{
	HBITMAP TempBitmap = CoverBitmap( pSymbol );
	CBitmap bitmap;
	bitmap.Attach(TempBitmap);

	int nindex =m_SymbolImage->Add(&bitmap,RGB(255,255,255));

    int nItem =GetItemCount();
	LV_ITEM lvi;

	lvi.mask = /*LVIF_TEXT |*/ LVIF_IMAGE /*| LVIF_STATE*/;
	lvi.iItem = nItem;
	lvi.iSubItem = 0;
	lvi.iImage = nindex;

	InsertItem( &lvi );
	AddItem( nItem, 1, str);
	AddItem( nItem, 2, strLabel );
	
	AddItem( nItem, 3, strCount );


}

void CUniquerRenderSymbolList::ReposItem(int oldpos, int newpos)
{
	LV_ITEM lvi,nlvi;


	lvi.iItem = oldpos;
	lvi.iSubItem = 0;
	lvi.mask = LVIF_IMAGE | LVIF_STATE;
	lvi.stateMask =(UINT)-1;   

	//获得要移动项的信息
	GetItem(&lvi);

	//获得目标项的信息
	nlvi.iItem =newpos;
	nlvi.iSubItem =0;
	nlvi.mask = LVIF_IMAGE | LVIF_STATE;
	nlvi.stateMask =(UINT)-1;  
	GetItem(&nlvi);

	lvi.iItem =newpos;
	SetItem(&lvi);

	nlvi.iItem =oldpos;
	SetItem(&nlvi);

	CString str;
    for(int i=1;i<=3;i++)
	{
       str =GetItemText(oldpos,i);
	   SetItemText(oldpos,i,GetItemText(newpos,i));
	   SetItemText(newpos,i,str);
	}
	
	Invalidate(FALSE);

	
	
}


