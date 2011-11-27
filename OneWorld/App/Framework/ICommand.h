//////////////////////////////////////////////////////////////////////
// ��Ȩ(c) 2010-2020, 
// ���ߣ�  hhz
// ʱ�䣺  2010.12
// ������  �������
//////////////////////////////////////////////////////////////////////
#ifndef  _ICOMMAND_H_
#define  _ICOMMAND_H_

#include <map>
#include "IUIObject.h"


namespace Framework
{
	class FRAMEWORK_DLL ICommand
	{
	public:
		ICommand(const char* name);
		~ICommand(void);


	public:
		//�������
		std::string GetName();

		//�����ʼ��
		virtual void Initialize(IUIObject *pTargetControl);

	public:
		//ͨ�����Ƶõ��������
		static ICommand* FindCommand(std::string strName);

		//ע������
		static void RegisterCommand(std::string strName, ICommand* pCommand);

		//��Ϣ
		virtual void Click();
	protected:

		std::string m_strName;

		//���������ؼ�
		IUIObject *m_pTarget;


	protected:

		static std::map<std::string,ICommand*> gCommands;
	};


}

#endif