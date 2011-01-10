#ifndef _Draw_MapElement_TOOL_h
#define _Draw_MapElement_TOOL_h

#include "ICommand.h"
#include "ILayoutCtrl.h"

namespace Control
{

	class  CDrawMapFrameElementCmd : public Framework::ICommand
	{


	public:
		CDrawMapFrameElementCmd();
		~CDrawMapFrameElementCmd();

	public:
		virtual void Initialize(Framework::IUIObject *pTargetControl);

		void Click();

	protected:
		Framework::ILayoutCtrl *m_pLayoutCtrl;
	};

}


#endif