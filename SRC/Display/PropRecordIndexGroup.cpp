#include "stdafx.h"
#include "PropRecordIndexGroup.h"

namespace Display{
CPropRecordIndexGroup::CPropRecordIndexGroup(void)
{

}

CPropRecordIndexGroup::~CPropRecordIndexGroup(void)
{

}

void CPropRecordIndexGroup::AddRecordIndex(unsigned int value)
{
	m_hotRecordIndex.Add(value);
}

void CPropRecordIndexGroup::RemoveValueByIndex(unsigned int index)
{
	m_hotRecordIndex.RemoveAt(index);
}

void CPropRecordIndexGroup::InsertRecordIndex(unsigned int value , unsigned int index)
{
	m_hotRecordIndex.InsertAt(index , value);
}

void CPropRecordIndexGroup::Clear()
{
	m_hotRecordIndex.RemoveAll();
}

const unsigned int& CPropRecordIndexGroup::GetRecordIndexByIndex(unsigned int index)
{
	 return m_hotRecordIndex.ElementAt(index);
}

int CPropRecordIndexGroup::GetRecordIndexSize()
{
	return m_hotRecordIndex.GetSize();
}

}