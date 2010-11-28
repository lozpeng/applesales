#include "stdafx.h"
#include "IRow.h"
#include "ITable.h"

namespace Geodatabase{


IRow::IRow(ITable *pTable,long oid)
{
	m_pTable =pTable;
	m_oid =oid;
	//值的数目设为字段的数目
	m_values.resize(pTable->FieldCount());
}

IRow::~IRow()
{
   
}

CFieldPtr IRow::GetField(long index)
{
	if(m_pTable)
	{
		return m_pTable->GetField(index);
	}
	else
	{
		return CFieldPtr();
	}
}

long IRow::FieldCount() const
{
	return m_pTable->FieldCount();
}

FieldValue& IRow::GetValue(long index)
{
	if(index>=1 && index<=m_values.size())
	{
		return m_values[index-1];
	}
	else
	{
		return FieldValue();
	}
}


} //namespace Geodatabase