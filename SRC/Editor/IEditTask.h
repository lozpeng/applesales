#ifndef _IEDIT_TASK_H
#define _IEDIT_TASK_H

#include "CEditor.h"

namespace Editor
{

	enum EditTaskType
	{
		EditTaskNone,
		CreateNewFeatrue, //������Ҫ��
		ExtendTrimLine,   //���ӳ�\�ü�
		LineSplit,        //�ߴ��
		PolygonSplit,     //����δ��
		MirrorFeature     //����      
	};


	//�༭����Ľӿ�
	class  IEditTask
	{
	public:
		IEditTask(void);
		virtual ~IEditTask(void);

	public:

		//�õ�������
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
