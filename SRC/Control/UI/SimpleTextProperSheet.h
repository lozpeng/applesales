#pragma once
#include "ElementProperSheet.h"

class CSimpleTextProperSheet :
	public CElementProperSheet
{
	DECLARE_DYNAMIC(CSimpleTextProperSheet)
public:
	CSimpleTextProperSheet(CString name , CWnd *pWnd = NULL);
	~CSimpleTextProperSheet(void);

public:

	virtual INT_PTR DoModal();

public:
	DECLARE_MESSAGE_MAP()

};
