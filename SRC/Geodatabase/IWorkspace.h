//////////////////////////////////////////////////////////////////////
// ��Ȩ(c) 2008-2020, ����ǻ�
// ���ߣ�  champion
// ʱ�䣺  2008.5
// ������  �����ռ���Ļ��࣬�ṩ�����ڴ򿪺ʹ������ݼ��������ļ��ķ���
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

	//���ع����ռ������
	long GetType() const {return m_type;}

	//��������ռ���һ���ļ��У��򷵻�����·������������ݿ⣬�򷵻ؿ��ַ���
	virtual std::string GetPathname() const {return m_pathname;};


	IWorkspaceFactory *GetWorkspaceFactory() const{return m_pFactory;}

	
	//�õ�ĳ�����ݼ�����������
	virtual void GetDatasetNames(GEODATATYPE type,std::vector<std::string> &names) const;

	//����ĳ�����ݼ�����Ŀ
	virtual long DatasetCount(GEODATATYPE type) const;

	//��ʸ�����ݼ�
	virtual IFeatureDatasetPtr OpenFeatureDataset(const char* name);

	//ͨ�����ƣ���ʸ��������
	virtual IFeatureClassPtr  OpenFeatureClass(const char *name);


	//����һ��ָ����ʸ��������,����ɹ�����������ָ�룬���򷵻ؿ�ָ��
	virtual IFeatureClassPtr  CreateFeatureClass(const char *name,const FeatureClassDef &FDef);

	/**
	* ͨ�����ƴ�դ��Ŀ¼
	* @return ����ɹ������ش򿪵����ݵ�ָ�룬��֮������NULL
	*/
	virtual IRasterCatalogPtr OpenRasterCatalog(const char *name);
    

	/**
	* ͨ�����ƴ�դ�����ݼ�
	* @return ����ɹ������ش򿪵����ݼ���ָ�룬��֮������NULL
	*/
	virtual IRasterDatasetPtr OpenRasterDataset(const char *name,bool ReadOnly=true);
    
	/**
	* ����һ��դ�����ݼ�
	* @param name ���ݼ�����
	* @param ImageType ���ݼ�����
	* @param fileInfo ���ݼ���Ϣ
	* @return ����ɹ�������true
	*/
	virtual bool CreateRasterDataset(const char *name,RasFileInfo *fileInfo);


	//�Ƿ��ڽ��б༭
	virtual bool IsEditing() const {return m_bEditing;};

	//��ʼһ���༭�Ự
	virtual void StartEdit();

	//�����༭�Ự
	virtual void StopEdit(bool bsave=true);

	//�ύ�޸�
	virtual void Commit();

	//�����޸�
	virtual void Abort();

	//��ʼһ���༭����
	virtual void StartEditOperation();

	//�����༭����
	virtual void StopEditOperation() ;

	//�����༭����
	virtual void AbortOperation();

	//����
	virtual void UndoEdit();

	//����
	virtual void RedoEdit();

	//�Ƿ��ܽ��л��˺�����
	virtual bool CanUndo() const;

	virtual bool CanRedo() const;

	/**
	* ���л�����Դ�����Ϣ
	* @param ar �����ļ���
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