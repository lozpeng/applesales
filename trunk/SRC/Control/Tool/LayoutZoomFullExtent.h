#ifndef _ActionLayoutZoomFullExtent_h
#define _ActionLayoutZoomFullExtent_h

#include "ITool.h"
#include "ILayoutCtrl.h"

namespace Control
{

class  CLayoutZoomFullExtentCmd : Framework::ICommand
{
public:
	CLayoutZoomFullExtentCmd();
	~CLayoutZoomFullExtentCmd();

public:
	virtual void Initialize(Framework::IUIObject *pTargetControl);

	void Click();

protected:
	Framework::ILayoutCtrl *m_pLayoutCtrl;

};

}


#endif