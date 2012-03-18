#pragma once
#include "Map.h"
class CMapProperSheet :
	public CPropertySheet
{
	DECLARE_DYNAMIC(CMapProperSheet)
public:
	CMapProperSheet(CString name , CWnd *pWnd = NULL);
	~CMapProperSheet(void);

	void SetMap(Carto::CMapPtr pMap);

public:

	virtual INT_PTR DoModal();

public:
	DECLARE_MESSAGE_MAP()

private:
	Carto::CMapPtr m_pMap;

};
