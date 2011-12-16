#pragma once


class CTransButton :
	public CButton
{
public:
	CTransButton(void);
	virtual ~CTransButton(void);

	DECLARE_MESSAGE_MAP()
public:
	
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

public:
	
};
