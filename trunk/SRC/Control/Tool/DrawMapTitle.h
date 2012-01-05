#ifndef _DRAW_MAP_TITLE_H
#define _DRAW_MAP_TITLE_H

#include "ITool.h"
#include "ILayoutCtrl.h"

namespace Control
{

class  CDrawMapTitle : public Framework::ICommand
{
public:
	CDrawMapTitle();
	~CDrawMapTitle();

public:
	virtual void Initialize(Framework::IUIObject *pTargetControl);

	void Click();

protected:
	Framework::ILayoutCtrl *m_pLayoutCtrl;

};

}


#endif