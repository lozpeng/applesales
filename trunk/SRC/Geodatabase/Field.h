//////////////////////////////////////////////////////////////////////
// ��Ȩ(c) 2008-2020, ����ǻ�
// ���ߣ�  champion
// ʱ�䣺  2008.5
// ������  �ֶ����Ƕ��ֶε����������ֶ������ֶγ��ȡ��ֶ����͵�
//////////////////////////////////////////////////////////////////////

#ifndef  _GEODATABASE_FIELD_H_
#define  _GEODATABASE_FIELD_H_

#include <string>

namespace Geodatabase
{

class GEODATABASE_DLL CField
{
public:
	CField();
	virtual ~CField();

public:
	//�ֶ�����
	std::string GetName() const{ return m_name;};
	
	void SetName(const char* name){m_name =name;};

    //�ֶγ���
	long GetLength() const {return m_length;};

	void SetLength(long length) {m_length =length;}

    //�ֶ�����
	long GetType() const{return m_type;}

	void SetType(long type) {m_type =(FIELD_TYPE)type;}

	//��ȷ��
	long Precision() const {return m_precision;}

	void SetPrecision(long precision) {m_precision =precision;}

    

public:
	std::string m_name;

	long m_length;

	long m_precision;

    FIELD_TYPE m_type;
};


typedef  SYSTEM::CSmartPtr<CField> CFieldPtr;



}




#endif