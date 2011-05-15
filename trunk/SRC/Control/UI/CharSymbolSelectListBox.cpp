#include "StdAfx.h"
#include "CharSymbolSelectListBox.h"
#include "CharSymbolSelectDlg.h"
#include "IDisplay.h"


CCharSymbolSelectListBox::CCharSymbolSelectListBox(void)
{
	m_lItemHeight = 0;
	m_pCharDraw.reset( new Display::CCharMarkerSymbol );
	m_pCharDraw->SetMarkerSize(20);
	m_pCharDraw->SetMarkerColor(RGB(0,0,0));


	m_lNewSelectId = m_lOldSelectId = 1;
	m_bToolTipCreate = false;

	m_pSymbolSelectProp = NULL;
}

CCharSymbolSelectListBox::~CCharSymbolSelectListBox(void)
{
}
BEGIN_MESSAGE_MAP(CCharSymbolSelectListBox, CListBox)
	ON_WM_KILLFOCUS()
	ON_WM_TIMER()
	ON_WM_SETFOCUS()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()

void CCharSymbolSelectListBox::SetSymbolSelectProp(CCharSymbolSelectProp* pSymbolSelectProp)
{
	m_pSymbolSelectProp = pSymbolSelectProp;
}

void CCharSymbolSelectListBox::OnKillFocus(CWnd* pNewWnd)
{

}

void CCharSymbolSelectListBox::OnTimer(UINT_PTR nIDEvent)
{
	CListBox::OnTimer(nIDEvent);
}

void CCharSymbolSelectListBox::OnSetFocus(CWnd* pOldWnd)
{
	CListBox::OnSetFocus(pOldWnd);
	// TODO: 在此处添加消息处理程序代码
}

void CCharSymbolSelectListBox::SetCharMarkSymbol(Display::CCharMarkerSymbolPtr pCharMarkSymbol)
{
	m_pCharMarkSymbol = pCharMarkSymbol;
	if (m_pCharMarkSymbol != NULL)
	{
		m_pCharDraw->SetFaceName(m_pCharMarkSymbol->GetFaceName());
		m_pCharDraw->SetCharSet(m_pCharMarkSymbol->GetCharSet());
		m_pCharDraw->SetCharMap(*m_pCharMarkSymbol->GetCharMap());
		m_lNewSelectId = m_lOldSelectId = *m_pCharDraw->GetCharMap();
	}
}

void CCharSymbolSelectListBox::ReSetScorll(long lRow)
{
	CWnd* pScroll = GetScrollBarCtrl(SB_VERT);

	if (pScroll)
	{
		SetScrollRange (SB_VERT, 0, lRow);
		int selectRow = m_lNewSelectId / NUMSYMBOLPERROW; 
		SetScrollPos (SB_VERT, selectRow);
	}
}

