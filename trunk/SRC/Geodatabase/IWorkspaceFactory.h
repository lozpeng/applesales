//////////////////////////////////////////////////////////////////////
  // ��Ȩ(c) 2008-2020, ����ǻ�
  // ���ߣ�  champion
  // ʱ�䣺  2008.5
  // ������  ���ڴ򿪹����ռ�Ĺ�����Ļ���
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
	//ͨ���ļ��򿪹����ռ�,���ļ������ǹ����ռ��ڵ������ļ��������Ǳ��ص����ݿ��ļ�
	virtual IWorkspace* OpenFromFile(const char* filename) =0;


	virtual IWorkspace* OpenFolder(const char* path){return NULL;}


protected:
	std::map<std::string,IWorkspace*> m_openedWorkspaces;


};






}




#endif