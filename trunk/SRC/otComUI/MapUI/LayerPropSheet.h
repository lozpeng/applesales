#pragma once

#include "ILayer.h"
#include "../ILayerPropCallback.h"

class CLayerPropSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CLayerPropSheet)
public:
	CLayerPropSheet(CString name , CWnd *pWnd = NULL);
	~CLayerPropSheet(void);
public:

	virtual INT_PTR DoModal();

	void SetLayer(Carto::ILayerPtr layer);

	void SetCallback(otComUI::ILayerPropCallback* pCallback){m_pCallback =pCallback;};
	
public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnApply();


	virtual BOOL OnInitDialog();
private:
	Carto::ILayerPtr m_layer;

	otComUI::ILayerPropCallback* m_pCallback;

};
