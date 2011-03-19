#ifndef _CREATEFEATURE_TASK_H_
#define _CREATEFEATURE_TASK_H_
#include "iedittask.h"

namespace Editor
{

//新建要素任务
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