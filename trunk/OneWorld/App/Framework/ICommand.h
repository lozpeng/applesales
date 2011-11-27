//////////////////////////////////////////////////////////////////////
// 版权(c) 2010-2020, 
// 作者：  hhz
// 时间：  2010.12
// 描述：  命令基类
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
		//获得名称
		std::string GetName();

		//命令初始化
		virtual void Initialize(IUIObject *pTargetControl);

	public:
		//通过名称得到命令对象
		static ICommand* FindCommand(std::string strName);

		//注册命令
		static void RegisterCommand(std::string strName, ICommand* pCommand);

		//消息
		virtual void Click();
	protected:

		std::string m_strName;

		//命令所属控件
		IUIObject *m_pTarget;


	protected:

		static std::map<std::string,ICommand*> gCommands;
	};


}

#endif