#include "StdAfx.h"
#include "MapTreeCallback.h"

CMapTreeCallback::CMapTreeCallback(void)
{
}

CMapTreeCallback::~CMapTreeCallback(void)
{
}

void CMapTreeCallback::UpdateMapCtrl()
{
	if(m_pMapControl)
	{
		m_pMapControl->Refresh();
	}
}