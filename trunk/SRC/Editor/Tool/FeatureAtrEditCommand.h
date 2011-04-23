#ifndef __FEATURE_ATREDIT_COMMAND_H
#define __FEATURE_ATREDIT_COMMAND_H

#include "ICommand.h"

namespace Editor
{
	class CFeatureAtrEditCommand : public Framework::ICommand
	{
	public:
		CFeatureAtrEditCommand();
		~CFeatureAtrEditCommand();

	public:
		//≥ı ºªØ
		void Initialize(Framework::IUIObject *pTargetControl);

		void Click();

	};


}
#endif