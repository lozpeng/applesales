#pragma once
#include "ElementProperSheet.h"

class CSimpleElementProperSheet :
	public CElementProperSheet
{
	DECLARE_DYNAMIC(CSimpleElementProperSheet)
public:
	CSimpleElementProperSheet(CString name , CWnd *pWnd = NULL);
	~CSimpleElementProperSheet(void);

public:

	virtual INT_PTR DoModal();

public:
	DECLARE_MESSAGE_MAP()

};
