//////////////////////////////////////////////////////////////////////
// ��Ȩ(c) 2008-2020, ����ǻ�
// ���ߣ�  champion
// ʱ�䣺  2008.7
// ������  դ������������࣬������դ���ļ������ռ�
//////////////////////////////////////////////////////////////////////
#ifndef _RASTER_WSFACTORY_H_
#define _RASTER_WSFACTORY_H_

#include "DSRasterDefine.h"
#include "IWorkspaceFactory.h"

class DSRASTER_DLL CRasterWSFactory: public Geodatabase::IWorkspaceFactory 
{
	friend class CRasterGarbo;
public:
	CRasterWSFactory(void);
	virtual ~CRasterWSFactory(void);

public:
	//���Ψһ��ʵ�� 
	static CRasterWSFactory* GetInstance();

	//�ر�ʵ��
	static void CloseInstance();

	Geodatabase::IWorkspace* OpenFromFile(const char* filename);


	Geodatabase::IWorkspace* OpenFolder(const char* path);

private:

	void ClearAllWorkspace();

	//��������Ψһ��ʵ��
	static CRasterWSFactory* m_instance;
};


#endif

