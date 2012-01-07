#pragma once
#include "ElementProperSheet.h"

class CMarkerNorthArrowProperSheet :
	public CElementProperSheet
{
	DECLARE_DYNAMIC(CMarkerNorthArrowProperSheet)
public:
	CMarkerNorthArrowProperSheet(CString name , CWnd *pWnd = NULL);
	~CMarkerNorthArrowProperSheet(void);

public:

	virtual INT_PTR DoModal();

public:
	DECLARE_MESSAGE_MAP()

};
