#pragma once

#include "ILayer.h"

class CLayerPropSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CLayerPropSheet)
public:
	CLayerPropSheet(CString name , CWnd *pWnd = NULL);
	~CLayerPropSheet(void);
public:

	virtual INT_PTR DoModal();

	void SetLayer(Carto::ILayerPtr layer);
	
public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnApply();
	afx_msg void OnOK();


	virtual BOOL OnInitDialog();
private:
	Carto::ILayerPtr m_layer;

};
