#pragma once
#include "IElement.h"

class CElementProperSheet :
	public CPropertySheet
{
	DECLARE_DYNAMIC(CElementProperSheet)
public:
	CElementProperSheet(CString name , CWnd *pWnd = NULL);
	~CElementProperSheet(void);

public:

	virtual INT_PTR DoModal()=0;

	virtual BOOL OnInitDialog();

	void SetElement(Element::IElementPtr pElement);

public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnApply();
	afx_msg void OnOK();

protected:
	Element::IElementPtr m_pElement;
};
