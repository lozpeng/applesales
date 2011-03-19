#include "stdafx.h"
#include "CreateFeatureTask.h"

namespace Editor
{

CCreateFeatureTask::CCreateFeatureTask(CEditor *pedit)
{
	m_taskName ="创建新要素";
	m_taskType =CreateNewFeatrue;

	m_pEdit =pedit;
}

CCreateFeatureTask::~CCreateFeatureTask(void)
{
   
}

void CCreateFeatureTask::DoWork()
{
   if(m_pEdit==NULL)
   {
	   return;
   }
   //将画笔中的要素添加到图层中
   m_pEdit->AppendGeometry(m_pEdit->GetSketchGeometry());
}

}

