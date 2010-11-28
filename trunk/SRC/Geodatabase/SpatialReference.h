//////////////////////////////////////////////////////////////////////
// ��Ȩ(c) 2008-2020, ����ǻ�
// ���ߣ�  champion
// ʱ�䣺  2008.6
// ������  ����ο�ϵ��Ķ���
//////////////////////////////////////////////////////////////////////

#ifndef  _SPATIAL_REFERENCE_H_
#define  _SPATIAL_REFERENCE_H_

#include "SystemUnit.h"

namespace Geodatabase
{


class GEODATABASE_DLL CSpatialReference
{
	friend class CSpatialReference;
public:
    CSpatialReference();
	CSpatialReference(const char *wkt);
	CSpatialReference(const CSpatialReference& other);
    
	virtual ~CSpatialReference();

	CSpatialReference &operator=(const CSpatialReference& other);

public:
    
	/**
	* ��ö���Ŀ���
	*/
	CSpatialReference* Clone() const;

	/**
	* ����Wkt�ַ���
	* @param wkt ��ʾ����ο�ϵ���ַ���
	*/
	bool ImportFromWkt(const char *wkt);

	/**
	* ����ESRIͶӰ�����ַ���
	* @param wkt ��ʾ����ο�ϵ���ַ���
	*/
	bool ImportFromESRI(const char *wkt);

	/**
	* ����Wkt�ַ���
	*/
	std::string ExportToWkt() const;

	/**
	* �Ƿ��������ϵ
	*/
	bool IsGeographic() const;

	/**
	* �Ƿ�ͶӰ����ϵ
	*/
	bool IsProjected() const;

	/**
	* �����ο�ϵ�Ƿ���ͬ
	*/
    bool IsSame(const CSpatialReference* pOther) const;

	/**
	* �õ�����ο�ϵ����
	*/
	std::string GetGeogName() const;

	/**
	* �õ�ͶӰ����
	*/
	std::string GetProjName() const;

    //�õ��������ϵ��λ
	SYSTEM::SYS_UNIT_TYPE GetLinearUnits() const;

	//�õ���γ�����굥λ
	SYSTEM::SYS_UNIT_TYPE GetAngularUnits() const;


	/**
	* �õ��ڲ�ָ��
	*/
	void* GetHandle() const;


private:

	//���ڲ�ָ�����
	void Clear();

private:
	//����GDAL��OGRSpatialReferenceָ��
	void *m_Handle;

};

typedef  SYSTEM::CSmartPtr<CSpatialReference> CSpatialReferencePtr;

}

#endif