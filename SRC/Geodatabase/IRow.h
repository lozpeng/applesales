//////////////////////////////////////////////////////////////////////
// 版权(c) 2008-2020, 天地智绘
// 作者：  champion
// 时间：  2008.5
// 描述：  记录基类
//////////////////////////////////////////////////////////////////////

#ifndef  _GEODATABASE_IROW_H_
#define  _GEODATABASE_IROW_H_

#include "Field.h"
#include <string>
#include <vector>
#include <sstream>
namespace Geodatabase
{


class ITable;

//字段的值类
class  FieldValue
{
public:
	enum VTYPE{
		VT_EMPTY = 0, //空值
		VT_NULL = 1,  //没有值
		VT_SHORT = 2, //short
		VT_INT = 3,   //int
		VT_FLOAT = 4,    //float
		VT_DOUBLE = 5, //double
		VT_STR = 6,   //std::string      
		VT_BOOL = 7,  //bool
		VT_DATE =8
	};
	struct Date{
		int  Year;
		unsigned char Month;
		unsigned char   Day;
		unsigned char   Hour;
		unsigned char   Minute;
		unsigned char   Second;
	} ;

public:
	//创造一个空的值
	FieldValue() { vtype =VT_EMPTY;};

	FieldValue(bool val) {vtype =VT_BOOL; m_Var.bVal =val;}

	FieldValue(short val) {vtype =VT_SHORT; m_Var.sVal =val;}

	FieldValue(long val) {vtype =VT_INT; m_Var.iVal =val;}

	FieldValue(int val) {vtype =VT_INT; m_Var.iVal =val;}

	FieldValue(float val) {vtype =VT_FLOAT; m_Var.fVal =val;}

	FieldValue(double val) {vtype =VT_DOUBLE; m_Var.dVal =val;}

	FieldValue(const char *val) {vtype =VT_STR;m_Var.pstrVal =new std::string; *m_Var.pstrVal =val;}

	FieldValue(const FieldValue &other)
	{
		vtype =other.vtype;

		if(vtype ==VT_STR)
		{
			m_Var.pstrVal =new std::string(*other.m_Var.pstrVal);
		}
		else
		{
			m_Var =other.m_Var;
		}
	}
	FieldValue& operator= (const FieldValue &other)
	{
		vtype =other.vtype;

		if(vtype ==VT_STR)
		{
			m_Var.pstrVal =new std::string(*other.m_Var.pstrVal);
		}
		else
		{
			m_Var =other.m_Var;
		}

		return *this;
	}

	~FieldValue()
	{
		clear();
	}
	void clear()
	{
		if(vtype ==VT_STR)
		{
			delete m_Var.pstrVal;
			m_Var.pstrVal =NULL;
		}
		vtype =VT_EMPTY;
	}

public:
	void SetString(const char *str){vtype =VT_STR;m_Var.pstrVal =new std::string; *m_Var.pstrVal =str;}

	std::string GetasString()
	{

		switch(vtype)
		{
		case VT_EMPTY:
		case VT_NULL:
			return "";
			break;
		case VT_SHORT:
			{
				std::ostringstream ostr;
				ostr<<m_Var.sVal;
				return ostr.str();
				break;
			}
		case VT_INT:
			{
				std::ostringstream ostr;
				ostr<<m_Var.iVal;
				return ostr.str();
				break;
			}
		case VT_FLOAT:
			{
				std::ostringstream ostr;
				ostr<<m_Var.fVal;
				return ostr.str();
				break;
			}
		case VT_DOUBLE:
			{
				std::ostringstream ostr;
				ostr<<m_Var.dVal;
				return ostr.str();
				break;
			}
		case VT_STR:
			{
				return *(m_Var.pstrVal);
				break;
			}
		case VT_BOOL:
			{
				if(m_Var.bVal)
				{
					return "Y";
				}
				else
				{
					return "N";
				}
			}
		default:
			return "";
			break;
		}
	}
	double GetAsDouble()
	{
		switch(vtype)
		{
		case VT_SHORT:
			{

				return double(m_Var.sVal);
				break;
			}
		case VT_INT:
			{
				return double(m_Var.iVal);
				break;
			}
		case VT_FLOAT:
			{

				return m_Var.fVal;
				break;
			}
		case VT_DOUBLE:
			{

				return m_Var.dVal;
				break;
			}
		default:
			return 0.0;
			break;
		}
	}
public:


	VTYPE vtype;
	union
	{
		bool bVal;
		short sVal;
		int   iVal;
		float fVal;
		double dVal;
		std::string* pstrVal;
		Date  date;

	}m_Var;

};

class GEODATABASE_DLL IRow
{
public:
	IRow(ITable *pTable,long oid);
	virtual ~IRow();

public:
	//得到记录相关联的表
	virtual ITable* GetTable() const {return m_pTable;};

	//通过序号得到一个字段的描述
	virtual CFieldPtr GetField(long index);
	//字段的数目
	virtual long FieldCount() const;

	virtual long GetId() const{return m_oid;}

	virtual void SetId(long id) {m_oid =id;}

	//将更改保存回表中
	virtual void Update() =0;
	//在表中删除该记录
	virtual void Delete() =0;
	//根据序号得到字段的值
	virtual FieldValue& GetValue(long index);

public:
	long                    m_oid;
	ITable*                 m_pTable;
	std::vector<FieldValue> m_values; //字段的值


};

typedef  SYSTEM::CSmartPtr<IRow> IRowPtr;




}




#endif