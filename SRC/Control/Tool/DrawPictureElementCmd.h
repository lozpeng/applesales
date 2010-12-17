#ifndef _Draw_Picture_Element_CMD_h
#define _Draw_Picture_Element_CMD_h

#include "ICommand.h"
#include "IMapCtrl.h"

namespace Control
{

class  CDrawPictureElementCmd : public Framework::ICommand
{
public:
	CDrawPictureElementCmd();
	~CDrawPictureElementCmd();

	void Initialize(Framework::IUIObject *pTargetControl);
public:
	void Click();

protected:
	Framework::IMapCtrl* m_pMapCtrl;
};

}


#endif