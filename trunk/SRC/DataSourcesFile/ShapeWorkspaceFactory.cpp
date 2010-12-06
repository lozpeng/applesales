#include "StdAfx.h"
#include "ShapeWorkspaceFactory.h"
#include "ShapeWorkspace.h"

CShapefileWorkspaceFactory* CShapefileWorkspaceFactory::m_instance =0;

using namespace Geodatabase;
using namespace std;

CShapefileWorkspaceFactory::CShapefileWorkspaceFactory()
{

}

CShapefileWorkspaceFactory::~CShapefileWorkspaceFactory()
{
	ClearAllWorkspace();

	m_instance =NULL;
}

CShapefileWorkspaceFactory* CShapefileWorkspaceFactory::GetInstance()
{
	if(!m_instance)
	{
		m_instance =new CShapefileWorkspaceFactory();
	}
	return m_instance;
}

void CShapefileWorkspaceFactory::CloseInstance()
{
	if(m_instance)
	{
		delete m_instance;
		m_instance =NULL;
	}
}

//打开工作空间
IWorkspace* CShapefileWorkspaceFactory::OpenFromFile(const char *filename)
{
	//得到文件所在文件夹的路径
	string path =filename;

	path =path.substr(0,path.rfind('\\'));

	//工作空间是否已经打开
	map<std::string,IWorkspace*>::iterator iter =m_openedWorkspaces.find(path);

	if(iter!=m_openedWorkspaces.end())
	{
		return iter->second; 
	}

	//如果没打开，则创建一个新的CTmsWorkspace
	CShapefileWorkspace *pWorkspace =new CShapefileWorkspace(this);

	pWorkspace->m_pathname =path;

	//将Workspace注册
	m_openedWorkspaces[path] =pWorkspace;

	return pWorkspace;

}

IWorkspace* CShapefileWorkspaceFactory::OpenFolder(const char *filename)
{
	string path =filename;



	//工作空间是否已经打开
	map<std::string,IWorkspace*>::iterator iter =m_openedWorkspaces.find(path);

	if(iter!=m_openedWorkspaces.end())
	{
		return iter->second; 
	}

	//如果没打开，则创建一个新的CTmsWorkspace
	CShapefileWorkspace *pWorkspace =new CShapefileWorkspace(this);

	pWorkspace->m_pathname =path;

	//将Workspace注册
	m_openedWorkspaces[path] =pWorkspace;

	return pWorkspace;
}



//关闭所有的工作空间
void CShapefileWorkspaceFactory::ClearAllWorkspace()
{
	map<std::string,IWorkspace*>::iterator iter;

	for(iter=m_openedWorkspaces.begin();iter!=m_openedWorkspaces.end();iter++)
	{
		delete iter->second;
	}

	m_openedWorkspaces.clear();
}