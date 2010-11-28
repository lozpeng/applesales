//////////////////////////////////////////////////////////////////////
// 版权(c) 2008-2020, 天地智绘
// 作者：  champion
// 时间：  2008.5
// 描述：  字段类是对字段的描述，如字段名、字段长度、字段类型等
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
	//字段名称
	std::string GetName() const{ return m_name;};
	
	void SetName(const char* name){m_name =name;};

    //字段长度
	long GetLength() const {return m_length;};

	void SetLength(long length) {m_length =length;}

    //字段类型
	long GetType() const{return m_type;}

	void SetType(long type) {m_type =(FIELD_TYPE)type;}

	//精确度
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