#pragma once
#include "IElement.h"
#include "../ILayerPropCallback.h"
#include "Map.h"

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

	void SetElement(Element::IElementPtr pElement,Carto::CMap* pMap,otComUI::ILayerPropCallback *pCallBack);


public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnApply();
	afx_msg void OnOK();

protected:
	Element::IElementPtr m_pElement;

    otComUI::ILayerPropCallback *m_pCallBack;
	Carto::CMap* m_pMap;
};
