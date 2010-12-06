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
	//���Ψһ��ʵ�� 
	static CShapefileWorkspaceFactory* GetInstance();

	//�ر�ʵ��
	static void CloseInstance();

	Geodatabase::IWorkspace* OpenFromFile(const char* filename);


	Geodatabase::IWorkspace* OpenFolder(const char* path);


private:

	void ClearAllWorkspace();

	//��������Ψһ��ʵ��
	static CShapefileWorkspaceFactory* m_instance;
};

#endif