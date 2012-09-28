#include "stdafx.h"
#include "IAttributeTable.h"

namespace Framework
{

IAttributeTable::IAttributeTable()
{
	m_totalRecord =0;
	m_selRecord =0;
}

IAttributeTable::~IAttributeTable()
{

}



void IAttributeTable::CloseTable()
{

}

bool IAttributeTable::TableIsOpen()
{
	return false;
}


void IAttributeTable::UpdateLayerSelction()
{

}

bool IAttributeTable::CanEdit()
{
	return false;
}

void IAttributeTable::SelectAll()
{

}

void IAttributeTable::SelectNone()
{

}
/**
* …Ë÷√—°‘ÒºØ
*/
void IAttributeTable::SetSelction(Geodatabase::ISelctionSetPtr pSel)
{

}

IAttributeTable* IAttributeTable::GetActiveAttributeTable()
{
	IAttributeTable* pAttrTable = (IAttributeTable*)IUIObject::GetUIObjectByName("ATTRIBUTE TABLE");
	return pAttrTable;
}

Carto::ILayerPtr IAttributeTable::GetCurSelectLayer()
{
	return m_pLayer;
}

void IAttributeTable::SetLayer(Carto::ILayerPtr pLayer) 
{
	m_pLayer = pLayer;
}

}  //namespace Framework

