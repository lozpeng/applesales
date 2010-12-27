#ifndef _OGR_WORKSPACEFACTORY_H_
#define _OGR_WORKSPACEFACTORY_H_

#include "IWorkspaceFactory.h"


class DSFile_DLL COGRWorkspaceFactory: public Geodatabase::IWorkspaceFactory
{
protected:
	COGRWorkspaceFactory();
public:
	~COGRWorkspaceFactory();
public:
	//获得唯一的实例 
	static COGRWorkspaceFactory* GetInstance();

	//关闭实例
	static void CloseInstance();

	Geodatabase::IWorkspace* OpenFromFile(const char* filename);

private:

	void ClearAllWorkspace();

	//单件对象唯一的实例
	static COGRWorkspaceFactory* m_instance;




};







#endif