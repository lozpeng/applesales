//////////////////////////////////////////////////////////////////////
// ��Ȩ(c) 2008-2020, ����ǻ�
// ���ߣ�  champion
// ʱ�䣺  2008.7
// ������  դ��Ĺ����ռ䣬�ṩ�˴򿪡�����դ��Ӱ��Ĺ���
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
	* ͨ�����ƴ�դ�����ݼ�
	* @return ����ɹ������ش򿪵����ݼ���ָ�룬��֮������NULL
	*/
	virtual Geodatabase::IRasterDatasetPtr OpenRasterDataset(const char *name,bool ReadOnly=true);


    
	/**
	* ����һ��դ�����ݼ�
	* @param name ���ݼ�����
	* @param ImageType ���ݼ�����
	* @param fileInfo ���ݼ���Ϣ
	* @return ����ɹ�������true
	*/
	virtual bool CreateRasterDataset(const char *name,Geodatabase::RasFileInfo *fileInfo);
	

public:
	


};







#endif