//////////////////////////////////////////////////////////////////////
  // 版权(c) 2008-2020, 天地智绘
  // 作者：  champion
  // 时间：  2008.5
  // 描述：  用于打开工作空间的工厂类的基类
//////////////////////////////////////////////////////////////////////

#ifndef  _GEODATABASE_IWORKSPACEFACTORY_H_
#define  _GEODATABASE_IWORKSPACEFACTORY_H_

#include <string>
#include <map>

namespace Geodatabase
{

class IWorkspace;

class GEODATABASE_DLL IWorkspaceFactory
{
public:
	IWorkspaceFactory();
	virtual ~IWorkspaceFactory();

public:
	//通过文件打开工作空间,该文件可能是工作空间内的数据文件，或者是本地的数据库文件
	virtual IWorkspace* OpenFromFile(const char* filename) =0;


	virtual IWorkspace* OpenFolder(const char* path){return NULL;}


protected:
	std::map<std::string,IWorkspace*> m_openedWorkspaces;


};






}




#endif