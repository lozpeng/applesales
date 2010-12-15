#include "StdAfx.h"
#include "ICommand.h"

namespace Framework
{

	std::map<std::string,ICommand*> ICommand::gCommands;

	ICommand::ICommand(const char* name)
	{
		m_pTarget =NULL;
		RegisterCommand(name,this);
	}
	ICommand::~ICommand(void)
	{
	}

	std::string ICommand::GetName()
	{
		return m_strName;
	}

	void ICommand::Initialize(IUIObject *pTarget)
	{
		m_pTarget =pTarget;
	}

	ICommand* ICommand::FindCommand(std::string strName)
	{
		std::map<std::string,ICommand*>::iterator iter =gCommands.find(strName);
		if(iter==gCommands.end())
		{
			return NULL;
		}

		return iter->second;
	}

	void ICommand::RegisterCommand(std::string strName, ICommand* pCommand)
	{
		gCommands[strName] = pCommand;
	}

	void ICommand::Click()
	{

	}
}