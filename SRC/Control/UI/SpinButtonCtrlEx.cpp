#include "stdafx.h"
#include "SpinButtonCtrlEx.h"
#include "SymbolPropList.h"
static int downPress = 0;
CSpinButtonCtrlEx::CSpinButtonCtrlEx(CBCGPPropEx *pPropEx)
{
	m_pPropEx = pPropEx;
		
}

CSpinButtonCtrlEx::~CSpinButtonCtrlEx(void)
{
}
BEGIN_MESSAGE_MAP(CSpinButtonCtrlEx, CSpinButtonCtrl)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_CANCELMODE()
	ON_WM_MOUSEMOVE()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
END_MESSAGE_MAP()
//static bool upDate = false;
void CSpinButtonCtrlEx::OnLButtonDown(UINT nFlags, CPoint point)
{
//	SetCapture();
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	int nRow;
	int nUpper;
	this->GetRange(nRow, nUpper);
	/*
	*�жϱ༭���е������Ƿ�Ϸ�
	*/
	CString strNum;
	this->GetBuddy()->GetWindowText(strNum);

		CRect Rect;
		this->GetWindowRect (&Rect);
		if( strNum.Find('.') > 0 )
		{
			int nDotpos = strNum.Find('.');
			strNum = strNum.Left(nDotpos+1);
			int pos = atoi(strNum);
			if(point.y <((Rect.bottom-Rect.top)/2))
			{
				this->SetPos(pos);
			}
			else
			{
				this->SetPos(pos + 1); 
			}
		}
		else
		{
			int pos = atoi(strNum);
			this->SetPos(pos);
		}

	CBCGPSpinButtonCtrl::OnLButtonDown(nFlags, point);
	downPress++;	
	
	m_pPropEx->OnUpdateValue();
//	ReleaseCapture(); 
}

void CSpinButtonCtrlEx::OnPaint() 
{
	CBCGPSpinButtonCtrl::OnPaint();

}

//*****************************************************************************************
void CSpinButtonCtrlEx::OnLButtonUp(UINT nFlags, CPoint point) 
{
	SetCapture();
//	_variant_t value = m_pPropEx->GetValue();
	CBCGPSpinButtonCtrl::OnLButtonUp( nFlags , point );
		downPress--;
	m_pPropEx->OnUpdateValue();
	 ReleaseCapture(); 

}
//*****************************************************************************************
void CSpinButtonCtrlEx::OnCancelMode() 
{
	CBCGPSpinButtonCtrl::OnCancelMode();
}
//*****************************************************************************************
void CSpinButtonCtrlEx::OnMouseMove(UINT nFlags, CPoint point) 
{
	ReleaseCapture();
	CBCGPSpinButtonCtrl::OnMouseMove( nFlags , point );
}
//*****************************************************************************************
LRESULT CSpinButtonCtrlEx::OnMouseLeave(WPARAM wParam,LPARAM lParam)
{	
	return CBCGPSpinButtonCtrl::OnMouseLeave( wParam , lParam );
}
//*********************************************************************************
BOOL CSpinButtonCtrlEx::OnEraseBkgnd(CDC* pDC) 
{
	return CBCGPSpinButtonCtrl::OnEraseBkgnd(pDC);
}
BOOL CSpinButtonCtrlEx::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	/*switch(pMsg->message)
	{
	case WM_KICKIDLE:
		  {
			  Sleep(1);
		  }
		break;
	default:
	    break;
	}*/
	return CBCGPSpinButtonCtrl::PreTranslateMessage(pMsg);
}


