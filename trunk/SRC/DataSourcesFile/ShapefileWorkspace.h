//////////////////////////////////////////////////////////////////////
  // 版权(c) 2010-2020, 天地智绘
  // 作者：  hhzhao
  // 时间：  2009/11/18
  // 描述：  shapefile数据的工作空间  负责shapefile数据的访问、编辑等
//////////////////////////////////////////////////////////////////////

#ifndef _SHP_WORKSPACE_H_
#define _SHP_WORKSPACE_H_

#include "DSFileDefine.h"
#include "IWorkspaceFactory.h"
#include "IWorkspace.h"
#include "FeatureEditCache.h"
#include "shapefil.h"

class CShapefileWorkspaceFactory;

class DSFile_DLL CShapefileWorkspace: public Geodatabase::IWorkspace
{
public:
	CShapefileWorkspace(CShapefileWorkspaceFactory *pFactory);
	virtual ~CShapefileWorkspace();
public:
	//包含数据集的数目	virtual long DatasetCount(Geodatabase::DatasetType type) const;

	//通过数据集的名称打开数据集，名称是文件名，或者是数据集名称，取决于工作空间的类型
	virtual Geodatabase::IFeatureDatasetPtr OpenFeatureDataset(const char* name);
	//通过名称，打开矢量数据类
	virtual Geodatabase::IFeatureClassPtr  OpenFeatureClass(const char *name);

	virtual Geodatabase::IFeatureClassPtr  CreateFeatureClass(const char *name,const Geodatabase::FeatureClassDef &FDef);

	///////////////////////编辑相关的方法/////////////////////////////////

	//开始一个编辑会话
	virtual void StartEdit();

	//提交修改
	virtual void Commit();

	//放弃修改
	virtual void Abort();


	//结束编辑会话
	virtual void StopEdit(bool bsave=true);

	//开始一个编辑操作
	virtual void StartEditOperation() ;

	//结束编辑操作
	virtual void StopEditOperation() ;

	//放弃编辑操作
	virtual void AbortOperation() ;

	//回退
	virtual void UndoEdit() ;

	//重做
	virtual void RedoEdit() ;

	//是否能进行回退和重做
	virtual bool CanUndo() const;

	virtual bool CanRedo() const;

public:
	//清理编辑缓存
	void ClearEditCache();

	//删除指定的数据类的编辑缓存
	void RemoveEditCache(std::string filename);

	//建立指定数据类的编辑缓存
	void BuildEditCache(Geodatabase::IFeatureClass *pFeatureClass);

	//数据类缓存是否存在
	bool ExistEditCache(std::string filename);

	Geodatabase::CFeatureEditCache* FindEditCache(std::string filename);

	//在指定数据集的编辑缓存中添加一个新的要素
	void AddFeature(Geodatabase::IFeatureClass *pFeatureClass,Geodatabase::CFeaturePtr pFeature);

	//在指定数据集的编辑缓存中添加一个新的要素
	void UpdateFeature(Geodatabase::IFeatureClass *pFeatureClass,Geodatabase::CFeaturePtr pFeature);

	//在指定数据集的编辑缓存中添加一个新的要素
	void DeleteFeature(Geodatabase::IFeatureClass *pFeatureClass,long index);

private:
	//清除掉堆栈中多余的记录
	void RemoveRedundant();

	//保存编辑
	void SaveEdit();

	//写入一个要素
	bool WriteFeature(Geodatabase::CFeature *pFeature,SHPHandle &hshp,DBFHandle &hdbf,bool bAppend=false);

	SHPObject *Geometry2Shp(GEOMETRY::geom::Geometry* pGeometry,int nSHPType);

	//增量导出、导入
	void IncrementalExport(std::string incrementalFile);
	void IncrementalImport(std::string incrementalFile);
private:

	typedef std::map<std::string,Geodatabase::CFeatureEditCache*> EditCacheMap;

	typedef std::vector<std::string> EditOperationContent;

	EditCacheMap m_EditCacheMap; //保存了所有进行编辑的要素类的编辑缓存的指针

	std::vector<EditOperationContent> m_EditStack;

	//编辑回滚的指针
	long  m_lcursor;

	//当前编辑操作的内容
	EditOperationContent m_curOperation;

	//是否开始了一个新的编辑操作
	bool m_bStartOp;

	std::string  m_FullName;
	IFeatureClassPtr m_FeatureClass;

};







#endif