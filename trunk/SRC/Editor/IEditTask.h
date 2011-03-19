#ifndef _IEDIT_TASK_H
#define _IEDIT_TASK_H

#include "CEditor.h"

namespace Editor
{

	enum EditTaskType
	{
		EditTaskNone,
		CreateNewFeatrue, //创建新要素
		ExtendTrimLine,   //线延长\裁剪
		LineSplit,        //线打断
		PolygonSplit,     //多边形打断
		MirrorFeature     //镜像      
	};


	//编辑任务的接口
	class  IEditTask
	{
	public:
		IEditTask(void);
		virtual ~IEditTask(void);

	public:

		//得到任务名
		virtual std::string GetName() const;

		virtual int  GetType() const;

		virtual void DoWork() =0;

		void SetEdit(CEditor *pEdit);


	protected:

		std::string m_taskName;

		EditTaskType m_taskType;


		CEditor *m_pEdit;



	};

}


#endif
