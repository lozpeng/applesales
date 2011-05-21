// SymbolListCtrl.cpp : 实现文件
//

#include "stdafx.h"
#include "SymbolList.h"
#include "CDC.h"


// CSymbolList

IMPLEMENT_DYNAMIC(CSymbolList, CListCtrl)
CSymbolList::CSymbolList()
{
	m_SymbolImage = NULL;
}

CSymbolList::~CSymbolList()
{
	m_mapSymbolArray.clear();
	if( m_SymbolImage != NULL)
	{
		int nCount = m_SymbolImage->GetImageCount();
		for ( int i=0 ; nCount<i ; i++ )
			m_SymbolImage->Remove( i );
		m_SymbolImage->DeleteImageList( );
		m_Bitmap.DeleteObject();
		delete m_SymbolImage;
		m_SymbolImage=NULL;
	}
}


BEGIN_MESSAGE_MAP(CSymbolList, CListCtrl)
	//	ON_NOTIFY_REFLECT(LVN_ITEMCHANGED, OnLvnItemchanged)
END_MESSAGE_MAP()


// CSymbolList 消息处理程序


void CSymbolList::AddSymbolArray(CString Name, vector<Display::ISymbolPtr>& pSymbolArray)
{
	m_Bitmap.DeleteObject();
	m_mapSymbolArray = pSymbolArray;

	CDC *dc;
	dc = GetDC();
	CDC MemDC;
	if(m_Bitmap.m_hObject)
	{
		m_Bitmap.DeleteObject();
	}
	m_Bitmap.CreateCompatibleBitmap(dc,m_LegendSize*pSymbolArray.size(),m_LegendSize);

	MemDC.CreateCompatibleDC(dc);
	CBitmap *pOldBmp=(CBitmap *)MemDC.SelectObject(&m_Bitmap);
	RECT rc1;
	rc1.top=rc1.left=0;
	rc1.right=m_LegendSize*pSymbolArray.size();
	rc1.bottom=m_LegendSize;
	CBrush brush(RGB(255,255,255));
	MemDC.FillRect( &rc1, &brush );
    brush.DeleteObject();

	Display::CDC *pDrawDC =new Display::CDC();
	pDrawDC->SetDC((long)MemDC.GetSafeHdc(), rc1.right, rc1.bottom);

	
	DIS_RECT rc;
	rc.top = rc.left = 0;
	rc.right = rc.bottom = m_LegendSize;
	HRGN hr = 0;
	long i;

	Display::ISymbolPtr pSymbol;
	for( i = 0 ; i < pSymbolArray.size() ; i++,rc.left+=m_LegendSize,rc.right+=m_LegendSize )
	{
		hr=CreateRectRgn(rc.left,rc.top,rc.right,rc.bottom);
		SelectClipRgn(MemDC.GetSafeHdc(),hr);
        
		pSymbol =pSymbolArray[i]->Clone() ;
		pSymbol->SelectDC(pDrawDC);
		pSymbol->SetReadyDraw();
		//通过符号绘制图例
		pSymbol->DrawLegend(&rc,0);

		SelectClipRgn(MemDC.GetSafeHdc(),NULL);
		if(hr!=0)
			DeleteObject(hr);
	}

	delete pDrawDC;

	MemDC.SelectObject(pOldBmp);
	MemDC.DeleteDC();
	
	ReleaseDC(dc);
	m_SymbolImage->Add( &m_Bitmap, RGB(255,254,253));

	long oldCount = GetItemCount();
	for( i = 0 ; i < pSymbolArray.size() ; i++ )
	{
		int iItem = InsertItem(  oldCount+i, pSymbolArray[i]->GetLabel().c_str() , oldCount+i);
		SetItemData( iItem , (DWORD)pSymbolArray[i].get() );
	}
}
void CSymbolList::AddSymbol(CString Name, Display::ISymbolPtr pInSymbol)
{
	CDC *dc;
	dc = GetDC();
	CDC MemDC;
	if(m_Bitmap.m_hObject)
	{
		m_Bitmap.DeleteObject();
	}
	m_Bitmap.CreateCompatibleBitmap(dc,m_LegendSize,m_LegendSize);

	MemDC.CreateCompatibleDC(dc);
	CBitmap *pOldBmp=(CBitmap *)MemDC.SelectObject(&m_Bitmap);
	RECT rc1;
	rc1.top=rc1.left=0;
	rc1.right=m_LegendSize;
	rc1.bottom=m_LegendSize;
	CBrush brush(RGB(255,255,255));
	MemDC.FillRect( &rc1, &brush );
	brush.DeleteObject();

	Display::CDC *pDrawDC =new Display::CDC();
	pDrawDC->SetDC((long)MemDC.GetSafeHdc(), rc1.right, rc1.bottom);


	DIS_RECT rc;
	rc.top = rc.left = 0;
	rc.right = rc.bottom = m_LegendSize;
	HRGN hr = 0;

	Display::ISymbolPtr pSymbol;

	hr=CreateRectRgn(rc.left,rc.top,rc.right,rc.bottom);
	SelectClipRgn(MemDC.GetSafeHdc(),hr);
	pSymbol =pInSymbol->Clone() ;
	pSymbol->SelectDC(pDrawDC);
	pSymbol->SetReadyDraw();

	//通过符号绘制图例
	pSymbol->DrawLegend(&rc,0);

	SelectClipRgn(MemDC.GetSafeHdc(),NULL);
	if(hr!=0)
		DeleteObject(hr);
	delete pDrawDC;

	MemDC.SelectObject(pOldBmp);
	MemDC.DeleteDC();

	ReleaseDC(dc);
	int iImge = m_SymbolImage->Add( &m_Bitmap, RGB(255,254,253));

	long lItemCont = GetItemCount();
	int iItem = InsertItem(  lItemCont, pSymbol->GetLabel().c_str() , iImge);
	SetItemData( iItem , (DWORD)pSymbol.get() );
}

