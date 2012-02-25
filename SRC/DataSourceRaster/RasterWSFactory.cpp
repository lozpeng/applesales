#include "StdAfx.h"
#include "RasterWSFactory.h"
#include "RasterWorkspace.h"
#include "gdal_priv.h"

using namespace Geodatabase;
using namespace std;

class CRasterGarbo //����Ψһ��������������������ɾ��CSingleton��ʵ��
{

public:

	~CRasterGarbo()

	{

		if( CRasterWSFactory::m_instance )

			delete CRasterWSFactory::m_instance;

	}

};
static CRasterGarbo Garbo;

CRasterWSFactory* CRasterWSFactory::m_instance =NULL;

CRasterWSFactory::CRasterWSFactory(void)
{
	GDALAllRegister();  //��ʼ����������
}


CRasterWSFactory::~CRasterWSFactory(void)
{
	ClearAllWorkspace();

	m_instance =NULL;

	GDALDestroyDriverManager();
}

CRasterWSFactory* CRasterWSFactory::GetInstance()
{
	if(!m_instance)
	{
		m_instance =new CRasterWSFactory();
	}
	return m_instance;
}

void CRasterWSFactory::CloseInstance()
{
	if(m_instance)
	{
		delete m_instance;
		m_instance =NULL;
	}
}

//�򿪹����ռ�
IWorkspace* CRasterWSFactory::OpenFromFile(const char *filename)
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

	//���û�򿪣��򴴽�һ���µ�Workspace
	CRasterWorkspace *pWorkspace =new CRasterWorkspace(this);

	pWorkspace->m_pathname =path;

	//��Workspaceע��
	m_openedWorkspaces[path] =pWorkspace;

	return pWorkspace;

}



IWorkspace* CRasterWSFactory::OpenFolder(const char *filename)
{
	string path =filename;



	//�����ռ��Ƿ��Ѿ���
	map<std::string,IWorkspace*>::iterator iter =m_openedWorkspaces.find(path);

	if(iter!=m_openedWorkspaces.end())
	{
		return iter->second; 
	}

	//���û�򿪣��򴴽�һ���µ�CRasterWorkspace
	CRasterWorkspace *pWorkspace =new CRasterWorkspace(this);

	pWorkspace->m_pathname =path;

	//��Workspaceע��
	m_openedWorkspaces[path] =pWorkspace;

	return pWorkspace;
}

//�ر����еĹ����ռ�
void CRasterWSFactory::ClearAllWorkspace()
{
	map<std::string,IWorkspace*>::iterator iter;

	for(iter=m_openedWorkspaces.begin();iter!=m_openedWorkspaces.end();iter++)
	{
		delete iter->second;
	}

	m_openedWorkspaces.clear();
}