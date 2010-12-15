#ifndef _COPY_ELEMENTS_CMD_H
#define _COPY_ELEMENTS_CMD_H

#include "ICommand.h"
#include "IMapCtrl.h"

namespace Control
{

class  CCopyElementCmd : public Framework::ICommand
{
public:
	CCopyElementCmd();
	~CCopyElementCmd();

public:
	void Click();
	virtual void Initialize(Framework::IUIObject *pTargetControl);
protected:
	Framework::IMapCtrl* m_pMapCtrl;
};

}


#endif