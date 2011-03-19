#ifndef _SwipeCommand_H_
#define _SwipeCommand_H_
#pragma once
#include "ITool.h"
#include "DlgSwipeSld.h"

namespace Control
{
	class CONTROL_DLL CSwipeCommand:public Framework::ICommand
	{
	public:
		CSwipeCommand(void);
		~CSwipeCommand(void);
	public:
		void Click();
	};
}

#endif//_SwipeCommand_H_