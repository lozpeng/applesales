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
	if(!m_mapSymbolArray.empty())
	{
		for ( iterator it = m_mapSymbolArray.begin() ; it != m_mapSymbolArray.end() ; it++ )
		{
			it->second->RemoveAll();
		}
		m_mapSymbolArray.clear();
	}
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


void CSymbolList::AddSymbolArray(CString Name, Display::ISymbolArrayPtr pSymbolArray)
{
	m_Bitmap.DeleteObject();
	m_mapSymbolArray[Name] = pSymbolArray;

	CDC *dc;
	dc = GetDC();
	CDC MemDC;
	m_Bitmap.CreateCompatibleBitmap(dc,m_LegendSize*pSymbolArray->GetSize(),m_LegendSize);

	MemDC.CreateCompatibleDC(dc);
	CBitmap *pOldBmp=(CBitmap *)MemDC.SelectObject(&m_Bitmap);
	RECT rc1;
	rc1.top=rc1.left=0;
	rc1.right=m_LegendSize*pSymbolArray->GetSize();
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
	for( i = 0 ; i < pSymbolArray->GetSize() ; i++,rc.left+=m_LegendSize,rc.right+=m_LegendSize )
	{
		hr=CreateRectRgn(rc.left,rc.top,rc.right,rc.bottom);
		SelectClipRgn(MemDC.GetSafeHdc(),hr);
        
		pSymbol =pSymbolArray->GetAt(i);
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
	
	ReleaseDC(dc);
	m_SymbolImage->Add( &m_Bitmap, RGB(255,254,253));

	long oldCount = GetItemCount();
	for( i = 0 ; i < pSymbolArray->GetSize() ; i++ )
	{
		int iItem = InsertItem(  oldCount+i, pSymbolArray->GetAt(i)->GetLabel().c_str() , oldCount+i);
		SetItemData( iItem , (DWORD)pSymbolArray->GetAt(i).get() );
	}
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
	m_SymbolImage->Create(m_LegendSize,m_LegendSize,ILC_COLOR32,1,1);
	SetImageList( m_SymbolImage , LVSIL_NORMAL );
}
/*
void CSymbolList::OnLvnItemchanged(NMHDR *pNMHDR, LRESULT *pResult)
{
LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
// TODO: 在此添加控件通知处理程序代码
*pResult = 0;

}*/



void CSymbolList::DelListCtrl(void)
{
	int nCount = m_SymbolImage->GetImageCount();
	for ( int i=0 ; i<=nCount ; i++ )
		m_SymbolImage->Remove( i );
	m_SymbolImage->DeleteImageList();
	delete m_SymbolImage;
	m_SymbolImage=NULL;
	m_SymbolImage=new CImageList;
	m_SymbolImage->Create(m_LegendSize,m_LegendSize,ILC_COLOR32,1,1);
	this->DeleteAllItems();
}
