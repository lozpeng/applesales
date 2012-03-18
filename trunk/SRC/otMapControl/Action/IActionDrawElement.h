#ifndef _Action_Draw_Element_h
#define _Action_Draw_Element_h

#include "IAction.h"


class IActionDrawElement :public IAction
{
public:
	IActionDrawElement(long id);
	~IActionDrawElement(void);

public:
	virtual void Init(CotMapCtrl *pMapCtrl,Carto::CMap *pMap);

	void LButtonDownEvent (UINT nFlags, CPoint point);
	void MouseMoveEvent (UINT nFlags, CPoint point);
	void LButtonUpEvent (UINT nFlags, CPoint point);
	void LButtonDblClkEvent (UINT nFlags, CPoint point);

protected:
	CPoint cPtStart,cPtEnd;
};


#endif
