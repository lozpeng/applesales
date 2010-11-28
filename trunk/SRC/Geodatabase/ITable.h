//////////////////////////////////////////////////////////////////////
// ��Ȩ(c) 2008-2020, ����ǻ�
// ���ߣ�  champion
// ʱ�䣺  2008.5
// ������  ���ݿ��Ļ���
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
	//������¼����Ŀ
	virtual long RowCount() const =0;

	///////����Ϊ��¼�Ĳ�������///////////////////////////////////////////////////
	//�ڱ��д���һ���յļ�¼������Ϊ��
	virtual IRowPtr CreateRow() =0;

	//���ݼ�¼ID��ȡ��¼
	virtual IRowPtr GetRow(long index) =0;

	//���һ���µļ�¼
	virtual void AddRow(IRow* pRow) =0;

	//����һ����¼
	virtual void UpdateRow(IRow* pRow) =0;

	//ɾ��һ����¼
	virtual void DeleteRow(long index) =0;

	///////����Ϊ�ֶεĲ�������///////////////////////////////////////////////////
	//���һ���µ��ֶ�
	virtual void AddField(CField* pField) =0;

	//ɾ��һ���ֶ�
	virtual void DeleteField(long index) =0;

	//ͨ���ֶ��������ֶε����
	virtual long FindField(const char* name) =0;

	//ͨ����ŵõ�һ���ֶε�����
	virtual CFieldPtr GetField(long index) =0;

	virtual long FieldCount() const=0;

	///////����Ϊ��ѯ�Ĳ�������///////////////////////////////////////////////////

	//ͨ����ѯ�������в�ѯ������һ��ѡ��
	virtual ISelctionSetPtr Select(CSimpleQuery* query) =0;

	//ͨ����ѯ������ѯ������һ��ָ��
	virtual ICursorPtr Query(CSimpleQuery* query,bool bReadOnly =true) =0;

};

typedef  SYSTEM::CSmartPtr<ITable> ITablePtr;





}




#endif