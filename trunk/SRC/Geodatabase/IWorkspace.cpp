#include "stdafx.h"
#include "IWorkspace.h"

namespace Geodatabase{



	IWorkspace::IWorkspace(Geodatabase::IWorkspaceFactory *pFactory)
	{
		m_pFactory =pFactory;

		m_bEditing =false;
	}

IWorkspace::~IWorkspace()
{

}

long IWorkspace::DatasetCount(GEODATATYPE type) const
{
	return 0;
}

void IWorkspace::GetDatasetNames(GEODATATYPE type,std::vector<std::string> &names) const
{

}


IFeatureDatasetPtr IWorkspace::OpenFeatureDataset(const char *name)
{
	return NULL;
}

IFeatureClassPtr  IWorkspace::OpenFeatureClass(const char *name)
{
	return IFeatureClassPtr();
}


IFeatureClassPtr  IWorkspace::CreateFeatureClass(const char *name, const Geodatabase::FeatureClassDef &FDef)
{
	return IFeatureClassPtr();
}

IRasterCatalogPtr  IWorkspace::OpenRasterCatalog(const char *name)
{
	return NULL;
}

IRasterDatasetPtr  IWorkspace::OpenRasterDataset(const char *name, bool ReadOnly)
{
	return NULL;
}

bool IWorkspace::CreateRasterDataset(const char *name, RasFileInfo *fileInfo)
{
	return false;
}


//开始一个编辑会话
void IWorkspace::StartEdit()
{

}

//结束编辑会话
void IWorkspace::StopEdit(bool bsave)
{

}

void IWorkspace::Commit()
{

}

void IWorkspace::Abort()
{

}

//开始一个编辑操作
void IWorkspace::StartEditOperation()
{

}

//结束编辑操作
void IWorkspace::StopEditOperation()
{

}

//放弃编辑操作
void IWorkspace::AbortOperation()
{

}

//回退
void IWorkspace::UndoEdit()
{

}

//重做
void IWorkspace::RedoEdit()
{

}

//是否能进行回退和重做
bool IWorkspace::CanUndo() const
{
	return false;
}

bool IWorkspace::CanRedo() const
{
	return false;
}

void IWorkspace::serialization(SYSTEM::IArchive &ar)
{

}


} //namespace Geodatabase