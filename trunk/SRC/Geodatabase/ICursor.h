//////////////////////////////////////////////////////////////////////
// ��Ȩ(c) 2008-2020, ����ǻ�
// ���ߣ�  champion
// ʱ�䣺  2008.5
// ������  �α�Ļ��࣬�����Ա���һ����¼���еļ�¼��
//         Ҳ���Ը��»���ɾ����Щ��¼
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

	//ͨ���ֶ��������ֶε����
	virtual long FindField(const char* name) =0;

	//ͨ����ŵõ�һ���ֶε�����
	virtual CFieldPtr GetField(long index) =0;
    //��ָ����ֶ���Ŀ
	virtual long FieldCount() const=0;

	virtual IRowPtr NextRow() =0;

	//ָ���Ƿ��Ѿ�������λ��
	virtual bool IsEOF() const =0;
protected:
	ITable*                 m_pTable;




};

typedef  SYSTEM::CSmartPtr<ICursor> ICursorPtr;




}




#endif