void CCharSymbolSelectListBox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC* pDC;
	long lCurRow = 0; //当前行数
	long lNumSymbols = 0;
	long lStartSymbol = 0;

	pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	lCurRow = long(lpDrawItemStruct->itemID);//得到当前行数
	if (lCurRow < 0 || NULL == m_pCharDraw)
		return;

	lStartSymbol = lCurRow * NUMSYMBOLPERROW + 1;
	lNumSymbols = FONTSYMBOLNUMS;

	CPen nPen(PS_SOLID,2,RGB(0,0,0)), nSelPen(PS_SOLID,2,RGB(255,0,0)) , *pOldPen;

	Display::IDisplayPtr pDisplay ( new Display::IDisplay() );
	pDisplay->SetDC( (long)pDC->GetSafeHdc() , m_rect.Width() , m_rect.Height() );
	CPoint  pt;
	CRect rect;
	for(int i = lStartSymbol ; i <  lStartSymbol + NUMSYMBOLPERROW && i<= lNumSymbols ; ++i)
	{
		pt.x = (i - lStartSymbol) * m_lItemHeight;//先计算左上角
		pt.y = lpDrawItemStruct->rcItem.top;
		rect.SetRect(pt.x,pt.y,pt.x + m_lItemHeight,pt.y + m_lItemHeight);//计算矩形区域

		pt.x +=  m_lItemHeight/2;
		pt.y +=  m_lItemHeight/2;

		pOldPen = pDC->SelectObject(&nPen);	

		if (rect.top < 0)
		{
			continue;
		}

		if (rect.bottom > m_rect.bottom)
		{
			continue;
		}
		pDC->Rectangle(&rect); 

		pDC->SelectObject(pOldPen);

		if (m_lNewSelectId == i)
		{
			pOldPen = pDC->SelectObject(&nSelPen);	
			pDC->Rectangle(&rect);
			pDC->SelectObject(pOldPen);

			unsigned long color = m_pCharDraw->GetMarkColor();
		//	m_pCharDraw->SetMarkerColor(RGB(255 , 255 , 255));
			m_pCharDraw->SetCharMap(i);

			DIS_RECT drawRect;
			drawRect.left =rect.left;
			drawRect.right =rect.right;
			drawRect.top =rect.top;
			drawRect.bottom =rect.bottom;

			pDisplay->DrawLegend( m_pCharDraw.get() , &drawRect , 0 );
		//	m_pCharDraw->SetMarkerColor(color);

			if (m_ctrlToolTip.m_hWnd != NULL)
			{
				CString tip;
				tip.Format("Unicode:%d" , m_lNewSelectId);
				m_ctrlToolTip.AddTool(this , tip , &rect , 10);
				m_ctrlToolTip.Activate(TRUE);

			}
		}
		else
		{
			DIS_RECT drawRect;
			drawRect.left =rect.left;
			drawRect.right =rect.right;
			drawRect.top =rect.top;
			drawRect.bottom =rect.bottom;
			m_pCharDraw->SetCharMap(i);
			pDisplay->DrawLegend( m_pCharDraw.get() , &drawRect , 0 );
		}
	}

		
}

void CCharSymbolSelectListBox::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{

	CRect Rect;
	/*long lScrollBarWidth;*/

	//CWnd* pScroll = GetScrollBarCtrl(SB_VERT);
	//pScroll->GetClientRect(&ScrollRect);
	GetClientRect(&Rect);

	/*lScrollBarWidth = GetSystemMetrics(SM_CXVSCROLL) ;*/

	//mp_lItemHeight = ( Rect.Width() - lScrollBarWidth )/4.0;
	m_lItemHeight = (long)((Rect.Width())*1./NUMSYMBOLPERROW);
	lpMeasureItemStruct->itemHeight = m_lItemHeight;
}

int CCharSymbolSelectListBox::CompareItem(LPCOMPAREITEMSTRUCT /*lpCompareItemStruct*/)
{

	// TODO:  添加您的代码以确定指定项的排序顺序
	// 返回 -1 表示项 1 排在项 2 之前
	// 返回 0 表示项 1 和项 2 顺序相同
	// 返回 1 表示项 1 排在项 2 之后

	return 0;
}


void CCharSymbolSelectListBox::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (!m_bToolTipCreate)
	{
		BOOL flag = m_ctrlToolTip.Create(this , TTS_NOPREFIX);
		if (flag)
		{
			m_bToolTipCreate = true;
			m_ctrlToolTip.SetDelayTime(50);
		}
	}
	
	long lScrollPos = 0;
	long lNewSelectId = 0;
	//得到滚动条位置
	lScrollPos = GetScrollPos(SB_VERT);
	lNewSelectId = SnapGrid(lScrollPos,point);
	if(-1 !=  lNewSelectId)
		SetNewSelectId(lNewSelectId);
	CListBox::OnLButtonDown(nFlags, point);
}

int CCharSymbolSelectListBox::SnapGrid(long lRowOffset, CPoint point)
{
	long lNewSelectId = 0;
	long lNumSymbols = 0;
	int iRow = 0;
	int iLei  = 0;
	iRow = point.y /m_lItemHeight + lRowOffset;
	iLei = point.x /m_lItemHeight;	
	lNewSelectId = (iRow * NUMSYMBOLPERROW) + iLei + 1;
	lNumSymbols = FONTSYMBOLNUMS;
	if(lNewSelectId <= lNumSymbols)
		return lNewSelectId;
	else
		return -1;

}

