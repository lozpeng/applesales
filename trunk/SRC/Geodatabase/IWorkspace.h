//////////////////////////////////////////////////////////////////////
// 版权(c) 2008-2020, 天地智绘
// 作者：  champion
// 时间：  2008.5
// 描述：  工作空间类的基类，提供了用于打开和创建数据集和数据文件的方法
//////////////////////////////////////////////////////////////////////

#ifndef  _GEODATABASE_IWORKSPACE_H_
#define  _GEODATABASE_IWORKSPACE_H_

#include "IWorkspaceFactory.h"
#include "IFeatureClass.h"
#include "IFeatureDataset.h"
#include "IRasterCatalog.h"
#include "IRasterDataset.h"
#include "IArchive.h"

namespace Geodatabase
{



class IRasterDataset;

class GEODATABASE_DLL IWorkspace
{
public:
	IWorkspace(IWorkspaceFactory *pFactory);
	virtual ~IWorkspace();

public:

	//返回工作空间的类型
	long GetType() const {return m_type;}

	//如果工作空间是一个文件夹，则返回它的路径，如果是数据库，则返回空字符串
	virtual std::string GetPathname() const {return m_pathname;};


	IWorkspaceFactory *GetWorkspaceFactory() const{return m_pFactory;}

	
	//得到某类数据集的所有名称
	virtual void GetDatasetNames(GEODATATYPE type,std::vector<std::string> &names) const;

	//包含某种数据集的数目
	virtual long DatasetCount(GEODATATYPE type) const;

	//打开矢量数据集
	virtual IFeatureDatasetPtr OpenFeatureDataset(const char* name);

	//通过名称，打开矢量数据类
	virtual IFeatureClassPtr  OpenFeatureClass(const char *name);


	//创建一个指定的矢量数据类,如果成功，返回它的指针，否则返回空指针
	virtual IFeatureClassPtr  CreateFeatureClass(const char *name,const FeatureClassDef &FDef);

	/**
	* 通过名称打开栅格目录
	* @return 如果成功，返回打开的数据的指针，反之，返回NULL
	*/
	virtual IRasterCatalogPtr OpenRasterCatalog(const char *name);
    

	/**
	* 通过名称打开栅格数据集
	* @return 如果成功，返回打开的数据集的指针，反之，返回NULL
	*/
	virtual IRasterDatasetPtr OpenRasterDataset(const char *name,bool ReadOnly=true);
    
	/**
	* 创建一个栅格数据集
	* @param name 数据集名称
	* @param ImageType 数据集类型
	* @param fileInfo 数据集信息
	* @return 如果成功，返回true
	*/
	virtual bool CreateRasterDataset(const char *name,RasFileInfo *fileInfo);


	//是否在进行编辑
	virtual bool IsEditing() const {return m_bEditing;};

	//开始一个编辑会话
	virtual void StartEdit();

	//结束编辑会话
	virtual void StopEdit(bool bsave=true);

	//提交修改
	virtual void Commit();

	//放弃修改
	virtual void Abort();

	//开始一个编辑操作
	virtual void StartEditOperation();

	//结束编辑操作
	virtual void StopEditOperation() ;

	//放弃编辑操作
	virtual void AbortOperation();

	//回退
	virtual void UndoEdit();

	//重做
	virtual void RedoEdit();

	//是否能进行回退和重做
	virtual bool CanUndo() const;

	virtual bool CanRedo() const;

	/**
	* 序列化数据源相关信息
	* @param ar 档案文件流
	*/
	virtual void serialization(SYSTEM::IArchive &ar);

public:
	IWorkspaceFactory *m_pFactory;
	std::string        m_pathname;

	bool m_bEditing;

	WorkspaceType  m_type;

};


}




#endif