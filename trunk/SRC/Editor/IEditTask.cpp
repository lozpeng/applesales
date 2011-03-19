#include "stdafx.h"
#include "IEditTask.h"

namespace Editor
{

IEditTask::IEditTask(void)
{
	m_pEdit =NULL;
}

IEditTask::~IEditTask(void)
{
}

std::string IEditTask::GetName() const
{
	return m_taskName;
}

int IEditTask::GetType() const
{
	return m_taskType;
}

void IEditTask::SetEdit(CEditor *pEdit)
{
	m_pEdit =pEdit;
}

} //namespace Editor
