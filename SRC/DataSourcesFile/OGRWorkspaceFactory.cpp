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

//�򿪹����ռ�
IWorkspace* COGRWorkspaceFactory::OpenFromFile(const char *filename)
{
	

	OGRDataSource *poDS = OGRSFDriverRegistrar::Open(filename, FALSE);
	if(!poDS)
	{
		return NULL;
	}

	COGRWorkspace *pWorkspace =new COGRWorkspace(this,poDS);
	pWorkspace->m_pathname =filename;

	//��Workspaceע��
	m_openedWorkspaces[string(filename)] =pWorkspace;
	return pWorkspace;

}



//�ر����еĹ����ռ�
void COGRWorkspaceFactory::ClearAllWorkspace()
{
	map<std::string,IWorkspace*>::iterator iter;

	for(iter=m_openedWorkspaces.begin();iter!=m_openedWorkspaces.end();iter++)
	{
		delete iter->second;
	}

	m_openedWorkspaces.clear();
}

