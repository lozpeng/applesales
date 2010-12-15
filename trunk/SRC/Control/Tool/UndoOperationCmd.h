#ifndef _UNDO_OPERATION_TOOL_H
#define _UNDO_OPERATION_TOOL_H

#include "ICommand.h"
#include "IMapCtrl.h"

namespace Control
{

	class  CUndoOperationCmd : public Framework::ICommand
	{
	public:
		CUndoOperationCmd();
		~CUndoOperationCmd();

	public:
		virtual void Initialize(Framework::IUIObject *pTargetControl);

		void Click();

	protected:
		Framework::IMapCtrl *m_pMapCtrl;

	};

}


#endif