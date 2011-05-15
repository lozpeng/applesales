#pragma once
#include "DashArray.h"

class CBCGPPropEx;
class  CSpinButtonCtrlEx :
	public CBCGPSpinButtonCtrl
{
public:
	CSpinButtonCtrlEx(CBCGPPropEx *pPropEx);
public:
	virtual ~CSpinButtonCtrlEx(void);

public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnCancelMode();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	afx_msg LRESULT OnMouseLeave(WPARAM,LPARAM);
	DECLARE_MESSAGE_MAP()
protected:
	CBCGPPropEx *m_pPropEx;
	
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	

};
