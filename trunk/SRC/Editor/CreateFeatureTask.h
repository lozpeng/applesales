#ifndef _CREATEFEATURE_TASK_H_
#define _CREATEFEATURE_TASK_H_
#include "iedittask.h"

namespace Editor
{

//�½�Ҫ������
class CCreateFeatureTask :
	public IEditTask
{
public:
	CCreateFeatureTask(CEditor *pedit);
	virtual ~CCreateFeatureTask(void);

public:
	virtual void DoWork();

};

}


#endif