#include "stdafx.h"
#include "OGRWorkspaceFactory.h"
#include "OGRWorkspace.h"
COGRWorkspaceFactory* COGRWorkspaceFactory::m_instance =0;


using namespace Geodatabase;
using namespace std;

COGRWorkspaceFactory::COGRWorkspaceFactory()
{
     OGRRegisterAll();
}

COGRWorkspaceFactory::~COGRWorkspaceFactory()
{
	ClearAllWorkspace();


	m_instance =NULL;
}

COGRWorkspaceFactory* COGRWorkspaceFactory::GetInstance()
{
	if(!m_instance)
	{
		m_instance =new COGRWorkspaceFactory();
	}
	return m_instance;
}

void COGRWorkspaceFactory::CloseInstance()
{
	if(m_instance)
	{
		delete m_instance;
		m_instance =NULL;
	}
}

//打开工作空间
IWorkspace* COGRWorkspaceFactory::OpenFromFile(const char *filename)
{
	

	OGRDataSource *poDS = OGRSFDriverRegistrar::Open(filename, FALSE);
	if(!poDS)
	{
		return NULL;
	}

	COGRWorkspace *pWorkspace =new COGRWorkspace(this,poDS);
	pWorkspace->m_pathname =filename;

	//将Workspace注册
	m_openedWorkspaces[string(filename)] =pWorkspace;
	return pWorkspace;

}



//关闭所有的工作空间
void COGRWorkspaceFactory::ClearAllWorkspace()
{
	map<std::string,IWorkspace*>::iterator iter;

	for(iter=m_openedWorkspaces.begin();iter!=m_openedWorkspaces.end();iter++)
	{
		delete iter->second;
	}

	m_openedWorkspaces.clear();
}

