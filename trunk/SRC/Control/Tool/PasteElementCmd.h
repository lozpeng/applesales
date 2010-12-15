#ifndef _PASTE_ELEMENT_CMD_H
#define _PASTE_ELEMENT_CMD_H

#include "ICommand.h"
#include "IMapCtrl.h"

namespace Control
{

	class CPasteElementCmd : public Framework::ICommand
	{
	public:
		CPasteElementCmd();
		~CPasteElementCmd();

	public:
		void Click();
		virtual void Initialize(Framework::IUIObject *pTargetControl);
	protected:
		Framework::IMapCtrl* m_pMapCtrl;

	};

}


#endif