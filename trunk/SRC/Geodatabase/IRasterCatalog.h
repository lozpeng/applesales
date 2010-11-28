//////////////////////////////////////////////////////////////////////
// 版权(c) 2008-2020, 天地智绘
// 作者：  champion
// 时间：  2008.5
// 描述：  栅格数据目录的基类
//////////////////////////////////////////////////////////////////////

#ifndef  _IRASTERCATALOG_H_
#define  _IRASTERCATALOG_H_

#include "IGeodataObject.h"
#include "IRasterDataset.h"

namespace Geodatabase
{

class IRasterDataset;

class GEODATABASE_DLL IRasterCatalog: public IGeodataObject
{
public:
	IRasterCatalog(IWorkspace *pWorkspace);
	virtual ~IRasterCatalog();

public:
    
	/*@*********************获得目录中栅格数据集的数目和名称的接口*********************************@*/

	/**
	* 包含数据集的数目
	* @return 返回long
	*/
	virtual long RasterDatasetCount() const;


	/**
	* 得到所有数据集的名称
	* @参数 names: 返回的数据集的名称将填充在vector里
	*/
	virtual void  GetDatasetNames(std::vector<std::string> &names);

	/*@*****************************打开目录中栅格数据集的接口*********************************@*/

	/**
	* 通过名称打开栅格数据集
	* @return 如果成功，返回打开的数据集的指针，反之，返回NULL
	*/
	virtual IRasterDatasetPtr OpenRasterDataset(const char *name,bool ReadOnly=true);

public:

};


typedef  SYSTEM::CSmartPtr<IRasterCatalog> IRasterCatalogPtr;



}




#endif