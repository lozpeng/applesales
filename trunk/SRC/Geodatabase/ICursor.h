//////////////////////////////////////////////////////////////////////
// 版权(c) 2008-2020, 天地智绘
// 作者：  champion
// 时间：  2008.5
// 描述：  游标的基类，它可以遍历一个记录集中的记录，
//         也可以更新或者删除这些记录
//////////////////////////////////////////////////////////////////////

#ifndef  _GEODATABASE_ICURSOR_H_
#define  _GEODATABASE_ICURSOR_H_

#include "IRow.h"

namespace Geodatabase
{

class ITable;

class GEODATABASE_DLL ICursor 
{
public:
	ICursor(ITable *pTable){ m_pTable =pTable;}
	virtual ~ICursor() {}

public:

    ITable* GetTable(){return m_pTable;}

	//通过字段名查找字段的序号
	virtual long FindField(const char* name) =0;

	//通过序号得到一个字段的描述
	virtual CFieldPtr GetField(long index) =0;
    //该指针的字段数目
	virtual long FieldCount() const=0;

	virtual IRowPtr NextRow() =0;

	//指针是否已经到最后的位置
	virtual bool IsEOF() const =0;
protected:
	ITable*                 m_pTable;




};

typedef  SYSTEM::CSmartPtr<ICursor> ICursorPtr;




}




#endif