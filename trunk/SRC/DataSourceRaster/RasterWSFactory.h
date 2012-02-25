//////////////////////////////////////////////////////////////////////
// 版权(c) 2008-2020, 天地智绘
// 作者：  champion
// 时间：  2008.7
// 描述：  栅格的驱动工厂类，用来打开栅格文件工作空间
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
	//获得唯一的实例 
	static CRasterWSFactory* GetInstance();

	//关闭实例
	static void CloseInstance();

	Geodatabase::IWorkspace* OpenFromFile(const char* filename);


	Geodatabase::IWorkspace* OpenFolder(const char* path);

private:

	void ClearAllWorkspace();

	//单件对象唯一的实例
	static CRasterWSFactory* m_instance;
};


#endif

