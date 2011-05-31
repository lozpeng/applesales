//////////////////////////////////////////////////////////////////////
  // ��Ȩ(c) 2010-2020, ����ǻ�
  // ���ߣ�  hhzhao
  // ʱ�䣺  2009/11/18
  // ������  shapefile���ݵĹ����ռ�  ����shapefile���ݵķ��ʡ��༭��
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
	//�������ݼ�����Ŀ	virtual long DatasetCount(Geodatabase::DatasetType type) const;

	//ͨ�����ݼ������ƴ����ݼ����������ļ��������������ݼ����ƣ�ȡ���ڹ����ռ������
	virtual Geodatabase::IFeatureDatasetPtr OpenFeatureDataset(const char* name);
	//ͨ�����ƣ���ʸ��������
	virtual Geodatabase::IFeatureClassPtr  OpenFeatureClass(const char *name);

	virtual Geodatabase::IFeatureClassPtr  CreateFeatureClass(const char *name,const Geodatabase::FeatureClassDef &FDef);

	///////////////////////�༭��صķ���/////////////////////////////////

	//��ʼһ���༭�Ự
	virtual void StartEdit();

	//�ύ�޸�
	virtual void Commit();

	//�����޸�
	virtual void Abort();


	//�����༭�Ự
	virtual void StopEdit(bool bsave=true);

	//��ʼһ���༭����
	virtual void StartEditOperation() ;

	//�����༭����
	virtual void StopEditOperation() ;

	//�����༭����
	virtual void AbortOperation() ;

	//����
	virtual void UndoEdit() ;

	//����
	virtual void RedoEdit() ;

	//�Ƿ��ܽ��л��˺�����
	virtual bool CanUndo() const;

	virtual bool CanRedo() const;

public:
	//����༭����
	void ClearEditCache();

	//ɾ��ָ����������ı༭����
	void RemoveEditCache(std::string filename);

	//����ָ��������ı༭����
	void BuildEditCache(Geodatabase::IFeatureClass *pFeatureClass);

	//�����໺���Ƿ����
	bool ExistEditCache(std::string filename);

	Geodatabase::CFeatureEditCache* FindEditCache(std::string filename);

	//��ָ�����ݼ��ı༭���������һ���µ�Ҫ��
	void AddFeature(Geodatabase::IFeatureClass *pFeatureClass,Geodatabase::CFeaturePtr pFeature);

	//��ָ�����ݼ��ı༭���������һ���µ�Ҫ��
	void UpdateFeature(Geodatabase::IFeatureClass *pFeatureClass,Geodatabase::CFeaturePtr pFeature);

	//��ָ�����ݼ��ı༭���������һ���µ�Ҫ��
	void DeleteFeature(Geodatabase::IFeatureClass *pFeatureClass,long index);

private:
	//�������ջ�ж���ļ�¼
	void RemoveRedundant();

	//����༭
	void SaveEdit();

	//д��һ��Ҫ��
	bool WriteFeature(Geodatabase::CFeature *pFeature,SHPHandle &hshp,DBFHandle &hdbf,bool bAppend=false);

	SHPObject *Geometry2Shp(GEOMETRY::geom::Geometry* pGeometry,int nSHPType);

	//��������������
	void IncrementalExport(std::string incrementalFile);
	void IncrementalImport(std::string incrementalFile);
private:

	typedef std::map<std::string,Geodatabase::CFeatureEditCache*> EditCacheMap;

	typedef std::vector<std::string> EditOperationContent;

	EditCacheMap m_EditCacheMap; //���������н��б༭��Ҫ����ı༭�����ָ��

	std::vector<EditOperationContent> m_EditStack;

	//�༭�ع���ָ��
	long  m_lcursor;

	//��ǰ�༭����������
	EditOperationContent m_curOperation;

	//�Ƿ�ʼ��һ���µı༭����
	bool m_bStartOp;

	std::string  m_FullName;
	IFeatureClassPtr m_FeatureClass;

};







#endif