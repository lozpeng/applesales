#include "stdafx.h"
#include "IMaptreeCtrl.h"

namespace Framework
{

IMaptreeCtrl::IMaptreeCtrl()
{
	m_iSelectedItemType = eMapItem;
}

IMaptreeCtrl::~IMaptreeCtrl()
{

}

inline HTREEITEM IMaptreeCtrl::GetMapItem()
{
	return m_hMapItem;
}

int IMaptreeCtrl::GetSelectedItemType()
{
	return m_iSelectedItemType;
}

void* IMaptreeCtrl::GetSelectedItemData()
{
	return NULL;
}

}