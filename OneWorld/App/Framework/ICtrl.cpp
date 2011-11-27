#include "ICtrl.h"

namespace Framework
{

static std::map<int,ICtrl*> uiobjects;
static std::map<int,ICtrl*>::iterator find_item;

ICtrl::ICtrl()
{
}

ICtrl::~ICtrl()
{
}

ICtrl* ICtrl::GetUIObjectByID(int nUIID)
{
	std::map<int,ICtrl* >::iterator item;
	item = uiobjects.find( nUIID );
	if( item == uiobjects.end() )
		return NULL;
	else
		return item->second;
}

ICtrl* ICtrl::GetFirstUI()
{
	find_item = uiobjects.begin();
	if( find_item == uiobjects.end() )
		return NULL;
	else
		return find_item->second;
}

ICtrl* ICtrl::GetNextUI()
{
	find_item++;
	if( find_item == uiobjects.end() )
		return NULL;
	else
		return find_item->second;
}

void ICtrl::CreateUI(int nUIID)
{
	std::map<int,ICtrl*>::iterator item;

	item = uiobjects.find( nUIID );
	if( item == uiobjects.end() )
		uiobjects.insert( std::map<int,ICtrl*>::value_type(nUIID, this ) );
	else
	{
		uiobjects[ nUIID ] = this;
		
	}
	m_nID = nUIID;
}

void ICtrl::DestroyUI()
{
	std::map<int,ICtrl*>::iterator item;

	item = uiobjects.find( m_nID );
	if( item != uiobjects.end() )
	{
		delete item->second;
		uiobjects.erase( item );
	}
	
}

std::string ICtrl::GetName()
{
	switch (m_nID)
	{
	case MapControl:
		return "MapControl";
	case LayoutControl:
		return "LayoutControl";
	case TocControl:
		return "TocControl";
	default:
		break;
	}
	return "";
}


}