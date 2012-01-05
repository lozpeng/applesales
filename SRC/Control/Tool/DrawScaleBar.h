#ifndef _DRAW_SCALEBAR_H
#define _DRAW_SCALEBAR_H

#include "ITool.h"
#include "ILayoutCtrl.h"

namespace Control
{

	class  CDrawScaleBarCmd : public Framework::ICommand
	{
	public:
		CDrawScaleBarCmd();
		~CDrawScaleBarCmd();

	public:
		virtual void Initialize(Framework::IUIObject *pTargetControl);

		void Click();

	protected:
		Framework::ILayoutCtrl *m_pLayoutCtrl;
	};

}


#endif