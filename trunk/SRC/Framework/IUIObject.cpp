#include "stdafx.h"
#include "IUIObject.h"

namespace Framework
{

std::string  CommonUIName::AppMapControl ="AppMapControl";

std::string  CommonUIName::AppDocument ="AppDocument";

std::string  CommonUIName::AppLayoutControl ="AppLayoutControl";

std::string  CommonUIName::AppTOCControl ="AppTOCControl";

std::string  CommonUIName::AppSymbolLstCtrl = "AppSymbolLstCtrl";

static std::map<std::string,IUIObject*> uiobjects;
static std::map<std::string,IUIObject*>::iterator find_item;

IUIObject::IUIObject()
{
	m_bAutoDestroy = false;

	m_bActiveX =false;
}

IUIObject::~IUIObject()
{
	DestroyAss();
}

void IUIObject::serialization(SYSTEM::IArchive &ar)
{
	SYSTEM::ISerialization::serialization(ar);
}

IUIObject* IUIObject::GetUIObjectByName(std::string Name)
{
	std::map<std::string,IUIObject* >::iterator item;
	item = uiobjects.find( Name );
	if( item == uiobjects.end() )
		return NULL;
	else
		return item->second;
}

IUIObject* IUIObject::GetFirstObject()
{
	find_item = uiobjects.begin();
	if( find_item == uiobjects.end() )
		return NULL;
	else
		return find_item->second;
}

IUIObject* IUIObject::GetNextObject()
{
	find_item++;
	if( find_item == uiobjects.end() )
		return NULL;
	else
		return find_item->second;
}

void IUIObject::CreateAss(std::string Name)
{
	std::map<std::string,IUIObject*>::iterator item;

	item = uiobjects.find( Name );
	if( item == uiobjects.end() )
		uiobjects.insert( std::map<std::string,IUIObject*>::value_type(Name, this ) );
	else
	{
		uiobjects[ Name ] = this;
		
	}
	m_Name = Name;
}

void IUIObject::DestroyAss()
{
	std::map<std::string,IUIObject*>::iterator item;
	if( m_Name.length() == 0 )
		return;

	item = uiobjects.find( m_Name );
	if( item != uiobjects.end() )
	{
		if(!m_bAutoDestroy)
			delete item->second;

		uiobjects.erase( item );
	}
	
}

std::string IUIObject::GetName()
{
	return m_Name;
}


}