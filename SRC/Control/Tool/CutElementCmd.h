#ifndef _CUT_ELEMENT_CMD_H
#define _CUT_ELEMENT_CMD_H

#include "ICommand.h"
#include "IMapCtrl.h"

namespace Control
{

class CCutElementCmd : public Framework::ICommand
{
public:
	CCutElementCmd();
	~CCutElementCmd();

public:
	void Click();
	virtual void Initialize(Framework::IUIObject *pTargetControl);
protected:
	Framework::IMapCtrl* m_pMapCtrl;

};

}


#endif