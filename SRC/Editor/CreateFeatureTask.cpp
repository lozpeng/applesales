#include "stdafx.h"
#include "CreateFeatureTask.h"

namespace Editor
{

CCreateFeatureTask::CCreateFeatureTask(CEditor *pedit)
{
	m_taskName ="������Ҫ��";
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
   //�������е�Ҫ����ӵ�ͼ����
   m_pEdit->AppendGeometry(m_pEdit->GetSketchGeometry());
}

}

