//////////////////////////////////////////////////////////////////////
// ��Ȩ(c) 2008-2020, ����ǻ�
// ���ߣ�  champion
// ʱ�䣺  2008.5
// ������  �������ݵĻ���
//////////////////////////////////////////////////////////////////////

#ifndef _IGeodataObject_h
#define _IGeodataObject_h

#include <Geometry/geom/Envelope.h>
#include "IArchive.h"

namespace Geodatabase
{

class IWorkspace;

class GEODATABASE_DLL IGeodataObject 
{
public:
	IGeodataObject(IWorkspace* workspace);
	virtual ~IGeodataObject();

public:

	/**
	* ��ȡ���ݶ�������
	* @return �������ݶ�������
	*/
	GEODATATYPE GetType() const;

	/**
	* �������
	* @return ��������
	*/
	std::string Getname() const;

	//�õ����ݼ��ķ�Χ��pEnvelop�Ƿ��صķ�Χ
	virtual bool GetExtent(GEOMETRY::geom::Envelope *pEnvelop) const;

	/**
	* ��ȡ����Դ
	* @return ��������Դ
	*/
	IWorkspace* GetWorkspace() const;

	/**
	* ���л�����Դ�����Ϣ,ֻ�洢��Ϣ����
	* @param ar �����ļ���
	*/
	virtual void serialization(SYSTEM::IArchive &ar);

protected:

	//
	std::string m_name;

	//
	GEODATATYPE m_objType;

	//
	IWorkspace* m_pWorkspace;

	//
	GEOMETRY::geom::Envelope m_Envelop;

};

typedef  SYSTEM::CSmartPtr<IGeodataObject> IGeodataObjectPtr;

}

#endif