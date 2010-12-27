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
	//���Ψһ��ʵ�� 
	static COGRWorkspaceFactory* GetInstance();

	//�ر�ʵ��
	static void CloseInstance();

	Geodatabase::IWorkspace* OpenFromFile(const char* filename);

private:

	void ClearAllWorkspace();

	//��������Ψһ��ʵ��
	static COGRWorkspaceFactory* m_instance;




};







#endif