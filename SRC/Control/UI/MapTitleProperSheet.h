#pragma once
#include "ElementProperSheet.h"

class CMapTitleProperSheet :
	public CElementProperSheet
{
	DECLARE_DYNAMIC(CMapTitleProperSheet)
public:
	CMapTitleProperSheet(CString name , CWnd *pWnd = NULL);
	~CMapTitleProperSheet(void);

public:

	virtual INT_PTR DoModal();

public:
	DECLARE_MESSAGE_MAP()

};
