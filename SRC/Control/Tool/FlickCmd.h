#ifndef _FlickCmd_H_
#define _FlickCmd_H_

#pragma once

#include "ITool.h"
#include "TransparentDLG.h"

namespace Control
{
	class CONTROL_DLL CFlickCmd : public Framework::ICommand
	{
	public:
		CFlickCmd(void);
		~CFlickCmd(void);

	public:
		void Click();
	};
}

#endif //_FlickCmd_H_


