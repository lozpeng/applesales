#pragma once
#include "ElementProperSheet.h"

class CPictureElementProperSheet :
	public CElementProperSheet
{
	DECLARE_DYNAMIC(CPictureElementProperSheet)
public:
	CPictureElementProperSheet(CString name , CWnd *pWnd = NULL);
	~CPictureElementProperSheet(void);

public:

	virtual INT_PTR DoModal();

public:
	DECLARE_MESSAGE_MAP()

};
