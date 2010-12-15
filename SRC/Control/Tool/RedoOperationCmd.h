#ifndef _REDO_OPERATION_H
#define _REDO_OPERATION_H

#include "ICommand.h"
#include "IMapCtrl.h"

namespace Control
{

	class  CRedoOperationCmd : public Framework::ICommand
	{
	public:
		CRedoOperationCmd();
		~CRedoOperationCmd();
	public:
		void Click();
		virtual void Initialize(Framework::IUIObject *pTargetControl);
	protected:
		Framework::IMapCtrl* m_pMapCtrl;

	};

}


#endif