//////////////////////////////////////////////////////////////////////
// 版权(c) 2008-2020, 天地智绘
// 作者：  champion
// 时间：  2008.7
// 描述：  栅格的工作空间，提供了打开、创建栅格影像的功能
//////////////////////////////////////////////////////////////////////

#ifndef _RASTER_WORKSPACE_H_
#define _RASTER_WORKSPACE_H_

#include "IWorkspaceFactory.h"
#include "IWorkspace.h"

class CRasterWSFactory;

class  CRasterWorkspace: public Geodatabase::IWorkspace
{
public:
	CRasterWorkspace(CRasterWSFactory *pFactory);
	virtual ~CRasterWorkspace();
public:


	/**
	* 通过名称打开栅格数据集
	* @return 如果成功，返回打开的数据集的指针，反之，返回NULL
	*/
	virtual Geodatabase::IRasterDatasetPtr OpenRasterDataset(const char *name,bool ReadOnly=true);


    
	/**
	* 创建一个栅格数据集
	* @param name 数据集名称
	* @param ImageType 数据集类型
	* @param fileInfo 数据集信息
	* @return 如果成功，返回true
	*/
	virtual bool CreateRasterDataset(const char *name,Geodatabase::RasFileInfo *fileInfo);
	

public:
	


};







#endif