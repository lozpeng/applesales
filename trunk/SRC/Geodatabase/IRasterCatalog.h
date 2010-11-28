//////////////////////////////////////////////////////////////////////
// ��Ȩ(c) 2008-2020, ����ǻ�
// ���ߣ�  champion
// ʱ�䣺  2008.5
// ������  դ������Ŀ¼�Ļ���
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
    
	/*@*********************���Ŀ¼��դ�����ݼ�����Ŀ�����ƵĽӿ�*********************************@*/

	/**
	* �������ݼ�����Ŀ
	* @return ����long
	*/
	virtual long RasterDatasetCount() const;


	/**
	* �õ��������ݼ�������
	* @���� names: ���ص����ݼ������ƽ������vector��
	*/
	virtual void  GetDatasetNames(std::vector<std::string> &names);

	/*@*****************************��Ŀ¼��դ�����ݼ��Ľӿ�*********************************@*/

	/**
	* ͨ�����ƴ�դ�����ݼ�
	* @return ����ɹ������ش򿪵����ݼ���ָ�룬��֮������NULL
	*/
	virtual IRasterDatasetPtr OpenRasterDataset(const char *name,bool ReadOnly=true);

public:

};


typedef  SYSTEM::CSmartPtr<IRasterCatalog> IRasterCatalogPtr;



}




#endif