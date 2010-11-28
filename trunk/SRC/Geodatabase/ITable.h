//////////////////////////////////////////////////////////////////////
// 版权(c) 2008-2020, 天地智绘
// 作者：  champion
// 时间：  2008.5
// 描述：  数据库表的基类
//////////////////////////////////////////////////////////////////////

#ifndef  _GEODATABASE_ITABLE_H_
#define  _GEODATABASE_ITABLE_H_

#include "IRow.h"
#include "Field.h"
#include "ISelectionSet.h"
#include "ICursor.h"
#include <string>
#include "IGeodataObject.h"

namespace Geodatabase
{

class IWorkspace;
class CSimpleQuery;

class GEODATABASE_DLL ITable : public IGeodataObject
{
public:
	ITable(IWorkspace *pWorkspace);
	virtual ~ITable();

public:
	//包含记录的数目
	virtual long RowCount() const =0;

	///////以下为记录的操作方法///////////////////////////////////////////////////
	//在表中创建一个空的记录，属性为空
	virtual IRowPtr CreateRow() =0;

	//根据记录ID获取记录
	virtual IRowPtr GetRow(long index) =0;

	//添加一条新的记录
	virtual void AddRow(IRow* pRow) =0;

	//更新一条记录
	virtual void UpdateRow(IRow* pRow) =0;

	//删除一条记录
	virtual void DeleteRow(long index) =0;

	///////以下为字段的操作方法///////////////////////////////////////////////////
	//添加一条新的字段
	virtual void AddField(CField* pField) =0;

	//删除一个字段
	virtual void DeleteField(long index) =0;

	//通过字段名查找字段的序号
	virtual long FindField(const char* name) =0;

	//通过序号得到一个字段的描述
	virtual CFieldPtr GetField(long index) =0;

	virtual long FieldCount() const=0;

	///////以下为查询的操作方法///////////////////////////////////////////////////

	//通过查询条件进行查询，返回一个选择集
	virtual ISelctionSetPtr Select(CSimpleQuery* query) =0;

	//通过查询条件查询，返回一个指针
	virtual ICursorPtr Query(CSimpleQuery* query,bool bReadOnly =true) =0;

};

typedef  SYSTEM::CSmartPtr<ITable> ITablePtr;





}




#endif