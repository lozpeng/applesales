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

//�򿪹����ռ�
IWorkspace* CShapefileWorkspaceFactory::OpenFromFile(const char *filename)
{
	//�õ��ļ������ļ��е�·��
	string path =filename;

	path =path.substr(0,path.rfind('\\'));

	//�����ռ��Ƿ��Ѿ���
	map<std::string,IWorkspace*>::iterator iter =m_openedWorkspaces.find(path);

	if(iter!=m_openedWorkspaces.end())
	{
		return iter->second; 
	}

	//���û�򿪣��򴴽�һ���µ�CTmsWorkspace
	CShapefileWorkspace *pWorkspace =new CShapefileWorkspace(this);

	pWorkspace->m_pathname =path;

	//��Workspaceע��
	m_openedWorkspaces[path] =pWorkspace;

	return pWorkspace;

}

IWorkspace* CShapefileWorkspaceFactory::OpenFolder(const char *filename)
{
	string path =filename;



	//�����ռ��Ƿ��Ѿ���
	map<std::string,IWorkspace*>::iterator iter =m_openedWorkspaces.find(path);

	if(iter!=m_openedWorkspaces.end())
	{
		return iter->second; 
	}

	//���û�򿪣��򴴽�һ���µ�CTmsWorkspace
	CShapefileWorkspace *pWorkspace =new CShapefileWorkspace(this);

	pWorkspace->m_pathname =path;

	//��Workspaceע��
	m_openedWorkspaces[path] =pWorkspace;

	return pWorkspace;
}



//�ر����еĹ����ռ�
void CShapefileWorkspaceFactory::ClearAllWorkspace()
{
	map<std::string,IWorkspace*>::iterator iter;

	for(iter=m_openedWorkspaces.begin();iter!=m_openedWorkspaces.end();iter++)
	{
		delete iter->second;
	}

	m_openedWorkspaces.clear();
}