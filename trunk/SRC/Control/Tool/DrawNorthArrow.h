#ifndef _DRAW_NORTH_ARROW_H
#define _DRAW_NORTH_ARROW_H

#include "ITool.h"
#include "ILayoutCtrl.h"


namespace Control
{

	class  CDrawNorthArrowCmd :public Framework::ICommand
	{
	public:
		CDrawNorthArrowCmd();
		~CDrawNorthArrowCmd();

	public:
		virtual void Initialize(Framework::IUIObject *pTargetControl);

		void Click();

	protected:
		Framework::ILayoutCtrl *m_pLayoutCtrl;
	};

}


#endif