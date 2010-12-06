//////////////////////////////////////////////////////////////////////
  // 版权(c) 2010-2020, 天地智绘
  // 作者：  hhzhao
  // 时间：  2009/11/10
  // 描述：  shapefile数据的空间工厂  负责shapefile数据的工作空间
//////////////////////////////////////////////////////////////////////

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