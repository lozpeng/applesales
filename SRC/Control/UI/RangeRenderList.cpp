// otRenderList.cpp : 实现文件
//

#include "stdafx.h"
#include "RangeRenderList.h"
#include "RangeRenderPage.h"
#include "IDisplay.h"

#ifdef DEBUG
#define new DEBUG_NEW
#endif

// CRangeRenderList

IMPLEMENT_DYNAMIC(CRangeRenderList, CListCtrl)

CRangeRenderList::CRangeRenderList()
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
	m_RangeRenderPage = NULL;

	m_LegendnWidth =m_LegendnHeight =16;


}

CRangeRenderList::~CRangeRenderList()
{
	if(m_SymbolImage)
	{
		m_SymbolImage->DeleteImageList();
		delete m_SymbolImage;
	}

}


BEGIN_MESSAGE_MAP(CRangeRenderList, CListCtrl)
	ON_NOTIFY_REFLECT(NM_CLICK, &CRangeRenderList::OnNMClick)
	ON_NOTIFY_REFLECT(NM_DBLCLK, &CRangeRenderList::OnNMDblclk)

END_MESSAGE_MAP()





void CRangeRenderList::InitCol()
{
	CRect rect;
	GetClientRect(rect);
	long lwidth =rect.Width();
	this->InsertColumn( 0, "符号", LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM, lwidth*0.2, 0 );
	this->InsertColumn( 1, "范围", LVCFMT_LEFT, lwidth*0.4, 0 );
	this->InsertColumn( 2, "值", LVCFMT_LEFT, lwidth*0.4, 0 );
	
}



void CRangeRenderList::AddItem(int nItem, int nSubItem, CString strName)
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

void CRangeRenderList::SetImgList(CImageList * pImgList)
{
	m_SymbolImage = pImgList ;
	if ( m_SymbolImage != NULL )
	{
		this->SetImageList( m_SymbolImage , LVSIL_NORMAL );
	}
}

void CRangeRenderList::AddImgList(CBitmap * hBitmap)
{
	m_SymbolImage->Add( hBitmap , RGB( 255 ,255 ,255 ) );
}

void CRangeRenderList::DeleteAll(void)
{
	if(m_SymbolImage)
	{
		int nCount = m_SymbolImage->GetImageCount();
		m_SymbolImage->DeleteImageList();
		delete m_SymbolImage;
	}
	m_SymbolImage = NULL;
	m_SymbolImage = new CImageList;
	m_SymbolImage->Create( m_LegendnWidth, m_LegendnHeight,  ILC_COLOR32, 1, 1 );
	this->DeleteAllItems();
}

void CRangeRenderList::SetbString(bool bStr)
{
	m_bString = bStr;
}

bool CRangeRenderList::GetbString(void)
{
	return m_bString;
}

void CRangeRenderList::OnNMClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	LPNMITEMACTIVATE phdr = reinterpret_cast< LPNMITEMACTIVATE >( pNMHDR );

	if( phdr->iItem == -1 )
	{
		return ;

	}

	m_iSubItem = phdr->iSubItem;
	if(m_RangeRenderPage != NULL)
	{
		((CRangeRenderPage *)m_RangeRenderPage)->ShowSymbol(phdr->iItem);
	}

	if( phdr->iItem >= 0 )
	{
		m_nSelect = phdr->iItem;
	}
}


void CRangeRenderList::CreateSymbolArrayBitmap(vector<Display::ISymbolPtr>& m_pSymbolArray)
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
void CRangeRenderList::SetImageSize(int nWidth , int nHeight)
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
void CRangeRenderList::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
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
LPCTSTR CRangeRenderList::MakeShortString(CDC* pDC, LPCTSTR lpszLong, int nColumnLen, int nOffset)
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
void CRangeRenderList::SetRangePage(void* pRangeRenderPage)
{
	m_RangeRenderPage = pRangeRenderPage;
}

void CRangeRenderList::OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	LPNMITEMACTIVATE phdr = reinterpret_cast< LPNMITEMACTIVATE >( pNMHDR );
	if( phdr->iItem == -1 )
	{
		return;
	}
	m_nSelect = phdr->iItem;
	if(m_RangeRenderPage != NULL && m_nSelect >= 0)
	{


		CRangeRenderPage* pPage =(CRangeRenderPage *)m_RangeRenderPage;

		if(pPage)
		{
			pPage->ModifySelItem(m_nSelect);
		}
	}
	*pResult = 0;
}


void CRangeRenderList::ReplaceSymbol(Display::ISymbolPtr pSymbol, int nItem)
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
HBITMAP CRangeRenderList::CoverBitmap( Display::ISymbolPtr pSymbol )
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

void CRangeRenderList::AddSymbolItem(Display::ISymbolPtr pSymbol, CString str, CString strLabel)
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

}




