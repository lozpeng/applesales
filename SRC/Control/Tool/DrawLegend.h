#ifndef _DRAW_LEGEND_H
#define _DRAW_LEGEND_H

#include "ITool.h"
#include "ILayoutCtrl.h"

namespace Control
{

class  CDrawLegendCmd : public Framework::ICommand
{
public:
	CDrawLegendCmd();
	~CDrawLegendCmd();

public:
	virtual void Initialize(Framework::IUIObject *pTargetControl);

	void Click();

protected:
	Framework::ILayoutCtrl *m_pLayoutCtrl;
};

}


#endif