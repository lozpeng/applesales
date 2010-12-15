#ifndef _DELETE_ELEMENT_CMD_H
#define _DELETE_ELEMENT_CMD_H

#include "ICommand.h"
#include "IMapCtrl.h"

namespace Control
{
	class  CDeleteElementCmd : public Framework::ICommand
	{
	public:
		CDeleteElementCmd();
		~CDeleteElementCmd();

	public:
		void Click();
		virtual void Initialize(Framework::IUIObject *pTargetControl);
	protected:
		Framework::IMapCtrl* m_pMapCtrl;

	};

}


#endif