void CCharSymbolSelectListBox::SetNewSelectId(long lNewSelectId)
{
	long preId = m_lNewSelectId;
	m_lNewSelectId = lNewSelectId;
	CRect RectOld,RectNew;
	DIS_RECT rectOld, rectNew;
	
	if(m_lNewSelectId != m_lOldSelectId)
	{
		UpdateWindow();

		//old
		GetItemRect((m_lOldSelectId - 1) / NUMSYMBOLPERROW, &RectOld);										
			
		RectOld.left = RectOld.left + (m_lOldSelectId - 1) % NUMSYMBOLPERROW * m_lItemHeight;
		RectOld.right = RectOld.left + m_lItemHeight;

		rectOld.left = RectOld.left;
		rectOld.right = RectOld.right;
		rectOld.top = RectOld.top;
		rectOld.bottom = RectOld.bottom;
		
		//new
		GetItemRect((m_lNewSelectId - 1) / NUMSYMBOLPERROW, &RectNew);

		RectNew.left = RectNew.left + (m_lNewSelectId - 1) % NUMSYMBOLPERROW * m_lItemHeight;
		RectNew.right = RectNew.left + m_lItemHeight;

		rectNew.left = RectNew.left;
		rectNew.right = RectNew.right;
		rectNew.top = RectNew.top;
		rectNew.bottom = RectNew.bottom;

		//draw
		CDC * pDC = GetDC();
		COLORREF bgCr = pDC->GetBkColor();
		Display::IDisplayPtr pDisplay ( new Display::IDisplay);
		pDisplay->SetDC( (long)pDC->GetSafeHdc() , m_rect.Width() , m_rect.Height() );
	
		CPen* pOldPen;
		//绘制旧
		CPen nPen(PS_SOLID,2,RGB(0,0,0)) ;
		pOldPen = pDC->SelectObject(&nPen);	
		pDC->Rectangle(&RectOld); 
		pDC->SelectObject(pOldPen);

		m_pCharDraw->SetCharMap(m_lOldSelectId);	
		pDisplay->DrawLegend( m_pCharDraw.get() , &rectOld , 0 );

		//绘制新
		CPen nNewPen(PS_SOLID,2,RGB(255,0,0));
		pOldPen = pDC->SelectObject(&nNewPen);	
		pDC->Rectangle(&RectNew); 
		pDC->SelectObject(pOldPen);

		m_pCharDraw->SetCharMap(m_lNewSelectId);		
		pDisplay->DrawLegend( m_pCharDraw.get() , &rectNew , 0 );
		
		ReleaseDC(pDC);
		UpdateWindow();

		m_lOldSelectId = preId;
	}
	
}
void CCharSymbolSelectListBox::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CListBox::OnRButtonDown(nFlags, point);
	((CCharSymbolSelectDlg*)this->GetParent())->EndDialog(IDOK);
}

void CCharSymbolSelectListBox::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CListBox::OnLButtonDblClk(nFlags, point);
	m_pCharMarkSymbol->SetCharMap(m_lNewSelectId);
	if (m_pSymbolSelectProp != NULL)
	{
		m_pSymbolSelectProp->SetValue((unsigned long)m_lNewSelectId);
	}
	
	((CCharSymbolSelectDlg*)this->GetParent())->EndDialog(IDOK);
}

BOOL CCharSymbolSelectListBox::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	// TODO: 在此添加专用代码和/或调用基类
	return CListBox::OnWndMsg(message, wParam, lParam, pResult);
}

BOOL CCharSymbolSelectListBox::PreTranslateMessage(MSG* pMsg)
{
	if (NULL != m_ctrlToolTip.m_hWnd)            
		m_ctrlToolTip.RelayEvent(pMsg);


	return CListBox::PreTranslateMessage(pMsg);
}
