#pragma once
#include "afxwin.h"

#include "ButtonInfo.h"
#include "TransButton.h"

class CButtonContainer :
	public CWnd
{
	DECLARE_DYNAMIC(CButtonContainer)
public:
	CButtonContainer(void);
	~CButtonContainer(void);
	DECLARE_MESSAGE_MAP()
public:

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
public:
	void SetButtonInfo(std::vector<stProduct> &ButtonInfo);

	void AddButtonInfo(stProduct &info) {m_ButtonInfo.push_back(info);}
private:
	std::vector<stProduct> m_ButtonInfo;
	std::vector<CTransButton*>  m_buttons;
};
