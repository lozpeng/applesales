#ifndef _SHP_WORKSPACEFACTORY_H_
#define _SHP_WORKSPACEFACTORY_H_

#include "DSFileDefine.h"
#include "IWorkspaceFactory.h"

class DSFile_DLL CShapefileWorkspaceFactory: public Geodatabase::IWorkspaceFactory
{
public:
	CShapefileWorkspaceFactory(void);
	virtual ~CShapefileWorkspaceFactory(void);
public:
	//获得唯一的实例 
	static CShapefileWorkspaceFactory* GetInstance();

	//关闭实例
	static void CloseInstance();

	Geodatabase::IWorkspace* OpenFromFile(const char* filename);


	Geodatabase::IWorkspace* OpenFolder(const char* path);


private:

	void ClearAllWorkspace();

	//单件对象唯一的实例
	static CShapefileWorkspaceFactory* m_instance;
};

#endif