#ifndef _ActionLayoutZoomActualSize_h
#define _ActionLayoutZoomActualSize_h

#include "ITool.h"
#include "ILayoutCtrl.h"

namespace Control
{

class  CLayoutZoomActualSizeCmd : Framework::ICommand
{
public:
	CLayoutZoomActualSizeCmd();
	~CLayoutZoomActualSizeCmd();

public:
	virtual void Initialize(Framework::IUIObject *pTargetControl);

	void Click();

protected:
	Framework::ILayoutCtrl *m_pLayoutCtrl;

};

}


#endif