#include "StdAfx.h"
#include "RasterWSFactory.h"
#include "RasterWorkspace.h"
#include "gdal_priv.h"

using namespace Geodatabase;
using namespace std;

class CRasterGarbo //它的唯一工作就是在析构函数中删除CSingleton的实例
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
	GDALAllRegister();  //初始化数据驱动
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

//打开工作空间
IWorkspace* CRasterWSFactory::OpenFromFile(const char *filename)
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

	//如果没打开，则创建一个新的Workspace
	CRasterWorkspace *pWorkspace =new CRasterWorkspace(this);

	pWorkspace->m_pathname =path;

	//将Workspace注册
	m_openedWorkspaces[path] =pWorkspace;

	return pWorkspace;

}



IWorkspace* CRasterWSFactory::OpenFolder(const char *filename)
{
	string path =filename;



	//工作空间是否已经打开
	map<std::string,IWorkspace*>::iterator iter =m_openedWorkspaces.find(path);

	if(iter!=m_openedWorkspaces.end())
	{
		return iter->second; 
	}

	//如果没打开，则创建一个新的CRasterWorkspace
	CRasterWorkspace *pWorkspace =new CRasterWorkspace(this);

	pWorkspace->m_pathname =path;

	//将Workspace注册
	m_openedWorkspaces[path] =pWorkspace;

	return pWorkspace;
}

//关闭所有的工作空间
void CRasterWSFactory::ClearAllWorkspace()
{
	map<std::string,IWorkspace*>::iterator iter;

	for(iter=m_openedWorkspaces.begin();iter!=m_openedWorkspaces.end();iter++)
	{
		delete iter->second;
	}

	m_openedWorkspaces.clear();
}