void CSymbolList::SetImageSize(int Size)
{
	m_LegendSize = Size;
	if( m_SymbolImage!= NULL)
	{
		int nCount = m_SymbolImage->GetImageCount();
		for ( int i=0 ; i<=nCount ; i++ )
			m_SymbolImage->Remove( i );
		m_SymbolImage->DeleteImageList();
		delete m_SymbolImage;
		m_SymbolImage=NULL;
	}
	m_SymbolImage = new CImageList;
	m_SymbolImage->Create(m_LegendSize,m_LegendSize,ILC_COLOR24,1,1);
	SetImageList( m_SymbolImage , LVSIL_NORMAL   );

	SetImageList( m_SymbolImage , LVSIL_STATE  );
}

void CSymbolList::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{

	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	int nItem = lpDrawItemStruct->itemID;
	static _TCHAR szBuff[MAX_PATH];

	LV_ITEM lvi;
	lvi.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_STATE;
	lvi.iItem = nItem;
	lvi.iSubItem = 0;
	lvi.pszText = szBuff;
	lvi.cchTextMax = sizeof(szBuff);
	lvi.stateMask = 0xFFFF;     
	this->GetItem(&lvi);

	if (m_SymbolImage)
	{
		int nImg = lvi.iImage;
		if( nImg==0 )
		{
			nImg = 1;

		}
		CRect rcIcon;
		GetItemRect(nItem, rcIcon, LVSIL_NORMAL);
		BOOL bDraw = ImageList_DrawEx(m_SymbolImage->m_hImageList, lvi.iImage, pDC->m_hDC,  
			rcIcon.left,rcIcon.top , m_LegendSize , m_LegendSize ,CLR_DEFAULT, CLR_DEFAULT, ILD_TRANSPARENT );
	}

}

void CSymbolList::DelListCtrl(void)
{
	int nCount = m_SymbolImage->GetImageCount();
	for ( int i=0 ; i<=nCount ; i++ )
		m_SymbolImage->Remove( i );
	m_SymbolImage->DeleteImageList();
	delete m_SymbolImage;
	m_SymbolImage=NULL;
	m_SymbolImage=new CImageList;
	m_SymbolImage->Create(m_LegendSize,m_LegendSize,ILC_COLOR24,1,1);
	this->DeleteAllItems();
}


