#ifndef _LayoutMapZoomFullExtent_h
#define _LayoutMapZoomFullExtent_h


#include "ITool.h"
#include "ILayoutCtrl.h"

namespace Control
{

class  CLayoutMapZoomFullExtent : public Framework::ICommand
{
public:
	CLayoutMapZoomFullExtent();
	~CLayoutMapZoomFullExtent();

public:
	virtual void Initialize(Framework::IUIObject *pTargetControl);

	void Click();

protected:
	Framework::ILayoutCtrl *m_pLayoutCtrl;

};

}


#endif